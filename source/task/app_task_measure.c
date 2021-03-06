/*******************************************************************************
 *   Revised:        All copyrights reserved to redmorningcn.
 *   Revision:       v1.0
 *   Writer:	     redmorningcn.
 *
 *   Description:    双击选中 store 按 Ctrl + H, 钩选 Match the case, Replace with
 *                   输入您要的名字，点击 Replace All
 *                   双击选中 Store 按 Ctrl + H, 钩选 Match the case, Replace with
 *                   输入您要的名字，点击 Replace All
 *                   双击选中 STORE 按 Ctrl + H, 钩选 Match the case, Replace with
 *                   输入您要的名字，点击 Replace All
 *                   在 app_cfg.h 中指定本任务的 优先级  （ APP_TASK_STORE_PRIO ）
 *                                            和 任务堆栈（ APP_TASK_STORE_STK_SIZE ）大小
 *                   在 app.h 中声明本任务的     创建函数（ void  App_TaskStoreCreate(void) ）
 *                                            和 看门狗标志位 （ WDTFLAG_Store ）
 *
 *   Notes:
 *     				E-mail: redmorningcn@qq.com
 *
 *******************************************************************************/

/*******************************************************************************
 * INCLUDES
 */
#define  SNL_APP_SOURCE
#include <includes.h>



//#ifdef VSC_INCLUDE_SOURCE_FILE_NAMES
//const  CPU_CHAR  *app_task_key__c = "$Id: $";
//#endif

#define APP_TASK_KEY_EN     DEF_ENABLED
#if APP_TASK_KEY_EN == DEF_ENABLED
/*******************************************************************************
 * CONSTANTS
 */

/*******************************************************************************
 * MACROS
 */
//该任务的控制周期   (OS_CFG_TICK_RATE_HZ)为1S
//#define  KEY_CYCLE_TIME_TICKS     (OS_CFG_TICK_RATE_HZ * 1u)
#define CYCLE_TIME_TICKS_MIN            (OS_TICKS_PER_SEC * 30)

//进气口电磁阀  pd.3
#define     DCF_GPIO_AIR_IN      303  
//出气口电磁阀 pd.2
#define     DCF_GPIO_AIR_OUT     302   
     
     
/*******************************************************************************
 * TYPEDEFS
 */
/***********************************************
* 描述： 任务控制块（TCB）
*/
static  OS_TCB   AppTaskMeasureTCB;

/***********************************************
* 描述： 任务堆栈（STACKS）
*/
static  CPU_STK  AppTaskMeasureStk[ APP_TASK_MEASURE_STK_SIZE ];

/*******************************************************************************
 * LOCAL VARIABLES
 */

/*******************************************************************************
 * GLOBAL VARIABLES
 */
/*******************************************************************************
 * LOCAL FUNCTIONS
 */
static  void    AppTaskMeasure          (void *p_arg);
static  void    APP_MeasureInit         (void);
void            StartAirMeasure         (void);



/*******************************************************************************
 * GLOBAL FUNCTIONS
 */

/*******************************************************************************
 * EXTERN VARIABLES
 */
extern OS_SEM   App_BeepSem;

/*******************************************************************************
 * EXTERN FUNCTIONS
 */

/*******************************************************************************/

/*******************************************************************************
 * 名    称： App_TaskMeasureCreate
 * 功    能： **任务创建
 * 入口参数： 无
 * 出口参数： 无
 * 作　　者： Roger-WY.
 * 创建日期： 2015-02-05
 * 修    改：
 * 修改日期：
 * 备    注： 任务创建函数需要在app.h文件中声明
 *******************************************************************************/
void  App_TaskMeasureCreate(void)
{
    OS_ERR  err;

    /***********************************************
    * 描述： 任务创建
    */
    OSTaskCreate((OS_TCB     *)&AppTaskMeasureTCB,                  // 任务控制块  （当前文件中定义）
                 (CPU_CHAR   *)"App Task Measure",                  // 任务名称
                 (OS_TASK_PTR ) AppTaskMeasure,                     // 任务函数指针（当前文件中定义）
                 (void       *) 0,                              // 任务函数参数
                 (OS_PRIO     ) APP_TASK_MEASURE_PRIO,              // 任务优先级，不同任务优先级可以相同，0 < 优先级 < OS_CFG_PRIO_MAX - 2（app_cfg.h中定义）
                 (CPU_STK    *)&AppTaskMeasureStk[0],               // 任务栈顶
                 (CPU_STK_SIZE) APP_TASK_MEASURE_STK_SIZE / 10,     // 任务栈溢出报警值
                 (CPU_STK_SIZE) APP_TASK_MEASURE_STK_SIZE,          // 任务栈大小（CPU数据宽度 * 8 * size = 4 * 8 * size(字节)）（app_cfg.h中定义）
                 (OS_MSG_QTY  ) 5u,                             // 可以发送给任务的最大消息队列数量
                 (OS_TICK     ) 0u,                             // 相同优先级任务的轮循时间（ms），0为默认
                 (void       *) 0,                              // 是一个指向它被用作一个TCB扩展用户提供的存储器位置
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK |           // 允许堆栈检查该任务
                                OS_OPT_TASK_STK_CLR),           // 创建任务时堆栈清零
                 (OS_ERR     *)&err);                           // 指向错误代码的指针，用于创建结果处理

}

OS_SEM			Bsp_MeasureSem;    	//信号量

/*******************************************************************************
 * 名    称： AppTaskMeasure
 * 功    能： 控制任务
 * 入口参数： p_arg - 由任务创建函数传入
 * 出口参数： 无
 * 作　　者： Roger-WY.
 * 创建日期： 2015-02-05
 * 修    改：
 * 修改日期：
 *******************************************************************************/
static  void  AppTaskMeasure (void *p_arg)
{
    OS_ERR      err;
    /***********************************************
    * 描述： 任务初始化
    */
    INT32U      ticks;
    INT32S      dly = CYCLE_TIME_TICKS_MIN;

    uint16  timeadd  = 0;
    APP_MeasureInit();

    BSP_OS_SemCreate(&Bsp_MeasureSem,0, "Bsp MeasureSem");      // 创建信号量
    BSP_OS_SemWait(&Bsp_MeasureSem,1);
    BSP_OS_TimeDlyMs(5000);
 
    
        
    while (DEF_TRUE) {
        /***********************************************
        * 描述： 本任务看门狗标志置位
        */
        OSSetWdtFlag( WDT_FLAG_MEASURE );
            
        /***********************************************
        * 描述： 得到系统当前时间
        */
        ticks = OSTimeGet(&err);
        /***********************************************
        * 描述： 等待10min后，测试
        */
            // 等待信号量 10min
        if(Ctrl.sRunPara.MeasureMin >60 || Ctrl.sRunPara.MeasureMin < 1)
            Ctrl.sRunPara.MeasureMin = 15;
        
 
        timeadd++;
        if (     (timeadd > Ctrl.sRunPara.MeasureMin*2 )
           ||   (1 == BSP_OS_SemWait(&Bsp_MeasureSem,dly)) 
            )
        {
            StartAirMeasure();
            timeadd= 0;
        }
        
        /***********************************************
        * 描述： 去除任务运行的时间，等到一个控制周期里剩余需要延时的时间
        */
        dly   = CYCLE_TIME_TICKS_MIN - ( OSTimeGet(&err) - ticks );
        if ( dly  <= 0 ) {
            dly   = 1;
        }else if(dly > CYCLE_TIME_TICKS_MIN)
        {
            dly   =  CYCLE_TIME_TICKS_MIN;
        }
    }
}

#define DCF_OPEN    0
#define DCF_CLOSE   1

/*******************************************************************************
 * 作　　者： redmorningcn.
 * 创建日期： 2017-11-22
 * 修    改：
 * 修改日期：
 *******************************************************************************/
void        Measure_GPIO_Init(void)
{
    //端口初始化为I/O口
    GPIO_Config(DCF_GPIO_AIR_IN,0);
    GPIO_Config(DCF_GPIO_AIR_OUT,0);
    
    GPIO_Set(DCF_GPIO_AIR_IN, DCF_CLOSE);   //关闭电磁阀
    GPIO_Set(DCF_GPIO_AIR_OUT,DCF_CLOSE);   //关闭电磁阀
    
    Ctrl.sRunPara.SysSts.OpenAir = 0;  //气路打开标识置1
    Ctrl.sRunPara.SysSts.CloseAir= 1;         
}

/*******************************************************************************
 * 作　　者： redmorningcn.
 * 创建日期： 2017-11-23
 * 修    改： 打开 电磁阀，先打开输出，再打开输入。然后置测量标识
              关闭 电磁阀，先关输入，在关输出。然后置测试标识
 * 修改日期：
 *******************************************************************************/
void    CloseAir(void)
{
    //OS_ERR  err;

    ////////关闭测试
    GPIO_Set(DCF_GPIO_AIR_IN,DCF_CLOSE);    //先关输入
    //OSTimeDly(1000, OS_OPT_TIME_DLY, &err);           //延时0.1s
    BSP_OS_TimeDlyMs(500);

    
    GPIO_Set(DCF_GPIO_AIR_OUT,DCF_CLOSE);   //再关输出

}

/*******************************************************************************
 * 作　　者： redmorningcn.
 * 创建日期： 2017-11-22
 * 修    改： 打开 电磁阀，先打开输出，再打开输入。然后置测量标识
              关闭 电磁阀，先关输入，在关输出。然后置测试标识
 * 修改日期：
 *******************************************************************************/
void    StartAirMeasure(void)
{
    //OS_ERR  err;

    ////////启动测试
    GPIO_Set(DCF_GPIO_AIR_OUT,DCF_OPEN);    //打开输出
    //OSTimeDly(1000, OS_OPT_TIME_DLY, &err);           //延时0.5s
    BSP_OS_TimeDlyMs(500);
    
    GPIO_Set(DCF_GPIO_AIR_IN,DCF_OPEN);     //打开输出
    //OSTimeDly(1000, OS_OPT_TIME_DLY, &err);           //延时0.1s

    Ctrl.sRunPara.SysSts.OpenAir = 1;          //气路打开标识置1
    Ctrl.sRunPara.SysSts.CloseAir= 0; 
    
    //OSTimeDly(12000, OS_OPT_TIME_DLY, &err);          //延时12s
    //BSP_OS_TimeDlyMs(12000);
    if(     Ctrl.sRunPara.MeasureSecond >30 
       ||   Ctrl.sRunPara.MeasureSecond < 1)
    {
        Ctrl.sRunPara.MeasureSecond = 3;
    }
    
    BSP_OS_TimeDlyMs(Ctrl.sRunPara.MeasureSecond*1000);

    Ctrl.sRunPara.SysSts.StartMeasure = 1;
    
    Ctrl.sRunPara.SysSts.Store   = 1;                       //可以进行数据储存（测量过程的数据）
    osal_set_event(OS_TASK_ID_STORE,OS_EVT_STORE_TICKS);    //设置存储事件，启动储存任务
    BSP_OS_TimeDlyMs(10);

    CloseAir();                                 //关闭气路
      
    Ctrl.sRunPara.SysSts.OpenAir = 0;           //气路打开标识置1
    Ctrl.sRunPara.SysSts.CloseAir= 1;     
    
    Ctrl.sRunPara.SysSts.StartMeasure = 0;
}


/*******************************************************************************
 * 名    称： APP_MeasureInit
 * 功    能： 任务初始化
 * 入口参数： 无
 * 出口参数： 无
 * 作　　者： Roger-WY.
 * 创建日期： 2015-03-28
 * 修    改：
 * 修改日期：
 *******************************************************************************/
static void APP_MeasureInit(void)
{
    /***********************************************
    * 描述： 初始化本任务用到的相关硬件
    */
    Measure_GPIO_Init();            //初始化端口

    /***********************************************
    * 描述： 在看门狗标志组注册本任务的看门狗标志
    */
    OSRegWdtFlag( WDT_FLAG_MEASURE );
}

/*******************************************************************************
 * 				end of file
 *******************************************************************************/
#endif
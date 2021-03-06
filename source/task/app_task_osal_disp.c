/*******************************************************************************
* Description  : 数码管显示任务
* Author       : 2018/5/16 星期三, by redmorningcn
*******************************************************************************/

/*******************************************************************************
 * INCLUDES
 */
#include <includes.h>
#include <bsp_max7219.h>
     
#ifdef VSC_INCLUDE_SOURCE_FILE_NAMES
const  CPU_CHAR  *app_task_disp__c = "$Id: $";
#endif

#define APP_TASK_DISP_EN     DEF_ENABLED
#if APP_TASK_DISP_EN == DEF_ENABLED
/*******************************************************************************
 * CONSTANTS
 */
#define CYCLE_TIME_TICKS     (OS_CFG_TICK_RATE_HZ * 1u)

/*******************************************************************************
 * MACROS
 */

/*******************************************************************************
 * TYPEDEFS
 */

/*******************************************************************************
 * LOCAL VARIABLES
 */
#if ( OSAL_EN == DEF_ENABLED )
#else
/***********************************************
* 描述： 任务控制块（TCB）
*/

/***********************************************
* 描述： 任务堆栈（STACKS）
*/

#endif     
     
static  uint8       dis_mode    =   0;
         uint16      ErrCode     =   0;

/*******************************************************************************
 * GLOBAL VARIABLES
 */

/*******************************************************************************
 * LOCAL FUNCTIONS
 */
     
#if ( OSAL_EN == DEF_ENABLED )
#else
static  void                AppTaskDisp           (void *p_arg);
#endif

/*******************************************************************************
 * GLOBAL FUNCTIONS
 */


/*******************************************************************************
 * EXTERN VARIABLES
 */

#define     DIS_INFO_NUM        9
#define     DIS_MAX_ERR_NUM     3      





     
/*******************************************************************************
* Description  : 装置正常运行时，循环显示的内容。
                 如果有故障，则显示故障代码。
* Author       : 2018/07/16 星期三, by redmorningcn
*******************************************************************************/
void    LedRunDisplayInfo(void)
{
    static  u8     times = 0;
    u8              mod = 9;
    
    //20180716 电磁兼容补丁
    switch((times/5) % mod)
    //switch(times/% mod)

    {
        case 0: uprintf("T");   
                break;    
        case 1: uprintf("%4d",Ctrl.Rec.sAir.Temperature);   
                break;     
        
        case 2: uprintf("H2o");   
                break;                              //显示湿度提示
        case 3: uprintf("%4d",Ctrl.Rec.sAir.Humidity);   
                break;                              //显示湿度值
        
        case 4: uprintf("o1L");   
                break;                              //显示油含量
        case 5: uprintf("%4d",Ctrl.Rec.sAir.VOCs);     
                break;                              //显示湿度值
        
        case 6: uprintf("dust");                            
                break;                              //显示粉尘提示
        case 7: uprintf("%4d",Ctrl.Rec.sAir.PM2D5_S);   
                break;                              //显示粉尘值  
        default:
            //times = 0;
            break;
    }
    times++;
    
    //20180716 电磁兼容补丁
    times %= (mod*5);
    //times %= mod;
}

/*******************************************************************************
 * 名    称： TaskDispEvtProcess
 * 功    能： 
 * 入口参数： 无
 * 出口参数： 无
 * 作    者： 无名沈
 * 创建日期： 2017/12/5
 * 修    改： 
 * 修改日期： 
 * 备    注： 
 *******************************************************************************/
osalEvt  TaskDispEvtProcess(osalTid task_id, osalEvt task_event)
{
    /***********************************************
    * 描述： 本任务看门狗标志置位
    */
    OSSetWdtFlag(( OS_FLAGS     ) WDT_FLAG_DISP);
    
    //20180716 电磁兼容补丁
    LED_SPI_SendData( MAX7279_DISP_TEST,0x00 );                         // 设置工作模式
    LED_SPI_SendData( MAX7279_SCAN,MAX7279_8_DIGIT_SCAN );              // 设置扫描界限
    LED_SPI_SendData( MAX7279_DECODE_MODE,MAX7279_DECODE_SET );         // 设置译码模式
    LED_SPI_SendData( MAX7279_BRIGHTNESS,MAX7279_BRIGHTNESS_LEVEL );    // 设置亮度
    LED_SPI_SendData( MAX7279_LOW_PWR,MAX7279_NORMAL_MODE );            // 设置为正常工作模式
    //20180716 电磁兼容补丁
    
    /***********************************************
    * 描述： 2017/11/27,无名沈：
    */
    if( task_event & OS_EVT_DISP_TICKS ) {
        OS_TICK         dly;
        OS_TICK         ticks;
        OS_ERR          err;
        
        /***********************************************
        * 描述： 得到系统当前时间
        */
        ticks = OSTimeGet(&err);
        
        /***********************************************
        * 描述： 根据显示模式显示
        */
        switch(dis_mode) {
            /*******************************************************************
            * 描述： 显示装置时间
            */
        case 0:         //车型
            dis_mode++;
            uprintf("%d",Ctrl.sProductInfo.LocoId.Type);  
            break;
        case 1:         //车号
            dis_mode++;
            uprintf("%d",Ctrl.sProductInfo.LocoId.Nbr);  
            break;
            
            /*******************************************************************
            * 描述： 显示软件版本
            *        时间：开机显示一次，显示2s；
            */
        case 2: 
            dis_mode++;
                uprintf("%2d.%02d",Ctrl.sProductInfo.SwVer/100,Ctrl.sProductInfo.SwVer%100);  
            break;
            
            /*******************************************************************
            * 描述： 粉尘修正值
            */
        case 3: 
            dis_mode++;
            uprintf("%d.",Ctrl.sAirPara.Dust_modefy);  
            break;
            /*******************************************************************
            * 描述： 湿度修正值
            */
        case 4:  
            dis_mode++;
            uprintf("%d.",Ctrl.sAirPara.Hum_modefy);  
            break;  
            /*******************************************************************
            * 描述： Voc修正值
            */
        case 5:  
            dis_mode++;
            uprintf("%d.",Ctrl.sAirPara.Voc_modefy);  
            break; 
            /*******************************************************************
            * 描述： 车型车号
            */
        case 6:  
            dis_mode++;
            uprintf("      ");
            
            break; 
            /*******************************************************************
            * 描述： 全灭
            */
        case 7:  
            dis_mode++;
            uprintf("88888888");
            
            break;   
            /*******************************************************************
            * 描述： 
            */

        default: 
            
            LedRunDisplayInfo();       //正常运行时显示内容
            break;
        }
        /***********************************************
        * 描述： 2018/1/30,无名沈：增加亮度调节,亮度值改变，调整亮度。 
        */
        static  int displevel = 10;  
        if(Ctrl.sRunPara.SysSts.DispLevel != displevel)
        {
            BSP_DispSetBrightness(Ctrl.sRunPara.SysSts.DispLevel); 
            displevel = Ctrl.sRunPara.SysSts.DispLevel;
        }
        /***********************************************
        * 描述： 去除任务运行的时间，等到一个控制周期里剩余需要延时的时间
        */
        dly   = CYCLE_TIME_TICKS - ( OSTimeGet(&err) - ticks );
        
        //20180716 电磁兼容补丁
        if(dis_mode > 7)
            dly /=5;
        
        if ( dly  < 1 ) {
            dly = 1;
        } else if ( dly > CYCLE_TIME_TICKS ) {
            dly = CYCLE_TIME_TICKS;
        } 
        
        osal_start_timerEx( OS_TASK_ID_DISP,
                           OS_EVT_DISP_TICKS,
                           dly);
        
        return ( task_event ^ OS_EVT_DISP_TICKS );
    }
    
    return 0;
}

/*******************************************************************************
 * 名    称： App_DispDelay
 * 功    能： 将显示任务挂起一段时间，用来显示其他内容
 * 入口参数： 无
 * 出口参数： 无
 * 作    者： 无名沈
 * 创建日期： 2017/12/20
 * 修    改： 
 * 修改日期： 
 * 备    注： 
 *******************************************************************************/
void App_DispDelay( osalTime dly)
{    
    osal_start_timerEx( OS_TASK_ID_DISP,
                        OS_EVT_DISP_TICKS,
                        dly);
}

/*******************************************************************************
 * 名    称： APP_DispInit
 * 功    能： 任务初始化
 * 入口参数： 无
 * 出口参数： 无
 * 作　 　者： wumingshen.
 * 创建日期： 2015-12-08
 * 修    改：
 * 修改日期：
 *******************************************************************************/
void TaskInitDisp(void)
{    
    /***********************************************
    * 描述： 初始化本任务用到的相关硬件
    */
    BSP_DispInit();
    /***********************************************
    * 描述： 2017/12/3,无名沈：关闭显示
    */
    BSP_DispOff();
    /***********************************************
    * 描述： 2018/1/30,无名沈：增加亮度调节默认参数
    */
    if ( Ctrl.sRunPara.SysSts.DispLevel == 0 )
         Ctrl.sRunPara.SysSts.DispLevel = 10;
    /***********************************************
    * 描述： 2017/12/3,无名沈：设置显示亮度
    */
    BSP_DispSetBrightness(Ctrl.sRunPara.SysSts.DispLevel);
    /***********************************************
    * 描述： 2017/12/3,无名沈：清除所有显示
    */
    BSP_DispClrAll();
    /***********************************************
    * 描述： 2017/12/3,无名沈：开机所有数码管显示8
    */
    uprintf("8.8.8.8.8.8.8.8."); 
    BSP_DispEvtProcess(); 
    
    /***********************************************
    * 描述： 在看门狗标志组注册本任务的看门狗标志
    */
    OSRegWdtFlag(( OS_FLAGS     )WDT_FLAG_DISP );
    
    /*************************************************
    * 描述：启动事件查询
    */
    osal_start_timerEx( OS_TASK_ID_DISP,
                        OS_EVT_DISP_TICKS,
                        OS_TICKS_PER_SEC);
    
}


/*******************************************************************************
 * 				                    end of file                                *
 *******************************************************************************/
#endif
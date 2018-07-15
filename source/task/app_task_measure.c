/*******************************************************************************
 *   Revised:        All copyrights reserved to redmorningcn.
 *   Revision:       v1.0
 *   Writer:	     redmorningcn.
 *
 *   Description:    ˫��ѡ�� store �� Ctrl + H, ��ѡ Match the case, Replace with
 *                   ������Ҫ�����֣���� Replace All
 *                   ˫��ѡ�� Store �� Ctrl + H, ��ѡ Match the case, Replace with
 *                   ������Ҫ�����֣���� Replace All
 *                   ˫��ѡ�� STORE �� Ctrl + H, ��ѡ Match the case, Replace with
 *                   ������Ҫ�����֣���� Replace All
 *                   �� app_cfg.h ��ָ��������� ���ȼ�  �� APP_TASK_STORE_PRIO ��
 *                                            �� �����ջ�� APP_TASK_STORE_STK_SIZE ����С
 *                   �� app.h �������������     ���������� void  App_TaskStoreCreate(void) ��
 *                                            �� ���Ź���־λ �� WDTFLAG_Store ��
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
//������Ŀ�������   (OS_CFG_TICK_RATE_HZ)Ϊ1S
//#define  KEY_CYCLE_TIME_TICKS     (OS_CFG_TICK_RATE_HZ * 1u)
#define CYCLE_TIME_TICKS_MIN            (OS_TICKS_PER_SEC * 30)

//�����ڵ�ŷ�  pd.3
#define     DCF_GPIO_AIR_IN      303  
//�����ڵ�ŷ� pd.2
#define     DCF_GPIO_AIR_OUT     302   
     
     
/*******************************************************************************
 * TYPEDEFS
 */
/***********************************************
* ������ ������ƿ飨TCB��
*/
static  OS_TCB   AppTaskMeasureTCB;

/***********************************************
* ������ �����ջ��STACKS��
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

//static  void    MeasureValueHandle      (StrCtrlDCB *dcb);


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
 * ��    �ƣ� App_TaskMeasureCreate
 * ��    �ܣ� **���񴴽�
 * ��ڲ����� ��
 * ���ڲ����� ��
 * �������ߣ� Roger-WY.
 * �������ڣ� 2015-02-05
 * ��    �ģ�
 * �޸����ڣ�
 * ��    ע�� ���񴴽�������Ҫ��app.h�ļ�������
 *******************************************************************************/
void  App_TaskMeasureCreate(void)
{
    OS_ERR  err;

    /***********************************************
    * ������ ���񴴽�
    */
    OSTaskCreate((OS_TCB     *)&AppTaskMeasureTCB,                  // ������ƿ�  ����ǰ�ļ��ж��壩
                 (CPU_CHAR   *)"App Task Measure",                  // ��������
                 (OS_TASK_PTR ) AppTaskMeasure,                     // ������ָ�루��ǰ�ļ��ж��壩
                 (void       *) 0,                              // ����������
                 (OS_PRIO     ) APP_TASK_MEASURE_PRIO,              // �������ȼ�����ͬ�������ȼ�������ͬ��0 < ���ȼ� < OS_CFG_PRIO_MAX - 2��app_cfg.h�ж��壩
                 (CPU_STK    *)&AppTaskMeasureStk[0],               // ����ջ��
                 (CPU_STK_SIZE) APP_TASK_MEASURE_STK_SIZE / 10,     // ����ջ�������ֵ
                 (CPU_STK_SIZE) APP_TASK_MEASURE_STK_SIZE,          // ����ջ��С��CPU���ݿ�� * 8 * size = 4 * 8 * size(�ֽ�)����app_cfg.h�ж��壩
                 (OS_MSG_QTY  ) 5u,                             // ���Է��͸�����������Ϣ��������
                 (OS_TICK     ) 0u,                             // ��ͬ���ȼ��������ѭʱ�䣨ms����0ΪĬ��
                 (void       *) 0,                              // ��һ��ָ����������һ��TCB��չ�û��ṩ�Ĵ洢��λ��
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK |           // �����ջ��������
                                OS_OPT_TASK_STK_CLR),           // ��������ʱ��ջ����
                 (OS_ERR     *)&err);                           // ָ���������ָ�룬���ڴ����������

}

OS_SEM			Bsp_MeasureSem;    	//�ź���

/*******************************************************************************
 * ��    �ƣ� AppTaskMeasure
 * ��    �ܣ� ��������
 * ��ڲ����� p_arg - �����񴴽���������
 * ���ڲ����� ��
 * �������ߣ� Roger-WY.
 * �������ڣ� 2015-02-05
 * ��    �ģ�
 * �޸����ڣ�
 *******************************************************************************/
static  void  AppTaskMeasure (void *p_arg)
{
    OS_ERR      err;
    /***********************************************
    * ������ �����ʼ��
    */
    INT32U      ticks;
    INT32S      dly = CYCLE_TIME_TICKS_MIN;

    uint16  timeadd  = 0;
    APP_MeasureInit();

    BSP_OS_SemCreate(&Bsp_MeasureSem,0, "Bsp MeasureSem");      // �����ź���
    BSP_OS_SemWait(&Bsp_MeasureSem,1);
    BSP_OS_TimeDlyMs(5000);
    /***********************************************
    * ������Task body, always written as an infinite loop.
    */
    //OSRegWdtFlag( WDT_FLAG_MEASURE );
        
    while (DEF_TRUE) {
        /***********************************************
        * ������ �������Ź���־��λ
        */
        //OSSetWdtFlag( WDT_FLAG_MEASURE );
            
        /***********************************************
        * ������ �õ�ϵͳ��ǰʱ��
        */
        ticks = OSTimeGet(&err);
        /***********************************************
        * ������ �ȴ�10min�󣬲���
        */
            // �ȴ��ź��� 10min
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
        * ������ ȥ���������е�ʱ�䣬�ȵ�һ������������ʣ����Ҫ��ʱ��ʱ��
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
 * �������ߣ� redmorningcn.
 * �������ڣ� 2017-11-22
 * ��    �ģ�
 * �޸����ڣ�
 *******************************************************************************/
void        Measure_GPIO_Init(void)
{
    //�˿ڳ�ʼ��ΪI/O��
    GPIO_Config(DCF_GPIO_AIR_IN,0);
    GPIO_Config(DCF_GPIO_AIR_OUT,0);
    
    GPIO_Set(DCF_GPIO_AIR_IN, DCF_CLOSE);   //�رյ�ŷ�
    GPIO_Set(DCF_GPIO_AIR_OUT,DCF_CLOSE);   //�رյ�ŷ�
    
    Ctrl.sRunPara.SysSts.OpenAir = 0;  //��·�򿪱�ʶ��1
    Ctrl.sRunPara.SysSts.CloseAir= 1;         
}

/*******************************************************************************
 * �������ߣ� redmorningcn.
 * �������ڣ� 2017-11-23
 * ��    �ģ� �� ��ŷ����ȴ�������ٴ����롣Ȼ���ò�����ʶ
              �ر� ��ŷ����ȹ����룬�ڹ������Ȼ���ò��Ա�ʶ
 * �޸����ڣ�
 *******************************************************************************/
void    CloseAir(void)
{
    //OS_ERR  err;

    ////////�رղ���
    GPIO_Set(DCF_GPIO_AIR_IN,DCF_CLOSE);    //�ȹ�����
    //OSTimeDly(1000, OS_OPT_TIME_DLY, &err);           //��ʱ0.1s
    BSP_OS_TimeDlyMs(500);

    
    GPIO_Set(DCF_GPIO_AIR_OUT,DCF_CLOSE);   //�ٹ����

}

/*******************************************************************************
 * �������ߣ� redmorningcn.
 * �������ڣ� 2017-11-22
 * ��    �ģ� �� ��ŷ����ȴ�������ٴ����롣Ȼ���ò�����ʶ
              �ر� ��ŷ����ȹ����룬�ڹ������Ȼ���ò��Ա�ʶ
 * �޸����ڣ�
 *******************************************************************************/
void    StartAirMeasure(void)
{
    //OS_ERR  err;

    ////////��������
    GPIO_Set(DCF_GPIO_AIR_OUT,DCF_OPEN);    //�����
    //OSTimeDly(1000, OS_OPT_TIME_DLY, &err);           //��ʱ0.5s
    BSP_OS_TimeDlyMs(500);
    
    GPIO_Set(DCF_GPIO_AIR_IN,DCF_OPEN);     //�����
    //OSTimeDly(1000, OS_OPT_TIME_DLY, &err);           //��ʱ0.1s

    Ctrl.sRunPara.SysSts.OpenAir = 1;          //��·�򿪱�ʶ��1
    Ctrl.sRunPara.SysSts.CloseAir= 0; 
    
    //OSTimeDly(12000, OS_OPT_TIME_DLY, &err);          //��ʱ12s
    //BSP_OS_TimeDlyMs(12000);
    if(     Ctrl.sRunPara.MeasureSecond >30 
       ||   Ctrl.sRunPara.MeasureSecond < 1)
    {
        Ctrl.sRunPara.MeasureSecond = 3;
    }
    
    BSP_OS_TimeDlyMs(Ctrl.sRunPara.MeasureSecond*1000);

    Ctrl.sRunPara.SysSts.StartMeasure = 1;
    

    //��ʼ����ʱ��
    osal_start_timerEx( OS_TASK_ID_STORE,
                      OS_EVT_STORE_TICKS,
                      1);                       //�ô洢��ʱ��1�����������洢
    Ctrl.sRunPara.SysSts.Store   = 1;  //���Խ������ݴ��棨�������̵����ݣ�
    

    CloseAir();                                 //�ر���·
      
    Ctrl.sRunPara.SysSts.OpenAir = 0;  //��·�򿪱�ʶ��1
    Ctrl.sRunPara.SysSts.CloseAir= 1;     
    
    Ctrl.sRunPara.SysSts.StartMeasure = 0;
}


/*******************************************************************************
 * ��    �ƣ� APP_MeasureInit
 * ��    �ܣ� �����ʼ��
 * ��ڲ����� ��
 * ���ڲ����� ��
 * �������ߣ� Roger-WY.
 * �������ڣ� 2015-03-28
 * ��    �ģ�
 * �޸����ڣ�
 *******************************************************************************/
static void APP_MeasureInit(void)
{
    /***********************************************
    * ������ ��ʼ���������õ������Ӳ��
    */
    Measure_GPIO_Init();            //��ʼ���˿�

    /***********************************************
    * ������ �ڿ��Ź���־��ע�᱾����Ŀ��Ź���־
    */
    //WdtFlags |= WDT_FLAG_KEY;
}

/*******************************************************************************
 * 				end of file
 *******************************************************************************/
#endif
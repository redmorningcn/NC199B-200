/*******************************************************************************
* Description  : �������ʾ����
* Author       : 2018/5/16 ������, by redmorningcn
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
* ������ ������ƿ飨TCB��
*/

/***********************************************
* ������ �����ջ��STACKS��
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
* Description  : װ����������ʱ��ѭ����ʾ�����ݡ�
                 ����й��ϣ�����ʾ���ϴ��롣
* Author       : 2018/07/16 ������, by redmorningcn
*******************************************************************************/
void    LedRunDisplayInfo(void)
{
    static  u8     times = 0;
    u8              mod = 9;
    
    //20180716 ��ż��ݲ���
    switch((times/5) % mod)
    //switch(times/% mod)

    {
        case 0: uprintf("T");   
                break;    
        case 1: uprintf("%4d",Ctrl.Rec.sAir.Temperature);   
                break;     
        
        case 2: uprintf("H2o");   
                break;                              //��ʾʪ����ʾ
        case 3: uprintf("%4d",Ctrl.Rec.sAir.Humidity);   
                break;                              //��ʾʪ��ֵ
        
        case 4: uprintf("o1L");   
                break;                              //��ʾ�ͺ���
        case 5: uprintf("%4d",Ctrl.Rec.sAir.VOCs);     
                break;                              //��ʾʪ��ֵ
        
        case 6: uprintf("dust");                            
                break;                              //��ʾ�۳���ʾ
        case 7: uprintf("%4d",Ctrl.Rec.sAir.PM2D5_S);   
                break;                              //��ʾ�۳�ֵ  
        default:
            //times = 0;
            break;
    }
    times++;
    
    //20180716 ��ż��ݲ���
    times %= (mod*5);
    //times %= mod;
}

/*******************************************************************************
 * ��    �ƣ� TaskDispEvtProcess
 * ��    �ܣ� 
 * ��ڲ����� ��
 * ���ڲ����� ��
 * ��    �ߣ� ������
 * �������ڣ� 2017/12/5
 * ��    �ģ� 
 * �޸����ڣ� 
 * ��    ע�� 
 *******************************************************************************/
osalEvt  TaskDispEvtProcess(osalTid task_id, osalEvt task_event)
{
    /***********************************************
    * ������ �������Ź���־��λ
    */
    OSSetWdtFlag(( OS_FLAGS     ) WDT_FLAG_DISP);
    
    //20180716 ��ż��ݲ���
    LED_SPI_SendData( MAX7279_DISP_TEST,0x00 );                         // ���ù���ģʽ
    LED_SPI_SendData( MAX7279_SCAN,MAX7279_8_DIGIT_SCAN );              // ����ɨ�����
    LED_SPI_SendData( MAX7279_DECODE_MODE,MAX7279_DECODE_SET );         // ��������ģʽ
    LED_SPI_SendData( MAX7279_BRIGHTNESS,MAX7279_BRIGHTNESS_LEVEL );    // ��������
    LED_SPI_SendData( MAX7279_LOW_PWR,MAX7279_NORMAL_MODE );            // ����Ϊ��������ģʽ
    //20180716 ��ż��ݲ���
    
    /***********************************************
    * ������ 2017/11/27,������
    */
    if( task_event & OS_EVT_DISP_TICKS ) {
        OS_TICK         dly;
        OS_TICK         ticks;
        OS_ERR          err;
        
        /***********************************************
        * ������ �õ�ϵͳ��ǰʱ��
        */
        ticks = OSTimeGet(&err);
        
        /***********************************************
        * ������ ������ʾģʽ��ʾ
        */
        switch(dis_mode) {
            /*******************************************************************
            * ������ ��ʾװ��ʱ��
            */
        case 0:         //����
            dis_mode++;
            uprintf("%d",Ctrl.sProductInfo.LocoId.Type);  
            break;
        case 1:         //����
            dis_mode++;
            uprintf("%d",Ctrl.sProductInfo.LocoId.Nbr);  
            break;
            
            /*******************************************************************
            * ������ ��ʾ����汾
            *        ʱ�䣺������ʾһ�Σ���ʾ2s��
            */
        case 2: 
            dis_mode++;
                uprintf("%2d.%02d",Ctrl.sProductInfo.SwVer/100,Ctrl.sProductInfo.SwVer%100);  
            break;
            
            /*******************************************************************
            * ������ �۳�����ֵ
            */
        case 3: 
            dis_mode++;
            uprintf("%d.",Ctrl.sAirPara.Dust_modefy);  
            break;
            /*******************************************************************
            * ������ ʪ������ֵ
            */
        case 4:  
            dis_mode++;
            uprintf("%d.",Ctrl.sAirPara.Hum_modefy);  
            break;  
            /*******************************************************************
            * ������ Voc����ֵ
            */
        case 5:  
            dis_mode++;
            uprintf("%d.",Ctrl.sAirPara.Voc_modefy);  
            break; 
            /*******************************************************************
            * ������ ���ͳ���
            */
        case 6:  
            dis_mode++;
            uprintf("      ");
            
            break; 
            /*******************************************************************
            * ������ ȫ��
            */
        case 7:  
            dis_mode++;
            uprintf("88888888");
            
            break;   
            /*******************************************************************
            * ������ 
            */

        default: 
            
            LedRunDisplayInfo();       //��������ʱ��ʾ����
            break;
        }
        /***********************************************
        * ������ 2018/1/30,�������������ȵ���,����ֵ�ı䣬�������ȡ� 
        */
        static  int displevel = 10;  
        if(Ctrl.sRunPara.SysSts.DispLevel != displevel)
        {
            BSP_DispSetBrightness(Ctrl.sRunPara.SysSts.DispLevel); 
            displevel = Ctrl.sRunPara.SysSts.DispLevel;
        }
        /***********************************************
        * ������ ȥ���������е�ʱ�䣬�ȵ�һ������������ʣ����Ҫ��ʱ��ʱ��
        */
        dly   = CYCLE_TIME_TICKS - ( OSTimeGet(&err) - ticks );
        
        //20180716 ��ż��ݲ���
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
 * ��    �ƣ� App_DispDelay
 * ��    �ܣ� ����ʾ�������һ��ʱ�䣬������ʾ��������
 * ��ڲ����� ��
 * ���ڲ����� ��
 * ��    �ߣ� ������
 * �������ڣ� 2017/12/20
 * ��    �ģ� 
 * �޸����ڣ� 
 * ��    ע�� 
 *******************************************************************************/
void App_DispDelay( osalTime dly)
{    
    osal_start_timerEx( OS_TASK_ID_DISP,
                        OS_EVT_DISP_TICKS,
                        dly);
}

/*******************************************************************************
 * ��    �ƣ� APP_DispInit
 * ��    �ܣ� �����ʼ��
 * ��ڲ����� ��
 * ���ڲ����� ��
 * ���� ���ߣ� wumingshen.
 * �������ڣ� 2015-12-08
 * ��    �ģ�
 * �޸����ڣ�
 *******************************************************************************/
void TaskInitDisp(void)
{    
    /***********************************************
    * ������ ��ʼ���������õ������Ӳ��
    */
    BSP_DispInit();
    /***********************************************
    * ������ 2017/12/3,�����򣺹ر���ʾ
    */
    BSP_DispOff();
    /***********************************************
    * ������ 2018/1/30,�������������ȵ���Ĭ�ϲ���
    */
    if ( Ctrl.sRunPara.SysSts.DispLevel == 0 )
         Ctrl.sRunPara.SysSts.DispLevel = 10;
    /***********************************************
    * ������ 2017/12/3,������������ʾ����
    */
    BSP_DispSetBrightness(Ctrl.sRunPara.SysSts.DispLevel);
    /***********************************************
    * ������ 2017/12/3,���������������ʾ
    */
    BSP_DispClrAll();
    /***********************************************
    * ������ 2017/12/3,�����򣺿��������������ʾ8
    */
    uprintf("8.8.8.8.8.8.8.8."); 
    BSP_DispEvtProcess(); 
    
    /***********************************************
    * ������ �ڿ��Ź���־��ע�᱾����Ŀ��Ź���־
    */
    OSRegWdtFlag(( OS_FLAGS     )WDT_FLAG_DISP );
    
    /*************************************************
    * �����������¼���ѯ
    */
    osal_start_timerEx( OS_TASK_ID_DISP,
                        OS_EVT_DISP_TICKS,
                        OS_TICKS_PER_SEC);
    
}


/*******************************************************************************
 * 				                    end of file                                *
 *******************************************************************************/
#endif
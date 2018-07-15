/*******************************************************************************
* Description  : LEDָʾ������
* Author       : 2018/5/15 ���ڶ�, by redmorningcn
*******************************************************************************/


/*******************************************************************************
* INCLUDES
*/
#include <includes.h>

#ifdef VSC_INCLUDE_SOURCE_FILE_NAMES
const  CPU_CHAR  *app_task_led__c = "$Id: $";
#endif

/*******************************************************************************
* CONSTANTS
*/

/*******************************************************************************
* MACROS
*/
//LEDָʾ��λ����
#define     RUN_LED             1
#define     X1_SPEED_LED        2
#define     X2_DTU_LED          3
#define     X3_TAX_LED          4
#define     X4_VOL_LED          5

/*******************************************************************************
* TYPEDEFS
*/

/*******************************************************************************
* LOCAL VARIABLES
*/


/*******************************************************************************
* GLOBAL VARIABLES
*/

/*******************************************************************************
* LOCAL FUNCTIONS
*/
#if ( OSAL_EN == DEF_ENABLED )
#else
static  void    AppTaskLed           (void *p_arg);
#endif

/*******************************************************************************
* GLOBAL FUNCTIONS
*/

/*******************************************************************************
* EXTERN VARIABLES
*/

/*******************************************************************************/


/**************************************************************
* Description  : ��ɫ��ָʾ
* Author       : 2018/7/15 ������, by redmorningcn
*/
osalEvt  TaskLedEvtProcess(osalTid task_id, osalEvt task_event)
{

        OSSetWdtFlag( WDT_FLAG_LED );

        if( task_event & OS_EVT_LED_TICKS ) {

            static  uint8   mode = 0;
            /***********************************************
            * ������ ������ʾ.red /green /blue
            */
            while(mode < 12)
            {
                mode++;
                switch(mode %4)
                {
                    case 0:
                            for(uint8 i= 0;i < 3;i++)
                                SetLedColor(i,RGB_LED_COLOR_RED);   break;
                    case 1:
                            for(uint8 i= 0;i < 3;i++)
                                SetLedColor(i,RGB_LED_COLOR_GREEN); break;
                    case 2:
                            for(uint8 i= 0;i < 3;i++)
                                SetLedColor(i,RGB_LED_COLOR_BLUE);  break;
                    case 3:
                            for(uint8 i= 0;i < 3;i++)
                                SetLedColor(i,RGB_LED_COLOR_WHITE); break;
                }
                    
                osal_start_timerEx( OS_TASK_ID_LED,
                                    OS_EVT_LED_TICKS,
                                    600);
                return ( task_event ^ OS_EVT_LED_TICKS );
            }

            /***********************************************
            * ������ ʪ����ʾ
            */
            switch(Ctrl.Rec.Air_Hum_Grade)
            {
                case GOOD_GRADE:
                    SetLedColor(HUM_LED,RGB_LED_COLOR_BLUE);    break;
                case NORMAL_GRADE:
                    SetLedColor(HUM_LED,RGB_LED_COLOR_GREEN);   break;
                case BAD_GRADE:
                    SetLedColor(HUM_LED,RGB_LED_COLOR_RED);     break;
                default:       
                    SetLedColor(HUM_LED,RGB_LED_COLOR_BLUE);    break;
            }
            
            /***********************************************
            * ������ ����ʾ
            */
            switch(Ctrl.Rec.Air_Voc_Grade)
            {
                case GOOD_GRADE:
                    SetLedColor(OIL_LED,RGB_LED_COLOR_BLUE);    break;
                case NORMAL_GRADE:
                    SetLedColor(OIL_LED,RGB_LED_COLOR_GREEN);   break;
                case BAD_GRADE:
                    SetLedColor(OIL_LED,RGB_LED_COLOR_RED);     break;
                default:       
                    SetLedColor(OIL_LED,RGB_LED_COLOR_BLUE);    break;
            }
               
            /***********************************************
            * ������ �۳���ʾ
            */
            switch(Ctrl.Rec.Air_Dust_Grade)
            {
                case GOOD_GRADE:
                    SetLedColor(DUST_LED,RGB_LED_COLOR_BLUE);    break;
                case NORMAL_GRADE:
                    SetLedColor(DUST_LED,RGB_LED_COLOR_GREEN);   break;
                case BAD_GRADE:
                    SetLedColor(DUST_LED,RGB_LED_COLOR_RED);     break;
                default:       
                    SetLedColor(DUST_LED,RGB_LED_COLOR_BLUE);    break;
            }            
            
            /***********************************************
            * ������ ��ʱ������
            */
            osal_start_timerEx( OS_TASK_ID_LED,
                                OS_EVT_LED_TICKS,
                                100);
            return ( task_event ^ OS_EVT_LED_TICKS );
        }
        
        
        
        return  task_event;
}



/*******************************************************************************
* ��    �ƣ�APP_LedInit
* ��    �ܣ������ʼ��
* ��ڲ�������
* ���ڲ�������
* ��    �ߣ�redmorningcn.
* �������ڣ�2018-07-15
* ��    �ģ�
* �޸����ڣ�
*******************************************************************************/
void TaskInitLed(void)
{   
    /***********************************************
    * ������ ��ʼ���������õ������Ӳ��
    */
    bsp_DM412Init();            //DM412��ʼ��
        
    /***********************************************
    * ������ �ڿ��Ź���־��ע�᱾����Ŀ��Ź���־
    */
    OSRegWdtFlag( WDT_FLAG_LED );

    /*************************************************
    * �����������¼���ѯ
    */
    

    osal_start_timerEx( OS_TASK_ID_LED,
                        OS_EVT_LED_TICKS,
                        1000);
}

/*******************************************************************************
* 				                    end of file                                *
*******************************************************************************/

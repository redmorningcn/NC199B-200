/*******************************************************************************
* Description  : LED指示灯任务
* Author       : 2018/5/15 星期二, by redmorningcn
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
//LED指示灯位定义
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
* Description  : 三色灯指示
* Author       : 2018/7/15 星期日, by redmorningcn
*/
osalEvt  TaskLedEvtProcess(osalTid task_id, osalEvt task_event)
{

        OSSetWdtFlag( WDT_FLAG_LED );

        if( task_event & OS_EVT_LED_TICKS ) {

            static  uint8   mode = 0;
            /***********************************************
            * 描述： 开机显示.red /green /blue
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
            * 描述： 湿度显示
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
            * 描述： 油显示
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
            * 描述： 粉尘显示
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
            * 描述： 定时器重启
            */
            osal_start_timerEx( OS_TASK_ID_LED,
                                OS_EVT_LED_TICKS,
                                100);
            return ( task_event ^ OS_EVT_LED_TICKS );
        }
        
        
        
        return  task_event;
}



/*******************************************************************************
* 名    称：APP_LedInit
* 功    能：任务初始化
* 入口参数：无
* 出口参数：无
* 作    者：redmorningcn.
* 创建日期：2018-07-15
* 修    改：
* 修改日期：
*******************************************************************************/
void TaskInitLed(void)
{   
    /***********************************************
    * 描述： 初始化本任务用到的相关硬件
    */
    bsp_DM412Init();            //DM412初始化
        
    /***********************************************
    * 描述： 在看门狗标志组注册本任务的看门狗标志
    */
    OSRegWdtFlag( WDT_FLAG_LED );

    /*************************************************
    * 描述：启动事件查询
    */
    

    osal_start_timerEx( OS_TASK_ID_LED,
                        OS_EVT_LED_TICKS,
                        1000);
}

/*******************************************************************************
* 				                    end of file                                *
*******************************************************************************/

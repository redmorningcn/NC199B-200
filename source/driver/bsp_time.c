
/*******************************************************************************
 *   Filename:       bsp_time.h
 *   Revised:        $Date: 2014-05-27$
 *   Revision:       $
 *	 Writer:		 Wuming Shen.
 *
 *   Description:
 *   ���ļ�ʵ�ֻ���RTC�����ڹ��ܣ��ṩ�����յĶ�д��������ANSI-C��time.h��
*
* RTC�б����ʱ���ʽ����UNIXʱ�����ʽ�ġ���һ��32bit��TIME_t������ʵΪu32��
*
* ANSI-C�ı�׼���У��ṩ�����ֱ�ʾʱ�������  �ͣ�
* time_t:    UNIXʱ�������1970-1-1��ĳʱ�侭����������
* typedef unsigned int time_t;
*
* struct tm: Calendar��ʽ����������ʽ��
* tm�ṹ���£�
* struct tm {
*   int tm_sec;   // �� seconds after the minute, 0 to 59
*               (0 - 59 allows for the occasional leap second)
*   int tm_min;   // �� minutes after the hour, 0 to 59
*   int tm_hour;  // ʱ hours since midnight, 0 to 23
*   int tm_mday;  // �� day of the month, 1 to 31
*   int tm_mon;   // �� months since January, 0 to 11
*   int tm_year;  // �� years since 1900
*   int tm_wday;  // ���� days since Sunday, 0 to 6
*   int tm_yday;  // ��Ԫ��������� days since January 1, 0 to 365
*   int tm_isdst; // ����ʱ����Daylight Savings Time flag
*   ...
* }
*  ����wday��yday�����Զ����������ֱ�Ӷ�ȡ
*  mon��ȡֵΪ0-11
* ***ע��***��
* tm_year:��time.h���ж���Ϊ1900�������ݣ���2008��Ӧ��ʾΪ2008-1900=108
*  ���ֱ�ʾ�������û���˵����ʮ���Ѻã�����ʵ�нϴ���졣
*  �����ڱ��ļ��У����������ֲ��졣
*  ���ⲿ���ñ��ļ��ĺ���ʱ��tm�ṹ�����͵����ڣ�tm_year��Ϊ2008
*  ע�⣺��Ҫ����ϵͳ��time.c�еĺ�������Ҫ���н�tm_year-=1900
*
* ��Ա����˵����
* struct tm TIME_ConvUnixToCalendar(time_t t);
*  ����һ��Unixʱ�����TIME_t��������Calendar��ʽ����
* time_t TIME_ConvCalendarToUnix(struct tm t);
*  ����һ��Calendar��ʽ���ڣ�����Unixʱ�����TIME_t��
* time_t TIME_GetUnixTime(void);
*  ��RTCȡ��ǰʱ���Unixʱ���ֵ
* struct tm TIME_GetCalendarTime(void);
*  ��RTCȡ��ǰʱ�������ʱ��
* void TIME_SetUnixTime(time_t);
*  ����UNIXʱ�����ʽʱ�䣬����Ϊ��ǰRTCʱ��
* void TIME_SetCalendarTime(struct tm t);
*  ����Calendar��ʽʱ�䣬����Ϊ��ǰRTCʱ��
*
* �ⲿ����ʵ����
* ����һ��Calendar��ʽ�����ڱ�����
* struct tm now;
* now.tm_year = 2008;
* now.tm_mon = 11;  //12��
* now.tm_mday = 20;
* now.tm_hour = 20;
* now.tm_min = 12;
* now.tm_sec = 30;
*
* ��ȡ��ǰ����ʱ�䣺
* tm_now = TIME_GetCalendarTime();
* Ȼ�����ֱ�Ӷ�tm_now.tm_wday��ȡ������
*
* ����ʱ�䣺
* Step1. tm_now.xxx = xxxxxxxxx;
* Step2. TIME_SetCalendarTime(tm_now);
*
* ��������ʱ��Ĳ�
* struct tm t1,t2;
* t1_t = TIME_ConvCalendarToUnix(t1);
* t2_t = TIME_ConvCalendarToUnix(t2);
* dt = t1_t - t2_t;
* dt��������ʱ��������
* dt_tm = mktime(dt); //ע��dt�����ƥ�䣬ansi���к���Ϊ�����ݣ�ע�ⳬ��
* ����Բο�������ϣ�����ansi-c��ĸ�ʽ������ȹ��ܣ�ctime��strftime��
*
 *   Notes:
 *					QQ:276193028
 *     				E-mail:shenchangwei945@163.com
 *
 *   All copyrights reserved to Wuming Shen.
 *
 *******************************************************************************/

/*******************************************************************************
 * INCLUDES
 */
#include <includes.h>
#include <bsp_time.h>
#include <ds3231.h>

/*******************************************************************************
 * CONSTANTS
 */
#define UTC 8
/*******************************************************************************
 * MACROS
 */

/*******************************************************************************
 * TYPEDEFS
 */

/*******************************************************************************
 * LOCAL VARIABLES
 */

/*******************************************************************************
 * GLOBAL VARIABLES
 */
struct tm   tm_now = {
  0,30,14,3,9,2015,4
};
time_t  t_now,t_last;

/*******************************************************************************
 * LOCAL FUNCTIONS
 */
void            TIME_Set        (u32 t);
unsigned int    xDate2Seconds   (struct tm *t_tm);
void            xSeconds2Date   (unsigned long seconds,struct tm *time );

/*******************************************************************************
 * GLOBAL FUNCTIONS
 */

/*******************************************************************************
 * EXTERN VARIABLES
 */

/*******************************************************************************
 * EXTERN FUNCTIONS
 */

/*******************************************************************************
* Function Name  : TIME_ConvUnixToCalendar(time_t t)
* Description    : ת��UNIXʱ���Ϊ����ʱ��
* Input    : u32 t  ��ǰʱ���UNIXʱ���
* Output   : None
* Return   : struct tm
*******************************************************************************/
struct tm TIME_ConvUnixToCalendar(time_t t)
{
    struct tm t_tm;
    xSeconds2Date(t,&t_tm );
    
    return t_tm;
}

/*******************************************************************************
* Function Name  : TIME_ConvCalendarToUnix(struct tm t)
* Description    : д��RTCʱ�ӵ�ǰʱ��
* Input    : struct tm t
* Output   : None
* Return   : time_t
*******************************************************************************/
time_t TIME_ConvCalendarToUnix(struct tm t)
{
  return xDate2Seconds((struct tm *) &t);
}

/*******************************************************************************
* Function Name  : TIME_GetUnixTime()
* Description    : ��RTCȡ��ǰʱ���Unixʱ���ֵ
* Input    : None
* Output   : None
* Return   : time_t t
*******************************************************************************/
time_t TIME_GetUnixTime(void)
{
    return TIME_ConvCalendarToUnix(TIME_GetCalendarTime());
}

/*******************************************************************************
* Function Name  : TIME_GetCalendarTime()
* Description    : ��RTCȡ��ǰʱ�������ʱ�䣨struct tm��
* Input    : None
* Output   : None
* Return   : time_t t
*******************************************************************************/
struct tm TIME_GetCalendarTime(void)
{
    struct tm t_tm;
    
    if ( BSP_GetTime(&t_tm) ) {
        return t_tm;
    } else {
        return tm_now;
    }
}

/*******************************************************************************
* Function Name  : TIME_SetUnixTime()
* Description    : ��������Unixʱ���д��RTC
* Input    : time_t t
* Output   : None
* Return   : None
*******************************************************************************/
void TIME_SetUnixTime(time_t t)
{    
    TIME_SetCalendarTime(TIME_ConvUnixToCalendar(t));
}

/*******************************************************************************
* Function Name  : TIME_SetCalendarTime()
* Description    : ��������Calendar��ʽʱ��ת����UNIXʱ���д��RTC
* Input    : struct tm t
* Output   : None
* Return   : None
*******************************************************************************/
void TIME_SetCalendarTime(struct tm t_tm)
{
    BSP_SetTime(t_tm);
}

/*******************************************************************************
* Function Name  : BSP_TIME_Init()
* Description    : 
* Input    : struct tm t
* Output   : None
* Return   : None
*******************************************************************************/
BOOL BSP_TIME_Init(void)
{
    BOOL ret = BSP_RTC_Init();
    /***********************************************
    * ������ ��ȡRTCʱ��
    */
    tm_now  = TIME_GetCalendarTime();

    return ret;
}   

/*******************************************************************************
* Description  : ʱ��оƬʱ��
* Author       : 2018/5/15 ���ڶ�, by redmorningcn
*******************************************************************************/
typedef struct t_xtime {
  int year; int month;  int day; 
  int hour; int minute;  int second; 
} _xtime ;

#define xMINUTE     (60)            //1�ֵ�����
#define xHOUR       (60*xMINUTE)    //1Сʱ������
#define xDAY        (24*xHOUR)      //1�������
#define xYEAR       (365*xDAY)      //1�������

/*******************************************************************************
* Function Name : xDate2Seconds()
* Description   : ��localtime��UTC+8����ʱ�䣩תΪUNIX TIME����1970��1��1��Ϊ��� 
* Input         : struct tm t
* Output        : None
* Return        : None
*******************************************************************************/
unsigned int  xDate2Seconds(struct tm *t_tm)
{
    const unsigned int  month[12]={
    /*01��*/xDAY*(0),
    /*02��*/xDAY*(31),
    /*03��*/xDAY*(31+28),
    /*04��*/xDAY*(31+28+31),
    /*05��*/xDAY*(31+28+31+30),
    /*06��*/xDAY*(31+28+31+30+31),
    /*07��*/xDAY*(31+28+31+30+31+30),
    /*08��*/xDAY*(31+28+31+30+31+30+31),
    /*09��*/xDAY*(31+28+31+30+31+30+31+31),
    /*10��*/xDAY*(31+28+31+30+31+30+31+31+30),
    /*11��*/xDAY*(31+28+31+30+31+30+31+31+30+31),
    /*12��*/xDAY*(31+28+31+30+31+30+31+31+30+31+30)
  };

  unsigned int  seconds = 0;
  unsigned int  year = 0;

  year      = t_tm->tm_year - 1970;                 //������2100��ǧ�������
  seconds   = xYEAR*year + xDAY*((year+1)/4);       //ǰ�����ȥ������
  seconds  += month[t_tm->tm_mon-1];                //���Ͻ��걾�¹�ȥ������

  if( (t_tm->tm_mon > 2) && (((year+2)%4)==0) )     //2008��Ϊ����
    seconds += xDAY;                                //�����1������

  seconds += xDAY*(t_tm->tm_mday-1);                //���ϱ����ȥ������
  seconds += xHOUR*t_tm->tm_hour;                   //���ϱ�Сʱ��ȥ������
  seconds += xMINUTE*t_tm->tm_min;                  //���ϱ����ӹ�ȥ������
  seconds += t_tm->tm_sec;                          //���ϵ�ǰ����<br>��seconds -= 8 * xHOUR;
  seconds -= (UTC * 3600);
  
  return seconds;
} 

/*******************************************************************************
* Function Name : xSeconds2Date()
* Description   : ��UNIXʱ��תΪUTC+8 ������ʱ��
*                 UNIXתΪUTC �ѽ���ʱ��ת�� ����ʱ��UTC+8
* Input         : struct tm t
* Output        : None
* Return        : None
*******************************************************************************/
void xSeconds2Date(unsigned long seconds,struct tm *time )
{
    const unsigned int month[12]={
    /*01��*/31,
    /*02��*/28,
    /*03��*/31,
    /*04��*/30,
    /*05��*/31,
    /*06��*/30,
    /*07��*/31,
    /*08��*/31,
    /*09��*/30,
    /*10��*/31,
    /*11��*/30,
    /*12��*/31 
    };

    unsigned int days; 
    unsigned short leap_y_count;  

    seconds        += UTC * 3600;               //ʱ������ תΪUTC+8 bylzs
    
    time->tm_sec    = seconds % 60;             //����� 
    seconds        /= 60; 
    time->tm_min    =  seconds % 60;            //��÷�  
    seconds        /= 60;  
    time->tm_hour   = seconds % 24;             //���ʱ 
    days            = seconds / 24;             //���������
    leap_y_count    = (days + 365) / 1461;      //��ȥ�˶��ٸ�����(4��һ��)  

    if( ((days + 366) % 1461) == 0) {           //��������1��  
        time->tm_year   = 1970 + (days / 366);  //�����  
        time->tm_mon    = 12;                   //������  
        time->tm_mday   = 31;  
        return;  
    }  

    days -= leap_y_count; 
    time->tm_year = 1970 + (days / 365);        //�����  
    days %= 365;                                //����ĵڼ���  

    days = 01 + days;                           //1�տ�ʼ  

    if( (time->tm_year % 4) == 0 ) { 
        if(days > 60)
            --days;                             //�������  
        else {  
            if(days == 60){  
                time->tm_mon = 2;  
                time->tm_mday = 29;  
                return;  
            }  
        }  
    }  

    for(time->tm_mon = 0;month[time->tm_mon] < days;time->tm_mon++) {  
        days -= month[time->tm_mon]; 
    }  

    ++time->tm_mon;                             //������  
    time->tm_mday = days;                       //�����  
} 

/*******************************************************************************
 *              end of file                                                    *
 *******************************************************************************/
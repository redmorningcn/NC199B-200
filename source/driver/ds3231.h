#ifndef  _DS3231_h_
#define  _DS3231_h_

#include <includes.h>
#include <time.h>


//ʱ��----------------------------------------
typedef struct	_stcTime_
{
	u8	    Sec;
	u8	    Min;
	u8	    Hour;
	u8	    Day;
	u8	    Mon;
	u8	    Year;
	u16 	CrcCheck;
}stcTime;


//-------------------------------------------------------------------------------------------------------
//��������:         void 	BSP_Ds3231Init(void)  
//��    ��:         ��ʼ��DS3231
//��ڲ���:         
//���ڲ���:         
//˵����            
//--------------------------------------------------------------------------------------------------------
extern	void	BSP_Ds3231Init(void) ; 

//-------------------------------------------------------------------------------------------------------
//��������:         stcTime 	ReadTime(void)  
//��    ��:         ��DS3231�ж���ʱ��
//��ڲ���:         ��
//���ڲ���:         ���ض�����ʱ��
//˵����            
//--------------------------------------------------------------------------------------------------------
extern	uint8 	ReadTime(stcTime * sTime)  ;

//-------------------------------------------------------------------------------------------------------
//��������:         void	SetTime(uint8 Year,uint8 Month,uint8 Data,uint8 Hour,uint8 Min,uint8 Sec)   
//��    ��:         ����ʱ��
//��ڲ���:         
//���ڲ���:         
//˵����            
//--------------------------------------------------------------------------------------------------------
extern	void	SetTime(uint8 Year,uint8 Month,uint8 Data,uint8 Hour,uint8 Min,uint8 Sec) ; 


//-------------------------------------------------------------------------------------------------------
//��������:         stcTime     ReadTime(void)  
//��    ��:         дDS3231ʱ��
//��ڲ���:         дʱ��
//���ڲ���:         
//˵����            
//--------------------------------------------------------------------------------------------------------
extern	void    WriteTime(stcTime  sTime)  ;



//-------------------------------------------------------------------------------------------------------
//��������:  	void    DisplayTime(void)  
//��    ��:  	��ʱ������-��-�� ʱ���֣��� ����
//��ڲ���:         
//���ڲ���:         
//--------------------------------------------------------------------------------------------------------
extern	void    DisplayTime(void)  ;
extern BOOL     BSP_RTC_Init(void);
extern BOOL     BSP_GetTime(struct tm *t_tm);
extern BOOL     BSP_SetTime(struct tm t_tm);
extern  s8 BSP_RTC_ReadTemp(void);
extern  void BSP_RTC_WriteTime(stcTime  sTime);

#endif
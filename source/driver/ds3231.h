#ifndef  _DS3231_h_
#define  _DS3231_h_

#include <includes.h>
#include <time.h>


//时间----------------------------------------
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
//函数名称:         void 	BSP_Ds3231Init(void)  
//功    能:         初始化DS3231
//入口参数:         
//出口参数:         
//说明：            
//--------------------------------------------------------------------------------------------------------
extern	void	BSP_Ds3231Init(void) ; 

//-------------------------------------------------------------------------------------------------------
//函数名称:         stcTime 	ReadTime(void)  
//功    能:         从DS3231中读出时间
//入口参数:         无
//出口参数:         返回读出的时间
//说明：            
//--------------------------------------------------------------------------------------------------------
extern	uint8 	ReadTime(stcTime * sTime)  ;

//-------------------------------------------------------------------------------------------------------
//函数名称:         void	SetTime(uint8 Year,uint8 Month,uint8 Data,uint8 Hour,uint8 Min,uint8 Sec)   
//功    能:         设置时间
//入口参数:         
//出口参数:         
//说明：            
//--------------------------------------------------------------------------------------------------------
extern	void	SetTime(uint8 Year,uint8 Month,uint8 Data,uint8 Hour,uint8 Min,uint8 Sec) ; 


//-------------------------------------------------------------------------------------------------------
//函数名称:         stcTime     ReadTime(void)  
//功    能:         写DS3231时间
//入口参数:         写时间
//出口参数:         
//说明：            
//--------------------------------------------------------------------------------------------------------
extern	void    WriteTime(stcTime  sTime)  ;



//-------------------------------------------------------------------------------------------------------
//函数名称:  	void    DisplayTime(void)  
//功    能:  	将时间以年-月-日 时：分：秒 出来
//入口参数:         
//出口参数:         
//--------------------------------------------------------------------------------------------------------
extern	void    DisplayTime(void)  ;
extern BOOL     BSP_RTC_Init(void);
extern BOOL     BSP_GetTime(struct tm *t_tm);
extern BOOL     BSP_SetTime(struct tm t_tm);
extern  s8 BSP_RTC_ReadTemp(void);
extern  void BSP_RTC_WriteTime(stcTime  sTime);

#endif

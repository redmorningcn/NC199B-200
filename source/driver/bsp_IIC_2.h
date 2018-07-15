#ifndef  _IIC_2_h_
#define  _IIC_2_h_

#include <includes.h>

/***********************************************
* 描述: OS接口
*/
#if UCOS_EN     == DEF_ENABLED
#if OS_VERSION > 30000U
static  OS_SEM			Bsp_FramSem;//Bsp_FramSem;    	//信号量
#else
static  OS_EVENT		*Bsp_FramSem;//Bsp_FramSem;       //信号量
#endif
#endif


#if (UCOS_EN     == DEF_ENABLED)
u8 FRAM_WaitEvent(void);
void FRAM_SendEvent(void);
void BSP_FramOsInit(void);
   
#endif



//------------------------------------------------------------
//函数名称:         StartI2C_2()
//功    能:         I2C_2总线开始条件
//入口参数:         无
//出口参数:         无
//说明：            I2C_2总线的开始条件：
//                  SCL高电平时SDA的下降沿
//------------------------------------------------------------
extern	void StartI2C_2(void);

//---------------------------------------------------------------
//函数名称:         StopI2C_2()
//功    能:         I2C_2总线结束条件
//入口参数:         无
//出口参数:         无
//说明：            I2C_2总线结束条件：SCL为高电平时SDA的上升沿
//--------------------------------------------------------------------
extern	void StopI2C_2(void);

//-------------------------------------------------------------------------------
//函数名称:         MasterAckI2C_2()
//功    能:         主机接收应答，在接收到1字节数据后，返回应答，告诉从机接收完成
//入口参数:         无
//出口参数:         无
//说明：            I2C_2总线应答：读完一个字节后将SDA线拉低，即应答0
//---------------------------------------------------------------------------------
extern	void MasterAckI2C_2(void);

//-----------------------------------------------------------------------------------
//函数名称:         MasterNoAckI2C_2()
//功    能:         主机接收应答，告诉通信从机接收完成
//入口参数:         无
//出口参数:         无
//说明：            I2C_2总线应答：
//                  读完所要求的字节数据后将SDA线拉高，为结束IIC总线操作做准备
//-------------------------------------------------------------------------------------
extern	void MasterNoAckI2C_2(void);

//------------------------------------------------------------------------------------
//函数名称:         CheckSlaveAckI2C_2()
//功    能:         读I2C_2从机应答
//入口参数:         无
//出口参数:         ackflag
//                  如果从机产生应答，则返回0，
//                  从机没有产生应答,否则返回1
//说明：            检查I2C_2器件(从机)应答情况,应答返回1,否则为零
//these waw a bug befor 2008/05/17.
//------------------------------------------------------------------------------------
extern	uint8 CheckSlaveAckI2C_2(void);

//------------------------------------------------------------------------------------
//函数名称:         WriteByteWithI2C_2()
//功    能:         主机对I2C_2总线写1操作
//入口参数:         Data:要写出的数据
//出口参数:         无
//说明：            写一字节数据Data
//------------------------------------------------------------------------------------
extern	void WriteByteWithI2C_2(uint8 Data)  ;

//-------------------------------------------------------------------------------------------------------
//函数名称:         ReadByteWithI2C_2()
//功    能:         主机对I2C_2总线写1操作
//入口参数:         无
//出口参数:         无
//说明：            读一字节数据：返回值即读的数据
//--------------------------------------------------------------------------------------------------------
extern	uint8 ReadByteWithI2C_2(void)      ;

void	GPIO_Fram_Init(void);



#endif

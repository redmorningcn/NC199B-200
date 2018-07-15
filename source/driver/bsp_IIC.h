#ifndef  _IIC_h_
#define  _IIC_h_

#include <includes.h>

/***********************************************
* ����: OS�ӿ�
*/
#if UCOS_EN     == DEF_ENABLED
#if OS_VERSION > 30000U
static  OS_SEM			Bsp_RtcSem;//Bsp_FramSem;    	//�ź���
#else
static  OS_EVENT		*Bsp_RtcSem;//Bsp_FramSem;       //�ź���
#endif
#endif


#if (UCOS_EN     == DEF_ENABLED)
u8 RTC_WaitEvent(void);
void RTC_SendEvent(void);
void BSP_RTCOsInit(void);
   
#endif

//------------------------------------------------------------------------
//  ��  �� ��void void InitI2CIO(void)
//  ��  �� ������ SDA SCL Ϊ��ͨIO�� ����ģ�����߲���
// ��ڲ�������
// ���ڲ�������
//------------------------------------------------------------------------
extern	void	GPIO_RTC_Init(void);

//------------------------------------------------------------
//��������:         StartI2C()
//��    ��:         I2C���߿�ʼ����
//��ڲ���:         ��
//���ڲ���:         ��
//˵����            I2C���ߵĿ�ʼ������
//                  SCL�ߵ�ƽʱSDA���½���
//------------------------------------------------------------
extern	void StartI2C(void);

//---------------------------------------------------------------
//��������:         StopI2C()
//��    ��:         I2C���߽�������
//��ڲ���:         ��
//���ڲ���:         ��
//˵����            I2C���߽���������SCLΪ�ߵ�ƽʱSDA��������
//--------------------------------------------------------------------
extern	void StopI2C(void);

//-------------------------------------------------------------------------------
//��������:         MasterAckI2C()
//��    ��:         ��������Ӧ���ڽ��յ�1�ֽ����ݺ󣬷���Ӧ�𣬸��ߴӻ��������
//��ڲ���:         ��
//���ڲ���:         ��
//˵����            I2C����Ӧ�𣺶���һ���ֽں�SDA�����ͣ���Ӧ��0
//---------------------------------------------------------------------------------
extern	void MasterAckI2C(void);

//-----------------------------------------------------------------------------------
//��������:         MasterNoAckI2C()
//��    ��:         ��������Ӧ�𣬸���ͨ�Ŵӻ��������
//��ڲ���:         ��
//���ڲ���:         ��
//˵����            I2C����Ӧ��
//                  ������Ҫ����ֽ����ݺ�SDA�����ߣ�Ϊ����IIC���߲�����׼��
//-------------------------------------------------------------------------------------
extern	void MasterNoAckI2C(void);

//------------------------------------------------------------------------------------
//��������:         CheckSlaveAckI2C()
//��    ��:         ��I2C�ӻ�Ӧ��
//��ڲ���:         ��
//���ڲ���:         ackflag
//                  ����ӻ�����Ӧ���򷵻�0��
//                  �ӻ�û�в���Ӧ��,���򷵻�1
//˵����            ���I2C����(�ӻ�)Ӧ�����,Ӧ�𷵻�1,����Ϊ��
//these waw a bug befor 2008/05/17.
//------------------------------------------------------------------------------------
extern	uint8 CheckSlaveAckI2C(void);

//------------------------------------------------------------------------------------
//��������:         WriteByteWithI2C()
//��    ��:         ������I2C����д1����
//��ڲ���:         Data:Ҫд��������
//���ڲ���:         ��
//˵����            дһ�ֽ�����Data
//------------------------------------------------------------------------------------
extern	void WriteByteWithI2C(uint8 Data)  ;

//-------------------------------------------------------------------------------------------------------
//��������:         ReadByteWithI2C()
//��    ��:         ������I2C����д1����
//��ڲ���:         ��
//���ڲ���:         ��
//˵����            ��һ�ֽ����ݣ�����ֵ����������
//--------------------------------------------------------------------------------------------------------
extern	uint8 ReadByteWithI2C(void)      ;

//------------------------------------------------------------------------
//  ��  �� ��void void InitI2CIO(void)
//  ��  �� ������ SDA SCL Ϊ��ͨIO�� ����ģ�����߲���
// ��ڲ�������
// ���ڲ�������
//------------------------------------------------------------------------
extern	void InitI2CIO(void);


#endif
/*******************************************************************************
* Description  : ģ��IIC���ߣ�IICʱ��
* Author       : 2018/5/15 ���ڶ�, by redmorningcn
*******************************************************************************/

#include <includes.h>

#define     SCL_2     	    407		//PE7
#define     SDA_2           408		//PE8


#define     Delay_Factor       5                                        		//��ʱ����

#if (UCOS_EN     == DEF_ENABLED)
/*******************************************************************************
* ��    �ƣ� 		FRAM_WaitEvent
* ��    �ܣ� 		�ȴ��ź���
* ��ڲ����� 	��
* ���ڲ�����  	0���������󣩣�1�������ɹ���
* ��    �ߣ� 	redmorningcn
* �������ڣ� 	2017-05-15
* ��    �ģ�
* �޸����ڣ�
* ��    ע�� ����ʹ��UCOS����ϵͳʱʹ��
*******************************************************************************/
u8 FRAM_WaitEvent(void)
{
    /***********************************************
    * ������ OS�ӿ�
    */
    return BSP_OS_SemWait(&Bsp_FramSem,0);           	// �ȴ��ź���
}

/*******************************************************************************
* ��    �ƣ�	 	FRAM_SendEvent
* ��    �ܣ� 		�ͷ��ź���
* ��ڲ����� 	��
* ���ڲ����� 	��
* ��    �ߣ� 	redmorningcn
* �������ڣ� 	2017-05-15
* ��    �ģ�
* �޸����ڣ�
* ��    ע�� ����ʹ��UCOS����ϵͳʱʹ��
*******************************************************************************/
void FRAM_SendEvent(void)
{
    BSP_OS_SemPost(&Bsp_FramSem);                        	// �����ź���
}

/*******************************************************************************
* ��    �ƣ� FRAM_SendEvent
* ��    �ܣ� �ͷ��ź���
* ��ڲ����� ��
* ���ڲ����� ��
* ��    �ߣ� redmorningcn
* �������ڣ� 2017-05-15
* ��    �ģ�
* �޸����ڣ�
* ��    ע�� ����ʹ��UCOS����ϵͳʱʹ��
*******************************************************************************/
void BSP_FramOsInit(void)
{
    /***********************************************
    * ������ OS�ӿ�
    */
#if (UCOS_EN     == DEF_ENABLED)
#if OS_VERSION > 30000U
    BSP_OS_SemCreate(&Bsp_FramSem,1, "Bsp EepSem");      // �����ź���
#else
    Bsp_FramSem     = OSSemCreate(1);                    // �����ź���
#endif
#endif
}

#endif /* end of (UCOS_EN     == DEF_ENABLED)*/


/*******************************************************************************
* Function Name  : I2C_2_delay
* Description    : ��ʱ����i������ʱʱ��
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
OPTIMIZE_NONE void I2C_2_delay(void)
{
	u8 i = Delay_Factor; 
	while(i) 
	{ 
		i--; 
	} 
}

//------------------------------------------------------------------------
//  ��  �� ��		GPIO_Fram_Init
//  ��  �� :          ��ʼ������� IO�ڣ�Ϊͨ��IO ��
// ��ڲ�����	    ��
// ���ڲ�����	    ��
//------------------------------------------------------------------------
void	GPIO_Fram_Init(void)
{
	GPIO_Config(SCL_2,0);
	GPIO_Config(SCL_2,0);
	GPIO_Config(SDA_2,0);
	GPIO_Config(SDA_2,0);
    
#if (UCOS_EN     == DEF_ENABLED)        //os�ӿ�
    BSP_FramOsInit();
#endif
}

//------------------------------------------------------------------------
//  ��  �� ��void WriteSCL_2( uint8 temp )
//  ��  �� ������ SCL_2
// ��ڲ�������
// ���ڲ�������
//------------------------------------------------------------------------
void WriteSCL_2(uint8 temp)
{	
	if(temp)		
	{
		GPIO_Set(SCL_2,1);
	}
	else
	{
		GPIO_Set(SCL_2,0);		
	}	

	I2C_2_delay();
}

//------------------------------------------------------------------------
//  ��  �� ��uint8 ReadSCL_2(void)
//  ��  �� ����ȡ SCL_2 ��ֵ
// ��ڲ�������
// ���ڲ�������
//------------------------------------------------------------------------
uint8 ReadSCL_2(void)
{
    uint8    temp;
    temp = 	GPIO_Read(SCL_2);
    I2C_2_delay();
    return temp;
}

//------------------------------------------------------------------------
//  ��  �� ��void WriteSDA_2( uint8 temp )
//  ��  �� ������ SDA_2
// ��ڲ�������
// ���ڲ�������
//------------------------------------------------------------------------
void WriteSDA_2(uint8 temp)
{
	if(temp)		
	{
		GPIO_Set(SDA_2,1);
	}
	else
	{
		GPIO_Set(SDA_2,0);		
	}	
	I2C_2_delay();
}

//------------------------------------------------------------------------
//  ��  �� ��uint8 ReadSDA_2(void)
//  ��  �� ����ȡ SDA_2 ��ֵ
// ��ڲ�������
// ���ڲ�������
//------------------------------------------------------------------------
uint8 ReadSDA_2(void)
{
    uint8 temp;
    
    temp = 	GPIO_Read(SDA_2);
    I2C_2_delay();

    return temp;
}

//------------------------------------------------------------
//��������:         StartI2C_2()
//��    ��:         I2C_2���߿�ʼ����
//��ڲ���:         ��
//���ڲ���:         ��
//˵����            I2C_2���ߵĿ�ʼ������
//                  SCL�ߵ�ƽʱSDA_2���½���
//------------------------------------------------------------
void StartI2C_2(void)
{
    WriteSCL_2(0);                                // SCL_2=0;
    WriteSDA_2(1);                                //SDA_2=1;
    WriteSCL_2(1);                                //SCL_2=1;
    WriteSDA_2(0);                                //SDA_2=0;
    WriteSCL_2(0);                                // SCL_2=0;
}

//---------------------------------------------------------------
//��������:         StopI2C_2()
//��    ��:         I2C_2���߽�������
//��ڲ���:         ��
//���ڲ���:         ��
//˵����            I2C_2���߽���������SCLΪ�ߵ�ƽʱSDA_2��������
//--------------------------------------------------------------------
void StopI2C_2(void)
{
    WriteSCL_2(0);                                // SCL_2=0;
    WriteSDA_2(0);                                //SDA_2=0;
    WriteSCL_2(1);                                //SCL_2=1;
    WriteSDA_2(1);                                //SDA_2=1;
    WriteSCL_2(0);                                //SCL_2=0;
}

//-------------------------------------------------------------------------------
//��������:         MasterAckI2C_2()
//��    ��:         ��������Ӧ���ڽ��յ�1�ֽ����ݺ󣬷���Ӧ�𣬸��ߴӻ��������
//��ڲ���:         ��
//���ڲ���:         ��
//˵����            I2C_2����Ӧ�𣺶���һ���ֽں�SDA_2�����ͣ���Ӧ��0
//---------------------------------------------------------------------------------
void MasterAckI2C_2(void)
{
    WriteSCL_2(0);                                // SCL_2=0;
    WriteSDA_2(0);                               //SDA_2=0;
    WriteSCL_2(1);                                //SCL_2=1;
    WriteSCL_2(0);                                 //SCL_2=0;
    WriteSDA_2(0);                                //SDA_2=0;
}

//-----------------------------------------------------------------------------------
//��������:         MasterNoAckI2C_2()
//��    ��:         ��������Ӧ�𣬸���ͨ�Ŵӻ��������
//��ڲ���:         ��
//���ڲ���:         ��
//˵����            I2C_2����Ӧ��
//                  ������Ҫ����ֽ����ݺ�SDA_2�����ߣ�Ϊ����IIC���߲�����׼��
//-------------------------------------------------------------------------------------
void MasterNoAckI2C_2(void)
{
    WriteSCL_2(0);                                    // SCL_2=0;
    WriteSDA_2(1);                                    //SDA_2=1;
    WriteSCL_2(1);                                    //SCL_2=1;
    WriteSCL_2(0);                                    //SCL_2=0;
    WriteSDA_2(0);                                    //SDA_2=0;
}

//------------------------------------------------------------------------------------
//��������:         CheckSlaveAckI2C_2()
//��    ��:         ��I2C_2�ӻ�Ӧ��
//��ڲ���:         ��
//���ڲ���:         ackflag
//                  ����ӻ�����Ӧ���򷵻�0��
//                  �ӻ�û�в���Ӧ��,���򷵻�1
//˵����            ���I2C_2����(�ӻ�)Ӧ�����,Ӧ�𷵻�1,����Ϊ��
//these waw a bug befor 2008/05/17.
//------------------------------------------------------------------------------------
uint8 CheckSlaveAckI2C_2(void)
{
    uint8  ackflag;                                  //���Ӧ���־;
    uint16 ctr  = 0;
    
    do {
        ackflag = ReadSDA_2();
    } while ( ( ++ctr < 5000 ) && ( ackflag ) );
    
    WriteSCL_2(1);                                    //SCL_2=1;
    WriteSCL_2(0);                                    //SCL_2=0;
    
    return ackflag;
}

//------------------------------------------------------------------------------------
//��������:         WriteByteWithI2C_2()
//��    ��:         	������I2C_2����д1����
//��ڲ���:         Data:Ҫд��������
//���ڲ���:         ��
//˵����            	дһ�ֽ�����Data
//------------------------------------------------------------------------------------
void WriteByteWithI2C_2(uint8 Data)  
{
    uint8 i;
    for(i=0;i<8;i++)
    {
        if(Data & 0x80)                             //����λ�Ӹ�λ����λ,�ȴ����λ 
        {
            WriteSDA_2(1);                            //SDA_2=1;
            WriteSCL_2(1);                            //SCL_2=1;
        }
        else
        {  
            WriteSDA_2(0);                            //SDA_2=0;
            WriteSCL_2(1);                            //SCL_2=1;
        }   
        WriteSCL_2(0);                                //SCL_2=0;
        WriteSDA_2(0);                                //SDA_2=0;
        Data <<= 1;                                 //��������             
    }
}

//-------------------------------------------------------------------------------------------------------
//��������:         ReadByteWithI2C_2()
//��    ��:         ������I2C_2����д1����
//��ڲ���:         ��
//���ڲ���:         ��
//˵����            ��һ�ֽ����ݣ�����ֵ����������
//--------------------------------------------------------------------------------------------------------
uint8 ReadByteWithI2C_2(void)            
{
    uint8 readdata=0;                           // Read_DataΪ��������ݣ�0
    uint8 j;
    
    for (j=0;j<8;j++)
    {
        readdata <<=1;
								  //���ݶ���������0����λ������1����0x01��
        if(ReadSDA_2())
        {
            readdata =(readdata | 0x01);               
        }
        WriteSCL_2(1);                              //SCL_2=1;
        WriteSCL_2(0);                              //SCL_2=0;
    }
    
    return   readdata ;                         //���ض������ֽ�
}


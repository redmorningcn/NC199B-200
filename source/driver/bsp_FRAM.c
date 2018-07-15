/*******************************************************************************
* Description  : ����FRAM����
* Author       : 2018/5/15 ���ڶ�, by redmorningcn
*******************************************************************************/

/*******************************************************************************
* INCLUDES
*/
#include <includes.h>
#include <bsp_FRAM.h>
#include <bsp_iic.h>


//-------------------------------------------------------------------------------------------------------
//��������: 		WriteFM24CL16()
//��    ��:			��FM24CL16ָ����ַ����д����
//��ڲ���:         ADDR:       ������ַ    ��ַ��0 ~ sizeof(FM24CL16)
//                  		*DataBuf:   ���ݻ���
//                  Len: 	���ݳ���
//��    �ߣ� 	redmorningcn
//�������ڣ� 	2017-05-15
//���ڲ���:    	��
//˵����            
//--------------------------------------------------------------------------------------------------------
OPTIMIZE_NONE u8 WriteFM24CL64(u16  Addr, u8 *DataBuf, u32 DataBufLen)            
{
    u32  i = 0;
    u8   SlaveAddr;                                      //�ӻ���ַ
    u16  AddrTemp = 0;                                   //��ַ����
    
	FRAM_WaitEvent();
    
    AddrTemp = Addr;
    AddrTemp += FRAM_START_ADDR;                            //�����ַ
    
    if( (u16)AddrTemp + DataBufLen > FRAM_END_ADDR ) {
        FRAM_SendEvent();
        return  FALSE;                                      //��ַδ����
    }
    
    SlaveAddr = FRAM_DIVICE_ADDR & (~(0x01));               //��FM24CL64�豸д��ַ
    
    StartI2C_2();                                             //����IIC����
    
    WriteByteWithI2C_2(SlaveAddr);                            //дFM24CL64��ַ
    CheckSlaveAckI2C_2();
    
    WriteByteWithI2C_2(Addr >> 8);                            //дFM24CL64��λ��ַ
    CheckSlaveAckI2C_2();
    
    WriteByteWithI2C_2( Addr );                               //дFM24CL64��λ��ַ
    CheckSlaveAckI2C_2();     
    
    for(i = 0; i < DataBufLen; i++) {                       //��������
        WriteByteWithI2C_2(DataBuf[i]);                       //д����
        CheckSlaveAckI2C_2();                                 //���ӻ�Ӧ���ź�
    }

    StopI2C_2();                                              //ֹͣIIC���� 
    
	FRAM_SendEvent();
    
    return  TRUE;                                           //��ȷ
}

//-------------------------------------------------------------------------------------------------------
//��������:         ReadFM24CL16()
//��    ��:         ��ȡFM24CL16ָ����ַ��������
//��ڲ���:         ADDR:       ������ַ   ��ַ��0 ~ sizeof(FM24CL16)
//                  *DataBuf:   ���ݻ��� 
//                  Len:        ���ݳ���
//���ڲ���:         ��
//��    �ߣ� 	redmorningcn
//�������ڣ� 	2017-05-15
//˵����            
//--------------------------------------------------------------------------------------------------------
OPTIMIZE_NONE u8 ReadFM24CL64(u16  Addr, u8 *DataBuf, u32 DataBufLen)            
{
    u32  i = 0;
    u8   SlaveAddr;                                      //�ӻ���ַ
    u16  AddrTemp;                                       //��ַ����
    
	FRAM_WaitEvent();
    
    AddrTemp = Addr;
    
    AddrTemp += FRAM_START_ADDR;                            //�����ַ
    
    if( (u16)AddrTemp + DataBufLen > FRAM_END_ADDR ) {
        FRAM_SendEvent();
        return  FALSE;                                      //��ַδ����
    }
    
    SlaveAddr = FRAM_DIVICE_ADDR & (~(0x01));               //��FM24CL64�豸д��ַ
    
    StartI2C_2();                                             //����IIC����
    
    WriteByteWithI2C_2(SlaveAddr);                            //дFM24CL64�豸д��ַ
    CheckSlaveAckI2C_2();                                     //���ӻ�Ӧ���ź�
    
    WriteByteWithI2C_2(Addr >> 8 );                           //д���ݸ�λ��ַ
    CheckSlaveAckI2C_2();                                     //���ӻ�Ӧ���ź�
    
    WriteByteWithI2C_2( Addr );                               //д���ݵ�λ��ַ
    CheckSlaveAckI2C_2();                                     //���ӻ�Ӧ���ź�
    
    SlaveAddr = (FRAM_DIVICE_ADDR)|(0x01);                  //��FM24CL64�豸����ַ
    
    StartI2C_2();                                             //����IIC����
    
    WriteByteWithI2C_2(SlaveAddr);                            //дFM24CL16��ַ
    CheckSlaveAckI2C_2();                                     //���ӻ�Ӧ���ź�
    
    for(i = 0; i < (DataBufLen -1); i++) {                  //��������
   
        DataBuf[i] = ReadByteWithI2C_2();                     //д����
        MasterAckI2C_2();                                     //����Ӧ��ӻ�
    }
    DataBuf[i] = ReadByteWithI2C_2();                         //д����
    
    MasterNoAckI2C_2();                                       //����Ӧ��ӻ�

    StopI2C_2();
    
	FRAM_SendEvent();
    
    return  TRUE;                                           //��ȷ
}

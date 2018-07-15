/*******************************************************************************
* Description  :  ����洢��¼�����ݽṹ
* Author       : 2018/5/15 ���ڶ�, by redmorningcn
*******************************************************************************/

#ifndef  _RecDataTypeDef_h_
#define  _RecDataTypeDef_h_

#include <includes.h>


typedef union _strDevicErr
{
    struct{
        u16         Speed1Comm     : 1;    //D0=1���ٶȼ���1ͨѶ����
        u16         Speed2Comm     : 1;    //D1=1���ٶȼ���2ͨѶ����
        u16         Speed3Comm     : 1;    //D2=1���ٶȼ���3ͨѶ����
        u16         Speed1Lose     : 1;    //D3=1���ٶȼ���1��������ϣ������ͨ��sta��
        u16         Speed2Lose     : 1;    //D4=1���ٶȼ���2��������ϣ������ͨ��sta��
        u16         Speed3Lose     : 1;    //D5=1���ٶȼ���3��������ϣ������ͨ��sta��
        u16         LocoComm       : 1;    //D6=1�������źż���ͨѶ����
        u16         Disp1CommErr   : 1;    //D7=1��һ����ʾģ��ͨѶ����
        u16         Disp2CommErr   : 1;    //D8=1��������ʾģ��ͨѶ����
        u16         TaxCommErr     : 1;    //D9=1��TAXͨѶ����
        u16         FlashErr       : 1;    //D10=1���洢������
        u16         FramErr        : 1;    //D11=1���������
        u16         TimeErr        : 1;    //D12=1��ʱ�����
        u16         RsvErr         : 3;   //     ��Ԥ��
    };
    u32                 Flags;
}strDeviceErr;

//2017-11-16  redmorningcn
//ѹ����������װ�ã�������������  
__packed
typedef struct _sAirQuality{
    u16				Temperature       ;//�¶�                                 2                    
    u16				Humidity          ;//ʪ��                                 2                    
    u16				VOCs              ;//�ӷ��л���                           2                    
    u16				CO2_EQU           ;//��ֵCO2                              2  
    CPU_INT32U      RS                ;// RS
    u16				PM1D0_S           ;//��׼������Ũ��ug/m3                  2                    
    u16				PM2D5_S           ;//��׼������Ũ��ug/m3                  2                    
    u16				PM10D_S           ;//��׼������Ũ��ug/m3                  2    
    u16				PM1D0_G           ;// ��������                              
    u16				PM2D5_G           ;// ��������                    
    u16				PM10D_G           ;// �������� 
    u16             Dusts_0D3         ;//0.1��������ֱ����0.3um�Ŀ��������
    u16             Dusts_0D5         ;//0.1��������ֱ����0.5um�Ŀ��������
    u16             Dusts_1D0         ;//0.1��������ֱ����1.0um�Ŀ��������
    u16             Dusts_2D5         ;//0.1��������ֱ����2.5um�Ŀ��������    
} stcAirQuality;      

//2017-11-16  redmorningcn
//ѹ����������װ�ã���������ݽṹ     
typedef __packed struct _stcFlshRec     //�������ݼ�¼���ݽṹ��20171116 ����ѹ��������
{
    u8				CmdTpye         ;//��������       1     		        	
    u8				EvtType         ;//�¼�����       1                  
    u16				LocoType        ;//�����ͺ�       2                  
    u16				LocoNbr         ;//�� �� ��       2                     
    u32				RecordId        ;//��¼��ˮ��     4
    
    stcAirQuality   sAir            ;//��������       28
    u8              RunSys          ;//����״̬       1�������Ŵ򿪣���ʼ���ԣ��ȵȣ�      
    u8				Recv[8]         ;//Ԥ��                               
    //u16				ErrCode           ;//���ϴ���       2 
    struct _ErrCode {
        u16         MtrCommErr      : 1;    // ��������
        u16         Res             : 15;   // D11~D06����
    } ErrCode;                                          // 04 ʱ��    
    
    
    u8              Air_Hum_Grade   ;//ʪ�ȵȼ�       1                  
    u8              Air_Voc_Grade   ;//VOC�ȼ�        1                   
    u8              Air_Dust_Grade  ;//�۳��ȼ�       1    
    struct  {
        u32      Sec                 : 6;        // D05~D00����
        u32      Min                 : 6;        // D11~D06����
        u32      Hour                : 5;        // D16~D12��ʱ
        u32      Day                 : 5;        // D21~D17����
        u32      Mon                 : 4;        // D25~D22����
        u32      Year                : 6;        // D31~D26����
    } ;                                      // 04 ʱ��
    
////////////////////////////////////////////////// TAX����������
    u8           TaxType             ;//TAX������       1                     
    u8           TaxFlg              ;//TAX������       64       
    /***************************************************
    * ������ TAX:64 bytes
    */
    union __uTAX__Rec {
//    _StrTax_II_Rec      Tax2;                           // ��¼����     
//    struct __sTAX_III__Rec {
//    StrTaxVariable      Vari;
//    StrTaxConstant      Cons;
//    } Tax3;
//    
    u8             buf1[64];
    u16            buf2[64/2];
    u32            buf3[64/4];
    
    } Tax;    
    
    u16				CrcCheck                        ;//У��   2                 
}stcFlshRec;



#endif

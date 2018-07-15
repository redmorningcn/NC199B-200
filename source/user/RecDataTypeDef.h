/*******************************************************************************
* Description  :  定义存储记录的数据结构
* Author       : 2018/5/15 星期二, by redmorningcn
*******************************************************************************/

#ifndef  _RecDataTypeDef_h_
#define  _RecDataTypeDef_h_

#include <includes.h>


typedef union _strDevicErr
{
    struct{
        u16         Speed1Comm     : 1;    //D0=1：速度检测板1通讯故障
        u16         Speed2Comm     : 1;    //D1=1：速度检测板2通讯故障
        u16         Speed3Comm     : 1;    //D2=1：速度检测板3通讯故障
        u16         Speed1Lose     : 1;    //D3=1：速度检测板1丢脉冲故障（详见各通道sta）
        u16         Speed2Lose     : 1;    //D4=1：速度检测板2丢脉冲故障（详见各通道sta）
        u16         Speed3Lose     : 1;    //D5=1：速度检测板3丢脉冲故障（祥见各通道sta）
        u16         LocoComm       : 1;    //D6=1：工况信号检测板通讯故障
        u16         Disp1CommErr   : 1;    //D7=1：一端显示模块通讯故障
        u16         Disp2CommErr   : 1;    //D8=1：二端显示模块通讯故障
        u16         TaxCommErr     : 1;    //D9=1：TAX通讯故障
        u16         FlashErr       : 1;    //D10=1：存储器故障
        u16         FramErr        : 1;    //D11=1：铁电故障
        u16         TimeErr        : 1;    //D12=1：时间故障
        u16         RsvErr         : 3;   //     ：预留
    };
    u32                 Flags;
}strDeviceErr;

//2017-11-16  redmorningcn
//压缩空气质量装置，测量数据内容  
__packed
typedef struct _sAirQuality{
    u16				Temperature       ;//温度                                 2                    
    u16				Humidity          ;//湿度                                 2                    
    u16				VOCs              ;//挥发有机物                           2                    
    u16				CO2_EQU           ;//等值CO2                              2  
    CPU_INT32U      RS                ;// RS
    u16				PM1D0_S           ;//标准颗粒物浓度ug/m3                  2                    
    u16				PM2D5_S           ;//标准颗粒物浓度ug/m3                  2                    
    u16				PM10D_S           ;//标准颗粒物浓度ug/m3                  2    
    u16				PM1D0_G           ;// 大气环境                              
    u16				PM2D5_G           ;// 大气环境                    
    u16				PM10D_G           ;// 大气环境 
    u16             Dusts_0D3         ;//0.1升空气中直径在0.3um的颗粒物个数
    u16             Dusts_0D5         ;//0.1升空气中直径在0.5um的颗粒物个数
    u16             Dusts_1D0         ;//0.1升空气中直径在1.0um的颗粒物个数
    u16             Dusts_2D5         ;//0.1升空气中直径在2.5um的颗粒物个数    
} stcAirQuality;      

//2017-11-16  redmorningcn
//压缩空气质量装置，保存的数据结构     
typedef __packed struct _stcFlshRec     //定义数据记录数据结构（20171116 机车压缩空气）
{
    u8				CmdTpye         ;//命令类型       1     		        	
    u8				EvtType         ;//事件类型       1                  
    u16				LocoType        ;//机车型号       2                  
    u16				LocoNbr         ;//机 车 号       2                     
    u32				RecordId        ;//记录流水号     4
    
    stcAirQuality   sAir            ;//空气质量       28
    u8              RunSys          ;//运行状态       1（阀门门打开，开始测试，等等）      
    u8				Recv[8]         ;//预留                               
    //u16				ErrCode           ;//故障代码       2 
    struct _ErrCode {
        u16         MtrCommErr      : 1;    // 主机故障
        u16         Res             : 15;   // D11~D06：分
    } ErrCode;                                          // 04 时间    
    
    
    u8              Air_Hum_Grade   ;//湿度等级       1                  
    u8              Air_Voc_Grade   ;//VOC等级        1                   
    u8              Air_Dust_Grade  ;//粉尘等级       1    
    struct  {
        u32      Sec                 : 6;        // D05~D00：秒
        u32      Min                 : 6;        // D11~D06：分
        u32      Hour                : 5;        // D16~D12：时
        u32      Day                 : 5;        // D21~D17：日
        u32      Mon                 : 4;        // D25~D22：月
        u32      Year                : 6;        // D31~D26：年
    } ;                                      // 04 时间
    
////////////////////////////////////////////////// TAX的数据内容
    u8           TaxType             ;//TAX特征码       1                     
    u8           TaxFlg              ;//TAX特征码       64       
    /***************************************************
    * 描述： TAX:64 bytes
    */
    union __uTAX__Rec {
//    _StrTax_II_Rec      Tax2;                           // 记录数据     
//    struct __sTAX_III__Rec {
//    StrTaxVariable      Vari;
//    StrTaxConstant      Cons;
//    } Tax3;
//    
    u8             buf1[64];
    u16            buf2[64/2];
    u32            buf3[64/4];
    
    } Tax;    
    
    u16				CrcCheck                        ;//校验   2                 
}stcFlshRec;



#endif

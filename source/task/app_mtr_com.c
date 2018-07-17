/**************************************************************
* Description  : 处理板和速度检测板及工况检测板通讯
(采用modbus协议，处理板为主机，其他为从。速度检测板地址：1-3，工况检测板地址为：4)
* Author       : 2018/5/21 星期一, by redmorningcn
*/

/*******************************************************************************
* INCLUDES
*/
#include    <includes.h>
#include    <app_mtr_com.h>
#include    <string.h>



/**************************************************************
* Description  : 通讯状态指示
* Author       : 2018/5/22 星期二, by redmorningcn
*/
void    MtrCommErrjudge(u8   node,u16    sta)
{
    u8  err = 0;            //正常
    
    if(sta == 0)
        err = 1;            //故障
    
    switch(node)
    {
    case 1:
        Ctrl.sRunPara.Err.Speed1Comm= err;
        break;
    case 2:
        Ctrl.sRunPara.Err.Speed2Comm= err;
        break;
    case 3:
        Ctrl.sRunPara.Err.Speed3Comm= err;
        break;
    case 4:
        Ctrl.sRunPara.Err.LocoComm  = err;
        break;
    default:
        break;
    }
}
                                        
/**************************************************************
* Description  : 处理板读指定地址值。读取得值存在MtrCom->Rd中。
* Author       : 2018/5/22 星期二, by redmorningcn
*/
void    MtrRdSpecial(u16 addr,u8  len)
{
    u8      node = MtrCom->ConnCtrl.MB_Node;    //modbus地址
    u16     sta;
    
    sta  = MBM_FC03_HoldingRegRd(   MtrCom->pch,
                                    node,
                                    addr,
                                    (u16 *)&MtrCom->Rd,
                                    len);

    MtrCommErrjudge(node,sta);                  //故障判断，置runpara中的故障标识位。异常置1，正常置0    
    
    MtrCom->RxCtrl.Len      = sta;              //置数据长度。（长度控制在255以内）
    MtrCom->RxCtrl.RecvFlg  = 1;                //置接收完成标识。协调其他任务。
}                                        

/**************************************************************
* Description  : 处理板写指定位置。写前数据存在MtrCom->Wr中。
* Author       : 2018/5/22 星期二, by redmorningcn
*/
void    MtrWrSpecial(u16 addr,u8  len)
{
    u8      node = MtrCom->ConnCtrl.MB_Node;    //modbus地址
    u16     sta = 0;
    
    sta  = MBM_FC16_HoldingRegWrN ( MtrCom->pch,
                                    node,
                                    addr,
                                    (u16 *)&MtrCom->Wr,
                                    len);

    MtrCommErrjudge(node,sta);                  //故障判断，置runpara中的故障标识位。异常置1，正常置0    
    
    MtrCom->ConnCtrl.datalen      = sta;        //置数据长度。（长度控制在255以内）
    MtrCom->ConnCtrl.RecvEndFlg   = 1;          //置接收完成标识。协调其他任务。
}


#define MTR_READ_FLG  2
#define MTR_WRITE_FLG 1
/**************************************************************
* Description  : 处理板和检测板通讯
* Author       : 2018/5/22 星期二, by redmorningcn
*/
void app_mtr_com(void)
{
    u8      node = MtrCom->ConnCtrl.MB_Node;            //modbus地址

    if(MtrCom->ConnCtrl.protocol == MODBUS_PROTOCOL)    //modbus协议
    {
        u8      conntype = MtrCom->ConnCtrl.ConnType;
        u16     addr;
        u8      len;
        switch(conntype)
        {
            
        case MTR_RD_DETECT:

            /**************************************************************
            * Description  : 读取检测模块的数据
            * Author       : 2018/7/15 星期日, by redmorningcn
            */
            node = NODE_AIR;
            if(node == NODE_AIR){
                
                MtrCom->ConnCtrl.MB_Node = node;
                len  = sizeof(Ctrl.Rec.sAir)/2 ;                                         //工况检测板有效参数长度
                addr = 1;                                                                   //有效参数存储在结构体后部
                
                MtrRdSpecial(addr,len);                 
                
                if(MtrCom->RxCtrl.Len == len){
                    memcpy((u8 *)&Ctrl.Rec.sAir,(u8 *)&MtrCom->Rd.sAir,sizeof(Ctrl.Rec.sAir));   //取工况信号
                    
                }
            }
            
            break;
        default:
            break;
        }
    }
}




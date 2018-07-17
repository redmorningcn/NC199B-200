/**************************************************************
* Description  : �������ٶȼ��弰��������ͨѶ
(����modbusЭ�飬�����Ϊ����������Ϊ�ӡ��ٶȼ����ַ��1-3�����������ַΪ��4)
* Author       : 2018/5/21 ����һ, by redmorningcn
*/

/*******************************************************************************
* INCLUDES
*/
#include    <includes.h>
#include    <app_mtr_com.h>
#include    <string.h>



/**************************************************************
* Description  : ͨѶ״ָ̬ʾ
* Author       : 2018/5/22 ���ڶ�, by redmorningcn
*/
void    MtrCommErrjudge(u8   node,u16    sta)
{
    u8  err = 0;            //����
    
    if(sta == 0)
        err = 1;            //����
    
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
* Description  : ������ָ����ֵַ����ȡ��ֵ����MtrCom->Rd�С�
* Author       : 2018/5/22 ���ڶ�, by redmorningcn
*/
void    MtrRdSpecial(u16 addr,u8  len)
{
    u8      node = MtrCom->ConnCtrl.MB_Node;    //modbus��ַ
    u16     sta;
    
    sta  = MBM_FC03_HoldingRegRd(   MtrCom->pch,
                                    node,
                                    addr,
                                    (u16 *)&MtrCom->Rd,
                                    len);

    MtrCommErrjudge(node,sta);                  //�����жϣ���runpara�еĹ��ϱ�ʶλ���쳣��1��������0    
    
    MtrCom->RxCtrl.Len      = sta;              //�����ݳ��ȡ������ȿ�����255���ڣ�
    MtrCom->RxCtrl.RecvFlg  = 1;                //�ý�����ɱ�ʶ��Э����������
}                                        

/**************************************************************
* Description  : �����дָ��λ�á�дǰ���ݴ���MtrCom->Wr�С�
* Author       : 2018/5/22 ���ڶ�, by redmorningcn
*/
void    MtrWrSpecial(u16 addr,u8  len)
{
    u8      node = MtrCom->ConnCtrl.MB_Node;    //modbus��ַ
    u16     sta = 0;
    
    sta  = MBM_FC16_HoldingRegWrN ( MtrCom->pch,
                                    node,
                                    addr,
                                    (u16 *)&MtrCom->Wr,
                                    len);

    MtrCommErrjudge(node,sta);                  //�����жϣ���runpara�еĹ��ϱ�ʶλ���쳣��1��������0    
    
    MtrCom->ConnCtrl.datalen      = sta;        //�����ݳ��ȡ������ȿ�����255���ڣ�
    MtrCom->ConnCtrl.RecvEndFlg   = 1;          //�ý�����ɱ�ʶ��Э����������
}


#define MTR_READ_FLG  2
#define MTR_WRITE_FLG 1
/**************************************************************
* Description  : �����ͼ���ͨѶ
* Author       : 2018/5/22 ���ڶ�, by redmorningcn
*/
void app_mtr_com(void)
{
    u8      node = MtrCom->ConnCtrl.MB_Node;            //modbus��ַ

    if(MtrCom->ConnCtrl.protocol == MODBUS_PROTOCOL)    //modbusЭ��
    {
        u8      conntype = MtrCom->ConnCtrl.ConnType;
        u16     addr;
        u8      len;
        switch(conntype)
        {
            
        case MTR_RD_DETECT:

            /**************************************************************
            * Description  : ��ȡ���ģ�������
            * Author       : 2018/7/15 ������, by redmorningcn
            */
            node = NODE_AIR;
            if(node == NODE_AIR){
                
                MtrCom->ConnCtrl.MB_Node = node;
                len  = sizeof(Ctrl.Rec.sAir)/2 ;                                         //����������Ч��������
                addr = 1;                                                                   //��Ч�����洢�ڽṹ���
                
                MtrRdSpecial(addr,len);                 
                
                if(MtrCom->RxCtrl.Len == len){
                    memcpy((u8 *)&Ctrl.Rec.sAir,(u8 *)&MtrCom->Rd.sAir,sizeof(Ctrl.Rec.sAir));   //ȡ�����ź�
                    
                }
            }
            
            break;
        default:
            break;
        }
    }
}




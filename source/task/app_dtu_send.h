/**************************************************************
* Description  : �������DTUͨѶ
* Author       : 2018/5/23 ������, by redmorningcn
*/
#ifndef  _APP_DTU_SEND_H_
#define  _APP_DTU_SEND_H_

#include <includes.h>
#include <app_dtu_rec.h>

#define IAP_FRAME_CODE              0x0a      /* IAP ����֡������     */
#define SET_FRAME_CODE              0x02      /* SET ���ÿ�����       */
#define RECORD_FRAME_CODE           0x00      /* ���ݼ�¼csnc������    */     

#define SET_REPLY_DATA_LEN          (4+4+1)   /* ��ѯ�����ò�����Ӧ�����ݳ���*/
#define IAP_REPLY_DATA_LEN          (4)       /* IAP��������������֡Ӧ�𳤶� */



extern  void app_dtu_send(StrCOMCtrl *Com);


#endif

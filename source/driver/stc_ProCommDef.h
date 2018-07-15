/*******************************************************************************
 *   Revised:        All copyrights reserved to redmorningcn.
 *   Revision:       v1.0
 *   Writer:	     redmoringcn.
 *   Description:    
 *   Notes:
 *     				 E-mail: redmorningcn@qq.com
 *
 *******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _STC_PRO_COMM_DEF_H
#define _STC_PRO_COMM_DEF_H

/*******************************************************************************
 * INCLUDES
 */
//#include <app_tax.h>

/*******************************************************************************
 * CONSTANTS
 */

/*******************************************************************************
 * MACROS
 */
    
/*******************************************************************************
 * TYPEDEFS
 */

////�����ͺż��������
typedef struct {     
 	uint16	Type;				//��������	2	�μ��������ʹ����
 	uint16	Num;				//������		2	
} stcLocoId;

//��Ʒ��Ϣ:  �ͺ�+ ���
//12 bytes
typedef struct _StrProductInfo {
	uint32		    Type;			//��Ʒ���0 :NDP02  ,1:NDP02-B
	uint32		    ID;				//��Ʒ���	16110002
	stcLocoId		sLocoId;		//������Ϣ	104(DF4B) - 1000
}stcProductInfo;

//��¼�Ź���:���ݼ�¼����
//16 bytes
typedef struct _StrRecNumMgr {
    uint32		Current;				//��ǰ��¼��	0~0xffffffff
    uint32		IcRead;				//IC���Ѷ�ȡ��¼��
    uint32		GrsRead;			//�����Ѷ�ȡ��¼��
    uint32		Back;				//����
}stcRecNumMgr;


//�����������: ģ�ͱ�ţ��߶ȣ��ܶȣ�б��
//32 bytes
__packed
typedef struct _StrAirPara {
     struct _sStandard_Hum {
        uint16      GoodLimit;          //����Ϊ�ţ�                         ��ɫָʾ
        uint16      NormalLimit;        //���ڸ�ֵ��С��good��Ϊһ��         ��ɫָʾ  С�ڸ�ֵ��Ϊ���ɫ��ʾ  
    } sStandard_Hum;                    //ʪ����ֵ                                 
    
    struct _sStandard_VOC {
        uint16      GoodLimit;          //����Ϊ�ţ�                         ��ɫָʾ
        uint16      NormalLimit;        //���ڸ�ֵ��С��good��Ϊһ��         ��ɫָʾ  С�ڸ�ֵ��Ϊ���ɫ��ʾ  
    } sStandard_VOC;                    //VOC��ֵ
    
    struct _sStandard_Dust {
        uint16      GoodLimit;          //����Ϊ�ţ�                         ��ɫָʾ
        uint16      NormalLimit;        //���ڸ�ֵ��С��good��Ϊһ��         ��ɫָʾ  С�ڸ�ֵ��Ϊ���ɫ��ʾ  
    } sStandard_Dust;                   //�۳���ֵ
    
    int16           Temp_modefy;        //�¶�����ֵ�����ڲ���
    int16           Hum_modefy;         //ʪ������ֵ�����ڲ���
    
    int16           Dust_modefy;        //�۳�����ֵ�����ڲ���
    int16           Voc_modefy;         //VOC����ֵ �����ڲ���          

    uint8           tmp[14];            //Ԥ��
    
    struct __SetFlg {
    uint16      SetHumStand             : 1;        // D0��=1:����·��=0:�ޣ�
    uint16      SetVocStand             : 1;        // D1��=1 �ر���·��=0:�ޣ�
    uint16      SetDustStand            : 1;        // D2��=1:��ʼ������=0:�ޣ�
    uint16      SetHumModefy            : 1;        // D3��=1:����������=0:�ޣ�
    uint16      SetVocModefy            : 1;        // D4��=1:���ݱ��棻=0:�ޣ�
    uint16      SetDustModefy           : 1;        // D5��=1:���ݱ��棻=0:�ޣ�
    uint16      Rsv                     : 10;       // D6~D15��Ԥ��
    } SetFlg;    
    
    uint16  recv;
    uint16  crc16;
}stcAirPara;

//
//���в�����װ��������أ����ݴ洢���ڣ���ʾ�������ָ���������
//8 bytes
__packed
typedef struct _stcRunPara_					
{
	uint8		StoreCycle;					// 1 		���ݼ�¼�洢����
	uint8		RecClear;					// 1		���ݼ�¼���㣬��StrRecNumMgr����
	uint8		SysReset;					// 1    	ϵͳ�������ã���StrRecNumMgr + StrOilPara 	�е����ݡ�
	uint8		StartFlg;					// 1    	�״�����

    struct __SysSta {
        uint8      OpenAir              : 1;        // D0��=1:����·��=0:�ޣ�
        uint8      CloseAir             : 1;        // D1��=1 �ر���·��=0:�ޣ�
        uint8      StartMeasure         : 1;        // D2��=1:��ʼ������=0:�ޣ�
        uint8      EndMeasure           : 1;        // D3��=1:����������=0:�ޣ�
        uint8      Store                : 1;        // D4��=1:���ݱ��棻=0:�ޣ�
        uint8      mtrsim               : 1;        //debug use
        uint8      mtrsend              : 1;        //debug use

        uint8      Rsv                  : 1;        // D7~D5��Ԥ��
    } SysSta;                                       // ϵͳ����״̬
    
	uint8		StoreType;                  // 1   	    ?�̨�3??DD���䨬?
	uint8		StoreTypeBak;               // 1   	    ?�̨�3??DD���䨬?
	uint8		SetBitFlg;					// 1        ����??��DD��????��?
    
    uint8       MeasureSecond;          //1          ???��2a��?����??
    uint8       MeasureMin;             //1          ???��2a��?????����??
    uint8       buf[26];
    
    struct __setflg {
        uint32      StoreCycle            : 1;        // D0��o=1:��?
        uint32      RecClear             : 1;        // D1��o=1 ��?
        uint32      StoreType            : 1;        // D2��o=1:��?
        uint32      MeasureSecond        : 1;        // D3��o=1:��?
        uint32      MeasureMin           : 1;      	  // D3��o=1:��?
    
        uint32      Rsv                  : 27;        // D7~D5��o?�訢?
    } setflg;      	
}stcRunPara;


/***********************************************
* ������ 2017/8/19�������������
*/
__packed
typedef struct {
                                                    //���  �ֶ�����	����	    ����	˵��	��ע
    CHAR                XinHao;                     // 0	��Ʒ�ͺ�	BYTE[10]	10		ASCII��NCS27
    CHAR                BianHao;                    //10	��Ʒ���	BYTE[10]	10		ASCII��2017070001
    WORD                HWVer;                      //20	Ӳ���汾	WORD	    2		��8λΪ��汾����8λΪС�汾��V1.0
    WORD                SWVer;                      //22	����汾	WORD	    2		��8λΪ��汾����8λΪС�汾��V1.0
    WORD                JiCheXingHao;               //24	�����ͺ�	WORD	    2		
    WORD                JiCheHao;                   //26	������	    WORD	    2		
    WORD                CeShiShiJian[6];            //28	����ʱ��	BYTE[6]	    6		170731
    WORD                CeShiRenYuan[8];            //34	������Ա	BYTE[8]	    8		
    CHAR                AnZhuangShiJian[6];         //42	��װʱ��	BYTE[6]	    6		
    CHAR                AnZhuangRenYuan[8];         //48	��װ��Ա	BYTE[10]	8		
    CHAR                WeiXiuShiJian[6];           //56	ά��ʱ��	BYTE[6]	    6		
    CHAR                WeiXiuRenYuan[8];           //62	ά����Ա	BYTE[10]	8		
    BYTE                WeiXiuCiShu;                //70	ά�޴���	BYTE	    1		
    BYTE                MuKuanPeiZhi;               //71	ģ������	BYTE	    1		����ͨѶ���豸������ÿһλ����һ���豸����ӦλΪ1����ʾʹ�ø��豸����ӦλΪ0����ʾ���ã����ݾ���Ӧ������
    DWORD               KaiJiCiShuo         :18;    //72	����״̬	DWORD	    4		D31~21������������ÿ����һ�μ�1
    DWORD               GongZuoShiJian      :14;    //                                  D20~0������ʱ������СʱΪ��λ
    BYTE                Rsv[50];                    //76	Ԥ��	    BYTE[50]	50		�Զ���
    WORD                Chk;                        //126	У����	    WORD	    2		CRC
}stcProLog;             //��Ʒ��־

/***************************************************
* ������ ��������������256 + 4 = 260�ֽ�
*/
__packed
typedef struct _StrCtrlPara {
    /***************************************************
    * ������ ϵͳ��������ʼ��ַ = 000
    */    
    INT16U              Password;                       // ����MODEBUSͨѶȷ����Կ��Ĭ��Ϊ6237����ֹ�Ƿ�������
    /***************************************************
    * ������ ����汾����ʼ��ַ = 002
    */
    INT16U		        SoftWareID;                     //	2  	����汾
    //
    /***************************************************
    * ��������¼�Ź����ַ����ʼ��ַ = 004
    */
    stcRecNumMgr        sRecNumMgr;			        //	16	��¼�Ź���: ��ǰ��¼�ţ����Ѷ���¼�ţ������Ѷ���¼��
       //
    /***************************************************
    * ��������Ʒ��Ϣ����ʼ��ַ = 020
    */
    stcProductInfo	    sProductInfo;			    //	12	��Ʒ��Ϣ: ��Ʒ�źż���Ʒ��ţ�
    //
    /***************************************************
    * ���������������������ʼ��ַ = 32
    */
	stcAirPara          sAirPara;                       //32

    //
    /***************************************************
    * ������ϵͳ���в�������ʼ��ַ = 64
    */
	stcRunPara	        sRunPara;				        // 8		//���ݴ洢���ڣ��������㣬��������
    
    /***************************************************
    * ��������Ʒ������־����ʼ��ַ = 72               
    */ 
    stcProLog           sProLog;                       //126     

//    /***************************************************
//    * ������ �ָ��������ã���ʼ��ַ = 198
//    */
//    INT16S          RestoreSetting;                     // �ָ���������

    const struct _StrCtrlPara *idx;                    // ���ָ�룬ռ4�ֽ�

} StrCtrlPara;


// �������ݽṹ		����-->ͳ��		
__packed
typedef union {
    StrCtrlPara	dat;   //	
    uint8		buf1[256];   //	
    uint8		buf2[256];   //	
} UniCtrlPara;
/*******************************************************************************
 * LOCAL VARIABLES
 */

/*******************************************************************************
 * GLOBAL VARIABLES
 */
 
/*******************************************************************************
 * LOCAL FUNCTIONS
 */

/*******************************************************************************
 * GLOBAL FUNCTIONS
 *
 * ��������         ��������                ��ڲ���
 */

/*******************************************************************************
 * EXTERN VARIABLES
 */

/*******************************************************************************
 * EXTERN FUNCTIONS
 */

#endif 



/*******************************************************************************
 *   Filename:       bsp_max7219.h
 *   Revised:        $Date: 2015-12-07$
 *   Revision:       $
 *	 Writer:		 Wuming Shen.
 *
 *   Description:
 *   Notes:
 *					QQ:276193028
 *     				E-mail:shenchangwei945@163.com
 *
 *   All copyrights reserved to Wuming Shen.
 *
 *******************************************************************************/
#ifndef	__BSP_MAX_7219_H__
#define	__BSP_MAX_7219_H__

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * INCLUDES
 */
#include <includes.h>

#ifdef   BSP_GLOBALS
#define  BSP_EXT
#else
#define  BSP_EXT  extern
#endif
    
/*******************************************************************************
 * CONSTANTS
 */
#define RIGHT               0
#define LEFT                1 

#define DISPLAY_FRAME_NUM   4
#define DISPLAY_LED_NUM     4   
/*******************************************************************************
 * MACROS
 */
/*******************************************************************************
 * CONSTANTS
 */
/***********************************************
* ������ max7219�Ĵ�����ַ����
*/
#define MAX7279_NON_OPT         0x00            // �ղ����Ĵ���
#define Digit0                  0x01            // �����1�Ĵ���
#define Digit1                  0x02            // �����2�Ĵ���
#define Digit2                  0x03            // �����3�Ĵ���
#define Digit3                  0x04            // �����4�Ĵ���
#define Digit4                  0x05            // �����5�Ĵ���
#define Digit5                  0x06            // �����6�Ĵ���
#define Digit6                  0x07            // �����7�Ĵ���
#define Digit7                  0x08            // �����8�Ĵ���
/**/
#define MAX7279_DECODE_MODE     0x09            // ����ģʽ�Ĵ���
#define MAX7279_BRIGHTNESS      0x0a            // ���ȼĴ���
#define MAX7279_SCAN            0x0b            // ɨ��λ���Ĵ���
#define MAX7279_LOW_PWR         0x0c            // �͹���ģʽ�Ĵ���
#define MAX7279_DISP_TEST       0x0f            // ��ʾ���ԼĴ���

/***********************************************
* ������ max7219���ƼĴ�������
*/
#define MAX7279_LOW_PWR_MODE    0x00            // �͹��ķ�ʽ
#define MAX7279_NORMAL_MODE     0x01            // ����������ʽ
#define MAX7279_DECODE_SET      0x00            // �������ã�8λ��ΪBCD��;��8����������
#define MAX7279_8_DIGIT_SCAN    0x07            // ɨ��λ�����ã���ʾ8λ�����
#define MAX7279_4_DIGIT_SCAN    0x03            // ɨ��λ�����ã���ʾ4λ�����
//#define MAX7279_BRIGHTNESS_LEVEL    0x00      // ���ȼ�������
#define MAX7279_BRIGHTNESS_LEVEL 0X0A           // ���ȼ�������
//#define MAX7279_BRIGHTNESS_LEVEL    0xf       // ���ȼ�������
#define MAX7279_TEST_ENTER      0x01            // ��ʾ����ģʽ
#define MAX7279_TEST_EXIT       0x00            // ��ʾ���Խ������ָ���������ģʽ


    
/*******************************************************************************
 * TYPEDEFS
 */
typedef struct _StrLedDisp {
    uint8	Flag;
    uint8	Cycle;
    uint8	Duty;
    uint8	Code[DISPLAY_LED_NUM];
}StrLedDisp;

/***********************************************
* ������ 
*/    
extern StrLedDisp  LedDispCtrl[DISPLAY_FRAME_NUM];
extern uint8       	LedDispBuf[DISPLAY_LED_NUM];
extern const uint8 	LED_SEG_CODE[];

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
void                BSP_MAX7219Init        ( void );
     
/*******************************************************************************
 * EXTERN VARIABLES
 */

/*******************************************************************************
 * EXTERN FUNCTIONS
 */

//-----------------------------------------------------------------------------
//��������: BSP_DispNum ()
//��    ��: ������ܽ�����������ʾ����
//��ڲ���:,number
//���ڲ���: ��
//----------------------------------------------------------------------------
extern void BSP_DispNum(uint32 Num, uint8 Flag);

//------------------------------------------------------
//��������:MovBSP_DispCharacter ()
//��    ��:���������ʾ�ַ����Ѷ��ַ�
//��ڲ���:character: �ַ�����
//���ڲ���:��
//��ʾ����:   -   E   H   L   P   Black
//���ݴ���:	  A	  B	  C	  D	  E	  F
//-------------------------------------------------------
extern void MovBSP_DispCharacter (uint8 character);

//------------------------------------------------------
//��������:MovBSP_DispCharacter ()
//��    ��:���������ʾ�ַ����Ѷ��ַ�
//��ڲ���:character: �ַ�����
//���ڲ���:��
//��ʾ����:   -   E   H   L   P   Black
//���ݴ���:	  A	  B	  C	  D	  E	  F
//-------------------------------------------------------
extern void MovBSP_DispCharacter (uint8 Character);
//-------------------------------------------------------------------
//��������:     BSP_DispInit ()
//��    ��:     7219��ʼ��
//��ڲ���:     ��
//���ڲ���:     ��
//-------------------------------------------------------------------
extern void BSP_DispInit (void);

//=====================================================
//��������:BSP_DispNum()
//��    ��:������ܽ�����������ʾ����
//��ڲ���1:    num         ��ʾ����
//��ڲ���2:    DotPosition ��ʾ���λ�ã�
//              ����λ��Ӧ4λ�������ʾ�㣬1Ϊ��ʾ��0����ʾ
//���ڲ���:��
//=====================================================
//
// 		uint8	Flag;
//		uint8	Cycle;
//		uint8	Duty;
//		uint8	OffX100ms;
//		uint8	Code[4];
extern void BSP_DispWrite(   int     Num,
                            char    *Fmt,
                            char    Align,
                            uint8   FmtType,
                            uint8   DotPosition,
                            uint8   Cycle,
                            uint8   Duty,
                           // uint8   OffX100ms,
                            uint8   Order);

//=====================================================
//��������:BSP_DispNum()
//��    ��:������ܽ�����������ʾ����
//��ڲ���1:    num         ��ʾ����
//��ڲ���2:    DotPosition ��ʾ���λ�ã�
//              ����λ��Ӧ4λ�������ʾ�㣬1Ϊ��ʾ��0����ʾ
//���ڲ���:��
//=====================================================
extern void BSP_Disp(uint8 Order);

//------------------------------------------------------
//��������:     BSP_DispString ()
//��    ��:     ���������ʾ�ַ�������
//��ڲ���:     String: �ַ�����
//���ڲ���:     ��
//��ʾ����:     String
//���ݴ���:	    ���ø�ʽ  BSP_DispString("ABCD");
//-------------------------------------------------------
extern void BSP_DispString(uint8 * String);

//=====================================================
//��������:BSP_DispChar()
//��    ��:������ܽ�����������ʾ����
//��ڲ���1:    num         ��ʾ����
//��ڲ���2:    DotPosition ��ʾ���λ�ã�
//              ����λ��Ӧ4λ�������ʾ�㣬1Ϊ��ʾ��0����ʾ
//���ڲ���:��
//=====================================================

// 		uint8	Flag;
//		uint8	Cycle;
//		uint8	Duty;
//		uint8	OffX100ms;
//		uint8	Code[4];
extern void BSP_DispWriteChar(	uint8 	*String,
							uint8 	DotPosition,
							uint8	Flag,
							uint8	Cycle,
							uint8	Duty,
							//uint8	OffX100ms,
							uint8	Order);

//------------------------------------------------------
//��������:BSP_DispClr ()
//��    ��:�����ʾ������,������ʾ��־λ����ʾ����
//��ڲ���:�ڼ�����ʾ������
//���ڲ���:
//-------------------------------------------------------
//=====================================================
//��������:BSP_DispEvtProcess()
//��    ��:������ܽ�����������ʾ����
//��ڲ���1:    num         ��ʾ����
//��ڲ���2:    DotPosition ��ʾ���λ�ã�
//              ����λ��Ӧ4λ�������ʾ�㣬1Ϊ��ʾ��0����ʾ
//���ڲ���:��
//=====================================================
extern uint8     BSP_DispEvtProcess(void);
extern void     BSP_DispClr(uint8 order );
extern void     BSP_DispSetBrightness ( u8 bl );

extern void     BSP_DispClrAll(void);
extern void     BSP_DispOff(void);
extern void     TestSegment(void);
extern void     LED_SPI_SendData(u8 Addr,u8 Num);


/*******************************************************************************
 *              end of file                                                    *
 *******************************************************************************/
#ifdef __cplusplus
}
#endif
#endif
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
* 描述： max7219寄存器地址定义
*/
#define MAX7279_NON_OPT         0x00            // 空操作寄存器
#define Digit0                  0x01            // 数码管1寄存器
#define Digit1                  0x02            // 数码管2寄存器
#define Digit2                  0x03            // 数码管3寄存器
#define Digit3                  0x04            // 数码管4寄存器
#define Digit4                  0x05            // 数码管5寄存器
#define Digit5                  0x06            // 数码管6寄存器
#define Digit6                  0x07            // 数码管7寄存器
#define Digit7                  0x08            // 数码管8寄存器
/**/
#define MAX7279_DECODE_MODE     0x09            // 译码模式寄存器
#define MAX7279_BRIGHTNESS      0x0a            // 亮度寄存器
#define MAX7279_SCAN            0x0b            // 扫描位数寄存器
#define MAX7279_LOW_PWR         0x0c            // 低功耗模式寄存器
#define MAX7279_DISP_TEST       0x0f            // 显示测试寄存器

/***********************************************
* 描述： max7219控制寄存器命令
*/
#define MAX7279_LOW_PWR_MODE    0x00            // 低功耗方式
#define MAX7279_NORMAL_MODE     0x01            // 正常操作方式
#define MAX7279_DECODE_SET      0x00            // 译码设置，8位均为BCD码;对8个数都编码
#define MAX7279_8_DIGIT_SCAN    0x07            // 扫描位数设置，显示8位数码管
#define MAX7279_4_DIGIT_SCAN    0x03            // 扫描位数设置，显示4位数码管
//#define MAX7279_BRIGHTNESS_LEVEL    0x00      // 亮度级别设置
#define MAX7279_BRIGHTNESS_LEVEL 0X0A           // 亮度级别设置
//#define MAX7279_BRIGHTNESS_LEVEL    0xf       // 亮度级别设置
#define MAX7279_TEST_ENTER      0x01            // 显示测试模式
#define MAX7279_TEST_EXIT       0x00            // 显示测试结束，恢复正常工作模式


    
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
* 描述： 
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
 * 返回类型         函数名称                入口参数
 */
void                BSP_MAX7219Init        ( void );
     
/*******************************************************************************
 * EXTERN VARIABLES
 */

/*******************************************************************************
 * EXTERN FUNCTIONS
 */

//-----------------------------------------------------------------------------
//函数名称: BSP_DispNum ()
//功    能: 用数码管将整型数据显示出来
//入口参数:,number
//出口参数: 无
//----------------------------------------------------------------------------
extern void BSP_DispNum(uint32 Num, uint8 Flag);

//------------------------------------------------------
//函数名称:MovBSP_DispCharacter ()
//功    能:用数码管显示字符即已定字符
//入口参数:character: 字符代码
//出口参数:无
//显示内容:   -   E   H   L   P   Black
//内容代码:	  A	  B	  C	  D	  E	  F
//-------------------------------------------------------
extern void MovBSP_DispCharacter (uint8 character);

//------------------------------------------------------
//函数名称:MovBSP_DispCharacter ()
//功    能:用数码管显示字符即已定字符
//入口参数:character: 字符代码
//出口参数:无
//显示内容:   -   E   H   L   P   Black
//内容代码:	  A	  B	  C	  D	  E	  F
//-------------------------------------------------------
extern void MovBSP_DispCharacter (uint8 Character);
//-------------------------------------------------------------------
//函数名称:     BSP_DispInit ()
//功    能:     7219初始化
//入口参数:     无
//出口参数:     无
//-------------------------------------------------------------------
extern void BSP_DispInit (void);

//=====================================================
//函数名称:BSP_DispNum()
//功    能:用数码管将整型数据显示出来
//入口参数1:    num         显示数据
//入口参数2:    DotPosition 显示点的位置，
//              低四位对应4位数码的显示点，1为显示，0不显示
//出口参数:无
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
//函数名称:BSP_DispNum()
//功    能:用数码管将整型数据显示出来
//入口参数1:    num         显示数据
//入口参数2:    DotPosition 显示点的位置，
//              低四位对应4位数码的显示点，1为显示，0不显示
//出口参数:无
//=====================================================
extern void BSP_Disp(uint8 Order);

//------------------------------------------------------
//函数名称:     BSP_DispString ()
//功    能:     用数码管显示字符串代码
//入口参数:     String: 字符代码
//出口参数:     无
//显示内容:     String
//内容代码:	    调用格式  BSP_DispString("ABCD");
//-------------------------------------------------------
extern void BSP_DispString(uint8 * String);

//=====================================================
//函数名称:BSP_DispChar()
//功    能:用数码管将整型数据显示出来
//入口参数1:    num         显示数据
//入口参数2:    DotPosition 显示点的位置，
//              低四位对应4位数码的显示点，1为显示，0不显示
//出口参数:无
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
//函数名称:BSP_DispClr ()
//功    能:清除显示缓冲区,包括显示标志位和显示内容
//入口参数:第几个显示缓冲区
//出口参数:
//-------------------------------------------------------
//=====================================================
//函数名称:BSP_DispEvtProcess()
//功    能:用数码管将整型数据显示出来
//入口参数1:    num         显示数据
//入口参数2:    DotPosition 显示点的位置，
//              低四位对应4位数码的显示点，1为显示，0不显示
//出口参数:无
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
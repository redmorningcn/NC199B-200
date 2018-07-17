/*******************************************************************************
 *   Revised:        $Date: 2017-11-15$
 *   Revision:       $
 *   Writer:	     redmorningcn.
 *   Description:    
 *   Notes:
 *     				E-mail:redmorningcn@qq.com
 *
 *   All copyrights reserved to redmorningcn.
 *
 *******************************************************************************/
#ifndef  _BSP_DM412_h_
#define  _BSP_DM412_h_

/* Define to prevent recursive inclusion -------------------------------------*/
//#include    <bsp_gpio.h>

/*******************************************************************************
 * MACROS
 */
    
/*******************************************************************************
 * TYPEDEFS
 */

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

/**-------------------------------------------------------
* @函数名  bsp_DM412Init
* @功能    初始化LED1的端口
author:    redmorningcn
data:      2017-11-13
***------------------------------------------------------*/
void bsp_DM412Init(void);

//---------------------------------------------------------------------------------
//功    能:  对led进行颜色设置
//入口参数:  需要连续发送三次，再发送一次装载指令，才能将数据下载至DM412           
//author:    redmorningcn，颜色为RGB，
//data:      2017-11-13
//----------------------------------------------------------------------------------
void    SetLedColor(uint8 lenuum,uint16  red,uint16  green,uint16  blue);

#define     RGB_LED_COLOR_RED       0xffff,0x0000,0x0000
#define     RGB_LED_COLOR_GREEN     0x0000,0xffff,0x0000
#define     RGB_LED_COLOR_BLUE      0x0000,0x0000,0xffff
#define     RGB_LED_COLOR_WHITE     0xffff,0xffff,0xffff

#define     HUM_LED         0
#define     DUST_LED        1
#define     OIL_LED         2

#define     GOOD_GRADE      0
#define     NORMAL_GRADE    1
#define     BAD_GRADE       2

#define     HUM_LIMIT_GOOD      (60)
#define     HUM_LIMIT_NORMAL    (85)

#define     DUST_LIMIT_GOOD     (200)
#define     DUST_LIMIT_NORMAL   (500)

#define     OIL_LIMIT_GOOD      (500)
#define     OIL_LIMIT_NORMAL    (2000)


#endif



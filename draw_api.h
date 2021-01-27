#ifndef __DRAW_API_H
#define __DRAW_API_H

/*ÔÚ´Ë´¦Ìí¼ÓoledÇý¶¯µÄÇý¶¯Í·ÎÄ¼þ*/
#include ""
//±ÈÈçÎÒµÄÊÇ #include "oled.h"
/* ************************* */


#include <math.h>




#ifndef uchar
#define uchar unsigned char
#endif
#ifndef uint
#define uint unsigned int
#endif

extern unsigned char BMP[1024];
void Draw_Point(uchar x,uchar y);//ï¿½ï¿½ï¿½Æµï¿½ï¿½ï¿½ï¿½ï¿½
void Draw_Line(uchar x1,uchar y1,uchar x2,uchar y2);//ï¿½ï¿½ï¿½ï¿½Ò»ï¿½ï¿½Ö±ï¿½ß£ï¿½ï¿½ï¿½ï¿½ï¿½x1<x2ï¿½ï¿½
void Draw_Rect(uchar x1,uchar y1,uchar x2,uchar y2,uchar Full);//ï¿½ï¿½ï¿½ï¿½Ò»ï¿½ï¿½ï¿½ï¿½ï¿½Î£ï¿½(x1,y1)ï¿½ï¿½ï¿½ï¿½ï¿½Ï½ï¿½ï¿½ï¿½ï¿½ê£¬ï¿½ï¿½Ò»ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Â½ï¿½ï¿½ï¿½ï¿½ê£¬Full=1Îªï¿½ï¿½ï¿½Ä£Ê½ï¿½ï¿?=0Îªï¿½ï¿½ï¿½ï¿½ï¿?
void Draw_Tri(uchar x1,uchar y1,uchar x2,uchar y2,uchar x3,uchar y3);//ï¿½ï¿½ï¿½ï¿½Ò»ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
void Draw_Circle(uchar x,uchar y,uchar r);//ï¿½ï¿½ï¿½ï¿½Ò»ï¿½ï¿½Ô²
void OLED_ShowCharRAM(uchar x,uchar y,uchar CHAR,uchar fontsize);
void OLED_ShowStrRAM(uchar x,uchar y,uchar*chr,uchar fontsize);
void OLED_ShowNumRAM(unsigned char x,unsigned char y,long int num,unsigned char len,unsigned char size);
void DisPlay(void);//ï¿½ï¿½Ê¾ï¿½ï¿½ï¿½Æµï¿½Í¼ï¿½ï¿½
void CanvasClear(void);//ï¿½ï¿½Õ»ï¿½ï¿½ï¿?

#endif



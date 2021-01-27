# 贪吃蛇逻辑库

## 移植
1. 将`SnakeGame`文件夹添加至keil工程中，在工程设置里添加`SnakeGame`的include路径
2. 打开`draw_api.h`文件，在文件开头添加你自己的oled驱动的头文件
3. 确保自己的oled驱动中有`OLED_WR_Byte()`跟`OLED_Set_Pos()`函数

## 使用
在main.c文件中包含头文件`snake.h`即可使用该库所有功能
1. main文件还需要包含正点原子的`delay.h`文件，并进行初始化
2. 调用`Snake_FOOD_Init()`函数，对游戏进行初始化
3. 在一个循环内(判断条件是`Gamestatus`)调用`GameCir()`实现游戏运行

~~~c
#include "stm32f10x.h"
#include "snake.h"
#include "delay.h"

int main(void)
{
    SystemInit();
    delay_Init(72); //不同的模板可能初始化不一样 你懂就行 

    Snake_FOOD_Init();
    while(Gamestatus)
	{
		GameCir();
	}
}

~~~
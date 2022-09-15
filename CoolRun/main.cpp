/*****************************************************************//**
 * \file   main.cpp
 * \brief  Setup CoolRun Window
 *
 * \author jinnian
 * \date   September 2022
 *********************************************************************/
//#include <stdio.h>
// // Import graphical library
//#include <graphics.h>
//#include <conio.h>
//#include "tools.h"
//
//#include <mmsystem.h>
//#pragma comment(lib, "winmm.lib")		// 连接到winmm库
////import std.core; 这部分导入失败出现了版本问题
//import obstacles;
//
//#define WIDTH 1012
//#define HEIGHT 396
//IMAGE imgs[3];
//int bgdstX[3];						// 背景图片位置x轴
//int bgSpeed[3] = { 1, 2, 4 };		// 滑动速度
//
//IMAGE heros[12];					// 英雄实现奔跑
//int hDstX;							// 英雄x坐标
//int hDstY;							// 英雄Y坐标
//bool canJump;						// 英雄是否可以跳跃
//int degrees[30];					// hero上跳过程中的速度程度,符合实际物理规律
//int dgIndex;						// degress数组索引
//bool update;
//
//IMAGE imgTortoise;					// 乌龟障碍物
//
//
//
//// 函数声明
//void init(int width, int height);
//void updateBackgroud();
//void bgSlide();
//void heroRun(int heroIndex);
//void keyCatch();
//void tortoiseProduct();

#include "base.h"
#include "tools.h"
import obstacles;

int main(void) {
	CoolRun master;
	//实时渲染
	int hIndex = 0, timer = 0;					// 计时器
	while (true) {								// 键盘捕获
		timer += getDelay();					// 替换sleep实时接受键盘操作
		if (timer > 30 || master.getUpdate()) {
			timer = 0; 
			master.setUpdate(false);
			master.keyCatch();
			BeginBatchDraw();					// 缓冲打印
			master.updateBackgroud();			// 背景渲染
			master.heroRun(hIndex);				// 英雄渲染
			master.tortoiseProduct();			// 乌龟障碍物渲染
			EndBatchDraw();						// 结束
			master.bgSlide();
			if (master.getCanJump() == true)				// hero跳跃过程中不奔跑
				hIndex = (hIndex + 1) % 12;
		}

		
	}

	return 0;

}
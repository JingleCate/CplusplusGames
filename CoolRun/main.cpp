/*****************************************************************//**
 * \file   main.cpp
 * \brief  Setup CoolRun Window
 *
 * \author jinnian
 * \date   September 2022
 *********************************************************************/
#include <stdio.h>
 // Import graphical library
#include <graphics.h>
#include <conio.h>
#include "tools.h"

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")		// 连接到winmm库
//import std.core; 这部分导入失败出现了版本问题
import obstacles;

#define WIDTH 1012
#define HEIGHT 396
IMAGE imgs[3];
int bgdstX[3];						// 背景图片位置x轴
int bgSpeed[3] = { 1, 2, 4 };		// 滑动速度

IMAGE heros[12];					// 英雄实现奔跑
int hDstX;							// 英雄x坐标
int hDstY;							// 英雄Y坐标
bool canJump;						// 英雄是否可以跳跃
int degrees[10] = { 5,4,3,2,1,-1,-2,-3,-4,-5 };// hero上跳过程中的速度程度,符合实际物理规律
int dgIndex;						// degress数组索引
bool update;

IMAGE imgTortoise;					// 乌龟障碍物


// 函数声明
void init(int width, int height);
void updateBackgroud();
void bgSlide();
void heroRun(int heroIndex);
void keyCatch();



int main(void) {
	init(WIDTH, HEIGHT);
	//实时渲染
	int hIndex = 0, timer = 0;				// 计时器
	while (true) {							// 键盘捕获
		timer += getDelay();				// 替换sleep实时接受键盘操作
		if (timer > 30 || update) {
			timer = 0; 
			update = false;
			keyCatch();
			BeginBatchDraw();					// 缓冲打印
			updateBackgroud();					// 背景渲染
			heroRun(hIndex);			// 英雄渲染
			EndBatchDraw();						// 结束
			bgSlide();
			if (canJump == true)				// hero跳跃过程中不奔跑
				hIndex = (hIndex + 1) % 12;
		}

		
	}

	return 0;

}


// 函数实现

/**
 * create game window
 * @param width width width of window
 * @param height height of window
 */
void init(int width = 1012, int height = 396) {
	initgraph(width, height);


	// 加载背景图片
	char name[64];
	for (int i = 0; i < 3; i++) {
		// 路径存到name缓冲区
		sprintf_s(name, "res/bg%03d.png", i + 1);// sprintf生成文件名
		loadimage(&imgs[i], name);// 这里调节字符集(项目)
		bgdstX[i] = 0;
	}

	// 加载英雄图片
	for (int i = 0; i < 12; i++) {
		sprintf_s(name, "res/hero%d.png", i + 1);
		loadimage(&heros[i], name);
	}

	// 初始化hero坐标
	hDstX = int(WIDTH * 0.5 - heros[0].getheight() * 0.5);
	hDstY = 345 - heros[0].getheight();

	canJump = true;				// 默认初始条件下可以起跳
	dgIndex = 0;
	update = false;

	// 加载乌龟图片
	sprintf_s(name, "res/t%d.png", 1);
	loadimage(&imgTortoise, name);
	
}

// 图片滑动效果
void bgSlide() {
	for (int i = 0; i < 3; i++) {
		bgdstX[i] -= bgSpeed[i];
		if (bgdstX[i] < -WIDTH)
			bgdstX[i] = 0;

	}
}

void updateBackgroud() {
	// 三个图片在y轴上分层平铺
	// putimage有穿透效果, putimagePNG不支持负坐标, 缓冲打印图片
	putimagePNG2(bgdstX[0], 0, &imgs[0]);
	putimagePNG2(bgdstX[1], 119, &imgs[1]);
	putimagePNG2(bgdstX[2], 330, &imgs[2]);
}

void heroRun(int heroIndex) {
	// 渲染英雄模型
	putimagePNG2(hDstX, hDstY, &heros[heroIndex]);
}

void jump() {

	hDstY -= 8 * degrees[dgIndex];

	// 界定dgIndex范围防止溢出
	dgIndex++;
	if (dgIndex >= 10) {
		dgIndex %= 10;
		canJump = true;
	}
}

/**
 * 处理键盘输入以控制hero动作.
 */
void keyCatch() {
	char key;
	//if(update==)
	// 如果允许跳跃则捕获键盘行为否则直接完成未结束的跳跃
	if (canJump == true) {
		if (_kbhit()) {			// 用户按下键盘
			key = _getch();		// 不需要回车可直接读取缓冲区的键盘输入
			if (key == ' ') {
				canJump = false;
				jump();
				update = true;
			}
		}
	}
	else
		jump();
}



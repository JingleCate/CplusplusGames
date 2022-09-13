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
int degrees[30];					// hero上跳过程中的速度程度,符合实际物理规律
int dgIndex;						// degress数组索引
bool update;

IMAGE imgTortoise;					// 乌龟障碍物



// 函数声明
void init(int width, int height);
void updateBackgroud();
void bgSlide();
void heroRun(int heroIndex);
void keyCatch();
void tortoiseProduct();



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
			heroRun(hIndex);					// 英雄渲染
			tortoiseProduct();					// 乌龟障碍物渲染
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

	// 初始化degrees数组
	int length = sizeof(degrees) / 4;
	for (int i = 0; i < length; i++){
		if (i < length / 2)
			degrees[i] = length / 2 - i;
		else
			degrees[i] = length / 2 - i - 1;
	}

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
	sprintf_s(name, "res/t1.png");
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

	hDstY -= 1 * degrees[dgIndex];

	// 界定dgIndex范围防止溢出
	dgIndex++;
	if (dgIndex >= 30) {
		dgIndex %= 30;
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


void tortoiseProduct(){
	static int tDstY = 300;							// tortoise的y坐标
	static int tSpeed = 6;							// tortoise移动速率
	static int tDstX[2] = { WIDTH,WIDTH };			// 乌龟的x坐标, 允许两只
	static bool isShow[2] = { false,false };		// 另一个乌龟是否显示
	static int frameSum[2] = { 0,0 };				// 两只乌龟的出现时间
	static bool begin = true;
	static int sum = 0;
	sum++;
	/*putimagePNG2(tDstX, tDstY, &imgTortoise);
	frameSum++;
	tDstX -= tSpeed;
	if (tDstX < imgTortoise.getwidth()) {
		tDstX = WIDTH;
	}

	if (frameSum > 300 && (rand() % 10 >= 5)) {

	}*/
	

	// 随机出现两只乌龟且保证乌龟之间的一定距离
	//if (isShow[0] == false && isShow[1] == false) begin = true;
	int rd = rand() % 10;
	if ((sum >= 50 && isShow[0] != true && (rd >= 5)) || ((rd >= 5) && begin)) {
		isShow[0] = true;
		begin = false;
	}
		
	rd = rand() % 10;
	if ((sum >= 50 && isShow[1] != true && (rd >= 7) ) || ((rd >= 5) && begin)) {
		isShow[1] = true;
		begin = false;
	}
		
	if (sum >= 50) sum %= 50;

	// 到达边界后自动重新计数
	if (tDstX[0] <= -imgTortoise.getwidth()) {
		tDstX[0] = WIDTH;
		isShow[0] = false;
		frameSum[0] = 0;
	}

	if (tDstX[1] <= -imgTortoise.getwidth()) {
		tDstX[1] = WIDTH;
		isShow[1] = false;
		frameSum[1] = 0;
	}


	if (isShow[0] == true) {
		putimagePNG2(tDstX[0], tDstY, WIDTH, &imgTortoise);
		tDstX[0] -= tSpeed;
		frameSum[0]++;
	}
	if (isShow[1] == true) {
		putimagePNG2(tDstX[1], tDstY, WIDTH, &imgTortoise);
		tDstX[1] -= tSpeed;
		frameSum[1]++;
	}


	



}

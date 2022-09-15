/*****************************************************************//**
 * \file   base.h
 * \brief  CoolRun base class
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

#define WIDTH 1012
#define HEIGHT 396

// 背景
struct BackGround {
	IMAGE imgs[3];							// 背景图片
	int bgdstX[3];							// 背景图片x轴位置
	const int bgSpeed[3] = { 1, 2, 4 };		// 滑动速度
};

// 英雄
struct Hero {
	IMAGE heros[12];						// 英雄实现奔跑
	int hDstX;								// 英雄x坐标
	int hDstY;								// 英雄Y坐标
	bool canJump;							// 英雄是否可以跳跃
	int degrees[30];						// hero上跳过程中的速度程度,符合实际物理规律
	int dgIndex;							// degress数组索引
};

class CoolRun {
private:

	BackGround bg;
	Hero hr;
	bool update;

	IMAGE imgTortoise;					// 乌龟障碍物
	void jump();

	

public:
	CoolRun();							// 构造函数
	~CoolRun() {};						// 析构函数
	// 函数声明
	void updateBackgroud();
	void bgSlide();
	void heroRun(int heroIndex);
	void keyCatch();
	void tortoiseProduct();
	bool getUpdate() { return update; }
	void setUpdate(bool value) { update = value; }
	bool getCanJump();

};

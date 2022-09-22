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
#include <vector>
#include "tools.h"
#include <iostream>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")		// 连接到winmm库

#define WIDTH 1012
#define HEIGHT 396
#define OBSTACLE_COUNT 10
#define DOWNIMG 2
#define WIN_SCORE 3


// 障碍物类型:tortoise lion
typedef enum { 
	TORTOISE, 
	LION ,
	HOOK1,
	HOOK2,
	HOOK3,
	HOOK4,
	NOW_OBSTACLE_COUNT						// 障碍物总数
}obstacle_t;

// 背景
struct BackGround {
	IMAGE imgs[3];							// 背景图片
	int bgdstX[3];							// 背景图片x轴位置
	const int bgSpeed[3] = { 1, 2, 4 };		// 滑动速度
	BackGround();
};

// 英雄
struct Hero {
	IMAGE *heros;							// 英雄实现奔跑
	int hDstX;								// 英雄x坐标
	int hDstY;								// 英雄Y坐标
	bool canJump, canDown;					// 英雄是否可以跳跃、下蹲
	int degrees[30];						// hero上跳过程中的速度程度,符合实际物理规律
	int dgIndex;							// degress数组索引

	// 默认加载12张英雄奔跑图片,若是下蹲自行输入
	Hero(int count = 12);
};

// 障碍物
struct Obstacle {
	obstacle_t type;				// 障碍物类型
	int ox, oy;						// 障碍物坐标
	int index;						// 图片索引
	int speed;						// 移动速度
	bool exist;						// 当前界面是否存在
	int power;						// 杀伤力
	bool isHited;					// 是否已经碰撞
	bool passed;					// 是否已经通过
};

class CoolRun {
private:

	BackGround bg;									// 背景
	int heroBlood;									// 英雄血量
	Hero hr;										// 英雄图片
	Hero hrDown = Hero(2);							// 下蹲时英雄图片
	bool update;
	int lastObst;									// 上一次障碍物
	int score;										// 分数,上不封顶
	IMAGE number[10];								// 数字

	std::vector<std::vector<IMAGE>> oImgs;			// 障碍物图标
	Obstacle obst[OBSTACLE_COUNT];					// 障碍物数量
	//bool isCrashed[OBSTACLE_COUNT] = {false};
	void jump();

public:
	CoolRun();										// 构造函数
	~CoolRun() {};									// 析构函数
	// 函数声明
	//void initPage();								// 初始界面
	void updateBackgroud();
	void bgSlide();
	void heroRun(int heroIndex);
	void keyCatch();
	void obProduct();
	inline bool getUpdate() { return update; }
	inline void setUpdate(bool value) { update = value; }
	bool getCanJump();
	// 创建障碍物
	void createObstacle();							
	// 下蹲
	void down();									
	inline bool getCanDown() { return hrDown.canDown; }

	/**
	 * 检测hero与obstacle是否碰撞.
	 * <p>模糊碰撞</p>
	 * \param heroIndex
	 */
	void checkCrash(int heroIndex);					
	// 加载血条
	void upBloodBar();	
	/**
	 * 更新分数.
	 * 
	 * \param isCrashed 是否相撞
	 */
	void upScore();
	// 检查游戏是否结束
	bool checkOver();								
};

void init();			// 初始化界面

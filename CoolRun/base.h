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
#pragma comment(lib, "winmm.lib")		// ���ӵ�winmm��

#define WIDTH 1012
#define HEIGHT 396
#define OBSTACLE_COUNT 10
#define DOWNIMG 2


// �ϰ�������:tortoise lion
typedef enum { 
	TORTOISE, 
	LION ,
	HOOK1,
	HOOK2,
	HOOK3,
	HOOK4,
	NOW_OBSTACLE_COUNT						// �ϰ�������
}obstacle_t;

// ����
struct BackGround {
	IMAGE imgs[3];							// ����ͼƬ
	int bgdstX[3];							// ����ͼƬx��λ��
	const int bgSpeed[3] = { 1, 2, 4 };		// �����ٶ�
	BackGround();
};

// Ӣ��
struct Hero {
	IMAGE *heros;							// Ӣ��ʵ�ֱ���
	int hDstX;								// Ӣ��x����
	int hDstY;								// Ӣ��Y����
	bool canJump, canDown;					// Ӣ���Ƿ������Ծ���¶�
	int degrees[30];						// hero���������е��ٶȳ̶�,����ʵ���������
	int dgIndex;							// degress��������

	// Ĭ�ϼ���12��Ӣ�۱���ͼƬ,�����¶���������
	Hero(int count = 12);
};

// �ϰ���
struct Obstacle {
	obstacle_t type;				// �ϰ�������
	int ox, oy;						// �ϰ�������
	int index;						// ͼƬ����
	int speed;						// �ƶ��ٶ�
	bool exist;						// ��ǰ�����Ƿ����
	int power;						// ɱ����
	bool isHited;					// �Ƿ��Ѿ���ײ
};

class CoolRun {
private:

	BackGround bg;									// ����
	int heroBlood;									// Ӣ��Ѫ��
	Hero hr;										// Ӣ��ͼƬ
	Hero hrDown = Hero(2);							// �¶�ʱӢ��ͼƬ
	bool update;
	int lastObst;									// ��һ���ϰ���

	std::vector<std::vector<IMAGE>> oImgs;			// �ϰ���ͼ��
	Obstacle obst[OBSTACLE_COUNT];					// �ϰ�������
	void jump();

public:
	CoolRun();										// ���캯��
	~CoolRun() {};									// ��������
	// ��������
	//void initPage();								// ��ʼ����
	void updateBackgroud();
	void bgSlide();
	void heroRun(int heroIndex);
	void keyCatch();
	void obProduct();
	inline bool getUpdate() { return update; }
	inline void setUpdate(bool value) { update = value; }
	bool getCanJump();
	void createObstacle();							// �����ϰ���
	void down();									// �¶�
	inline bool getCanDown() { return hrDown.canDown; }
	void checkCrash(int heroIndex);					// �����ײ
	void upBloodBar();								// ����Ѫ��
	bool checkOver();								// �����Ϸ�Ƿ����
};

void init();			// ��ʼ������

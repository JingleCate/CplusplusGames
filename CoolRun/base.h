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
#pragma comment(lib, "winmm.lib")		// ���ӵ�winmm��

#define WIDTH 1012
#define HEIGHT 396

// ����
struct BackGround {
	IMAGE imgs[3];							// ����ͼƬ
	int bgdstX[3];							// ����ͼƬx��λ��
	const int bgSpeed[3] = { 1, 2, 4 };		// �����ٶ�
};

// Ӣ��
struct Hero {
	IMAGE heros[12];						// Ӣ��ʵ�ֱ���
	int hDstX;								// Ӣ��x����
	int hDstY;								// Ӣ��Y����
	bool canJump;							// Ӣ���Ƿ������Ծ
	int degrees[30];						// hero���������е��ٶȳ̶�,����ʵ���������
	int dgIndex;							// degress��������
};

class CoolRun {
private:

	BackGround bg;
	Hero hr;
	bool update;

	IMAGE imgTortoise;					// �ڹ��ϰ���
	void jump();

	

public:
	CoolRun();							// ���캯��
	~CoolRun() {};						// ��������
	// ��������
	void updateBackgroud();
	void bgSlide();
	void heroRun(int heroIndex);
	void keyCatch();
	void tortoiseProduct();
	bool getUpdate() { return update; }
	void setUpdate(bool value) { update = value; }
	bool getCanJump();

};

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
#pragma comment(lib, "winmm.lib")		// ���ӵ�winmm��
//import std.core; �ⲿ�ֵ���ʧ�ܳ����˰汾����
import obstacles;

#define WIDTH 1012
#define HEIGHT 396
IMAGE imgs[3];
int bgdstX[3];						// ����ͼƬλ��x��
int bgSpeed[3] = { 1, 2, 4 };		// �����ٶ�

IMAGE heros[12];					// Ӣ��ʵ�ֱ���
int hDstX;							// Ӣ��x����
int hDstY;							// Ӣ��Y����
bool canJump;						// Ӣ���Ƿ������Ծ
int degrees[10] = { 5,4,3,2,1,-1,-2,-3,-4,-5 };// hero���������е��ٶȳ̶�,����ʵ���������
int dgIndex;						// degress��������
bool update;

IMAGE imgTortoise;					// �ڹ��ϰ���


// ��������
void init(int width, int height);
void updateBackgroud();
void bgSlide();
void heroRun(int heroIndex);
void keyCatch();



int main(void) {
	init(WIDTH, HEIGHT);
	//ʵʱ��Ⱦ
	int hIndex = 0, timer = 0;				// ��ʱ��
	while (true) {							// ���̲���
		timer += getDelay();				// �滻sleepʵʱ���ܼ��̲���
		if (timer > 30 || update) {
			timer = 0; 
			update = false;
			keyCatch();
			BeginBatchDraw();					// �����ӡ
			updateBackgroud();					// ������Ⱦ
			heroRun(hIndex);			// Ӣ����Ⱦ
			EndBatchDraw();						// ����
			bgSlide();
			if (canJump == true)				// hero��Ծ�����в�����
				hIndex = (hIndex + 1) % 12;
		}

		
	}

	return 0;

}


// ����ʵ��

/**
 * create game window
 * @param width width width of window
 * @param height height of window
 */
void init(int width = 1012, int height = 396) {
	initgraph(width, height);


	// ���ر���ͼƬ
	char name[64];
	for (int i = 0; i < 3; i++) {
		// ·���浽name������
		sprintf_s(name, "res/bg%03d.png", i + 1);// sprintf�����ļ���
		loadimage(&imgs[i], name);// ��������ַ���(��Ŀ)
		bgdstX[i] = 0;
	}

	// ����Ӣ��ͼƬ
	for (int i = 0; i < 12; i++) {
		sprintf_s(name, "res/hero%d.png", i + 1);
		loadimage(&heros[i], name);
	}

	// ��ʼ��hero����
	hDstX = int(WIDTH * 0.5 - heros[0].getheight() * 0.5);
	hDstY = 345 - heros[0].getheight();

	canJump = true;				// Ĭ�ϳ�ʼ�����¿�������
	dgIndex = 0;
	update = false;

	// �����ڹ�ͼƬ
	sprintf_s(name, "res/t%d.png", 1);
	loadimage(&imgTortoise, name);
	
}

// ͼƬ����Ч��
void bgSlide() {
	for (int i = 0; i < 3; i++) {
		bgdstX[i] -= bgSpeed[i];
		if (bgdstX[i] < -WIDTH)
			bgdstX[i] = 0;

	}
}

void updateBackgroud() {
	// ����ͼƬ��y���Ϸֲ�ƽ��
	// putimage�д�͸Ч��, putimagePNG��֧�ָ�����, �����ӡͼƬ
	putimagePNG2(bgdstX[0], 0, &imgs[0]);
	putimagePNG2(bgdstX[1], 119, &imgs[1]);
	putimagePNG2(bgdstX[2], 330, &imgs[2]);
}

void heroRun(int heroIndex) {
	// ��ȾӢ��ģ��
	putimagePNG2(hDstX, hDstY, &heros[heroIndex]);
}

void jump() {

	hDstY -= 8 * degrees[dgIndex];

	// �綨dgIndex��Χ��ֹ���
	dgIndex++;
	if (dgIndex >= 10) {
		dgIndex %= 10;
		canJump = true;
	}
}

/**
 * ������������Կ���hero����.
 */
void keyCatch() {
	char key;
	//if(update==)
	// ���������Ծ�򲶻������Ϊ����ֱ�����δ��������Ծ
	if (canJump == true) {
		if (_kbhit()) {			// �û����¼���
			key = _getch();		// ����Ҫ�س���ֱ�Ӷ�ȡ�������ļ�������
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



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
//#pragma comment(lib, "winmm.lib")		// ���ӵ�winmm��
////import std.core; �ⲿ�ֵ���ʧ�ܳ����˰汾����
//import obstacles;
//
//#define WIDTH 1012
//#define HEIGHT 396
//IMAGE imgs[3];
//int bgdstX[3];						// ����ͼƬλ��x��
//int bgSpeed[3] = { 1, 2, 4 };		// �����ٶ�
//
//IMAGE heros[12];					// Ӣ��ʵ�ֱ���
//int hDstX;							// Ӣ��x����
//int hDstY;							// Ӣ��Y����
//bool canJump;						// Ӣ���Ƿ������Ծ
//int degrees[30];					// hero���������е��ٶȳ̶�,����ʵ���������
//int dgIndex;						// degress��������
//bool update;
//
//IMAGE imgTortoise;					// �ڹ��ϰ���
//
//
//
//// ��������
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
	//ʵʱ��Ⱦ
	int hIndex = 0, timer = 0;					// ��ʱ��
	while (true) {								// ���̲���
		timer += getDelay();					// �滻sleepʵʱ���ܼ��̲���
		if (timer > 30 || master.getUpdate()) {
			timer = 0; 
			master.setUpdate(false);
			master.keyCatch();
			BeginBatchDraw();					// �����ӡ
			master.updateBackgroud();			// ������Ⱦ
			master.heroRun(hIndex);				// Ӣ����Ⱦ
			master.tortoiseProduct();			// �ڹ��ϰ�����Ⱦ
			EndBatchDraw();						// ����
			master.bgSlide();
			if (master.getCanJump() == true)				// hero��Ծ�����в�����
				hIndex = (hIndex + 1) % 12;
		}

		
	}

	return 0;

}
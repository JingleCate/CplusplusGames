/*****************************************************************//**
 * \file   main.cpp
 * \brief  Setup CoolRun Window, main function
 *
 * \author jinnian
 * \date   September 2022
 *********************************************************************/

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
			if (master.getCanJump() == true)	// hero��Ծ�����в�����
				hIndex = (hIndex + 1) % 12;
		}

		
	}

	return 0;

}
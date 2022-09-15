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
			if (master.getCanJump() == true)	// hero跳跃过程中不奔跑
				hIndex = (hIndex + 1) % 12;
		}

		
	}

	return 0;

}
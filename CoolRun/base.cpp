#include "base.h"

// CoolRun类成员函数实现

/**
 * create game window
 * @param width width width of window
 * @param height height of window
 */
CoolRun::CoolRun() {
	initgraph(WIDTH, HEIGHT);

	// 初始化degrees数组
	int length = sizeof(hr.degrees) / 4;
	for (int i = 0; i < length; i++) {
		if (i < length / 2)
			hr.degrees[i] = length / 2 - i;
		else
			hr.degrees[i] = length / 2 - i - 1;
	}

	// 加载背景图片
	char name[64];
	for (int i = 0; i < 3; i++) {
		// 路径存到name缓冲区
		sprintf_s(name, "res/bg%03d.png", i + 1);// sprintf生成文件名
		loadimage(&bg.imgs[i], name);// 这里调节字符集(项目)
		bg.bgdstX[i] = 0;
	}

	// 加载英雄图片
	for (int i = 0; i < 12; i++) {
		sprintf_s(name, "res/hero%d.png", i + 1);
		loadimage(&hr.heros[i], name);
	}

	// 初始化hero坐标
	hr.hDstX = int(WIDTH * 0.5 - hr.heros[0].getheight() * 0.5);
	hr.hDstY = 345 - hr.heros[0].getheight();

	hr.canJump = true;				// 默认初始条件下可以起跳
	hr.dgIndex = 0;
	update = false;

	// 加载乌龟图片
	sprintf_s(name, "res/t1.png");
	loadimage(&imgTortoise, name);

}

// 图片滑动效果
void CoolRun::bgSlide() {
	for (int i = 0; i < 3; i++) {
		bg.bgdstX[i] -= bg.bgSpeed[i];
		if (bg.bgdstX[i] < -WIDTH)
			bg.bgdstX[i] = 0;

	}
}


void CoolRun::updateBackgroud() {
	// 三个图片在y轴上分层平铺
	// putimage有穿透效果, putimagePNG不支持负坐标, 缓冲打印图片
	putimagePNG2(bg.bgdstX[0], 0, &bg.imgs[0]);
	putimagePNG2(bg.bgdstX[1], 119, &bg.imgs[1]);
	putimagePNG2(bg.bgdstX[2], 330, &bg.imgs[2]);
}

void CoolRun::heroRun(int heroIndex) {
	// 渲染英雄模型
	putimagePNG2(hr.hDstX, hr.hDstY, &hr.heros[heroIndex]);
}

void CoolRun::jump() {

	hr.hDstY -= 1 * hr.degrees[hr.dgIndex];

	// 界定dgIndex范围防止溢出
	hr.dgIndex++;
	if (hr.dgIndex >= 30) {
		hr.dgIndex %= 30;
		hr.canJump = true;
	}
}

/**
 * 处理键盘输入以控制hero动作.
 */
void CoolRun::keyCatch() {
	char key;
	//if(update==)
	// 如果允许跳跃则捕获键盘行为否则直接完成未结束的跳跃
	if (hr.canJump == true) {
		if (_kbhit()) {			// 用户按下键盘
			key = _getch();		// 不需要回车可直接读取缓冲区的键盘输入
			if (key == ' ') {
				hr.canJump = false;
				jump();
				update = true;
			}
		}
	}
	else
		jump();
}


void CoolRun::tortoiseProduct() {
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
	if ((sum >= 50 && isShow[1] != true && (rd >= 7)) || ((rd >= 5) && begin)) {
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

bool CoolRun::getCanJump(){
	return hr.canJump;
}

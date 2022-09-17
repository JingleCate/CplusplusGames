#include "base.h"
Hero::Hero(int count) {
	heros = new IMAGE[count];
	if (count == 2) {
		// 加载英雄下蹲时的图片
		loadimage(&heros[0], "res/d1.png");
		loadimage(&heros[1], "res/d2.png");
		hDstX = int(WIDTH * 0.5 - heros[0].getheight() * 0.5);
		hDstY = 370 - heros[0].getheight();
	}
	else if (count == 12) {
		// 加载英雄图片
		char name[64];
		for (int i = 0; i < 12; i++) {
			sprintf_s(name, "res/hero%d.png", i + 1);
			loadimage(&heros[i], name);
		}
		hDstX = int(WIDTH * 0.5 - heros[0].getheight() * 0.5);
		hDstY = 345 - heros[0].getheight();
	}
	// 初始化hero坐标
	canDown = true;				// 默认初始条件下可以下蹲
	canJump = true;				// 默认初始条件下可以起跳
	dgIndex = 0;



	// 初始化degrees数组
	int length = sizeof(degrees) / 4;
	for (int i = 0; i < length; i++) {
		if (i < length / 2)
			degrees[i] = length / 2 - i;
		else
			degrees[i] = length / 2 - i - 1;
	}
}

BackGround::BackGround() {
	// 加载背景图片
	char name[64];
	for (int i = 0; i < 3; i++) {
		// 路径存到name缓冲区
		sprintf_s(name, "res/bg%03d.png", i + 1);// sprintf生成文件名
		loadimage(&imgs[i], name);// 这里调节字符集(项目)
		bgdstX[i] = 0;
	}
}

// CoolRun类成员函数实现

/**
 * create game window
 * @param width width width of window
 * @param height height of window
 */
CoolRun::CoolRun() {
	initgraph(WIDTH, HEIGHT);

	char name[64];
	update = false;

	// 加载乌龟障碍物
	std::vector<IMAGE> oTemp;
	for (int i = 0; i < 7; i++){
		IMAGE imgOb;
		sprintf_s(name, "res/t%d.png", i + 1);
		loadimage(&imgOb, name);
		oTemp.push_back(imgOb);
	}
	oImgs.push_back(oTemp);
	

	// 加载狮子障碍物
	oTemp.clear();
	for (int i = 0; i < 6; i++){
		IMAGE imgL;							// 魔鬼这地方真的是,loadimage工具函数没有写好,用一个变量多个传参图片直接被截断了
		sprintf_s(name, "res/p%d.png", i + 1);
		loadimage(&imgL, name);
		oTemp.push_back(imgL);
	}
	oImgs.push_back(oTemp);

		
	// 加载柱子障碍物
	oTemp.clear();
	for (int i = 0; i < 4; i++) {
		IMAGE imgH;							
		sprintf_s(name, "res/h%d.png", i + 1);
		loadimage(&imgH, name, 63, 260, true);
		oTemp.push_back(imgH);
		oImgs.push_back(oTemp);
		oTemp.clear();
	}
	
	// 初始均不存在 
	for (int i = 0; i < OBSTACLE_COUNT; i++) {
		obst[i].exist = false;
		obst[i].index = 0;
		obst[i].ox = WIDTH;
		////if (i < OBSTACLE_COUNT)
		//	obst[i].type = TORTOISE;
		//else
		//	obst[i].type = LION;
	}

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
	if (hrDown.canDown == false) {
		putimagePNG2(hrDown.hDstX, hrDown.hDstY, &hrDown.heros[hrDown.dgIndex]);
		return;
	}
	
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

	//正在下蹲
	if (hrDown.canDown == false) {
		down();
		return;
	}
	//if(update==)
	// 如果允许跳跃则捕获键盘行为否则直接完成未结束的跳跃
	if (hr.canJump == true) {
		if (_kbhit()) {			// 用户按下键盘
			key = _getch();		// 不需要回车可直接读取缓冲区的键盘输入
			if (key == ' ') {							// 起跳
				hr.canJump = false;
				jump();
				update = true;
			}
			else if (key == 'Z' || key == 'z') {		// 下蹲
				hrDown.canDown = false;
				down();
				update = true;
			}
		}
	}
	else
		jump();
}


void CoolRun::obProduct() {
	//static int tDstY = 300;							// tortoise的y坐标
	//static int tSpeed = 6;							// tortoise移动速率
	//static int tDstX[2] = { WIDTH,WIDTH };			// 乌龟的x坐标, 允许两只
	//static bool isShow[2] = { false,false };		// 另一个乌龟是否显示
	//static int frameSum[2] = { 0,0 };				// 两只乌龟的出现时间
	//static bool begin = true;
	//static int sum = 0;
	//sum++;
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
	//int rd = rand() % 10;
	//if ((sum >= 50 && isShow[0] != true && (rd >= 5)) || ((rd >= 5) && begin)) {
	//	isShow[0] = true;
	//	begin = false;
	//}

	//rd = rand() % 10;
	//if ((sum >= 50 && isShow[1] != true && (rd >= 7)) || ((rd >= 5) && begin)) {
	//	isShow[1] = true;
	//	begin = false;
	//}

	//if (sum >= 50) sum %= 50;

	//// 到达边界后自动重新计数
	//if (tDstX[0] <= -imgTortoise.getwidth()) {
	//	tDstX[0] = WIDTH;
	//	isShow[0] = false;
	//	frameSum[0] = 0;
	//}

	//if (tDstX[1] <= -imgTortoise.getwidth()) {
	//	tDstX[1] = WIDTH;
	//	isShow[1] = false;
	//	frameSum[1] = 0;
	//}


	//if (isShow[0] == true) {
	//	putimagePNG2(tDstX[0], tDstY, WIDTH, &imgTortoise);
	//	tDstX[0] -= tSpeed;
	//	frameSum[0]++;
	//}
	//if (isShow[1] == true) {
	//	putimagePNG2(tDstX[1], tDstY, WIDTH, &imgTortoise);
	//	tDstX[1] -= tSpeed;
	//	frameSum[1]++;
	//}

	static int frameCount = 0;
	static int Sum = 60;
	frameCount++;
	if (frameCount > Sum) {
		frameCount = 0;
		Sum = 60 + rand() % 60;
		createObstacle();
	}

	for (int i = 0; i < OBSTACLE_COUNT; i++){
		if (obst[i].exist) {
			putimagePNG2(obst[i].ox, obst[i].oy, WIDTH, &oImgs[obst[i].type][obst[i].index]);
			if (obst[i].ox < -oImgs[obst[i].type][obst[i].index].getwidth()) {
				obst[i].exist = false;
			}

			int len = int(oImgs[obst[i].type].size());
			obst[i].index = (obst[i].index + 1) % len;
			obst[i].ox -= obst[i].speed;
		}
	}
}

bool CoolRun::getCanJump(){
	return hr.canJump;
}


void CoolRun::createObstacle(){
	int i = 0;
	for (i = 0; i < OBSTACLE_COUNT; i++){
		if (obst[i].exist == false)
			break;
	}
	if (i >= OBSTACLE_COUNT)
		return;
	//if (update = true)
		//i = 0;
	obst[i].exist = true;
	obst[i].index = 0;
	obst[i].type = obstacle_t(rand() % NOW_OBSTACLE_COUNT);
	obst[i].ox = WIDTH;
	//obst[i].oy = 320 - oImgs[obst[i].type][0].getheight();

	if (obst[i].type == TORTOISE) {
		obst[i].speed = 8;
		obst[i].oy = 310;
	}
	else if (obst[i].type == LION) {
		obst[i].speed = 8;
		obst[i].oy = 260;
	}
	else {
		obst[i].speed = 4;
		obst[i].oy = 0;
	}

}

void CoolRun::down(){
	static bool begin = true;
	// 初始直接退出
	if (begin == true) {
		begin = false;
		return;
	}
	static int frames[2] = { 0,0 };
	// 这里复用了deIndex变量
	if (hrDown.dgIndex == 0) {
		frames[0]++;
		if (frames[0] >= 5) {
			frames[0] = 0;
			hrDown.dgIndex++;
		}
		
	}
		
	else if (hrDown.dgIndex == 1) {
		frames[1]++;
		if (frames[1] >= 10) {
			hrDown.canDown = true;
			frames[1] = 0;
			hrDown.dgIndex = 0;
		}
	}
}

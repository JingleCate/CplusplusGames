#include "base.h"

// CoolRun���Ա����ʵ��

/**
 * create game window
 * @param width width width of window
 * @param height height of window
 */
CoolRun::CoolRun() {
	initgraph(WIDTH, HEIGHT);

	// ��ʼ��degrees����
	int length = sizeof(hr.degrees) / 4;
	for (int i = 0; i < length; i++) {
		if (i < length / 2)
			hr.degrees[i] = length / 2 - i;
		else
			hr.degrees[i] = length / 2 - i - 1;
	}

	// ���ر���ͼƬ
	char name[64];
	for (int i = 0; i < 3; i++) {
		// ·���浽name������
		sprintf_s(name, "res/bg%03d.png", i + 1);// sprintf�����ļ���
		loadimage(&bg.imgs[i], name);// ��������ַ���(��Ŀ)
		bg.bgdstX[i] = 0;
	}

	// ����Ӣ��ͼƬ
	for (int i = 0; i < 12; i++) {
		sprintf_s(name, "res/hero%d.png", i + 1);
		loadimage(&hr.heros[i], name);
	}

	// ��ʼ��hero����
	hr.hDstX = int(WIDTH * 0.5 - hr.heros[0].getheight() * 0.5);
	hr.hDstY = 345 - hr.heros[0].getheight();

	hr.canJump = true;				// Ĭ�ϳ�ʼ�����¿�������
	hr.dgIndex = 0;
	update = false;

	// �����ڹ�ͼƬ
	sprintf_s(name, "res/t1.png");
	loadimage(&imgTortoise, name);

}

// ͼƬ����Ч��
void CoolRun::bgSlide() {
	for (int i = 0; i < 3; i++) {
		bg.bgdstX[i] -= bg.bgSpeed[i];
		if (bg.bgdstX[i] < -WIDTH)
			bg.bgdstX[i] = 0;

	}
}


void CoolRun::updateBackgroud() {
	// ����ͼƬ��y���Ϸֲ�ƽ��
	// putimage�д�͸Ч��, putimagePNG��֧�ָ�����, �����ӡͼƬ
	putimagePNG2(bg.bgdstX[0], 0, &bg.imgs[0]);
	putimagePNG2(bg.bgdstX[1], 119, &bg.imgs[1]);
	putimagePNG2(bg.bgdstX[2], 330, &bg.imgs[2]);
}

void CoolRun::heroRun(int heroIndex) {
	// ��ȾӢ��ģ��
	putimagePNG2(hr.hDstX, hr.hDstY, &hr.heros[heroIndex]);
}

void CoolRun::jump() {

	hr.hDstY -= 1 * hr.degrees[hr.dgIndex];

	// �綨dgIndex��Χ��ֹ���
	hr.dgIndex++;
	if (hr.dgIndex >= 30) {
		hr.dgIndex %= 30;
		hr.canJump = true;
	}
}

/**
 * ������������Կ���hero����.
 */
void CoolRun::keyCatch() {
	char key;
	//if(update==)
	// ���������Ծ�򲶻������Ϊ����ֱ�����δ��������Ծ
	if (hr.canJump == true) {
		if (_kbhit()) {			// �û����¼���
			key = _getch();		// ����Ҫ�س���ֱ�Ӷ�ȡ�������ļ�������
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
	static int tDstY = 300;							// tortoise��y����
	static int tSpeed = 6;							// tortoise�ƶ�����
	static int tDstX[2] = { WIDTH,WIDTH };			// �ڹ��x����, ������ֻ
	static bool isShow[2] = { false,false };		// ��һ���ڹ��Ƿ���ʾ
	static int frameSum[2] = { 0,0 };				// ��ֻ�ڹ�ĳ���ʱ��
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


	// ���������ֻ�ڹ��ұ�֤�ڹ�֮���һ������
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

	// ����߽���Զ����¼���
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

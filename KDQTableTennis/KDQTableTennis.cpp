#include "KDQTableTennis.h"

KDQTableTennis::KDQTableTennis() {
	initTexture();
	initTable();
	initBalls();
	initCue();
	initFlag();
}

KDQTableTennis::~KDQTableTennis() {
	delete table;
	delete[] balls;
	delete cue;
	delete[] texture;
}

void KDQTableTennis::initTable() {
	table = new Table();
}

void KDQTableTennis::initBalls() {
	balls = new Ball[N_BALL];
	for (int i = 0; i < N_BALL; ++i) {
		balls[i].radius = BALL_RADIUS;
		balls[i].leftBound = table->getLeft();
		balls[i].rightBound = table->getRight();
		balls[i].bottomBound = table->getBottom();
		balls[i].topBound = table->getTop();
	}
	//cue ball
	balls[CUE_BALL].xPos = 50.0;
	balls[CUE_BALL].yPos = 50.0;
	balls[CUE_BALL].zPos = BALL_RADIUS;
	balls[CUE_BALL].colorR = 1.0;
	balls[CUE_BALL].colorG = 1.0;
	balls[CUE_BALL].colorB = 1.0;
	balls[CUE_BALL].xSpeed = 0.0;
	balls[CUE_BALL].ySpeed = 0.0;
	balls[CUE_BALL].zSpeed = 0.0;
	balls[CUE_BALL].miu = 0.03;
	balls[CUE_BALL].texName = 0;

	//golden ball
	/*balls[GOLDEN_BALL].xPos = 150.0;
	balls[GOLDEN_BALL].yPos = 50.0;
	balls[GOLDEN_BALL].zPos = BALL_RADIUS;
	balls[GOLDEN_BALL].colorR = 1.0;
	balls[GOLDEN_BALL].colorG = 0.7;
	balls[GOLDEN_BALL].colorB = 0.4;
	balls[GOLDEN_BALL].xSpeed = 0.0;
	balls[GOLDEN_BALL].ySpeed = 0.0;
	balls[GOLDEN_BALL].zSpeed = 0.0;
	balls[GOLDEN_BALL].miu = 0.0;
	*/
	//ghost balls
	/*for (int i = GHOST_BALL; i < GHOST_BALL+N_GHOST_BALL; ++i) {
		balls[i].xPos = i * 22;
		balls[i].yPos = 150;
		balls[i].zPos = BALL_RADIUS;
		balls[i].colorR = 0.7;
		balls[i].colorG = 1.0;
		balls[i].colorB = 0.6;
		balls[i].xSpeed = 0.0;
		balls[i].ySpeed = 0.0;
		balls[i].zSpeed = 0.0;
		balls[i].miu = 0.02;
	}*/

	//walking balls
	for (int i = WALKING_BALL; i < WALKING_BALL + N_WALKING_BALL; ++i) {
		balls[i].xPos = (i-WALKING_BALL+2) * 22;
		balls[i].yPos = (i % 2) ? 80 : 120;
		balls[i].zPos = BALL_RADIUS;
		balls[i].colorR = 1.0;
		balls[i].colorG = 1.0;
		balls[i].colorB = 1.0;
		balls[i].xSpeed = 3.0-i%2;
		balls[i].ySpeed = 1.0+i%2;
		balls[i].zSpeed = 0.0;
		balls[i].miu = 0.0;
		balls[i].texName = texture[2];
	}
}

void KDQTableTennis::initCue() {
	cue = new Cue();
	cue->gap = 5 + balls[CUE_BALL].radius;
	cue->angle = 270;
}

void KDQTableTennis::initFlag() {
	flag_1 = new Flag();
	flag_2 = new Flag();
	flag_1->init(texture[0], 20, 8, 4);
	flag_2->init(texture[1], 20, 8, 4);
}

void KDQTableTennis::initTexture() {
	texture = new GLuint[3];
	//flag1
	AUX_RGBImageRec *texImage = auxDIBImageLoad(TEXTURE_FILE_1);
	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texImage->sizeX, texImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texImage->data);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//flag2
	texImage = auxDIBImageLoad(TEXTURE_FILE_2);
	glGenTextures(1, &texture[1]);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texImage->sizeX, texImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texImage->data);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//ball texture by perlin noise
	const int perlinTextureNum = 256;
	unsigned char perlinTextureArray[perlinTextureNum][perlinTextureNum][3];

	//set random seed once
	Perlin::setPerlin();
	for (int i = 0; i < perlinTextureNum; ++i) {
		for (int j = 0; j < perlinTextureNum; ++j) {
			perlinTextureArray[i][j][0] = Perlin::getPerlin(i, j, perlinTextureNum);
			perlinTextureArray[i][j][1] = 0.2 * perlinTextureArray[i][j][0];
			perlinTextureArray[i][j][2] = 0.0;
		}
	}

	glGenTextures(1, &texture[2]);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, perlinTextureNum, perlinTextureNum, 0, GL_RGB, GL_UNSIGNED_BYTE, perlinTextureArray);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

void KDQTableTennis::process() {
	static int timer = 0;
	timer++;
	if (timer > 60) timer = 0;

	//both the max bound of i and j are N_BALL-1
	for (int i = 0; i < N_BALL-1; ++i)
		for (int j = i + 1; j < N_BALL; ++j) {
			if (balls[i].hitTest(balls[j])) {
				//particle effect
				Particles particle(double(balls[i].xPos + balls[j].xPos) / 2, double(balls[i].yPos + balls[j].yPos) / 2, double(balls[i].zPos + balls[j].zPos) / 2);
				particles.push_back(particle);
			}
		}

	//golden ball process
	//z position
	if (timer == 0 || timer == 30) {
		if (balls[GOLDEN_BALL].zPos > BALL_RADIUS + 50)
			balls[GOLDEN_BALL].zSpeed = 3.0 * (rand() % 2 - 1);
		else balls[GOLDEN_BALL].zSpeed = 3.0 * (rand() % 3 - 1);
	}
	if (balls[GOLDEN_BALL].zPos + balls[GOLDEN_BALL].zSpeed < BALL_RADIUS) {
		balls[GOLDEN_BALL].zSpeed = 0;
		balls[GOLDEN_BALL].zPos = BALL_RADIUS;
	}
	//x,y speed
	if (timer == 15 || timer == 45) {
		balls[GOLDEN_BALL].xSpeed = rand() % 6 - 3.0;
		balls[GOLDEN_BALL].ySpeed = rand() % 6 - 3.0;
	}

	//balls moving
	for (int i = 0; i < N_BALL; ++i) {
		balls[i].testBound();
		balls[i].move();
		balls[i].setZPos(table->getHeight(balls[i].getXPos(), balls[i].getYPos()) + BALL_RADIUS);
	}	
	flag_1->move();
	flag_2->move();
	for (std::list<Particles>::iterator iter = particles.begin(); iter != particles.end(); ++iter) {
		if (!iter->move()) {
			//not alive
			particles.erase(iter);
			break;
		}
	}
}

void KDQTableTennis::display() {
	table->display();
	for (int i = 0; i < N_BALL; ++i)
		balls[i].display();
	if (balls[CUE_BALL].xSpeed == 0 && balls[CUE_BALL].ySpeed == 0) {
		cue->display(balls[CUE_BALL].xPos, balls[CUE_BALL].yPos, balls[CUE_BALL].radius);
	}
	flag_1->display(table->getLeft(), table->getTop(), MAX_HEIGHT + 20, 0, 1, 0, 0);
	flag_2->display(table->getRight(), table->getTop(), MAX_HEIGHT + 20, 0, 1, 0, 0);
	for (std::list<Particles>::iterator iter = particles.begin(); iter != particles.end(); ++iter) {
		iter->display();
	}
}

void KDQTableTennis::changeCueAngle(double a) {
	if (balls[CUE_BALL].xSpeed == 0 && balls[CUE_BALL].ySpeed == 0)
		cue->angle += a;
}

void KDQTableTennis::hitCueBall() {
	if (balls[CUE_BALL].xSpeed == 0 && balls[CUE_BALL].ySpeed == 0) {
		balls[CUE_BALL].xSpeed = -cos(PI * cue->angle / 180) * HITTING_SPEED;
		balls[CUE_BALL].ySpeed = -sin(PI * cue->angle / 180) * HITTING_SPEED;
	}
}
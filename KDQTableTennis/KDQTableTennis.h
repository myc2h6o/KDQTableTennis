#ifndef KDQ_TABLE_TENNIS_H
#define KDQ_TABLE_TENNIS_H
#include <stdlib.h>
#include <list>
#include "Camera.h"
#include "Table.h"
#include "Ball.h"
#include "Cue.h"
#include "Flag.h"
#include "Particle.h"
#include "KDQMath.h"
#include <string>
#include <gl/GLAUX.H>

const double BALL_RADIUS = 8.0;
const double HITTING_SPEED = 5.0;
//number of various balls
const int N_BALL = 7;
const int N_GHOST_BALL = 6;
const int N_WALKING_BALL = 6;
//position in balls[] of vauious balls
const int CUE_BALL = 0;
const int GOLDEN_BALL = 13;
const int GHOST_BALL = 7;
const int WALKING_BALL = 1;


#define TEXTURE_FILE_1 "resources/flag_1.bmp"
#define TEXTURE_FILE_2 "resources/flag_2.bmp"

class KDQTableTennis {
	friend class GUI;
public:
	KDQTableTennis();
	~KDQTableTennis();
	void process();
	void display();
	void changeCueAngle(double a);
	void hitCueBall();
private:
	Table *table;
	Ball *balls;
	Cue *cue;
	Flag *flag_1;
	Flag *flag_2;
	std::list<Particles> particles;
	GLuint *texture;
	void initTable();
	void initBalls();
	void initCue();
	void initFlag();
	void initTexture();
	KDQTableTennis(const KDQTableTennis&) {}
};

#endif

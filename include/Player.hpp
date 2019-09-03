#pragma once
#include "Base.hpp"
#include "SnowBall.hpp"

class Player {
    const unsigned int id; //プレーヤーID

    GLfloat position[3]; //プレーヤーの位置(x,y,z)

    //位置→視線の先のベクトル
    //絶対値が10になるようにしておく
    GLfloat direction[3];

    int snowballs; //持ち雪玉の数

    int life; //ライフ

    int hitPoint; // HP(MAXは100)

	//最後にボールを投げた時間
	//連投を制限する
	double lastThrough;

public:
	Player(GLint id, const GLfloat positionX, const GLfloat positionY, const GLfloat positionZ,
		const GLfloat directionX, const GLfloat directionY, const GLfloat directionZ, int snowballs, int life);

	void damage(int damage);

	void death();

	void gameOver();

	GLfloat* getPosition();

	GLfloat* getDirection();

	void move(GLfloat x, GLfloat y, GLfloat z);

	void rotate(GLfloat x, GLfloat y);

	SnowBall* throwBall(GLfloat speed, GLfloat lifespan, GLfloat directionX = 100.0f, GLfloat directionY = 100.0f, GLfloat directionZ = 100.0f);
};
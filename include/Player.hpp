#pragma once
#include "Base.hpp"
#include "SnowBall.hpp"

class Player {
    const unsigned int id; //�v���[���[ID

    GLfloat position[3]; //�v���[���[�̈ʒu(x,y,z)

    //�ʒu�������̐�̃x�N�g��
    //��Βl��10�ɂȂ�悤�ɂ��Ă���
    GLfloat direction[3];

    int snowballs; //������ʂ̐�

    int life; //���C�t

    int hitPoint; // HP(MAX��100)

	//�Ō�Ƀ{�[���𓊂�������
	//�A���𐧌�����
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
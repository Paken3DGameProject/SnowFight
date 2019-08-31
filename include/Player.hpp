#pragma once

#include "Base.hpp"
#include "SnowBall.hpp"

class Player {
    const unsigned int id; //プレーヤーID

    GLfloat position[3]; //プレーヤーの位置(x,y,z)

    //位置→視線の先のベクトル
    //絶対値が1になるようにしておく
    GLfloat direction[3];

    int snowballs; //持ち雪玉の数

    int life; //ライフ

    int hitPoint; // HP(MAXは100)

public:
    Player(GLint id, const GLfloat positionX, const GLfloat positionY, const GLfloat positionZ,
           const GLfloat directionX, const GLfloat directionY, const GLfloat directionZ, int snowballs, int life) : id(
            id), snowballs(snowballs), life(life) {
        position[0] = positionX;
        position[1] = positionY;
        position[2] = positionZ;
        direction[0] = directionX;
        direction[1] = directionY;
        direction[2] = directionZ;
        hitPoint = 100;
    }

    Player &operator=(const Player &);

    void damage(int damage) {
        if (hitPoint < damage)
            death();
        else
            hitPoint -= damage;
    }

    void death() {
        life--;
        if (life == 0)
            gameOver();
        else
            hitPoint = 100;
    }

    void gameOver() {
        this->~Player();
    }

    GLfloat *getPosition() {
        return position;
    }

    GLfloat *getDirection() {
        return direction;
    }

    void move(GLfloat x, GLfloat y, GLfloat z) {
        position[0] += x;
        position[1] += y;
        position[2] += z;
        position[0] = std::max(static_cast<GLfloat>(-29.5f), position[0]);
        position[0] = std::min(static_cast<GLfloat>(29.5f), position[0]);
        position[2] = std::max(static_cast<GLfloat>(-29.5f), position[2]);
        position[2] = std::min(static_cast<GLfloat>(29.5f), position[2]);
    }

    void rotate(GLfloat x, GLfloat y) {
        direction[0] = -sin(x);
		direction[1] = sin(y);
        direction[2] = -cos(x);

        GLfloat mag = 10.0f / hypot(hypot(direction[0], direction[1]),direction[2]);
        direction[0] *= mag;
		direction[1] *= mag;
        direction[2] *= mag;
    }

    SnowBall throwBall(GLfloat speed, GLfloat lifespan) {
		return SnowBall(position[0], position[1] + 1.0f, position[2], direction[0], direction[1], direction[2], speed, id, lifespan);
    }

    SnowBall throwBall(GLfloat directionX, GLfloat directionY, GLfloat directionZ, GLfloat speed, GLfloat lifespan) {
		return SnowBall(position[0], position[1] + 1.0f, position[2], directionX, directionY, directionZ, speed, id, lifespan);
	}
};
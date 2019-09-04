#pragma once
#include "Player.hpp"

Player::Player(GLint id, const GLfloat positionX, const GLfloat positionY, const GLfloat positionZ, const GLfloat directionX, const GLfloat directionY, const GLfloat directionZ, int snowballs, int life) :
    id(id), snowballs(snowballs), life(life), lastThrough(glfwGetTime() - 1.0) {
	position[0] = positionX;
	position[1] = positionY;
	position[2] = positionZ;
	direction[0] = directionX;
	direction[1] = directionY;
	direction[2] = directionZ;

	GLfloat mag = 10.0f / hypot(hypot(direction[0], direction[1]), direction[2]);
	direction[0] *= mag;
	direction[1] *= mag;
	direction[2] *= mag;

	ySpeed = 0.0f;
	hitPoint = 100;
}

void Player::damage(int damage) {
	if (hitPoint < damage)
		death();
	else
		hitPoint -= damage;
}

void Player::death() {
	life--;
	if (life == 0)
		gameOver();
	else
		hitPoint = 100;
}

void Player::gameOver() {
	this->~Player();
}

GLfloat* Player::getPosition() {
	return position;
}

GLfloat* Player::getDirection() {
	return direction;
}

void Player::move(GLfloat x, GLfloat y, GLfloat z) {
	position[0] += x;
	position[1] += y + ySpeed;
	position[2] += z;

	position[0] = std::max(static_cast<GLfloat>(-31.5f), position[0]);
	position[0] = std::min(static_cast<GLfloat>(31.5f), position[0]);
	position[2] = std::max(static_cast<GLfloat>(-31.5f), position[2]);
	position[2] = std::min(static_cast<GLfloat>(31.5f), position[2]);
	if (position[1] <= 0.0f){
		ySpeed = 0.0f;
		position[1] = 0.0f;
	}
	else ySpeed -= 0.06f;
}

void Player::rotate(GLfloat x, GLfloat y) {
	direction[0] = -sin(x);
	direction[1] = sin(y);
	direction[2] = -cos(x);

	GLfloat mag = 10.0f / hypot(hypot(direction[0], direction[1]), direction[2]);
	direction[0] *= mag;
	direction[1] *= mag;
	direction[2] *= mag;
}

void Player::jump(GLfloat speed) {
	if (ySpeed == 0.0f) ySpeed = speed;
}

SnowBall* Player::throwBall(GLfloat speed, GLfloat lifespan, GLfloat directionX, GLfloat directionY, GLfloat directionZ) {
	if (glfwGetTime() < lastThrough + 1) return nullptr;

	if (directionX == 100.0f && directionY == 100.0f && directionZ == 100.0f) {
		directionX = direction[0];
		directionY = direction[1];
		directionZ = direction[2];
	}

	lastThrough = glfwGetTime();
	return new SnowBall(position[0], position[1] + 1.0f, position[2], directionX, directionY, directionZ, speed, id, lifespan);
}
#pragma once
#include "Base.hpp"
#include "Object.hpp"
#include "Shape.hpp"
#include "ShapeIndex.hpp"
//雪玉の情報を管理する
class SnowBall {
	GLfloat position[3]; //位置

	GLfloat direction[3]; //向き

	GLfloat speed; //スピード

	const unsigned int fromID; //どのプレイヤーから投げられたか

	const int slices = 64, stacks = 32;

	std::vector<Object::Vertex> sphereVertex;
	std::vector<GLuint> sphereIndex;

	std::shared_ptr<Shape> shape;

  public:
	SnowBall(GLfloat positionX, GLfloat positionY, GLfloat positionZ, GLfloat directionX, GLfloat directionY, GLfloat directionZ, GLfloat speed, unsigned int fromID) : speed(speed), fromID(fromID) {
		position[0] = positionX;
		position[1] = positionY;
		position[2] = positionZ;
		direction[0] = directionX;
		direction[1] = directionY;
		direction[2] = directionZ;

		// Indexを作る
		for (int i = 0; i < stacks; i++) {
			const int k((slices + 1) * i);
			for (int j = 0; j < slices; j++) {
				const GLuint k0(k + j);
				const GLuint k1(k0 + 1);
				const GLuint k2(k1 + slices);
				const GLuint k3(k2 + 1);

				sphereIndex.push_back(k0);
				sphereIndex.push_back(k2);
				sphereIndex.push_back(k3);

				sphereIndex.push_back(k0);
				sphereIndex.push_back(k3);
				sphereIndex.push_back(k1);
			}
		}

		update();
	}

	SnowBall(const SnowBall& snowball) : speed(snowball.speed), fromID(snowball.fromID) {
		position[0] = snowball.position[0];
		position[1] = snowball.position[1];
		position[2] = snowball.position[2];
		direction[0] = snowball.direction[0];
		direction[1] = snowball.direction[1];
		direction[2] = snowball.direction[2];
		sphereVertex = snowball.sphereVertex;
		sphereIndex = snowball.sphereIndex;
		shape = snowball.shape;
	}

	void update() {
		sphereVertex.clear();
		GLfloat mag = speed / hypot(hypot(direction[0], direction[1]), direction[2]);
		move(direction[0] * mag, direction[1] * mag, direction[2] * mag);

		for (int i = 0; i <= stacks; i++) {
			const float t(static_cast<float>(i) / static_cast<float>(stacks));
			const float y(cos(acos(-1) * t)), r(sin(acos(-1) * t));
			for (int j = 0; j <= slices; j++) {
				const float s(static_cast<float>(j) / static_cast<float>(slices));
				const float z(r * cos(acos(-1) * 2 * s)), x(r * sin(acos(-1) * 2 * s));

				const Object::Vertex v = {position[0] + x, position[1] + y, position[2] + z, 1.0f, 1.0f, 1.0f};
				sphereVertex.push_back(v);
			}
		}

		shape = std::make_shared<ShapeIndex>(3, static_cast<GLsizei>(sphereVertex.size()), sphereVertex.data(), static_cast<GLsizei>(sphereIndex.size()), sphereIndex.data());
	}

	void draw() {
		shape->draw(GL_TRIANGLES);
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
};
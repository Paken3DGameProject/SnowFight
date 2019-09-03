#pragma once
#include "Base.hpp"
#include "Matrix.hpp"

class Vector {
	GLfloat element[4];
<<<<<<< HEAD
	GLfloat length;

public:
=======

  public:
>>>>>>> 83e6d7c3ec4a8970cf9db19579d3c0af09582f7b
	//コンストラクタ 変換したいものを渡す
	Vector(GLfloat x, GLfloat y, GLfloat z, GLfloat w = 1.0f);

	//(x,y,z)のベクトルを中心にangle度回す Matrix::rotate(angle,x,y,z)をMatrixを引数にとるupdate関数に渡している
	void update(GLfloat x, GLfloat y, GLfloat z, GLfloat angle);

	//変換対象にtを掛ける
	void update(Matrix t);

	//操作後のベクトルへの参照を返す
	GLfloat* get();
};
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
	//�R���X�g���N�^ �ϊ����������̂�n��
	Vector(GLfloat x, GLfloat y, GLfloat z, GLfloat w = 1.0f);

	//(x,y,z)�̃x�N�g���𒆐S��angle�x�� Matrix::rotate(angle,x,y,z)��Matrix�������ɂƂ�update�֐��ɓn���Ă���
	void update(GLfloat x, GLfloat y, GLfloat z, GLfloat angle);

	//�ϊ��Ώۂ�t���|����
	void update(Matrix t);

	//�����̃x�N�g���ւ̎Q�Ƃ�Ԃ�
	GLfloat* get();
};
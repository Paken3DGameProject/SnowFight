#pragma once

#include "Base.hpp"
#include "Player.hpp"

class Matrix {
    GLfloat matrix[16]; //�s��̏��

public:
    Matrix() {} //�f�t�H���g�R���X�g���N�^

    Matrix(const GLfloat *a); //�z�񂩂�C���X�^���X�𐶐�

    Matrix(const Player player); //�v���[���[�ɍ��킹�Ď��_���ړ�

    const GLfloat *data() const; //�z���Ԃ�

    void getNormalMatrix(GLfloat *m) const;

    void loadIdentity(); //�P�ʍs��ɂ���

    static Matrix identity(); //�P�ʍs���Ԃ�

    static Matrix translate(GLfloat x, GLfloat y, GLfloat z); //(x,y,z)�ړ�����

    static Matrix scale(GLfloat x, GLfloat y, GLfloat z); //(x,y,z)�{�g�傷��

    static Matrix rotate(GLfloat a, GLfloat x, GLfloat y, GLfloat z); //(x,y,z)������A��]����

    static Matrix rotateX(GLfloat s); // X����s��]����

    Matrix operator*(const Matrix &m) const; //��Z���Z�q

    static Matrix lookat(GLfloat ex, GLfloat ey, GLfloat ez, //���_�̍��W
                         GLfloat gx, GLfloat gy, GLfloat gz,                  //�ڕW�_�̍��W
                         GLfloat ux, GLfloat uy, GLfloat uz);

    static Matrix orthogonal(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat z_near, GLfloat z_far);

    static Matrix frustum(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat z_near, GLfloat z_far);

    static Matrix perspective(GLfloat fovy, GLfloat aspect, GLfloat z_near, GLfloat z_far);
};

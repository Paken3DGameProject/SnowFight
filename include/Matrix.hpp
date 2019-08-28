#pragma once

#include "Base.hpp"
#include "Player.hpp"

class Matrix {
    GLfloat matrix[16]; //行列の情報

public:
    Matrix() {} //デフォルトコンストラクタ

    Matrix(const GLfloat *a); //配列からインスタンスを生成

    Matrix(const Player player); //プレーヤーに合わせて視点を移動

    const GLfloat *data() const; //配列を返す

    void getNormalMatrix(GLfloat *m) const;

    void loadIdentity(); //単位行列にする

    static Matrix identity(); //単位行列を返す

    static Matrix translate(GLfloat x, GLfloat y, GLfloat z); //(x,y,z)移動する

    static Matrix scale(GLfloat x, GLfloat y, GLfloat z); //(x,y,z)倍拡大する

    static Matrix rotate(GLfloat a, GLfloat x, GLfloat y, GLfloat z); //(x,y,z)を軸にA回転する

    static Matrix rotateX(GLfloat s); // X軸でs回転する

    Matrix operator*(const Matrix &m) const; //乗算演算子

    static Matrix lookat(GLfloat ex, GLfloat ey, GLfloat ez, //視点の座標
                         GLfloat gx, GLfloat gy, GLfloat gz,                  //目標点の座標
                         GLfloat ux, GLfloat uy, GLfloat uz);

    static Matrix orthogonal(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat z_near, GLfloat z_far);

    static Matrix frustum(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat z_near, GLfloat z_far);

    static Matrix perspective(GLfloat fovy, GLfloat aspect, GLfloat z_near, GLfloat z_far);
};

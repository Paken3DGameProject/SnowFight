//基本図形データを扱うクラス
//描画手順は以下の流れで、ここでは6までを行う
// 1.頂点配列オブジェクトを作成
// 2.頂点配列オブジェクトを結合する
// 3.頂点バッファオブジェクトを作成
// 4.頂点バッファオブジェクトを結合して、頂点配列オブジェクトに対応づける
// 5.GPU用のメモリに頂点の情報を送る
// 6.頂点バッファオブジェクトをシェーダファイルの変数に対応づける
// 7.描画命令を実施

#pragma once

#include "Base.hpp"

class Object { //図形データの管理

    GLuint vao; //頂点配列オブジェクト名

    GLuint vbo; //頂点バッファオブジェクト名

    GLuint ibo; // indexの頂点バッファオブジェクト名

public:
    struct Vertex {
        GLfloat position[3]; //頂点の位置(x,y,z)

        GLfloat color[3]; //色(R,G,B)
    };

	struct TextureVertex {
		GLfloat position[3];

		GLfloat UV[2];
	};

    //コンストラクタ
    //(次元、頂点数、頂点を格納した配列,indexの数,indexを格納した配列
    Object(GLint size, GLsizei vertexCount, const Vertex *vertex, GLsizei indexCount = 0, const GLuint *index = NULL);

	Object(GLint size, GLsizei texturevertexCount, const TextureVertex* vertex, GLsizei indexCount = 0, const GLuint * index = NULL);

    virtual ~Object(); //仮想関数にすることで派生クラスで再定義可能に

private:
    //コピーコンストラクタをprivateにする
    //複数のオブジェクトで同じ頂点オブジェクトを保持するのを防ぐ
    Object(const Object &o);

    Object &operator=(const Object &o);

public:
    void bind() const {         //描画指定の関数
        glBindVertexArray(vao); //描画する頂点配列オブジェクトを指定
    }
};
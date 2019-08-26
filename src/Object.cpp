//基本図形データを扱うクラス
//描画手順は以下の流れで、ここでは6までを行う
// 1.頂点配列オブジェクトを作成
// 2.頂点配列オブジェクトを結合する
// 3.頂点バッファオブジェクトを作成
// 4.頂点バッファオブジェクトを結合して、頂点配列オブジェクトに対応づける
// 5.GPU用のメモリに頂点の情報を送る
// 6.頂点バッファオブジェクトをシェーダファイルの変数に対応づける
// 7.描画命令を実施

#include "Base.hpp"
#include "Object.hpp"

Object::Object(GLint size, GLsizei vertexcount, const Vertex* vertex, GLsizei indexcount, const GLuint* index) {
	//頂点配列オブジェクトを作成(数,indexを格納する配列)
	glGenVertexArrays(1, &vao);
	//頂点配列オブジェクトを結合(オブジェクトのindex)
	glBindVertexArray(vao);

	//頂点バッファオブジェクトを作成(数、indexを格納する配列)
	glGenBuffers(1, &vbo);
	//頂点バッファオブジェクトを結合して、配列オブジェクトに対応づける
	//(バッファの種類,オブジェクトのindex)
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//頂点の情報をメモリに書き込む
	glBufferData(GL_ARRAY_BUFFER, vertexcount * sizeof(Vertex), vertex, GL_STATIC_DRAW);
	//結合されている頂点バッファオブジェクトをin変数から参照できるようにする
	glVertexAttribPointer(0, size, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<Vertex*>(0)->position); //座標
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<Vertex*>(0)->color);       //色
	//変数を有効にする
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	//インデックスの頂点バッファオブジェクト
	glGenBuffers(1, &ibo);
	//結合
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	//インデックスの情報をメモリに書き込む
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexcount * sizeof(GLuint), index, GL_STATIC_DRAW);
}

Object::~Object() {
	//頂点配列オブジェクトを削除
	glDeleteBuffers(1, &vao);
	//頂点バッファオブジェクトを削除
	glDeleteBuffers(1, &vbo);
	// indexの頂点バッファオブジェクトを削除
	glDeleteBuffers(1, &ibo);
}

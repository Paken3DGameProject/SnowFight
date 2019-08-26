#pragma once
#include "Base.hpp"
#include "Object.hpp" //図形データ

class Shape { //図形の描画

	//図形データ
	// shared_ptrを使うことで、使われなくなったら自動的に消える
	std::shared_ptr<const Object> object;

  protected:
	const GLsizei vertexcount; //頂点数

  public:
	//コンストラクタ
	//(次元,頂点数,頂点を格納した配列,indexの数,indexを格納した配列)
	Shape(GLint size, GLsizei vertexcount, const Object::Vertex* vertex, GLsizei indexcount = 0, const GLuint* index = NULL) : object(new Object(size, vertexcount, vertex, indexcount, index)), vertexcount(vertexcount) {}

	virtual void execute(GLenum mode) const { //描画の実行
		glDrawArrays(mode, 0, vertexcount);   //(図形の種類,描画する頂点の先頭番号,頂点の数)
	}

	virtual void draw(GLenum mode) const { //描画
		object->bind();                    //頂点配列オブジェクトの結合
		execute(mode);                     //描画の実行
	}
};
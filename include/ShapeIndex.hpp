#pragma once

#include "Shape.hpp"

class ShapeIndex : public Shape {
  protected:
	//頂点の数
	const GLsizei indexcount;

  public:
	//コンストラクタ
	//(次元,頂点数,頂点を格納した配列,indexの数,indexを格納した配列)
	ShapeIndex(GLint size, GLsizei vertexcount, const Object::Vertex* vertex, GLsizei indexcount, const GLuint* index) : Shape(size, vertexcount, vertex, indexcount, index), indexcount(indexcount) {}

	//描画の実行
	virtual void execute(GLenum mode) const {
		//線分群で描画する
		glDrawElements(mode, indexcount, GL_UNSIGNED_INT, 0);
	}
};
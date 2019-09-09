#pragma once

#include "Shape.hpp"

class ShapeIndex : public Shape {
protected:
    //頂点の数
    const GLsizei indexCount;

public:
    //コンストラクタ
    //(次元,頂点数,頂点を格納した配列,indexの数,indexを格納した配列)
    ShapeIndex(GLint size, GLsizei vertexCount, const Object::Vertex *vertex, GLsizei indexCount, const GLuint *index)
		:Shape(size, vertexCount, vertex, indexCount, index), indexCount(indexCount) {}

	ShapeIndex(GLint size, GLsizei textureVertexCount, const Object::TextureVertex* textureVertex, GLsizei indexCount, const GLuint* index)
		:Shape(size, textureVertexCount, textureVertex, indexCount, index), indexCount(indexCount) {}

    //描画の実行
    virtual void execute(GLenum mode) const {
        //線分群で描画する
        glDrawElements(mode, indexCount, GL_UNSIGNED_INT, 0);
    }
};
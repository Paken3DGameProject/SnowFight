#pragma once

#include "Base.hpp"
#include "Object.hpp" //図形データ

class Shape { //図形の描画

    //図形データ
    // shared_ptrを使うことで、使われなくなったら自動的に消える
    std::shared_ptr<const Object> object;

protected:
    const GLsizei vertexCount; //頂点数

public:
    //コンストラクタ
    //(次元,頂点数,頂点を格納した配列,indexの数,indexを格納した配列)
    Shape(GLint size, GLsizei vertexCount, const Object::Vertex *vertex, GLsizei indexCount = 0,
		const GLuint *index = NULL) : object(new Object(size, vertexCount, vertex, indexCount, index)),
		vertexCount(vertexCount) {}

	Shape(GLint size, GLsizei textureVertexCount, const Object::TextureVertex* vertex, GLsizei indexCount = 0,
		const GLuint * index = NULL) :object(new Object(size, textureVertexCount, vertex, indexCount, index)),
		vertexCount(vertexCount) {}

    virtual void execute(GLenum mode) const { //描画の実行
        glDrawArrays(mode, 0, vertexCount);   //(図形の種類,描画する頂点の先頭番号,頂点の数)
    }

    virtual void draw(GLenum mode) const { //描画
        object->bind();                    //頂点配列オブジェクトの結合
        execute(mode);                     //描画の実行
    }
};
#pragma once

#include "Shape.hpp"

class ShapeIndex : public Shape {
protected:
    //頂点の数
    const GLsizei index_count;

public:
    //コンストラクタ
    //(次元,頂点数,頂点を格納した配列,indexの数,indexを格納した配列)
    ShapeIndex(GLint size, GLsizei vertex_count, const Object::Vertex *vertex, GLsizei index_count, const GLuint *index)
            : Shape(size, vertex_count, vertex, index_count, index), index_count(index_count) {}

    //描画の実行
    virtual void execute(GLenum mode) const {
        //線分群で描画する
        glDrawElements(mode, index_count, GL_UNSIGNED_INT, 0);
    }
};
#pragma once

#include "Shape.hpp"

class ShapeIndex : public Shape {
protected:
    //Έ_Μ
    const GLsizei index_count;

public:
    //RXgN^
    //(³,Έ_,Έ_πi[΅½zρ,indexΜ,indexπi[΅½zρ)
    ShapeIndex(GLint size, GLsizei vertex_count, const Object::Vertex *vertex, GLsizei index_count, const GLuint *index)
            : Shape(size, vertex_count, vertex, index_count, index), index_count(index_count) {}

    //`ζΜΐs
    virtual void execute(GLenum mode) const {
        //όͺQΕ`ζ·ι
        glDrawElements(mode, index_count, GL_UNSIGNED_INT, 0);
    }
};
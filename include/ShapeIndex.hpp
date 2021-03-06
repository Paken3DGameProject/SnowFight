#pragma once

#include "Shape.hpp"

class ShapeIndex : public Shape {
protected:
    //Έ_Μ
    const GLsizei indexCount;

public:
    //RXgN^
    //(³,Έ_,Έ_πi[΅½zρ,indexΜ,indexπi[΅½zρ)
    ShapeIndex(GLint size, GLsizei vertexCount, const Object::Vertex *vertex, GLsizei indexCount, const GLuint *index)
		:Shape(size, vertexCount, vertex, indexCount, index), indexCount(indexCount) {}

	ShapeIndex(GLint size, GLsizei textureVertexCount, const Object::TextureVertex* textureVertex, GLsizei indexCount, const GLuint* index)
		:Shape(size, textureVertexCount, textureVertex, indexCount, index), indexCount(indexCount) {}

    //`ζΜΐs
    virtual void execute(GLenum mode) const {
        //όͺQΕ`ζ·ι
        glDrawElements(mode, indexCount, GL_UNSIGNED_INT, 0);
    }
};
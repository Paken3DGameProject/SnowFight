#pragma once

#include "Shape.hpp"

class ShapeIndex : public Shape {
protected:
    //���_�̐�
    const GLsizei indexCount;

public:
    //�R���X�g���N�^
    //(����,���_��,���_���i�[�����z��,index�̐�,index���i�[�����z��)
    ShapeIndex(GLint size, GLsizei vertexCount, const Object::Vertex *vertex, GLsizei indexCount, const GLuint *index)
		:Shape(size, vertexCount, vertex, indexCount, index), indexCount(indexCount) {}

	ShapeIndex(GLint size, GLsizei textureVertexCount, const Object::TextureVertex* textureVertex, GLsizei indexCount, const GLuint* index)
		:Shape(size, textureVertexCount, textureVertex, indexCount, index), indexCount(indexCount) {}

    //�`��̎��s
    virtual void execute(GLenum mode) const {
        //�����Q�ŕ`�悷��
        glDrawElements(mode, indexCount, GL_UNSIGNED_INT, 0);
    }
};
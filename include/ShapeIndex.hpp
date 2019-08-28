#pragma once

#include "Shape.hpp"

class ShapeIndex : public Shape {
protected:
    //���_�̐�
    const GLsizei index_count;

public:
    //�R���X�g���N�^
    //(����,���_��,���_���i�[�����z��,index�̐�,index���i�[�����z��)
    ShapeIndex(GLint size, GLsizei vertex_count, const Object::Vertex *vertex, GLsizei index_count, const GLuint *index)
            : Shape(size, vertex_count, vertex, index_count, index), index_count(index_count) {}

    //�`��̎��s
    virtual void execute(GLenum mode) const {
        //�����Q�ŕ`�悷��
        glDrawElements(mode, index_count, GL_UNSIGNED_INT, 0);
    }
};
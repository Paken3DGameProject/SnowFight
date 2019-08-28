#pragma once

#include "Base.hpp"
#include "Object.hpp" //�}�`�f�[�^

class Shape { //�}�`�̕`��

    //�}�`�f�[�^
    // shared_ptr���g�����ƂŁA�g���Ȃ��Ȃ����玩���I�ɏ�����
    std::shared_ptr<const Object> object;

protected:
    const GLsizei vertex_count; //���_��

public:
    //�R���X�g���N�^
    //(����,���_��,���_���i�[�����z��,index�̐�,index���i�[�����z��)
    Shape(GLint size, GLsizei vertex_count, const Object::Vertex *vertex, GLsizei index_count = 0,
          const GLuint *index = NULL) : object(new Object(size, vertex_count, vertex, index_count, index)),
                                        vertex_count(vertex_count) {}
  Shape(GLint size, GLsizei vertex_count, const Object::TextureVertex* vertex, GLsizei index_count = 0, const GLuint* index = NULL) : object(new Object(size, vertex_count, vertex, index_count, index)), vertex_count(vertex_count) {}

    virtual void execute(GLenum mode) const { //�`��̎��s
        glDrawArrays(mode, 0, vertex_count);   //(�}�`�̎��,�`�悷�钸�_�̐擪�ԍ�,���_�̐�)
    }

    virtual void draw(GLenum mode) const { //�`��
        object->bind();                    //���_�z��I�u�W�F�N�g�̌���
        execute(mode);                     //�`��̎��s
    }
};
#pragma once

#include "Base.hpp"
#include "Object.hpp" //�}�`�f�[�^

class Shape { //�}�`�̕`��

    //�}�`�f�[�^
    // shared_ptr���g�����ƂŁA�g���Ȃ��Ȃ����玩���I�ɏ�����
    std::shared_ptr<const Object> object;

protected:
    const GLsizei vertexCount; //���_��

public:
    //�R���X�g���N�^
    //(����,���_��,���_���i�[�����z��,index�̐�,index���i�[�����z��)
    Shape(GLint size, GLsizei vertexCount, const Object::Vertex *vertex, GLsizei indexCount = 0,
		const GLuint *index = NULL) : object(new Object(size, vertexCount, vertex, indexCount, index)),
		vertexCount(vertexCount) {}

	Shape(GLint size, GLsizei textureVertexCount, const Object::TextureVertex* vertex, GLsizei indexCount = 0,
		const GLuint * index = NULL) :object(new Object(size, textureVertexCount, vertex, indexCount, index)),
		vertexCount(vertexCount) {}

    virtual void execute(GLenum mode) const { //�`��̎��s
        glDrawArrays(mode, 0, vertexCount);   //(�}�`�̎��,�`�悷�钸�_�̐擪�ԍ�,���_�̐�)
    }

    virtual void draw(GLenum mode) const { //�`��
        object->bind();                    //���_�z��I�u�W�F�N�g�̌���
        execute(mode);                     //�`��̎��s
    }
};
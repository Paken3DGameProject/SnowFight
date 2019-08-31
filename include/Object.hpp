//��{�}�`�f�[�^�������N���X
//�`��菇�͈ȉ��̗���ŁA�����ł�6�܂ł��s��
// 1.���_�z��I�u�W�F�N�g���쐬
// 2.���_�z��I�u�W�F�N�g����������
// 3.���_�o�b�t�@�I�u�W�F�N�g���쐬
// 4.���_�o�b�t�@�I�u�W�F�N�g���������āA���_�z��I�u�W�F�N�g�ɑΉ��Â���
// 5.GPU�p�̃������ɒ��_�̏��𑗂�
// 6.���_�o�b�t�@�I�u�W�F�N�g���V�F�[�_�t�@�C���̕ϐ��ɑΉ��Â���
// 7.�`�施�߂����{

#pragma once

#include "Base.hpp"

class Object { //�}�`�f�[�^�̊Ǘ�

    GLuint vao; //���_�z��I�u�W�F�N�g��

    GLuint vbo; //���_�o�b�t�@�I�u�W�F�N�g��

    GLuint ibo; // index�̒��_�o�b�t�@�I�u�W�F�N�g��

public:
    struct Vertex {
        GLfloat position[3]; //���_�̈ʒu(x,y,z)

        GLfloat color[3]; //�F(R,G,B)
    };

	struct TextureVertex {
		GLfloat position[3];

		GLfloat UV[2];
	};

    //�R���X�g���N�^
    //(�����A���_���A���_���i�[�����z��,index�̐�,index���i�[�����z��
    Object(GLint size, GLsizei vertexCount, const Vertex *vertex, GLsizei indexCount = 0, const GLuint *index = NULL);

	Object(GLint size, GLsizei texturevertexCount, const TextureVertex* vertex, GLsizei indexCount = 0, const GLuint * index = NULL);

    virtual ~Object(); //���z�֐��ɂ��邱�ƂŔh���N���X�ōĒ�`�\��

private:
    //�R�s�[�R���X�g���N�^��private�ɂ���
    //�����̃I�u�W�F�N�g�œ������_�I�u�W�F�N�g��ێ�����̂�h��
    Object(const Object &o);

    Object &operator=(const Object &o);

public:
    void bind() const {         //�`��w��̊֐�
        glBindVertexArray(vao); //�`�悷�钸�_�z��I�u�W�F�N�g���w��
    }
};
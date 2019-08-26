//��{�}�`�f�[�^�������N���X
//�`��菇�͈ȉ��̗���ŁA�����ł�6�܂ł��s��
// 1.���_�z��I�u�W�F�N�g���쐬
// 2.���_�z��I�u�W�F�N�g����������
// 3.���_�o�b�t�@�I�u�W�F�N�g���쐬
// 4.���_�o�b�t�@�I�u�W�F�N�g���������āA���_�z��I�u�W�F�N�g�ɑΉ��Â���
// 5.GPU�p�̃������ɒ��_�̏��𑗂�
// 6.���_�o�b�t�@�I�u�W�F�N�g���V�F�[�_�t�@�C���̕ϐ��ɑΉ��Â���
// 7.�`�施�߂����{

#include "Base.hpp"
#include "Object.hpp"

Object::Object(GLint size, GLsizei vertexcount, const Vertex* vertex, GLsizei indexcount, const GLuint* index) {
	//���_�z��I�u�W�F�N�g���쐬(��,index���i�[����z��)
	glGenVertexArrays(1, &vao);
	//���_�z��I�u�W�F�N�g������(�I�u�W�F�N�g��index)
	glBindVertexArray(vao);

	//���_�o�b�t�@�I�u�W�F�N�g���쐬(���Aindex���i�[����z��)
	glGenBuffers(1, &vbo);
	//���_�o�b�t�@�I�u�W�F�N�g���������āA�z��I�u�W�F�N�g�ɑΉ��Â���
	//(�o�b�t�@�̎��,�I�u�W�F�N�g��index)
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//���_�̏����������ɏ�������
	glBufferData(GL_ARRAY_BUFFER, vertexcount * sizeof(Vertex), vertex, GL_STATIC_DRAW);
	//��������Ă��钸�_�o�b�t�@�I�u�W�F�N�g��in�ϐ�����Q�Ƃł���悤�ɂ���
	glVertexAttribPointer(0, size, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<Vertex*>(0)->position); //���W
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<Vertex*>(0)->color);       //�F
	//�ϐ���L���ɂ���
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	//�C���f�b�N�X�̒��_�o�b�t�@�I�u�W�F�N�g
	glGenBuffers(1, &ibo);
	//����
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	//�C���f�b�N�X�̏����������ɏ�������
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexcount * sizeof(GLuint), index, GL_STATIC_DRAW);
}

Object::~Object() {
	//���_�z��I�u�W�F�N�g���폜
	glDeleteBuffers(1, &vao);
	//���_�o�b�t�@�I�u�W�F�N�g���폜
	glDeleteBuffers(1, &vbo);
	// index�̒��_�o�b�t�@�I�u�W�F�N�g���폜
	glDeleteBuffers(1, &ibo);
}

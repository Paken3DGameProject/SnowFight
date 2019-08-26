#pragma once
#include "Base.hpp"
#include "Object.hpp" //�}�`�f�[�^

class Shape { //�}�`�̕`��

	//�}�`�f�[�^
	// shared_ptr���g�����ƂŁA�g���Ȃ��Ȃ����玩���I�ɏ�����
	std::shared_ptr<const Object> object;

  protected:
	const GLsizei vertexcount; //���_��

  public:
	//�R���X�g���N�^
	//(����,���_��,���_���i�[�����z��,index�̐�,index���i�[�����z��)
	Shape(GLint size, GLsizei vertexcount, const Object::Vertex* vertex, GLsizei indexcount = 0, const GLuint* index = NULL) : object(new Object(size, vertexcount, vertex, indexcount, index)), vertexcount(vertexcount) {}

	virtual void execute(GLenum mode) const { //�`��̎��s
		glDrawArrays(mode, 0, vertexcount);   //(�}�`�̎��,�`�悷�钸�_�̐擪�ԍ�,���_�̐�)
	}

	virtual void draw(GLenum mode) const { //�`��
		object->bind();                    //���_�z��I�u�W�F�N�g�̌���
		execute(mode);                     //�`��̎��s
	}
};
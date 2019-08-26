#pragma once

#include "Shape.hpp"

class ShapeIndex : public Shape {
  protected:
	//���_�̐�
	const GLsizei indexcount;

  public:
	//�R���X�g���N�^
	//(����,���_��,���_���i�[�����z��,index�̐�,index���i�[�����z��)
	ShapeIndex(GLint size, GLsizei vertexcount, const Object::Vertex* vertex, GLsizei indexcount, const GLuint* index) : Shape(size, vertexcount, vertex, indexcount, index), indexcount(indexcount) {}

	//�`��̎��s
	virtual void execute(GLenum mode) const {
		//�����Q�ŕ`�悷��
		glDrawElements(mode, indexcount, GL_UNSIGNED_INT, 0);
	}
};
#pragma once

#include "Shape.hpp"

class ShapeIndex : public Shape {
  protected:
	//Έ_Μ
	const GLsizei indexcount;

  public:
	//RXgN^
	//(³,Έ_,Έ_πi[΅½zρ,indexΜ,indexπi[΅½zρ)
	ShapeIndex(GLint size, GLsizei vertexcount, const Object::Vertex* vertex, GLsizei indexcount, const GLuint* index) : Shape(size, vertexcount, vertex, indexcount, index), indexcount(indexcount) {}

	//`ζΜΐs
	virtual void execute(GLenum mode) const {
		//όͺQΕ`ζ·ι
		glDrawElements(mode, indexcount, GL_UNSIGNED_INT, 0);
	}
};
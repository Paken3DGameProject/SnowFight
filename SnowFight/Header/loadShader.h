#pragma once
//�V�F�[�_�v���O���������[�h���Ďg��
#include <iostream>
#include <fstream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

GLboolean printShaderInfoLog(GLuint shader, const char* str) {//�R���p�C�����ʂ�\������

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);//�V�F�[�_�I�u�W�F�N�g�̏����擾
	if (status == GL_FALSE)std::cerr << "Compile Error in" << str << std::endl;

	GLsizei bufSize;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &bufSize);//�R���p�C�����O�̒������擾

	if (bufSize > 1) {
		std::vector<GLchar> infoLog(bufSize);
		GLsizei length;
		glGetShaderInfoLog(shader, bufSize, &length, &infoLog[0]);//�R���p�C�����O�����o��
		std::cerr << &infoLog[0] << std::endl;
	}

	return static_cast<GLboolean>(status);
}

GLboolean printProgramInfoLog(GLuint program){//�����N���ʂ�\������

	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);//�����N���ʂ��擾
	if (status == GL_FALSE) std::cerr << "Link Error." << std::endl;

	GLsizei bufSize;
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufSize);//�����N���O�̒������擾

	if (bufSize > 1){
		std::vector<GLchar> infoLog(bufSize);
		GLsizei length;
		glGetProgramInfoLog(program, bufSize, &length, &infoLog[0]);//�����N���O�����o��
		std::cerr << &infoLog[0] << std::endl;
	}

	return static_cast<GLboolean>(status);
}

bool readShaderSource(const char* name, std::vector<GLchar>& buffer) {//�V�F�[�_�t�@�C����ǂݍ���

	if (name == NULL)return false;

	std::ifstream file(name, std::ios::binary);
	if (file.fail()) {//�J���̂Ɏ��s����
		std::cerr << "Error: Can't open source file: " << name << std::endl;
		return false;
	}

	file.seekg(0L, std::ios::end);//�����܂ňړ�
	GLsizei length = static_cast<GLsizei>(file.tellg());//�����𓾂�

	buffer.resize(length + 1);//buffer�̃T�C�Y���m��

	file.seekg(0L, std::ios::beg);
	file.read(buffer.data(), length);
	buffer[length] = '\0';

	if (file.fail()) {//�ǂݍ��݂Ɏ��s
		std::cerr << "Error: Could not read souce file: " << name << std::endl;
		file.close();
		return false;
	}

	file.close();
	return true;
}

GLuint createProgram(const char* vsrc, const char* fsrc) {

	const GLuint program(glCreateProgram());//��̃v���O�����I�u�W�F�N�g���쐬�A���s�Ȃ�0��Ԃ�

	if (vsrc != NULL) {
		//�v���O��������V�F�[�_�I�u�W�F�N�g�𐶐����ăR���p�C��
		const GLuint vobj(glCreateShader(GL_VERTEX_SHADER));
		glShaderSource(vobj, 1, &vsrc, NULL);
		glCompileShader(vobj);

		glAttachShader(program, vobj);//�v���O�����ɃV�F�[�_�I�u�W�F�N�g���A�^�b�`(�t��glDetachShader)
		glDeleteShader(vobj);//�V�F�[�_�I�u�W�F�N�g�ɍ폜�}�[�N��t���A�ǂ��ł��g���Ȃ��Ȃ����瑦����
	}

	if (fsrc != NULL) {
		//��Ɠ��l
		const GLuint fobj(glCreateShader(GL_FRAGMENT_SHADER));
		glShaderSource(fobj, 1, &fsrc, NULL);
		glCompileShader(fobj);

		glAttachShader(program, fobj);
		glDeleteShader(fobj);
	}

	glBindAttribLocation(program, 0, "position");//�o�[�e�b�N�X�V�F�[�_�̓��͂�index��ݒ�
	glBindFragDataLocation(program, 0, "fragment");//�t���O�����g�V�F�[�_�̏o�͂�index��ݒ�
	//������GPU�̃��W�X�^�ԍ��ɑ�������

	//�v���O�����I�u�W�F�N�g�������N
	glLinkProgram(program);

	return program;
}

GLuint loadProgram(const char* vert, const char* frag){//�v���O�����I�u�W�F�N�g���t�@�C��������쐬
	//�V�F�[�_�t�@�C����ǂݍ���
	std::vector<GLchar> vsrc;
	const bool vstat(readShaderSource(vert, vsrc));
	std::vector<GLchar> fsrc;
	const bool fstat(readShaderSource(frag, fsrc));

	//�v���O�����I�u�W�F�N�g���쐬����
	return vstat && fstat ? createProgram(vsrc.data(), fsrc.data()) : 0;
}
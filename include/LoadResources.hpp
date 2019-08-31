#pragma once

#include "Base.hpp"
#include <GLFW/glfw3.h>
#include <GL/glew.h>

GLboolean printShaderInfoLog(GLuint shader, const char *str); //�V�F�[�_�̃R���p�C�����ʂ�\������

GLboolean printProgramInfoLog(GLuint program); //�����N���ʂ�\������

bool readShaderSource(const char *name, std::vector<GLchar> &buffer); //�V�F�[�_�t�@�C����ǂݍ���

GLuint createProgram(const char *vsrc, const char *fsrc); //�v���O�����I�u�W�F�N�g���쐬

GLuint loadProgram(const char *vert, const char *frag); //�v���O�����I�u�W�F�N�g���t�@�C��������쐬

GLuint loadBMP(const char* imagePath, GLenum unit);
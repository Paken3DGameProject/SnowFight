/******************************************/
/*              Made by kaage             */
/*          Last Update 2019/08/13        */
/******************************************/

#include <iostream>
#include "Header/loadShader.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
int main() {
	if (glfwInit() == GL_FALSE) {//������
		//�I�����̃��\�[�X����Ȃǂ������I�ɍs����
		//exit()��main�ȊO�̏ꏊ�ȂǂŖ����ɏI��������ꍇ��glfwTerminate()�𖾎��I�ɌĂԂ���
		std::cerr << "Can't initialize GLFW" << std::endl;
		return 1;
	}

	//GLFW�̃o�[�W������I��(Version 3.2 Core Profile)
	//glfwDefaultWindowHints()�Ńf�t�H���g�ɖ߂���炵��
	//GPU���Ή����Ă��Ȃ��ꍇ�͌��glfwCreateWindow()�Ŏ��s����
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* const window(glfwCreateWindow(640, 480, "Snow Fight", NULL, NULL));//Window�̍쐬
	if (window == NULL) {//Window�쐬���s
		std::cerr << "Can't create GLFW Window." << std::endl;
		return 1;
	}

	glfwMakeContextCurrent(window);//����Ώ�Window��ݒ�

	glewExperimental = GL_TRUE;//GLEW�̏������ɕK�v
	if (glewInit() != GLEW_OK) {//GLEW�̏�����
		std::cerr << "Can't initialize GLEW" << std::endl;
		return 1;
	}

	glfwSwapInterval(1);//�o�b�t�@����ւ���҂^�C�~���O�A0�ɂ���ƃe�B�A�����O����̂�1�ł悢

	glClearColor(0.0f, 1.0f, 1.0f, 0.0f);//Window��h��Ԃ��F��ݒ�

	const GLuint program(loadProgram("Shader/Source.vert", "Shader/Source.frag"));

	while (glfwWindowShouldClose(window) == GL_FALSE) {//�`��X�V
		glClear(GL_COLOR_BUFFER_BIT);//�J���[�o�b�t�@��glClearColor�Ŏw�肵���F�œh��Ԃ�

		glfwSwapBuffers(window);//�o�b�t�@�����ւ���(�_�u���o�b�t�@�����O)

		glfwWaitEvents();//�C�x���g(�}�E�X����Ȃ�)��҂�
	}
}
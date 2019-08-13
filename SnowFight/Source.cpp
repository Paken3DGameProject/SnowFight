/******************************************/
/*              Made by kaage             */
/*          Last Update 2019/08/13        */
/******************************************/

#include <iostream>
#include "Header/loadShader.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
int main() {
	if (glfwInit() == GL_FALSE) {//初期化
		//終了時のリソース解放なども自動的に行われる
		//exit()やmain以外の場所などで無理に終了させる場合はglfwTerminate()を明示的に呼ぶこと
		std::cerr << "Can't initialize GLFW" << std::endl;
		return 1;
	}

	//GLFWのバージョンを選択(Version 3.2 Core Profile)
	//glfwDefaultWindowHints()でデフォルトに戻せるらしい
	//GPUが対応していない場合は後のglfwCreateWindow()で失敗する
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* const window(glfwCreateWindow(640, 480, "Snow Fight", NULL, NULL));//Windowの作成
	if (window == NULL) {//Window作成失敗
		std::cerr << "Can't create GLFW Window." << std::endl;
		return 1;
	}

	glfwMakeContextCurrent(window);//操作対象Windowを設定

	glewExperimental = GL_TRUE;//GLEWの初期化に必要
	if (glewInit() != GLEW_OK) {//GLEWの初期化
		std::cerr << "Can't initialize GLEW" << std::endl;
		return 1;
	}

	glfwSwapInterval(1);//バッファ入れ替えを待つタイミング、0にするとティアリングするので1でよい

	glClearColor(0.0f, 1.0f, 1.0f, 0.0f);//Windowを塗りつぶす色を設定

	const GLuint program(loadProgram("Shader/Source.vert", "Shader/Source.frag"));

	while (glfwWindowShouldClose(window) == GL_FALSE) {//描画更新
		glClear(GL_COLOR_BUFFER_BIT);//カラーバッファをglClearColorで指定した色で塗りつぶす

		glfwSwapBuffers(window);//バッファを入れ替える(ダブルバッファリング)

		glfwWaitEvents();//イベント(マウス操作など)を待つ
	}
}
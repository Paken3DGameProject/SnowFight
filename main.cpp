/******************************************/
/*              Made by kaage             */
/*          Last Update 2019/08/21        */
/******************************************/

#include "Base.hpp"
#include "LoadShader.hpp"
#include "Shape.hpp"
#include "Object.hpp"
#include "Window.hpp"
#include "Matrix.hpp"
#include "ShapeIndex.hpp"
#include "Player.hpp"
#include "SnowBall.hpp"

constexpr Object::Vertex groundVertex[] = {{-30.0f, 0.0f, -30.0f, 0.45f, 0.30f, 0.19f}, {-30.0f, 0.0f, 30.0f, 0.45f, 0.30f, 0.19f}, {30.0f, 0.0f, -30.0f, 0.45f, 0.30f, 0.19f}, {30.0f, 0.0f, 30.0f, 0.45f, 0.30f, 0.19f}};

constexpr Object::Vertex wallsVertex[] = {
    {-30.0f, 0.0f, -30.0f, 0.96f, 0.87f, 0.7f},
    {-30.0f, 7.0f, -30.0f, 0.96f, 0.87f, 0.7f},
    {-30.0f, 0.0f, 30.0f, 0.96f, 0.87f, 0.7f},
    {-30.0f, 7.0f, 30.0f, 0.96f, 0.87f, 0.7f},
    {30.0f, 0.0f, 30.0f, 0.96f, 0.87f, 0.7f},
    {30.0f, 7.0f, 30.0f, 0.96f, 0.87f, 0.7f},
    {30.0f, 0.0f, -30.0f, 0.96f, 0.87f, 0.7f},
    {30.0f, 7.0f, -30.0f, 0.96f, 0.87f, 0.7f},
};

constexpr GLuint wallsIndex[] = {0, 1, 2, 1, 2, 3, 2, 3, 4, 3, 4, 5, 4, 5, 6, 5, 6, 7, 6, 7, 0, 7, 0, 1};

constexpr Object::Vertex wallsBoundVertex[] = {
    {-30.0f, 0.0f, -30.0f, 0.0f, 0.0f, 0.0f},
    {-30.0f, 7.0f, -30.0f, 0.0f, 0.0f, 0.0f},
    {-29.5f, 0.0f, -30.0f, 0.0f, 0.0f, 0.0f},
    {-29.5f, 7.0f, -30.0f, 0.0f, 0.0f, 0.0f},
    {-30.0f, 0.0f, -29.5f, 0.0f, 0.0f, 0.0f},
    {-30.0f, 7.0f, -29.5f, 0.0f, 0.0f, 0.0f},
    {-29.5f, 0.0f, -29.5f, 0.0f, 0.0f, 0.0f},
    {-29.5f, 7.0f, -29.5f, 0.0f, 0.0f, 0.0f},

    {-30.0f, 0.0f, 30.0f, 0.0f, 0.0f, 0.0f},
    {-30.0f, 7.0f, 30.0f, 0.0f, 0.0f, 0.0f},
    {-29.5f, 0.0f, 30.0f, 0.0f, 0.0f, 0.0f},
    {-29.5f, 7.0f, 30.0f, 0.0f, 0.0f, 0.0f},
    {-30.0f, 0.0f, 29.5f, 0.0f, 0.0f, 0.0f},
    {-30.0f, 7.0f, 29.5f, 0.0f, 0.0f, 0.0f},
    {-29.5f, 0.0f, 29.5f, 0.0f, 0.0f, 0.0f},
    {-29.5f, 7.0f, 29.5f, 0.0f, 0.0f, 0.0f},

    {30.0f, 0.0f, 30.0f, 0.0f, 0.0f, 0.0f},
    {30.0f, 7.0f, 30.0f, 0.0f, 0.0f, 0.0f},
    {29.5f, 0.0f, 30.0f, 0.0f, 0.0f, 0.0f},
    {29.5f, 7.0f, 30.0f, 0.0f, 0.0f, 0.0f},
    {30.0f, 0.0f, 29.5f, 0.0f, 0.0f, 0.0f},
    {30.0f, 7.0f, 29.5f, 0.0f, 0.0f, 0.0f},
    {29.5f, 0.0f, 29.5f, 0.0f, 0.0f, 0.0f},
    {29.5f, 7.0f, 29.5f, 0.0f, 0.0f, 0.0f},

    {30.0f, 0.0f, -30.0f, 0.0f, 0.0f, 0.0f},
    {30.0f, 7.0f, -30.0f, 0.0f, 0.0f, 0.0f},
    {29.5f, 0.0f, -30.0f, 0.0f, 0.0f, 0.0f},
    {29.5f, 7.0f, -30.0f, 0.0f, 0.0f, 0.0f},
    {30.0f, 0.0f, -29.5f, 0.0f, 0.0f, 0.0f},
    {30.0f, 7.0f, -29.5f, 0.0f, 0.0f, 0.0f},
    {29.5f, 0.0f, -29.5f, 0.0f, 0.0f, 0.0f},
    {29.5f, 7.0f, -29.5f, 0.0f, 0.0f, 0.0f},
};

constexpr GLuint wallsBoundIndex[] = {1, 3, 5, 3, 5, 7, 2, 3, 6, 3, 6, 7, 4, 5, 6, 5, 6, 7,

    9, 11, 13, 11, 13, 15, 10, 11, 14, 11, 14, 15, 12, 13, 14, 13, 14, 15,

    17, 19, 21, 19, 21, 23, 18, 19, 22, 19, 22, 23, 20, 21, 22, 21, 22, 23,

    25, 27, 29, 27, 29, 31, 26, 27, 30, 27, 30, 31, 28, 29, 30, 29, 30, 31};

int main() {
	if (glfwInit() == GL_FALSE) { //初期化
		//終了時のリソース解放なども自動的に行われる
		// exit()やmain以外の場所などで無理に終了させる場合はglfwTerminate()を明示的に呼ぶこと
		std::cerr << "Can't initialize GLFW" << std::endl;
		return 1;
	}

	// GLFWのバージョンを選択(Version 3.2 Core Profile)
	// glfwDefaultWindowHints()でデフォルトに戻せるらしい
	// GPUが対応していない場合は後のglfwCreateWindow()で失敗する
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	Window window;

	glClearColor(160.0 / 256, 216.0 / 256, 239.0 / 256, 1.0f); // Windowを塗りつぶす色を設定

	//デプスバッファを有効にする
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);

	//プログラムオブジェクトを作成
	const GLuint normalProgram(loadProgram("../resources/normal.vert", "../resources/normal.frag"));
	const GLuint textureProgram(loadProgram("../resources/texture.vert", "../resources/texture.frag"));

	//バーテックスシェーダのuniform変数の場所を取得
	const GLuint normalModelviewLoc(glGetUniformLocation(normalProgram, "modelview"));
	const GLuint normalProjectionLoc(glGetUniformLocation(normalProgram, "projection"));

	// unique_ptrを使うことでptrの削除時にインスタンスも消える
	std::unique_ptr<const Shape> ground(new Shape(3, 4, groundVertex));
	std::unique_ptr<const Shape> walls(new ShapeIndex(3, 8, wallsVertex, 24, wallsIndex));
	std::unique_ptr<const Shape> wallsBound(new ShapeIndex(3, 32, wallsBoundVertex, 72, wallsBoundIndex));

	std::vector<SnowBall> snowBallsVec;

	Player player(1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -10.0f, 10, 3);
	window.setPlayer(&player);

	glfwSetTime(0.0);

	while (window) {                                        //描画更新
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //カラーバッファをglClearColorで指定した色で塗りつぶす

		glUseProgram(normalProgram); //シェーダプログラムの使用開始

		if (window.getMouseButton(GLFW_MOUSE_BUTTON_1) != GLFW_RELEASE && glfwGetTime() > 1.0) {
			glfwSetTime(0.0);
			player.throwBall(0.3f, snowBallsVec);
		}

		//ここから描画処理
		const GLfloat* const size(window.getSize());
		const GLfloat fovy(window.getScale() * 0.01f); //画角(初期値は60度)
		const GLfloat aspect(size[0] / size[1]);
		const Matrix projection(Matrix::perspective(fovy, aspect, 0.1f, 100.0f));

		const Matrix view(player);

		const Matrix modelview(view);

		// uniform変数の設定
		glUniformMatrix4fv(normalProjectionLoc, 1, GL_FALSE, projection.data());
		glUniformMatrix4fv(normalModelviewLoc, 1, GL_FALSE, modelview.data());

		//描画
		ground->draw(GL_TRIANGLE_STRIP);
		wallsBound->draw(GL_TRIANGLES);
		walls->draw(GL_TRIANGLES);
		for (SnowBall& ball : snowBallsVec) {
			ball.update();
			ball.draw();
		}

		window.swapBuffers();
	}
}
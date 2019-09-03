/******************************************/
/*              Made by kaage             */
/*          Last Update 2019/09/01        */
/******************************************/

#include "Base.hpp"
#include "LoadResources.hpp"
#include "Shape.hpp"
#include "Object.hpp"
#include "Window.hpp"
#include "Matrix.hpp"
#include "ShapeIndex.hpp"
#include "Player.hpp"
#include "SnowBall.hpp"

constexpr Object::TextureVertex groundVertex[] = {
	{-32.0f, 0.0f, -32.0f, 0.0f,1.0f},
	{-32.0f, 0.0f, 32.0f, 0.0f,0.0f},
	{32.0f, 0.0f, -32.0f, 1.0f,1.0f},
	{32.0f, 0.0f, 32.0f, 1.0f,0.0f}
};

constexpr Object::TextureVertex wallsVertex[] = {
	{-32.0f, 0.0f, -32.0f, 0.0f,0.0f},
	{-32.0f, 8.0f, -32.0f, 0.0f,1.0f},
	{-32.0f, 0.0f, 32.0f, 1.0f,0.0f},
	{-32.0f, 8.0f, 32.0f, 1.0f,1.0f},
	{32.0f, 0.0f, 32.0f, 0.0f,0.0f},
	{32.0f, 8.0f, 32.0f, 0.0f,1.0f},
	{32.0f, 0.0f, -32.0f, 1.0f,0.0f},
	{32.0f, 8.0f, -32.0f, 1.0f,1.0f},
};

constexpr GLuint wallsIndex[] = {
	0, 1, 2,
	1, 2, 3,
	2, 3, 4,
	3, 4, 5,
	4, 5, 6,
	5, 6, 7,
	6, 7, 0,
	7, 0, 1
};

constexpr Object::Vertex wallsBoundVertex[] = {
    {-32.0f, 0.0f, -32.0f, 0.0f, 0.0f, 0.0f},
    {-32.0f, 8.0f, -32.0f, 0.0f, 0.0f, 0.0f},
    {-31.5f, 0.0f, -32.0f, 0.0f, 0.0f, 0.0f},
    {-31.5f, 8.0f, -32.0f, 0.0f, 0.0f, 0.0f},
    {-32.0f, 0.0f, -31.5f, 0.0f, 0.0f, 0.0f},
    {-32.0f, 8.0f, -31.5f, 0.0f, 0.0f, 0.0f},
    {-31.5f, 0.0f, -31.5f, 0.0f, 0.0f, 0.0f},
    {-31.5f, 8.0f, -31.5f, 0.0f, 0.0f, 0.0f},

    {-32.0f, 0.0f, 32.0f, 0.0f, 0.0f, 0.0f},
    {-32.0f, 8.0f, 32.0f, 0.0f, 0.0f, 0.0f},
    {-31.5f, 0.0f, 32.0f, 0.0f, 0.0f, 0.0f},
    {-31.5f, 8.0f, 32.0f, 0.0f, 0.0f, 0.0f},
    {-32.0f, 0.0f, 31.5f, 0.0f, 0.0f, 0.0f},
    {-32.0f, 8.0f, 31.5f, 0.0f, 0.0f, 0.0f},
    {-31.5f, 0.0f, 31.5f, 0.0f, 0.0f, 0.0f},
    {-31.5f, 8.0f, 31.5f, 0.0f, 0.0f, 0.0f},

    {32.0f, 0.0f, 32.0f, 0.0f, 0.0f, 0.0f},
    {32.0f, 8.0f, 32.0f, 0.0f, 0.0f, 0.0f},
    {31.5f, 0.0f, 32.0f, 0.0f, 0.0f, 0.0f},
    {31.5f, 8.0f, 32.0f, 0.0f, 0.0f, 0.0f},
    {32.0f, 0.0f, 31.5f, 0.0f, 0.0f, 0.0f},
    {32.0f, 8.0f, 31.5f, 0.0f, 0.0f, 0.0f},
    {31.5f, 0.0f, 31.5f, 0.0f, 0.0f, 0.0f},
    {31.5f, 8.0f, 31.5f, 0.0f, 0.0f, 0.0f},

    {32.0f, 0.0f, -32.0f, 0.0f, 0.0f, 0.0f},
    {32.0f, 8.0f, -32.0f, 0.0f, 0.0f, 0.0f},
    {31.5f, 0.0f, -32.0f, 0.0f, 0.0f, 0.0f},
    {31.5f, 8.0f, -32.0f, 0.0f, 0.0f, 0.0f},
    {32.0f, 0.0f, -31.5f, 0.0f, 0.0f, 0.0f},
    {32.0f, 8.0f, -31.5f, 0.0f, 0.0f, 0.0f},
    {31.5f, 0.0f, -31.5f, 0.0f, 0.0f, 0.0f},
    {31.5f, 8.0f, -31.5f, 0.0f, 0.0f, 0.0f},
};

constexpr GLuint wallsBoundIndex[] = {
	1, 3, 5,
	3, 5, 7,
	2, 3, 6,
	3, 6, 7,
	4, 5, 6,
	5, 6, 7,

    9, 11, 13,
	11, 13, 15,
	10, 11, 14,
	11, 14, 15,
	12, 13, 14,
	13, 14, 15,

    17, 19, 21,
	19, 21, 23,
	18, 19, 22,
	19, 22, 23,
	20, 21, 22,
	21, 22, 23,

    25, 27, 29,
	27, 29, 31,
	26, 27, 30,
	27, 30, 31,
	28, 29, 30,
	29, 30, 31
};

int main() {
	if (glfwInit() == GL_FALSE) { //初期化
		//終了時のリソース解放なども自動的に行われる
		// exit()やmain以外の場所などで無理に終了させる場合はglfwTerminate()を明示的に呼ぶこと
		std::cerr << "Can't initialize GLFW" << std::endl;
		return 1;
	}

	//GLFWのバージョンを選択(Version 3.3 Core Profile)
	//glfwDefaultWindowHints()でデフォルトに戻せるらしい
	//GPUが対応していない場合は後のglfwCreateWindow()で失敗する
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwSetTime(0.0);

	Window window;

	glClearColor(160.0 / 256, 216.0 / 256, 239.0 / 256, 1.0f); // Windowを塗りつぶす色を設定

	//デプスバッファを有効にする
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);

	//プログラムオブジェクトを作成
	const GLuint normalProgram(loadProgram("../resources/normal.vert", "../resources/normal.frag"));
	const GLuint textureProgram(loadProgram("../resources/texture.vert", "../resources/texture.frag"));

	const GLuint groundTexture(loadBMP("../resources/ground.bmp", GL_TEXTURE0));
	const GLuint wallsTexture(loadBMP("../resources/wall.bmp", GL_TEXTURE1));

	//バーテックスシェーダのuniform変数の場所を取得
	const GLuint normalModelviewLoc(glGetUniformLocation(normalProgram, "modelview"));
	const GLuint normalProjectionLoc(glGetUniformLocation(normalProgram, "projection"));
	const GLuint textureModelviewLoc(glGetUniformLocation(textureProgram, "modelview"));
	const GLuint textureProjectionLoc(glGetUniformLocation(textureProgram, "projection"));
	const GLuint textureTextureLoc(glGetUniformLocation(textureProgram, "texture"));

	//unique_ptrを使うことでptrの削除時にインスタンスも消える
	std::unique_ptr<const Shape> ground(new Shape(3, 4, groundVertex));
	std::unique_ptr<const Shape> walls(new ShapeIndex(3, 8, wallsVertex, 24, wallsIndex));
	std::unique_ptr<const Shape> wallsBound(new ShapeIndex(3, 32, wallsBoundVertex, 72, wallsBoundIndex));

	std::vector<SnowBall> snowBallsVec;

	Player player(1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -10.0f, 10, 3);
	window.setPlayer(&player);

	while (window) {//描画更新
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//カラーバッファをglClearColorで指定した色で塗りつぶす

		if (window.getMouseButton(GLFW_MOUSE_BUTTON_1) != GLFW_RELEASE) {
			SnowBall* ball = player.throwBall(0.3f, 5.5f);
			if (ball != nullptr)snowBallsVec.push_back(*ball);
		}

		//ここから描画処理
		const GLfloat* const size(window.getSize());
		const GLfloat fovy(window.getScale() * 0.01f);//画角(初期値は60度)
		const GLfloat aspect(size[0] / size[1]);
		const Matrix projection(Matrix::perspective(fovy, aspect, 0.1f, 100.0f));

		const Matrix view(player);

		const Matrix modelview(view);

		{//normalProgramでの描画
			glUseProgram(normalProgram);

			// uniform変数の設定
			glUniformMatrix4fv(normalProjectionLoc, 1, GL_FALSE, projection.data());
			glUniformMatrix4fv(normalModelviewLoc, 1, GL_FALSE, modelview.data());

			//描画
			wallsBound->draw(GL_TRIANGLES);
			for (int i = 0; i < snowBallsVec.size(); i++) {
				snowBallsVec[i].update();
				if (!snowBallsVec[i].shouldRemove())snowBallsVec[i].draw();
				else {
					std::vector<SnowBall> evac;
					for (int j = i + 1; j < snowBallsVec.size(); j++)evac.push_back(snowBallsVec[j]);
					for (int j = 0; j <= evac.size(); j++)snowBallsVec.pop_back();
					for (int j = 0; j < evac.size(); j++)snowBallsVec.push_back(evac[j]);
					i--;
				}
			}
		}

		{//textureProgramでの描画
			glUseProgram(textureProgram);

			// uniform変数の設定
			glUniformMatrix4fv(textureProjectionLoc, 1, GL_FALSE, projection.data());
			glUniformMatrix4fv(textureModelviewLoc, 1, GL_FALSE, modelview.data());

			glUniform1i(textureTextureLoc, 0);
			ground->draw(GL_TRIANGLE_STRIP);

			glUniform1i(textureTextureLoc, 1);
			walls->draw(GL_TRIANGLES);
		}

		window.swapBuffers();
	}
}
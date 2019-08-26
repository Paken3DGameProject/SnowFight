#pragma once
#include "base.hpp"
#include "Player.hpp"
class Window {
	GLFWwindow* const window;

	GLfloat size[2]; // windowのサイズ

	GLfloat center[2]; //画面の中心座標

	GLfloat scale; //画面への拡大率、初期値は100(1の長さに対し100画素)

	GLfloat cursor[2]; //マウスの正規化デバイス座標系上での位置

	GLfloat cursorVector[2]; //マウスの中心からのベクトル

	int keyStatus; //キーボード操作の状態

	Player* player; //操作するプレーヤー

  public:
	Window(int width = 640, int height = 480, const char* title = "SnowFight"); //コンストラクタ

	static void resize(GLFWwindow* const window, int width, int height); // Windowをリサイズする

	inline virtual ~Window() {
		glfwDestroyWindow(window); // windowの削除
	}

	explicit operator bool();

	inline void swapBuffers() const { //カラーバッファを入れ替える
		glfwSwapBuffers(window);
	}

	// Windowのサイズを取得
	const GLfloat* getSize() const {
		return size;
	}
	// Windowの拡大率を取得
	const GLfloat getScale() const {
		return scale;
	}
	//ホイール操作で呼ばれる関数
	static void wheel(GLFWwindow* window, double x, double y);
	//キーボード操作で呼ばれる関数
	static void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods);
	//操作するPlayerをセット
	void setPlayer(Player* player);
	//ボタンが押されているか
	int getMouseButton(int button);
};
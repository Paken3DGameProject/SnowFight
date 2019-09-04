#include "Window.hpp"
Window::Window(int width, int height, const char *title) : window(glfwCreateWindow(width, height, title, NULL, NULL)),
                                                           scale(100.0f), keyStatus(GLFW_RELEASE), player(NULL) {
    if (window == NULL) { // windowの作成に失敗
        std::cerr << "Can't create GLFW Window." << std::endl;
        exit(1);
    }

    glfwMakeContextCurrent(window); //現在のウィンドウを処理対象にする

    glewExperimental = GL_TRUE;  // GLEWの初期化に必要
    if (glewInit() != GLEW_OK) { // GLEWを初期化
        std::cerr << "Can't initialize GLEW" << std::endl;
        exit(1);
    }

    glfwSwapInterval(1); //バッファ入れ替えを待つタイミング、0にするとティアリングするので1でよい

    glfwSetWindowUserPointer(window, this); // windowに対してthisを記録しておく

    glfwSetWindowSizeCallback(window, resize); // windowのsizeが変わったときにresizeを呼ぶ

    glfwSetScrollCallback(window, wheel); //ホイールに操作があったときwheelを呼ぶ

    glfwSetKeyCallback(window, keyboard);

    resize(window, width, height);
}

Window::operator bool() {
    glfwPollEvents(); //イベントを待たないで取り出す

    double x, y;
    glfwGetCursorPos(window, &x, &y); //マウスカーソルの位置を取得

    //正規化デバイス座標系上の座標に変換
    cursor[0] = static_cast<GLfloat>(x) * 2.0f / size[0] - 1.0f;
    cursor[1] = 1.0f - static_cast<GLfloat>(y) * 2.0f / size[1];

    //適当な数をかけて回す
    player->rotate(-cursor[0] * 5.0f, cursor[1] * 5.0f);

    //プレイヤーの移動
    GLfloat direction[2] = {0, 0};//動く方向のベクトル
    if (glfwGetKey(window, GLFW_KEY_A)) { //左側を向いたベクトル(x,z)を求める
        direction[0] += *(player->getDirection() + 2);
        direction[1] += -*(player->getDirection());
    }
    if (glfwGetKey(window, GLFW_KEY_W)) { //同様
        direction[0] += *(player->getDirection());
        direction[1] += *(player->getDirection() + 2);
    }
    if (glfwGetKey(window, GLFW_KEY_D)) { //同様
        direction[0] += -*(player->getDirection() + 2);
        direction[1] += *(player->getDirection());
    }
    if (glfwGetKey(window, GLFW_KEY_S)) { //同様
        direction[0] += -*(player->getDirection());
        direction[1] += -*(player->getDirection() + 2);
    }
	if (glfwGetKey(window, GLFW_KEY_SPACE)) player->jump();
	if (direction[0] || direction[1]) {
		//ベクトルの長さを適当に直す
		GLfloat mag(0.2f / static_cast<GLfloat>(hypot(direction[0], direction[1])));
		direction[0] *= mag;
		direction[1] *= mag;

		//動かす
		player->move(direction[0], 0, direction[1]);
	}
	else
		player->move(0, 0, 0);

    return !glfwWindowShouldClose(window) &&
           !glfwGetKey(window, GLFW_KEY_ESCAPE); //ウィンドウを閉じる必要がなく、Escapeが押されてなければtrueを返す
}

void Window::resize(GLFWwindow *const window, int width, int height) { //ビューポートのresizeを行う
    //フレームバッファのサイズを調べる
    // retinaディスプレイではフレームバッファとwindowのサイズが違うことがある
    int fbwidth, fbheight;
    glfwGetFramebufferSize(window, &fbwidth, &fbheight);

    glViewport(0, 0, fbwidth, fbheight); //ビューポートの設定

    Window *const instance(static_cast<Window *>(glfwGetWindowUserPointer(window)));

    if (instance != NULL) {
        // sizeの更新
        instance->size[0] = static_cast<GLfloat>(width);
        instance->size[1] = static_cast<GLfloat>(height);

        // centerの更新
        instance->center[0] = instance->size[0] / 2.0f;
        instance->center[1] = instance->size[1] / 2.0f;
    }
}

void Window::wheel(GLFWwindow *window, double x, double y) {
    //インスタンスのポインタを得る
    Window *const instance(static_cast<Window *>(glfwGetWindowUserPointer(window)));

    if (instance != NULL) {
        //拡大率を上げる
        instance->scale += static_cast<GLfloat>(y);
    }
}

void Window::keyboard(GLFWwindow *window, int key, int scancode, int action, int mods) {
    //インスタンスのポインタを得る
    Window *const instance(static_cast<Window *>(glfwGetWindowUserPointer(window)));

    if (instance != NULL) {
        // keyStatusに状態を代入
        instance->keyStatus = action;
    }
}

void Window::setPlayer(Player *player) {
    this->player = player;
}

int Window::getMouseButton(int button) {
    return glfwGetMouseButton(window, button);
}

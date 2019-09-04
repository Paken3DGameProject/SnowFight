#include "Window.hpp"
Window::Window(int width, int height, const char *title) : window(glfwCreateWindow(width, height, title, NULL, NULL)),
                                                           scale(100.0f), keyStatus(GLFW_RELEASE), player(NULL) {
    if (window == NULL) { // window�̍쐬�Ɏ��s
        std::cerr << "Can't create GLFW Window." << std::endl;
        exit(1);
    }

    glfwMakeContextCurrent(window); //���݂̃E�B���h�E�������Ώۂɂ���

    glewExperimental = GL_TRUE;  // GLEW�̏������ɕK�v
    if (glewInit() != GLEW_OK) { // GLEW��������
        std::cerr << "Can't initialize GLEW" << std::endl;
        exit(1);
    }

    glfwSwapInterval(1); //�o�b�t�@����ւ���҂^�C�~���O�A0�ɂ���ƃe�B�A�����O����̂�1�ł悢

    glfwSetWindowUserPointer(window, this); // window�ɑ΂���this���L�^���Ă���

    glfwSetWindowSizeCallback(window, resize); // window��size���ς�����Ƃ���resize���Ă�

    glfwSetScrollCallback(window, wheel); //�z�C�[���ɑ��삪�������Ƃ�wheel���Ă�

    glfwSetKeyCallback(window, keyboard);

    resize(window, width, height);
}

Window::operator bool() {
    glfwPollEvents(); //�C�x���g��҂��Ȃ��Ŏ��o��

    double x, y;
    glfwGetCursorPos(window, &x, &y); //�}�E�X�J�[�\���̈ʒu���擾

    //���K���f�o�C�X���W�n��̍��W�ɕϊ�
    cursor[0] = static_cast<GLfloat>(x) * 2.0f / size[0] - 1.0f;
    cursor[1] = 1.0f - static_cast<GLfloat>(y) * 2.0f / size[1];

    //�K���Ȑ��������ĉ�
    player->rotate(-cursor[0] * 5.0f, cursor[1] * 5.0f);

    //�v���C���[�̈ړ�
    GLfloat direction[2] = {0, 0};//���������̃x�N�g��
    if (glfwGetKey(window, GLFW_KEY_A)) { //�������������x�N�g��(x,z)�����߂�
        direction[0] += *(player->getDirection() + 2);
        direction[1] += -*(player->getDirection());
    }
    if (glfwGetKey(window, GLFW_KEY_W)) { //���l
        direction[0] += *(player->getDirection());
        direction[1] += *(player->getDirection() + 2);
    }
    if (glfwGetKey(window, GLFW_KEY_D)) { //���l
        direction[0] += -*(player->getDirection() + 2);
        direction[1] += *(player->getDirection());
    }
    if (glfwGetKey(window, GLFW_KEY_S)) { //���l
        direction[0] += -*(player->getDirection());
        direction[1] += -*(player->getDirection() + 2);
    }
	if (glfwGetKey(window, GLFW_KEY_SPACE)) player->jump();
	if (direction[0] || direction[1]) {
		//�x�N�g���̒�����K���ɒ���
		GLfloat mag(0.2f / static_cast<GLfloat>(hypot(direction[0], direction[1])));
		direction[0] *= mag;
		direction[1] *= mag;

		//������
		player->move(direction[0], 0, direction[1]);
	}
	else
		player->move(0, 0, 0);

    return !glfwWindowShouldClose(window) &&
           !glfwGetKey(window, GLFW_KEY_ESCAPE); //�E�B���h�E�����K�v���Ȃ��AEscape��������ĂȂ����true��Ԃ�
}

void Window::resize(GLFWwindow *const window, int width, int height) { //�r���[�|�[�g��resize���s��
    //�t���[���o�b�t�@�̃T�C�Y�𒲂ׂ�
    // retina�f�B�X�v���C�ł̓t���[���o�b�t�@��window�̃T�C�Y���Ⴄ���Ƃ�����
    int fbwidth, fbheight;
    glfwGetFramebufferSize(window, &fbwidth, &fbheight);

    glViewport(0, 0, fbwidth, fbheight); //�r���[�|�[�g�̐ݒ�

    Window *const instance(static_cast<Window *>(glfwGetWindowUserPointer(window)));

    if (instance != NULL) {
        // size�̍X�V
        instance->size[0] = static_cast<GLfloat>(width);
        instance->size[1] = static_cast<GLfloat>(height);

        // center�̍X�V
        instance->center[0] = instance->size[0] / 2.0f;
        instance->center[1] = instance->size[1] / 2.0f;
    }
}

void Window::wheel(GLFWwindow *window, double x, double y) {
    //�C���X�^���X�̃|�C���^�𓾂�
    Window *const instance(static_cast<Window *>(glfwGetWindowUserPointer(window)));

    if (instance != NULL) {
        //�g�嗦���グ��
        instance->scale += static_cast<GLfloat>(y);
    }
}

void Window::keyboard(GLFWwindow *window, int key, int scancode, int action, int mods) {
    //�C���X�^���X�̃|�C���^�𓾂�
    Window *const instance(static_cast<Window *>(glfwGetWindowUserPointer(window)));

    if (instance != NULL) {
        // keyStatus�ɏ�Ԃ���
        instance->keyStatus = action;
    }
}

void Window::setPlayer(Player *player) {
    this->player = player;
}

int Window::getMouseButton(int button) {
    return glfwGetMouseButton(window, button);
}

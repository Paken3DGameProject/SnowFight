#pragma once
#include "base.hpp"
#include "Player.hpp"
class Window {
	GLFWwindow* const window;

	GLfloat size[2]; // window�̃T�C�Y

	GLfloat center[2]; //��ʂ̒��S���W

	GLfloat scale; //��ʂւ̊g�嗦�A�����l��100(1�̒����ɑ΂�100��f)

	GLfloat cursor[2]; //�}�E�X�̐��K���f�o�C�X���W�n��ł̈ʒu

	GLfloat cursorVector[2]; //�}�E�X�̒��S����̃x�N�g��

	int keyStatus; //�L�[�{�[�h����̏��

	Player* player; //���삷��v���[���[

  public:
	Window(int width = 640, int height = 480, const char* title = "SnowFight"); //�R���X�g���N�^

	static void resize(GLFWwindow* const window, int width, int height); // Window�����T�C�Y����

	inline virtual ~Window() {
		glfwDestroyWindow(window); // window�̍폜
	}

	explicit operator bool();

	inline void swapBuffers() const { //�J���[�o�b�t�@�����ւ���
		glfwSwapBuffers(window);
	}

	// Window�̃T�C�Y���擾
	const GLfloat* getSize() const {
		return size;
	}
	// Window�̊g�嗦���擾
	const GLfloat getScale() const {
		return scale;
	}
	//�z�C�[������ŌĂ΂��֐�
	static void wheel(GLFWwindow* window, double x, double y);
	//�L�[�{�[�h����ŌĂ΂��֐�
	static void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods);
	//���삷��Player���Z�b�g
	void setPlayer(Player* player);
	//�{�^����������Ă��邩
	int getMouseButton(int button);
};
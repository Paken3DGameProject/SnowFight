#version 150 core//GLSL�̃o�[�W�������w��
//in�ϐ��͒��_���ƁAuniform�ϐ��͕`�施�߂��Ƃ�CPU���瑗���Ă���
uniform mat4 modelview;
uniform mat4 projection;
in vec4 position;
in vec4 color;
//�F�f�[�^���t���O�����g�V�F�[�_�ɓn��
out vec4 vertex_color;
void main(){
	vertex_color=color;
	gl_Position=projection*modelview*position;
}

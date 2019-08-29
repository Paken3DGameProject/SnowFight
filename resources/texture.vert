#version 150 core//GLSL�̃o�[�W�������w��
//in�ϐ��͒��_���ƁAuniform�ϐ��͕`�施�߂��Ƃ�CPU���瑗���Ă���
uniform mat4 modelview;
uniform mat4 projection;
uniform sampler2D texture; 
in vec4 position;
in vec2 UV;
//�F�f�[�^���t���O�����g�V�F�[�_�ɓn��
out vec4 vertex_color;
void main(){
	vertex_color=vec4(texture2D(texture,UV).rgb,1.0f);
	gl_Position=projection*modelview*position;
}

#version 330 core//GLSL�̃o�[�W�������w��
//in�ϐ��͒��_���ƁAuniform�ϐ��͕`�施�߂��Ƃ�CPU���瑗���Ă���
uniform mat4 modelview;
uniform mat4 projection;
layout(location=0) in vec4 position;
layout(location=1) in vec2 vertexUV;

out vec2 UV;
void main(){
	gl_Position=projection*modelview*position;
	UV=vertexUV;
}

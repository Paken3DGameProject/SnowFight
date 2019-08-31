#version 460 core//GLSLのバージョンを指定
in vec4 vertex_color;
out vec4 fragment;
void main(){
	fragment=vertex_color;
}

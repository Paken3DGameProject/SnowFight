#version 330 core//GLSLのバージョンを指定
in vec2 UV;
uniform sampler2D texture;
out vec4 fragment;
void main(){
	fragment=texture2D(texture,UV);
}

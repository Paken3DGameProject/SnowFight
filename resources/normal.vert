#version 460 core//GLSLのバージョンを指定
//in変数は頂点ごと、uniform変数は描画命令ごとにCPUから送られてくる
uniform mat4 modelview;
uniform mat4 projection;
layout(location=0) in vec4 position;
layout(location=1) in vec4 color;
//色データをフラグメントシェーダに渡す
out vec4 vertex_color;
void main(){
	vertex_color=color;
	gl_Position=projection*modelview*position;
}

#version 150 core//GLSLのバージョンを指定
//in変数は頂点ごと、uniform変数は描画命令ごとにCPUから送られてくる
uniform mat4 modelview;
uniform mat4 projection;
uniform sampler2D texture; 
in vec4 position;
in vec2 UV;
//色データをフラグメントシェーダに渡す
out vec4 vertex_color;
void main(){
	vertex_color=vec4(texture2D(texture,UV).rgb,1.0f);
	gl_Position=projection*modelview*position;
}

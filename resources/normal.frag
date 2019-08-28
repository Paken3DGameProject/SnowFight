#version 150 core//GLSLのバージョンを指定
in vec4 vertex_color;
out vec4 fragment;//この変数がカラーバッファに格納される
void main(){
	//fragmentに色情報を代入する
	fragment=vertex_color;//(R,G,B,透明度)
}

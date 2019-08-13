#version 150 core//GLSLのバージョンを指定
out vec4 fragment;//この変数がカラーバッファに格納される
void main(){
	//fragmentに色情報を代入する
	fragment=vec4(1.0,0.0,0.0,1.0);//(R,G,B,透明度)
}

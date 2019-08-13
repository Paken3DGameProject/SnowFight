#version 150 core//GLSLのバージョンを指定
in vec4 position;//レンダリングの過程で送られてくる変数を宣言する
void main(){
	//組み込み変数gl_positionに頂点の情報を代入する
	gl_Position=position;
}

#pragma once
//シェーダプログラムをロードして使う
#include <iostream>
#include <fstream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

GLboolean printShaderInfoLog(GLuint shader, const char* str) {//コンパイル結果を表示する

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);//シェーダオブジェクトの情報を取得
	if (status == GL_FALSE)std::cerr << "Compile Error in" << str << std::endl;

	GLsizei bufSize;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &bufSize);//コンパイルログの長さを取得

	if (bufSize > 1) {
		std::vector<GLchar> infoLog(bufSize);
		GLsizei length;
		glGetShaderInfoLog(shader, bufSize, &length, &infoLog[0]);//コンパイルログを取り出す
		std::cerr << &infoLog[0] << std::endl;
	}

	return static_cast<GLboolean>(status);
}

GLboolean printProgramInfoLog(GLuint program){//リンク結果を表示する

	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);//リンク結果を取得
	if (status == GL_FALSE) std::cerr << "Link Error." << std::endl;

	GLsizei bufSize;
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufSize);//リンクログの長さを取得

	if (bufSize > 1){
		std::vector<GLchar> infoLog(bufSize);
		GLsizei length;
		glGetProgramInfoLog(program, bufSize, &length, &infoLog[0]);//リンクログを取り出す
		std::cerr << &infoLog[0] << std::endl;
	}

	return static_cast<GLboolean>(status);
}

bool readShaderSource(const char* name, std::vector<GLchar>& buffer) {//シェーダファイルを読み込む

	if (name == NULL)return false;

	std::ifstream file(name, std::ios::binary);
	if (file.fail()) {//開くのに失敗した
		std::cerr << "Error: Can't open source file: " << name << std::endl;
		return false;
	}

	file.seekg(0L, std::ios::end);//末尾まで移動
	GLsizei length = static_cast<GLsizei>(file.tellg());//長さを得る

	buffer.resize(length + 1);//bufferのサイズを確保

	file.seekg(0L, std::ios::beg);
	file.read(buffer.data(), length);
	buffer[length] = '\0';

	if (file.fail()) {//読み込みに失敗
		std::cerr << "Error: Could not read souce file: " << name << std::endl;
		file.close();
		return false;
	}

	file.close();
	return true;
}

GLuint createProgram(const char* vsrc, const char* fsrc) {

	const GLuint program(glCreateProgram());//空のプログラムオブジェクトを作成、失敗なら0を返す

	if (vsrc != NULL) {
		//プログラムからシェーダオブジェクトを生成してコンパイル
		const GLuint vobj(glCreateShader(GL_VERTEX_SHADER));
		glShaderSource(vobj, 1, &vsrc, NULL);
		glCompileShader(vobj);

		glAttachShader(program, vobj);//プログラムにシェーダオブジェクトをアタッチ(逆はglDetachShader)
		glDeleteShader(vobj);//シェーダオブジェクトに削除マークを付け、どこでも使われなくなったら即消す
	}

	if (fsrc != NULL) {
		//上と同様
		const GLuint fobj(glCreateShader(GL_FRAGMENT_SHADER));
		glShaderSource(fobj, 1, &fsrc, NULL);
		glCompileShader(fobj);

		glAttachShader(program, fobj);
		glDeleteShader(fobj);
	}

	glBindAttribLocation(program, 0, "position");//バーテックスシェーダの入力のindexを設定
	glBindFragDataLocation(program, 0, "fragment");//フラグメントシェーダの出力のindexを設定
	//これらはGPUのレジスタ番号に相当する

	//プログラムオブジェクトをリンク
	glLinkProgram(program);

	return program;
}

GLuint loadProgram(const char* vert, const char* frag){//プログラムオブジェクトをファイル名から作成
	//シェーダファイルを読み込む
	std::vector<GLchar> vsrc;
	const bool vstat(readShaderSource(vert, vsrc));
	std::vector<GLchar> fsrc;
	const bool fstat(readShaderSource(frag, fsrc));

	//プログラムオブジェクトを作成する
	return vstat && fstat ? createProgram(vsrc.data(), fsrc.data()) : 0;
}
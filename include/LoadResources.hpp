#pragma once

#include "Base.hpp"
#include <GLFW/glfw3.h>
#include <GL/glew.h>

GLboolean printShaderInfoLog(GLuint shader, const char *str); //シェーダのコンパイル結果を表示する

GLboolean printProgramInfoLog(GLuint program); //リンク結果を表示する

bool readShaderSource(const char *name, std::vector<GLchar> &buffer); //シェーダファイルを読み込む

GLuint createProgram(const char *vsrc, const char *fsrc); //プログラムオブジェクトを作成

GLuint loadProgram(const char *vert, const char *frag); //プログラムオブジェクトをファイル名から作成

GLuint loadBMP(const char* imagePath, GLenum unit);
//リソースをロードして使う
#include "LoadResources.hpp"

GLboolean printShaderInfoLog(GLuint shader, const char *str) {
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status); //シェーダオブジェクトの情報を取得
    if (status == GL_FALSE) std::cerr << "Compile Error in " << str << std::endl;

    GLsizei bufSize;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &bufSize); //コンパイルログの長さを取得

    if (bufSize > 1) {
        std::vector<GLchar> infoLog(bufSize);
        GLsizei length;
        glGetShaderInfoLog(shader, bufSize, &length, &infoLog[0]); //コンパイルログを取り出す
        std::cerr << &infoLog[0] << std::endl;
    }

    return static_cast<GLboolean>(status);
}

GLboolean printProgramInfoLog(GLuint program) {
    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status); //リンク結果を取得
    if (status == GL_FALSE) std::cerr << "Link Error." << std::endl;

    GLsizei bufSize;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufSize); //リンクログの長さを取得

    if (bufSize > 1) {
        std::vector<GLchar> infoLog(bufSize);
        GLsizei length;
        glGetProgramInfoLog(program, bufSize, &length, &infoLog[0]); //リンクログを取り出す
        std::cerr << &infoLog[0] << std::endl;
    }

    return static_cast<GLboolean>(status);
}

bool readShaderSource(const char *name, std::vector<GLchar> &buffer) {
    if (name == NULL) return false;

    std::ifstream file(name, std::ios::binary);
    if (file.fail()) { //開くのに失敗した
        std::cerr << "Error: Can't open source file: " << name << std::endl;
        return false;
    }

    file.seekg(0L, std::ios::end);                       //末尾まで移動
    GLsizei length = static_cast<GLsizei>(file.tellg()); //長さを得る

    buffer.resize(length + 1); // bufferのサイズを確保

    file.seekg(0L, std::ios::beg);
    file.read(buffer.data(), length);
    buffer[length] = '\0';

    if (file.fail()) { //読み込みに失敗
        std::cerr << "Error: Could not read souce file: " << name << std::endl;
        file.close();
        return false;
    }

    file.close();
    return true;
}

GLuint createProgram(const char *vsrc, const char *fsrc) {
    const GLuint program(glCreateProgram()); //空のプログラムオブジェクトを作成、失敗なら0を返す

    if (vsrc != NULL) {
        //プログラムからシェーダオブジェクトを生成してコンパイル
        const GLuint vobj(glCreateShader(GL_VERTEX_SHADER));
        glShaderSource(vobj, 1, &vsrc, NULL);
        glCompileShader(vobj);

        if (printShaderInfoLog(vobj, "vertex shader")) glAttachShader(program, vobj); //プログラムにシェーダオブジェクトをアタッチ(逆はglDetachShader)
        glDeleteShader(vobj);                                                         //シェーダオブジェクトに削除マークを付け、どこでも使われなくなったら即消す
    }

    if (fsrc != NULL) {
        //上と同様
        const GLuint fobj(glCreateShader(GL_FRAGMENT_SHADER));
        glShaderSource(fobj, 1, &fsrc, NULL);
        glCompileShader(fobj);

        if (printShaderInfoLog(fobj, "fragment shader")) glAttachShader(program, fobj);
        glDeleteShader(fobj);
    }

	glBindFragDataLocation(program, 0, "fragment");

    //プログラムオブジェクトをリンク
    glLinkProgram(program);

    if (printProgramInfoLog(program)) return program;
    glDeleteProgram(program);
    return 0;
}

GLuint loadProgram(const char *vert, const char *frag) {
    //シェーダファイルを読み込む
    std::vector<GLchar> vsrc;
    const bool vstat(readShaderSource(vert, vsrc));
    std::vector<GLchar> fsrc;
    const bool fstat(readShaderSource(frag, fsrc));

    //プログラムオブジェクトを作成する
    return vstat && fstat ? createProgram(vsrc.data(), fsrc.data()) : 0;
}

GLuint loadBMP(const char* imagePath, GLenum unit) {
	//ヘッダのデータ
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int height, width;
	unsigned int imageSize;
	//実際のRGBデータ
	unsigned char* data;

	FILE* file = fopen(imagePath, "rb");
	if (!file) {
		std::cerr << "Can't open image file" << std::endl;
		return 0;
	}
	if (fread(header, 1, 54, file) != 54) {//ヘッダ読み込み
		std::cerr << "The file is not BMP" << std::endl;
		return false;
	}

	//データの読み込み
	dataPos = *(int*) & (header[0x0A]);
	imageSize = *(int*) & (header[0x22]);
	width = *(int*) & (header[0x12]);
	height = *(int*) & (header[0x16]);

	//ミスフォーマットを補足
	if (imageSize == 0)imageSize = width * height * 3;
	if (dataPos == 0)dataPos = 54;

	data = new unsigned char[imageSize];//バッファを作る
	fread(data, 1, imageSize, file);//バッファに読み込む
	fclose(file);//ファイルを閉じる

	glActiveTexture(unit);
	//テクスチャオブジェクトを作る
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	return textureID;
}
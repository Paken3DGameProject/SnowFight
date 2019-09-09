//���\�[�X�����[�h���Ďg��
#include "LoadResources.hpp"

GLboolean printShaderInfoLog(GLuint shader, const char *str) {
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status); //�V�F�[�_�I�u�W�F�N�g�̏����擾
    if (status == GL_FALSE) std::cerr << "Compile Error in " << str << std::endl;

    GLsizei bufSize;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &bufSize); //�R���p�C�����O�̒������擾

    if (bufSize > 1) {
        std::vector<GLchar> infoLog(bufSize);
        GLsizei length;
        glGetShaderInfoLog(shader, bufSize, &length, &infoLog[0]); //�R���p�C�����O�����o��
        std::cerr << &infoLog[0] << std::endl;
    }

    return static_cast<GLboolean>(status);
}

GLboolean printProgramInfoLog(GLuint program) {
    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status); //�����N���ʂ��擾
    if (status == GL_FALSE) std::cerr << "Link Error." << std::endl;

    GLsizei bufSize;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufSize); //�����N���O�̒������擾

    if (bufSize > 1) {
        std::vector<GLchar> infoLog(bufSize);
        GLsizei length;
        glGetProgramInfoLog(program, bufSize, &length, &infoLog[0]); //�����N���O�����o��
        std::cerr << &infoLog[0] << std::endl;
    }

    return static_cast<GLboolean>(status);
}

bool readShaderSource(const char *name, std::vector<GLchar> &buffer) {
    if (name == NULL) return false;

    std::ifstream file(name, std::ios::binary);
    if (file.fail()) { //�J���̂Ɏ��s����
        std::cerr << "Error: Can't open source file: " << name << std::endl;
        return false;
    }

    file.seekg(0L, std::ios::end);                       //�����܂ňړ�
    GLsizei length = static_cast<GLsizei>(file.tellg()); //�����𓾂�

    buffer.resize(length + 1); // buffer�̃T�C�Y���m��

    file.seekg(0L, std::ios::beg);
    file.read(buffer.data(), length);
    buffer[length] = '\0';

    if (file.fail()) { //�ǂݍ��݂Ɏ��s
        std::cerr << "Error: Could not read souce file: " << name << std::endl;
        file.close();
        return false;
    }

    file.close();
    return true;
}

GLuint createProgram(const char *vsrc, const char *fsrc) {
    const GLuint program(glCreateProgram()); //��̃v���O�����I�u�W�F�N�g���쐬�A���s�Ȃ�0��Ԃ�

    if (vsrc != NULL) {
        //�v���O��������V�F�[�_�I�u�W�F�N�g�𐶐����ăR���p�C��
        const GLuint vobj(glCreateShader(GL_VERTEX_SHADER));
        glShaderSource(vobj, 1, &vsrc, NULL);
        glCompileShader(vobj);

        if (printShaderInfoLog(vobj, "vertex shader")) glAttachShader(program, vobj); //�v���O�����ɃV�F�[�_�I�u�W�F�N�g���A�^�b�`(�t��glDetachShader)
        glDeleteShader(vobj);                                                         //�V�F�[�_�I�u�W�F�N�g�ɍ폜�}�[�N��t���A�ǂ��ł��g���Ȃ��Ȃ����瑦����
    }

    if (fsrc != NULL) {
        //��Ɠ��l
        const GLuint fobj(glCreateShader(GL_FRAGMENT_SHADER));
        glShaderSource(fobj, 1, &fsrc, NULL);
        glCompileShader(fobj);

        if (printShaderInfoLog(fobj, "fragment shader")) glAttachShader(program, fobj);
        glDeleteShader(fobj);
    }

	glBindFragDataLocation(program, 0, "fragment");

    //�v���O�����I�u�W�F�N�g�������N
    glLinkProgram(program);

    if (printProgramInfoLog(program)) return program;
    glDeleteProgram(program);
    return 0;
}

GLuint loadProgram(const char *vert, const char *frag) {
    //�V�F�[�_�t�@�C����ǂݍ���
    std::vector<GLchar> vsrc;
    const bool vstat(readShaderSource(vert, vsrc));
    std::vector<GLchar> fsrc;
    const bool fstat(readShaderSource(frag, fsrc));

    //�v���O�����I�u�W�F�N�g���쐬����
    return vstat && fstat ? createProgram(vsrc.data(), fsrc.data()) : 0;
}

GLuint loadBMP(const char* imagePath, GLenum unit) {
	//�w�b�_�̃f�[�^
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int height, width;
	unsigned int imageSize;
	//���ۂ�RGB�f�[�^
	unsigned char* data;

	FILE* file = fopen(imagePath, "rb");
	if (!file) {
		std::cerr << "Can't open image file" << std::endl;
		return 0;
	}
	if (fread(header, 1, 54, file) != 54) {//�w�b�_�ǂݍ���
		std::cerr << "The file is not BMP" << std::endl;
		return false;
	}

	//�f�[�^�̓ǂݍ���
	dataPos = *(int*) & (header[0x0A]);
	imageSize = *(int*) & (header[0x22]);
	width = *(int*) & (header[0x12]);
	height = *(int*) & (header[0x16]);

	//�~�X�t�H�[�}�b�g��⑫
	if (imageSize == 0)imageSize = width * height * 3;
	if (dataPos == 0)dataPos = 54;

	data = new unsigned char[imageSize];//�o�b�t�@�����
	fread(data, 1, imageSize, file);//�o�b�t�@�ɓǂݍ���
	fclose(file);//�t�@�C�������

	glActiveTexture(unit);
	//�e�N�X�`���I�u�W�F�N�g�����
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	return textureID;
}
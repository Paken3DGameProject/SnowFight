#version 150 core//GLSL�̃o�[�W�������w��
in vec4 position;//�����_�����O�̉ߒ��ő����Ă���ϐ���錾����
void main(){
	//�g�ݍ��ݕϐ�gl_position�ɒ��_�̏���������
	gl_Position=position;
}

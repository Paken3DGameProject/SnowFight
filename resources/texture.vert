#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 vertexUV;

out vec2 UV;

uniform mat4 modelview;
uniform mat4 projection;

void main(){
	gl_Position=projection*modelview*position;
	UV=vertexUV;
}
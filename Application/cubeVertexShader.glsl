#version 440
layout (location = 0) in vec3 vs_position;
layout (location = 1) in vec3 vs_normal;
layout (location = 2) in vec2 vs_texcoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec2 cb_texcoord;

void main(){
	gl_Position = projectionMatrix*viewMatrix*modelMatrix*vec4(vs_position,1.f);
	cb_texcoord = vs_texcoord;
}


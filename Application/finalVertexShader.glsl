#version 440
layout(location=0) in vec4 vs_positon;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec2 vs_texcoord;

void main(){
	gl_Position = projectionMatrix*viewMatrix*modelMatrix*vec4(vs_positon.xy,0.f,1.f);
	vs_texcoord = vs_positon.xy;
}
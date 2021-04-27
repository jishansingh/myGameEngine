#version 440
layout(location=0) in vec4 vs_positon;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec2 vs_texcoord;
out vec4 cb_pos;
out vec4 cb_normal;

void main(){
	cb_pos =  projectionMatrix*viewMatrix*modelMatrix*vec4(vs_positon.xy,0.f,1.f);
	gl_Position = cb_pos;
	vs_texcoord = vs_positon.zw;
	//cb_pos = modelMatrix*vec4(vs_positon.xy,0.f,1.f);
	cb_normal = vec4(0.f,1.f,0.f,0.f);
}
#version 440

layout(location=0) out vec4 fs_color;


in vec2 cb_texcoord;
in vec4 cb_pos;
in vec3 cb_normal;

uniform sampler2D texture0;

void main(){
	fs_color = vec4(1.f,0.f,0.f,1.f);
}

#version 440

layout(location=0) out vec4 fs_color;
layout(location=1) out vec4 fs_position;
layout(location=2) out vec4 fs_normal;


in vec2 cb_texcoord;
in vec4 cb_pos;
in vec3 cb_normal;

uniform sampler2D texture0;

void main(){
	fs_position = cb_pos;
	fs_normal = vec4(cb_normal,0.f);
	fs_color = texture(texture0,cb_texcoord);
}

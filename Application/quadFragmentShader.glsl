#version 440

layout(location=0) out vec4 fs_color;
layout(location=1) out vec4 fs_position;
layout(location=2) out vec4 fs_normal;

in vec2 vs_texcoord;
in vec4 cb_pos;
in vec4 cb_normal;

uniform sampler2D texture0;
void main(){
	//fs_color=vec4(1.f,0.f,0.f,1.f);
	fs_color = texture(texture0,vs_texcoord*100);
	fs_position = 0.5*cb_pos+0.5f;
	fs_normal = cb_normal;

}

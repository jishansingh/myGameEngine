#version 440

out vec4 fs_color;

in vec2 cb_texcoord;
uniform sampler2D texture0;

void main(){
	fs_color = texture(texture0,cb_texcoord);
}

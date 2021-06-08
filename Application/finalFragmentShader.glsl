#version 440

in vec2 vs_texcoord;

out vec4 fs_color;

uniform sampler2D texture0;
void main(){
	//fs_color=vec4(1.f,0.f,0.f,1.f);
	//float dep = texture(texture0,vs_texcoord).r;
	//fs_color = vec4(vec3(dep),1.f);
	fs_color = texture(texture0,vs_texcoord);
	//gl_FragDepth = 100.f;
}



#version 440
layout(location=0) out vec4 fs_color;
layout(location=1) out vec4 fs_position;
layout(location=2) out vec4 fs_normal;

in vec2 fs_texcoord;

//out vec4 fs_color;
struct Material{
	sampler2D diffuseTex;
	sampler2D specularTex;
};

in vec4 cb_pos;
in vec3 cb_normal;

uniform Material material0;
void main(){
	
	fs_color = texture(material0.diffuseTex,fs_texcoord);
	//fs_color += texture(material0.specularTex,fs_texcoord)*0.6;
	/*if(material0.specularTex){
		fs_color = texture(material0.specularTex,fs_texcoord);
	}*/
	//fs_color = vec4(1.f,0.f,0.f,1.f);
	fs_position = cb_pos;
	fs_normal = vec4(cb_normal,0.f);

	
}

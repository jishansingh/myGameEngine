#version 440
layout (location = 0) out vec4 fs_color;
in vec2 fs_texcoord;

//out vec4 fs_color;
struct Material{
	sampler2D diffuseTex;
	sampler2D specularTex;
};


uniform Material material0;
void main(){
	
	fs_color = texture(material0.diffuseTex,fs_texcoord);
	//fs_color += texture(material0.specularTex,fs_texcoord)*0.6;
	/*if(material0.specularTex){
		fs_color = texture(material0.specularTex,fs_texcoord);
	}*/
	
}

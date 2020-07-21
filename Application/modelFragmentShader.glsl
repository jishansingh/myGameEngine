#version 440

in vec2 fs_texcoord;

out vec4 fs_color;
struct Material{
	sampler2D diffuseTex;
	sampler2D specularTex;
};
uniform Material material0;
void main(){
	//fs_color=vec4(1.f,0.f,0.f,1.f);
	fs_color = texture(material0.diffuseTex,fs_texcoord);
	//fs_color += texture(material0.specularTex,fs_texcoord)*0.6;
	/*if(material0.specularTex){
		fs_color = texture(material0.specularTex,fs_texcoord);
	}*/
	
}

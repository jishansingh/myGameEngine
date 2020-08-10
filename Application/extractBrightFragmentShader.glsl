#version 440
//layout (location = 0) out vec4 fs_color;
in vec2 vs_texcoord;

out vec4 fs_color;

uniform sampler2D texture0;
void main(){
	fs_color = vec4(0.1f,0.1f,0.1f,1.f);
	fs_color = texture(texture0,vs_texcoord);
	/*if(texture(texture0,vs_texcoord).r>0.7f){
		fs_color = texture(texture0,vs_texcoord);
	}*/
	//fs_color += texture(material0.specularTex,fs_texcoord)*0.6;
	/*if(material0.specularTex){
		fs_color = texture(material0.specularTex,fs_texcoord);
	}*/
	//fs_color = vec4(1.f,0.f,0.f,1.f);
	//gl_FragDepth = gl_FragCoord.z;
	
}

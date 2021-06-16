#version 440
layout(location = 0) out vec4 fso_albedo;
in vec3 fs_position;
in vec2 fs_texcoord;
                                #define DEF_NORMAL vec3(0.f,0.f,1.f)
                                #define DEF_ROUGH 1.f
                                #define DEF_SPECULAR vec3(0.f)
                                #define DEF_COLOR vec4(1.f,0.f,0.f,1.f)
struct Material{
   sampler2D albedoTex;
   sampler2D specularTex;
   sampler2D normalTex;
   };
uniform Material materialData[1];
void main(){
fso_albedo = texture(materialData[0].albedoTex,fs_texcoord);
}




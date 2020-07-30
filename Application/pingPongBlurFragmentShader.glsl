#version 440

in vec2 vs_texcoord;

out vec4 fs_color;

uniform sampler2D texture0;

uniform int horizontal;
uniform float weight[5] = float[] (0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);
void main(){
	fs_color=vec4(1.f,0.f,0.f,1.f);
	//fs_color = texture(texture0,vs_texcoord);

	vec2 tex_offset = 1.0 / textureSize(texture0, 0); // gets size of single texel
    vec3 result = texture(texture0, vs_texcoord).rgb * weight[0]; // current fragment's contribution
    if(horizontal)
    {
        for(int i = 1; i < 5; ++i)
        {
            result += texture(texture0, vs_texcoord + vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
            result += texture(texture0, vs_texcoord - vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
        }
    }
    else
    {
        for(int i = 1; i < 5; ++i)
        {
            result += texture(texture0, vs_texcoord + vec2(0.0, tex_offset.y * i)).rgb * weight[i];
            result += texture(texture0, vs_texcoord - vec2(0.0, tex_offset.y * i)).rgb * weight[i];
        }
    }
    fs_color = vec4(result, 1.0);
    fs_color = texture(texture0,vs_texcoord);

}


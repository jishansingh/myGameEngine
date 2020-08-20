#version 440

in vec2 vs_texcoord;

out vec4 fs_color;

uniform sampler2D texture0; // color
uniform sampler2D texture1; // position
uniform sampler2D texture2; // normal

struct Light{
	vec3 position;
	vec3 color;
};
uniform int noOfLight;
uniform Light sceneLight[10];

uniform vec3 camPos;

/*
vec4 calcSpecular(vec3 position,vec3 lightPos,vec3 normal,vec3 camPosition){
	vec3 posToLightVec=normalize(lightPos-position);
	vec3 norm_normal=normalize(normal);
	vec3 posToCamVec=normalize(camPosition-position);
	vec3 reflectVec=normalize(reflect(-posToLightVec,norm_normal));
	float spec_const=pow(clamp(dot(reflectVec,posToCamVec),0,1),30);
	vec4 spec_final=vec4(1.f,1.f,1.f,1.f)*spec_const;
	return spec_final;
}*/



void main(){
	//fs_color=vec4(1.f,0.f,0.f,1.f);
	//float dep = texture(texture0,vs_texcoord).r;
	//fs_color = vec4(vec3(dep),1.f);
	vec4 ambient = texture(texture0,vs_texcoord);
	vec4 diffuse = texture(texture0,vs_texcoord);

	vec3 normal = texture(texture2,vs_texcoord).rgb;
	vec3 positonCube =  texture(texture1,vs_texcoord).rgb;

	float acc=0.f;
	for(int i=0;i<1;i++){
		vec3 lightDir = normalize(sceneLight[i].position - positonCube);
        acc += max(-dot(normalize(normal), lightDir), 0.0);
        //acc += diffuse;

		vec3 incVec = normalize(sceneLight[i].position - positonCube );
		vec3 reflectVec = reflect(-incVec ,normalize((normal)));
		vec3 camVec =  normalize(camPos - positonCube);
		float spec_const=pow(clamp(-dot(reflectVec,camVec),0,1),30);
		acc+=spec_const;
	}

	fs_color = ambient + diffuse*acc;
	gl_FragDepth = 100.f;
}

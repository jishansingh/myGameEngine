#version 440
layout(location = 0) in vec2 vs_position;
layout (location = 1) in vec2 vs_texcoord;
uniform mat4 positionMatrix[1];
uniform mat4 rotationMatrix[1];
uniform mat4 scaleMatrix[1];
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
out vec3 fs_position;
out vec2 fs_texcoord;
void main(){
vec4 somPos = positionMatrix[0]*rotationMatrix[0]*scaleMatrix[0]*vec4(vs_position,0.f,1.f);
fs_texcoord = vs_texcoord;
gl_Position = projectionMatrix*viewMatrix*somPos;
fs_position = somPos.xyz;
}

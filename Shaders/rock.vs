#version 330
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 uv;
layout (location = 3) in mat4 modelInstance; 

out VS_OUT
{
	vec3 normal;
	vec2 uv;
} vs_out;

layout (std140) uniform Matices
{
	mat4 projection;
	mat4 view;
};

void main()
{
	gl_Position =  projection*view*modelInstance*vec4(aPos,1.0);
	vs_out.normal = aNormal;
	vs_out.uv = uv;
}
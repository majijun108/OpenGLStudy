
# version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 uv;


/*out vec3 normal;
out vec2 ourUV;
out vec3 vertWorldPos;*/

out VS_OUT{
	vec3 normal;
	vec2 ourUV;
	vec3 vertWorldPos;
} vs_out;

uniform mat4 model;
/*uniform mat4 view;
uniform mat4 projection;*/
layout (std140) uniform Matices
{
	mat4 projection;
	mat4 view;
};

void main()
{
	gl_Position = projection * view * model* vec4(aPos,1.0f);
	gl_PointSize = gl_Position.z;
	vs_out.normal = aNormal;
	vs_out.ourUV = uv;
	vs_out.vertWorldPos = vec3(model * vec4(aPos,1.0f));
}
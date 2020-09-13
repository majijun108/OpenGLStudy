
#version 330


struct Material
{
	sampler2D texture_diffuse1;
};
uniform Material material;

in VS_OUT
{
	vec3 normal;
	vec2 uv;
}fs_in;

out vec4 fColor;

void main()
{
	vec3 color = vec3(texture(material.texture_diffuse1,fs_in.uv));
	fColor = vec4(color,1.0);
}
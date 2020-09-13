#version 330
//爆炸效果
layout(triangles) in;
layout(triangle_strip,max_vertices = 3) out;

uniform float time;

in VS_OUT{
	vec3 normal;
	vec2 ourUV;
	vec3 vertWorldPos;
} gs_in[];

out GS_OUT
{
	vec3 normal;
	vec2 ourUV;
	vec3 vertWorldPos;
}gs_out;

vec3 GetNormal()
{
	vec3 dir1 = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
	vec3 dir2 = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
	return normalize(cross(dir1,dir2));
}

vec4 Explode(vec4 pos,vec3 normal)
{
	float distance = 2.0;
	vec3 direction = normal * ((sin(time) + 1.0) * 0.5) * distance;
	return pos + vec4(direction,0.0);
}

void main()
{
	vec3 normal = GetNormal();
	gl_Position = Explode(gl_in[0].gl_Position,normal);
	gs_out.normal = gs_in[0].normal;
	gs_out.ourUV = gs_in[0].ourUV;
	gs_out.vertWorldPos = gs_in[0].vertWorldPos;
	EmitVertex();

	gl_Position = Explode(gl_in[1].gl_Position,normal);
	gs_out.normal = gs_in[1].normal;
	gs_out.ourUV = gs_in[1].ourUV;
	gs_out.vertWorldPos = gs_in[1].vertWorldPos;
	EmitVertex();

	gl_Position = Explode(gl_in[2].gl_Position,normal);
	gs_out.normal = gs_in[2].normal;
	gs_out.ourUV = gs_in[2].ourUV;
	gs_out.vertWorldPos = gs_in[2].vertWorldPos;
	EmitVertex();

	EndPrimitive();
}
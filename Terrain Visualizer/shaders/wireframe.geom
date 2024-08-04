#version 460

layout (triangles) in;

layout(line_strip, max_vertices = 4) out;

uniform mat4 camera;
uniform mat4 projection;

void main() {
	gl_Position = projection * camera * gl_in[0].gl_Position;
	EmitVertex();
	gl_Position = projection * camera * gl_in[1].gl_Position;
	EmitVertex();
	gl_Position = projection * camera * gl_in[2].gl_Position;
	EmitVertex();
	gl_Position = projection * camera * gl_in[0].gl_Position;
	EmitVertex();
	EndPrimitive();
}
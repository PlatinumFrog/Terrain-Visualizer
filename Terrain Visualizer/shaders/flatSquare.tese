#version 460

layout(quads, equal_spacing, ccw) in;

//uniform sampler2D heightMap;
uniform mat4 camera;
uniform mat4 projection;

out float height;
out vec2 texCoord;

void main() {
	
	vec2 t0 = gl_TessCoord.x * (gl_in[1].gl_Position.zw - gl_in[0].gl_Position.zw) + gl_in[0].gl_Position.zw;
	vec2 t1 = gl_TessCoord.x * (gl_in[3].gl_Position.zw - gl_in[2].gl_Position.zw) + gl_in[2].gl_Position.zw;
	vec2 t2 = gl_TessCoord.x * (gl_in[1].gl_Position.xy - gl_in[0].gl_Position.xy) + gl_in[0].gl_Position.xy;
	vec2 t3 = gl_TessCoord.x * (gl_in[3].gl_Position.xy - gl_in[2].gl_Position.xy) + gl_in[2].gl_Position.xy;
	vec2 posCoords = gl_TessCoord.y * (t2 - t3) + t2;
	vec2 texCoords = gl_TessCoord.y * (t1 - t0) + t0;
	float h = 0;
	texCoord = texCoords;
	gl_Position = projection * camera * vec4(posCoords.x, h, posCoords.y, 1.0);
}
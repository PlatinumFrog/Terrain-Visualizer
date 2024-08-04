#version 460

layout(quads, equal_spacing, ccw) in;

uniform sampler2D heightMap;
uniform mat4 camera;
uniform mat4 projection;
uniform float height;
void main() {
	vec2 t0 = gl_TessCoord.x * (gl_in[1].gl_Position.zw - gl_in[0].gl_Position.zw) + gl_in[0].gl_Position.zw;
	vec2 t1 = gl_TessCoord.x * (gl_in[3].gl_Position.zw - gl_in[2].gl_Position.zw) + gl_in[2].gl_Position.zw;
	vec2 texCoords = gl_TessCoord.y * (t1 - t0) + t0;
	float h = texture(heightMap, texCoords).r;
	h *= height;
	vec2 t2 = gl_TessCoord.x * (gl_in[1].gl_Position.xy - gl_in[0].gl_Position.xy) + gl_in[0].gl_Position.xy;
	vec2 t3 = gl_TessCoord.x * (gl_in[3].gl_Position.xy - gl_in[2].gl_Position.xy) + gl_in[2].gl_Position.xy;
	vec2 posCoords = gl_TessCoord.y * (t3 - t2) + t2;
	gl_Position = vec4(posCoords.x, h, posCoords.y, 1.0);
}
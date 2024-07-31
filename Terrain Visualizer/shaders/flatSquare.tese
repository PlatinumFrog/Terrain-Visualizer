#version 460

layout(quads, equal_spacing, ccw) in;

uniform sampler2D heightMap;
uniform mat4 camera;
uniform mat4 projection;

out vec3 texCoord;
out vec2 posCoord;
out vec3 normal;
out float height;

void main() {

	vec2 t0 = gl_TessCoord.x * (gl_in[1].gl_Position.zw - gl_in[0].gl_Position.zw) + gl_in[0].gl_Position.zw;
	vec2 t1 = gl_TessCoord.x * (gl_in[3].gl_Position.zw - gl_in[2].gl_Position.zw) + gl_in[2].gl_Position.zw;
	vec2 texCoords = gl_TessCoord.y * (t1 - t0) + t0;
	
	const float sDist = 0.000001;
	height = 1.0;

	vec2 s1 = vec2(texCoords.x + sDist, texCoords.y);
	vec2 s2 = vec2(texCoords.x, texCoords.y + sDist);
	vec3 h0 = vec3(texCoords, texture(heightMap, texCoords).r);
	vec3 h1 = vec3(s1, texture(heightMap, s1).r);
	vec3 h2 = vec3(s2, texture(heightMap, s2).r);
	normal = normalize(cross(h1 - h0, h2 - h0)).xzy;
	texCoord = vec3(texCoords, h0);
	h0.z *= height;
	vec2 t2 = gl_TessCoord.x * (gl_in[1].gl_Position.xy - gl_in[0].gl_Position.xy) + gl_in[0].gl_Position.xy;
	vec2 t3 = gl_TessCoord.x * (gl_in[3].gl_Position.xy - gl_in[2].gl_Position.xy) + gl_in[2].gl_Position.xy;
	vec2 posCoords = gl_TessCoord.y * (t3 - t2) + t2;
	gl_Position = projection * camera * vec4(posCoords.x, h0.z, posCoords.y, 1.0);
}
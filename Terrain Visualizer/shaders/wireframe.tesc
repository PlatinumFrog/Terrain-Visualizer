#version 460

layout(vertices = 4) out;

uniform mat4 camera;

const float maxT = 64.0;
const float slopeT = 1.0;
const float ceilAmount = 16.0;
void main() {
	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
	if(gl_InvocationID == 0) {
		float l0 = clamp(maxT + ceilAmount - slopeT * length((camera * vec4(gl_in[0].gl_Position.x, 0, gl_in[0].gl_Position.y, 1)).xyz), 1.0, maxT);
		float l1 = clamp(maxT + ceilAmount - slopeT * length((camera * vec4(gl_in[1].gl_Position.x, 0, gl_in[1].gl_Position.y, 1)).xyz), 1.0, maxT);
		float l2 = clamp(maxT + ceilAmount - slopeT * length((camera * vec4(gl_in[2].gl_Position.x, 0, gl_in[2].gl_Position.y, 1)).xyz), 1.0, maxT);
		float l3 = clamp(maxT + ceilAmount - slopeT * length((camera * vec4(gl_in[3].gl_Position.x, 0, gl_in[3].gl_Position.y, 1)).xyz), 1.0, maxT);

		gl_TessLevelOuter[0] = max(l0, l2);
		gl_TessLevelOuter[1] = max(l0, l1);
		gl_TessLevelOuter[2] = max(l1, l3);
		gl_TessLevelOuter[3] = max(l2, l3);
		gl_TessLevelInner[0] = max(max(l0, l1), max(l2, l3));
		gl_TessLevelInner[1] = max(max(l0, l1), max(l2, l3));
	}
}
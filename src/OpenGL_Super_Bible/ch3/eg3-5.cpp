#version 450 core
// 'offset' is an input vertex attribute
layout(location = 0) in vec4 offset;
layout(location = 1) in vec4 color;
// Declare VS_OUT as an output interface block
out VS_OUT
{
vec4 color; // Send color to the next stage
} vs_out;
void main(void)
{
	const vec4 vertices[3] = vec4[3](vec4(0.25, -0.25, 0.5, 1.0),
		vec4(-0.25, -0.25, 0.5, 1.0),
		vec4(0.25, 0.25, 0.5, 1.0));
	// Add 'offset' to our hard-coded vertex position
	gl_Position = vertices[gl_VertexID] + offset;
	// Output a fixed value for vs_color
	vs_out.color = color;
}
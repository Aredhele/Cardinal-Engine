#version 330 core

// In
layout(location = 0) in vec2 vertex;
layout(location = 1) in vec2 vertexUV;

// Out
out vec2 UV;

void main(){

	// Output position of the vertex, in clip space
	// map [0..800][0..600] to [-1..1][-1..1]
	vec2 vertexPosition_homoneneousspace = vertex - vec2(400,300); // [0..800][0..600] -> [-400..400][-300..300]
	vertexPosition_homoneneousspace /= vec2(400,300);
	gl_Position =  vec4(vertexPosition_homoneneousspace,0,1);

	// UV of the vertex. No special space for this one.
	UV = vec2(vertexUV.x, 1.0f - vertexUV.y);
	// UV = vertexUV;
}

#version 460

layout(binding = 1) uniform sampler2D texSampler[100];

layout(location = 0) in vec3 Normal;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec3 FragPos;

layout(location = 0) out vec4 outColor;

layout(push_constant) uniform constants {
    int numOfTexture;
    int numOfObjectWithinMaterial;
    mat4 modelMatrix;
} PushConstants;

void main() {
    // * Original
    outColor = texture(texSampler[PushConstants.numOfTexture], fragTexCoord);

	// // vec2 st = fragTexCoord.xy * 0.052;
	// vec2 st = fragTexCoord * 0.032;
	// // float angle = 0.3;
	// // mat2 rot = mat2(cos(angle), -sin(angle),sin(angle), cos(angle));
	// // st = rot * st;

	// vec3 color=vec3(abs(step(0.5,fract(st.x))-step(0.5,fract(st.y))),0.1,0.2);
	// outColor = vec4(color, 1.0);
}

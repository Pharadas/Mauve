#version 450 core
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

// layout(binding = 0) uniform sampler2D texSampler;

// layout(set = 0, binding = 0) uniform sampler texSampler;
// layout(set = 0, binding = 1) uniform texture2D textures[2];

layout(set = 0, binding = 0) uniform sampler samp;
layout(set = 0, binding = 1) uniform texture2D textures[1000];

layout(push_constant) uniform constants {
    int numOfTexture;
    mat4 render_matrix;
} PushConstants;

void main() {
    // outColor = vec4(texture(texSampler, fragTexCoord * 3.0).rgb, 1.0);
    outColor = texture(sampler2D(textures[PushConstants.numOfTexture], samp), fragTexCoord);
    // outColor = vec4(fragTexCoord, 0, 1);
}

// layout(location = 1) in vec2 TexCoord;

// layout(location = 0) out vec4 outColor;

// layout(binding = 1) uniform sampler2D texture1;

// void main()
// {
// 	vec2 st = fragTexCoord.xy * 10;
// 	// float angle = 1;
// 	// mat2 rot = mat2(cos(angle), -sin(angle),sin(angle), cos(angle));
// 	// st = rot * st;

// 	vec3 color=vec3(abs(step(0.5,fract(st.x))-step(0.5,fract(st.y))),0.1,0.2);
// 	outColor = vec4(color, 1.0);
// }

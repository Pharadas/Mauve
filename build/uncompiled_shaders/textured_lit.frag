// #version 450

// layout(binding = 0) uniform sampler2D texSampler[100];
// layout(binding = 1) uniform LightingInfo {
//     vec3 objectColor;
//     vec3 lightColor;
//     vec3 lightPos;
//     vec3 viewPos;
// } lighting;

// layout(location = 0) in vec3 fragNormal;
// layout(location = 1) in vec2 fragTexCoord;

// layout(location = 0) out vec4 outColor;

// layout(push_constant) uniform constants {
//     int numOfTexture;
//     mat4 render_matrix;
// } PushConstants;

// void main() {
//     // outColor = texture(texSampler[PushConstants.numOfTexture], fragTexCoord) * vec4(lighting.objectColor, 1);
//     // outColor = texture(texSampler[PushConstants.numOfTexture], fragTexCoord);
//     // ambient
//     float ambientStrength = 0.1;
//     vec3 ambient = ambientStrength * lighting.lightColor;

//     // diffuse 
//     vec3 norm = normalize(fragNormal);
//     vec3 lightDir = normalize(lighting.lightPos - fragTexCoord);
//     float diff = max(dot(norm, lightDir), 0.0);
//     vec3 diffuse = diff * lighting.lightColor;

//     // specular
//     float specularStrength = 0.5;
//     vec3 viewDir = normalize(lighting.viewPos - fragTexCoord);
//     vec3 reflectDir = reflect(-lightDir, norm);  
//     float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
//     vec3 specular = specularStrength * spec * lighting.lightColor;  

//     vec3 result = (ambient + diffuse + specular) * lighting.objectColor;
//     outColor = vec4(result, 1);
// }

#version 460

layout(binding = 1) uniform sampler2D texSampler[100];

layout(location = 0) in vec3 Normal;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec3 FragPos;

layout(location = 0) out vec4 outColor;

layout(push_constant) uniform constants {
    int numOfTexture;
    mat4 render_matrix;
} PushConstants;

void main() {
    outColor = texture(texSampler[PushConstants.numOfTexture], fragTexCoord);
}


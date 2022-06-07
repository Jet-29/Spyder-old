#pragma once

#include <string>

namespace Spyder::Vulkan::Shaders {
	const std::string VertexMeshShader = R"(
#version 460
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in float pointSize;
layout(location = 0) out vec3 fragColor;
layout(set = 0, binding = 0) uniform GlobalUbo {
    mat4 projection;
    mat4 view;
    mat4 invView;
} ubo;
layout(push_constant) uniform Push {
    mat4 modelMatrix;
    mat4 additionalMatrix;
} push;
void main() {
	vec4 positionWorld = push.modelMatrix * vec4(position, 1.0);
    gl_Position = ubo.projection * ubo.view * positionWorld;
	fragColor = color;
    gl_PointSize = pointSize;
}
)";

	const std::string FragmentMeshShader = R"(
#version 460
layout(location = 0) in vec3 fragColor;
layout (location = 0) out vec4 outColor;
layout(set = 0, binding = 0) uniform GlobalUbo {
    mat4 projection;
    mat4 view;
    mat4 invView;
} ubo;
layout(push_constant) uniform Push {
    mat4 modelMatrix;
    mat4 additionalMatrix;
} push;
void main() {
    outColor = vec4(fragColor, 1.0);
}
)";
}
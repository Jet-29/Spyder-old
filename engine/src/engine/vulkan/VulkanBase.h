#pragma once

#include "engine/core/Base.h"
#include "VulkanPrecompiledHeaders.h"
#include "VulkanTypes.h"

#define VK_CHECK(x)                                                         \
    do                                                                      \
    {                                                                       \
        VkResult err = x;                                                   \
        if (err)                                                            \
        {                                                                   \
            SPYDER_CORE_ERROR("Detected Vulkan error: {}", err);            \
            abort();                                                        \
        }                                                                   \
    } while (0)
namespace Spyder::Vulkan {
	static constexpr int MAX_FRAMES_IN_FLIGHT = 3;
}
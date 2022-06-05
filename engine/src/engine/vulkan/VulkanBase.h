#pragma once

#include "engine/core/Base.h"

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

#include "UI.h"

#include "engine/vulkan/gui/imgui/imgui.h"
#include "engine/vulkan/gui/imgui/imgui_impl_vulkan.h"
#include "engine/vulkan/gui/imgui/imgui_impl_glfw.h"

namespace Spyder::Vulkan {
	UI::UI(Instance &instance, Device &device) : r_Instance{instance}, r_Device{device} {}

	void UI::init() {
		VkDescriptorPoolSize pool_sizes[] =
				{
						{ VK_DESCRIPTOR_TYPE_SAMPLER, 1000 },
						{ VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000 },
						{ VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 1000 },
						{ VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1000 },
						{ VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 1000 },
						{ VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 1000 },
						{ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1000 },
						{ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1000 },
						{ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000 },
						{ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000 },
						{ VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 1000 }
				};

		VkDescriptorPoolCreateInfo pool_info = {};
		pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		pool_info.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
		pool_info.maxSets = 1000;
		pool_info.poolSizeCount = std::size(pool_sizes);
		pool_info.pPoolSizes = pool_sizes;

		VK_CHECK(vkCreateDescriptorPool(r_Device.getDevice(), &pool_info, nullptr, &m_ImguiPool));

		ImGui::CreateContext();

		//this initializes imgui for SDL
//		ImGui_ImplSDL2_InitForVulkan(_window);

		ImGui_ImplVulkan_InitInfo init_info = {};
		init_info.Instance = r_Instance.getInstance();
		init_info.PhysicalDevice = r_Device.getPhysicalDevice();
		init_info.Device = r_Device.getDevice();
		init_info.Queue = r_Device.getGraphicsQueue();
		init_info.DescriptorPool = m_ImguiPool;
		init_info.MinImageCount = MAX_FRAMES_IN_FLIGHT;
		init_info.ImageCount = MAX_FRAMES_IN_FLIGHT;
		init_info.MSAASamples = VK_SAMPLE_COUNT_1_BIT;

		ImGui_ImplVulkan_Init(&init_info, m_ImguiRenderPass);

//		immediate_submit([&](VkCommandBuffer cmd) {
//			ImGui_ImplVulkan_CreateFontsTexture(cmd);
//		});

		ImGui_ImplVulkan_DestroyFontUploadObjects();
	}

	void UI::cleanup() {
		vkDestroyDescriptorPool(r_Device.getDevice(), m_ImguiPool, nullptr);
		ImGui_ImplVulkan_Shutdown();
	}
} // Spyder
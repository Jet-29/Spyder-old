#pragma once

#include "engine/core/Base.h"

namespace Spyder {

	class Mesh {
	public:
		struct Builder {
			std::vector<Vertex> m_Vertices{};
			std::vector<uint32_t> m_Indices{};
			void loadModel(const std::vector<Vertex> vertices);
		};

		lve_model(lve_device &device, const Builder &builder);
		~lve_model();

		lve_model(const lve_model &) = delete;
		lve_model &operator=(const lve_model &) = delete;

		static std::unique_ptr<lve_model> createModelFromFile(lve_device &device, const std::string &filepath);
		static std::unique_ptr<lve_model> createModelFromString(lve_device &device, const std::string &obj_text, const std::string &mtl_text);

		void bind(VkCommandBuffer commandBuffer);
		void draw(VkCommandBuffer commandBuffer);

	private:
		void createVertexBuffers(const std::vector<Vertex> &vertices);
		void createIndexBuffers(const std::vector<uint32_t> &indices);

		lve_device &lveDevice;

		std::unique_ptr<lve_buffer> vertexBuffer;
		uint32_t vertexCount{};

		bool hasIndexBuffer = false;

		std::unique_ptr<lve_buffer> indexBuffer;
		uint32_t indexCount{};
	};

} // Spyder
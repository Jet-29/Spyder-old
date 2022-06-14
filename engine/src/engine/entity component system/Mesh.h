#pragma once

#include "engine/core/Base.h"

namespace Spyder {

	class Mesh {
	public:
		Mesh() = default;
		~Mesh() = default;

		Mesh(const Mesh &) = delete;
		Mesh &operator=(const Mesh &) = delete;
		Mesh(Mesh &&) = default;
		Mesh &operator=(Mesh &&) = default;

		void loadModel(const std::vector<Vertex>& vertices);

		[[nodiscard]] std::vector<Vertex> &getUniqueVertices();
		[[nodiscard]] std::vector<uint32_t> &getUniqueIndices();

	private:
		std::vector<Vertex> m_AllVertices{};
		std::vector<Vertex> m_UniqueVertices{};
		std::unordered_map<Vertex, uint32_t, VertexHash> m_VertexMap{};
		std::vector<uint32_t> m_Indices{};

	};

} // Spyder
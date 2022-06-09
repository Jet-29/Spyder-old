#pragma once

#include "engine/core/Base.h"

namespace Spyder {

	class Mesh {
	public:
		Mesh() = default;
		~Mesh() = default;

		Mesh(const Mesh &) = delete;
		Mesh &operator=(const Mesh &) = delete;

		void loadModel(std::vector<Vertex> vertices);

		std::vector<Vertex> &getUniqueVertices();
		std::vector<uint32_t> &getUniqueIndices();

	private:
		std::vector<Vertex> m_AllVertices{};
		std::vector<Vertex> m_UniqueVertices{};
		std::unordered_map<Vertex, uint32_t, VertexHash> m_VertexMap{};
		std::vector<uint32_t> m_Indices{};

	};

} // Spyder
#include "Mesh.h"

namespace Spyder {

	void Mesh::loadModel(const std::vector<Vertex>& vertices) {
		SPYDER_TRACE("loading model to game object mesh...");
		m_AllVertices.clear();
		m_UniqueVertices.clear();
		m_VertexMap.clear();

		m_Indices.clear();

		for (const Vertex &vertex : vertices) {
			m_AllVertices.push_back(vertex);

			if (m_VertexMap.count(vertex) == 0) {
				m_VertexMap[vertex] = static_cast<uint32_t>(m_UniqueVertices.size());
				m_UniqueVertices.push_back(vertex);
			}
			m_Indices.push_back(m_VertexMap[vertex]);
		}
		SPYDER_TRACE("game object mesh has:");
		SPYDER_TRACE("Total vertices: {0}", m_AllVertices.size());
		SPYDER_TRACE("Total optimized vertices: {0}", m_UniqueVertices.size());
		SPYDER_TRACE("Total indices: {0}", m_Indices.size());
	}

	std::vector<Vertex> &Mesh::getUniqueVertices() {
		return m_UniqueVertices;
	}

	std::vector<uint32_t> &Mesh::getUniqueIndices() {
		return m_Indices;
	}
} // Spyder
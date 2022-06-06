#include "Mesh.h"

namespace Spyder {

	void Mesh::loadModel(std::vector<Vertex> vertices) {
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
	}
} // Spyder
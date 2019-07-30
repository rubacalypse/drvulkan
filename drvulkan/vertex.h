#pragma once
#include <vulkan/vulkan.h>
#include <glm/gtx/hash.hpp>

#ifndef VERTEX_H
#define VERTEX_H

namespace std {
	struct Vertex {
		glm::vec3 pos;
		glm::vec3 color;
		glm::vec2 texCoord;

		static VkVertexInputBindingDescription getBindingDescription();
		static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions();
		bool operator==(const Vertex& other) const {
			return pos == other.pos && color == other.color && texCoord == other.texCoord;
		}
	};
		template<> struct hash<Vertex> {
			size_t operator()(Vertex const& vertex) const {
				return ((hash<glm::vec3>()(vertex.pos) ^
					(hash<glm::vec3>()(vertex.color) << 1)) >> 1) ^
					(hash<glm::vec2>()(vertex.texCoord) >> 1);
			}
		};
}


#endif // !VERTEX_H


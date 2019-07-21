#include <glm/glm.hpp> 
#include <string>
#include <unordered_map>
#include "vertex.h"
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <fstream>
#include <array>
#include <chrono>
#include "model.h"
#include "tiny_obj_loader.h"
#include "bufferUtil.h"
#include "BufferSet.h"

namespace std {
	Model::Model(std::string path, std::string texture) {
		path = path;
		texture = texture;
		position = glm::vec3(0.0f, 0.0f, 0.0f);
	}

	Model::Model(std::string modelPath, std::string texture, glm::vec3 pos) {
		path = modelPath;
		texture = texture;
		position = pos;
	}

	void Model::setupModel(std::string modelPath, std::string texPath, glm::vec3 pos) { 
		path = modelPath;
		texture = texPath;
		pos = pos;
	}

	Model::Model() {}

	void Model::loadModel() {
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		std::string err;

		if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path.c_str())) {
			throw std::runtime_error(err);
		}
		std::unordered_map<Vertex, uint32_t> uniqueVertices = {};

		for (const auto& shape : shapes) {
			for (const auto& index : shape.mesh.indices) {
				Vertex vertex = {};

				vertex.pos = {
					attrib.vertices[3 * index.vertex_index + 0],
					attrib.vertices[3 * index.vertex_index + 1],
					attrib.vertices[3 * index.vertex_index + 2]
				};

				vertex.texCoord = {
					attrib.texcoords[2 * index.texcoord_index + 0],
					1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
				};

				vertex.color = { 1.0f, 1.0f, 1.0f };
				if (uniqueVertices.count(vertex) == 0) {
					uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
					vertices.push_back(vertex);
				}

				indices.push_back(uniqueVertices[vertex]);
			}
		}
	}
	void Model::createVertexBuffer(BufferSet* bufferSet, VkDevice* device, VkPhysicalDevice* physicalDevice, VkCommandPool* commandPool, VkQueue* graphicsQueue) {
		VkDeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();
		VkBuffer stagingBuffer;
		VkDeviceMemory stagingBufferMemory;

		buffer::createBuffer(device, bufferSize, physicalDevice, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

		void* data;
		vkMapMemory(*device, stagingBufferMemory, 0, bufferSize, 0, &data);
		memcpy(data, vertices.data(), (size_t)bufferSize);
		vkUnmapMemory(*device, stagingBufferMemory);

		buffer::createBuffer(device, bufferSize, physicalDevice, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, bufferSet->vertexBuffer, bufferSet->vertexBufferMemory);

		buffer::copyBuffer(&stagingBuffer, &(bufferSet->vertexBuffer), device, bufferSize, commandPool, graphicsQueue);
		vkDestroyBuffer(*device, stagingBuffer, nullptr);
		vkFreeMemory(*device, stagingBufferMemory, nullptr);

	}


	void Model::createIndexBuffer(BufferSet* bufferSet, VkDevice* device, VkPhysicalDevice* physicalDevice, VkCommandPool* commandPool, VkQueue* graphicsQueue) {
		VkDeviceSize bufferSize = sizeof(indices[0]) * indices.size();
		VkBuffer stagingBuffer;
		VkDeviceMemory stagingBufferMemory;

		buffer::createBuffer(device, bufferSize, physicalDevice, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

		void* data;
		vkMapMemory(*device, stagingBufferMemory, 0, bufferSize, 0, &data);
		memcpy(data, indices.data(), (size_t)bufferSize);
		vkUnmapMemory(*device, stagingBufferMemory);

		buffer::createBuffer(device, bufferSize, physicalDevice, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, bufferSet->indexBuffer, bufferSet->indexBufferMemory);

		buffer::copyBuffer(&stagingBuffer, &(bufferSet->indexBuffer), device, bufferSize, commandPool, graphicsQueue);

		vkDestroyBuffer(*device, stagingBuffer, nullptr);
		vkFreeMemory(*device, stagingBufferMemory, nullptr);
	}

	void Model::createUniformBuffer(BufferSet* bufferSet, VkDevice* device, VkPhysicalDevice* physicalDevice) {
		VkDeviceSize bufferSize = sizeof(UniformBufferObject);
		buffer::createBuffer(device, bufferSize, physicalDevice, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, bufferSet->uniformBuffer, bufferSet->uniformBufferMemory);

	}


}
	


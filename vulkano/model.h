#pragma once
#include <string>
#include "vertex.h"
#include "BufferSet.h"

namespace std {
	class Model
	{
	public:
		std::vector<std::Vertex> vertices;
		std::vector<uint32_t> indices;
		std::string path;
		glm::vec3 position;
		std::string texture;
		Model::Model();
		Model(std::string path, std::string texture);
		Model(std::string path, std::string texture, glm::vec3 pos);
		
		void setupModel(std::string modelPath, std::string texPath, glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f));

		void loadModel();
		void createVertexBuffer(BufferSet* bufferSet, VkDevice* device, VkPhysicalDevice* physicalDevice, VkCommandPool* commandPool, VkQueue* graphicsQueue);
		void createUniformBuffer(BufferSet* bufferSet, VkDevice* device, VkPhysicalDevice* physicalDevice);
		void createIndexBuffer(BufferSet* bufferSet, VkDevice* device, VkPhysicalDevice* physicalDevice, VkCommandPool* commmandPool, VkQueue* graphicsQueue);
		//~model();
	};
}
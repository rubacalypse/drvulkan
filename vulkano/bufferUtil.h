#pragma once
#include "bufferUtil.h"
#include <vulkan/vulkan.h>
#include <glm/glm.hpp>

#ifndef BUFFER_H
#define BUFFER_H

struct UniformBufferObject {
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 proj;
};


struct buffer {

	static VkBuffer vertexBuffer;
	static VkDeviceMemory vertexBufferMemory;
	static VkBuffer indexBuffer;
	static VkDeviceMemory indexBufferMemory;
	static VkBuffer uniformBuffer;
	static VkDeviceMemory uniformBufferMemory;


	static VkCommandBuffer beginSingleTimeCommands(VkDevice* device, VkCommandPool* commandPool);
	
	static void endSingleTimeCommands(VkCommandBuffer* commandBuffer, VkDevice* device, VkCommandPool* commandPool, VkQueue* graphicsQueue);
	
	static void copyBuffer(VkBuffer* srcBuffer, VkBuffer* dstBuffer, VkDevice* device, VkDeviceSize size, VkCommandPool* commandPool, VkQueue* graphicsQueue);

	static void createBuffer(VkDevice* device, VkDeviceSize size, VkPhysicalDevice* physicalDevice, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer & buffer, VkDeviceMemory & bufferMemory);

	static uint32_t findMemoryType(VkPhysicalDevice* physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties);

};

#endif

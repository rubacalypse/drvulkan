#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public: 
	glm::vec3 pos = glm::vec3(0.0f, 0.0f, 6.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 right = glm::vec3(0.0f, 0.0f, 0.0f);

	float pitch = 0.0f;
	float yaw = -90.0f;
	float movementSpeed = 3.0f;
	float mouseSensitivity = 0.25f;
	float zoom = 45.0f;
	
	void updateCameraVectors(glm::vec3 newPos, glm::vec3 newFront) {
		pos = newPos;
		cameraFront = newFront;
		right = glm::normalize(glm::cross(cameraFront, worldUp));
		
	}

	Camera(glm::vec3 pos) {
		pos = pos;
	}
	

};
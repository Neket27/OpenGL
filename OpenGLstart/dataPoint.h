#pragma once

#include <vector>
#include "glew.h" // ����������� GLEW
#include <glfw3.h> 
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

struct dataPoint {
	std::vector<glm::vec3> coordinates;
	std::vector<glm::vec3>  colors;
	size_t sizeDataPoints;

	void addCoordinates(glm::vec3 coordinate) {
		coordinates.push_back(coordinate);
		sizeDataPoints = (coordinates.size()) == 0 ? 0 : 3 * coordinates.size();
	}

	void addColors(glm::vec3 color) {
		colors.push_back(color);
	}
	// ����� ��� ��������� ��������� �� ������ ���������
	glm::vec3* getCoordinatesData() {
		return coordinates.data();
	}

	// ����� ��� ��������� ��������� �� ������ ������
	glm::vec3* getColorsData() {
		return colors.data();
	}
};


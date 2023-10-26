#pragma once
#include <vector>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
bool OBJLoad(
	const char* path,
	std::vector<glm::vec3>& outVertices, //�������� ������ ���������
	std::vector<glm::vec2>& outTextures, //�������� ������ ���������� ���������
	std::vector<glm::vec3>& outNormals //�������� ������ ��������
);
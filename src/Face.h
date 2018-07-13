#ifndef FACE_H
#define FACE_H

#include "BasicVertex.h"

class Face
{
public:
	Face();

	RubiksCubeVertex vertices[6];

	void setVertexPosition(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);

	void setColor(float r, float g, float b, float a);

	void setColorByColorId(int colorId);

	//void updateNormals();

	void calculateNormalTangentAndBinormal(glm::vec3 p0, glm::vec3 p1, glm::vec3 p3);

	void updateUvCoordinates();
};

#endif // FACE_H

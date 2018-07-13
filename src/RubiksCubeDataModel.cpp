#include "RubiksCubeDataModel.h"
#include <iostream>
#include <string>
#include <assert.h>

RubiksCubeDataModel::RubiksCubeDataModel()
{
	resetCube();
}

void RubiksCubeDataModel::printCubeToTtyAsUnwrappedCube()
{
	std::string dashes5 = "-----";
	std::string dashes17 = "-----------------";
	std::string seperator = "¦";

	//face 4:
	std::cout << dashes5 << std::endl;
	for(int i = 0; i < 3; i++)
	{
		std::cout << seperator;
		for(int j = 0; j < 3; j++)
		{
			std::cout << colorMap[4][i][j];
		}
		std::cout << seperator << std::endl;
	}

	//face 0, 1, 2, 3:
	std::cout << dashes17 << std::endl;
	for(int i = 0; i < 3; i++)
	{
		for(int f = 0; f < 4; f++)
		{
			std::cout << seperator;
			for(int j = 0; j < 3; j++)
			{
				std::cout << colorMap[f][i][j];
			}
		}
		std::cout << seperator << std::endl;
	}
	std::cout << dashes17 << std::endl;

	//face 5:
	for(int i = 0; i < 3; i++)
	{
		std::cout << seperator;
		for(int j = 0; j < 3; j++)
		{
			std::cout << colorMap[5][i][j];
		}
		std::cout << seperator << std::endl;
	}
	std::cout << dashes5 << std::endl;
}

void RubiksCubeDataModel::resetCube()
{
	for(int i = 0; i < 6; i++)
		for(int j = 0; j < 3; j++)
			for(int k = 0; k < 3; k++)
				colorMap[i][j][k] = i;
}

/**
 * @brief RubiksCubeDataModel::getTuple
 * @param face
 * @param edge
 * @param tuple
 * Fertig!
 */
void RubiksCubeDataModel::getTuple(int face, int edge, int** tuple)
{
	switch (edge)
	{
	case 0:
		tuple[0] =  &(colorMap[face][0][0]);
		tuple[1] =  &(colorMap[face][0][1]);
		tuple[2] =  &(colorMap[face][0][2]);
		break;

	case 1:
		tuple[0] =  &(colorMap[face][0][2]);
		tuple[1] =  &(colorMap[face][1][2]);
		tuple[2] =  &(colorMap[face][2][2]);
		break;

	case 2:
		tuple[0] =  &(colorMap[face][2][2]);
		tuple[1] =  &(colorMap[face][2][1]);
		tuple[2] =  &(colorMap[face][2][0]);
		break;

	case 3:
		tuple[0] =  &(colorMap[face][2][0]);
		tuple[1] =  &(colorMap[face][1][0]);
		tuple[2] =  &(colorMap[face][0][0]);
		break;
	}
}

/**
 * @brief RubiksCubeDataModel::rotateValuesOfTuples
 * @param tuples
 * Tauscht die übergebenen Tupel im Uhrzeigersinn herum.
 * Schiebt die Tupel also rechts herum und der der hinten rausfällt wird vorne wieder eingefügt.
 */
//FERTIG!
void RubiksCubeDataModel::rotateValuesOfTuples(int *tuples[4][3])
{
	int swapHelp[3];
	for(int i = 0; i < 3; i++)
		swapHelp[i] = *tuples[3][i];

	for(int i = 3; i > 0; i--)
		for(int j = 0; j < 3; j++)
			*tuples[i][j] = *tuples[i-1][j];

	for(int i = 0; i < 3; i++)
		*tuples[0][i] = swapHelp[i];
}

/**
 * @brief RubiksCubeDataModel::rotateColorsOnField
 * @param field
 * Rotiert die Farben auf dem Feld im Uhrzeigersinn.
 */
//FERTIG
//TESTED
void RubiksCubeDataModel::rotateColorsOnFace(int face)
{
	//	(0,0)(0,1)(0,2)
	//	(1,0)(1,1)(1,2)
	//	(2,0)(2,1)(2,2)

	int swapHelp[2];
	swapHelp[0] = colorMap[face][0][0];
	swapHelp[1] = colorMap[face][1][0];

	colorMap[face][0][0] = colorMap[face][2][0];
	colorMap[face][1][0] = colorMap[face][2][1];
	colorMap[face][2][0] = colorMap[face][2][2];
	colorMap[face][2][1] = colorMap[face][1][2];
	colorMap[face][2][2] = colorMap[face][0][2];
	colorMap[face][1][2] = colorMap[face][0][1];
	colorMap[face][0][2] = swapHelp[0];
	colorMap[face][0][1] = swapHelp[1];
}

//gibt die Frabe zurück:
//Der ursprung liegt dabei unten links, damit man wie in kaartisischen koordinaten gewohnt drauf zugreifen kann. Weil der Cube auch so aufgebaut ist macht es das leichter.
int RubiksCubeDataModel::getColorAt(int face, int x, int y)
{
	return colorMap[face][2-y][x];
}

void RubiksCubeDataModel::printCubeToTtyAsList()
{
	std::cout << "Current state of the rubik's cube:" << std::endl;
	for(int i = 0; i < 6; i++)
	{
		std::cout << "––– face " << i << std::endl;
		for(int j = 0; j < 3; j++)
		{
			for(int k = 0; k < 3; k++)
			{
				std::cout << colorMap[i][j][k];
			}
			std::cout << std::endl;
		}
	}
}

void RubiksCubeDataModel::rotateFaceClockwise(int face)
{
	assert((-1 < face) && (face < 6));

	//Rotate colors on the field
	rotateColorsOnFace(face);

	//Adjust neigborsing fields
	int* neighborTuples[4][3];

	if(face < 4)
	{
		int edge;
		if(face == 1 || face == 3)
			edge = face;
		else
			edge = (face+2)%4;
		getTuple(4,edge,neighborTuples[0]);

		getTuple((face+1)%4,3,neighborTuples[1]);
		getTuple(5,face,neighborTuples[2]);
		getTuple((face+3)%4,1,neighborTuples[3]);
	}
	else if(face == 4)
	{
		for(int i = 0; i < 4; i++)
			getTuple(3-i,0,neighborTuples[i]);
	}
	else if(face == 5)
	{
		for(int i = 0; i < 4; i++)
			getTuple(i, 2, neighborTuples[i]);
	}
	rotateValuesOfTuples(neighborTuples);
}

void RubiksCubeDataModel::rotateFaceCounterclockwise(int face)
{
	assert((-1 < face) && (face < 6));
	rotateFaceClockwise(face);
	rotateFaceClockwise(face);
	rotateFaceClockwise(face);
}



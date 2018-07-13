#ifndef RUBIKSCUBEDATAMODEL_HPP
#define RUBIKSCUBEDATAMODEL_HPP

/**
 * @brief The RubiksCubeDataModel class
 * Das Datenmodel für den Rubiks Cube
 */
class RubiksCubeDataModel
{
public:
	RubiksCubeDataModel();
	void printCubeToTtyAsList();
	void printCubeToTtyAsUnwrappedCube();

	int getColorAt(int face, int row, int column);
	void rotateFaceClockwise(int face);
	void rotateFaceCounterclockwise(int face);
	void resetCube();
private:
	int colorMap[6][3][3];
	void getTuple(int face, int edge, int** tuple);
	void rotateValuesOfTuples(int *tuples[4][3]);
	void rotateColorsOnFace(int face);
};

#endif // RUBIKSCUBEDATAMODEL_HPP

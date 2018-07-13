//Copyright (C) 2010-2012 by Jason L. McKesson
//This file is licensed under the MIT License.


#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <glload/gl_3_3.h>
#include <GL/freeglut.h>
#include "../framework/framework.h"

#include "RubiksCubeDataModel.h"
#include "BasicVertex.h"
#include "Face.h"
#include "Cube.h"
#include "RubiksCubeMesh.h"

#include "../glsdk/glm/glm/glm.hpp"
#include "../glsdk/glm/glm/gtc/matrix_transform.hpp"
#include "../glsdk/glm/glm/gtx/transform.hpp"

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))

RubiksCubeDataModel dataModel;

GLuint theProgram;
GLuint MVP_MatrixID;
GLuint M_MatrixID;
GLuint V_MatrixID;
GLuint lightPosition_worldSpace_VectorID;

void InitializeProgram()
{
	std::vector<GLuint> shaderList;

	shaderList.push_back(Framework::LoadShader(GL_VERTEX_SHADER, "standard.vert"));
	shaderList.push_back(Framework::LoadShader(GL_FRAGMENT_SHADER, "standard.frag"));

	theProgram = Framework::CreateProgram(shaderList);

	MVP_MatrixID = glGetUniformLocation(theProgram, "MVP");
	M_MatrixID = glGetUniformLocation(theProgram, "M");
	V_MatrixID = glGetUniformLocation(theProgram, "V");
	lightPosition_worldSpace_VectorID = glGetUniformLocation(theProgram, "lightPosition_worldSpace");
}

RubiksCubeVertex *vertices = (RubiksCubeVertex*) malloc(sizeof(RubiksCubeMesh));
RubiksCubeMesh *rubicsCubeMesh = new RubiksCubeMesh(1.0f);

GLuint positionBufferObject;
GLuint vao;

void InitializeVertexBuffer()
{
	//Vertices:
	glGenBuffers(1, &positionBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);

	glBufferData(GL_ARRAY_BUFFER, sizeof(RubiksCubeMesh), rubicsCubeMesh, GL_STREAM_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//Called after the window and OpenGL are initialized. Called exactly once, before the main loop.
void init()
{
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);

	InitializeProgram();

	InitializeVertexBuffer();

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	dataModel.printCubeToTtyAsUnwrappedCube();
	dataModel.rotateFaceClockwise(5);
	//dataModel.rotateFaceClockwise(1);
}

//Called to update the display.
//You should call glutSwapBuffers after all of your rendering to display what you rendered.
//If you need continuous updates of the screen, call glutPostRedisplay() at the end of the function.
float grad = 0.f;
int display_w;
int display_h;
void display()
{
	grad += 0.5f;
	rubicsCubeMesh->updateColors(dataModel);
	dataModel.printCubeToTtyAsUnwrappedCube();
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(RubiksCubeMesh), rubicsCubeMesh);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//glClear(GL_COLOR_BUFFER_BIT);
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(theProgram);

	glm::vec3 myRotationAxis( 1.0f, 1.0f, 0.0f);

	glm::mat4 rotationMatrix = glm::rotate( grad, myRotationAxis );
	glm::mat4 modelMatrix = rotationMatrix;

	glm::mat4 projectionMatrix = glm::perspective(
		50.f,         // The horizontal Field of View, in degrees : the amount of "zoom". Think "camera lens". Usually between 90° (extra wide) and 30° (quite zoomed in)
		//4.0f / 3.0f, // Aspect Ratio. Depends on the size of your window. Notice that 4/3 == 800/600 == 1280/960, sounds familiar ?
		(float) display_w / (float)display_h,
				0.1f,        // Near clipping plane. Keep as big as possible, or you'll get precision issues.
		100.0f       // Far clipping plane. Keep as little as possible.
	);

	//glm::vec3 cameraPosition(0,3,3); // Camera is at (0,3,3), in World Space
	glm::vec3 cameraPosition(0,0,3); // Camera is at (0,3,3), in World Space

	glm::vec3 lightPosition_worldSpace(0,0,1.5);

	// Camera matrix
	glm::mat4 viewMatrix = glm::lookAt(
		//glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
		cameraPosition,
		glm::vec3(0,0,0), // and looks at the origin
		glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
	);
	glm::mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;

	glUniformMatrix4fv(MVP_MatrixID, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(M_MatrixID, 1, GL_FALSE, &modelMatrix[0][0]);
	glUniformMatrix4fv(V_MatrixID, 1, GL_FALSE, &viewMatrix[0][0]);
	glUniform3fv(lightPosition_worldSpace_VectorID, 1, &lightPosition_worldSpace[0]);

	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(RubiksCubeVertex), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(RubiksCubeVertex), (void*)offsetof(RubiksCubeVertex, color));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(RubiksCubeVertex), (void*)offsetof(RubiksCubeVertex, normal));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(RubiksCubeVertex), (void*)offsetof(RubiksCubeVertex, uv));

	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(RubiksCubeVertex), (void*)offsetof(RubiksCubeVertex, tangent));

	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(RubiksCubeVertex), (void*)offsetof(RubiksCubeVertex, binormal));

	int numberOfIndicesToBeRendered = sizeof(RubiksCubeMesh) / sizeof(RubiksCubeVertex);
	//std::cout << "numberOfIndicesToBeRendered: " << numberOfIndicesToBeRendered << std::endl;
	glDrawArrays(GL_TRIANGLES, 0, numberOfIndicesToBeRendered);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
	glDisableVertexAttribArray(5);
	glUseProgram(0);

	glutSwapBuffers();
	glutPostRedisplay();
}

//Called whenever the window is resized. The new window size is given, in pixels.
//This is an opportunity to call glViewport or glScissor to keep up with the change in size.
void reshape (int w, int h)
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	display_w = w;
	display_h = h;
}

//Called whenever a key on the keyboard was pressed.
//The key is given by the ''key'' parameter, which is in ASCII.
//It's often a good idea to have the escape key (ASCII value 27) call glutLeaveMainLoop() to 
//exit the program.
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	  case 27:
		  glutLeaveMainLoop();
		  return;
	}
}


unsigned int defaults(unsigned int displayMode, int &width, int &height) {return displayMode;}

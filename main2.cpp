//В буфер кроме координатпомещаются и цвета для каждой из вершин, но они пока не используются
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include "loadshaders.h"
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

using namespace std;


GLuint program;
GLuint Buffer;
GLuint VA;
GLuint shaderprogram;

void init(void)
{
	glGenVertexArrays(1, &VA);
	glBindVertexArray(VA);

	GLfloat vert[24] = {
		-0.85, -0.85, // Triangle 1
		-0.10, 0.0,
		-0.85, 0.85,
		-0.85, 0.85, // Triangle 2
		0.0, 0.10,
		0.85, 0.85,
		0.85, 0.85, // Triangle 3
		0.10, 0.0,
		0.85, -0.85,
		0.85, -0.85, // Triangle 4
		0.0, -0.10,
		-0.85, -0.85
	}; 

	GLfloat col[36] = {
		0.435f, 0.602f, 0.223f,
		0.310f, 0.747f, 0.185f,
		0.597f, 0.770f, 0.761f,
		0.559f, 0.436f, 0.730f,
		0.359f, 0.583f, 0.152f,
		0.483f, 0.596f, 0.789f,
		0.559f, 0.861f, 0.639f,
		0.195f, 0.548f, 0.859f,
		0.14f, 0.184f, 0.576f,
		0.771f, 0.328f, 0.970f,
		0.406f, 0.615f, 0.116f,
		0.676f, 0.977f, 0.133f
	};

	glGenBuffers(1, &Buffer);
	glBindBuffer(GL_ARRAY_BUFFER, Buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vert)+sizeof(col), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, NULL, sizeof(vert), vert);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vert), sizeof(col), col);

	ShaderInfo shaders[] =
	{
		{ GL_VERTEX_SHADER, "NULL" },
		{ GL_FRAGMENT_SHADER, "NULL" },
		{ GL_NONE, NULL }
	};

	shaderprogram = LoadShaders(shaders);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(shaderprogram);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, Buffer);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 12);
	glDisableVertexAttribArray(0);
	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(512, 512);
	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow(argv[0]);
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		cerr << "Unable to initialize GLEW ... exiting" << endl;
		exit(EXIT_FAILURE);
	}
	init();
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glutDisplayFunc(display);
	glutMainLoop();
}

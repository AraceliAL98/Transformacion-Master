// PlantillaOpenGL.cpp: define el punto de entrada de la aplicación de consola.


#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>

using namespace std;

float poiscionXTriangulo = 0.0f;
float posicionYTriangulo = 0.0f;
float angulo = 0;

enum Direccion {Izquierda, Drecha, Arriba, Abajo};
Direccion direccionTriangulo = Direccion:: Izquierda;

Direccion direccionTrianguloY = Direccion::Arriba;

void dibujarTrangulo() {
	//utilizar matriz identidad
	glPushMatrix();
	//transformaciones
	glTranslatef(poiscionXTriangulo, posicionYTriangulo, 0.0f);
	glRotatef(angulo, 0.0f, 0.0f, 0.0f);

	//dibujar los vertices
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.8f,0);
	glVertex3f(-0.4,- 0.4, 0);
	glVertex3f(0.4, -0.4, 0);
	glVertex3f(0, 0.2f, 0);
	glEnd();

	//soltar la matriz
	glPopMatrix();
}

void dibujar() {
	dibujarTrangulo();
}

void actualizar() {

	if (angulo >= 360)
	{
		angulo = 0.0f;
	}

	if (direccionTriangulo == Direccion::Izquierda)
	{


		if (poiscionXTriangulo > -0.6f)
		{
			poiscionXTriangulo -= 0.001f;

		}
		else {

			direccionTriangulo = Direccion::Drecha;
		}

	}

	if (direccionTriangulo == Direccion::Drecha)
	{

		if (poiscionXTriangulo < 0.6f) {
			poiscionXTriangulo += 0.001f;

		}
		else
		{
			direccionTriangulo = Direccion::Izquierda;

		}

	}
	if (direccionTrianguloY == Direccion::Abajo)
	{


		if (posicionYTriangulo > -0.6f)
		{
			posicionYTriangulo -= 0.001f;

		}
		else {

			direccionTrianguloY = Direccion::Arriba;
		}

	}
	if (direccionTrianguloY == Direccion::Arriba)
	{


		if (posicionYTriangulo < 0.6f)
		{
			posicionYTriangulo += 0.001f;

		}
		else {

			direccionTrianguloY = Direccion::Abajo;
		}

	}
}
int main()
{
	//Declaramos apuntador de ventana
	GLFWwindow *window;

	//si no se pudo inicializar glfw terminamos ejecución
	if (!glfwInit())
		exit(EXIT_FAILURE);

	//si se pudo iniciar GLFW entonces inicializamos la ventana
	window = glfwCreateWindow(1024, 768, "Ventana", NULL, NULL);

	//si no podemos iniciar la ventana entonces terminamos la ejecución
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	//establecemos el contexto
	glfwMakeContextCurrent(window);

	//UNa vez establecido el contexto activamos funciones modernas (CPU/GPU)
	glewExperimental = true;
	GLenum errorGlew = glewInit();

	if (errorGlew != GLEW_OK) {
		cout << glewGetErrorString(errorGlew);
	}

	const GLubyte *versionGL = glGetString(GL_VERSION);
	cout << "Version OpenGL: " << versionGL;


	//Cilco de dibijo (Draw loop)
	while (!glfwWindowShouldClose(window)) {
		//Establecer region de dibujo
		glViewport(0, 0, 1024, 768);
		//Esctablece el color de borrado
		glClearColor(0.25, 0, 0.3, 1);
		//Borramos
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Rutina de dibujo
		actualizar();
		dibujar();
		

		//Cambiar los buffers
		glfwSwapBuffers(window);
		//Reconocer si hay entradas
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

    return 0;
}


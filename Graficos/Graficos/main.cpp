#include<glew.h>
#include<glfw3.h>
#include "wtypes.h"
#include <iostream>
using namespace std;
const GLchar *vertexSource = R"glsl(
#version 150 core
in vec2 position;
void main()
{
gl_Position=vec4(position,0.0,1.0);
}
)glsl";
const GLchar *fragmentSource = R"glsl(
#version 150 core
out vec4 outColor;
void main()
{
outColor=vec4(0.0,1.0,0.0,1.0);
}
)glsl";
void GetDesktopResolution(int& horizontal, int& vertical);

int main(int argc, char*argv[])
{
	int horizontal = 0;
	int vertical = 0;
	GetDesktopResolution(horizontal, vertical);
	glfwInit();
	GLFWwindow*window = glfwCreateWindow(horizontal, vertical, "OpenGL", NULL, NULL);
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	glewInit();
	GLfloat vertices[] =
	{
		0.0f,0.2f,
		0.2f,0.2f,
		0.2f,-0.2f,
		0.0,-0.2

	};
	GLuint vbo;
	glGenBuffers(1, &vbo); 
	glBindBuffer(GL_ARRAY_BUFFER, vbo); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); 
	glShaderSource(vertexShader, 1, &vertexSource, NULL); 
	glCompileShader(vertexShader); 
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); 
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL); 
	glCompileShader(fragmentShader); 
	GLuint shaderProgram = glCreateProgram(); 
	glAttachShader(shaderProgram, vertexShader); 
	glAttachShader(shaderProgram, fragmentShader); 
	glLinkProgram(shaderProgram); 
	glUseProgram(shaderProgram); 
	GLint posAttrib = glGetAttribLocation(shaderProgram, "position"); 
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0); 
	glEnableVertexAttribArray(posAttrib); 
	while (!glfwWindowShouldClose(window))
	{ 
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE); 
		glfwPollEvents();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //color de la ventana
		glClear(GL_COLOR_BUFFER_BIT); 
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
	}
	glDeleteProgram(shaderProgram);
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteBuffers(1, &vbo);
}

void GetDesktopResolution(int& horizontal, int& vertical)
{
	RECT desktop;
	// Get a handle to the desktop window
	const HWND hDesktop = GetDesktopWindow();
	// Get the size of screen to the variable desktop
	GetWindowRect(hDesktop, &desktop);
	// The top left corner will have coordinates (0,0)
	// and the bottom right corner will have coordinates
	// (horizontal, vertical)
	horizontal = desktop.right;
	vertical = desktop.bottom;
}
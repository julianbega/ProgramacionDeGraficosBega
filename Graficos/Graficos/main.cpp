#include<glew.h>
#include<glfw3.h>
const GLchar *vertexSource = R"glsl(
#version 150 core
in vec2 position;
void main()
{
gl_Position=vec4(position,0.0,1.0);
}
)
glsl";
const GLchar* fragmentSource = R"glsl(
#version 150 core
out vec4 outColor;
voidmain()
{
outColor=vec4(1.0,0.0,0.0,1.0);
}
)glsl";
int main(int argc, char*argv[])
{
	glfwInit();
	GLFWwindow*window = glfwCreateWindow(640, 480, "OpenGL", NULL, NULL);
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	glewInit();
	GLfloat vertices[] =
	{
		0.0f,0.5f,
		0.5f,-0.5f,
		-0.5f,-0.5f
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
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT); glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
	}
	glDeleteProgram(shaderProgram);
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteBuffers(1, &vbo);
}
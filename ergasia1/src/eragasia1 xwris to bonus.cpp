#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#define 	GLFW_KEY_TAB   258 
#define 	GLFW_KEY_BACKSPACE   259


const char* vertexShaderSourceCode =
"#version 330 core \n"
"\n"
"layout (location = 0) in vec3 pos; \n"
"void main() \n"
"{   \n"
"gl_Position = vec4(pos.x,pos.y,0.0, 1.0); \n"
"} \n";

const char* vertexShaderSourceCode1 =
"#version 330 core \n"
"\n"
"layout (location = 0) in vec3 pos; \n"
"void main() \n"
"{   \n"
"float pos_x=pos.x-0.1;\n"
"float pos_y=pos.y; \n"
"gl_Position = vec4(-pos_x,-pos_y,0.0, 1.0); \n"
"} \n";


const char* fragmentShaderSourceCode =
"#version 330 core \n"
"\n"
"void main() \n"
"{ \n"
"gl_FragColor = vec4(0.0f, 0.8f, 0.6f, 1.0); \n"
"} \n";

const char* fragmentShaderSourceCode1 =
"#version 330 core \n"
"\n"
"void main() \n"
"{ \n"
"gl_FragColor = vec4(0.8f, 0.6f, 0.5f, 1.0); \n"
"} \n";





void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow* givenWindow)
{
	if (glfwGetKey(givenWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(givenWindow, true);
}

bool flag = true;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_TAB && action == GLFW_PRESS) {
		if (flag) {
			flag = !flag;
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glLineWidth(10.0f);

		}
		else {
			flag = !flag;
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glLineWidth(10.0f);

		}
	}
}






int main() {

	std::cout << "Hello OpenGL!" << std::endl;

	// Initialize GLFW
	if (!glfwInit()) {
		std::cout << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	// Create window
	GLFWwindow* window = glfwCreateWindow(800, 600, "Hercules Gousis AM : 58650", NULL, NULL);

	// Check if the window is created.
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Make the context that is created the current one
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwSetKeyCallback(window, key_callback);

	// Set our viewport --> we tell openGL how to render everything that we give.
	glViewport(0, 0, 800, 600);

	// Create callback function
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	GLfloat vertices[] = {

		-0.5f, 0.5f, 0.0f,  
		-0.5f, -0.5f, 0.0f, 
		0.5f, -0.5f, 0.0f, 
		
		
	};

	//generate a unique buffer ID
	GLuint triangle_vbo;
	glGenBuffers(1, &triangle_vbo);

	//bind the buffer to the context
	glBindBuffer(GL_ARRAY_BUFFER, triangle_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Vertex shader
	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSourceCode, NULL);
	glCompileShader(vertexShader);

	GLuint vertexShader1;
	vertexShader1= glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader1, 1, &vertexShaderSourceCode1, NULL);
	glCompileShader(vertexShader1);

	// Fragment Shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSourceCode, NULL);
	glCompileShader(fragmentShader);

	GLuint fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader1, 1, &fragmentShaderSourceCode1, NULL);
	glCompileShader(fragmentShader1);


	// Program shader
	GLuint shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);


	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	GLuint shaderProgram1;
	shaderProgram1 = glCreateProgram();
	glAttachShader(shaderProgram1, vertexShader1);
	glAttachShader(shaderProgram1, fragmentShader1);
	glLinkProgram(shaderProgram1);


	glDeleteShader(vertexShader1);
	glDeleteShader(fragmentShader1);
	bool flag = true;

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		ProcessInput(window);

		

		glUseProgram(shaderProgram);

		// bind vbo
		glBindBuffer(GL_ARRAY_BUFFER, triangle_vbo);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);
		glEnableVertexAttribArray(0);

		glDrawArrays(GL_TRIANGLES, 0, 3);
		

		glUseProgram(shaderProgram1);

		// bind vbo
		glBindBuffer(GL_ARRAY_BUFFER, triangle_vbo);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);

		glEnableVertexAttribArray(0);


		glDrawArrays(GL_TRIANGLES, 0, 3);



		glfwSwapBuffers(window); //send new frame to window
		glfwPollEvents();
	}


	glfwTerminate();

	return 0;
}
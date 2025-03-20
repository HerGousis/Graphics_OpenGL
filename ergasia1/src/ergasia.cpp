#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Shader.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#define 	GLFW_KEY_TAB   258 
#define 	GLFW_KEY_BACKSPACE   259
void FrameBufferSizeCallback(GLFWwindow* givenWindow, int givenWidth, int givenHeight)
{
	glViewport(0, 0, givenWidth, givenHeight);
}

void ProcessInput(GLFWwindow* givenWindow)
{
	if (glfwGetKey(givenWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(givenWindow, true);
}

bool flag = false;

void ProcessInput1(GLFWwindow* givenWindow)
{

	if (glfwGetKey(givenWindow, GLFW_KEY_TAB) == GLFW_PRESS) {
		flag = !flag;
		if (flag) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glLineWidth(10.0f);
		}
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glLineWidth(10.0f);
		}
	}
}
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

int main()
{
	// Initialization

	if (!glfwInit())
	{
		std::cout << "Failed to initialize glfw!" << std::endl;
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(800, 600, "Hercules Gousis AM : 58650", NULL, NULL);

	if (!window)
	{
		std::cout << "Failed to initialize the window!" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	// Set the callback function
	glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize glew!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwSetKeyCallback(window, key_callback);
	const char* glsl_version = "#version 330";
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	ImGui::StyleColorsClassic();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	
	GLfloat  vertices[] =
	{
		 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,    // top right 
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right 
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom left 
		-0.5f, 0.5f, 0.0f,  1.0f, 1.0f, 1.0f // top left 
	};


	// first buffer (vbo)
	unsigned int vertexBufferId;
	glGenBuffers(1, &vertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//RECTANGLE - VBO and EBO - part2: EBO
	GLuint indices[] =
	{
		3, 1, 0, // first triangle 
		
	};
	GLuint indices1[] =
	{ 
		  
		3, 2, 1, // second triangle 
	};

	unsigned int elementBufferId;
	glGenBuffers(1, &elementBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	Shader shaderProgram("res/Shaders/VertexShaderLab2.glsl", "res/Shaders/FragmentShaderLab2.glsl");
	//FileName
	//VertexShaderLab2
	
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);
	Shader shaderProgram1("res/Shaders/FileName.glsl", "res/Shaders/FragmentShaderLab2.glsl");
	

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//glLineWidth(10.0f);

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		ProcessInput(window);

		
		
		
		
		glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Hello, world!");

		ImGui::ColorEdit3("clear color", (float*)&clear_color);

		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Render Using the shader program
		shaderProgram.use();
		
		
		
		float time = glfwGetTime();
		float Chanel = sin(time) * 0.5f + 0.5f;
		float Chanel1 = sin(time) * 0.8f + 0.5f;
		float Chanel2 = sin(time) * 0.1f + 0.5f;


		int uniformLocation = glGetUniformLocation(shaderProgram.ID, "color1");
		
		glUniform3f(uniformLocation, Chanel2, Chanel, Chanel1);
		
		// Draw the triangle
		
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		shaderProgram1.use();

		int uniformLocation1 = glGetUniformLocation(shaderProgram1.ID, "color1");

		glUniform3f(uniformLocation1, Chanel, Chanel, Chanel2);

		glDrawElements(GL_TRIANGLES,3, GL_UNSIGNED_INT, 0);

		


		glfwSwapBuffers(window);
		glfwPollEvents();
		
		
	}

	glfwTerminate();
	return 0;
}
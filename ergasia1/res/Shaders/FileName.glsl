#version 330 core 

layout (location = 0) in vec3 inputPosition;
layout (location = 1) in vec3 inputColor;

out vec3 color;

void main() 

{ 
float pos_x=inputPosition.x - 0.1;
  float pos_y=inputPosition.y;
	gl_Position = vec4(-pos_x,-pos_y, 0.0, 1.0);
	color = inputColor;
}
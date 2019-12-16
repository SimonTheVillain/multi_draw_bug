#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
struct Vertex
{
	float x, y;
};
const char* const vertex_shader_str =
#include "shader.vert"
;
const char* const fragment_shader_str =
#include "shader.frag"
;


static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}
bool workaround = true;
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		workaround = !workaround;

}
int main(void)
{



	GLFWwindow* window;
	GLuint vao,vertex_buffer, vertex_shader, fragment_shader, program;
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		exit(EXIT_FAILURE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwSetKeyCallback(window, key_callback);
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	glewInit();
	glGetError();

	glfwSwapInterval(1);


	int base = 300;
	//set up a 2d grid of vertices
	vector<Vertex> vertices ( base*base);
	int k=0;
	for(int i=0;i<base;i++){
		for(int j=0;j<base;j++){
			vertices[k].x = (0.5f + i)*2.0f/(float)base -1.0f;
			vertices[k].y = (0.5f + j)*2.0f/(float)base -1.0f;
			k++;
		}
	}


	//Gen buffer
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	//setup shader
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_str, NULL);
	glCompileShader(vertex_shader);
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_str, NULL);
	glCompileShader(fragment_shader);
	program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);



	//bind the buffer
	glUseProgram(program);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0,
					 vertex_buffer);
	//glPointSize(3);
	while (!glfwWindowShouldClose(window))
	{
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);

		glClear(GL_COLOR_BUFFER_BIT);

		vector<GLint> first(base,0);
		vector<GLsizei > count(base,base);

		for(int i=0;i<base;i++){
			first[i] = i*base;
			count[i] = i;
		}

		if(!workaround){
			//THIS DOESN't WORK but should behave like
			glMultiDrawArrays(GL_POINTS,&first[0],&count[0],base);
		}else{
			//THIS, which draws a perfect triangle
			for(int i=0;i<base;i++){
				glDrawArrays(GL_POINTS, first[i], count[i]);
			}
			//IT DOESN't THOUGH
		}





		glfwSwapBuffers(window);

		glfwPollEvents();

	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
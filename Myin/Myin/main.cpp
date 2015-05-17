#include <iostream>

#include <gl_core_4_4.h>
#include <glfw3.h>

#include <Gizmos.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat4;

GLFWwindow* g_Window = nullptr;
mat4 g_View = glm::lookAt(vec3(10, 10, 10), vec3(0), vec3(0, 1, 0));
mat4 g_Projection = glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f);

void print(const char*, bool = false, bool = false);

bool init();
void exit();
void loop();
void update(float);
void render();

int main()
{
	if (init() == true)
	{
		loop();
	}

	exit();
	system("pause");
	return 0;
}

void print(const char* a_string, bool a_pause, bool a_clear)
{
	printf("%s\n", a_string);
	if (a_pause)
		system("pause");
	if (a_clear)
		system("cls");
}

bool init()
{
	if (glfwInit() == false)
		return false;
	print("GLFW3: initialized.");

	g_Window = glfwCreateWindow(1280, 720, "Computer Graphics", nullptr, nullptr);
	if (g_Window == nullptr)
	{
		print("Window creation failed. Terminating");
		return false;
	}
	print("GLFWwindow: created.");

	glfwMakeContextCurrent(g_Window);
	print("GLFWwindow: context current.");

	if (ogl_LoadFunctions() == ogl_LOAD_FAILED) {
		print("ogl: Load Failed.");
		return false;
	}
	
	int major = ogl_GetMajorVersion();
	int minor = ogl_GetMinorVersion();
	printf("GLVersion: %i.%i\n", major, minor);

	Gizmos::create();
	
	return true;
}

void exit()
{
	Gizmos::destroy();

	if (g_Window)
	{
		glfwDestroyWindow(g_Window);
		print("GLFWwindow: destroyed.");
	}

	glfwTerminate();
	print("GLFW3: terminated.");
}

void loop()
{
	glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	while (	glfwWindowShouldClose(g_Window) == false &&
			glfwGetKey(g_Window, GLFW_KEY_ESCAPE) != GLFW_PRESS) 
	{	
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		Gizmos::clear();

		Gizmos::addTransform(glm::mat4(1));

		// our game logic and update code goes here!
		update(0.16f);
		// so does our render code!
		render();

		glfwSwapBuffers(g_Window);
		glfwPollEvents();
	}
}

void update(float a_deltaTime)
{
	
}

void render()
{
	vec4 white(1);
	vec4 black(0, 0, 0, 1);

	for (int i = 0; i <= 20; i++) {
		Gizmos::addLine(vec3(-10 + i, 0, 10), vec3(-10 + i, 0, -10), i == 10 ? white : black);
		Gizmos::addLine(vec3(10, 0, -10 + i), vec3(-10, 0, -10 + i), i == 10 ? white : black);
	}

	Gizmos::draw(g_Projection * g_View);
}
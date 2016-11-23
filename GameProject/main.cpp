#include <GLFW/glfw3.h>
#include <random>
#include <chrono>
#include <thread>
#include "stdio.h"
#include "windows.h"

//window infomation
int width = 640;
int height = 480;

//frame counter vars
static unsigned int frame_count = 0;
static int current_fps = 0;
static double start_time = 0;

//vars for sleep calculations
static double target_frame_rate = 30;
static double frame_start = 0;

void calc_frame_rate()
{
	frame_count++;

	double elapsed = (glfwGetTime() - start_time);

	if (elapsed > 1)
	{
		current_fps = frame_count;
		start_time = glfwGetTime();
		frame_count = 0;
	}
}

void calc_sleep()
{
	double wait_time = 1.0 / (target_frame_rate);
	double curr_frame_time = glfwGetTime() - frame_start;
	double dur = 1000.0 * (wait_time - curr_frame_time) + 0.5;
	int durDW = (int)dur;
	if (durDW > 0) // ensures that we don't have a dur > 0.0 which converts to a durDW of 0.
	{
		Sleep((DWORD)durDW);
	}

	double frame_end = glfwGetTime();
	frame_start = frame_end;
}	

GLfloat randomnum() {
	//the random device that will seed the generator
	std::random_device seeder;
	//then make a mersenne twister engine
	std::mt19937 engine(seeder());
	//then the easy part... the distribution
	std::uniform_int_distribution<int> dist(0, 1);
	//then just generate the integer like this:
	GLfloat compGuess = dist(engine);
	return compGuess;
}

GLfloat testybit = 1;
void display(GLFWwindow* window) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBegin(GL_QUADS);
		glColor3f(testybit, testybit, testybit);
		glVertex2f(-1, 1);
		glColor3f(testybit, testybit, testybit);
		glVertex2f(-1, -1);
		glColor3f(testybit, testybit, testybit);
		glVertex2f(1, -1);
		glColor3f(testybit, testybit, testybit);
		glVertex2f(1, 1);
	glEnd();
	glfwSwapBuffers(window);
}

static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
	testybit = ypos / height;
}

//Gets the resize callback and sets the new dimesions to the viewport and saves it globally
static void window_size_callback(GLFWwindow* window, int widthcall, int heightcall) {
	width = widthcall;
	height = heightcall;
	glViewport(0, 0, widthcall, heightcall);
}

int main(void)
{
	GLFWwindow* window;

	//Initialize glfw
	if (!glfwInit())
		return -1;

	// Creates a window and checks if it is created.
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	// Sets the context to the previously created window.
	glfwMakeContextCurrent(window);
	
	// Sets callback for cursor moving while over window.
	glfwSetCursorPosCallback(window, cursor_pos_callback);
	glfwSetWindowSizeCallback(window, window_size_callback);

	while (!glfwWindowShouldClose(window))
	{
		calc_frame_rate();
		display(window);
		calc_sleep();
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

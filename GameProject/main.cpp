#include <GLFW/glfw3.h>
#include <random>
#include <chrono>
#include <thread>

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

void display(GLFWwindow* window) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBegin(GL_QUADS);
		glColor3f(randomnum(), randomnum(), randomnum()); // make this vertex purple
		glVertex2f(-1, 1);
		glColor3f(randomnum(), randomnum(), randomnum()); // make this vertex red
		glVertex2f(-1, -1);
		glColor3f(randomnum(), randomnum(), randomnum()); // make this vertex green
		glVertex2f(1, -1);
		glColor3f(randomnum(), randomnum(), randomnum()); // make this vertex yellow
		glVertex2f(1, 1);
	glEnd();
	glfwSwapBuffers(window);
}
int main(void)
{
	GLFWwindow* window;

	//Initialize glfw
	if (!glfwInit())
		return -1;

	// Creates a window and checks if it is created.
	window = glfwCreateWindow(2160, 1440, "Hello World", glfwGetPrimaryMonitor(), NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	// Sets the context to the previously created window.
	glfwMakeContextCurrent(window);
	glfwSetWindowSize(window, 2160, 1440);
	
	while (!glfwWindowShouldClose(window))
	{
		display(window);
		glfwPollEvents();
		std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 45));
	}

	glfwTerminate();
	return 0;
}

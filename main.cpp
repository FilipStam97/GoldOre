#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

//the moment a user resizes the window the viewport should be adjusted as well
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	//we check whether the user has pressed the escape key (if it's not pressed, glfwGetKey returns GLFW_RELEASE)
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

int main() {
	//GLFW Init
	glfwInit();
	//We'd like to tell GLFW that 3.3 is the OpenGL version we want to use.
	//This way GLFW can make the proper arrangements when creating the OpenGL context.
	//This ensures that when a user does not have the proper OpenGL version GLFW fails to run.
	//We set the major and minor version both to 3. We also tell GLFW we want to explicitly use the core-profile. 
	//Telling GLFW we want to use the core-profile means we'll get access to a smaller subset of OpenGL features without backwards - compatible features we no longer need
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //for Mac OS X

	GLFWwindow* window = glfwCreateWindow(800, 600, "GoldOre", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// GLAD manages function pointers for OpenGL so we want to initialize GLAD before we call any OpenGL function
	//We pass GLAD the function to load the address of the OpenGL function pointers which is OS-specific.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);

	//There are many callbacks functions we can set to register our own functions. 
	//For example, we can make a callback function to process joystick input changes, process error messages etc.
	//We register the callback functions after we've created the window and before the render loop is initiated.
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//render loop
	// checks at the start of each loop iteration if GLFW has been instructed to close. 
	//If so, the function returns true and the render loop stops running, after which we can close the application.
	while (!glfwWindowShouldClose(window))
	{
		// ------------ input ---------------
		processInput(window);

		// ----------- rendering commands go here ----------------
		//Whenever we call glClear and clear the color buffer, the entire color buffer will be filled with the color as configured by glClearColor
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//---------------- check and call events and swap the buffers --------------------

		//will swap the color buffer (a large 2D buffer that contains color values for each pixel in GLFW's window)
		//that is used to render to during this render iteration and show it as output to the screen
		glfwSwapBuffers(window);

		//checks if any events are triggered (like keyboard input or mouse movement events), updates the window state, 
		//and calls the corresponding functions (which we can register via callback methods)
		glfwPollEvents();
	}


	//As soon as we exit the render loop we would like to properly clean/delete all of GLFW's resources that were allocated
	glfwTerminate();
	return 0;
}
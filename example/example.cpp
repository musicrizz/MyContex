#include "../context_util/util.h"

int main(int argc, char **argv) {

	/*
	 * SIMPLE TIMER
	 */
	const char *SIMPLE_TIMER = "Simple_Timer";
	int flag = 0;
	while (flag < 5) {
		if (TempoMap::getElapsedMill(SIMPLE_TIMER) >= 1000) {

			std::cout << "hello" << std::endl;
			flag++;

			TempoMap::updateStart(SIMPLE_TIMER);
		}
	}

	/*
	 * Create OpenGL Context
	 */

	if (!glfwInit()) {
		fprintf(stderr, "GLEW INTI ERROR");
		exit(EXIT_FAILURE);
	}

	glfwSetErrorCallback ([](int error, const char *description) {
		fprintf(stderr, "GLFW_ERROR: %u :  %s ", error, description);
	});

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	//To enable set DEVELOPEMENT 1 in contex_util/CommonHeaders
#if DEVELOPEMENT
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif

	const char *CONTEX_1 = "ctx1", *CONTEX_2 = "ctx_2";

	//                           name,  w,  h, GLFWmonitor*,  visible,  decorated,  trasparentFrameBuffer)
	OpenGLContext::createContex(CONTEX_1, 400, 400, NULL, true, true, true);

	OpenGLContext::createContex(CONTEX_2, 400, 400, NULL, true, false, true);

	OpenGLContext::setWindowPosition(CONTEX_1, 50, 50);
	OpenGLContext::setWindowPosition(CONTEX_2, 0, 880);

	OpenGLContext::makecurrent(CONTEX_1);
	OpenGLContext::setKeyboard([](GLFWwindow* window, int key, int scancode, int action, int mods ){
			switch (key) {
			case GLFW_KEY_ESCAPE:
				if (action == GLFW_PRESS) {
					OpenGLContext::setWindowShouldClose(GL_TRUE);
				}
				break;
			}
	});

	while (!glfwWindowShouldClose(OpenGLContext::getCurrent())) {

		//DIsplay

		glfwPollEvents(); //  It MUST be in the main thread
	}

	OpenGLContext::destroyAll();

	glfwTerminate();
}






















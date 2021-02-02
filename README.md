# MyContex
Simple utility to menage multiple OpenGL Context (no share) and multiple GLSL programs with GLFW

*required libraries (-l) GL GLEW glfw*

-----------------------------------

How to use TempoMap : 

* create a simple timer : *the timer is created at the first call of TempoMap::getElapsedMill(string);*
 
```cpp
	
	const char* SIMPLE_TIMER = "Simple_Timer";

	while(true)  {
		if(TempoMap::getElapsedMill(SIMPLE_TIMER) >= 1000)  {

			std::cout<<"hello"<<std::endl;

			TempoMap::updateStart(SIMPLE_TIMER);
		}
	}

```

* create two OpenGL context : *GLFW VERSION : 3.3.2 X11 GLX EGL OSMesa clock_gettime evdev shared*

```cpp

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
	
	const char *CONTEX_1 = "ctx1", *CONTEX_2 = "ctx_2";

//  name,  w,  h, GLFWmonitor*,  visible,  decorated,  trasparentFrameBuffer) 
	OpenGLContext::createContex(CONTEX_1, 400, 400, NULL, true, false, true);
	OpenGLContext::createContex(CONTEX_2, 400, 400, NULL, true, false, true);

	OpenGLContext::setWindowPosition(CONTEX_1, 50, 50);
	OpenGLContext::setWindowPosition(CONTEX_2, 0, 880);

	OpenGLContext::makecurrent(CONTEX_1);
	OpenGLContext::setKeyboard(
		[](GLFWwindow* window, int key, int scancode, int action, int mods ){
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
	
```

* create multiple program in one context : 
*for example in previous CONTEX_1 three program with uniform buffer*

```cpp



```
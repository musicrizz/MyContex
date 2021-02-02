# MyContext
Simple utility to menage multiple OpenGL Context (no share) and multiple GLSL programs with GLFW

*required libraries (-l) GL GLEW glfw*

>* You can found complete and working examples in this git repos: 
	* [My Utility For TheBookOfShader & ShaderToy](https://github.com/musicrizz/MyUtilityForTheBookOfShaderEShaderToy)


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
	}
);

while (!glfwWindowShouldClose(OpenGLContext::getCurrent())) {
		
	//DIsplay
		
	glfwPollEvents(); //  It MUST be in the main thread
		
}
OpenGLContext::destroyAll();

glfwTerminate();
	
```

* create multiple program in one context : 
*for example in previous CONTEX_1 two program with uniform buffer and one program in CONTEX_2*

```cpp

//CONTEX 1
OpenGLContext::makecurrent(CONTEX_1);
ShaderMap::createProgram(SIMPLE_TRIANGLE, "simpleTriangle_vrtx.glsl", "simpleTriangle_frag.glsl");
ShaderMap::createProgram(POINT_SPRITE, "PointSprite_vertx.glsl", "PointSprite_frag.glsl");

unsigned int uniform_binding_point = 2;
ShaderMap::bindingUniformBlocks("CommonUniform", uniform_binding_point);
glBindBufferBase(GL_UNIFORM_BUFFER, uniform_binding_point, buffers[UNIFORM]);
//......other OpenGl stuff

//CONTEXT 2
OpenGLContext::makecurrent(CONTEX_2);
ShaderMap::createProgram(TEXTURE_CAM, "CameraTexture_vertx.glsl", "CameraTexture_frag.glsl");
//.....other OpenGl stuff

while (!glfwWindowShouldClose(OpenGLContext::getCurrent())) {

	OpenGLContext::makecurrent(CONTEX_1);
			//DIsplay CONTEX 1
	OpenGLContext::swapBuffers();
	OpenGLContext::releaseContex();
	
	//Swap Context ;)
		
	OpenGLContext::makecurrent(CONTEX_2);
			//DIsplay CONTEX 2
	OpenGLContext::swapBuffers();
	OpenGLContext::releaseContex();
		
	glfwPollEvents(); //  It MUST be in the main thread
		
}
OpenGLContext::destroyAll();

glfwTerminate();


```

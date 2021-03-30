# MyContext
Simple utility to menage multiple OpenGL Context (no share) and multiple GLSL programs with GLFW

*required libraries (-l) GL GLEW glfw*

There are also an utility TempoMap to create a map of simple Tempo and Timer.

* You can found complete and working examples in this git repos: 
	* [My Utility For TheBookOfShader & ShaderToy](https://github.com/musicrizz/MyUtilityForTheBookOfShaderEShaderToy)
	* [Multiple Context GLFW example](https://github.com/musicrizz/Multiple-Context-GLFW-example)


-----------------------------------

How to use TempoMap : 

(*TempoMap is ThreadSafe*)

* create a simple tempo : 

*the tempo is created at the first call of* `TempoMap::getElapsedMill( std:: string );`  
*there are also other methods* `getElapsedMicro` , `getElapsedNano` ...

```cpp
	
const char* SIMPLE_TIMER = "Simple_Timer";

while(true)  {
	if(TempoMap::getElapsedMill(SIMPLE_TIMER) >= 1000)  {

		std::cout<<"hello"<<std::endl; //hello will be printed each second

		TempoMap::updateStart(SIMPLE_TIMER);
	}
}

```

* create Timer : 

	`static void createTimer(std::string name, void (*pFunc)(), unsigned long long int interval, long long int timeout = -1, bool started = true);`
			
*name*     = map key

*pFunc*    = function to execute at interval

*interval* = interval in millis

*timeout*  = in millis , if negative the timer is infinite

*started*  = boolean flag to start at creation

The timers can start, stop and delete from the map

```cpp

	std::string timer_simple = "timer simple name";	
	//Simple Timer - execute function every 400 millis
	TempoMap::createTimer(timer_simple, []()->void{
		std::cout<<"test timer"<<std::endl;
	}, 400);
	
	//-------
	
	std::string timer_with_timeout = "timer timeout name";	
	//Timer with timeout - execute function every 1,5 seconds ,
	//and stop after 5 seconds
	TempoMap::createTimer(timer_simple, []()->void{
		std::cout<<"test timer"<<std::endl;
	}, 1500, 5000 );
	
	//the timers if ended or stopped can be restarted ;) 
	TempoMap::startTimer(timer_with_timeout);
	

```

----------------------------------------

How to use multiple GLFW Contex :

* create two OpenGL context : *GLFW VERSION : 3.3.2 X11 GLX EGL OSMesa *

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
OpenGLContext::createContext(CONTEX_1, 400, 400, NULL, true, false, true); //CONTEXT 1

OpenGLContext::createContext(CONTEX_2, 400, 400, NULL, true, false, true); //CONTEXT 2

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

* create multiple glsl programs in one context : 
*for example in the following code, we use previous CONTEX_1 to create two program with uniform buffer and in CONTEX_2 I create a standard glsl program*

  complete example is [MultipleContext](https://github.com/musicrizz/Multiple-Context-GLFW-example) or //TOdo

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

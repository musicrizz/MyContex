# MyContext
Simple utility to menage multiple OpenGL Context (no share) and multiple GLSL programs with GLFW

*required libraries (-l) GL GLEW glfw*

There are also an utility TempoMap to create a map of simple Tempo and Timer.

* You can found complete and working examples in this git repos: 
	* [MyFragmentsLoader](https://github.com/musicrizz/MyFragmentsLoader)
	* [Multiple Context GLFW](https://github.com/musicrizz/Multiple-Context-GLFW-example)


-----------------------------------

How to use TempoMap : 

(*TempoMap is ThreadSafe*)

* create a simple tempo : 

*the tempo is created at the first call of* `TempoMap::getElapsedMill( std:: string );`  
*there are also other methods* `getElapsedMicro` , `getElapsedNano` ...

```cpp
	
const char* SIMPLE_TEMPO = "Simple_Tempo";

while(true)  {
	if(TempoMap::getElapsedMill(SIMPLE_TEMPO) >= 1000)  {

		std::cout<<"hello"<<std::endl; //hello will be printed each second

		TempoMap::updateStart(SIMPLE_TEMPO);
	}
}

```

* create Timer :    
*The pFunc will be executed in another thread. Use simple function that don't take much time,   
soon I have to implement and add a ThreadPool* 

	```cpp
	
	static void createTimer(
						std::string name,             // map key
						std::function<void()> f,     // function to execute at interval
						ulong interval,              // interval in millis
						long long int timeout = -1,  //in millis , if negative the timer is infinite
						bool started = true);       //boolean flag to start at creation
	```
			

The timers can start, stop and delete from the map

```cpp

	//Simple Timer - execute function every 400 millis
	TempoMap::createTimer("timer1", []()->void{
		std::cout<<"test timer"<<std::endl;
	}, 400);
	
	//-------
	
	//Timer with timeout - execute function every 1,5 seconds ,
	//and stop after 5 seconds
	TempoMap::createTimer("timer2", []()->void{
		std::cout<<"test timer"<<std::endl;
	}, 1500, 5000 );
	
	//the timers that ended or was stopped can be restarted.
	TempoMap::startTimer(timer_with_timeout);
	

```

----------------------------------------

How to use multiple GLFW Contex :

* create two OpenGL context : *GLFW VERSION : 3.3.2  *

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
	
//Contexts creation 

const char *CONTEX_1 = "ctx1", *CONTEX_2 = "ctx_2";

// CONTEXT_1
OpenGLContext::createContext(CONTEX_1,  // name 
						400,      // window width
						400,      // window height
						NULL,     // pointer to GLFWmonitor*
						true,     // window is visible
						false,    // window is decorated
						true);    // window trasparent framebuffer

OpenGLContext::createContext(CONTEX_2, 400, 400, NULL, true, false, true); //CONTEXT_2

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
	
	//in the main thread you have to swap context	
	
	OpenGLContext::makecurrent(CONTEX_1);
			//DIsplay CONTEX 1 ...
	OpenGLContext::swapBuffers();
	OpenGLContext::releaseContex();
	
		
	OpenGLContext::makecurrent(CONTEX_2);
			//DIsplay CONTEX 2 ...
	OpenGLContext::swapBuffers();
	OpenGLContext::releaseContex();
	
		
	glfwPollEvents(); //  It MUST be in the main thread
		
}
OpenGLContext::destroyAll();

glfwTerminate();
	
```

* create multiple glsl programs in one context :   
*for example in the following code, I use previous CONTEX_1 to create two program with uniform buffer and in CONTEX_2 to create a standard glsl program*   

PS: * at the moment only Vertex and Fragment , .. soon Geometry Shader*


```cpp

//CONTEX 1
OpenGLContext::makecurrent(CONTEX_1);
ShaderMap::createProgram(PGR_1, "vrtx.glsl", "pgr1_frag.glsl");
ShaderMap::createProgram(PGR_2, "vrtx.glsl", "pgr2_frag.glsl");

unsigned int uniform_binding_point = 2;
ShaderMap::bindingUniformBlocks("CommonUniform", uniform_binding_point);
glBindBufferBase(GL_UNIFORM_BUFFER, uniform_binding_point, buffers[UNIFORM]);
//......other OpenGl stuff

//CONTEXT 2
OpenGLContext::makecurrent(CONTEX_2);
ShaderMap::createProgram(TEXTURE_CAM, "another_vertex.glsl", "another_frag.glsl");
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
	
	
	//the events of keyboard or mouse ecc will be handled 
	//by the last current context - OpenGLContext::makecurrent(..)
		
	glfwPollEvents(); //  It MUST be in the main thread
		
}
OpenGLContext::destroyAll();

glfwTerminate();


```

# MyContex
*Simple utility to menage multiple OpenGL Context (no share) and multiple GLSL programs with GLFW*
<hr/> 
required libraries (-l) GL GLEW glfw


uniform buffer

```
ShaderMap::createProgram("pgr1", "shaders/base_vert.glsl", "shaders/base_frag.glsl");
cout<<OpenGLerror::check("CREAZIONE PROGRAMMA PGR1")<<endl;

ShaderMap::createProgram("pgr2", "shaders/test_uni_vert.glsl", "shaders/test_uni_frag.glsl");
cout<<OpenGLerror::check("CREAZIONE PROGRAMMA PGR2")<<endl;

unsigned int binding_point = 1;
ShaderMap::bindingUniformBlocks("ExampleBlock", binding_point);
glBindBufferBase(GL_UNIFORM_BUFFER, binding_point, buffs[UNIFORM]);
```
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<fstream>
#include<string>

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char *src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);
	
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char *message = new char[length];
		glGetShaderInfoLog(id, length, &length, message);
		std::cout<<"Failed to compile"<<
			(type == GL_VERTEX_SHADER ? "vertex" : "fragment")
			<<" shader!"<<std::endl;
		std::cout<<message<<std::endl;
		glDeleteShader(id);
		delete message;
		return 0;
	}
	return id;
}

static int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program =  glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	
	glLinkProgram(program);
	glValidateProgram(program);


	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

struct buffer_shader
{
	unsigned int buffer;
	unsigned int ibo;
	unsigned int shader;
};

struct buffer_shader create_buffer_shader(float x = 0.5)
{

	//prepare buffer
	float positions[12] = 
	{
		-x, -x,//0
		 x, -x,//1
		 x,  x,//2
		-x,  x //3
	};

	unsigned int indices[] =
	{
		0, 1, 2,
		2, 3, 0
	};


	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 8*sizeof(float), &(positions[0]), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);


	unsigned int ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(unsigned int), &(indices[0]), GL_STATIC_DRAW);

	std::string vertexShader = 
		"#version 330 core\n"
		"\n"
		"layout(location = 0) in vec4 position;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	gl_Position = position;\n"
		"}\n";


	std::string fragmentShader = 
		"#version 330 core\n"
		"\n"
		"layout(location = 0) out vec4 color;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	color = vec4(0.0f, 0.5f, 0.0f, 1.0f);\n"
		"}\n";
	unsigned int shader = CreateShader(vertexShader, fragmentShader);
	glUseProgram(shader);

	return {buffer, ibo, shader};

	//end prepare buffer
}





int main(void)
{
	//intialize the library
	
	if (!glfwInit())
		return -1;

	GLFWwindow *window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	if (glewInit() != GLEW_OK)
		std::cout<< "Error!"<<std::endl;

	std::cout<<glGetString(GL_VERSION)<<std::endl;


	float x = 0;
	while (!glfwWindowShouldClose(window))
	{
		if (x>1.0)
			x = 0;
		x += 0.01;
	struct buffer_shader bs = create_buffer_shader(x);
		//render
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);



		//end render
		glfwSwapBuffers(window);
		glfwPollEvents();
	glDeleteProgram(bs.shader);
	glDeleteBuffers(1, &(bs.buffer));
	glDeleteBuffers(1, &(bs.ibo));
	}


	glfwTerminate();
	return 0;
}

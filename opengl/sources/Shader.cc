#include"Shader.h"
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

#include"Renderer.h"

Shader::Shader(const std::string& filename)
	: m_FilePath(filename), m_RendererID(0)
{
	ParseShader();
	m_RendererID = CreateShader();
}
Shader::~Shader()
{
	glDeleteProgram(m_RendererID);
}


void Shader::Bind() const
{
	glUseProgram(m_RendererID);
}
void Shader::Unbind() const
{
	glUseProgram(0);
}

void Shader::SetUniform1i(const std::string& name, int value)
{
	glUniform1i(GetUniformLocation(name), value);
}
void Shader::SetUniform1f(const std::string& name, float value)
{
	glUniform1f(GetUniformLocation(name), value);
}
void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}
void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);	
}
void Shader::ParseShader()
{
	std::ifstream stream(m_FilePath);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};
	ShaderType type = ShaderType::NONE;

	std::string line;
	std::stringstream s[2];
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			s[int(type)] << line << "\n";
		}
	}

	m_VertexShader = s[0].str();
	m_FragmentShader = s[1].str();
}
unsigned int Shader::CreateShader()
{
	unsigned int program =  glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	
	glLinkProgram(program);
	glValidateProgram(program);


	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}
unsigned int Shader::CompileShader(unsigned int type)
{
	unsigned int id = glCreateShader(type);
	const char *src;
	if (GL_VERTEX_SHADER == type)
		src = m_VertexShader.c_str();
	else if (GL_FRAGMENT_SHADER == type)
		src = m_FragmentShader.c_str();

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
int Shader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	int location = glGetUniformLocation(m_RendererID, name.c_str());
	if (location == -1)
		std::cout<<"Warning: uniform "<<name<<" does not exist!"<<std::endl;
       
	m_UniformLocationCache[name] = location;	
	return location;
}


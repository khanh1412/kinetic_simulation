#ifndef _SHADER_H_
#define _SHADER_H_
#include<string>
#include<unordered_map>
#include<glm/glm.hpp>
class Shader
{
	private:
		std::string m_FilePath;
		unsigned int m_RendererID;
		std::string m_VertexShader;
		std::string m_FragmentShader;
		std::unordered_map<std::string, int> m_UniformLocationCache;
	public:
		Shader(const std::string& filename);
		~Shader();

		void Bind() const;
		void Unbind() const;

		//set uniform	
		void SetUniform1i(const std::string& name, int value);
		void SetUniform1f(const std::string& name, float value);
		void SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3);
		void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
	private:
		void ParseShader();
		unsigned int CreateShader();
		unsigned int CompileShader(unsigned int type);
		int GetUniformLocation(const std::string& name);
};

#endif

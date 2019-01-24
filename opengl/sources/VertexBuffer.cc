#include"VertexBuffer.h"
#include"Renderer.h"
#include<iostream>
VertexBuffer::VertexBuffer(const void *data, unsigned int size)
	: m_Dynamic(false), m_Size(size)
{
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
VertexBuffer::VertexBuffer(unsigned int size)
	: m_Dynamic(true), m_Size(size)
{
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}
VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}
void VertexBuffer::setData(const void *data, unsigned int size)
{
	if (not m_Dynamic) return;
	if (size > m_Size)
	{
		std::cout<<"Set a larger data than buffer size!"<<std::endl;
		__builtin_trap();
	}
	else 
	{
		if (size < m_Size)
			std::cout<<"Set a smaller data than buffer size!"<<std::endl;

		//void glBufferData(GLenum target, GLsizeiptr size, const GLvoid * data, GLenum usage);
		//void glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid * data);
		Bind();
		glBufferSubData(GL_ARRAY_BUFFER, static_cast<int>(0), size, data);
	}
}
void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}
void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

#ifndef _VERTEX_ARRAY_
#define _VERTEX_ARRAY_

#include"VertexBuffer.h"
//#include"VertexBufferLayout.h"

class VertexBufferLayout;
class VertexArray
{
	private:
		unsigned int m_RendererID;
	public:
		VertexArray();
		~VertexArray();

		void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
		void Bind() const;
		void Unbind() const;
};
#endif

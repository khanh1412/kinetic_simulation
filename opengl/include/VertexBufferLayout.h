#ifndef _VERTEXBUFFERLAYOUT_H_
#define _VERTEXBUFFERlAYOUT_H_
#include<vector>
#include"Renderer.h"
struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type);
};
class VertexBufferLayout
{
	private:
		std::vector<VertexBufferElement> m_Elements;
		unsigned int m_Stride;
	public:
		VertexBufferLayout()
			: m_Stride(0) {}

		void Push_float(unsigned int count);
		void Push_unsigned_int(unsigned int count);
		void Push_unsigned_char(unsigned int count);


		inline const std::vector<VertexBufferElement> GetElements() const {return m_Elements;}
		inline unsigned int GetStride() const {return m_Stride;}
};
#endif

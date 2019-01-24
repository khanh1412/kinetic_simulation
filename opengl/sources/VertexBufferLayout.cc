#include"VertexBufferLayout.h"
unsigned int VertexBufferElement::GetSizeOfType(unsigned int type)
{
	switch (type)
	{
		case GL_FLOAT: 		return 4;
		case GL_UNSIGNED_INT: 	return 4;
		case GL_UNSIGNED_BYTE: 	return 1;
	}
	return 0;
}

void VertexBufferLayout::Push_float(unsigned int count)
{
	m_Elements.push_back( {GL_FLOAT, count, GL_FALSE} );
	m_Stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
}
void VertexBufferLayout::Push_unsigned_int(unsigned int count)
{
	m_Elements.push_back( {GL_UNSIGNED_INT, count, GL_FALSE} );
	m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
}
void VertexBufferLayout::Push_unsigned_char(unsigned int count)
{
	m_Elements.push_back( {GL_UNSIGNED_BYTE, count, GL_TRUE} );
	m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
}

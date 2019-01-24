#ifndef _RENDERER_H_
#define _RENDERER_H_

#include<GL/glew.h>

#include"VertexArray.h"
#include"IndexBuffer.h"
#include"Shader.h"

#define ASSERT(x) if (!(x)) __builtin_trap()
class Renderer
{
	public:
		void Clear();
		void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};




#endif

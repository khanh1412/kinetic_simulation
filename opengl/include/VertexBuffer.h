#ifndef _VERTEX_BUFFER_H_
#define _VERTEX_BUFFER_H_

class VertexBuffer
{
	private:
		unsigned int m_RendererID;
		unsigned int m_Size;
		bool m_Dynamic;
	public:
		//size : size in bytes of data
		VertexBuffer(const void *data, unsigned int size);
		VertexBuffer(unsigned int size);
		~VertexBuffer();

		void setData(const void *data, unsigned int size);
		void Bind() const;
		void Unbind() const;
		inline unsigned int getID() const {return m_RendererID;}
};

#endif

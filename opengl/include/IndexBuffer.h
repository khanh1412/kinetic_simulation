#ifndef _INDEX_BUFFER_H_
#define _INDEX_BUFFER_H_

class IndexBuffer
{
	private:
		unsigned int m_RendererID;
		unsigned int m_Count;
		bool m_Dynamic;
	public:
		//size : size in bytes of data
		IndexBuffer(const unsigned int *data, unsigned int count);
		IndexBuffer(unsigned int count);
		~IndexBuffer();

                void setData(const unsigned int *data, unsigned int count);
		void Bind() const;
		void Unbind() const;

		inline unsigned int GetCount() const {return m_Count;}
		inline unsigned int getID() const {return m_RendererID;}
};

#endif

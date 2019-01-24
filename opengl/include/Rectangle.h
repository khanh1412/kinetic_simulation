#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_
#include"Engine.h"
class Rectangle: public Object
{
	private:
		glm::vec3 center;
		glm::vec3 vec1;
		glm::vec3 vec2;
	protected:
		void genLayout();
	public:
		void genPositions();
		void genIndices(glm::vec3& cam);
	public:
		Rectangle(glm::vec3& center, glm::vec3& vec1, glm::vec3& vec2, bool vb_dynamic=false, bool ib_dynamic=false);
		~Rectangle();
};
#endif

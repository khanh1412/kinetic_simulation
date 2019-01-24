#include"Rectangle.h"

Rectangle::Rectangle(glm::vec3& center, glm::vec3& vec1, glm::vec3& vec2, bool vb_dynamic, bool ib_dynamic)
	: center(center), vec1(vec1), vec2(vec2), Object(vb_dynamic, ib_dynamic)
{}
Rectangle::~Rectangle()
{}
void Rectangle::genLayout()
{
	layout = new VertexBufferLayout();
	layout->Push_float(3);
	layout->Push_float(2);
}
void Rectangle::genPositions()
{
	glm::vec3 tr = center + vec1 + vec2;
	glm::vec3 tl = center - vec1 + vec2;
	glm::vec3 bl = center - vec1 - vec2;
	glm::vec3 br = center + vec1 - vec2;

	size = 5*4*sizeof(float);
	float s_positions[5*4] = 
	{
		tr[0], tr[1], tr[2], 1, 1,//top right
		tl[0], tl[1], tl[2], 0, 1,//top left
		bl[0], bl[1], bl[2], 0, 0,//bottom left
		br[0], br[1], br[2], 1, 0 //bottom right
	};
	if (positions == nullptr) delete positions;
	positions = new float[5*4];
	for (int i=0; i<5*4; i++) positions[i] = s_positions[i];
}
void Rectangle::genIndices(glm::vec3& cam)
{
	unsigned int s_indices[6] = 
	{
		0, 1, 2,
		2, 3, 0
	};
	if (indices == nullptr) delete indices;
	indices = new unsigned int[6];
	for (int i=0; i<6; i++) indices[i] = s_indices[i];
	count = 6;
}

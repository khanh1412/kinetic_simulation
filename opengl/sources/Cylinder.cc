#include"Cylinder.h"
#include<cmath>
#include<iostream>
Cylinder::Cylinder(float x1, float y1, float z1, float x2, float y2, float z2, float r, float d)
	: r(r), d(d)
{
	pos1[0] = x1;
	pos1[1] = y1;
	pos1[2] = z1;
	pos2[0] = x2;
	pos2[1] = y2;
	pos2[2] = z2;
}
Cylinder::~Cylinder()
{}
int Cylinder::getPositions(float*& positions)
{
	float pos[3] = {pos2[0]-pos1[0], pos2[1]-pos1[1], pos2[2]-pos1[2]};
	//find e1 (e1*(pos2 - pos1) == 0)
	if (pos2[2] != pos1[2])
	{
		e1[0] = 1;
		e1[1] = 1;
		e1[2] = -(e1[0]*pos[0] + e1[1]*pos[1])/pos[2];
	}
	else if (pos2[1] != pos1[1])
	{
		e1[0] = 1;
		e1[2] = 1;
		e1[1] = -(e1[0]*pos[0] + e1[2]*pos[2])/pos[1];	
	}
	else
	{
		e1[1] = 1;
		e1[2] = 1;
		e1[0] = -(e1[1]*pos[1] + e1[2]*pos[2])/pos[0];	
	
	}
	{
	float k = std::sqrt(e1[0]*e1[0] + e1[1]*e1[1] + e1[2]*e1[2]);
	e1[0] = e1[0]/k;
	e1[1] = e1[1]/k;
	e1[2] = e1[2]/k;
	}
	//find e2 (e2*e1 == 0, e2*(pos2-pos1) == 0)
	float det, dx, dy, dz;
	if (e1[1]*pos[2] - e1[2]*pos[1] != 0)
	{
		det = e1[1]*pos[2] - e1[2]*pos[1];
		dy = -e1[0]*pos[2] + e1[2]*pos[0];
		dz = -e1[1]*pos[0] + e1[0]*pos[1];
		e2[0] = 1;
		e2[1] = dy/det;
		e2[2] = dz/det;
	}
	else if (e1[0]*pos[1] - e1[1]*pos[0] != 0)
	{
		det = e1[0]*pos[1] - e1[1]*pos[0];
		dx = -e1[2]*pos[1] + e1[1]*pos[2];
		dy = -e1[0]*pos[2] + e1[2]*pos[0];
		e2[0] = dx/det;
		e2[1] = dy/det;
		e2[2] = 1;
	}
	else
	{
		det = e1[0]*pos[2] - e1[2]*pos[0];
		dx = -e1[1]*pos[2] + e1[2]*pos[1];
		dz = -e1[0]*pos[1] + e1[1]*pos[0];
		e2[0] = dx/det;
		e2[1] = 1;
		e2[2] = dz/det;
	}
	
	{
	float k = std::sqrt(e2[0]*e2[0] + e2[1]*e2[1] + e2[2]*e2[2]);
	e2[0] = e2[0]/k;
	e2[1] = e2[1]/k;
	e2[2] = e2[2]/k;
	}

	//std::cout<<"e1 = ("<<e1[0]<<", "<<e1[1]<<", "<<e1[2]<<")"<<std::endl;
	//std::cout<<"e2 = ("<<e2[0]<<", "<<e2[1]<<", "<<e2[2]<<")"<<std::endl;


	//

        float texCoordx1, texCoordy1, texCoordx2, texCoordy2;
        float x1, y1, z1, x2, y2, z2;

	nr = static_cast<int>((2*pi)/d);

	int count = 2 * 5* (nr+1);
	positions = new float[count];

	float *ptr = &(positions[0]);

	for (int i=0; i<=nr; i++)
	{
		float alpha = static_cast<float>(i)*2*pi/nr;
		//std::cout<<alpha<<std::endl;
                float x = r*(std::cos(alpha)*e1[0] + std::sin(alpha)*e2[0]);
                float y = r*(std::cos(alpha)*e1[1] + std::sin(alpha)*e2[1]);
                float z = r*(std::cos(alpha)*e1[2] + std::sin(alpha)*e2[2]);


		x1 = pos1[0] + x;
		y1 = pos1[1] + y;
		z1 = pos1[2] + z;

		texCoordx1 = static_cast<float>(i)/nr;
		//std::cout<< std::sqrt(x*x + y*y + z*z) <<std::endl;
		texCoordy1 = 1;

		x2 = pos2[0] + x;
		y2 = pos2[1] + y;
		z2 = pos2[2] + z;
		
		texCoordx2 = static_cast<float>(i)/nr; 
		texCoordy2 = 0;


		ptr[0] = x1;
		ptr[1] = y1;
		ptr[2] = z1;
		ptr[3] = texCoordx1; 
		ptr[4] = texCoordy1;
		ptr += 5;
		ptr[0] = x2;
		ptr[1] = y2;
		ptr[2] = z2;
		ptr[3] = texCoordx2;
		ptr[4] = texCoordy2;
		ptr += 5;

		//std::cout<<x1<<" : "<<y1<<" : "<<z1<<std::endl;
	}
	//std::cout<<count<<":"<<nr<<std::endl;


	//__builtin_trap();
	return count;
}
int Cylinder::getIndices(float *cam_pos, unsigned int*& indices)
{

	float cam[3];
        cam[0] = cam_pos[0] - pos1[0];
	cam[1] = cam_pos[1] - pos1[1];
        cam[2] = cam_pos[2] - pos1[2];

	std::vector<int> out_vec;

	for (int i=0; i<nr; i++)
	{
		int tl = 2*i;
		int bl = 2*i+1;
		int tr = 2*i+2;
		int br = 2*i+3;




                float alpha = (0.5+static_cast<float>(i))*2*pi/nr;

                float x = r*(std::cos(alpha)*e1[0] + std::sin(alpha)*e2[0]);
                float y = r*(std::cos(alpha)*e1[1] + std::sin(alpha)*e2[1]);
                float z = r*(std::cos(alpha)*e1[2] + std::sin(alpha)*e2[2]);
		//std::cout<<x*cam[0] + y*cam[1] + z*cam[2]<<std::endl;
		if (x*cam[0] + y*cam[1] + z*cam[2] > 0)
		{
                        out_vec.push_back(bl);
                        out_vec.push_back(br);
                        out_vec.push_back(tl);
                        out_vec.push_back(tl);
                        out_vec.push_back(tr);
                        out_vec.push_back(br);
		}
	}
	int hm_indices = out_vec.size();
	indices = new unsigned int[hm_indices];
	for (int i=0; i<hm_indices; i++)
		indices[i] = out_vec.at(i);
	return hm_indices;
}

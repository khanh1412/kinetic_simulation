#ifndef _ENVIRONMENT_H_
#define _ENVIRONMENT_H_
#include<cmath>
#include<vector>
#include<iostream>
struct vector
{
	double x;
	double y;
	double z;
	double length() const
	{
		return std::sqrt(x*x + y*y + z*z);
	}
	friend double dotproduct(const vector& a, const vector& b);
	friend vector operator-(const vector& obj);
	friend vector operator*(const vector& obj, double dt);
	friend vector operator/(const vector& obj, double dt);
	friend vector operator+(const vector& a, const vector& b);
	friend vector operator-(const vector& a, const vector& b);
};
double dotproduct(const vector& a, const vector& b)
{
	return a.x*b.x + a.y*b.y + a.z*b.z;
}
vector operator-(const vector& obj)
{
	return vector({-obj.x, -obj.y, -obj.z});
}
vector operator*(const vector& obj, double dt)
{
	return vector({obj.x*dt, obj.y*dt, obj.z*dt});
}
vector operator/(const vector& obj, double dt)
{
	return vector({obj.x/dt, obj.y/dt, obj.z/dt});
}
vector operator+(const vector& a, const vector& b)
{
	return vector({a.x + b.x, a.y + b.y, a.z + b.z});
}
vector operator-(const vector& a, const vector& b)
{
	return vector({a.x - b.x, a.y - b.y, a.z - b.z});
}
class Object
{
	public:
		Object(){}
		virtual ~Object(){}
		virtual void move(double dt) = 0;
		virtual void move(double dt, const vector& a) = 0;
		virtual void details()=0;
};
class Sphere: public Object
{
	public:
		vector pos;
		double r;
		double mass;
		vector vel;
		Sphere(const vector& pos, double r = 1, double mass = 1, const vector& vel = vector({0,0,0}))
			: Object(), pos(pos), r(r), mass(mass), vel(vel)
		{}
		void move(double dt)
		{
			pos = pos + vel * dt;
		}
		void move(double dt, const vector& a)
		{
			vector vel_before = vel;
			vector vel_after = vel + a * dt;
			vector vel_avg = (vel_before + vel_after)/2;

			pos = pos + vel_avg * dt;
			vel = vel_after;	
		}
		vector momentum()
		{
			return vel * mass;
		}
		void details()
		{
			std::cout<<"\tSphere"<<std::endl;
			std::cout<<"\t\t      mass: "<<mass<<std::endl;
			std::cout<<"\t\t         r: "<<r<<std::endl;
			std::cout<<"\t\t x,  y,  z: "<<pos.x<<" "<<pos.y<<" "<<pos.z<<std::endl;
			std::cout<<"\t\tvx, vy, vz: "<<vel.x<<" "<<vel.y<<" "<<vel.z<<std::endl;
		}
};
class Plane: public Object
{
	public:
		vector point;
		vector norm;
		Plane(const vector& point, const vector& norm = vector({0, 0, 1}))
			: Object(), point(point), norm(norm/norm.length())
		{}
		void move(double dt) {}
		void move(double dt, const vector& a) {}
		void details()
		{
			std::cout<<"\tPlane"<<std::endl;
			std::cout<<"\t\tpoint: "<<point.x<<" "<<point.y<<" "<<point.z<<std::endl;
			std::cout<<"\t\tnorm : "<<norm.x<<" "<<norm.y<<" "<<norm.z<<std::endl;
		}
};
class Event
{
	public:
		Event(Object *obj1, Object *obj2)
		{
			Plane* plane1 = dynamic_cast<Plane*>(obj1);
			Plane* plane2 = dynamic_cast<Plane*>(obj2);
			Sphere* sphere1 = dynamic_cast<Sphere*>(obj1);
			Sphere* sphere2 = dynamic_cast<Sphere*>(obj2);

			if (plane1 != nullptr and plane2 != nullptr)
				return;
			else if (sphere1 != nullptr and plane2 != nullptr)
				Sphere2Plane(*sphere1, *plane2);
			else if (plane1 != nullptr and sphere2 != nullptr)
				Sphere2Plane(*sphere2, *plane1);
			else if (sphere1 != nullptr and sphere2 != nullptr)
				Sphere2Sphere(*sphere1, *sphere2);
			else
				__builtin_trap();
		}
		void Sphere2Sphere(Sphere& obj1, Sphere& obj2)
		{
			double dist = (obj1.pos - obj2.pos).length();
			if (dist > (obj1.r + obj2.r)) return;

			vector vG = (obj1.momentum() + obj2.momentum())/(obj1.mass + obj2.mass);
			obj1.vel = vG*2 - obj1.vel;	
			obj2.vel = vG*2 - obj2.vel;
		}
		void Sphere2Plane(Sphere& obj, Plane& table)
		{
			double dot = dotproduct(table.norm, (obj.pos - table.point));
			dot = (dot >= 0) ? dot : -dot;

			if (dot > obj.r) return;

			obj.vel = -obj.vel;
		}
		~Event(){}
};
class Environment
{
	public:
		double timer;
		double dt;
		vector g;
		std::vector<Object*> ObjectsList;
		std::vector<Event*> EventsList;
		Environment(double dt): timer(0), dt(dt)
		{
			g = vector({0, 0, -9.8});
		}
		~Environment()
		{
			for (size_t i=0; i<EventsList.size();++i)
				delete EventsList[i];
			EventsList.clear();
			ObjectsList.clear();
		}
		void pushObject(Object *obj)
		{
			ObjectsList.push_back(obj);
		}
		void nextState()
		{
			size_t count = ObjectsList.size();
			for (size_t i=0; i<count; ++i)
				ObjectsList[i]->move(dt, g);
			for (size_t i1=0; i1<count; ++i1)
			for (size_t i2=i1+1; i2<count; ++i2)
			{
				auto obj1 = ObjectsList[i1];
				auto obj2 = ObjectsList[i2];
				EventsList.push_back(new Event(obj1, obj2));
			}
			timer += dt;
			#ifndef NDEBUG
			details();
			#endif
		}
		void details()
		{
			std::cout<<"Environment: time "<<timer<<std::endl;
			for (size_t i=0; i<ObjectsList.size(); ++i)
				ObjectsList[i]->details();
		}
};
#endif

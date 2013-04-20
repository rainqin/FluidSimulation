#include "Vector\Vector.hpp"

#ifndef field_flag 
#define field_flag
struct myField{
	int index;
	Vector3f Wgradient;
	double Wlaplaceian;
	double W;
};


class Particle {
public:
	int pNum;
	float mass;
	double density;
	Vector3f acc;
	Vector3f position;
	Vector3f velocity;
	Vector3f force;
	Vector3f csGradient;
	double csLaplaceian;

	bool flagX1;
	bool flagX2;
	bool flagY1;
	bool flagY2;
	bool flagZ1;
	bool flagZ2;

	myField* inField;
	int inFieldCount;
	
	Particle();
	~Particle();

	void setPosition(Vector3f position);
	void setVelocity(Vector3f velocity);
	void setPressure(Vector3f pressure);

	Vector3f getPosition();
	Vector3f getVelocity();
	Vector3f getPressure();

	void draw();
	void clearInField();
	void applyForce();
};
#endif 

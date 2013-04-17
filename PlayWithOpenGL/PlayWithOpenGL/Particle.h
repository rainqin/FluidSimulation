#include "Vector\Vector.hpp"
#include <gl\glut.h>

class Particle {
private:
	Vector3f position;
	Vector3f velocity;
	Vector3f pressure;

public:
	Particle(Vector3f position, Vector3f velocity, Vector3f pressure);
	Particle(Vector3f position, Vector3f velocity);
	Particle(Vector3f position);
	Particle();
	~Particle();

	void setPosition(Vector3f position);
	void setVelocity(Vector3f velocity);
	void setPressure(Vector3f pressure);

	Vector3f getPosition();
	Vector3f getVelocity();
	Vector3f getPressure();

	void draw();
};
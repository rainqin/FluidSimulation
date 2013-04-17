#include "Particle.h"

Particle::Particle(Vector3f position, Vector3f velocity, Vector3f pressure) {
	this->position = position;
	this->velocity = velocity;
	this->pressure = pressure;
}

Particle::Particle(Vector3f position, Vector3f velocity) {
	this->position = position;
	this->velocity = velocity;
}

Particle::Particle(Vector3f postion) {
	this->position = position;
}

Particle::Particle(){

}

Particle::~Particle(){

}

void Particle::setPosition(Vector3f position) {
	this->position = position;
}

void Particle::setVelocity(Vector3f velocity) {
	this->velocity = velocity;
}
	
void Particle::setPressure(Vector3f pressure) {
	this->pressure = pressure;
}

Vector3f Particle::getPosition() {
	return position;
}

Vector3f Particle::getVelocity() {
	return velocity;
}
	
Vector3f Particle::getPressure() {
	return pressure;
}

void Particle::draw() {
	glPushMatrix();
	GLUquadricObj* quadratic;
	quadratic =gluNewQuadric();  
	glTranslatef(position.x, position.y, position.z); 	 
	gluSphere(quadratic, 0.25, 200, 160);   /* draw sun */
	glPopMatrix();
}
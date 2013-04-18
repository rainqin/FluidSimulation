#include "Particle.h"
#include <gl\glut.h>
#include <iostream>

#define delta_t 0.0001
#define damping 0.3

Particle::Particle(){
	inFieldCount = 0;
	pNum = 125;
	mass = 0.02;
	force = make_vector(0.0, 0.0, 0.0);
	acc = make_vector(0.0, 0.0, 0.0);
	velocity = make_vector(0.0, 0.0, 0.0);
	density = 0;
	csGradient = make_vector(0.0, 0.0, 0.0);
	csLaplaceian = 0;
	inFieldCount = 0;

	inField = new myField[pNum];
	this->clearInField();
}

Particle::~Particle(){
	delete [] inField;
}

void Particle::draw() {
	glPushMatrix();
	GLUquadricObj* quadratic;
	quadratic =gluNewQuadric();  
	glTranslatef(position.x, position.y, position.z); 	 
	gluSphere(quadratic, 0.25, 200, 160);   /* draw sun */
	glPopMatrix();
}

void Particle::clearInField() {
	for (int i = 0; i < pNum; i++) {
		inField[i].index = 0;
	}
}

void Particle::applyForce() {
	float constraint = 3;
	
	acc = force / mass;

	velocity += acc * delta_t;
	//std::cout<<"Prev: "<<position<<std::endl;
	position += velocity * delta_t;

	if (position.y >constraint) {
		//position.y = constraint;
		velocity.y = -damping * velocity.y;
	}

	if (position.y < 0) {
		//position.y = 0;
		velocity.y = -damping * velocity.y;
	}
	if (position.x < -constraint) {
		//position.x = -constraint;
		velocity.x = -damping * velocity.x;
	}
	if (position.x > constraint) {
		//position.x = constraint;
		velocity.x = -damping * velocity.x;
	} 
	if (position.z < -constraint) {
		//std::cout<<"Prev: "<<position<<std::endl;
		//position.z = -constraint;
		velocity.z = -damping * velocity.z;
		//std::cout<<"After: "<<position<<std::endl;
	} 
	if (position.z > constraint) {
		//position.z = constraint;
		velocity.z = -damping * velocity.z;
	}
}
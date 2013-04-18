#include "Particle.h"
#include <gl\glut.h>

#define delta_t 0.001
#define damping 0.3

Particle::Particle(){
	inFieldCount = 0;
	pNum = 64;
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

	position += velocity * delta_t;
	if (position.y < 0.2) {
		acc = -damping * force / mass;
	} else {
		acc = force / mass;
	}
	velocity += acc * delta_t;
}
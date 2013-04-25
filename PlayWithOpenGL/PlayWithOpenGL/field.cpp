#include "field.h"
#include <math.h>
#define FACTOR	945/32/3.1415926
#define density0 1.0
#define my_k 1000 
#define my_u 0.3
#define my_sigma 1.0
#define my_g 98.1

Field::Field(Particle* particle, float scope, int num) {
	p = particle;
	fieldScope = scope;
	particleNum = num;
}

Field::~Field() {

}

void Field::CalculateField() {
	for (int i = 0; i < particleNum; i++) {
		p[i].force = make_vector(0.0, 0.0, 0.0);
		p[i].density = 0;
		p[i].csGradient = make_vector(0.0, 0.0, 0.0);
		p[i].csLaplaceian = 0;
		p[i].inFieldCount = 0;
	}
	for (int i = 0; i < particleNum - 1; i++) {
		for (int j = i + 1; j < particleNum; j++) {
			if (length(p[i].position - p[j].position) < fieldScope) {
				Vector3f Wgra = CalculateWgradient(p[i].position - p[j].position, fieldScope);
				double Wlap = CalculateWlaplaceian(p[i].position - p[j].position, fieldScope);
				double W = CalculateW(p[i].position - p[j].position, fieldScope);

				p[i].inField[p[i].inFieldCount].index = j;
				p[i].inField[p[i].inFieldCount].Wgradient = Wgra;
				p[i].inField[p[i].inFieldCount].Wlaplaceian = Wlap;
				p[i].inField[p[i].inFieldCount++].W = W;
				p[i].density += p[j].mass * W;

				p[j].inField[p[j].inFieldCount].index = i;
				p[j].inField[p[j].inFieldCount].Wgradient = -Wgra;
				p[j].inField[p[j].inFieldCount].Wlaplaceian = Wlap;
				p[j].inField[p[j].inFieldCount++].W = W;
				p[j].density += p[i].mass * W;
			}
		}
	}

	for (int i = 0; i < particleNum; i++) {
		for (int j = 0; j < p[i].inFieldCount - 1; j++) {
			//Particle q = p[p[i].inField[j].index];
			double pressi = my_k * (p[i].density - density0);
			double pressj = my_k * (p[p[i].inField[j].index].density - density0);

			p[i].force += p[p[i].inField[j].index].mass * (pressi + pressj) / 2 / p[p[i].inField[j].index].density * p[i].inField[j].Wgradient;  //pressure
			p[i].force += my_u * p[p[i].inField[j].index].mass * (p[p[i].inField[j].index].velocity - p[i].velocity) / p[p[i].inField[j].index].density * p[i].inField[j].Wlaplaceian; //viscosity
			
			p[i].csLaplaceian += p[p[i].inField[j].index].mass / p[p[i].inField[j].index].density * p[i].inField[j].Wlaplaceian;
			p[i].csGradient += p[p[i].inField[j].index].mass / p[p[i].inField[j].index].density * p[i].inField[j].Wgradient; 
		}
		p[i].force += -my_sigma * p[i].csLaplaceian * normalize(p[i].csGradient); //surface tension
		p[i].force -= my_g * make_vector<float>(0.0, 1.0, 0.0);                   //gravity
	}
	for(int i=0;i<particleNum;i++)
		p[i].acc=p[i].force/p[i].mass;
}

Vector3f Field::CalculateWgradient(Vector3f r, float h) {
	return -FACTOR * r / pow(h, 9) * (h - length(r)) * (h * h - length(r));
}

double Field::CalculateWlaplaceian(Vector3f r, float h) {
	return -FACTOR / pow(h, 9) * (h * h - length_squared(r)) * (3 * h * h - 7 * length_squared(r));
}

double Field::CalculateW(Vector3f r, float h) {
	double squareR = length(r);
	double squareH = h;
	if (squareR > squareH) {
		return 0;
	} else {
		return 315 / 64 /3.1415926 / pow(h, 9) * pow(squareH - squareR, 3);
	}
}

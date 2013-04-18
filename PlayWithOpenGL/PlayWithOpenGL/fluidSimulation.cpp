#include "stdafx.h"
#include "fluidSimulation.h"
#include "Particle.h"
#include "field.h"

using namespace std;

#define M_PI 3.1415926
#define scope 0.75

GLfloat viewX = 0;
GLfloat xrotate = 0, yrotate = 0;
Vector3f loc_init = {5, 5, 5};
Vector3f target_init = {0, 0, 0};
Vector3f up_init = { 0, 1, 0};
int screenX = 500, screenY = 500;

GLboolean mouserdown = GL_FALSE;
GLboolean mouseldown = GL_FALSE;
GLboolean mousemdown = GL_FALSE;

int wid = 4;
int len = 4;
int hei = 4;
int particleNum = wid * len * hei;
int mousex, mousey;
Camera* camera;
Particle* particles;
Field* field;

void init(void) {
	camera = new Camera(loc_init, target_init, up_init);
	particles = new Particle[particleNum]();
	field = new Field(particles, scope, particleNum);

	for (int i = 0; i < len; i++) {
		for (int j= 0; j < wid; j++) {
			for (int z = 0; z < hei; z++) {
				particles[i * len * wid + j * wid + z].position = make_vector<float>(i * 0.5, z * 0.5, j* 0.5); 
			}
		}
	}

	GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 };
	glClearColor (1.0, 1.0, 1.0, 0.0);
	glShadeModel (GL_SMOOTH);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);

	GLfloat background_light_position[] = {10, 10, 10, 1};
	GLfloat background_light_ambient[] = {1, 1, 1, 1};
	GLfloat background_light_diffuse[] = {1, 1, 1, 1};
	GLfloat background_light_specular[] = {1, 1, 1, 1};

	glLightfv(GL_LIGHT1, GL_POSITION, background_light_position);
	glLightfv(GL_LIGHT1, GL_AMBIENT,  background_light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE,  background_light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, background_light_specular);


	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
}

void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt (camera->GetLoc().x, camera->GetLoc().y, camera->GetLoc().z, 
				camera->GetTarget().x, camera->GetTarget().y, camera->GetTarget().z, 
				camera->GetUp().x, camera->GetUp().y, camera->GetUp().z);

	GLfloat sun_light_position[] = {0.0f, 0.0f, 0.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);

	glColor3f (1.0, 1.0, 1.0);

	glPushMatrix();
	
	draw();

	glPopMatrix();
	glutSwapBuffers();
}

void reshape (int w, int h)
{
	screenX = w;
	screenY = h;
	glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void MouseFunc(int button, int state, int x, int y) {
	if(state == GLUT_DOWN)
	{
		if(button == GLUT_RIGHT_BUTTON) mouserdown = GL_TRUE;
		if(button == GLUT_LEFT_BUTTON) mouseldown = GL_TRUE;
		if(button == GLUT_MIDDLE_BUTTON)mousemdown = GL_TRUE;
	}
	else
	{
		if(button == GLUT_RIGHT_BUTTON) mouserdown = GL_FALSE;
		if(button == GLUT_LEFT_BUTTON) mouseldown = GL_FALSE;
		if(button == GLUT_MIDDLE_BUTTON)mousemdown = GL_FALSE;
	}
	mousex = x, mousey = y;
}

void MouseMotion(int x, int y)
{
	if(mouserdown == GL_TRUE)
	{      
		xrotate = (x - mousex) / 80.0f;     
		yrotate = (y - mousey) / 120.0f;
	}
	camera->RotateCamera(xrotate, yrotate);
	mousex = x, mousey = y;
	glutPostRedisplay();
}


void keyboard (unsigned char key, int x, int y)
{
	switch (key) {
	case 'w':
		camera->LenCamera(-0.5);
		break;
	case 's':
		camera->LenCamera(0.5);
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void release() {
	delete camera;
	delete [] particles;
}

void draw() {
	
	glColor3f(0.0, 0.0, 0.0);
	glutWireCube(5);

	field->CalculateField();

	for (int i = 0; i < particleNum; i++) {
		particles[i].applyForce();
		particles[i].draw();
	}
}


int _tmain(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (500, 500); 
	glutInitWindowPosition (100, 100);
	glutCreateWindow (argv[0]);
	init ();

	glutDisplayFunc(display); 
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(MouseFunc);    
	glutMotionFunc(MouseMotion); 

	glutMainLoop();

	release();
	return 0;
}
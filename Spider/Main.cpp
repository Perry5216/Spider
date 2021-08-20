#include <gl/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include "BmpLoader.h"

GLuint txtBody,txtLegs,txtEarth;
GLUquadricObj *Body, *Cylinder, *Earth;

BITMAPINFOHEADER bitmapInfoHeader;
unsigned char* bitmapData;

const int windowWidth = 800;
const int windowHeight = 600;

const float BASE_HEIGHT = 1;
const float LOWER_ARM_LENGTH = 1.8;
const float UPPER_ARM_LENGTH = 1.2;
const float TOP_ARM_LENGTH = 0.8;

int axis = 0;

float theta[3];
float earth[1];
float angle[6];

bool lowerArmDownOne, upperArmDownOne, topArmDownOne, lowerArmDownTwo, upperArmDownTwo, topArmDownTwo = true;

void rotateSide()
{
	if (lowerArmDownOne) angle[0] -= 0.25;
	else angle[0] += 0.25;

	if (angle[0] < 340) lowerArmDownOne = false;
	if (angle[0] > 360) lowerArmDownOne = true;

	if (upperArmDownOne) angle[1] -= 0.2;
	else angle[1] += 0.2;

	if (angle[1] < 300) upperArmDownOne = false;
	if (angle[1] > 315) upperArmDownOne = true;

	if (topArmDownOne) angle[2] -= 0.15;
	else angle[2] += 0.15;

	if (angle[2] < 45) topArmDownOne = false;
	if (angle[2] > 55) topArmDownOne = true;

	if (lowerArmDownTwo) angle[3] -= 0.25;
	else angle[3] += 0.25;

	if (angle[3] < 340) lowerArmDownTwo = false;
	if (angle[3] > 360) lowerArmDownTwo = true;

	if (upperArmDownTwo) angle[4] -= 0.2;
	else angle[4] += 0.2;

	if (angle[4] < 300) upperArmDownTwo = false;
	if (angle[4] > 315) upperArmDownTwo = true;

	if (upperArmDownTwo) angle[5] -= 0.1;
	else angle[5] += 0.1;

	if (angle[5] < 45) topArmDownTwo = false;
	if (angle[5] > 55) topArmDownTwo = true;

	theta[axis] += 0.2;
	if (theta[axis] > 360.0)
		theta[axis] -= 360.0;

	earth[0] += 0.5;
	if (earth[0] > 360.0)
		earth[0] -= 360.0;

	glutPostRedisplay();
}

void mouse(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		axis = 0;
	if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
		axis = 1;
	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		axis = 2;
}

//Draw Joint
void drawJoint()
{
	glPushMatrix();
	glScalef(0.2, 0.2, 0.2);
	gluSphere(Body, 0.5, 48, 48);
	glPopMatrix();
}

//body
void drawBase()
{
	glPushMatrix();
	glScalef(1.0, BASE_HEIGHT, 1.0);
	gluSphere(Body, 0.5, 48, 48);
	glPopMatrix();
}

//parts of the legs
void drawTopArm()
{
	glPushMatrix();
	glRotatef(-45, 0.0, 0.0, 1.0);
	glTranslatef(0.0, (TOP_ARM_LENGTH*1.2), 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	gluCylinder(Cylinder, 0.001f, 0.09f, 0.9f, 32, 32);
	glPopMatrix();
}

void drawUpperArm()
{
	glPushMatrix();
	glRotatef(-45, 0.0, 0.0, 1.0);
	glTranslatef(0.0, (UPPER_ARM_LENGTH), 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	gluCylinder(Cylinder, 0.08f, 0.1f, 1.15f, 32, 32);
	glPopMatrix();
}

void drawLowerArm()
{
	glPushMatrix();
	glTranslatef(0.0, (LOWER_ARM_LENGTH), 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	gluCylinder(Cylinder, 0.09f, 0.125f, 2.1f, 44, 44);
	glPopMatrix();
}

//drawleg
void drawLegOne()
{
	glRotatef(-40, 0.0, 0.0, 1.0);
	glScalef(0.6, 0.6, 0.6);

	glTranslatef(0.0, (BASE_HEIGHT * 0.5), 0.0);
	glRotatef(angle[0], 0.0, 0.0, 1.0);
	drawLowerArm();

	glTranslatef(0.0, LOWER_ARM_LENGTH, 0.0);
	glRotatef(angle[1], 0.0, 0.0, 1.0);
	drawUpperArm();
	drawJoint();

	glRotatef(-45, 0.0, 0.0, 1.0);
	glTranslatef(0.0, UPPER_ARM_LENGTH, 0.0);
	glRotatef(angle[2], 0.0, 0.0, 1.0);
	drawTopArm();
	drawJoint();
}

void drawLegTwo()
{
	glRotatef(-40, 0.0, 0.0, 1.0);
	glScalef(0.6, 0.6, 0.6);

	glTranslatef(0.0, (BASE_HEIGHT * 0.5), 0.0);
	glRotatef(angle[3], 0.0, 0.0, 1.0);
	drawLowerArm();

	glTranslatef(0.0, LOWER_ARM_LENGTH, 0.0);
	glRotatef(angle[4], 0.0, 0.0, 1.0);
	drawUpperArm();
	drawJoint();

	glRotatef(-45, 0.0, 0.0, 1.0);
	glTranslatef(0.0, UPPER_ARM_LENGTH, 0.0);
	glRotatef(angle[5], 0.0, 0.0, 1.0);
	drawTopArm();
	drawJoint();
}

void drawWorld()
{
	//draw the world
	glPushMatrix();
	glTranslatef(0, (-BASE_HEIGHT *1.02), 0);
	glBindTexture(GL_TEXTURE_2D, txtEarth);
	gluSphere(Earth, 1, 80, 80);
	glRotatef(earth[0], earth[0], 0, 1.0);
	glPopMatrix();
}

void drawPartsOfSpider()
{
	glBindTexture(GL_TEXTURE_2D, txtBody);
	//body
	glPushMatrix();
	drawBase();
	glPopMatrix();

	//back
	glPushMatrix();
	glTranslatef(0.0, 0.0, -(BASE_HEIGHT));
	glScalef(1.2, 1.0, 1.2);
	drawBase();
	glPopMatrix();

	//leg one
	glPushMatrix();
	glTranslatef(BASE_HEIGHT*0.3, -(BASE_HEIGHT*0.3), 0.0);
	drawLegOne();
	glPopMatrix();

	//leg two
	glPushMatrix();
	glTranslatef(-(BASE_HEIGHT * 0.3), -(BASE_HEIGHT*0.3), 0.0);
	glRotatef(180, 0, 1, 0);
	drawLegTwo();
	glPopMatrix();

	//leg three
	glPushMatrix();
	glRotatef(200, 0, 1, 0);
	glTranslatef(BASE_HEIGHT*0.3, -(BASE_HEIGHT*0.3), 0.0);
	drawLegOne();
	glPopMatrix();

	//leg four
	glPushMatrix();
	glRotatef(340, 0, 1, 0);
	glTranslatef(BASE_HEIGHT*0.3, -(BASE_HEIGHT*0.3), 0.0);
	drawLegTwo();
	glPopMatrix();

	//leg five
	glPushMatrix();
	glRotatef(160, 0, 1, 0);
	glTranslatef(BASE_HEIGHT*0.3, -(BASE_HEIGHT*0.3), 0.0);
	drawLegOne();
	glPopMatrix();

	//leg six
	glPushMatrix();
	glRotatef(20, 0, 1, 0);
	glTranslatef(BASE_HEIGHT*0.3, -(BASE_HEIGHT*0.3), 0.0);
	drawLegTwo();
	glPopMatrix();

	//leg seven
	glPushMatrix();
	glRotatef(220, 0, 1, 0);
	glTranslatef(BASE_HEIGHT*0.3, -(BASE_HEIGHT*0.3), 0.0);
	drawLegTwo();
	glPopMatrix();

	//leg eight
	glPushMatrix();
	glRotatef(320, 0, 1, 0);
	glTranslatef(BASE_HEIGHT*0.3, -(BASE_HEIGHT*0.3), 0.0);
	drawLegOne();
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, txtLegs);

	//Fang one
	glPushMatrix();
	glRotatef(290, 0, 1, 0);
	glTranslatef(BASE_HEIGHT*0.3, -(BASE_HEIGHT*0.3), 0.0);
	glScalef(0.3, 0.3, 0.3);
	drawLegOne();
	glPopMatrix();

	//Fang tw0
	glPushMatrix();
	glRotatef(250, 0, 1, 0);
	glTranslatef(BASE_HEIGHT*0.3, -(BASE_HEIGHT*0.3), 0.0);
	glScalef(0.3, 0.3, 0.3);
	drawLegOne();
	glPopMatrix();

	//eye one
	glPushMatrix();
	glRotatef(285, 0, 1, 0);
	glTranslatef((BASE_HEIGHT*0.4), (BASE_HEIGHT*0.3), 0.0);
	glScalef(0.7, 0.7, 0.7);
	drawJoint();
	glPopMatrix();

	//eye two
	glPushMatrix();
	glRotatef(255, 0, 1, 0);
	glTranslatef((BASE_HEIGHT*0.4), (BASE_HEIGHT*0.3), 0.0);
	glScalef(0.7, 0.7, 0.7);
	drawJoint();
	glPopMatrix();
}

void drawTheScene()
{

	glPushMatrix();
	glRotatef(-90, 90, 0, 0);
	drawWorld();
	glPopMatrix();
	glPushMatrix();
	glRotatef(270, 270, 0, 0);
	glScalef(0.05, 0.05, 0.05);
	drawPartsOfSpider();
	glPopMatrix();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	switch (axis)
	{
	case 0:glRotatef(theta[0], 1.0, 0.0, 0.0); break;
	case 1:glRotatef(theta[1], 0.0, 1.0, 0.0); break;
	case 2:glRotatef(theta[2], 0.0, 0.0, 1.0); break;
	}

	drawTheScene();
	glutSwapBuffers();
}

void loadTexture()
{
	glEnable(GL_TEXTURE_2D);
	bitmapData = LoadBitmapFile("earth.bmp", &bitmapInfoHeader);
	glGenTextures(1, &txtEarth);
	glBindTexture(GL_TEXTURE_2D, txtEarth);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth, bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	free(bitmapData);

	Earth = gluNewQuadric();
	gluQuadricDrawStyle(Earth, GLU_FILL);
	gluQuadricDrawStyle(Earth, GLU_SMOOTH);
	gluQuadricTexture(Earth, GL_TRUE);
	glPopMatrix();

	bitmapData = LoadBitmapFile("brown.bmp", &bitmapInfoHeader);
	glGenTextures(1, &txtBody);
	glBindTexture(GL_TEXTURE_2D, txtBody);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth, bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	free(bitmapData);

	Cylinder = gluNewQuadric();
	gluQuadricDrawStyle(Cylinder, GLU_FILL);
	gluQuadricDrawStyle(Cylinder, GLU_SMOOTH);
	gluQuadricTexture(Cylinder, GL_TRUE);

	bitmapData = LoadBitmapFile("gray.bmp", &bitmapInfoHeader);
	glGenTextures(1, &txtLegs);
	glBindTexture(GL_TEXTURE_2D, txtLegs);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth, bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	free(bitmapData);

	Body = gluNewQuadric();
	gluQuadricDrawStyle(Body, GLU_FILL);
	gluQuadricDrawStyle(Body, GLU_SMOOTH);
	gluQuadricTexture(Body, GL_TRUE);
}

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glColor3f(1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1, 1.2, 0.8, 10.0);

	loadTexture();

	//set up the lighting
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	//setting the light intestity trying to make it like a sun
	GLfloat AmbientLight[] = { 0.0,0.0,0.7,1.0 };
	GLfloat DiffuseLight[] = { 1.0,1.0,0.3,1.0 };
	GLfloat SpecularLight[] = { 1.0,1.0,1.0,1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);

	//set light pos
	GLfloat LightPos[] = { -1, 1, -0, 0 };
	glLightfv(GL_LIGHT0, GL_POSITION, LightPos);
}

int main(int argc, char** argv)
{
	//set the angle for the legs
	angle[0] = 359;
	angle[1] = 314;
	angle[2] = 54;
	angle[3] = 341;
	angle[4] = 301;
	angle[5] = 46;

	earth[0] = 180;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Anthony Perry - 21705596 - Spider Assignment");
	glEnable(GL_TEXTURE_2D);
	glutDisplayFunc(display);
	init();
	glutIdleFunc(rotateSide);
	glutMouseFunc(mouse);
	glutMainLoop();
}
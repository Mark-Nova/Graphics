//
//  main.cpp
//  Curve
//
//  Created by Saint on 2014/02/26.
//  Copyright (c) 2014 Saint. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <math.h>

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>


#define PI 3.142
#define r1 .5
#define r2 .7

// Viewing angles
float xViewAngle = 0.0;
float yViewAngle = 0.0;
float zViewAngle = 0.0;


float cF = PI / 180.0;

void drawCurve(float startAngle, float stopAngle) {
	// near surface
	glBegin(GL_QUAD_STRIP);
    glColor3f(0, 0, 1);
    for (float theta = startAngle; theta <= stopAngle; theta = theta + 1.0) {
        float thetaRad = theta * cF;
        glNormal3f(0, 0, 1);
        glVertex3f(r1 * cos(thetaRad), r1 * sin(thetaRad), 0.5);
        glNormal3f(0, 0, 1);
        glVertex3f(r2 * cos(thetaRad), r2 * sin(thetaRad), 0.5);
    }
	glEnd();
	// far surface
	glBegin(GL_QUAD_STRIP);
    glColor3f(0, 1, 0);
    for (float theta = startAngle; theta <= stopAngle; theta = theta + 1.0) {
        float thetaRad = theta * cF;
        glNormal3f(0, 0, -1);
        glVertex3f(r1 * cos(thetaRad), r1 * sin(thetaRad), -0.5);
        glNormal3f(0, 0, -1);
        glVertex3f(r2 * cos(thetaRad), r2 * sin(thetaRad), -0.5);
    }
	glEnd();
	// inner surface
	glBegin(GL_QUAD_STRIP);
    glColor3f(1, 0, 0);
    for (float theta = startAngle; theta <= stopAngle; theta = theta + 1.0) {
        float thetaRad = theta * cF;
        glNormal3f(-r1 * cos(thetaRad), -r1 * sin(thetaRad), 0);
        glVertex3f(r1 * cos(thetaRad), r1 * sin(thetaRad), 0.5);
        glNormal3f(-r1 * cos(thetaRad), -r1 * sin(thetaRad), 0);
        glVertex3f(r1 * cos(thetaRad), r1 * sin(thetaRad), -0.5);
    }
	glEnd();
	// outer surface
	glBegin(GL_QUAD_STRIP);
    glColor3f(1, 1, 0);
    for (float theta = startAngle; theta <= stopAngle; theta = theta + 1.0) {
        float thetaRad = theta * cF;
        glNormal3f(r2 * cos(thetaRad), r2 * sin(thetaRad), 0);
        glVertex3f(r2 * cos(thetaRad), r2 * sin(thetaRad), 0.5);
        glNormal3f(r2 * cos(thetaRad), r2 * sin(thetaRad), 0);
        glVertex3f(r2 * cos(thetaRad), r2 * sin(thetaRad), -0.5);
    }
	glEnd();
	// At start angle we need to create a polygon
	glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(r2 * cos(startAngle * cF), r2 * sin(startAngle * cF), 0.5);
    glVertex3f(r1 * cos(startAngle * cF), r1 * sin(startAngle * cF), 0.5);
    glVertex3f(r1 * cos(startAngle * cF), r1 * sin(startAngle * cF), -0.5);
    glVertex3f(r2 * cos(startAngle * cF), r2 * sin(startAngle * cF), -0.5);
	glEnd();
	// At stopAngle we need to create a polygon
	glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glNormal3f(r1 * cos(stopAngle * cF), r1 * sin(stopAngle * cF), 0);
    glVertex3f(r1 * cos(stopAngle * cF), r1 * sin(stopAngle * cF), 0.5);
    glNormal3f(r2 * cos(stopAngle * cF), r2 * sin(stopAngle * cF), 0);
    glVertex3f(r2 * cos(stopAngle * cF), r2 * sin(stopAngle * cF), 0.5);
    glNormal3f(r2 * cos(stopAngle * cF), r2 * sin(stopAngle * cF), 0);
    glVertex3f(r2 * cos(stopAngle * cF), r2 * sin(stopAngle * cF), -0.5);
    glNormal3f(r1 * cos(stopAngle * cF), r1 * sin(stopAngle * cF), 0);
    glVertex3f(r1 * cos(stopAngle * cF), r1 * sin(stopAngle * cF), -0.5);
	glEnd();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glRotatef(xViewAngle, 1, 0, 0);
	glRotatef(yViewAngle, 0, 1, 0);
	glRotatef(zViewAngle, 0, 0, 1);
    
    glScalef(0.5, 0.5, 1);
    
    glPushMatrix();
        glTranslatef(0, 0.5, 0);
        drawCurve(0, 270);
    
    glPopMatrix();
    
    
    glPushMatrix();
        glTranslatef(0, -0.7, 0);
    glRotatef(180, 0, 0, 1);
        drawCurve(0, 270);
    
    glPopMatrix();
    
    
	
    
    
    
	glFlush();
}

void keyboard(unsigned char key, int x, int y) {
	if (key == 'x')
		xViewAngle += 1.0;
	else if (key == 'X')
		xViewAngle -= 1.0;
	else if (key == 'y')
		yViewAngle += 1.0;
	else if (key == 'Y')
		yViewAngle -= 1.0;
	else if (key == 'z')
		zViewAngle += 1.0;
	else if (key == 'Z')
		zViewAngle -= 1.0;
	else if (key == 'r' || key == 'R') {
		xViewAngle = 0.0;
		yViewAngle = 0.0;
		zViewAngle = 0.0;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 100);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_DEPTH | GLUT_RGBA);
	glutCreateWindow("Basic 3D Curve: A C");
	glEnable(GL_DEPTH_TEST);
    
	glutDisplayFunc( display );
	glutKeyboardFunc( keyboard );
    
	glutMainLoop();
    
	return 0;
}
















































































































































































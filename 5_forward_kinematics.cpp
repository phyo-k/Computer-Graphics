#include <GL/glut.h>
#include <GL/GL.h>
#include <GL/glu.h>
#include <math.h>
#include <stdio.h>
#include <math.h>
#define INIT_WIN_X 600
#define INIT_WIN_Y 600

GLfloat theta1, theta2;
GLfloat x, _x, y, _y;

void Body() { //바닥부분
	glBegin(GL_POLYGON);
	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, -1.0, 0.0);
	glVertex3f(-2.0, -1.0, 0.0);
	glVertex3f(-2.0, 0.0, 0.0);
	glEnd();
}

void kine() { //연골
	float angle1 = 3.141592 / 180;
	float radius = 0.3;
	glBegin(GL_POLYGON);
	glColor3f(0.3f, 0.3f, 0.3f);
	for (int i = 0; i < 360; i++) {
		float angle = i * angle1;
		glVertex2f((cos(angle) * radius), (sin(angle) * radius));
	}
	glEnd();
	glFlush();
}

void DrawArm() { //전체 팔 그리기
	x = 1.5 * cos(theta1);
	y = 1.5 * sin(theta1);
	_x = 2.0 * cos(theta1) + 1.0 * cos(theta1 + theta2);
	_y = 2.0 * sin(theta1) + 1.0 * sin(theta1 + theta2);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Body();

	glPushMatrix();
	glLineWidth(100.0);
	glColor3f(0.7f, 0.7f, 0.7f);
	glBegin(GL_LINES);
	glVertex2f(0.0, 0.0);
	glVertex2f(x, y);
	glEnd();

	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	kine();
	glPopMatrix();

	glPushMatrix();
	glLineWidth(100.0);
	glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_LINES);
	glVertex2f(x, y);
	glVertex2f(_x, _y);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(x, y, 0.0);
	kine();
	glPopMatrix();

	glPopMatrix();
}

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	DrawArm();
	glutSwapBuffers();
}

void MyKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'q':
		theta1 += 0.1;
		glutPostRedisplay();
		break;
	case 'a':
		theta1 -= 0.1;
		glutPostRedisplay();
		break;
	case 'w':
		theta2 += 0.1;
		glutPostRedisplay();
		break;
	case 's':
		theta2 -= 0.1;
		glutPostRedisplay();
		break;
	}
}

void MyTimer(int Value) {
	if (theta2 <= 0.0)
		theta2 = 0.0; //팔목이 뒤로 굽혀지지 않게

	glutPostRedisplay();
	glutTimerFunc(10, MyTimer, 1);
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(INIT_WIN_X, INIT_WIN_Y);
	glutInitWindowPosition(100, 0);
	glutCreateWindow("robot_arm");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5.0, 5.0, -5.0, 5.0, 1.0, -1.0);
	glutDisplayFunc(MyDisplay);
	glutKeyboardFunc(MyKeyboard);
	glutTimerFunc(10, MyTimer, 1);
	glutMainLoop();
	return 0;
}
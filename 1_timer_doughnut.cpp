#include <iostream>
#include <gl/glut.h>
#define INIT_WIN_X 400
#define INIT_WIN_Y 400

GLfloat inner_radius = 0.2f;
GLfloat outer_radius = 0.5f;
GLfloat volume = 0.2;
GLfloat dx = 0.02;
GLint sides = 12;
GLint rings = 24;

void Draw() {

	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0, 0.0, 0.0);

	glutWireTorus(inner_radius, outer_radius, sides, rings);
	glFlush();
	glutSwapBuffers();
}

void MyTimer(int Value) // 타이머 콜백 함수
{
	outer_radius += dx; // 모양이 커진다.
	if (outer_radius + volume > 1 || outer_radius - volume < -1) {
		dx *= -1; //반대방향으로 변하게 한다.
	}
	glutPostRedisplay();
	glutTimerFunc(40, MyTimer, 1);
}

void MyReshape(int NewWidth, int NewHeight)
{
	glViewport(0, 0, NewWidth, NewHeight);
	GLfloat WidthFactor = (GLfloat)NewWidth / (GLfloat)INIT_WIN_X;
	GLfloat HeightFactor = (GLfloat)NewHeight / (GLfloat)INIT_WIN_Y;
	glLoadIdentity();

	glOrtho(-1.0 * WidthFactor, 1.0 * WidthFactor, -1.0 * HeightFactor, 1.0 * HeightFactor, -1.0, -1.0);
	glRotated(70, .3, .3, .3);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(INIT_WIN_X, INIT_WIN_Y);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("OpenGL TEST");

	glClearColor(1.0, 1.0, 1.0, 1.0);

	glutDisplayFunc(Draw);
	glutReshapeFunc(MyReshape);
	glutTimerFunc(40, MyTimer, 1);
	glutMainLoop();

	return 0;
}
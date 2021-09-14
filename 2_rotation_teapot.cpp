#include <iostream>
#include <gl/glut.h>
#include <math.h>
#define INIT_WIN_X 400
#define INIT_WIN_Y 400
GLfloat mouse_dx, mouse_dy, rotation_x, rotation_y;

void InitLight() {
	GLfloat mat_diffuse[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_ambient[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat mat_shininess[] = { 15.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat light_position[] = { -3, 6, 3.0, 0.0 };
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW); //모델의 matrix 조작
	glLoadIdentity(); //전역 좌표계 초기화
	gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0); //시점 변환 함수

	glRotatef((GLfloat)mouse_dy, 1.0, 0.0, 0.0);
	glRotatef((GLfloat)mouse_dx, 0.0, 1.0, 0.0);
	mouse_dx += atan2f(rotation_y, rotation_x) * 180 / 3.141592;
	mouse_dy += atan2f(rotation_x, rotation_y) * 180 / 3.141592;
	glutSolidTeapot(0.5);

	glFlush();
}
void MyReshape(int width, int height)
{
	glViewport(0, 0, (GLsizei) width, (GLsizei) height);
	glMatrixMode(GL_MODELVIEW);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

void MyMouseMove(GLint X, GLint Y) {
	mouse_dx = X;
	mouse_dy = Y;
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(INIT_WIN_X, INIT_WIN_Y);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("차 주전자");
	
	glClearColor(0.4, 0.4, 0.4, 0.0);
	InitLight();
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutMotionFunc(MyMouseMove);
	
	glutMainLoop();
	return 0;
}
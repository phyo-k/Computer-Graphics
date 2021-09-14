// ConsoleApplication1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

//#include <iostream>

//int main()
//{
  //  std::cout << "Hello World!\n";
//}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.

//https://m.blog.naver.com/PostView.nhn?blogId=hermet&logNo=51760873&proxyReferer=https:%2F%2Fwww.google.com%2F
//바닥그리기 https://m.blog.naver.com/PostView.nhn?blogId=dkskwjdu54&logNo=130011113494&proxyReferer=https:%2F%2Fwww.google.com%2F
//http://blog.daum.net/pg365/147
#include <iostream>
#include <gl/glut.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>
#define INIT_WIN_X 800
#define INIT_WIN_Y 800
GLfloat tx = 0.1, tz = 0.1;
GLfloat mx = 3.5, my = 2.0, mz = 3.5;

void DrawFloor() {
	GLfloat x, y,z;
	GLint k=30;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	for (int i = 0; i < k; i++) { 
		for (int j = 0; j < k; j++) {
			if ((i+j) % 2 == 0) {
				x = i * 0.1;
				y = j * 0.1;
				z = k * 0.1;
				glColor3f(1.0, 1.0, 1.0); //흰색
				glBegin(GL_QUADS);
				glVertex3f((x - z / 2) + 0.0, 0.0, (y - z / 2) + 0.0);
				glVertex3f((x - z / 2) + 0.1, 0.0, (y - z / 2) + 0.0);
				glVertex3f((x - z / 2) + 0.1, 0.0, (y - z / 2) + 0.1);
				glVertex3f((x - z / 2) + 0.0, 0.0, (y - z / 2) + 0.1);
				glEnd();
				
			}
			else {
				x=i * 0.1;
				y=j * 0.1;
				z = k * 0.1;
				glColor3f(0.0, 0.0, 0.0); //검정색
				glBegin(GL_QUADS);
				glVertex3f((x - z / 2) + 0.0, 0.0, (y - z / 2) + 0.0);
				glVertex3f((x - z / 2) + 0.1, 0.0, (y - z / 2) + 0.0);
				glVertex3f((x - z / 2) + 0.1, 0.0, (y - z / 2) + 0.1);
				glVertex3f((x - z / 2) + 0.0, 0.0, (y - z / 2) + 0.1);
				glEnd();
				
			}
		}
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.0, 0.0, -1.0);
	glColor3f(0.9, 0.9, 0.0); //노란색큐브
	glutSolidCube(0.1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, -1.0);
	glColor3f(0.0, 0.5, 0.5); //녹색큐브
	glutSolidCube(0.1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.3, 0.0, -1.0);
	glColor3f(0.7, 0.0, 0.7); //자주색큐브
	glutSolidCube(0.1);
	glPopMatrix();

	glFlush();
}

void MyDisplay() {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluPerspective(5, 1.0, 2.0, 50.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	gluLookAt(mx+tx, my, mz+tz, tx, 0.3, tz, 0.0, 10.0, 0.0);
	DrawFloor();
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	
	glFlush();
}

void MyKeyboard(unsigned char KeyPressed, int x, int y) {
	GLfloat walking = 0.03;
	GLfloat speed = 0.3;

	switch (KeyPressed) {
	case 'w': //카메라 전
		tx -= (walking * speed);
		tz -= (walking * speed);
		break;
	case's': //후
		tx += (walking * speed);
		tz += (walking * speed);
		break;
	case 'a': //좌
		tx -= (walking * speed);
		tz += (walking * speed);
		break;
	case 'd': //우
		tx += (walking * speed);
		tz -= (walking * speed);
		break;
	case 27: //esc 종료
		exit(0);
		break;
	}
	glutPostRedisplay();
}

bool mouse = true;
GLfloat yaw = -90.0f;
GLfloat pitch = 0.0f;
GLfloat lastX = 400.0;
GLfloat lastY = 300.0;

void MyMouseMove(GLint xpos, GLint ypos){
	if (mouse){
		lastX = xpos;
		lastY = ypos;
		mouse = false;
	}

	GLfloat xoffset = xpos - lastX; 
	GLfloat yoffset = lastY - ypos; // 움직인 마우스 값 
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.001f; //마우스 움직임 적게
	xoffset *= sensitivity;
	yoffset *= sensitivity;
	
	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch <= -89.0f)
		pitch = -89.0f;
	

	mx = cos(yaw*3.141592) * cos(pitch*3.141592);
	mz = sin(yaw* 3.141592) * cos(pitch * 3.141592);
	glutPostRedisplay();
}

void MyTimer(int Value) // 타이머 콜백 함수
{
	my += 0.03; // 걷기
	if (my > 2.04) {
		my = 2.0;
	}
	glutTimerFunc(40, MyTimer, 1);
}


void MyReshape(int NewWidth, int NewHeight)
{
	glViewport(0, 0, NewWidth, NewHeight);
	GLfloat WidthFactor = (GLfloat)NewWidth / (GLfloat)INIT_WIN_X;
	GLfloat HeightFactor = (GLfloat)NewHeight / (GLfloat)INIT_WIN_Y;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-1.0 * WidthFactor, 1.0 * WidthFactor, -1.0 * HeightFactor, 1.0 * HeightFactor, -1.0, 1.0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(INIT_WIN_X, INIT_WIN_Y);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Walking_Through");
	glClearColor(0.8, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glutDisplayFunc(MyDisplay);
	glutKeyboardFunc(MyKeyboard);
	glutMotionFunc(MyMouseMove);
	glutTimerFunc(40, MyTimer, 1);
	glutReshapeFunc(MyReshape);
	glutMainLoop();
	return 0;
}

/*
bool mouse = true;
GLfloat yaw = -180.0f;//원랜 -180.0f
GLfloat pitch = 0.0f;
GLfloat lastX; //= 800.0f / 2.0;// 100.0f;
GLfloat lastY; //= 600.0 / 2.0;// 100.0f;

void MyMouseMove(GLint xpos, GLint ypos){
	if (mouse)
	{
		lastX = xpos;
		lastY = ypos;
		mouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	/float sensitivity = 0.1f;
	//tx *= sensitivity;
	//tz *= sensitivity;

	xoffset += tx;
	yoffset += tz;

	yaw += (tx/15);
	pitch += (tz/15);

	if (pitch > 90.0f)
		pitch = 89.0f;
	if (pitch <= -90.0f)
		pitch = -89.0f;

	mx = cos(yaw*3.141592) * cos(pitch*3.141592);
	//my = sin(pitch*3.141592);
	mz = sin(yaw* 3.141592) * cos(pitch * 3.141592);
	glutPostRedisplay();
}
*/
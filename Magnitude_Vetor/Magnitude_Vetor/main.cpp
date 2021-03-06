#include <GL/freeglut.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

class Vetor {
public:
	Vetor(GLdouble x, GLdouble y)  { 
		_x = x; 
		_y = y;
	};

	void SetX(GLdouble x) {
		_x = x; 
	};

	void SetY(GLdouble y) {
		_y = y;
	};

	GLdouble GetX() const { 
		return(_x);
	};

	GLdouble GetY() const {
		return(_y);
	};

	void add(Vetor _v) {
		_x += _v.GetX();
		_y += _v.GetY();
	};

	void sub(Vetor _v) {
		_x -= _v.GetX();
		_y -= _v.GetY();
	};

	GLdouble mag() {
		return(sqrt((_x*_x) + (_y*_y)));
	};

private:
	GLdouble _x, _y;
};

GLdouble margemEsquerda = -300, margemDireita = 300;
GLdouble margemInferior = 300, margemSuperior = -300;
GLdouble larguraJanela = 600, alturaJanela = 600;

double _m;
Vetor _mouse(0, 0);

void mouse(int x, int y) {
	_mouse = Vetor(x, y);
	Vetor canto(300, 267);
	_mouse.sub(canto);
	_m = _mouse.mag();

//	std::cout << _m << std::endl;
	printf("Magnitude mouse %0.1f \n", _m);
	glutPostRedisplay();
}

void PontoInical(){
	glLineWidth(2.5);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2d(0.0f, 0.0f);
	glVertex2d(_mouse.GetX(), _mouse.GetY());
	glEnd();
}

void barraProgresso(){
	GLdouble posicao;
	if (_mouse.GetX() > 0.0){
		posicao = _mouse.GetX();
		glColor3f(0.0f, 0.0f, 1.0f);
		glBegin(GL_QUADS);
		glVertex2d(-300.0f, -300.0f);
		glVertex2d(-300.0f, 300.0f);
		glVertex2d(posicao, 300.0f);
		glVertex2d(posicao, -300.0f);
	}
	if (_mouse.GetX() < 0.0){
		posicao = (_mouse.GetX()*-1);
		glColor3f(0.0f, 0.0f, 1.0f);
		glBegin(GL_QUADS);
		glVertex2d(-300.0f, -300.0f);
		glVertex2d(-300.0f, 300.0f);
		glVertex2d(posicao, 300.0f);
		glVertex2d(posicao, -300.0f);
	}
	if (_mouse.GetY() > 0.0){
		posicao = _mouse.GetY();
		glColor3f(0.0f, 0.0f, 1.0f);
		glBegin(GL_QUADS);
		glVertex2d(-300.0f, -300.0f);
		glVertex2d(-300.0f, 300.0f);
		glVertex2d(posicao, 300.0f);
		glVertex2d(posicao, -300.0f);
	}
	if (_mouse.GetY() < 0.0){
		posicao = (_mouse.GetY()*-1);
		glColor3f(0.0f, 0.0f, 1.0f);
		glBegin(GL_QUADS);
		glVertex2d(-300.0f, -300.0f);
		glVertex2d(-300.0f, 300.0f);
		glVertex2d(posicao, 300.0f);
		glVertex2d(posicao, -300.0f);
	}
	glEnd();
}
void desenha() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_VIEWPORT);

	//viewPort mouse
	glViewport(0, 33, larguraJanela, alturaJanela);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(margemEsquerda, margemDireita, margemInferior, margemSuperior);
	PontoInical();

	//viewPort Barra progresso
	glViewport(0, 0, _m, 30);
	barraProgresso();
	
	glutSwapBuffers();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Gc - Magnitude Vetor");
	glutDisplayFunc(desenha);
	glutPassiveMotionFunc(mouse);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glutMainLoop();
	return(0);
}
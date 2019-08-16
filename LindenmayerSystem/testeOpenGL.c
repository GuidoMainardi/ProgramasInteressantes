#include <GL/glut.h>

void DesenhaNaTela(void){
    glClear(GL_COLOR_BUFFER_BIT);

    glutSwapBuffers();
}

void inicializa(void){
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(320,240);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Primeiro Programa em OpenGL");
    glutDisplayFunc(DesenhaNaTela);
    inicializa();
    glutMainLoop();
}
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define PI (3.141592653589793)

double grausToRad(double graus){
    return graus/180 * PI;
}
char* find(char* s, char l){
    while(*s != l)
        s++;
    return s;
}
void rotaAntHorario(double* x, double* y, double graus){
    graus = grausToRad(graus);
    double xTemp = *x * cos(graus) - *y * sin(graus);
    double yTemp = *x * sin(graus) + *y * cos(graus);
    *x = xTemp;
    *y = yTemp;

}
void rotaHorario(double* x, double* y, double graus){
    graus = grausToRad(graus);
    double xTemp = *x * cos(graus) + *y * sin(graus);
    double yTemp = *x * -sin(graus) + *y * cos(graus);
    *x = xTemp;
    *y = yTemp;

}
void desenhaLinha(double xInic, double yInic, double xFim, double yFim){
    glColor3f(0.0f, 0.8f, 0.0f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glVertex2f(xInic,yInic);
    glVertex2f(xFim,yFim);
    glEnd();
}
void lind(char* s, double xPF, double yPF, double xVB, double yVB){
    while(1){
        printf("%c", *s);
        switch (*s)
        {
        case '^':
            desenhaLinha(xPF, yPF, xPF+xVB, yPF+yVB);
            xPF += xVB;
            yPF += yVB;
            break;
        case '>':
            rotaHorario(&xVB, &yVB, 30);
            desenhaLinha(xPF, yPF, xPF+xVB, yPF+yVB);
            xPF += xVB;
            yPF += yVB; 
            break;
        case '<':
            rotaAntHorario(&xVB, &yVB, 30);
            desenhaLinha(xPF, yPF, xPF+xVB, yPF+yVB);
            xPF += xVB;
            yPF += yVB;
            break;
        case '[':
            lind((s+1), xPF, yPF, xVB, yVB);
            s = find(s, ']');
            break;
        case ']':
            return;
        case '\0':
            return;
        default:
            return;
        }
        s++;
    }
}
void DesenhaNaTela(){
    glClear(GL_COLOR_BUFFER_BIT);
    lind("^^[<^][>^]^^", 0, 0, 0, 10);
    printf("\n");
    glutSwapBuffers();
}

void inicializa(void){
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100,100,-100,100);
    glMatrixMode(GL_MODELVIEW);

}

int main(int argc, char** argv){

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(580,450);
    glutInitWindowPosition(100,100);
    glutCreateWindow("O Comeco Do Fim");
    glutDisplayFunc(DesenhaNaTela);
    inicializa();
    glutMainLoop();
}
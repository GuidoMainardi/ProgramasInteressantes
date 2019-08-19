#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define PI (3.141592653589793)


double grausToRad(double graus){
    return graus/180 * PI;
}
char* findCol(char* s){
    int rec = 1;
    while(rec != 0){
        if(*s == '[')
            rec ++;
        if(*s == ']')
            rec --;
        s++;
    }
    return s - 1;
}
void rotaHorario(double* x, double* y, double graus){
    graus = grausToRad(graus);
    double xTemp = *x * cos(graus) + *y * sin(graus);
    double yTemp = *x * -sin(graus) + *y * cos(graus);
    *x = xTemp;
    *y = yTemp;

}
void desenhaLinha(double xInic, double yInic, double xFim, double yFim, double color){
    glColor3f(0.0f, 0.8f, color);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glVertex2f(xInic,yInic);
    glVertex2f(xFim,yFim);
    glEnd();
}
void lind(char* s, double xPF, double yPF, double xVB, double yVB, double color){
    while(1){
        printf("%c", *s);
        switch (*s)
        {
            // desenha a linha pra onde a "tartaruga ta apontando"
        case '^':
            desenhaLinha(xPF, yPF, xPF+xVB, yPF+yVB, color);
            xPF += xVB;
            yPF += yVB;
            break;
        // vira a tartaruga 10º no sentido horario
        case '>':
            rotaHorario(&xVB, &yVB, 10);
            break;
        //vira a tartaruga 10º no sentido antHorario
        case '<':
            rotaHorario(&xVB, &yVB, -10);
            break;
        //começa uma recurção
        case '[':
            lind((s+1), xPF, yPF, xVB, yVB, color);
            s = findCol(s + 1);
            break;
        // encerra uma recurção
        case ']':
            return;
        // deixa o risco mais azul
        case '+':
            color += 0.3;
            break;
        case 'p':
            xVB = xVB * 1.1;
            yVB = yVB * 1.1;
            break;
        case 'm': 
            xVB = xVB * 0.9;
            yVB = yVB * 0.9;
            break;
        // fim da string termina o programa
        case '\0':
            return;
        // alguns casos legais para ignorar
        case ' ':
            break;
        case ':':
            break;
        case ';':
            break;
        default:
            //começando a pensar como fazer métodos
            /*
            if(*s >= 65 && *s <= 90){
                if(!(*(s+1) == ':')){
                    findFunc(*s);
                }
            }
            */
            return;
        }
        s++;
    }
}
void DesenhaNaTela(){
    glClear(GL_COLOR_BUFFER_BIT);
    lind("", 0, 0, 0, 10, 0);
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
/*
    Sistema de Lindenmayer feito por Guido Mainardi

    comandos:
    '^': faz uma linha na direção que esta "olhando"
    '>0': rota no snetido horario o valor que vem a seguir, nesse caso 000 graus, o numero precisa  ser inteiro
    '<0': rota no sentido anti-horario o valor que vem coaldo nele, nesse caso 0 graus, o numero precisa ser inteiro
    '+': torna o risco um pouco mais azul, um valor fixo
    's1.0': muda o tamnho do risco, nesse caso (1.0) o risco fica do mesmo tamanho
    '[': começa uma recurção
    ']': encerra a função
    "X:": declara uma função, deve ser usada uma letra maiuscula (tente eviar usar 'E') seguida de ':' para declarar a função
    "X" : chama a função que foi declarada 
*/
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PI (3.141592653589793)

//programa exemplo
char* programa = "B; B:^[<30s0.9+B][>30s0.9+B]s0.9+B";


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
    return s - 1 ;
}
char* findFunc(char f){
    char* s = programa;
    while(*s){
        if(*s == f)
            if(*(s+1) == ':')
                return s + 1;
        s++;
    }
    return NULL;
}
char* findNext(char* s){
    while(*s >= '0' && *s <= '9' || *s == '.'){
        s++;
    }
    return (s-1);
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
void lind(char* s, double xPF, double yPF, double xVB, double yVB, double color, int rec){
    if(rec == 0){
        return;
    }
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
            s++;
            rotaHorario(&xVB, &yVB, atoi(s));
            s = findNext(s);
            break;
        //vira a tartaruga 10º no sentido antHorario
        case '<':
            s++;
            rotaHorario(&xVB, &yVB, -1 * atoi(s));
            s = findNext(s);
            break;
        //começa uma recurção
        case '[':
            lind((s+1), xPF, yPF, xVB, yVB, color, rec);
            s = findCol(s + 1);
            break;
        // encerra uma recurção
        case ']':
            return;
        // deixa o risco mais azul
        case '+':
            color += 0.1;
            break;
        //muda o tamanho do risco
        case 's':
            s++;
            xVB = xVB * atof(s);
            yVB = yVB * atof(s);
            s = findNext(s);
            break;
        // fim da string termina o programa
        case '\0':
            return;
        // alguns casos legais para ignorar
        case ' ':
            break;
        case ';':
            break;
        case ':':
            break;
        default:
            //confere se é uma letra maiuscula, se for, procura por ela e chama a função
            if(*s >= 65 && *s <= 90){
                if(*(s+1) != ':'){
                    char* aux = findFunc(*s);
                    lind(aux, xPF, yPF, xVB, yVB, color, rec - 1);
                    break;
                }
            }
            return;
        }
        s++;
    }
}
void DesenhaNaTela(){
    glClear(GL_COLOR_BUFFER_BIT);
    // chamada da função principal, os dois primeiros valores são aonde vai começar o desenho, a grade vai de 100 a -100 no x e no y
    // os dois proximos valores são os pontos x y do vetor que vai ser escrito (nesse caso é um vetor reto pra cima de tamanho 20)
    // o numero seguinte é o quanto de azul o risco deve ter
    // por fim o ultimo numero é quantas recurções devem acontecer
    lind(programa, 0, -50, 0, 20, 0, 9);
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
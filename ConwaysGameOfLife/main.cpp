/*
 *  Conway's Game Of Life
 *
 *
 *  Vinicius Rodrigues
 *  08.09.2019
 *
 *
 *
 */

#include <GL/glut.h>
#include <iostream>
#include <ctime>
#include <unistd.h>

#define LIFE true
#define DEAD false

const int envWidth = 100, envHeight = 100;
bool enviroment[envWidth][envHeight];
bool enviromentAux[envWidth][envHeight];
int iadd[8] = {0, 1, 1, 1, 0, -1, -1, -1};  // Indices for neighbors cells
int jadd[8] = {1, 1, 0, -1, -1, -1, 0, 1};

void initGraphics()
{
    srand(std::clock());
    for(int i = 0; i < envWidth; i++)
    {
        for(int j = 0; j < envHeight; j++)
        {
            enviroment[i][j] = rand() % 3;
            enviromentAux[i][j] = DEAD;
        }
    }
}


void UpdateEnviroment()
{
    for(int i = 1; i < envWidth-1; i++)
    {
        for(int j = 1; j < envHeight-1; j++)
        {
            int neighbors = 0;
            for(int k = 0; k < 8; k++)
                neighbors += enviroment[i + iadd[k]][j + jadd[k]];

            if(neighbors == 3)
                enviromentAux[i][j] = LIFE;
            else if(neighbors == 2)
                enviromentAux[i][j] = enviroment[i][j];
            else
                enviromentAux[i][j] = DEAD;
        }
    }

    for(int i = 0; i < envWidth; i++)
    {
        for(int j = 0; j < envHeight; j++)
        {
            enviroment[i][j] = enviromentAux[i][j];
        }
    }
    std::cout << "swap";
    usleep(500000);
}

void DrawScene()
{
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(5.0f);
    glEnable(GL_POINT_SMOOTH);
    glBegin(GL_POINTS);

        glColor3f(0.0f, 0.0f, 0.0f);

        float x, y;
        for(int i = 0; i < envWidth; i++)
        {
            for(int j = 0; j < envHeight; j++)
            {
                if(enviroment[i][j])
                {
                    x = 2.0f * float(i) / envWidth - 1.0f;
                    y = 2.0f * float(j) / envHeight - 1.0f;

                    glVertex2f(x, y);
                }
            }
        }
    glEnd();

    glutSwapBuffers();
    glutPostRedisplay();
}

void Update()
{
    UpdateEnviroment();
    DrawScene();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE bitor GLUT_RGB);
    glutInitWindowSize(600, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Conway's Game of Life");

    glutDisplayFunc(DrawScene);
    initGraphics();
    glutIdleFunc(Update);

    glutMainLoop();
}

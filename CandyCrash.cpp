// Bakalis Dimitrios A.M. 3033 year: 2019-2020

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <time.h>
#include <iostream>
#include <fstream>

#include <cstring>

using namespace std;


#define maxx 16
#define maxy 16
#define dx 32
#define dy 32

bool game_started = false;
bool game_ended = false;
int moves_counter = 30;
int points_counter = 0;

int TILESIZE = 40;

GLuint ROCK ;
GLuint PAPER ;
GLuint SCISSORS ;

GLubyte* ICON_ROCK;
GLubyte* ICON_PAPER;
GLubyte* ICON_SCISSORS;

typedef struct cell
{
    GLfloat x0,y0,x1,y1;
    int color;
}cellt;

cellt board[16][16];
GLfloat color[6][3]={{0,0,1},{1,0,0},{0,1,0},{1,0,1},{1,1,0},{1,1,1}};  // 5 basika xrwmata + to aspro
GLfloat x0=0,y0=0;
GLint i,j,stroke=0,pastx,pasty,nextx,nexty,swapthetwo=0;


void init(){

    int i=0,j=0;
    glClearColor(1.0,1.0,1.0,1.0);
    glColor3f(1.0,0.0,0.0);
    glPointSize(5.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,499.0,0.0,499.0);
    glutPostRedisplay();

    int temp = 0;
    int value = 0;

    for(i=0;i<maxx;i++)
        for(j=0;j<maxy;j++)
        {
            board[i][j].x0=x0+i*dx+1;
            board[i][j].x1=x0+(i+1)*dx-1;
            board[i][j].y0=y0+j*dy+1;
            board[i][j].y1=y0+(j+1)*dy-1;
            value = rand()%5;
            while(value == temp){
                value = rand()%5;
            }
            temp = value;
            board[i][j].color=value;
        }
}


void display(void){

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Bazw to backround se mauro xrwma  
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear Screen And Depth Buffer

    char moves[20];                                // emfanish twn kinhsewn
    sprintf(moves,"Moves: %d", moves_counter);
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f( 265, 480 );
    int j = strlen( moves );
    for( int i = 0; i < j; i++ ) {
        glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, moves[i] );
    }

    char points[20];                               // emfanish tou score
    sprintf(points,"Points: %d", points_counter);
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f( 380, 480 );
    int k = strlen( points );
    for( int i = 0; i < k; i++ ) {
        glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, points[i] );
    }

    if(game_ended == true){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear Screen And Depth Buffer
        char points_2[40];                               // emfanish tou game over kai toy telikou score
        sprintf(points_2,"Game Over Final Score: %d", points_counter);
        glColor3f(1.0, 1.0, 1.0);
        glRasterPos2f( 110, 480 );
        int q = strlen( points_2 );
        for( int i = 0; i < q; i++ ) {
            glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, points_2[i] );
        }
    }
    
    if(game_started == false){  // arxikopoihsh plegmatos me aspro xrwma
        for(i=0;i<maxx-1;i++){
            for(j=0;j<maxy-1;j++){

                glColor3f(0.95,0.96,0.80); // anoixto bez

                glBegin(GL_POLYGON);
                    glVertex2f(board[i][j].x0,board[i][j].y0);
                    glVertex2f(board[i][j].x0,board[i][j].y1);
                    glVertex2f(board[i][j].x1,board[i][j].y1);
                    glVertex2f(board[i][j].x1,board[i][j].y0);
                glEnd();
                glColor3f(0.0,0.0,0.0);
                glBegin(GL_LINE_LOOP);
                    glVertex2f(board[i][j].x0,board[i][j].y0);
                    glVertex2f(board[i][j].x0,board[i][j].y1);
                    glVertex2f(board[i][j].x1,board[i][j].y1);
                    glVertex2f(board[i][j].x1,board[i][j].y0);
                glEnd();
            }
        }    
    }

    if(game_started == true){
        for(i=0;i<maxx-1;i++){
            for(j=0;j<maxy-1;j++){
               
                glColor3fv(color[board[i][j].color]);

                glBegin(GL_POLYGON);
                    glVertex2f(board[i][j].x0,board[i][j].y0);
                    glVertex2f(board[i][j].x0,board[i][j].y1);
                    glVertex2f(board[i][j].x1,board[i][j].y1);
                    glVertex2f(board[i][j].x1,board[i][j].y0);
                glEnd();
                glColor3f(0.0,0.0,0.0);
                glBegin(GL_LINE_LOOP);
                    glVertex2f(board[i][j].x0,board[i][j].y0);
                    glVertex2f(board[i][j].x0,board[i][j].y1);
                    glVertex2f(board[i][j].x1,board[i][j].y1);
                    glVertex2f(board[i][j].x1,board[i][j].y0);
                glEnd();
            }
        }
    }

    glFlush();
    glutSwapBuffers();
}

void disOne(int x1, int y1, int x2, int y2, bool horizontal, int op_color){

    if(horizontal == false){   // ka8eth triada
        int i = y1+2;
        int j = y2-1;

        if (board[x1][y1+1].color != op_color){
            points_counter+=2;
            board[x1][y1+1].color = 5; 
        }else points_counter--;
        if (board[x2][y2-1].color != op_color){
            points_counter+=2;
            board[x2][y2-1].color = 5;
        }else points_counter--;

        for(i>j;i--;){
            if(i<j){
                break;
            }
            if(board[x1-1][i].color != op_color ){
                board[x1-1][i].color = 5;
                points_counter+=2;
                display();
            }else points_counter--;
            if(board[x1+1][i].color != op_color ){
                board[x1+1][i].color = 5;
                points_counter+=2;
                display();
            }else points_counter--;
        }
    }else{  // orizontia triada

        int i = x1-2;
        int j = x2+1;
    
        if (board[x1-1][y1].color != op_color){
            points_counter+=2;
            board[x1-1][y1].color = 5; 
        }else points_counter--;
        if (board[x2+1][y2].color != op_color){
            board[x2+1][y2].color = 5; 
            points_counter+=2;
        }else points_counter--;

        for(i<j;i++;){
            if(i>j){
                break;
            }
            if(board[i][y1-1].color != op_color ){
                board[i][y1-1].color = 5;
                points_counter+=2;
                display();
            }else points_counter--;
            if(board[i][y1+1].color != op_color ){
                board[i][y1+1].color = 5;
                points_counter+=2;
                display();
            }else points_counter--; 
        }
    }
    
}

void disTwo(int x1, int y1, int x2, int y2, bool horizontal, int des_color){

    if(horizontal == false){   // ka8eth triada

        int i = y1+3;
        int j = y2-2;

        for(i>j; i--;){
            if(i<j){
                break;
            }
            if(board[x1-2][i].color == des_color){
                board[x1-2][i].color = 5;
                points_counter+=3;
                display();
            }
            if(board[x1+2][i].color == des_color){
                board[x1+2][i].color = 5;
                points_counter+=3;
                display();
            }
        }

        int q = x1-3;
        int z = x1+2;

        for(q<z; q++;){
            
            if(q>z){
                break;
            }
            if(board[q][y1+2].color == des_color){
                board[q][y1+2].color = 5;
                points_counter+=3;
                display();
            }
            if(board[q][y2-2].color == des_color){
                board[q][y2-2].color = 5;
                points_counter+=3;
                display();
            }
        }

    }else{  // orizontia triada

        int i = y1+3;
        int j = y1-2;

        for(i>j; i--;){
            if(i<j){
                break;
            }
            if(board[x1-2][i].color == des_color){
                board[x1-2][i].color = 5;
                points_counter+=3;
                display();
            }
            if(board[x2+2][i].color == des_color){
                board[x2+2][i].color = 5;
                points_counter+=3;
                display();
            }
        }

        int q = x1-3;
        int z = x2+2;

        for(q<z; q++;){
            if(q>z){
                break;
            }
            if(board[q][y1+2].color == des_color){
                board[q][y1+2].color = 5;
                points_counter+=3;
                display();
            }
            if(board[q][y1-2].color == des_color){
                board[q][y1-2].color = 5;
                points_counter+=3;
                display();
            }
        }
    }
}

void disThree(int x1, int y1, int x2, int y2, bool horizontal, int des_color){

    if(horizontal == false){   // ka8eth triada

        int i = y1+4;
        int j = y2-3;

        for(i>j; i--;){
            if(i<j){
                break;
            }
            if(board[x1-3][i].color == des_color){
                board[x1-3][i].color = 5;
                points_counter+=3;
                display();
            }
            if(board[x1+3][i].color == des_color){
                board[x1+3][i].color = 5;
                points_counter+=3;
                display();
            }
        }

        int q = x1-4;
        int z = x1+3;

        for(q<z; q++;){
            if(q>z){
                break;
            }
            if(board[q][y1+3].color == des_color){
                board[q][y1+3].color = 5;
                points_counter+=3;
                display();
            }
            if(board[q][y2-3].color == des_color){
                board[q][y2-3].color = 5;
                points_counter+=3;
                display();
            }
        }

    }else{  // orizontia triada

        int i = y1+4;
        int j = y1-3;

        for(i>j; i--;){
            if(i<j){
                break;
            }
            if(board[x1-3][i].color == des_color){
                board[x1-3][i].color = 5;
                points_counter+=3;
                display();
            }
            if(board[x2+3][i].color == des_color){
                board[x2+3][i].color = 5;
                points_counter+=3;
                display();
            }
        }

        int q = x1-4;
        int z = x2+3;

        for(q<z; q++;){
            if(q>z){
                break;
            }
            if(board[q][y1+3].color == des_color){
                board[q][y1+3].color = 5;
                points_counter+=3;
                display();
            }
            if(board[q][y1-3].color == des_color){
                board[q][y1-3].color = 5;
                points_counter+=3;
                display();
            }
        }
    }
}

void neighbor(int x, int y, int op_color){

    int damage_color;

    if(op_color == 2){         // (green = psalidi = 2)  (kitrino = xarti = 4)  (magenda = braxos = 3)  //
        damage_color = 4;       
    }else if(op_color == 4){
        damage_color = 3;         
    }else if(op_color == 3){
        damage_color = 2;
    }

    if(board[x][y+1].color == damage_color){
        board[x][y+1].color = 5;
        points_counter+=2;
        display();
    }
    if(board[x][y-1].color == damage_color){
        board[x][y-1].color = 5;
        points_counter+=2;
        display();
    }
    if(board[x+1][y].color == damage_color){
        board[x+1][y].color = 5;
        points_counter+=2;
        display();
    }
    if(board[x-1][y].color == damage_color){
        board[x-1][y].color = 5;
        points_counter+=2;
        display();
    }

}


/////////////////////////////// KATASTROFH KYBWN OTAN EXW 3 IDIA TUPOU SE GRAMMH H SE STHLH ME KA8E PI8ANO SYNDIASMO ///////////////////////////////

void destruction(int x, int y){

    if(board[x][y].color == 0 ) {  // blue
        if(board[x][y-1].color == 0 and board[x][y-2].color == 0){
            board[x][y].color = 5;
            board[x][y-1].color = 5;
            board[x][y-2].color = 5;
            points_counter+= 10;
            display();
        }else if(board[x][y+1].color == 0 and board[x][y+2].color == 0){
            board[x][y].color = 5;
            board[x][y+1].color = 5;
            board[x][y+2].color = 5;
            points_counter+= 10;
            display();
        }else if(board[x-1][y].color == 0 and board[x-2][y].color == 0){
            board[x][y].color = 5;
            board[x-1][y].color = 5;
            board[x-2][y].color = 5;
            points_counter+= 10;
            display();
        }else if(board[x+1][y].color == 0 and board[x+2][y].color == 0){
            board[x][y].color = 5;
            board[x+1][y].color = 5;
            board[x+2][y].color = 5;
            points_counter+= 10;
            display();
        }else if(board[x][y-1].color == 0 and board[x][y+1].color == 0){
            board[x][y].color = 5;
            board[x][y-1].color = 5;
            board[x][y+1].color = 5;
            points_counter+= 10;
            display();
        }else if(board[x-1][y].color == 0 and board[x+1][y].color == 0){
            board[x][y].color = 5;
            board[x-1][y].color = 5;
            board[x+1][y].color = 5;
            points_counter+= 10;
            display();
        }
    }else if(board[x][y].color == 1 ) {  // red
        if(board[x][y-1].color == 1 and board[x][y-2].color == 1){
            board[x][y].color = 5;
            board[x][y-1].color = 5;
            board[x][y-2].color = 5;
            points_counter+= 10;
            display();
        }else if(board[x][y+1].color == 1 and board[x][y+2].color == 1){
            board[x][y].color = 5;
            board[x][y+1].color = 5;
            board[x][y+2].color = 5;
            points_counter+= 10;
            display();
        }else if(board[x-1][y].color == 1 and board[x-2][y].color == 1){
            board[x][y].color = 5;
            board[x-1][y].color = 5;
            board[x-2][y].color = 5;
            points_counter+= 10;
            display();
        }else if(board[x+1][y].color == 1 and board[x+2][y].color == 1){
            board[x][y].color = 5;
            board[x+1][y].color = 5;
            board[x+2][y].color = 5;
            points_counter+= 10;
            display();
        }else if(board[x][y-1].color == 1 and board[x][y+1].color == 1){
            board[x][y].color = 5;
            board[x][y-1].color = 5;
            board[x][y+1].color = 5;
            points_counter+= 10;
            display();
        }else if(board[x-1][y].color == 1 and board[x+1][y].color == 1){
            board[x][y].color = 5;
            board[x-1][y].color = 5;
            board[x+1][y].color = 5;
            points_counter+= 10;
            display();
        }
    }else if(board[x][y].color == 2){  // 2 = green = psalidi
        if(board[x][y-1].color == 2 and board[x][y-2].color == 2){
            board[x][y].color = 5;
            board[x][y-1].color = 5;
            board[x][y-2].color = 5;
            points_counter+= 10;
            display();
            disOne(x,y,x,y-2,false,3);
            disTwo(x,y,x,y-2,false,4);
            disThree(x,y,x,y-2,false,4);
        }else if(board[x][y+1].color == 2 and board[x][y+2].color == 2){
            board[x][y].color = 5;
            board[x][y+1].color = 5;
            board[x][y+2].color = 5;
            points_counter+= 10;
            display();
            disOne(x,y+2,x,y,false,3);
            disTwo(x,y+2,x,y,false,4);
            disThree(x,y+2,x,y,false,4);
        }else if(board[x-1][y].color == 2 and board[x-2][y].color == 2){
            board[x][y].color = 5;
            board[x-1][y].color = 5;
            board[x-2][y].color = 5;
            points_counter+= 10;
            display();
            disOne(x-2,y,x,y,true,3);
            disTwo(x-2,y,x,y,true,4);
            disThree(x-2,y,x,y,true,4);
        }else if(board[x+1][y].color == 2 and board[x+2][y].color == 2){
            board[x][y].color = 5;
            board[x+1][y].color = 5;
            board[x+2][y].color = 5;
            points_counter+= 10;
            display();
            disOne(x,y,x+2,y,true,3);
            disTwo(x,y,x+2,y,true,4);
            disThree(x,y,x+2,y,true,4);
        }else if(board[x][y-1].color == 2 and board[x][y+1].color == 2){
            board[x][y].color = 5;
            board[x][y-1].color = 5;
            board[x][y+1].color = 5;
            points_counter+= 10;
            display();
            disOne(x,y+1,x,y-1,false,3);
            disTwo(x,y+1,x,y-1,false,4);
            disThree(x,y+1,x,y-1,false,4);
        }else if(board[x-1][y].color == 2 and board[x+1][y].color == 2){
            board[x][y].color = 5;
            board[x-1][y].color = 5;
            board[x+1][y].color = 5;
            points_counter+= 10;
            display();
            disOne(x-1,y,x+1,y,true,3);
            disTwo(x-1,y,x+1,y,true,4);
            disThree(x-1,y,x+1,y,true,4);
        }
    }else if(board[x][y].color == 4){  // 4 = kitrino = xarti
        if(board[x][y-1].color == 4 and board[x][y-2].color == 4){
            board[x][y].color = 5;
            board[x][y-1].color = 5;
            board[x][y-2].color = 5;
            points_counter+= 10;
            display();
            disOne(x,y,x,y-2,false,2);
            disTwo(x,y,x,y-2,false,3);
            disThree(x,y,x,y-2,false,3);
        }else if(board[x][y+1].color == 4 and board[x][y+2].color == 4){
            board[x][y].color = 5;
            board[x][y+1].color = 5;
            board[x][y+2].color = 5;
            points_counter+= 10;
            display();
            disOne(x,y+2,x,y,false,2);
            disTwo(x,y+2,x,y,false,3);
            disThree(x,y+2,x,y,false,3);
        }else if(board[x-1][y].color == 4 and board[x-2][y].color == 4){
            board[x][y].color = 5;
            board[x-1][y].color = 5;
            board[x-2][y].color = 5;
            points_counter+= 10;
            display();
            disOne(x-2,y,x,y,true,2);
            disTwo(x-2,y,x,y,true,3);
            disThree(x-2,y,x,y,true,3);
        }else if(board[x+1][y].color == 4 and board[x+2][y].color == 4){
            board[x][y].color = 5;
            board[x+1][y].color = 5;
            board[x+2][y].color = 5;
            points_counter+= 10;
            display();
            disOne(x,y,x+2,y,true,2);
            disTwo(x,y,x+2,y,true,3);
            disThree(x,y,x+2,y,true,3);
        }else if(board[x][y-1].color == 4 and board[x][y+1].color == 4){
            board[x][y].color = 5;
            board[x][y-1].color = 5;
            board[x][y+1].color = 5;
            points_counter+= 10;
            display();
            disOne(x,y+1,x,y-1,false,2);
            disTwo(x,y+1,x,y-1,false,3);
            disThree(x,y+1,x,y-1,false,3);
        }else if(board[x-1][y].color == 4 and board[x+1][y].color == 4){
            board[x][y].color = 5;
            board[x-1][y].color = 5;
            board[x+1][y].color = 5;
            points_counter+= 10;
            display();
            disOne(x-1,y,x+1,y,true,2);
            disTwo(x-1,y,x+1,y,true,3);
            disThree(x-1,y,x+1,y,true,3);
        }
    }else if(board[x][y].color == 3){  // 3 = magenda = braxos
        if(board[x][y-1].color == 3 and board[x][y-2].color == 3){
            board[x][y].color = 5;
            board[x][y-1].color = 5;
            board[x][y-2].color = 5;
            points_counter+= 10;
            display();
            disOne(x,y,x,y-2,false,4);
            disTwo(x,y,x,y-2,false,2);
        }else if(board[x][y+1].color == 3 and board[x][y+2].color == 3){
            board[x][y].color = 5;
            board[x][y+1].color = 5;
            board[x][y+2].color = 5;
            points_counter+= 10;
            display();
            disOne(x,y+2,x,y,false,4);
            disTwo(x,y+2,x,y,false,2);
            disThree(x,y+2,x,y,false,2);
        }else if(board[x-1][y].color == 3 and board[x-2][y].color == 3){
            board[x][y].color = 5;
            board[x-1][y].color = 5;
            board[x-2][y].color = 5;
            points_counter+= 10;
            display();
            disOne(x-2,y,x,y,true,4);
            disTwo(x-2,y,x,y,true,2);
            disThree(x-2,y,x,y,true,2);
        }else if(board[x+1][y].color == 3 and board[x+2][y].color == 3){
            board[x][y].color = 5;
            board[x+1][y].color = 5;
            board[x+2][y].color = 5;
            points_counter+= 10;
            display();
            disOne(x,y,x+2,y,true,4);
            disTwo(x,y,x+2,y,true,2);
            disThree(x,y,x+2,y,true,2);
        }else if(board[x][y-1].color == 3 and board[x][y+1].color == 3){
            board[x][y].color = 5;
            board[x][y-1].color = 5;
            board[x][y+1].color = 5;
            points_counter+= 10;
            display();
            disOne(x,y+1,x,y-1,false,4);
            disTwo(x,y+1,x,y-1,false,2);
            disThree(x,y+1,x,y-1,false,2);
        }else if(board[x-1][y].color == 3 and board[x+1][y].color == 3){
            board[x][y].color = 5;
            board[x-1][y].color = 5;
            board[x+1][y].color = 5;
            points_counter+= 10;
            display();
            disOne(x-1,y,x+1,y,true,4);
            disTwo(x-1,y,x+1,y,true,2);
            disThree(x-1,y,x+1,y,true,2);
        }
    }

}

/////////////////////////////// TELOS H KATASTROFH TWN KYBWV ///////////////////////////////



void mouse(int btn,int status,int x,int y){//mouse interfacing{

    y=500-y;
    if((stroke == 0) && (btn == GLUT_LEFT_BUTTON) && (status == GLUT_DOWN))
    {
        if(game_ended == true){
            return;
        }
        if( board[x/dx][y/dy].color == 5 ){
            return;
        }else{
            status = GLUT_UP;
            stroke=1;
            pastx=x;
            pasty=y;
            printf("pastx=%d,%d\n",pastx/dx,pasty/dy);
        }
        
    }
    if((stroke == 1) && (btn == GLUT_LEFT_BUTTON) && (status == GLUT_DOWN)){
        status = GLUT_UP;
        stroke=0;
        nextx=x;
        nexty=y;
        printf("nextx=%d,%d\n",nextx/dx,nexty/dy);
        if( (abs(((pastx/dx)-(nextx/dx)) == 1) || abs(((nextx/dx)-(pastx/dx)) == 1)) && ((pasty/dy) == (nexty/dy))){
            swapthetwo=1;
        }
        if( (abs(((pasty/dy)-(nexty/dy)) == 1) || abs(((nexty/dy)-(pasty/dy)) == 1)) && ((pastx/dx) == (nextx/dx))){
            swapthetwo=1;
        }
    }
}

void idle(void){

    int temp;
    if(swapthetwo){
        swapthetwo=0;
        temp=board[pastx/dx][pasty/dy].color;
        board[pastx/dx][pasty/dy].color=board[nextx/dx][nexty/dy].color;
        board[nextx/dx][nexty/dy].color=temp;
        moves_counter--;
        printf("swapped\n");
        display();

        destruction(nextx/dx, nexty/dy);

        if(board[pastx/dx][pasty/dy].color == 5){
            neighbor((nextx/dx),(nexty/dy),temp);
        }

        if(moves_counter == 0){
            game_ended = true;
            display();
        }
    }
}

void goMenu(int value){
    
    switch(value){
        case 2:
            exit(0);
        case 1:
            game_started = true;
            display();
    }
}

void startingMenu(){
    
    int sub1=glutCreateMenu(goMenu);

    glutAddMenuEntry("Start Game",1);
    glutAddMenuEntry("Exit",2);
    glutCreateMenu(goMenu);
    glutAddSubMenu("Menu", sub1); 
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}


int main(int argc,char **argv)  {

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("BraXaPsa III");
    glutDisplayFunc(display);

    init();
    
    glutIdleFunc(idle);
    glutMouseFunc(mouse);

    startingMenu();

    glutMainLoop();
    return(0);
}
#include "graphics.h"
#include "circle.h"
#include "rect.h"
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

GLdouble width, height;
int wd;
const color skyBlue(77/255.0, 213/255.0, 240/255.0);
const color grassGreen(26/255.0, 176/255.0, 56/255.0);
const color white(1, 1, 1);
const color brickRed(201/255.0, 20/255.0, 20/255.0);
const color darkBlue(1/255.0, 110/255.0, 214/255.0);
const color purple(119/255.0, 11/255.0, 224/255.0);
const color black(0, 0, 0);
const color magenta(1, 0, 1);
const color orange(1, 163/255.0, 22/255.0);
const color cyan (0, 1, 1);
const color yellow(1, 1, 0);

// Initial movement in the Y direction

int deltaY = -5;
vector<int> deltaYVec = {-5, -5, -5};
// Screens 
enum screens {
    SCREEN_ONE, 
    SCREEN_TWO, 
    SCREEN_THREE,
    SCREEN_FOUR,
    SCREEN_FIVE,
    SCREEN_FINAL
    };

struct UserCenter {
    int x;
    int y;
};

const UserCenter USER_INITIAL_POS = { .x = 30, .y = 250};

Rect deathTangle1;
Rect deathTangle2;
Rect deathTangle3;
Rect deathTangle4;

vector<Rect> deathTangleVec1;

Rect user;
Rect goal;
screens curr_screen = SCREEN_ONE;


void initDeathTangle1() {
    deathTangle1.setCenter(250,250);
    deathTangle1.setSize(40, 300);
    deathTangle1.setColor(black);
}

void initDeathTangle2() {
    deathTangle2.setCenter(250,250);
    deathTangle2.setSize(40, 300);
    deathTangle2.setColor(black);
}

void initDeathTangle3() {
    deathTangle3.setCenter(250,250);
    deathTangle3.setSize(40, 300);
    deathTangle3.setColor(black);
}

void initDeathTangle4() {
    deathTangleVec1.push_back(Rect(black, {250, 250}, {40, 300})); 
    deathTangleVec1.push_back(Rect(black, {100, 300}, {40, 300})); 
    deathTangleVec1.push_back(Rect(black, {400, 200}, {40, 300})); 
}


void initGoal() {
    goal.setCenter(480, 250);
    goal.setSize(40, 500);
    user.setColor(orange);
}

void initUser() {
    // TODO: Initialize the user to be a 20x20 white block
    // centered in the top left corner of the graphics window
    user.setCenter(USER_INITIAL_POS.x, USER_INITIAL_POS.y);
    user.setSize(20, 20);
    user.setColor(cyan);
}


void init() {
    width = 500;
    height = 500;
    initUser();
    initGoal();
    initDeathTangle1();
    initDeathTangle2();
    initDeathTangle3();
    initDeathTangle4();
}

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(brickRed.red, black.green, darkBlue.blue, 1.0f);
}

void finalScreenMessage(std::string message) {
    glColor3f(1, 1, 1);
    glRasterPos2i(210, 250);
    for (const char &letter: message) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
    }
}


/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
    // Tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width, height); // DO NOT CHANGE THIS LINE
    
    // Do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION); // DO NOT CHANGE THIS LINE
    glLoadIdentity(); // DO NOT CHANGE THIS LINE
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f); // DO NOT CHANGE THIS LINE

    // Clear the color buffer with current clearing color
    glClear(GL_COLOR_BUFFER_BIT); // DO NOT CHANGE THIS LINE
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // DO NOT CHANGE THIS LINE
    
    /*
     * Draw here
     */


    switch(curr_screen) { 
        case SCREEN_ONE:

            goal.setColor(orange);
            user.setColor(cyan);
            if (goal.isOverlapping(user)) {
                curr_screen = SCREEN_TWO;
                user.setCenter(USER_INITIAL_POS.x, USER_INITIAL_POS.y);
                break;
            } else {
                goal.setColor(orange);
                goal.draw();
            }
            user.draw();
            break;
        case SCREEN_TWO:
            goal.setColor(orange);
            user.setColor(cyan);
            deathTangle1.setColor(black);
            if (deathTangle1.isOverlapping(user)) {
                user.setCenter(USER_INITIAL_POS.x, USER_INITIAL_POS.y);
            }
            if (goal.isOverlapping(user)) {
                curr_screen = SCREEN_THREE;
                user.setCenter(USER_INITIAL_POS.x, USER_INITIAL_POS.y);
                break;
            } else {
                goal.setColor(orange);
                goal.draw();
            }
            deathTangle1.draw();
            user.draw();
            break;
        case SCREEN_THREE:
            goal.setColor(orange);
            user.setColor(cyan);
            deathTangle2.setColor(black);
            if (deathTangle2.isOverlapping(user)) {
                user.setCenter(USER_INITIAL_POS.x, USER_INITIAL_POS.y);
                deathTangle2.setCenter(250, 250);
            }
            if (goal.isOverlapping(user)) {
                curr_screen = SCREEN_FOUR;
                user.setCenter(USER_INITIAL_POS.x, USER_INITIAL_POS.y);
                break;
            } else {
                goal.setColor(orange);
                goal.draw();
            }
            deathTangle2.draw();
            user.draw();
            break;
        case SCREEN_FOUR:
            goal.setColor(orange);
            user.setColor(cyan);
            deathTangle3.setColor(black);
            if (deathTangle3.isOverlapping(user)) {
                user.setCenter(USER_INITIAL_POS.x, USER_INITIAL_POS.y);
            }
            if (goal.isOverlapping(user)) {
                curr_screen = SCREEN_FIVE;
                user.setCenter(USER_INITIAL_POS.x, USER_INITIAL_POS.y);
                break;
            } else {
                goal.setColor(orange);
                goal.draw();
            }
            deathTangle3.draw();
            user.draw();
            break;
        case SCREEN_FIVE:
            goal.setColor(orange);
            for (Rect &r : deathTangleVec1) {
                r.setColor(black);
            }
            user.setColor(cyan);
            for (Rect &r :deathTangleVec1) {
                if (r.isOverlapping(user)) {
                    user.setCenter(USER_INITIAL_POS.x, USER_INITIAL_POS.y);
                }
                if (goal.isOverlapping(user)) {
                    curr_screen = SCREEN_FINAL;
                    user.setCenter(USER_INITIAL_POS.x, USER_INITIAL_POS.y);
                    break;
                } else {
                    goal.setColor(orange);
                    goal.draw();
                }
            }

            for (Rect &r : deathTangleVec1) {
                r.draw();
            }
            user.draw();
            break;
        case SCREEN_FINAL:
            finalScreenMessage("You Win!");
            break;
    }


    glFlush();  // Render now
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y) {
    // escape
    if (key == 27) {
        glutDestroyWindow(wd);
        exit(0);
    }
    
    glutPostRedisplay();
}

void kbdS(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_DOWN:
            user.moveY(5);
            break;
        case GLUT_KEY_LEFT:
            user.moveX(-5);
            break;
        case GLUT_KEY_RIGHT:
            user.moveX(5);
            break;
        case GLUT_KEY_UP:
            user.moveY(-5);
            break;
        case GLUT_KEY_DOWN && GLUT_KEY_LEFT:
            break;
    }
    
    glutPostRedisplay();
}

void cursor(int x, int y) {
    glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {

    glutPostRedisplay();
}


void deathTangleTimer(int dummy) {
    switch(curr_screen) {
        case SCREEN_ONE:
            break;
        case SCREEN_TWO:
            break;
        case SCREEN_THREE:
            deathTangle2.move(-2, 0);
            break;
        case SCREEN_FOUR:
            if (deathTangle3.getTopY() < 0) {
                deltaY = 5;
                deathTangle3.moveY(deltaY);
            } else if (deathTangle3.getBottomY() > 500) {
                deltaY = -5;
                deathTangle3.moveY(deltaY);
            } else {
                deathTangle3.moveY(deltaY); // inital case I think ? 
            } 
            break;
        case SCREEN_FIVE:
            int i = 0;
            for (Rect &r : deathTangleVec1) {
                if (r.getTopY() < 0) {
                    deltaYVec[i] = 5;
                    r.moveY(deltaYVec[i]);
                } else if (r.getBottomY() > 500) {
                    deltaYVec[i] = -5;
                    r.moveY(deltaYVec[i]);
                } else {
                    r.moveY(deltaYVec[i]); // inital case I think ? 
                }
                i++;
            }
            break;
    }

    glutPostRedisplay();
    glutTimerFunc(30, deathTangleTimer, dummy);
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
    
    init();
    
    glutInit(&argc, argv);          // Initialize GLUT
    
    glutInitDisplayMode(GLUT_RGBA);
    
    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(100, 200); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    wd = glutCreateWindow("Runner" /* title */ );
    
    // Register callback handler for window re-paint event
    glutDisplayFunc(display);
    
    // Our own OpenGL initialization
    initGL();
    
    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);
    
    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);
    
    // handles mouse movement
    glutPassiveMotionFunc(cursor);
    
    // handles mouse click
    glutMouseFunc(mouse);
    
    // handles timer
    glutTimerFunc(0, deathTangleTimer, 0);
    
    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}

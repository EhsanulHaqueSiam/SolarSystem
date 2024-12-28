#include "InputHandler.h"
#include <GL/freeglut.h>
#include <iostream>
#include "globalVariable.h"


int changeCamera = 0;

void mouseControl(const int button, const int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        if (logoScene) logoScene = 0;

    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) exit(0);
    glutPostRedisplay();
}

void mouseWheel(int wheel, const int direction, int x, int y) {
    if (direction > 0 && zoom < 100) zoom++;
    if (direction < 0 && zoom > -75) zoom--;
    glutPostRedisplay();
}

void keyInput(const unsigned char key, int x, int y) {
    switch (key) {
        case 27: exit(0);
            break;
        case ' ': if (isAnimate) isAnimate = 0;
            else {
                isAnimate = 1;
                animate(1);
            }
            break;
        case 'o': if (smallOrbitActive) smallOrbitActive = 0;
            else smallOrbitActive = 1;
            glutPostRedisplay();
            break;
        case 'O': if (bigOrbitActive) bigOrbitActive = 0;
            else bigOrbitActive = 1;
            glutPostRedisplay();
            break;
        case 'm': if (moonsActive) moonsActive = 0;
            else moonsActive = 1;
            glutPostRedisplay();
            break;
        case 'M': if (moonsActive) moonsActive = 0;
            else moonsActive = 1;
            glutPostRedisplay();
            break;
        case 'l': if (labelsActive) labelsActive = 0;
            else labelsActive = 1;
            glutPostRedisplay();
            break;
        case 'L': if (labelsActive) labelsActive = 0;
            else labelsActive = 1;
            glutPostRedisplay();
            break;
        case '1': changeCamera = 0;
            glutPostRedisplay();
            break;
        case '2': changeCamera = 1;
            glutPostRedisplay();
            break;
        case '3': changeCamera = 2;
            glutPostRedisplay();
            break;
        default: break;
    }
}

void instructions() {
    std::cout << "SPACE to play/pause the simulation." << std::endl;
    std::cout << "ESC to exit the simulation." << std::endl;
    std::cout << "O to show/hide Big Orbital Trails." << std::endl;
    std::cout << "o to show/hide Small Orbital Trails." << std::endl;
    std::cout << "M/m to show/hide Moons." << std::endl;
    std::cout << "L/l to show/hide labels" << std::endl;
    std::cout << "1, 2 and 3 to change camera angles." << std::endl;
    std::cout << "Scroll to change camera movement" << std::endl;
}

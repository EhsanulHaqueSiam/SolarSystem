#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

void mouseControl(int button, int state, int x, int y);

void mouseWheel(int wheel, int direction, int x, int y);

void keyInput(unsigned char key, int x, int y);

void instructions();


void animate(int n);

#endif // INPUTHANDLER_H

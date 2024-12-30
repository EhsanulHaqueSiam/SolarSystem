#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glext.h>
#include "planet.h"
#include "InputHandler.h"
#include "SolarSystem.h"

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#endif

// Sun, Planets and Stars
Planet sun(5.0, 0, 0, 0, 0, 0); // Sun
Planet mer(1.0, 7, 0, 4.74, 02.11, 0); // Mercury
Planet ven(1.5, 11, 0, 3.50, 177.0, 0); // Venus
Planet ear(2.0, 16, 0, 2.98, 23.44, 0); // Earth
Planet mar(1.2, 21, 0, 2.41, 25.00, 0); // Mars
Planet jup(3.5, 28, 0, 1.31, 03.13, 0); // Jupiter
Planet sat(3.0, 37, 0, 0.97, 26.70, 0); // Saturn
Planet ura(2.5, 45.5, 0, 0.68, 97.77, 0); // Uranus
Planet nep(2.3, 53.6, 0, 0.54, 28.32, 0); // Neptune
Planet plu(0.3, 59, 0, 0.47, 119.6, 0); // Pluto
Planet lun(.40, 3, 0, 5.40, 0, 0); // Luna (Earth)
Planet pho(.20, 1.8, 0, 2.30, 0, 0); // Phobos (Mars)
Planet dei(.24, 2.4, 0, 3.60, 0, 0); // Deimos (Mars)
Planet eur(.24, 4, 0, 4.40, 0, 0); // Europa (Jupiter)
Planet gan(.24, 4.7, 0, 5.00, 0, 0); // Ganymede (Jupiter)
Planet cal(.24, 5.3, 0, 2.30, 0, 0); // Callisto (Jupiter)
Planet tit(.75, 3.7, 0, 2.40, 0, 0); // Titan (Saturn)
Planet nix(.10, 1.5, 0, 5.00, 0, 0); // Nix (Pluto)
Planet puc(.26, 2.9, 0, 7.00, 0, 0); // Puck (Uranus)
Planet tri(.36, 3.2, 0, 3.40, 0, 0); // Triton (Neptune)

int main(int argc, char **argv) {
    instructions();
    glutInit(&argc, argv);

#ifdef __APPLE__
    glutInitDisplayMode(GLUT_3_2_CORE_PROFILE | GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
#else
    glutInitContextVersion(4, 2);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
#endif

    glutInitWindowSize(1100, 1020);
    glutInitWindowPosition(500, 0);
    glutCreateWindow("Solar System");
    glutDisplayFunc(drawScenesInOrder);
    glutReshapeFunc(resize);
    glutMouseFunc(mouseControl);
    glutKeyboardFunc(keyInput);
    glutMouseWheelFunc(mouseWheel);
    glewExperimental = GL_TRUE;
    glewInit();

    setup();
    glutMainLoop();
}
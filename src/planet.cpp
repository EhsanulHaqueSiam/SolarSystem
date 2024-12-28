#include "planet.h"

Planet::Planet(const float _radius, const float _distance, const float _orbit, const float _orbitSpeed, const float _axisTilt, const float _axisAni)
    : radius(_radius), distance(_distance), orbit(_orbit), orbitSpeed(_orbitSpeed), axisTilt(_axisTilt),
      axisAni(_axisAni) {
}

void Planet::drawSmallOrbit() const {
    glPushMatrix();
    glColor3ub(255, 255, 255);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glutWireTorus(0.001, distance, 100.0, 100.0);
    glPopMatrix();
}

void Planet::drawMoon() const {
    GLUquadricObj *quad = gluNewQuadric();
    glPushMatrix();
    glColor3ub(255, 255, 255);
    glRotatef(orbit, 0.0, 1.0, 0.0);
    glTranslatef(distance, 0.0, 0.0);
    gluSphere(quad, radius, 20.0, 20.0);
    glPopMatrix();
}

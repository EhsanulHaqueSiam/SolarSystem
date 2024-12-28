#ifndef PLANET_H
#define PLANET_H

#include <GL/glew.h>
#include <GL/freeglut.h>

class Planet {
public:
    float radius, distance, orbit, orbitSpeed, axisTilt, axisAni;

    Planet(float _radius, float _distance, float _orbit, float _orbitSpeed, float _axisTilt, float _axisAni);

    void drawSmallOrbit() const;

    void drawMoon() const;
};

#endif // PLANET_H

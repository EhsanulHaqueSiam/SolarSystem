#include "SolarSystem.h"
#include "TextureLoader.h"
#include "Lighting.h"
#include "planet.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glext.h>
#include "globalVariable.h"

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#endif

extern Planet sun, mer, ven, ear, mar, jup, sat, ura, nep, plu, lun, pho, dei, eur, gan, cal, tit, nix, puc, tri;

void setup() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    setupTextures();
    setupLighting();
}

void writeBitmapString(void *font, const char *string) {
    for (const char *c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

void drawScenesInOrder() {
    if (logoScene == 1) {
        drawLogoScene();
    } else {
        drawScene();
    }
}

void resize(const int w, const int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
}

void animate(int n) {
    if (isAnimate) {
        mer.orbit += mer.orbitSpeed;
        ven.orbit += ven.orbitSpeed;
        ear.orbit += ear.orbitSpeed;
        mar.orbit += mar.orbitSpeed;
        jup.orbit += jup.orbitSpeed;
        sat.orbit += sat.orbitSpeed;
        ura.orbit += ura.orbitSpeed;
        nep.orbit += nep.orbitSpeed;
        plu.orbit += plu.orbitSpeed;
        lun.orbit += lun.orbitSpeed;
        pho.orbit += pho.orbitSpeed;
        dei.orbit += dei.orbitSpeed;
        eur.orbit += eur.orbitSpeed;
        gan.orbit += gan.orbitSpeed;
        cal.orbit += cal.orbitSpeed;
        tit.orbit += tit.orbitSpeed;
        nix.orbit += nix.orbitSpeed;
        puc.orbit += puc.orbitSpeed;
        tri.orbit += tri.orbitSpeed;
        if (mer, ven, ear, mar, jup, sat, ura, nep, plu, lun, pho, dei, eur, gan, cal, tit, nix, puc, tri.orbit >
            360.0) {
            mer, ven, ear, mar, jup, sat, ura, nep, plu, lun, pho, dei, eur, gan, cal, tit, nix, puc, tri.orbit -=
                    360.0;
        }
        mer.axisAni += 10.0;
        ven.axisAni += 10.0;
        ear.axisAni += 10.0;
        mar.axisAni += 10.0;
        jup.axisAni += 10.0;
        sat.axisAni += 10.0;
        ura.axisAni += 10.0;
        nep.axisAni += 10.0;
        plu.axisAni += 10.0;
        if (mer, ven, ear, mar, jup, sat, ura, nep, plu.axisAni > 360.0) {
            mer, ven, ear, mar, jup, sat, ura, nep, plu.axisAni -= 360.0;
        }
        glutPostRedisplay();
        glutTimerFunc(30, animate, 1);
    }
}

void orbitalTrails() {
    glPushMatrix();
    glColor3ub(255, 255, 255);
    glTranslatef(0.0, 0.0, 0.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glutWireTorus(0.001, mer.distance, 100.0, 100.0);
    glutWireTorus(0.001, ven.distance, 100.0, 100.0);
    glutWireTorus(0.001, ear.distance, 100.0, 100.0);
    glutWireTorus(0.001, mar.distance, 100.0, 100.0);
    glutWireTorus(0.001, jup.distance, 100.0, 100.0);
    glutWireTorus(0.001, sat.distance, 100.0, 100.0);
    glutWireTorus(0.001, ura.distance, 100.0, 100.0);
    glutWireTorus(0.001, nep.distance, 100.0, 100.0);
    glutWireTorus(0.001, plu.distance, 100.0, 100.0);
    glPopMatrix();
}

void drawLogoScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, logTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-100, -100, -100);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(100, -100, -100);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(100, 100, -100);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-100, 100, -100);
    glEnd();

    glutSwapBuffers();
}

void drawScene() {
    frameCount++;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if (changeCamera == 0)gluLookAt(0.0, zoom, 50.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    if (changeCamera == 1)gluLookAt(0.0, 0.0, zoom, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    if (changeCamera == 2)gluLookAt(0.0, zoom, 0.00001, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    if (bigOrbitActive == 1) orbitalTrails();

    GLUquadric *quad = gluNewQuadric();

    //Sun
    glPushMatrix();
    glRotatef(sun.orbit, 0.0, 1.0, 0.0);
    glTranslatef(sun.distance, 0.0, 0.0);
    if (labelsActive == 1) {
        glRasterPos3f(-1.2, 7.0, 0.0);
        glColor3ub(255, 255, 255);
        writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Sun");
    }
    glPushMatrix();
    glRotatef(sun.axisTilt, 1.0, 0.0, 0.0);
    glRotatef(sun.axisAni, 0.0, 1.0, 0.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, sunTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    gluQuadricTexture(quad, 1);
    gluSphere(quad, sun.radius, 20.0, 20.0);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glPopMatrix();

    //Mercury
    glPushMatrix();
    glRotatef(mer.orbit, 0.0, 1.0, 0.0);
    glTranslatef(mer.distance, 0.0, 0.0);
    if (labelsActive == 1) {
        glRasterPos3f(0.0, 3, 0.0);
        glColor3ub(255, 255, 255);
        writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Mercury");
    }
    glPushMatrix();
    glRotatef(mer.axisTilt, 1.0, 0.0, 0.0);
    glRotatef(mer.axisAni, 0.0, 1.0, 0.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, merTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    gluQuadricTexture(quad, 1);
    gluSphere(quad, mer.radius, 20.0, 20.0);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glPopMatrix();

    //Venus
    glPushMatrix();
    glRotatef(ven.orbit, 0.0, 1.0, 0.0);
    glTranslatef(ven.distance, 0.0, 0.0);
    if (labelsActive == 1) {
        glRasterPos3f(0.0, 3, 0.0);
        glColor3ub(255, 255, 255);
        writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Venus");
    }
    glPushMatrix();
    glRotatef(ven.axisTilt, 1.0, 0.0, 0.0);
    glRotatef(ven.axisAni, 0.0, 1.0, 0.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, venTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    gluQuadricTexture(quad, 1);
    gluSphere(quad, ven.radius, 20.0, 20.0);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glPopMatrix();

    //Earth, Orbit, Moon
    glPushMatrix();
    glRotatef(ear.orbit, 0.0, 1.0, 0.0);
    glTranslatef(ear.distance, 0.0, 0.0);
    if (labelsActive == 1) {
        glRasterPos3f(0.0, 3, 0.0);
        glColor3ub(255, 255, 255);
        writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Earth");
    }
    glPushMatrix();
    glRotatef(ear.axisTilt, 1.0, 0.0, 0.0);
    glRotatef(ear.axisAni, 0.0, 1.0, 0.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, earTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    gluQuadricTexture(quad, 1);
    gluSphere(quad, ear.radius, 20.0, 20.0);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    if (smallOrbitActive == 1) {
        lun.drawSmallOrbit();
    }
    if (moonsActive == 1) {
        lun.drawMoon();
    }
    glPopMatrix();

    //Mars, Orbits, Moons
    glPushMatrix();
    glRotatef(mar.orbit, 0.0, 1.0, 0.0);
    glTranslatef(mar.distance, 0.0, 0.0);
    if (labelsActive == 1) {
        glRasterPos3f(0.0, 3, 0.0);
        glColor3ub(255, 255, 255);
        writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Mars");
    }
    glPushMatrix();
    glRotatef(mar.axisTilt, 1.0, 0.0, 0.0);
    glRotatef(mar.axisAni, 0.0, 1.0, 0.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, marTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    gluQuadricTexture(quad, 1);
    gluSphere(quad, mar.radius, 20.0, 20.0);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    if (smallOrbitActive == 1) {
        pho.drawSmallOrbit();
        dei.drawSmallOrbit();
    }
    if (moonsActive == 1) {
        pho.drawMoon();
        dei.drawMoon();
    }
    glPopMatrix();

    //Jupiter, Orbits, Moons
    glPushMatrix();
    glRotatef(jup.orbit, 0.0, 1.0, 0.0);
    glTranslatef(jup.distance, 0.0, 0.0);
    if (labelsActive == 1) {
        glRasterPos3f(0.0, 4.4, 0.0);
        glColor3ub(255, 255, 255);
        writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Jupiter");
    }
    glPushMatrix();
    glRotatef(jup.axisTilt, 1.0, 0.0, 0.0);
    glRotatef(jup.axisAni, 0.0, 1.0, 0.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, jupTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    gluQuadricTexture(quad, 1);
    gluSphere(quad, jup.radius, 20.0, 20.0);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    if (smallOrbitActive == 1) {
        eur.drawSmallOrbit();
        gan.drawSmallOrbit();
        cal.drawSmallOrbit();
    }
    if (moonsActive == 1) {
        eur.drawMoon();
        gan.drawMoon();
        cal.drawMoon();
    }
    glPopMatrix();

    //Saturn, Orbit, Moon
    glPushMatrix();
    glRotatef(sat.orbit, 0.0, 1.0, 0.0);
    glTranslatef(sat.distance, 0.0, 0.0);
    if (labelsActive == 1) {
        glRasterPos3f(0.0, 4.4, 0.0);
        glColor3ub(255, 255, 255);
        writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Saturn");
    }
    glPushMatrix();
    glRotatef(sat.axisTilt, 1.0, 0.0, 0.0);
    glRotatef(sat.axisAni, 0.0, 1.0, 0.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, satTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    gluQuadricTexture(quad, 1);
    gluSphere(quad, sat.radius, 20.0, 20.0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glPushMatrix();
    glColor3ub(158, 145, 137);
    glRotatef(-63.0, 1.0, 0.0, 0.0);
    glutWireTorus(0.2, 6.0, 30.0, 30.0);
    glutWireTorus(0.4, 5.0, 30.0, 30.0);
    glPopMatrix();
    if (smallOrbitActive == 1) {
        tit.drawSmallOrbit();
    }
    if (moonsActive == 1) {
        tit.drawMoon();
    }
    glPopMatrix();

    glColor3ub(255, 255, 255); //FIXES SHADING ISSUE

    //Uranus, Orbit, Moon
    glPushMatrix();
    glRotatef(ura.orbit, 0.0, 1.0, 0.0);
    glTranslatef(ura.distance, 0.0, 0.0);
    if (labelsActive == 1) {
        glRasterPos3f(0.0, 4.4, 0.0);
        glColor3ub(255, 255, 255);
        writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Uranus");
    }
    glPushMatrix();
    glRotatef(ura.axisTilt, 1.0, 0.0, 0.0);
    glRotatef(ura.axisAni, 0.0, 1.0, 0.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, uraTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    gluQuadricTexture(quad, 1);
    gluSphere(quad, ura.radius, 20.0, 20.0);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    if (smallOrbitActive == 1) {
        puc.drawSmallOrbit();
    }
    if (moonsActive == 1) {
        puc.drawMoon();
    }
    glPopMatrix();

    //Neptune, Orbit, Moon
    glPushMatrix();
    glRotatef(nep.orbit, 0.0, 1.0, 0.0);
    glTranslatef(nep.distance, 0.0, 0.0);
    if (labelsActive == 1) {
        glRasterPos3f(0.0, 4.4, 0.0);
        glColor3ub(255, 255, 255);
        writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Neptune");
    }
    glPushMatrix();
    glRotatef(nep.axisTilt, 1.0, 0.0, 0.0);
    glRotatef(nep.axisAni, 0.0, 1.0, 0.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, nepTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    gluQuadricTexture(quad, 1);
    gluSphere(quad, nep.radius, 20.0, 20.0);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    if (smallOrbitActive == 1) {
        tri.drawSmallOrbit();
    }
    if (moonsActive == 1) {
        tri.drawMoon();
    }
    glPopMatrix();

    //Pluto, Orbit, Moon
    glPushMatrix();
    glRotatef(plu.orbit, 0.0, 1.0, 0.0);
    glTranslatef(plu.distance, 0.0, 0.0);
    if (labelsActive == 1) {
        glRasterPos3f(0.0, 3.0, 0.0);
        glColor3ub(255, 255, 255);
        writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Pluto");
    }
    glPushMatrix();
    glRotatef(plu.axisTilt, 1.0, 0.0, 0.0);
    glRotatef(plu.axisAni, 0.0, 1.0, 0.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, pluTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    gluQuadricTexture(quad, 1);
    gluSphere(quad, plu.radius, 20.0, 20.0);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    if (smallOrbitActive == 1) {
        nix.drawSmallOrbit();
    }
    if (moonsActive == 1) {
        nix.drawMoon();
    }
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, staTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBegin(GL_POLYGON);
    glTexCoord2f(-1.0, 0.0);
    glVertex3f(-200, -200, -100);
    glTexCoord2f(2.0, 0.0);
    glVertex3f(200, -200, -100);
    glTexCoord2f(2.0, 2.0);
    glVertex3f(200, 200, -100);
    glTexCoord2f(-1.0, 2.0);
    glVertex3f(-200, 200, -100);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, staTexture);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-200, -83, 200);
    glTexCoord2f(8.0, 0.0);
    glVertex3f(200, -83, 200);
    glTexCoord2f(8.0, 8.0);
    glVertex3f(200, -83, -200);
    glTexCoord2f(0.0, 8.0);
    glVertex3f(-200, -83, -200);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glutSwapBuffers();
}

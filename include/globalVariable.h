#ifndef GLOBALVARIABLE_H
#define GLOBALVARIABLE_H

inline int logoScene = 1;
inline int isAnimate = 0;
inline int smallOrbitActive = 1;
inline int bigOrbitActive = 1;
inline int moonsActive = 1;
inline int labelsActive = 0;
extern int changeCamera;
inline int zoom = 0;
inline float lightPos[] = {0.0, 0.0, -75.0, 1.0}; // Spotlight position.
inline float spotAngle = 40; // Spotlight cone half-angle.
inline float spotDirection[] = {1.0, 0.0, 0.0}; // Spotlight direction.
inline float spotExponent = 1.0; // Spotlight exponent = attenuation factor.;
inline int frameCount = 0;

#endif //GLOBALVARIABLE_H

#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include "imageloader.h"
#include <GL/glew.h>

void setupTextures();

GLuint loadTexture(const Image *image);

extern GLuint sunTexture, merTexture, venTexture, earTexture, marTexture, jupTexture, satTexture, uraTexture, nepTexture
        , pluTexture, staTexture, logTexture;

#endif // TEXTURELOADER_H

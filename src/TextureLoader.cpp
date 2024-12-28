#include "TextureLoader.h"

GLuint sunTexture, merTexture, venTexture, earTexture, marTexture, jupTexture, satTexture, uraTexture, nepTexture,
        pluTexture, staTexture, logTexture;

GLuint loadTexture(const Image *image) {
    GLuint textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
    return textureId;
}

void setupTextures() {
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    const Image *sta = loadBMP("stars.bmp");
    staTexture = loadTexture(sta);
    delete sta;
    const Image *sun = loadBMP("sun.bmp");
    sunTexture = loadTexture(sun);
    delete sun;
    const Image *mer = loadBMP("mercury.bmp");
    merTexture = loadTexture(mer);
    delete mer;
    const Image *ven = loadBMP("venus.bmp");
    venTexture = loadTexture(ven);
    delete ven;
    const Image *ear = loadBMP("earth.bmp");
    earTexture = loadTexture(ear);
    delete ear;
    const Image *mar = loadBMP("mars.bmp");
    marTexture = loadTexture(mar);
    delete mar;
    const Image *jup = loadBMP("jupiter.bmp");
    jupTexture = loadTexture(jup);
    delete jup;
    const Image *sat = loadBMP("saturn.bmp");
    satTexture = loadTexture(sat);
    delete sat;
    const Image *ura = loadBMP("uranus.bmp");
    uraTexture = loadTexture(ura);
    delete ura;
    const Image *nep = loadBMP("neptune.bmp");
    nepTexture = loadTexture(nep);
    delete nep;
    const Image *plu = loadBMP("pluto.bmp");
    pluTexture = loadTexture(plu);
    delete plu;
    const Image *log = loadBMP("logo.bmp");
    logTexture = loadTexture(log);
    delete log;
}

#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <string>

// Represents an image
class Image {
public:
    Image(char *ps, int w, int h);

    ~Image();

    char *pixels;
    int width;
    int height;
};

// Reads a bitmap image from file.
Image *loadBMP(const std::string &filename);

#endif // IMAGELOADER_H

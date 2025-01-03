#include "imageloader.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <filesystem>

Image::Image(char *ps, const int w, const int h) : pixels(ps), width(w), height(h) {
}

Image::~Image() {
    delete[] pixels;
}

namespace {
    int toInt(const char *bytes) {
        return (int) ((static_cast<unsigned char>(bytes[3]) << 24) |
                      (static_cast<unsigned char>(bytes[2]) << 16) |
                      (static_cast<unsigned char>(bytes[1]) << 8) |
                      static_cast<unsigned char>(bytes[0]));
    }

    short toShort(const char *bytes) {
        return static_cast<short>((static_cast<unsigned char>(bytes[1]) << 8) |
                                  static_cast<unsigned char>(bytes[0]));
    }

    int readInt(std::ifstream &input) {
        char buffer[4];
        input.read(buffer, 4);
        return toInt(buffer);
    }

    short readShort(std::ifstream &input) {
        char buffer[2];
        input.read(buffer, 2);
        return toShort(buffer);
    }

    template<class T>
    class auto_array {
    private:
        T *array;
        mutable bool isReleased;

    public:
        explicit auto_array(T *array_ = nullptr) : array(array_), isReleased(false) {
        }

        auto_array(const auto_array<T> &aarray) {
            array = aarray.array;
            isReleased = aarray.isReleased;
            aarray.isReleased = true;
        }

        ~auto_array() {
            if (!isReleased && array != nullptr) {
                delete[] array;
            }
        }

        T *get() const {
            return array;
        }

        T &operator*() const {
            return *array;
        }

        void operator=(const auto_array<T> &aarray) {
            if (!isReleased && array != nullptr) {
                delete[] array;
            }
            array = aarray.array;
            isReleased = aarray.isReleased;
            aarray.isReleased = true;
        }

        T *operator->() const {
            return array;
        }

        T *release() {
            isReleased = true;
            return array;
        }

        void reset(T *array_ = nullptr) {
            if (!isReleased && array != nullptr) {
                delete[] array;
            }
            array = array_;
        }

        T *operator+(int i) {
            return array + i;
        }

        T &operator[](int i) {
            return array[i];
        }
    };
}

Image *loadBMP(const std::string &filename) {
    std::filesystem::path filePath = std::filesystem::current_path() / "assets" / filename;
    std::ifstream input(filePath, std::ifstream::binary);
    if (!input) {
        std::cerr << "Could not find file: " << filePath << std::endl;
        return nullptr;
    }

    char buffer[2];
    input.read(buffer, 2);
    assert(buffer[0] == 'B' && buffer[1] == 'M' || !"Not a bitmap file");
    input.ignore(8);
    int dataOffset = readInt(input);

    int headerSize = readInt(input);
    int width;
    int height;
    switch (headerSize) {
        case 40:
            width = readInt(input);
            height = readInt(input);
            input.ignore(2);
            assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
            assert(readShort(input) == 0 || !"Image is compressed");
            break;
        case 12:
            width = readShort(input);
            height = readShort(input);
            input.ignore(2);
            assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
            break;
        default:
            std::cerr << "Unknown bitmap format" << std::endl;
            return nullptr;
    }

    int bytesPerRow = ((width * 3 + 3) / 4) * 4 - (width * 3 % 4);
    int size = bytesPerRow * height;
    auto_array<char> pixels(new char[size]);
    input.seekg(dataOffset, std::ios_base::beg);
    input.read(pixels.get(), size);

    auto_array<char> pixels2(new char[width * height * 3]);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            for (int c = 0; c < 3; c++) {
                pixels2[3 * (width * y + x) + c] = pixels[bytesPerRow * y + 3 * x + (2 - c)];
            }
        }
    }

    input.close();
    return new Image(pixels2.release(), width, height);
}

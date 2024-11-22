#include "jpeg.h"

JPEG::JPEG(std::vector<char> data, const int32_t width, const int32_t height, const bool isRgb) {
    this->data = std::move(data);
    this->width = width;
    this->height = height;
    this->isRgb = isRgb;
}

JPEG::JPEG(std::vector<char> r, std::vector<char> g, std::vector<char> b, const int32_t width, const int32_t height) {
    this->r = std::move(r);
    this->g = std::move(g);
    this->b = std::move(b);
    this->width = width;
    this->height = height;
    this->isRgb = false;
    isRgb = true;
}

void JPEG::setValueRGB(const int32_t row, const int32_t column, const char value, const int32_t channel) {
    if (column >= this->width || row >= this->height) {
        return;
    }

    switch (channel) {
        case 1:
            this->r[row * width + column] = value;
            break;
        case 2:
            this->g[row * width + column] = value;
            break;
        case 3:
            this->b[row * width + column] = value;
            break;
        default:
            // Error
    }
}

void JPEG::setPixelRGB(const int32_t row, const int32_t column, const char r, const char g, const char b) {
    if (column >= this->width || row >= this->height) {
        return;
    }

    this->setValueRGB(row, column, r, 0);
    this->setValueRGB(row, column, g, 1);
    this->setValueRGB(row, column, b, 2);
}

void JPEG::setValueYUV(int32_t row, int32_t column, char value, int32_t channel) {
    if (column >= this->width || row >= this->height) {
        return;
    }

    switch (channel) {
        case 1:
            this->y[row * width + column] = value;
            break;
        case 2:
            this->u[row * width + column] = value;
            break;
        case 3:
            this->v[row * width + column] = value;
            break;
        default:
            // Error
    }
}

void JPEG::setPixelYUV(int32_t row, int32_t column, char y, char u, char v) {
    if (column >= this->width || row >= this->height) {
        return;
    }

    this->setValueYUV(row, column, y, 0);
    this->setValueYUV(row, column, v, 1);
    this->setValueYUV(row, column, y, 2);
}

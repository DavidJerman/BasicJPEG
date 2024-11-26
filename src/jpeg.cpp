#include "jpeg.h"

#include <stdexcept>
#include <iostream>

#include "bmp.h"

JPEG::JPEG(const std::string &filename) {
    const BMP bmp(filename);

    this->r = bmp.getR();
    this->g = bmp.getG();
    this->b = bmp.getB();

    // TODO: This is an assumption
    this->isRgb = true;

    bmp.writeToFile("samples/sample_copy.bmp");
}

JPEG::JPEG(std::vector<char> r, std::vector<char> g, std::vector<char> b, const int32_t width, const int32_t height) {
    this->r = std::move(r);
    this->g = std::move(g);
    this->b = std::move(b);
    this->width = width;
    this->height = height;
    this->isRgb = true;
}

// TODO: Fix conversion

// https://en.wikipedia.org/wiki/Y%E2%80%B2UV
void JPEG::rgbToYUV() {
    if (!this->isRgb) {
        std::wcerr << "Image is not in RGB format, skipping conversion to YUV" << std::endl;
        return;
    }

    if (this->r.size() != this->g.size() || this->r.size() != this->b.size()) {
        throw std::runtime_error("RGB channels have different sizes");
    }

    if (this->r.size() != this->y.size() || this->r.size() != this->u.size() || this->r.size() != this->v.size()) {
        this->y.resize(this->width * this->height);
        this->u.resize(this->width * this->height);
        this->v.resize(this->width * this->height);
    }

    for (int i = 0; i < this->width * this->height; ++i) {
        const uint8_t r = this->r[i];
        const uint8_t g = this->g[i];
        const uint8_t b = this->b[i];

        // Convert to YUV
        auto y =  0.257 * r + 0.504 * g + 0.098 * b + 16;
        auto u = -0.148 * r - 0.291 * g + 0.439 * b + 128;
        auto v =  0.439 * r - 0.368 * g - 0.071 * b + 128;

        // Clamp values to [0, 255]
        y = std::clamp(y, 0.0, 255.0);
        u = std::clamp(u, 0.0, 255.0);
        v = std::clamp(v, 0.0, 255.0);

        // Store values
        this->y[i] = static_cast<char>(y);
        this->u[i] = static_cast<char>(u);
        this->v[i] = static_cast<char>(v);
    }
}

void JPEG::yuvToRGB() {
    if (this->y.size() != this->u.size() || this->y.size() != this->v.size()) {
        throw std::runtime_error("YUV channels have different sizes");
    }

    if (this->y.size() != this->r.size() || this->y.size() != this->g.size() || this->y.size() != this->b.size()) {
        this->r.resize(this->width * this->height);
        this->g.resize(this->width * this->height);
        this->b.resize(this->width * this->height);
    }

    for (int i = 0; i < this->width * this->height; ++i) {
        const uint8_t y = this->y[i];
        const uint8_t u = this->u[i];
        const uint8_t v = this->v[i];

        // Convert to RGB
        auto r = 1.164 * y             + 1.596 * v;
        auto g = 1.164 * y - 0.392 * u - 0.813 * v;
        auto b = 1.164 * y + 2.017 * u;

        // Clamp values to [0, 255]
        r = std::clamp(r, 0.0, 255.0);
        g = std::clamp(g, 0.0, 255.0);
        b = std::clamp(b, 0.0, 255.0);

        // Store values
        this->r[i] = static_cast<char>(r);
        this->g[i] = static_cast<char>(g);
        this->b[i] = static_cast<char>(b);
    }
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
            throw std::runtime_error("Invalid channel for RGB value");
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
            throw std::runtime_error("Invalid channel for YUV value");
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

void JPEG::setWidth(const int32_t width) {
    this->width = width;
}

void JPEG::setHeight(const int32_t height) {
    this->height = height;
}

void JPEG::setIsRgb(const bool isRgb) {
    this->isRgb = isRgb;
}

void JPEG::setG(std::vector<char> g) {
    this->g = std::move(g);
}

void JPEG::setB(std::vector<char> b) {
    this->b = std::move(b);
}

void JPEG::setR(std::vector<char> r) {
    this->r = std::move(r);
}

void JPEG::setY(std::vector<char> y) {
    this->y = std::move(y);
}

void JPEG::setU(std::vector<char> u) {
    this->u = std::move(u);
}

void JPEG::setV(std::vector<char> v) {
    this->v = std::move(v);
}

int32_t JPEG::getWidth() const {
    return width;
}

int32_t JPEG::getHeight() const {
    return height;
}

bool JPEG::getIsRgb() const {
    return isRgb;
}

const std::vector<char> &JPEG::getR() const {
    return r;
}

const std::vector<char> &JPEG::getG() const {
    return g;
}

const std::vector<char> &JPEG::getB() const {
    return b;
}

const std::vector<char> &JPEG::getY() const {
    return y;
}

const std::vector<char> &JPEG::getU() const {
    return u;
}

const std::vector<char> &JPEG::getV() const {
    return v;
}

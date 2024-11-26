#pragma once

#include <cstdint>
#include <string>
#include <vector>

#pragma pack(push, 1)

// TODO: Set default values for BMPHeader and DIBHeader

struct BMPHeader {
    char signature[2];
    uint32_t fileSize;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t dataOffset;
};

struct DIBHeader {
    uint32_t headerSize;
    int32_t width;
    int32_t height;
    uint16_t colorPlanes;
    uint16_t bitsPerPixel;
    uint32_t compressionMethod;
    uint32_t imageSize;
    int32_t horizontalResolution;
    int32_t verticalResolution;
    uint32_t colorsInPalette;
    uint32_t importantColors;
};

struct BMPData {
    BMPHeader header;
    DIBHeader dibHeader;
    std::vector<char> r;
    std::vector<char> g;
    std::vector<char> b;
};

#pragma pack(pop)

class BMP {
    BMPData data;

public:
    BMP() = default;
    explicit BMP(const std::string &filename);

    [[nodiscard]] std::vector<char> getR() const {
        return data.r;
    }

    [[nodiscard]] std::vector<char> getG() const {
        return data.g;
    }

    [[nodiscard]] std::vector<char> getB() const {
        return data.b;
    }

    void setR(std::vector<char> r) {
        data.r = std::move(r);
    }

    void setG(std::vector<char> g) {
        data.g = std::move(g);
    }

    void setB(std::vector<char> b) {
        data.b = std::move(b);
    }

    [[nodiscard]] int32_t getWidth() const {
        return data.dibHeader.width;
    }

    [[nodiscard]] int32_t getHeight() const {
        return data.dibHeader.height;
    }

    void setWidth(const int32_t width) {
        data.dibHeader.width = width;
    }

    void setHeight(const int32_t height) {
        data.dibHeader.height = height;
    }

    void writeToFile(const std::string &filename) const;

private:
    void readFromFilename(const std::string &filename);
};

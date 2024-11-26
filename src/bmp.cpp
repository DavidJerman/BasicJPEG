#include "bmp.h"

#include <fstream>

BMP::BMP(const std::string &filename) {
    readFromFilename(filename);
}

void BMP::writeToFile(const std::string &filename) const {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file for writing: " + filename);
    }

    const uint32_t rowSize = (3 * data.dibHeader.width + 3) / 4 * 4;
    const uint32_t padding = rowSize - (3 * data.dibHeader.width);

    const uint32_t imageSize = (3 * data.dibHeader.width + padding) * data.dibHeader.height;

    // BMPHeader
    BMPHeader bmpHeader{};
    bmpHeader.signature[0] = 'B';
    bmpHeader.signature[1] = 'M';
    bmpHeader.fileSize = sizeof(BMPHeader) + sizeof(DIBHeader) + imageSize;
    bmpHeader.reserved1 = 0;
    bmpHeader.reserved2 = 0;
    bmpHeader.dataOffset = sizeof(BMPHeader) + sizeof(DIBHeader);

    // DIBHeader
    DIBHeader dibHeader{};
    dibHeader.headerSize = sizeof(DIBHeader);
    dibHeader.width = data.dibHeader.width;
    dibHeader.height = data.dibHeader.height;
    dibHeader.colorPlanes = 1;
    dibHeader.bitsPerPixel = 24;
    dibHeader.compressionMethod = 0;
    dibHeader.imageSize = imageSize;
    dibHeader.horizontalResolution = 0;
    dibHeader.verticalResolution = 0;
    dibHeader.colorsInPalette = 0;
    dibHeader.importantColors = 0;

    // Write BMP header
    file.write(reinterpret_cast<const char*>(&bmpHeader), sizeof(BMPHeader));

    // Write DIB header
    file.write(reinterpret_cast<const char*>(&dibHeader), sizeof(DIBHeader));

    // Write pixel data
    for (int y = 0; y < data.dibHeader.height; ++y) {
        for (int x = 0; x < data.dibHeader.width; ++x) {
            uint32_t pixelIndex = y * data.dibHeader.width + x;

            file.put(data.b[pixelIndex]);
            file.put(data.g[pixelIndex]);
            file.put(data.r[pixelIndex]);
        }

        // Padding
        for (uint32_t i = 0; i < padding; ++i) {
            file.put(0);
        }
    }

    file.close();
}

void BMP::readFromFilename(const std::string &filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open BMP file: " + filename);
    }

    file.read(reinterpret_cast<char*>(&data.header), sizeof(BMPHeader));
    if (data.header.signature[0] != 'B' || data.header.signature[1] != 'M') {
        throw std::runtime_error("Not a valid BMP file: " + filename);
    }

    file.read(reinterpret_cast<char*>(&data.dibHeader), sizeof(DIBHeader));

    const uint32_t rowSize = (data.dibHeader.bitsPerPixel * data.dibHeader.width + 31) / 32 * 4;
    const uint32_t padding = rowSize - (data.dibHeader.width * 3);

    file.seekg(data.header.dataOffset, std::ios::beg);

    const uint32_t totalPixels = data.dibHeader.width * data.dibHeader.height;
    data.r.resize(totalPixels);
    data.g.resize(totalPixels);
    data.b.resize(totalPixels);

    uint32_t pixelIndex = 0;
    for (int y = 0; y < data.dibHeader.height; ++y) {
        for (int x = 0; x < data.dibHeader.width; ++x) {
            char blue, green, red;
            file.read(&blue, sizeof(char));
            file.read(&green, sizeof(char));
            file.read(&red, sizeof(char));

            data.b[pixelIndex] = blue;
            data.g[pixelIndex] = green;
            data.r[pixelIndex] = red;
            ++pixelIndex;
        }

        file.ignore(padding);
    }

    file.close();
}

#pragma once

#include <cstdint>
#include <string>
#include <vector>

class JPEG {
    int32_t width {0}, height {0};
    bool isRgb {false};

    std::vector<char> r;
    std::vector<char> g;
    std::vector<char> b;

    std::vector<char> y;
    std::vector<char> u;
    std::vector<char> v;

public:
    explicit JPEG(const std::string &filename);
    JPEG(std::vector<char> r, std::vector<char> g, std::vector<char> b, int32_t width, int32_t height);

    void rgbToYUV();
    void yuvToRGB();

    void setValueRGB(int32_t row, int32_t column, char value, int32_t channel = 0);
    void setPixelRGB(int32_t row, int32_t column, char r, char g, char b);
    void setValueYUV(int32_t row, int32_t column, char value, int32_t channel = 0);
    void setPixelYUV(int32_t row, int32_t column, char y, char u, char v);

    void setWidth(int32_t width);
    void setHeight(int32_t height);
    void setIsRgb(bool isRgb);

    void setG(std::vector<char> g);
    void setB(std::vector<char> b);
    void setR(std::vector<char> r);

    void setY(std::vector<char> y);
    void setU(std::vector<char> u);
    void setV(std::vector<char> v);

    [[nodiscard]] int32_t getWidth() const;
    [[nodiscard]] int32_t getHeight() const;
    [[nodiscard]] bool getIsRgb() const;

    [[nodiscard]] const std::vector<char> &getR() const;
    [[nodiscard]] const std::vector<char> &getG() const;
    [[nodiscard]] const std::vector<char> &getB() const;

    [[nodiscard]] const std::vector<char> &getY() const;
    [[nodiscard]] const std::vector<char> &getU() const;
    [[nodiscard]] const std::vector<char> &getV() const;
};

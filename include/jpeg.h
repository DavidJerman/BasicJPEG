#pragma once

#include <cstdint>
#include <vector>

class JPEG {
    std::vector <char> data;       // Raw data
    int32_t width {0}, height {0}; // Image width, height
    bool isRgb {false};            // Is the image RGB (grayscale is saved in R)

    std::vector<char> r;
    std::vector<char> g;
    std::vector<char> b;

    std::vector<char> y;
    std::vector<char> u;
    std::vector<char> v;

public:
    JPEG(std::vector <char> data, int32_t width, int32_t height, bool isRgb);
    JPEG(std::vector<char> r, std::vector<char> g, std::vector<char> b, int32_t width, int32_t height);

    void setValueRGB(int32_t row, int32_t column, char value, int32_t channel = 0);
    void setPixelRGB(int32_t row, int32_t column, char r, char g, char b);
    void setValueYUV(int32_t row, int32_t column, char value, int32_t channel = 0);
    void setPixelYUV(int32_t row, int32_t column, char y, char u, char v);

    void setData(std::vector <char> data);
    void setData(std::vector <char> data, int32_t width, int32_t height, bool isRgb);
    void setWidth(int32_t width);
    void setHeight(int32_t height);
    void setIsRgb(bool isRgb);

    void setG(std::vector<char> g);
    void setB(std::vector<char> b);
    void setR(std::vector<char> r);

    void setY(std::vector<char> y);
    void setU(std::vector<char> u);
    void setV(std::vector<char> v);

    [[nodiscard]] const std::vector <char> &getData() const;
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

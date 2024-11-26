#include <gtest/gtest.h>

#include "jpeg.h"

class JPEGTest : public ::testing::Test {
protected:
    JPEGTest() = default;

    ~JPEGTest() override = default;
};

TEST_F(JPEGTest, RGBToYUV1) {
    const std::vector r = {static_cast<char>(255), static_cast<char>(0),   static_cast<char>(0),   static_cast<char>(255)};
    const std::vector g = {static_cast<char>(0),   static_cast<char>(255), static_cast<char>(0),   static_cast<char>(255)};
    const std::vector b = {static_cast<char>(0),   static_cast<char>(0),   static_cast<char>(255), static_cast<char>(255)};

    JPEG jpeg(r, g, b, 2, 2);
    jpeg.rgbToYUV();

    const std::vector y = {static_cast<char>(81),  static_cast<char>(144), static_cast<char>(40),  static_cast<char>(235)};
    const std::vector u = {static_cast<char>(90),  static_cast<char>(53),  static_cast<char>(239), static_cast<char>(128)};
    const std::vector v = {static_cast<char>(239), static_cast<char>(34),  static_cast<char>(109), static_cast<char>(128)};

    for (int i = 0; i < 4; ++i) {
        EXPECT_EQ(jpeg.getY()[i], y[i]);
        EXPECT_EQ(jpeg.getU()[i], u[i]);
        EXPECT_EQ(jpeg.getV()[i], v[i]);
    }
}

TEST_F(JPEGTest, YUVToRGB1) {
    const std::vector y = {static_cast<char>(81),  static_cast<char>(144), static_cast<char>(40),  static_cast<char>(235)};
    const std::vector u = {static_cast<char>(90),  static_cast<char>(53),  static_cast<char>(239), static_cast<char>(128)};
    const std::vector v = {static_cast<char>(239), static_cast<char>(34),  static_cast<char>(109), static_cast<char>(128)};

    JPEG jpeg(y, u, v, 2, 2);
    jpeg.setY(y);
    jpeg.setU(u);
    jpeg.setV(v);
    jpeg.yuvToRGB();

    const std::vector r = {static_cast<char>(255), static_cast<char>(0),   static_cast<char>(0),   static_cast<char>(255)};
    const std::vector g = {static_cast<char>(0),   static_cast<char>(255), static_cast<char>(0),   static_cast<char>(255)};
    const std::vector b = {static_cast<char>(0),   static_cast<char>(0),   static_cast<char>(255), static_cast<char>(255)};

    for (int i = 0; i < 4; ++i) {
        EXPECT_EQ(jpeg.getR()[i], r[i]);
        EXPECT_EQ(jpeg.getG()[i], g[i]);
        EXPECT_EQ(jpeg.getB()[i], b[i]);
    }
}

TEST_F(JPEGTest, RGBToYUVToRGB) {
    const std::vector r = {static_cast<char>(255), static_cast<char>(0),   static_cast<char>(0),   static_cast<char>(255)};
    const std::vector g = {static_cast<char>(0),   static_cast<char>(255), static_cast<char>(0),   static_cast<char>(255)};
    const std::vector b = {static_cast<char>(0),   static_cast<char>(0),   static_cast<char>(255), static_cast<char>(255)};

    JPEG jpeg(r, g, b, 2, 2);
    jpeg.rgbToYUV();
    jpeg.yuvToRGB();

    for (int i = 0; i < 4; ++i) {
        EXPECT_EQ(jpeg.getR()[i], r[i]);
        EXPECT_EQ(jpeg.getG()[i], g[i]);
        EXPECT_EQ(jpeg.getB()[i], b[i]);
    }
}

#include <gtest/gtest.h>

#include "bmp.h"

#include <fstream>

class BMPTest : public ::testing::Test {
protected:
    BMPTest() = default;

    ~BMPTest() override = default;

    // Helper function to check if a BMP file can be read correctly
    static bool isBMPFileValid(const std::string& filename) {
        try {
            BMP bmp(filename);
            return true;
        } catch (const std::runtime_error&) {
            return false;
        }
    }

    static bool areBMPFilesIdentical(const std::string& file1, const std::string& file2) {
        BMP bmp1(file1);
        BMP bmp2(file2);

        // Compare width and height
        if (bmp1.getWidth() != bmp2.getWidth() || bmp1.getHeight() != bmp2.getHeight()) {
            return false;
        }

        // Compare pixel data (r, g, b channels)
        const auto r1 = bmp1.getR();
        const auto g1 = bmp1.getG();
        const auto b1 = bmp1.getB();

        const auto r2 = bmp2.getR();
        const auto g2 = bmp2.getG();
        const auto b2 = bmp2.getB();

        for (int i = 0; i < bmp1.getWidth() * bmp1.getHeight(); ++i)
            if (r1[i] != r2[i] || g1[i] != g2[i] || b1[i] != b2[i])
                return false;

        return true;
    }
};

TEST_F(BMPTest, ReadInvalidBMPFile) {
    const std::string filename = "../samples/sample.jpg";

    EXPECT_FALSE(isBMPFileValid(filename));
}

TEST_F(BMPTest, ReadValidBMPFile) {
    const std::string filename = "../samples/sample.bmp";

    EXPECT_TRUE(isBMPFileValid(filename));
}

TEST_F(BMPTest, ReadBMPFile) {
    const std::string filename = "../samples/sample.bmp";

    const BMP bmp(filename);

    EXPECT_EQ(bmp.getWidth(), 640);
    EXPECT_EQ(bmp.getHeight(), 426);
    EXPECT_EQ(bmp.getR().size(), 640 * 426);
    EXPECT_EQ(bmp.getG().size(), 640 * 426);
    EXPECT_EQ(bmp.getB().size(), 640 * 426);
}

TEST_F(BMPTest, ReadWriteReadBMPFile) {
    const std::string originalFilename = "../samples/sample.bmp";
    const std::string newFilename = "new.bmp";

    const BMP bmp(originalFilename);
    bmp.writeToFile(newFilename);

    EXPECT_TRUE(isBMPFileValid(originalFilename));
    EXPECT_TRUE(isBMPFileValid(newFilename));
    EXPECT_TRUE(areBMPFilesIdentical(originalFilename, newFilename));
}

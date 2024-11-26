find_package(GTest REQUIRED)

include_directories(../include)

add_executable(JPEGTests
        test_bmp.cpp
        test_jpeg.cpp
)

target_link_libraries(JPEGTests PRIVATE JPEGLib GTest::GTest GTest::Main)

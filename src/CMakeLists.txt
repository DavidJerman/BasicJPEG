include_directories(../include)

add_library(JPEGLib
        jpeg.cpp
        bmp.cpp
)

target_include_directories(JPEGLib PUBLIC ../include)

add_executable(BasicJPEG main.cpp)

target_link_libraries(BasicJPEG JPEGLib)

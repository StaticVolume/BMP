#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <ncurses.h>

/* Используем 24 битовое изображение. Это важно, так как размер строки данных в BMP должен быть кратен 4 байтам. В случае 24 бит и длины строки в 5 мы
 получим (5*24)/8 = 15 байт, что не кратно 4, а значит будет добавлен 1 байт пустого символа, и вот этот байт в конце каждой строки надо игнорировать  */

#define BM 0x4d42
#define BIT_SIZE 8

class Image {

private:

#pragma pack (push)
#pragma pack(2) // выравнивание структуры на 2 байта

    struct BITMAP_FILE_HEADER {

            uint16_t bfType;
            uint32_t bfSize;
            uint16_t bfReserved1;
            uint16_t bfReserved2;
            uint32_t bfOffBits; ;
    };

#pragma pack(pop)

    struct BITMAP_P_INFO_HEADER {

        uint32_t biSize;
        int32_t biWidth;
        int32_t biHeight;

        uint16_t biPlanes;
        uint16_t biBitCount;
        uint32_t biCompression;
        uint32_t biSizeImage;
        int32_t biXPelsPerMeter;
        int32_t biYPelsPerMeter;
        uint32_t biClrUsed;
        uint32_t biClrImportant;

    };


    struct RGBQUAD_ARRAY { // основная проблема что стандартная RGB палитра в BMP файле читается как BGR, что и отражено в структуре

        unsigned char rgbBlue;
        unsigned char rgbGreen;
        unsigned char rgbRed;
        unsigned char rgbReserved; // если резервед, то будем использовать это поле для установки символа, если получится

    };

    std::fstream* file = nullptr;
    std::string  filepath = "image.bmp";

    BITMAP_FILE_HEADER* bmp_header = nullptr ;
    BITMAP_P_INFO_HEADER* bmp_info_header = nullptr ;
    RGBQUAD_ARRAY** rgb_array = nullptr;

    int ImgPadding;
    int ImgSize;
    int bmp_header_size;
    int bmp_info_header_size;
public:

    Image();

    void CreateImage(std::string& in_filepath);
    void DrawCharArray(struct RGBQUAD_ARRAY** rgb_array);
    void DrawBMPHeader(BITMAP_FILE_HEADER* bmp_header );
    void DrawBMPInfoHeader(BITMAP_P_INFO_HEADER* bmp_info_header);
    void DrawAnotherAttributes();

    RGBQUAD_ARRAY** GetRGBArray() const { return rgb_array; }
    BITMAP_FILE_HEADER* GetBMPHeader() const { return bmp_header; }
    BITMAP_P_INFO_HEADER* GetBMPInfoHeader() const { return bmp_info_header; }

   ~Image(){

        if ( file ) { delete file; file = nullptr ; }
        if ( bmp_header ) { delete bmp_header; bmp_header = nullptr; }
        if ( bmp_info_header ) {delete bmp_info_header; bmp_info_header = nullptr; }
        if ( rgb_array ) { delete [] rgb_array; rgb_array = nullptr; }
    }
};



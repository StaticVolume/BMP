#include "image.h"

Image::Image(){

    bmp_header = new BITMAP_FILE_HEADER();
    bmp_info_header = new BITMAP_P_INFO_HEADER();
}

void Image::CreateImage(std::string& in_filepath) {

    char ee[256];

    if(!in_filepath.empty()) {

        filepath = in_filepath;
        file = new std::fstream();
        file->open(filepath, std::ios::in | std::ios::binary);

    }

    file->read((char*)bmp_header, sizeof ( BITMAP_FILE_HEADER ) );

        if(bmp_header->bfType != BM) { // Здесь зашит код файла BM, если не совпадает, значит файл не BM

            std::cout << "Error, file is not a .bmp" << std::endl;

        }

    file->read((char*)bmp_info_header, sizeof ( BITMAP_P_INFO_HEADER ) );

    if (bmp_info_header->biSize != 40) {

         std::cout << "Error type of image" << std::endl;
    }

    bmp_header_size = sizeof(BITMAP_FILE_HEADER);
    bmp_info_header_size = sizeof(BITMAP_P_INFO_HEADER);

    ImgSize = sizeof(bmp_header) + bmp_info_header->biSize + ( (bmp_info_header->biBitCount/BIT_SIZE) * bmp_info_header->biWidth * bmp_info_header->biHeight );

    ImgPadding =  ((bmp_info_header->biWidth * (bmp_info_header->biBitCount / 8)) % 4); // пропускаем пустые байты, не несущие никакой информации

    rgb_array = new RGBQUAD_ARRAY* [bmp_info_header->biWidth];



    for ( int i = 0; i < bmp_info_header->biWidth ; ++i) {

       rgb_array[i] = new RGBQUAD_ARRAY[bmp_info_header->biHeight];
    }



    for ( int i = 0; i < bmp_info_header->biWidth; ++i) {

        for ( int j = 0; j < bmp_info_header->biHeight; ++j) {

            rgb_array[i][j].rgbBlue = file->get();
            rgb_array[i][j].rgbGreen = file->get();
            rgb_array[i][j].rgbRed = file->get();


            if (static_cast<int>(rgb_array[i][j].rgbBlue)  == 0 && static_cast<int>(rgb_array[i][j].rgbGreen) == 0 && static_cast<int>(rgb_array[i][j].rgbRed) == 0) {

                rgb_array[i][j].rgbReserved = '$';

            } else if (static_cast<int>(rgb_array[i][j].rgbBlue)  == 255 && static_cast<int>(rgb_array[i][j].rgbGreen) == 255 && static_cast<int>(rgb_array[i][j].rgbRed) == 255 ) {

                 rgb_array[i][j].rgbReserved = '*';
            } else {

                 rgb_array[i][j].rgbReserved = '%';
            }

            file->seekg(ImgPadding, std::ios_base::cur);

        }



    }


    std::cout<< "\nCREATE DONE" << std::endl;
    std::cout <<"........................................................................\n" << std::endl;

    file->close();
}



void Image::DrawCharArray(struct RGBQUAD_ARRAY** rgb_array) {

       std::cout << "IMAGE : \n" << std::endl;

    for (unsigned int i = bmp_info_header->biHeight -1 ; i > 0 ; --i) {

           for (unsigned int j = 0; j < bmp_info_header->biWidth; j++) {

               std::cout << rgb_array[i][j].rgbReserved;
           }
             std::cout << std::endl;
       }



    std::cout<< "\nDRAW DONE" << std::endl;
    std::cout <<"........................................................................\n" << std::endl;
}


void Image::DrawBMPHeader(BITMAP_FILE_HEADER* bmp_header ) {

    std::cout << "STRUCT BITMAP_FILE_HEADER : \n" << std::endl;

    std::cout << "bfType = " << bmp_header->bfType << std::endl;
    std::cout << "bfSize = " << bmp_header->bfSize << std::endl;
    std::cout << "bfReserved1 = " << bmp_header->bfReserved1 << std::endl;
    std::cout << "bfReserved2 = " << bmp_header->bfReserved2 << std::endl;
    std::cout << "bfOffBits = " << bmp_header->bfOffBits << std::endl;

    std::cout <<"........................................................................\n" << std::endl;
}


void Image::DrawBMPInfoHeader(BITMAP_P_INFO_HEADER* bmp_info_header) {

     std::cout << "STRUCT BITMAP_P_INFO_HEADER : \n" << std::endl;

     std::cout << "biSize = " << bmp_info_header->biSize << std::endl;
     std::cout << "biWidth = " << bmp_info_header->biWidth << std::endl;
     std::cout << "biHeight = " << bmp_info_header->biHeight << std::endl;

     std::cout << "biPlanes = " << bmp_info_header->biPlanes << std::endl;
     std::cout << "biBitCount = " << bmp_info_header->biBitCount << std::endl;
     std::cout << "biCompression = " << bmp_info_header->biCompression << std::endl;
     std::cout << "biSizeImage = " << bmp_info_header->biSizeImage << std::endl;
     std::cout << "biXPelsPerMeter = " << bmp_info_header->biXPelsPerMeter << std::endl;
     std::cout << "biYPelsPerMeter = " << bmp_info_header->biYPelsPerMeter << std::endl;
     std::cout << "biClrUsed = " << bmp_info_header->biClrUsed << std::endl;
     std::cout << "biClrImportant = " << bmp_info_header->biClrImportant << std::endl;

    std::cout <<"........................................................................\n" << std::endl;


}

void Image::DrawAnotherAttributes() {

     std::cout << "ANOTHER ATTRIBUTES : \n" << std::endl;


    std::cout << "BMP_HEADER_SIZE = " <<bmp_header_size << std::endl;

    std::cout << "BMP_INFO_HEADER_SIZE = " <<bmp_info_header_size << std::endl;

    std::cout << "imgPadding = " <<ImgPadding << std::endl;

    std::cout << "ImgSize = " <<ImgSize << std::endl;

    std::cout <<"........................................................................\n" << std::endl;
}

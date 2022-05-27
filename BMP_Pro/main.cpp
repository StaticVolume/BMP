#pragma once
#include <iostream>
#include "image.h"
#include <string>
#include <ncurses.h>

int main(int argc, char* argv[]) {

 Image* img = nullptr;
 std::string filepath;

        if( argc > 1 ) {

            std::cout << "We use the file : " << argv[1] << std::endl;
            filepath = argv[1];

        } else {

            std::cout << "Filepath is empty, we start with standart filepath \"img.bmp\" " << std::endl;
            filepath = "img.bmp";

        }


  img = new Image();
  img->CreateImage(filepath);
  img->DrawAnotherAttributes();
  img->DrawBMPHeader(img->GetBMPHeader());
  img->DrawBMPInfoHeader(img->GetBMPInfoHeader());
  img->DrawCharArray(img->GetRGBArray());

  delete img;

}




#include <iostream>
#include <string>
#include <vector>

import Display;


int main(int argc, char* argv[])
{
    if ( argc != 2 )
    {
        printf("usage:  DisplayImage.out <Image_Path>\n");
        return -1;
    }

    std::string current_exec_name = argv[0]; // Name of the current exec program
    std::string imagePath;

    if (argc > 1) {
        imagePath = argv[1];
        Display d;
        d.display(imagePath);
    }
    return 0;
}

//Bu maini wrap et Display image die sonra onu export module yap
//Burada onu import edelim, daha simdiden kodu bolelm dependency sadece o module de kalsin
//CLI yapabilirm, GUI ile ugrasilmaz
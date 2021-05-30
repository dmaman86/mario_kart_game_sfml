#include <iostream>
#include <cstdlib>
#include <exception>

#include "MarioKart.h"

int main()
{
    try{
        MarioKart().run();
    }catch( std::exception & e){
        std::cout << e.what();
    }

    return( EXIT_SUCCESS );
}

#include <iostream>

#include "AffichageSDL2.h"

using namespace std;

int main(int argc, char **argv)
{
    srand(time(NULL));
    AffichageSDL as;
    as.sdlBouclemenu();
    return 0;
}
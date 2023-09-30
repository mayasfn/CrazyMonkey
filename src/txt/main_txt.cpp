
#include "AffichageTxt.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    termClear();

    //mise en place de la jungle
    Vec2 pos = make_vec2(5,15);
    Singe sin(3, pos, 1, 10, 9.81, 0);
    Vec2 curs = make_vec2(sin.getpos().x + 5, sin.getpos().y);

    Arbre * a = new Arbre[5]();
    a[0].setCentre(make_vec2(sin.getpos().x + 5, 10));
    a[1].setCentre(make_vec2(a[0].getCentre().x + 7, a[0].getCentre().y));
    a[2].setCentre(make_vec2(a[0].getCentre().x, a[0].getCentre().y + 10));
    a[3].setCentre(make_vec2(a[2].getCentre().x + 6, a[2].getCentre().y));
    a[4].setCentre(make_vec2(22, sin.getpos().y + 2));
    a[4].set_coffretbananes(true);
    for (unsigned int i = 0; i<5; i++) {
        a[i].set_rayon(0);
    }
    
    Jungle ji(35, 40,a, 5, 1, sin, 0, curs, false, false, -1);
    AffichageTxt AF;
    AF.txtBoucle(ji);
    termClear();
    return 0;
}
#include <iostream>
#include <assert.h>
#include "Arbre.h"

using namespace std;

Arbre::Arbre()
{
    banane_magique = false;
    coffret_bananes = false;
    serpent = false;
    centre = make_vec2(200, 500);
    rayon = 100;
}

Arbre::Arbre(bool m, bool c, bool s, Vec2 cen, int r)
{
    assert(r >= 0);
    assert(cen.x >= 0 && cen.y >= 0);
    banane_magique = m;
    coffret_bananes = c;
    serpent = s;
    centre = cen;
    rayon = r;
}

bool Arbre::getBanane_magique() const
{
    return banane_magique;
}

bool Arbre::getCoffret_bananes() const
{
    return coffret_bananes;
}

bool Arbre::getSerpent() const
{
    return serpent;
}

Vec2 Arbre::getCentre() const
{
    return centre;
}

int Arbre::getRayon() const
{
    return rayon;
}

void Arbre::setCentre(Vec2 v)
{
    assert(v.x >= 0 && v.y >= 0);
    centre = make_vec2(v.x, v.y);
}

void Arbre::set_serpent(bool se)
{
    serpent = se;
}

void Arbre::set_rayon(int r)
{
    rayon = r;
}

void Arbre::set_coffretbananes(bool ba)
{
    coffret_bananes = ba;
}

void Arbre::set_banane_mag(bool ba)
{
    banane_magique = ba;
}
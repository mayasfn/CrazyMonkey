#include <iostream>
#include "Singe.h"
#include <math.h>
#include <assert.h>

using namespace std;

Singe::Singe()
{
    nb_vie_init = 3;
    nb_vie = nb_vie_init;
    pos_init.x = 100;
    pos_init.y = 500;
    position = pos_init;
    v0 = 50;
    rayon = 55;
    g = 9.81;
    pos_point = 0;
}

Singe::Singe(unsigned int viesInit, Vec2 p, double r, double v, double gr, int po)
{
    assert(viesInit > 0);
    assert(p.x >= 0 && p.y >= 0);
    assert(r > 0);
    assert(v > 0);
    assert(gr > 0);
    assert(po >= 0);
    nb_vie = viesInit;
    nb_vie_init = viesInit;
    pos_init = p;
    position = pos_init;
    rayon = r;
    v0 = v;
    g = gr;
    pos_point = po;
}

unsigned int Singe::get_nb_vie() const
{
    return nb_vie;
}

Vec2 Singe::getpos() const
{
    return position;
}

double Singe::get_v0() const
{
    return v0;
}

unsigned int Singe::get_nb_vie_init() const
{
    return nb_vie_init;
}

Vec2 Singe::getpos_init() const
{
    return pos_init;
}

int Singe::getpos_point() const
{
    return pos_point;
}

double Singe::getG() const
{
    return g;
}
double Singe::getrayon() const
{
    return rayon;
}

void Singe::set_nb_vie(unsigned int nb)
{
    assert(nb >= 0);
    nb_vie = nb;
}

void Singe::set_nb_vie_init(unsigned int nb)
{
    assert(nb > 0);
    nb_vie_init = nb;
}

void Singe::set_g(double p)
{
    assert(p > 0);
    g = p;
}

void Singe::set_pos(const Vec2 &v)
{
    assert(v.x >= 0 && v.y >= 0);
    position = v;
}

void Singe::set_pos_init(const Vec2 &ve)
{
    assert(ve.x >= 0 && ve.y >= 0);
    pos_init = ve;
}

void Singe::setrayon(double r)
{
    assert(r > 0);
    rayon = r;
}

void Singe::set_v0(double v)
{
    assert(v > 0);
    v0 = v;
}

void Singe::set_pos_point(int p)
{
    assert(p > 0);
    pos_point = p;
}

Vec2 Singe::calcule_pos(double angle, double t)
{
    Vec2 p;
    p.x = v0 * cos(angle) * t + pos_init.x;
    p.y = (0.5 * g * t * t - v0 * sin(angle) * t + pos_init.y);
    return p;
}

double Singe::calculeAlpha(const Vec2 &pos_curseur) const
{
    assert(pos_curseur.x >= 0 && pos_curseur.y >= 0);
    double alpha;
    alpha = -atan((pos_curseur.y - pos_init.y) / (pos_curseur.x - pos_init.x));
    return alpha;
}

void Singe::calculeVitesse(Vec2 point, Vec2 debut, Vec2 fin)
{
    assert(point.x >= 0 && point.y >= 0);
    assert(debut.x > 0 && debut.y > 0);
    assert(fin.x > 0 && fin.y > 0);
    double distanceTotale = sqrt(pow(fin.x - debut.x, 2) + pow(fin.y - debut.y, 2));
    double vitesseMin = 15.0f;
    double vitesseMax = 100.0f;
    double distancePoint = sqrt(pow(point.x - debut.x, 2) + pow(point.y - debut.y, 2));
    double pourcentagePoint = distancePoint / distanceTotale;
    double vitesse = (1 - pourcentagePoint) * vitesseMin + pourcentagePoint * vitesseMax;
    v0 = vitesse;
}

void Singe::changer_pos_point(int x, int w)
{
    assert(x > 0);
    assert(w > 0);
    if (pos_point > x + w)
    {
        pos_point = x;
    }
    else
        pos_point = pos_point + 2;
}
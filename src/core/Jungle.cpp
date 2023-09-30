#include <iostream>
#include "Jungle.h"
#include <assert.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // WIN32

using namespace std;

Jungle::Jungle()
{
   Singe singe;
   dimx = 1800;
   dimy = 850;
   s = singe;
   tab_arbre = new Arbre[1]();
   nb_arbre = 1;
   arbre_prec = -1;
   etat = 0;
   temps_partie = 50;
   curseur = make_vec2(s.getpos().x + 5, s.getpos().y);
   collision_sol = false;
   coffret = false;
}

Jungle::Jungle(unsigned int x, unsigned int y, Arbre *a, unsigned int nba, int temps, const Singe &sin, int e, Vec2 curs, bool sol, bool cof, int prec)
{
   assert(x > 0 && y > 0);
   assert(nba > 0);
   assert(temps > 0);
   assert(sin.position.x < x);
   assert(sin.position.y < y);
   assert(curs.x < x && curs.x >= 0);
   assert(curs.y < y && curs.y >= 0);
   dimx = x;
   dimy = y;
   tab_arbre = a;
   nb_arbre = nba;
   temps_partie = temps;
   s = sin;
   etat = e;
   curseur = curs;
   collision_sol = sol;
   coffret = cof;
   arbre_prec = prec;
}

Jungle::~Jungle()
{

   if (tab_arbre != nullptr)
   {
      delete[] tab_arbre;
      tab_arbre = nullptr;
   }
}

void Jungle::jungle_niveau1()
{
   tab_arbre = new Arbre[5]();
   nb_arbre = 5;
   tab_arbre[0].setCentre(make_vec2(s.getpos().x + 350, s.getpos().y + 200));
   tab_arbre[1].setCentre(make_vec2(tab_arbre[0].getCentre().x + 350, s.getpos().y - 200));
   tab_arbre[2].setCentre(make_vec2(tab_arbre[1].getCentre().x + 250, tab_arbre[0].getCentre().y));
   tab_arbre[3].setCentre(make_vec2(tab_arbre[2].getCentre().x + 250, tab_arbre[1].getCentre().y - 50));
   tab_arbre[4].setCentre(make_vec2(s.getpos().x + 1500, s.getpos().y));
   tab_arbre[4].set_coffretbananes(true);
   temps_partie = 40;
}

void Jungle::jungle_niveau2()
{
   tab_arbre = new Arbre[7]();
   nb_arbre = 7;
   tab_arbre[0].setCentre(make_vec2(s.getpos().x + 300, s.getpos().y + 200));
   tab_arbre[1].setCentre(make_vec2(tab_arbre[0].getCentre().x + 350, s.getpos().y - 200));
   tab_arbre[2].setCentre(make_vec2(tab_arbre[1].getCentre().x + 50, tab_arbre[0].getCentre().y));
   tab_arbre[3].setCentre(make_vec2(tab_arbre[2].getCentre().x + 350, tab_arbre[1].getCentre().y - 50));
   tab_arbre[4].setCentre(make_vec2(tab_arbre[3].getCentre().x + 50, tab_arbre[0].getCentre().y));
   tab_arbre[5].setCentre(make_vec2(tab_arbre[0].getCentre().x, tab_arbre[3].getCentre().y - 20)); // celle en haut à gauche
   tab_arbre[6].setCentre(make_vec2(s.getpos().x + 1500, s.getpos().y));
   tab_arbre[6].set_coffretbananes(true);
   int numserpent = rand() % 6;

   tab_arbre[numserpent].set_serpent(true);
   int numbanane;
   do
   {
      numbanane = rand() % 6;
   } while (numbanane == numserpent);
   tab_arbre[numbanane].set_banane_mag(true);
   temps_partie = 50;
}

void Jungle::jungle_niveau3()
{
   s.setrayon(35);
   tab_arbre = new Arbre[10]();
   nb_arbre = 10;
   for (unsigned int i = 0; i < nb_arbre; i++)
   {
      tab_arbre[i].set_rayon(75);
   }
   tab_arbre[0].setCentre(make_vec2(350, 300));
   tab_arbre[1].setCentre(make_vec2(tab_arbre[0].getCentre().x + 250, tab_arbre[0].getCentre().y - 20));
   tab_arbre[2].setCentre(make_vec2(tab_arbre[1].getCentre().x + 250, tab_arbre[1].getCentre().y + 80));
   tab_arbre[3].setCentre(make_vec2(tab_arbre[2].getCentre().x + 300, tab_arbre[1].getCentre().y - 50));
   tab_arbre[4].setCentre(make_vec2(tab_arbre[3].getCentre().x + 175, tab_arbre[0].getCentre().y - 45));
   tab_arbre[5].setCentre(make_vec2(tab_arbre[0].getCentre().x, 750));
   tab_arbre[6].setCentre(make_vec2(tab_arbre[5].getCentre().x + 225, tab_arbre[5].getCentre().y - 20)); // celle en haut à gauche
   tab_arbre[7].setCentre(make_vec2(tab_arbre[6].getCentre().x + 265, tab_arbre[6].getCentre().y - 75)); // celle en haut à gauche
   tab_arbre[8].setCentre(make_vec2(tab_arbre[7].getCentre().x + 320, tab_arbre[7].getCentre().y + 45)); // celle en haut à gauche

   tab_arbre[9].setCentre(make_vec2(s.getpos().x + 1500, s.getpos().y));
   tab_arbre[9].set_coffretbananes(true);

   int numserpent = rand() % 9;
   tab_arbre[numserpent].set_serpent(true);
   int numserpent2;
   do
   {
      numserpent2 = rand() % 9;
   } while (numserpent == numserpent2);
   tab_arbre[numserpent2].set_serpent(true);
   int numbanane;
   do
   {
      numbanane = rand() % 9;
   } while ((numbanane == numserpent) && (numbanane == numserpent2));
   tab_arbre[numbanane].set_banane_mag(true);
   temps_partie = 40;
}

unsigned int Jungle::get_dimx() const
{
   return dimx;
}

unsigned int Jungle::get_dimy() const
{
   return dimy;
}

Arbre Jungle::getTab_arbre(unsigned int indice) const
{
   assert(indice >= 0);
   return tab_arbre[indice];
}

Singe Jungle::get_singe() const
{
   return s;
}

int Jungle::get_etat() const
{
   return etat;
}

Vec2 Jungle::get_curseur() const
{
   return curseur;
}

unsigned int Jungle::get_nb_arbre() const
{
   return nb_arbre;
}

void Jungle::set_singe(const Singe &sin)
{
   assert(sin.position.x >= 0 && sin.position.x < dimx);
   assert(sin.position.y >= 0 && sin.position.y < dimy);
   s = sin;
}

void Jungle::set_dimx(unsigned int x)
{
   assert(dimx > 0);
   dimx = x;
}

void Jungle::set_dimy(unsigned int y)
{
   assert(dimy > 0);
   dimy = y;
}

void Jungle::set_nb_arbre(unsigned int nb)
{
   assert(nb > 0);
   nb_arbre = nb;
}

void Jungle::set_etat(int e)
{
   etat = e;
}

void Jungle::set_curseur(Vec2 c)
{
   assert(c.x >= 0 && c.x < dimx);
   assert(c.y >= 0 && c.y < dimy);
   curseur = c;
}

void Jungle::testRegression()
{
   // test constructeur par défaut
   Jungle ju_test;
   assert(ju_test.dimx == 1800);
   assert(ju_test.dimy == 850);
   assert(ju_test.temps_partie == 50);
   assert(ju_test.etat == 0);
   assert(ju_test.collision_sol == false);
   assert(ju_test.coffret == false);
   assert(ju_test.get_singe().getpos().x <= ju_test.dimx && ju_test.get_singe().getpos().x >= 0);
   assert(ju_test.get_singe().getpos().y <= ju_test.dimy && ju_test.get_singe().getpos().y >= 0);
   for (unsigned int i = 0; i < 7; i++)
   {
      assert(ju_test.tab_arbre[i].getCentre().x <= ju_test.dimx && ju_test.tab_arbre[i].getCentre().x >= 0);
      assert(ju_test.tab_arbre[i].getCentre().y <= ju_test.dimy && ju_test.tab_arbre[i].getCentre().y >= 0);
   }
   assert(ju_test.curseur.x <= ju_test.dimx && ju_test.curseur.x >= 0);
   assert(ju_test.curseur.y <= ju_test.dimy && ju_test.curseur.y >= 0);

   // test le constructeur par copie
   Arbre *arb = new Arbre[6];
   Arbre ab;
   for (unsigned int j = 0; j < 6; j++)
   {
      arb[j] = ab;
   }
   Singe S;
   int et = 0;
   Vec2 c = make_vec2(55, 32);
   bool so = false;
   bool co = false;
   Jungle ju_test2(1500, 900, arb, 6, 80, S, et, c, so, co, -1);
   assert(ju_test2.dimx == 1500);
   assert(ju_test2.dimy == 900);
   assert(ju_test2.temps_partie == 80);
   assert(ju_test2.etat == 0);
   assert(ju_test2.collision_sol == false);
   assert(ju_test2.coffret == false);
   assert(ju_test2.get_singe().getpos().x <= ju_test2.dimx && ju_test2.get_singe().getpos().x >= 0);
   assert(ju_test2.get_singe().getpos().y <= ju_test2.dimy && ju_test2.get_singe().getpos().y >= 0);
   assert(ju_test2.curseur.x <= ju_test2.dimx && ju_test2.curseur.x >= 0);
   assert(ju_test2.curseur.y <= ju_test2.dimy && ju_test2.curseur.y >= 0);
   assert(ju_test2.arbre_prec == -1);
   for (unsigned int i = 0; i < 6; i++)
   {
      assert(ju_test2.tab_arbre[i].getCentre().x == ab.getCentre().x && ju_test2.tab_arbre[i].getCentre().y == ab.getCentre().y);
      assert(ju_test2.tab_arbre[i].getCentre().x == 200);
   }

   // teste des accesseurs: get
   assert(ju_test2.get_dimx() == ju_test2.dimx);
   assert(ju_test2.get_dimy() == ju_test2.dimy);
   assert(ju_test2.getTab_arbre(2).getCentre().x == ju_test2.tab_arbre[2].getCentre().x && ju_test2.getTab_arbre(2).getCentre().y == ju_test2.tab_arbre[2].getCentre().y);
   assert(ju_test2.get_singe().getpos().x == S.getpos().x && ju_test2.get_singe().getpos().y == S.getpos().y);
   assert(ju_test2.get_etat() == et);
   assert(ju_test2.get_curseur().x == c.x && ju_test2.get_curseur().y == c.y);
   assert(ju_test2.get_nb_arbre() == 6);
   assert(ju_test2.s.getpos_point() == 0);
   // test des mutateurs set
   ju_test2.set_dimx(1600);
   assert(ju_test2.get_dimx() == 1600);
   ju_test2.set_dimy(700);
   assert(ju_test2.get_dimy() == 700);
   ju_test2.set_nb_arbre(8);
   assert(ju_test2.get_nb_arbre() == 8);
   ju_test2.set_etat(1);
   assert(ju_test2.get_etat() == 1);
   Vec2 V = make_vec2(50, 30);
   ju_test2.set_curseur(V);
   assert(ju_test2.get_curseur().x == V.x && ju_test2.get_curseur().y == V.y);
   Vec2 ve = make_vec2(50, 690);
   Singe Sing(5, ve, 20, 10, 9.5, 0);
   ju_test2.set_singe(Sing);
   assert(ju_test2.get_singe().getpos().x == Sing.getpos().x && ju_test2.get_singe().getpos().y == Sing.getpos().y);
   int pointTest = 5;
   ju_test2.s.set_pos_point(pointTest);
   assert(ju_test2.s.getpos_point() == pointTest);

   // test de la fonction collisionsol
   assert(ju_test.collisionsol() == false);
   assert(ju_test2.collisionsol() == true);

   // test de la fonction collisionarbre
   Vec2 vec = make_vec2(150, 480);
   Singe Si(5, vec, 20, 10, 9.5, 0);
   ju_test2.set_singe(Si);
   assert(ju_test2.collisionarbre() != -1);
}

bool Jungle::collisionsol()
{

   if (distance(s.getpos(), make_vec2(s.getpos().x, dimy)) <= s.getrayon())
   {

      cout << "collision détéctée avec le sol" << endl;
      collision_sol = true;
      etat = 0;
      return true;
   }
   return false;
}

int Jungle::collisionarbre()
{

   for (int i = 0; i < (int)nb_arbre; i++)
   {
      if (i != arbre_prec && s.getpos().y + s.getrayon() <= tab_arbre[i].getCentre().y && distance(s.getpos(), tab_arbre[i].getCentre()) <= (s.getrayon() + tab_arbre[i].getRayon()))
      {
         etat = 0;
         cout << "collision détectée avec l'arbre " << i << endl;

#ifdef _WIN32
         Sleep(100);
#else
         usleep(10000);
#endif // WIN32
         s.set_pos(make_vec2(tab_arbre[i].getCentre().x, tab_arbre[i].getCentre().y - (tab_arbre[i].getRayon() + s.getrayon())));
         s.set_pos_init(s.getpos());

         if (tab_arbre[i].getCoffret_bananes())
         {
            coffret = true;
            cout << "gagné!" << endl;
         }
         if (tab_arbre[i].getSerpent())
         {
            s.set_nb_vie(s.get_nb_vie() - 1);
         }
         if (tab_arbre[i].getBanane_magique())
         {
            temps_partie += 5;
         }
         return i;
      }
   }
   return -1;
}

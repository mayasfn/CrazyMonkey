#ifndef _JUNGLE_H
#define _JUNGLE_H
#include "Arbre.h"
#include "Singe.h"


/**
 * @brief Classe qui représente une jungle avec ses composantes.
 *
 */
class Jungle
{
private:
    unsigned int dimx, dimy;
    Arbre *tab_arbre;
    unsigned int nb_arbre;
    // unsigned int nb_serpent;
    int temps_partie; // en seconde
    Singe s;
    int etat; // si = 0 alors au joueur de choisir l'angle, si = 1 alors le singe bouge
    Vec2 curseur;
    bool collision_sol;
    bool coffret;
    int arbre_prec;
    friend class AffichageSDL;
    friend class AffichageTxt;

public:
    /**
     * @brief Constructeur par défaut de la classe jungle
     *
     */
    Jungle();

    /**
     * @brief Constructeur par copie
     *
     * @param[in] x
     * @param[in] y
     * @param[in] a
     * @param[in] nba
     * @param[in] temps
     * @param[in] sin
     * @param[in] e
     * @param[in] curs
     * @param[in] sol
     * @param[in] cof
     * @param[in] prec
     */
    Jungle(unsigned int x, unsigned int y, Arbre *a, unsigned int nba, int temps, const Singe &sin, int e, Vec2 curs, bool sol, bool cof, int prec);

    /**
     * @brief Destructeur
     *
     */
    ~Jungle();

    /**
     * @brief Met en place la jungle par rapport au niveau 1
     *
     */
    void jungle_niveau1();

    /**
     * @brief Met en place la jungle par rapport au niveau 2
     *
     */
    void jungle_niveau2();

    /**
     * @brief Met en place la jungle par rapport au niveau 3
     *
     */
    void jungle_niveau3();

    /**
     * @brief Accesseur de la dimension x de la fenêtre
     *
     * @return unsigned int
     */
    unsigned int get_dimx() const;

    /**
     * @brief Accesseur de la dimension y de la fenêtre
     *
     * @return unsigned int
     */
    unsigned int get_dimy() const;

    /**
     * @brief Accesseur du pointeur vers le tableau d'arbre
     *
     * @return Arbre*
     */
    Arbre getTab_arbre(unsigned int indice) const;

    /**
     * @brief Accesseur du singe
     *
     * @return Singe
     */
    Singe get_singe() const;

    /**
     * @brief Accesseur de l'état
     *
     * @return int
     */
    int get_etat() const;

    /**
     * @brief Accesseur du nombre d'arbre
     *
     * @return nb_arbre
     */
    unsigned int get_nb_arbre() const;

    /**
     * @brief Accesseur du curseur
     *
     * @return Vec2
     */
    Vec2 get_curseur() const;

    /**
     * @brief Mutateur du nombre d'arbre
     *
     * @param[in] nb
     */
    void set_nb_arbre(unsigned int nb);

    /**
     * @brief Mutateur de la dimension x de la jungle
     *
     * @param[in] x
     */
    void set_dimx(unsigned int x);

    /**
     * @brief Mutateur de la dimension y de la jungle
     *
     * @param[in] y
     */
    void set_dimy(unsigned int y);

    /**
     * @brief Mutateur du singe
     *
     * @param[in] sin
     */
    void set_singe(const Singe &sin);

    /**
     * @brief Mutateur de l'état
     *
     * @param[in] e
     */
    void set_etat(int e);

    /**
     * @brief Mutateur du curseur
     *
     * @param[in] c
     */
    void set_curseur(Vec2 c);

    /**
     * @brief Vérifie si y a collision avec le sol
     *
     * @return true
     * @return false
     */
    bool collisionsol();

    /**
     * @brief Vérifie si y a collision avec un arbre
     *
     * @return true
     * @return false
     */
    int collisionarbre();

    /**
     * @brief fonction qui vérifie si les autres fonctions de la classe fonctionnent.
     *
     */
    void testRegression();
};

#endif

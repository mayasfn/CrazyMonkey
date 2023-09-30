#ifndef _AFFICHAGETXT_H
#define _AFFICHAGETXT_H
#include "../core/Jungle.h"
#include "winTxt.h"

/**
 * @brief Classe qui gère une version minimale du jeu
 * 
 */
class AffichageTxt
{
private:
  WinTXT win;

public:
  /**
   * @brief Constructeur par défaut de la classe AffichageTxt.
   *
   */
  AffichageTxt();

  /**
   * @brief Affiche les éléments de la fenétre
   *
   * @param[in] j
   */
  void txtAff(const Jungle &j);

  /**
   * @brief affiche seulement l singe avce la nouvelle position.
   *
   * @param[in] j
   */
  void txtAff2(const Jungle &j);

  /**
   * @brief calcule si il ya  collision du singe avec les autres elements de la fenetre.
   *
   * @param[in] j
   * @param[in] angle
   * @param[in] t
   */
  void collisiontxt(Jungle &j, double angle, double t);

  /**
   * @brief Affichage en mode txt
   *
   * @param[in] j
   */
  void txtBoucle(Jungle &j);
};

#endif
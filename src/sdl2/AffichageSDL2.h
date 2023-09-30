#ifndef _AFFICHAGESDL2_H
#define _AFFICHAGESDL2_H

#include </usr/include/SDL2/SDL.h>
#include </usr/include/SDL2/SDL_image.h>
#include </usr/include/SDL2/SDL_ttf.h>
#include </usr/include/SDL2/SDL_mixer.h>

#include "../core/Jungle.h"

//! @brief Pour gérer une image avec SDL2
class Image
{

private:
   SDL_Surface *m_surface;
   SDL_Texture *m_texture;
   bool m_a_change;

public:
   /**
    * @brief constructeur par defaut de la classe image
    *
    */
   Image();
   /**
    * @brief Destructeur d ela classe image
    *
    */
   ~Image();

   /**
    * @brief télécharge un fichier
    *
    * @param[in] filename
    * @param[in] renderer
    */
   void telecharger_fichier(const char *filename, SDL_Renderer *renderer);

   /**
    * @brief télécharger à partir d'une surface
    *
    * @param[in] renderer
    */
   void telecharger_apartir_surface_courante(SDL_Renderer *renderer);

   /**
    * @brief dessiner la fenetre
    *
    * @param[in] renderer
    * @param[in] x
    * @param[in] y
    * @param[in] w
    * @param[in] h
    */
   void dessiner(SDL_Renderer *renderer, int x, int y, int w, int h);
   /**
    * @brief accesseur de la donnée membre texture
    *
    * @return SDL_Texture*
    */
   SDL_Texture *getTexture() const;

   SDL_Surface *getSurface() const;

   /**
    * @brief mutateur de la donnée membre surface
    *
    * @param surf
    */
   void setSurface(SDL_Surface *surf);
};

/**
   @brief classe gerant le jeu avec un affichage SDL
*/
class AffichageSDL
{

private:
   Jungle jungle;

   // Fenêtre du jeu niveau 2
   SDL_Window *fenetre;
   SDL_Renderer *renderer;

   // Fenêtre page menu
   SDL_Window *menu;
   SDL_Renderer *menu_renderer;

   // Fenêtre règles du jeu
   SDL_Window *regles;
   SDL_Renderer *regles_renderer;

   // Police de tous les textes:
   TTF_Font *police;
   SDL_Color police_couleur;

   // Pour le choix de la vitesse
   SDL_Rect box_rect;
   SDL_Color couleur_vitesse;

   // Pour le chronomètre
   SDL_TimerID chrono_id;
   SDL_Color chrono_couleur;

   // Son pour toutes les fenêtres
   Mix_Chunk *son;
   bool avec_son;

   // Pour le menu:

   // Contient du texte:
   Image im_menu;
   Image im_niveau1;
   Image im_niveau2;
   Image im_niveau3;
   Image im_policem;
   Image im_regle;
   Image im_arbre2;

   // Pour les règles du jeu :
   //  Police pour l'explication:
   TTF_Font *police2;

   // Contient du texte:
   Image im_intro;
   Image im_intro2;
   Image im_regle1;
   Image im_regle2;
   Image im_regle3;
   Image im_regle4;
   Image im_conclu;
   Image im_jouer1;
   Image im_jouer2;
   Image im_jouer3;

   // Pour le jeu:

   // Contient du texte:
   Image im_perdu;
   Image im_gagne;
   Image im_police;
   Image im_chrono;
   Image im_vie;

   // Contient des images :
   Image im_singe;
   Image im_arbre;
   Image im_serpent;
   Image im_banane_mag;
   Image im_coffret_banane;

   bool nouveau_saut;
   bool disparait;

public:
   /**
    * @brief Constructeur par défaut de la classe SDLSimple
    *
    */
   AffichageSDL();

   /**
    * @brief Destructeur de la classe SDLSimple
    *
    */
   ~AffichageSDL();

   /**
    * @brief Initalize la fenêtre du niveau 2
    *
    */
   void initjeu();

   /**
    * @brief Initalize la fenêtre des règles
    *
    */
   void initRegles();

   /**
    * @brief Initalize la fenêtre du menu
    *
    */
   void initMenu();

   /**
    * @brief affiche les objets de la fenetre du jeu
    *
    */
   void sdlAff();

   /**
    * @brief affiche les objets de la fenêtre du menu
    *
    */
   void sdlAffmenu();

   /**
    * @brief affiche les objets de la fenêtre du règles
    *
    */
   void sdlAffRegles();

   /**
    * @brief prend en considèration l'interaction de l'utilisateur avec l'interface
    *
    */
   void sdlBouclemenu();

   /**
    * @brief prend en considèration l'interaction de l'utilisateur avec l'interface
    *
    */
   void sdlBoucleregles();

   /**
    * @brief prend en considèration l'interaction de l'utilisateur avec l'interface
    *
    */
   void sdlBouclejeu();
};

/**
 * @brief Fonction qui décrémenter un pointeur entier à chaque fois qu'elle est appelée, c'est pour le chronomètre
 *
 * @param interval
 * @param param
 * @return Uint32
 */
Uint32 chrono_callback(Uint32 interval, void *param);

#endif

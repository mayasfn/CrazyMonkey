#include <iostream>
#include <cassert>
#include <time.h>
#include <stdlib.h>
#include "AffichageSDL2.h"

using namespace std;

float temps()
{
    return float(SDL_GetTicks()) / CLOCKS_PER_SEC; // conversion des ms en secondes en divisant par 1000
}

// ============= CLASS IMAGE =============== //

Image::Image() : m_surface(nullptr), m_texture(nullptr), m_a_change(false)
{
}

Image::~Image()
{
    SDL_FreeSurface(m_surface);
    SDL_DestroyTexture(m_texture);

    m_surface = nullptr;
    m_texture = nullptr;
    m_a_change = false;
}

void Image::telecharger_fichier(const char *filename, SDL_Renderer *renderer)
{
    m_surface = IMG_Load(filename);
    if (m_surface == nullptr)
    {
        string nfn = string("../") + filename;
        cout << "Error: cannot load " << filename << ". Trying " << nfn << endl;
        m_surface = IMG_Load(nfn.c_str());
        if (m_surface == nullptr)
        {
            nfn = string("../") + nfn;
            m_surface = IMG_Load(nfn.c_str());
        }
    }
    if (m_surface == nullptr)
    {
        cout << "Error: cannot load " << filename << endl;
        SDL_Quit();
        exit(1);
    }

    SDL_Surface *surfaceCorrectPixelFormat = SDL_ConvertSurfaceFormat(m_surface, SDL_PIXELFORMAT_ARGB8888, 0);
    SDL_FreeSurface(m_surface);
    m_surface = surfaceCorrectPixelFormat;

    m_texture = SDL_CreateTextureFromSurface(renderer, surfaceCorrectPixelFormat);
    if (m_texture == NULL)
    {
        cout << "Error: problem to create the texture of " << filename << endl;
        SDL_Quit();
        exit(1);
    }
}

void Image::telecharger_apartir_surface_courante(SDL_Renderer *renderer)
{
    m_texture = SDL_CreateTextureFromSurface(renderer, m_surface);
    if (m_texture == nullptr)
    {
        cout << "erreur:probleme de création de la texture à partir de la surface " << endl;
        SDL_Quit();
        exit(1);
    }
}

void Image::dessiner(SDL_Renderer *renderer, int x, int y, int w, int h)
{
    int ok;
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = w;
    r.h = (h < 0) ? m_surface->h : h;

    if (m_a_change)
    {
        ok = SDL_UpdateTexture(m_texture, nullptr, m_surface->pixels, m_surface->pitch);
        assert(ok == 0);
        m_a_change = false;
    }

    ok = SDL_RenderCopy(renderer, m_texture, nullptr, &r);
    assert(ok == 0);
}

SDL_Texture *Image::getTexture() const { return m_texture; }

SDL_Surface *Image::getSurface() const { return m_surface; }

void Image::setSurface(SDL_Surface *surf) { m_surface = surf; }

// ============= CLASS SDLJEU =============== //

AffichageSDL::AffichageSDL()
{

    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    if (TTF_Init() != 0)
    {
        cout << "Erreur lors de l'initialisation de la SDL_ttf : " << TTF_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
        cout << "No sound !!!" << endl;
        SDL_Quit();
        exit(1);
        avec_son = false;
    }
    else
        avec_son = true;

    // FONTS
    police = TTF_OpenFont("data/fonts/Samson.ttf", 50);
    if (police == nullptr)
        police = TTF_OpenFont("../data/fonts/Samson.ttf", 50);
    if (police == nullptr)
    {
        cout << "Failed to load Samson.ttf! SDL_TTF Error: " << TTF_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    police2 = TTF_OpenFont("data/fonts/PTS55F.ttf", 50);
    if (police2 == nullptr)
        police2 = TTF_OpenFont("../data/fonts/PTS55F.ttf", 50);
    if (police2 == nullptr)
    {
        cout << "Failed to load PTS55F.ttf! SDL_TTF Error: " << TTF_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    police_couleur = {0, 0, 0};
    chrono_couleur = {0, 0, 0};

    // Initialisation fenêtre menu :
    initMenu();

    // Initialisation fenêtre des règles :
    initRegles();

    // Pour la fenêtre du jeu:
    initjeu();
    // initialisation des bool
    nouveau_saut = true;
    disparait = false;

    // SONS
    if (avec_son)
    {
        son = Mix_LoadWAV("data/sounds/ArthurVyncke-ChildhoodFriend.mp3");
        if (son == nullptr)
            son = Mix_LoadWAV("../data/sounds/ArthurVyncke-ChildhoodFriend.mp3");
        if (son == nullptr)
        {
            cout << "Failed to load son.wav! SDL_mixer Error: " << Mix_GetError() << endl;
            SDL_Quit();
            exit(1);
        }
    }
}

void AffichageSDL::initjeu()
{
    // création fenetre jeu
    fenetre = SDL_CreateWindow("Crazy Monkey", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, jungle.get_dimx(), jungle.get_dimy(), SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (fenetre == nullptr)
    {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }
    renderer = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);

    // IMAGES
    im_singe.telecharger_fichier("data/img/singe.png", renderer);
    im_arbre.telecharger_fichier("data/img/arbre.png", renderer);
    im_serpent.telecharger_fichier("data/img/serpent.png", renderer);
    im_coffret_banane.telecharger_fichier("data/img/bananes.png", renderer);
    im_banane_mag.telecharger_fichier("data/img/banane_magique.png", renderer);

    im_police.setSurface(TTF_RenderText_Solid(police, "Crazy Monkey", police_couleur));
    im_police.telecharger_apartir_surface_courante(renderer);

    // message perdu
    im_perdu.setSurface(TTF_RenderText_Solid(police, "PERDU!", police_couleur));
    im_perdu.telecharger_apartir_surface_courante(renderer);

    // message gagné
    im_gagne.setSurface(TTF_RenderText_Solid(police, "GAGNE!", police_couleur));
    im_gagne.telecharger_apartir_surface_courante(renderer);
}

void AffichageSDL::initMenu()
{
    // Creation de la fenetre du menu
    menu = SDL_CreateWindow("Crazy Monkey", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, jungle.get_dimx(), jungle.get_dimy(), SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (menu == nullptr)
    {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }
    menu_renderer = SDL_CreateRenderer(menu, -1, SDL_RENDERER_ACCELERATED);

    // Pour le texte:

    // bouton niveau 1
    im_niveau1.setSurface(TTF_RenderText_Solid(police, "Niveau 1", police_couleur));
    im_niveau1.telecharger_apartir_surface_courante(menu_renderer);

    // bouton niveau 2
    im_niveau2.setSurface(TTF_RenderText_Solid(police, "Niveau 2", police_couleur));
    im_niveau2.telecharger_apartir_surface_courante(menu_renderer);

    // bouton niveau 3
    im_niveau3.setSurface(TTF_RenderText_Solid(police, "Niveau 3", police_couleur));
    im_niveau3.telecharger_apartir_surface_courante(menu_renderer);

    // titre
    im_policem.setSurface(TTF_RenderText_Solid(police, "Crazy Monkey", police_couleur));
    im_policem.telecharger_apartir_surface_courante(menu_renderer);

    // règles du jeu
    im_regle.setSurface(TTF_RenderText_Solid(police, "Regles du jeu", police_couleur));
    im_regle.telecharger_apartir_surface_courante(menu_renderer);

    im_singe.telecharger_fichier("data/img/singe.png", menu_renderer);
    im_arbre2.telecharger_fichier("data/img/arbre.png", menu_renderer);
    im_coffret_banane.telecharger_fichier("data/img/bananes.png", menu_renderer);
}

void AffichageSDL::initRegles()
{

    regles = SDL_CreateWindow("Crazy Monkey", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, jungle.get_dimx(), jungle.get_dimy(), SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (regles == nullptr)
    {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }
    regles_renderer = SDL_CreateRenderer(regles, -1, SDL_RENDERER_ACCELERATED);

    im_intro.setSurface(TTF_RenderText_Solid(police2, "Pour gagner la partie il faut que le singe atteint l'arbre de la jungle qui contient le coffret de banane ,  ", police_couleur));
    im_intro.telecharger_apartir_surface_courante(regles_renderer);

    im_intro2.setSurface(TTF_RenderText_Solid(police2, "avant que le compte a rebours arrive a sa fin. Pour cela, voici les regles a suivre: ", police_couleur));
    im_intro2.telecharger_apartir_surface_courante(regles_renderer);

    im_regle1.setSurface(TTF_RenderText_Solid(police2, "- Cliquer n'importe ou sur la fenetre pour choisir un angle du lance du singe.", police_couleur));
    im_regle1.telecharger_apartir_surface_courante(regles_renderer);

    im_regle2.setSurface(TTF_RenderText_Solid(police2, "- Enfoncez la touche Espace sur votre clavier pour choisir une vitesse de lance. (Rouge = faible, vert = fort)", police_couleur));
    im_regle2.telecharger_apartir_surface_courante(regles_renderer);

    im_regle3.setSurface(TTF_RenderText_Solid(police2, "- Essayez de recuperer les bananes magiques, elles rajoutent 5 secondes au temps du jeu! ", police_couleur));
    im_regle3.telecharger_apartir_surface_courante(regles_renderer);

    im_regle4.setSurface(TTF_RenderText_Solid(police2, "- Attention aux serpent ils vous font perdre une vie!", police_couleur));
    im_regle4.telecharger_apartir_surface_courante(regles_renderer);

    im_conclu.setSurface(TTF_RenderText_Solid(police2, "A vous de jouer!", police_couleur));
    im_conclu.telecharger_apartir_surface_courante(regles_renderer);

    im_jouer1.setSurface(TTF_RenderText_Solid(police2, "Niveau 1", police_couleur));
    im_jouer1.telecharger_apartir_surface_courante(regles_renderer);

    im_jouer2.setSurface(TTF_RenderText_Solid(police2, "Niveau 2", police_couleur));
    im_jouer2.telecharger_apartir_surface_courante(regles_renderer);

    im_jouer3.setSurface(TTF_RenderText_Solid(police2, "Niveau 3", police_couleur));
    im_jouer3.telecharger_apartir_surface_courante(regles_renderer);
}

AffichageSDL::~AffichageSDL()
{
    if (avec_son)
    {
        Mix_Quit();
        Mix_FreeChunk(son);
    }

    Mix_CloseAudio();
    TTF_CloseFont(police);
    TTF_CloseFont(police2);
    TTF_Quit();

    SDL_DestroyWindow(fenetre);
    SDL_DestroyWindow(menu);
    SDL_DestroyWindow(regles);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyRenderer(menu_renderer);
    SDL_DestroyRenderer(regles_renderer);

    SDL_Quit();
}

// dessine le menu
void AffichageSDL::sdlAffmenu()
{
    // Remplir l'écran de bleu ciel
    SDL_SetRenderDrawColor(menu_renderer, 166, 223, 255, 255);
    SDL_RenderClear(menu_renderer);

    // Affichage du bouton de niveau 1
    SDL_Rect positionBouton1({(int)jungle.dimx / 2 - 75, (int)jungle.dimy / 2 - 200, 300, 120});
    SDL_RenderCopy(menu_renderer, im_niveau1.getTexture(), nullptr, &positionBouton1);

    // Affichage du bouton de niveau 2
    SDL_Rect positionBouton2({(int)jungle.dimx / 2 - 75, (int)jungle.dimy / 2 - 50, 300, 120});
    SDL_RenderCopy(menu_renderer, im_niveau2.getTexture(), nullptr, &positionBouton2);

    // Affichage du bouton de niveau 3
    SDL_Rect positionBouton3({(int)jungle.dimx / 2 - 75, (int)jungle.dimy / 2 + 100, 300, 120});
    SDL_RenderCopy(menu_renderer, im_niveau3.getTexture(), nullptr, &positionBouton3);

    // Titre du jeu
    SDL_Rect positionTitre({70, 0, 200, 60});
    SDL_RenderCopy(menu_renderer, im_policem.getTexture(), nullptr, &positionTitre);

    // Règles du jeu:
    SDL_Rect positionRegles({1500, 0, 200, 60});
    SDL_RenderCopy(menu_renderer, im_regle.getTexture(), nullptr, &positionRegles);

    im_arbre2.dessiner(menu_renderer, 800, 1000, 100, 100);

}

// dessine les règles
void AffichageSDL::sdlAffRegles()
{
    // Remplir l'écran de bleu ciel
    SDL_SetRenderDrawColor(regles_renderer, 166, 223, 255, 255);
    SDL_RenderClear(regles_renderer);

    // Texte du règle affichage
    SDL_Rect positionIntro({150, 100, 1300, 50});
    SDL_RenderCopy(regles_renderer, im_intro.getTexture(), nullptr, &positionIntro);

    SDL_Rect positionIntro2({150, positionIntro.y + positionIntro.h, 1300, 50});
    SDL_RenderCopy(regles_renderer, im_intro2.getTexture(), nullptr, &positionIntro2);

    SDL_Rect positionRegle1({150, positionIntro2.y + positionIntro2.h + 100, 1300, 50});
    SDL_RenderCopy(regles_renderer, im_regle1.getTexture(), nullptr, &positionRegle1);

    SDL_Rect positionRegle2({150, positionRegle1.y + positionRegle1.h + 20, 1350, 50});
    SDL_RenderCopy(regles_renderer, im_regle2.getTexture(), nullptr, &positionRegle2);

    SDL_Rect positionRegle3({150, positionRegle2.y + positionRegle2.h + 20, 1350, 50});
    SDL_RenderCopy(regles_renderer, im_regle3.getTexture(), nullptr, &positionRegle3);

    SDL_Rect positionRegle4({150, positionRegle3.y + positionRegle3.h + 20, 1200, 50});
    SDL_RenderCopy(regles_renderer, im_regle4.getTexture(), nullptr, &positionRegle4);

    SDL_Rect positionConclu({150, positionRegle4.y + positionRegle4.h + 50, 400, 50});
    SDL_RenderCopy(regles_renderer, im_conclu.getTexture(), nullptr, &positionConclu);

    SDL_Rect positionJouer2({(int)jungle.dimx / 2 + 50, positionConclu.y + positionConclu.h + 50, 300, 120});
    SDL_RenderCopy(regles_renderer, im_jouer2.getTexture(), nullptr, &positionJouer2);

    SDL_Rect positionJouer3({(int)jungle.dimx / 2 + 600, positionConclu.y + positionConclu.h + 50, 300, 120});
    SDL_RenderCopy(regles_renderer, im_jouer3.getTexture(), nullptr, &positionJouer3);

    SDL_Rect positionJouer1({(int)jungle.dimx / 2 - 600, positionConclu.y + positionConclu.h + 50, 300, 120});
    SDL_RenderCopy(regles_renderer, im_jouer1.getTexture(), nullptr, &positionJouer1);
}

void AffichageSDL::sdlBoucleregles()
{
    bool quit = false;
    bool sortir = false;
    bool niveau_1 = false;
    bool niveau_2 = false;
    bool niveau_3 = false;
    SDL_Event e;

    while (!quit)
    {

        SDL_RenderClear(regles_renderer);
        sdlAffRegles();
        while (SDL_PollEvent(&e))
        {
            if ((avec_son))
            {
                Mix_PlayChannel(-1, son, 0);
                Mix_Volume(-1, 100);
            }
            if (e.type == SDL_QUIT)
            {
                sortir = true;
                quit = true;
            }

            switch (e.type)
            {
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    sortir = true;
                    quit = true;
                    break;
                }
            case SDL_MOUSEBUTTONDOWN:
                int curseur_x, curseur_y;
                SDL_GetMouseState(&curseur_x, &curseur_y);
                // si il clique sur Jouer :
                if ((curseur_x >= (int)jungle.dimx / 2 + 50) && (curseur_x <= (int)jungle.dimx / 2 + 350) && (curseur_y >= 740) && (curseur_y <= 900))
                {
                    niveau_2 = true;
                    quit = true;
                }

                if ((curseur_x >= (int)jungle.dimx / 2 + 600) && (curseur_x <= (int)jungle.dimx / 2 + 900) && (curseur_y >= 740) && (curseur_y <= 900))
                {
                    niveau_3 = true;
                    quit = true;
                }

                if ((curseur_x >= (int)jungle.dimx / 2 - 600) && (curseur_x <= (int)jungle.dimx / 2 - 300) && (curseur_y >= 740) && (curseur_y <= 900))
                {
                    niveau_1 = true;
                    quit = true;
                }
            }
        }
        // Render the menu background
        sdlAffRegles();
        SDL_RenderPresent(regles_renderer);
    }

    SDL_DestroyRenderer(regles_renderer);
    SDL_DestroyWindow(regles);
    if (!sortir)
    {
        if (niveau_2)
        {
            jungle.jungle_niveau2();
            sdlBouclejeu();
        }
        if (niveau_1)
        {
            jungle.jungle_niveau1();
            sdlBouclejeu();
        }
        if (niveau_3)
        {
            jungle.jungle_niveau3();
            sdlBouclejeu();
        }
    }
}

void AffichageSDL::sdlBouclemenu()
{
    bool quit = false;
    bool sortir = false;
    bool niveau_1 = false;
    bool niveau_2 = false;
    bool niveau_3 = false;
    bool regles = false;
    SDL_Event e;

    while (!quit)
    {

        SDL_RenderClear(menu_renderer);
        sdlAffmenu();
        while (SDL_PollEvent(&e))
        {
            if ((avec_son))
            {
                Mix_PlayChannel(-1, son, 0);
                Mix_Volume(-1, 100);
            }
            if (e.type == SDL_QUIT)
            {
                sortir = true;
                quit = true;
            }
            switch (e.type)
            {
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    quit = true;
                    sortir = true;
                    break;
                }
            case SDL_MOUSEBUTTONDOWN:
                int curseur_x, curseur_y;
                SDL_GetMouseState(&curseur_x, &curseur_y);
                // si il clique sur Jouer :

                if ((curseur_x >= (int)jungle.dimx / 2 - 75) && (curseur_x <= (int)jungle.dimx / 2 + 225) && (curseur_y >= (int)jungle.dimy / 2 - 200) && (curseur_y <= (int)jungle.dimy / 2 - 80))
                {
                    niveau_1 = true;
                    quit = true;
                }
                if ((curseur_x >= (int)jungle.dimx / 2 - 75) && (curseur_x <= (int)jungle.dimx / 2 + 225) && (curseur_y >= (int)jungle.dimy / 2 - 50) && (curseur_y <= (int)jungle.dimy / 2 + 70))
                {
                    niveau_2 = true;
                    quit = true;
                }
                if ((curseur_x >= (int)jungle.dimx / 2 - 75) && (curseur_x <= (int)jungle.dimx / 2 + 225) && (curseur_y >= (int)jungle.dimy / 2 + 100) && (curseur_y <= (int)jungle.dimy / 2 + 220))
                {
                    niveau_3 = true;
                    quit = true;
                }
                if ((curseur_x >= 1500) && (curseur_x <= 1500 + 200) && (curseur_y >= 0) && (curseur_y <= 60))
                {
                    regles = true;
                    quit = true;
                }

                break;
            }
        }
        // Render the menu background
        sdlAffmenu();
        SDL_RenderPresent(menu_renderer);
    }
    SDL_DestroyRenderer(menu_renderer);
    SDL_DestroyWindow(menu);
    if (!sortir)
    {
        if (niveau_2)
        {
            jungle.jungle_niveau2();
            sdlBouclejeu();
        }
        if (niveau_1)
        {
            jungle.jungle_niveau1();
            sdlBouclejeu();
        }
        if (niveau_3)
        {
            jungle.jungle_niveau3();
            sdlBouclejeu();
        }
        if (regles)
            sdlBoucleregles();
    }
}

// dessine les objets du jeu
void AffichageSDL::sdlAff()
{
    // Remplir l'écran de bleu ciel
    SDL_SetRenderDrawColor(renderer, 166, 223, 255, 255);
    SDL_RenderClear(renderer);

    // Afficher le singe
    im_singe.dessiner(renderer, jungle.s.getpos().x - jungle.s.getrayon(), jungle.s.getpos().y - jungle.s.getrayon(), 2 * jungle.s.getrayon(), 2 * jungle.s.getrayon());
    // Afficher les arbres
    for (unsigned int i = 0; i < jungle.nb_arbre; i++)
    {
        im_arbre.dessiner(renderer, jungle.tab_arbre[i].getCentre().x - jungle.tab_arbre[i].getRayon(), jungle.tab_arbre[i].getCentre().y - jungle.tab_arbre[i].getRayon(), 2 * jungle.tab_arbre[i].getRayon(), 2 * jungle.tab_arbre[i].getRayon());
        // Afficher le serpent (s'il y en a un)
        if (jungle.tab_arbre[i].getSerpent())
            im_serpent.dessiner(renderer, jungle.tab_arbre[i].getCentre().x - jungle.tab_arbre[i].getRayon() + 50, jungle.tab_arbre[i].getCentre().y - jungle.tab_arbre[i].getRayon() - 45, 60, 60);
        // Afficher le coffret de bananes (s'il y en a un)
        if (jungle.tab_arbre[i].getCoffret_bananes())
        {
            im_coffret_banane.dessiner(renderer, jungle.tab_arbre[i].getCentre().x - jungle.tab_arbre[i].getRayon() + 50, jungle.tab_arbre[i].getCentre().y - jungle.tab_arbre[i].getRayon() - 45, 100, 100);
        }
        // Afficher la banane magique (s'il y en a une)
        if (jungle.tab_arbre[i].getBanane_magique())
        {

            im_banane_mag.dessiner(renderer, jungle.tab_arbre[i].getCentre().x - jungle.tab_arbre[i].getRayon() + 50, jungle.tab_arbre[i].getCentre().y - jungle.tab_arbre[i].getRayon() - 45, 60, 60);
        }
    }

    // Titre du jeu
    SDL_Rect positionTitre({70, 0, 200, 60});
    SDL_RenderCopy(renderer, im_police.getTexture(), nullptr, &positionTitre);

    // Message perdu
    if (jungle.temps_partie == 0 || jungle.collision_sol)
    {
        SDL_Rect positionTitre({(int)jungle.dimx / 2 - 75, (int)jungle.dimy / 2 - 50, 300, 120});
        SDL_RenderCopy(renderer, im_perdu.getTexture(), nullptr, &positionTitre);
    }
    // Message gagné
    if (jungle.coffret)
    {
        SDL_Rect positionTitre({(int)jungle.dimx / 2 - 75, (int)jungle.dimy / 2 - 50, 300, 120});
        SDL_RenderCopy(renderer, im_gagne.getTexture(), nullptr, &positionTitre);
    }

    // Choix de vitesse
    if (jungle.etat == 0 && !disparait && !jungle.coffret)
    {
        // Definir le degradé de couleur
        SDL_Color couleur_debut = {255, 0, 0, 255};
        SDL_Color couleur_fin = {0, 255, 0, 255};

        // Definir la position du rectangle de degradé
        box_rect = {(int)jungle.s.getpos().x + 100, (int)jungle.s.getpos().y - 50, 250, 20};

        // PLacer le point pour la position du départ
        if (nouveau_saut)
        {
            jungle.s.set_pos_point((int)box_rect.x + 5);
            nouveau_saut = false;
        }
        int taille_point = 20;

        // dessine le dégradé des couleurs du rectangle
        for (int x = 0; x < box_rect.w; x++)
        {
            float t = (float)x / (float)box_rect.w;
            couleur_vitesse = {
                (Uint8)((1.0f - t) * couleur_debut.r + t * couleur_fin.r),
                (Uint8)((1.0f - t) * couleur_debut.g + t * couleur_fin.g),
                (Uint8)((1.0f - t) * couleur_debut.b + t * couleur_fin.b),
                255};
            SDL_Rect rect = {box_rect.x + x, box_rect.y, 1, box_rect.h};
            SDL_SetRenderDrawColor(renderer, couleur_vitesse.r, couleur_vitesse.g, couleur_vitesse.b, couleur_vitesse.a);
            SDL_RenderFillRect(renderer, &rect);
        }
        // Dessiner le point dans le rectangle
        SDL_Rect dot_rect = {jungle.s.getpos_point() - taille_point / 2, box_rect.y - taille_point / 2, taille_point, taille_point};
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &dot_rect);
    }
    // affiche le chronomètre en noir, et s'il reste moins que 10sec en rouge
    if (jungle.temps_partie < 10)
        chrono_couleur = {255, 0, 0};
    string temps_partie_str = to_string(jungle.temps_partie);
    im_chrono.setSurface(TTF_RenderText_Solid(police, temps_partie_str.c_str(), chrono_couleur));
    im_chrono.telecharger_apartir_surface_courante(renderer);
    im_chrono.dessiner(renderer, jungle.dimx / 2, 10, 120, 60);

    // Afficher le nombre de vies
    string nbvies = to_string(jungle.s.get_nb_vie());
    string message = "Vies : " + nbvies;
    im_vie.setSurface(TTF_RenderText_Solid(police, message.c_str(), police_couleur));
    im_vie.telecharger_apartir_surface_courante(renderer);
    im_vie.dessiner(renderer, 1600, 0, 200, 60);
}

Uint32 chrono_callback(Uint32 interval, void *param)
{
    int *chrono = (int *)param;
    (*chrono)--;
    return interval;
}

void AffichageSDL::sdlBouclejeu()
{

    SDL_Event events;
    double angle;
    bool bouger = false;
    bool point = true;
    bool quit = false;
    bool fin_saut = false;
    chrono_id = SDL_AddTimer(1000, chrono_callback, &jungle.temps_partie);
    int col = -1;

    // tant que ce n'est pas la fin ...
    while (!quit)
    {

        // tant qu'il y a des évenements à traiter (cette boucle n'est pas bloquante)

        SDL_RenderClear(renderer);
        sdlAff();

        // quand le temps est fini, le chronomètre reste à 1 et ne part pas au négatif
        if (jungle.temps_partie <= 0)
        {
            jungle.temps_partie = 0;
            SDL_RemoveTimer(chrono_id);
        }
        if (jungle.collision_sol || jungle.coffret)
            SDL_RemoveTimer(chrono_id);

        while (SDL_PollEvent(&events))
        {

            // joue le son
            if ((avec_son))
            {
                Mix_PlayChannel(-1, son, 0);
                Mix_Volume(-1, 100);
            }

            if (events.type == SDL_QUIT)
                quit = true;

            switch (events.type)
            {
            case SDL_KEYDOWN:
                switch (events.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    quit = true;
                    break;
                case SDLK_SPACE:
                    if (jungle.get_etat() == 0)
                    {
                        bouger = false;
                        jungle.s.calculeVitesse((make_vec2((double)jungle.s.getpos_point(), (double)box_rect.y)), make_vec2((double)box_rect.x, (double)box_rect.y), make_vec2(((double)box_rect.x + (double)box_rect.w), (double)box_rect.y));
                        point = false;
                    }
                    break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (jungle.temps_partie > 0 && !jungle.collision_sol && !jungle.coffret)
                {
                    if (jungle.etat == 0)
                    {
                        angle = jungle.s.calculeAlpha(make_vec2(events.button.x, events.button.y));
                        jungle.etat = 1;
                    }
                }

                // SDL_RenderClear(renderer);
                // sdlAff();
                break;
            }
        }
        // Pour bouger le point sur le rectangle de vitesse
        if (point)
            bouger = true;
        if (jungle.etat == 0 && bouger)
        {
            jungle.s.changer_pos_point(box_rect.x, box_rect.w);
        }

        if (jungle.temps_partie > 0 && !jungle.collision_sol && !jungle.coffret)
            fin_saut = false;

        // Si le singe est dans la deuxieme phase (etat 1), c'est-à-dire pendant son mouvement:
        if (jungle.etat == 1)
        {
            double t = 0;
            double dt = 0.1;
            SDL_RenderClear(renderer);
            do
            {
                t += dt;

                // calcule le mouvement parabolique
                jungle.s.set_pos(jungle.s.calcule_pos(angle, t));

                SDL_RenderClear(renderer);
                sdlAff();
                SDL_RenderPresent(renderer);

                // SI y a une collision avec le sol, le singe s'arrête
                if (jungle.collisionsol())
                {
                    disparait = true;
                    fin_saut = true;
                    
                }
                // Si le temps de la partie est finie, le jeu s'arrête
                if (jungle.temps_partie == 0)
                {
                    fin_saut = true;
                   
                }
                // S'il y a une collision avec un arbre, le singe s'arrête
                if ((col = jungle.collisionarbre()) >= 0)
                {
                    nouveau_saut = true;
                    point = true;
                    fin_saut = true;
                    jungle.arbre_prec = col;
                    
                }
            } while (!fin_saut);
        }

        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
    }
}

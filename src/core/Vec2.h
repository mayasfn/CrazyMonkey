#ifndef _VEC2_H
#define _VEC2_H

/**
 * @brief Structure Vec2 qui contient deux double x et y
 *
 */
struct Vec2
{
    double x, y;
};

/**
 * @brief Créer un vecteur à partir de deux points
 *
 * @param[in] x
 * @param[in] y
 * @return Vec2
 */
Vec2 make_vec2(double x, double y);

/**
 * @brief Operateur +, additionne deux vecteurs
 *
 * @param[in] a
 * @param[in] b
 * @return Vec2
 */
Vec2 operator+(Vec2 a, Vec2 b);

/**
 * @brief Opérateur - , soustrait deux vecteurs
 *
 * @param[in] a
 * @param[in] b
 * @return Vec2
 */
Vec2 operator-(Vec2 a, Vec2 b);

/**
 * @brief Operateur += , permet d'ajouter b à a sans récrire a
 *
 * @param[in] a
 * @param[in] b
 * @return Vec2
 */
Vec2 operator+=(Vec2 a, Vec2 b);

/**
 * @brief Operateur *, multiplie un réel et un vecteur
 *
 * @param[in] a
 * @param[in] b
 * @return Vec2
 */
Vec2 operator*(float a, Vec2 b);

/**
 * @brief Operateur *, multiplie un réel et un vecteur
 * Deux opérateurs * pour éviter des erreurs avec l'ordre du vecteur et du réel
 *
 * @param[in] a
 * @param[in] b
 * @return Vec2
 */
Vec2 operator*(Vec2 b, float a);

/**
 * @brief Operateur /, divise un vecteur par un réel
 *
 * @param[in] a
 * @param[in] b
 * @return Vec2
 */
Vec2 operator/(Vec2 a, float b);

/**
 * @brief Calcule la distance entre deux points
 *
 * @param[in] a
 * @param[in] b
 * @return double
 */
double distance(Vec2 a, Vec2 b);

#endif

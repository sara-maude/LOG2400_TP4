// #include "nuage.h"
// #include <cmath>
// #include <iostream>
// #include <sstream>
// #include <algorithm>

// using namespace std;

// Nuage::Nuage(vector<Point>& points) : elements(points), grille(vector<Point>(points.begin(), points.end())) {
// }

// void Nuage::afficherInfo() {
//     for (Element& element : elements) {
//         element.afficherInfo();
//     }
// }

// void Nuage::afficherIndex(Grille& grille) {
//     for (Element& element : elements) {
//         element.afficherIndex(grille);
//     }
// }

// void Nuage::afficherTexture(Grille& grille) {
//     for (Element& element : elements) {
//         element.afficherTexture(grille);
//     }
// }

// void Nuage::deplacerPoint(int id, int nouvelleX, int nouvelleY) {
//     for (Element& element : elements) {
//         element.deplacerPoint(id, nouvelleX, nouvelleY);
//     }
// }

// // trouver et supprimer point dans tous les nuages auxquels ce point appartient
// void Nuage::supprimerPoint(int id) {
//     for (int i = 0; i < elements.size(); i++) {
//         elements[i].getId();
//         if (elements[i].getId() == id) {
//             elements.erase(elements.begin() + i);
//         } else if (elements[i].getId() == -1) {
//             Nuage& nuage = static_cast<Nuage&>(elements[i]);
//             nuage.supprimerPoint(id);
//         }
//     }
// }


// // pourrait rester dans grille.cpp je pense
// void Nuage::tracerLigne(Grille& grille, int x0, int y0, int x1, int y1) {
//     int dx = x1 - x0;
//     int dy = y1 - y0;
//     int taille = max(abs(dx), abs(dy));

//     // Ligne horizontale
//     if (dy == 0) {
//         for (int i = 0; i <= taille; i++) {
//             int x = (dx > 0) ? x0 + i : x0 - i;
//             if (y0 >= 0 && y0 < grille.hauteur && x >= 0 && x < grille.largeur)
//                 grille.grille[y0][x] = '-';
//         }
//         return;
//     }

//     // Ligne verticale
//     if (dx == 0) {
//         for (int i = 0; i <= taille; i++) {
//             int y = (dy > 0) ? y0 + i : y0 - i;
//             if (x0 >= 0 && x0 < grille.largeur && y >= 0 && y < grille.hauteur)
//                 grille.grille[y][x0] = '|';
//         }
//         return;
//     }

//     // Diagonales
//     for (int i = 0; i <= taille; ++i) {
//         double t = (double)i / taille;
//         int x = round(x0 + t * dx);
//         int y = round(y0 + t * dy);

//         if (x >= 0 && x < grille.largeur && y >= 0 && y < grille.hauteur) {
//             grille.grille[y][x] = (dx * dy > 0) ? '/' : '\\';
//         }
//     }
// }

// void Nuage::traceDistanceMinimale() {
//     // On peut choisir de tracer la distance minimale entre les points du nuage.
//     // Pour l'instant, cette méthode est laissée vide.
// }

// void Nuage::traceOrdreId() {
//     // for (int i = 0; i < elements.size(); i++) {
//     //     if (i < elements.size() - 1) {
//     //         tracerLigne(grille, points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
//     //     } else {
//     //         tracerLigne(grille, points[i].x, points[i].y, points[0].x, points[0].y);
//     //     }
//     // }
// }

// void Nuage::fusionnerPoints(vector<Point>& points) {
//     vector<Element> nouveauxElements;
//     nouveauxElements.insert(nouveauxElements.end(), points.begin(), points.end());
//     Nuage nouveauNuage = Nuage(nouveauxElements);
//     char texture = texturesNuages[indexTexture % texturesNuages.size()];
//     indexTexture++;

//     for (Element& element : nouveauxElements) {
//         // element.texture = texture;
//         // supprimer l'élément des éléments actuels ou marquer comme fusionné
//     }
// }
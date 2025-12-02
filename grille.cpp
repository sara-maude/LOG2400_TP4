#include "grille.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

Grille::Grille() : grille(hauteur, vector<char>(largeur, ' ')) {}

void Grille::viderGrille() {
    for (int y = 0; y < hauteur; ++y) {
        for (int x = 0; x < largeur; ++x) {
            grille[y][x] = ' ';
        }
    }
}

void Grille::imprimerGrille() const {
    for (int y = hauteur - 1; y >= 0; --y) {
        for (int x = 0; x < largeur; ++x)
            cout << grille[y][x];
        cout << '\n';
    }
}

void Grille::tracerLigne(int x0, int y0, int x1, int y1) {

    int dx = x1 - x0;
    int dy = y1 - y0;
    int taille = max(abs(dx), abs(dy));

    if (dy == 0) {
        for (int i = 0; i <= taille; i++) {
            int x = (dx > 0) ? x0 + i : x0 - i;
            if (y0 >= 0 && y0 < hauteur && x >= 0 && x < largeur)
                grille[y0][x] = '-';
        }
        return;
    }

    if (dx == 0) {
        for (int i = 0; i <= taille; i++) {
            int y = (dy > 0) ? y0 + i : y0 - i;
            if (x0 >= 0 && x0 < largeur && y >= 0 && y < hauteur)
                grille[y][x0] = '|';
        }
        return;
    }

    for (int i = 0; i <= taille; ++i) {
        double t = (double)i / taille;
        int x = round(x0 + t * dx);
        int y = round(y0 + t * dy);

        if (x >= 0 && x < largeur && y >= 0 && y < hauteur) {
            grille[y][x] = (dx * dy > 0) ? '/' : '\\';
        }
    }
}
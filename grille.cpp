#include "grille.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

Grille::Grille(vector<Point>& points) : grille(hauteur, vector<char>(largeur, ' ')), points(points) {
    for (Point point : points) {
        const char affichage = '.';
        grille[point.getY()][point.getX()] = affichage;
    }
}

void Grille::viderGrille() {
    for (int y = 0; y < hauteur; ++y) {
        for (int x = 0; x < largeur; ++x) {
            grille[y][x] = ' ';
        }
    }
}

void Grille::afficherTexture() {
    for (Point point : points) {
        grille[point.getY()][point.getX()] = texture;
    }
    afficherGrille();
}

void Grille::afficherGrille() const {
    // On imprime la grille.
    for (int y = hauteur - 1; y >= 0; --y) {
        for (int x = 0; x < largeur; ++x)
            cout << grille[y][x];
        cout << '\n';
    }
}

void Grille::afficherIndex(){
    for (int i = 0; i < points.size(); ++i) {
        const Point& point = points[i];
        grille[point.getY()][point.getX()] = '0' + i;
    }
    afficherGrille();
}

void Grille::tracerLigne(vector<vector<char>>& grille, int x0, int y0, int x1, int y1) {

    int dx = x1 - x0;
    int dy = y1 - y0;
    int taille = max(abs(dx), abs(dy));

    // Ligne horizontale
    if (dy == 0) {
        for (int i = 0; i <= taille; i++) {
            int x = (dx > 0) ? x0 + i : x0 - i;
            if (y0 >= 0 && y0 < hauteur && x >= 0 && x < largeur)
                grille[y0][x] = '-';
        }
        return;
    }

    // Ligne verticale
    if (dx == 0) {
        for (int i = 0; i <= taille; i++) {
            int y = (dy > 0) ? y0 + i : y0 - i;
            if (x0 >= 0 && x0 < largeur && y >= 0 && y < hauteur)
                grille[y][x0] = '|';
        }
        return;
    }

    // Diagonales
    for (int i = 0; i <= taille; ++i) {
        double t = (double)i / taille;
        int x = round(x0 + t * dx);
        int y = round(y0 + t * dy);

        if (x >= 0 && x < largeur && y >= 0 && y < hauteur) {
            grille[y][x] = (dx * dy > 0) ? '/' : '\\';
        }
    }
}


void Grille::imprimerTraceOrdreId() {
    viderGrille();

    for (int i = 0; i < points.size(); i++) {
        if (i < points.size() - 1) {
            tracerLigne(grille, points[i].getX(), points[i].getY(), points[i + 1].getX(), points[i + 1].getY());
        } else {
            tracerLigne(grille, points[i].getX(), points[i].getY(), points[0].getX(), points[0].getY());
        }
    }
}

void Grille::imprimerTraceDistanceMinimale() {
    viderGrille();
    
    vector<int> connexion(points.size(), 0);
    int indexActuel = 0;
    for (int count = 1; count < points.size(); ++count) {
        connexion[indexActuel]++;
        int indexPlusProche = -1;
        double plusPetiteDistance = numeric_limits<double>::max();
        for (int i = 0; i < points.size(); ++i) {
            if (connexion[i] == 0) {
                double distance = sqrt(pow(points[i].getX() - points[indexActuel].getX(), 2) +
                                       pow(points[i].getY() - points[indexActuel].getY(), 2));
                if (distance < plusPetiteDistance) {
                    plusPetiteDistance = distance;
                    indexPlusProche = i;
                }
            }
        }
        tracerLigne(grille, points[indexActuel].getX(), points[indexActuel].getY(),
                    points[indexPlusProche].getX(), points[indexPlusProche].getY());

        connexion[indexPlusProche]++;
        indexActuel = indexPlusProche;
    }
    int premierIndex = -1;
    int deuxiemeIndex = -1;
    for (int i = 0; i < connexion.size(); ++i) {
        if (connexion[i] == 1) {
            if (premierIndex == -1) {
                premierIndex = i;
            } else {
                deuxiemeIndex = i;
                break;
            }
        }
    }
    tracerLigne(grille, points[premierIndex].getX(), points[premierIndex].getY(),
                    points[deuxiemeIndex].getX(), points[deuxiemeIndex].getY());
}
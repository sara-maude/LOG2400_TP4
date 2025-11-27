#pragma once
#include <string>
#include <vector>

class Point;

const int LARGEUR = 30;
const int HAUTEUR = 20;

std::vector<Point> creerPoints(const std::string& ligne);
// void tracerLigne(std::vector<std::vector<char>>& grille, int x0, int y0, int x1, int y1);
// void imprimerGrille(const std::vector<Point>& points);
// void deplacerPoint(Point& point, int positionX, int positionY);

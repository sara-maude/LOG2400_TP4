#include "orthese.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <memory>

using namespace std;

Orthese::Orthese(const string& ligne) : grille() {
    int idCompteur = 0;
    // On crée un flux de lecture (istringstream) à partir de la chaîne ligne.
    istringstream iss(ligne);
    string token;
    // On lit chaque point de la ligne (séparé par des espaces).
    while (iss >> token) {
        // On vérifie que le point est entre parenthèses
        if (token.size() >= 3 && token.front() == '(' && token.back() == ')') {
            // On enlève les parenthèses au début et à la fin.
            token = token.substr(1, token.size() - 2);
            // On remplace la virgule par un espace.
            replace(token.begin(), token.end(), ',', ' ');
            // On crée un flux de lecture pour chaque point
            istringstream pair(token);
            int x, y;
            // On ajoute un point {x, y} au vecteur de points.
            if (pair >> x >> y) {
                points.push_back(make_shared<Point>(x, y, idCompteur++));
            }
        }
    }
}

void Orthese::afficherInfo() {
    for (shared_ptr<Point>& point : points) {
        point->afficherInfo();
    }
    for (unique_ptr<Nuage>& nuage : nuages) {
        nuage->afficherInfo();
    }
}

void Orthese::afficherAvecTransformation(function<vector<char>(const Point&)> f) {
    for (shared_ptr<Point> point : points) {
        for (int i = 0; i < f(*point).size(); ++i) {
            grille.grille[point->getY()][point->getX() + i] = f(*point)[i];
        }
    }
    grille.imprimerGrille();
}


void Orthese::afficherTexture() {
    afficherAvecTransformation([](const Point& p) {
        return p.getTexture();
    });
}


void Orthese::afficherIndex() {
    afficherAvecTransformation([](const Point& p) {
        vector<char> ids;
        ids.push_back('0' + p.getId());
        return ids;
    });
}


void Orthese::fusionnerPoints(vector<int> ids) {
    grille.viderGrille();
    vector<shared_ptr<Point>> pointsAAjouter;

    for (int id : ids) {
        for (shared_ptr<Point>& point : points) {
            if (point->getId() == id) {
                pointsAAjouter.push_back(point);
                break;
            }
        }
    }

    if (!pointsAAjouter.empty()) {
        unique_ptr<Nuage> nuage = make_unique<Nuage>(pointsAAjouter, prochainIdNuage++);
        nuages.push_back(move(nuage));
    }
}

void Orthese::deplacerPoint(int id, int nouvelleX, int nouvelleY) {
    grille.viderGrille();
    for (shared_ptr<Point>& point : points) {
        if (point->getId() == id) {
            point->deplacerPoint(id, nouvelleX, nouvelleY);
            return;
        }
    }
    cout << "Point avec ID " << id << " non trouvé.\n";
}

void Orthese::supprimerPoint(int id) {
    grille.viderGrille();
    bool trouve = false;

    // Supprimer le point global
    for (shared_ptr<Point>& point : points) {
        if (point->getId() == id) {
            points.erase(remove(points.begin(), points.end(), point), points.end());
            trouve = true;
            break;
        }
    }


    for (unique_ptr<Nuage>& nuage : nuages) {
        if (nuage) {
            nuage->supprimerPoint(id);
        }
    }

    if (!trouve) {
        cout << "Point avec ID " << id << " non trouvé.\n";
    }

    // Mettre à jour les IDs restants
    for (shared_ptr<Point>& point : points) {
        if (point->getId() > id) {
            if (point) point->setId(point->getId() - 1);
        }
    }
}

void Orthese::afficherSurface(const InterfaceStrategieSurface& strategie) {
    grille.viderGrille();
    for (unique_ptr<Nuage>& nuage : nuages) {
        strategie.tracerSurface(nuage->getPoints(), grille);
    }
}

void SurfaceId::tracerSurface(vector<shared_ptr<Point>>& points, Grille& grille) const {
    for (int i = 0; i < points.size(); i++) {
        if (i < points.size() - 1) {
            grille.tracerLigne(points[i]->getX(), points[i]->getY(), points[i + 1]->getX(), points[i + 1]->getY());
        } else {
            grille.tracerLigne(points[i]->getX(), points[i]->getY(), points[0]->getX(), points[0]->getY());
        }
    }
}

void SurfaceDistance::tracerSurface(vector<shared_ptr<Point>>& points, Grille& grille) const {
    vector<int> connexion(points.size(), 0);
    int indexActuel = 0;
    for (int count = 1; count < points.size(); ++count) {
        connexion[indexActuel]++;
        int indexPlusProche = -1;
        double plusPetiteDistance = numeric_limits<double>::max();
        for (int i = 0; i < points.size(); ++i) {
            if (connexion[i] == 0) {
                double distance = sqrt(pow(points[i]->getX() - points[indexActuel]->getX(), 2) +
                                       pow(points[i]->getY() - points[indexActuel]->getY(), 2));
                if (distance < plusPetiteDistance) {
                    plusPetiteDistance = distance;
                    indexPlusProche = i;
                }
            }
        }
        grille.tracerLigne(points[indexActuel]->getX(), points[indexActuel]->getY(),
                    points[indexPlusProche]->getX(), points[indexPlusProche]->getY());

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
    grille.tracerLigne(points[premierIndex]->getX(), points[premierIndex]->getY(),
                    points[deuxiemeIndex]->getX(), points[deuxiemeIndex]->getY());
}

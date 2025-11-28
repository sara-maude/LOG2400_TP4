#include "orthese.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <memory>

using namespace std;

// faire une fonction de recherche d'élément par ID ?

Orthese::Orthese(const string& ligne) : grille() {
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
                elements.push_back(make_shared<Point>(x, y));
            }
        }
    }
}

void Orthese::afficherInfo() {
    for (shared_ptr<Element>& element : elements) {
        element->afficherInfo();
    }
}

void Orthese::afficherAvecTransformation(function<vector<char>(Point&)> f) {
    for (shared_ptr<Element> element : elements) {
        if (auto point = dynamic_pointer_cast<Point>(element)) {
            for (int i = 0; i < f(*point).size(); ++i) {
                if (point->getX() + i >= grille.largeur) {
                    cout << "Point " << point->getId() << " a la texture " << f(*point)[i] <<" hors de la grille\n";
                    continue;
                }
                grille.grille[point->getY()][point->getX() + i] = f(*point)[i];
            }
        }
    }
    grille.imprimerGrille();
}


void Orthese::afficherTexture() {
    afficherAvecTransformation([](Point& p) {
        return p.getTexture();
    });
}


void Orthese::afficherIndex() {
    afficherAvecTransformation([](Point& p) {
        vector<char> ids;
        ids.push_back('0' + p.getId());
        return ids;
    });
}


void Orthese::fusionnerPoints(vector<int> ids) {
    grille.viderGrille();
    vector<shared_ptr<Element>> elementsAAjouter;

    for (int id : ids) {
        for (shared_ptr<Element>& element : elements) {
            if (element->getId() == id) {
                elementsAAjouter.push_back(element);
                break;
            }
        }
    }

    if (!elementsAAjouter.empty()) {
        shared_ptr<Nuage> nuage = make_shared<Nuage>(elementsAAjouter);
        elements.push_back(nuage);
    }
}

void Orthese::deplacerPoint(int id, int nouvelleX, int nouvelleY) {
    grille.viderGrille();
    for (shared_ptr<Element>& element : elements) {
        if (element->getId() == id) {
            if (auto point = dynamic_pointer_cast<Point>(element)) {
                point->deplacerPoint(id, nouvelleX, nouvelleY);
                return;
            }
        }
    }
    cout << "Point avec ID " << id << " non trouvé.\n";
}

void Orthese::supprimerPoint(int id) {
    grille.viderGrille();
    bool trouve = false;

    elements.erase(
        remove_if(elements.begin(), elements.end(),
            [id, &trouve](shared_ptr<Element>& elem) {
                if (auto p = dynamic_pointer_cast<Point>(elem)) {
                    if (p->getId() == id) {
                        trouve = true;
                        return true;
                    }
                }
                return false;
            }
        ),
        elements.end()
    );

    for (auto& elem : elements) {
        if (auto nuage = dynamic_pointer_cast<Nuage>(elem)) {
            nuage->supprimerPoint(id);
        }
    }

    if (!trouve) {
        cout << "Point avec ID " << id << " non trouvé.\n";
    }

    for (auto& elem : elements) {
        if (elem->getId() > id) {
            elem->setId(elem->getId() - 1);
        }
    }
}


void Orthese::afficherSurface(const InterfaceStrategieSurface& strategie) {
    grille.viderGrille();
    for (shared_ptr<Element>& element : elements) {
        if (auto nuage = dynamic_pointer_cast<Nuage>(element)) {
            strategie.tracerSurface(nuage->getPoints(), grille);
        }
    }
}

void SurfaceId::tracerSurface(vector<shared_ptr<Point>> points, Grille& grille) const {
    for (int i = 0; i < points.size(); i++) {
        if (i < points.size() - 1) {
            grille.tracerLigne(points[i]->getX(), points[i]->getY(), points[i + 1]->getX(), points[i + 1]->getY());
        } else {
            grille.tracerLigne(points[i]->getX(), points[i]->getY(), points[0]->getX(), points[0]->getY());
        }
    }
}

void SurfaceDistance::tracerSurface(vector<shared_ptr<Point>> points, Grille& grille) const {
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

#include "orthese.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <memory>

using namespace std;

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
                elements.push_back(make_shared<PointConcret>(x, y, idElement++));
            }
        }
    }
}

void Orthese::afficherInfo() {
    for (shared_ptr<Element>& element : elements) {
        element->afficherInfo();
    }
}

void Orthese::afficherAvecTransformation(function<string(Point&)> f) {
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
        string texture = p.getTexture() == "" ? "." : p.getTexture();
        return texture;
    });
}


void Orthese::afficherIndex() {
    afficherAvecTransformation([](Point& p) {
        return std::to_string(p.getId());
    });
}

void Orthese::fusionnerPoints(const vector<int>& ids) {
    vector<shared_ptr<Element>> elementsAAjouter;

    for (int id : ids) {
        for (auto it = elements.begin(); it != elements.end(); ++it) {
            if ((*it)->getId() == id) {
                elementsAAjouter.push_back(*it);
                break;
            }
        }
    }

    shared_ptr<Nuage> nuage = make_shared<Nuage>(elementsAAjouter, idElement++);

    elements.push_back(nuage);

    vector<shared_ptr<Point>> pointsDecores = nuage->getPoints();

    for (shared_ptr<Point>& point : pointsDecores) {
        int id = point->getId();

        elements[id] = point;
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

    for (shared_ptr<Element> elem : elements) {
        if (elem->getId() > id) {
            elem->setId(elem->getId() - 1);
        }
    }
}

void Orthese::ajouterPoint(shared_ptr<Point> point, vector<shared_ptr<Nuage>> nuages) {
    grille.viderGrille();
    int id = point->getId();

    for (shared_ptr<Element> element: elements) {
        int elemId = element->getId();
        if (elemId >= id) {
            element->setId(++elemId);
        }
    }

    elements.insert(elements.begin() + id, point);
    
    for (shared_ptr<Nuage> nuage: nuages) {
        nuage->ajouterPoint(point);
    }
}


void Orthese::afficherSurface() {
    grille.viderGrille();
    for (shared_ptr<Element>& element : elements) {
        if (auto nuage = dynamic_pointer_cast<Nuage>(element)) {
            strategie->tracerSurface(nuage->getPoints(), grille);
        }
    }
}

void SurfaceId::tracerSurface(vector<shared_ptr<Point>> points, Grille& grille) const {
    sort(points.begin(), points.end(), [](const shared_ptr<Point>& a, const shared_ptr<Point>& b){
        return a->getId() < b->getId();
    });

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

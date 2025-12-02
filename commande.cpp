#include "commande.h"

using namespace std;

CommandeSupression::CommandeSupression(Orthese& orthese, int id): orthese(orthese), id(id) {
    ancienPoint = dynamic_pointer_cast<Point>(orthese.getElements()[id]);

    for (shared_ptr<Element> element: orthese.getElements()) {
        if (shared_ptr<Nuage> nuage = dynamic_pointer_cast<Nuage>(element)) {
            for (shared_ptr<Element> element: nuage->getElements()) {
                if (shared_ptr<Point> point = dynamic_pointer_cast<Point>(element)) {
                    if (point->getId() == id) {
                        nuagesContenantPoint.push_back(nuage);
                        break;
                    }
                }
            }
        }
    }
}

void CommandeSupression::executer() const {
    orthese.supprimerPoint(id);
}

void CommandeSupression::annuler() const {
    orthese.ajouterPoint(ancienPoint, nuagesContenantPoint);
}

CommandeDeplacement::CommandeDeplacement(Orthese& orthese, int id, int positionX, int positionY):
    orthese(orthese), id(id), nouveauX(positionX), nouveauY(positionY) {
    
    shared_ptr<Point> point = dynamic_pointer_cast<Point>(orthese.getElements()[id]);

    ancienX = point->getX();
    ancienY = point->getY();
}

void CommandeDeplacement::executer() const {
    orthese.deplacerPoint(id, nouveauX, nouveauY);
}

void CommandeDeplacement::annuler() const {
    orthese.deplacerPoint(id, ancienX, ancienY);
}

void GestionCommande::setCommande(shared_ptr<Commande> commande) {
    commandeSuivante = commande;
}

void GestionCommande::executer() {
    commandeSuivante->executer();
    ordreAnnulation.push_back(commandeSuivante);
    ordreReexecution.clear();
}

void GestionCommande::annuler() {
    if (ordreAnnulation.empty()) {
        return;
    }
    shared_ptr<Commande> commande = ordreAnnulation.back();
    commande->annuler();

    ordreAnnulation.pop_back();
    ordreReexecution.push_back(commande);
}

void GestionCommande::remettre() {
    if (ordreReexecution.empty()) {
        return;
    }
    shared_ptr<Commande> commande = ordreReexecution.back();
    commande->executer();

    ordreReexecution.pop_back();
    ordreAnnulation.push_back(commande);
}
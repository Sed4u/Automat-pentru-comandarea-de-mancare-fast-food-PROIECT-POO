#include "Staff.h"
#include "Mancare.h"
#include "Bautura.h"
#include <algorithm>
using namespace std;

Staff Staff::staffInstance;

Staff::Staff() : meniu(Meniu::get_instance()) {}

Staff::~Staff() {
    for (const auto comanda : comenzi) {
        delete comanda;
    }
    meniu = nullptr;
}

void Staff::afiseazaComenzi() const {
    cout << "-------------------------Comenzi-------------------------\n";
    for(const auto&i : comenzi) {
        i->afiseazaComanda();
        cout<<endl<<endl;
    }
    cout << "---------------------------------------------------------\n";
}

void Staff::adaugaComanda(Comanda* comanda) {
    comenzi.push_back(comanda);
}


void Staff::setStatus() {
    cout << "ID-ul comenzii pe careia doresti sa ii modifici status-ul: ";
    unsigned int id;
    cin >> id;

    Comanda* found_comanda = nullptr;

    for (auto* c : comenzi) {
        if (c->id_c == id) {
            found_comanda = c;
            break;
        }
    }

    if (found_comanda != nullptr) {
        unsigned int optiune;
        cout << "\t1. In pregatire\n";
        cout << "\t2. Gata\n";
        cout << "Optiune: ";
        cin >> optiune;

        if (optiune == 2) { // Gata
            found_comanda->status = true;
            cout << "Comanda cu ID-ul " << id << " a fost setata la Gata." << endl;
        } else if (optiune == 1) { // in pregatire
            found_comanda->status = false;
            cout << "Comanda cu ID-ul " << id << " a fost setata la In pregatire." << endl;
        }
    } else {
        cout << "Comanda cu ID-ul " << id << " nu a fost gasita!" << endl;
    }
}

void Staff::modificaElement() const {
    cout << "ID-ul elementului pe care vrei sa il modifici: ";
    unsigned int id;
    cin >> id;

    Element* found_elem = nullptr;

    for (auto* e : meniu->get_lista()) {
        if (e->getId() == id) {
            found_elem = e;
            break;
        }
    }

    if (found_elem != nullptr) {
        cout << "Vei modifica datele elementului:\n";
        cout << "Nume: " << found_elem->getNume() << ", Kcal: " << found_elem->getKcal()
             << ", Pret: " << found_elem->getPret() << " lei, ";

        if (const auto* bautura = dynamic_cast<Bautura*>(found_elem)) {
            cout << "Mililitri: " << bautura->getMililitri() << " ml" << endl;
        }
        else if (const auto* mancare = dynamic_cast<Mancare*>(found_elem)) {
            cout << "Grame: " << mancare->getGrame() << " g" << endl;
        }

        cout << "Introduceti noul nume: ";
        string nou_nume;
        if(cin.peek() == '\n')
            cin.get();
        getline(cin, nou_nume);
        found_elem->setNume(nou_nume);

        cout << "Introduceti noul numar de calorii: ";
        float nou_kcal;
        cin >> nou_kcal;
        found_elem->setKcal(nou_kcal);

        cout << "Introduceti noul pret: ";
        float nou_pret;
        cin >> nou_pret;
        found_elem->setPret(nou_pret);


        if (auto* bautura = dynamic_cast<Bautura*>(found_elem)) {
            cout << "Introduceti noul numar de mililitri: ";
            unsigned int noi_mililitri;
            cin >> noi_mililitri;
            bautura->setMililitri(noi_mililitri);
        }
        else if (auto* mancare = dynamic_cast<Mancare*>(found_elem)) {
            cout << "Introduceti noul numar de grame: ";
            unsigned int noi_grame;
            cin >> noi_grame;
            mancare->setGrame(noi_grame);
        }
    } else {
        cout << "Elementul cu ID-ul " << id << " nu a fost gasit." << endl;
    }
}


void Staff::stergeElement() const {
    cout << "ID-ul elementului pe care vrei sa il stergi: ";
    unsigned int id;
    cin >> id;

    Element* found_elem = nullptr;
    for (auto* e : meniu->get_lista()) {
        if (e->getId() == id) {
            found_elem = e;
            break;
        }
    }

    if (found_elem != nullptr) {
        meniu->get_lista().erase(std::remove_if(meniu->get_lista().begin(), meniu->get_lista().end(), [found_elem](const Element* e) { return e == found_elem; }), meniu->get_lista().end());
        delete found_elem;

        cout << "Elementul cu ID-ul " << id << " a fost sters!" << endl;
    } else {
        cout << "Elementul cu ID-ul " << id << " nu a fost gasit!" << endl;
    }
}

void Staff::afiseazaStatusComenzi() const {
    cout<<"---------Comenzi---------"<<endl;
    for(const auto& i : comenzi) {
        cout<<"Comanda "<<i->id_c<<" - ";
        i->status?(cout<<"GATA!"):(cout<<"IN PREGATIRE...");
        cout<<endl;
    }
    cout<<"-------------------------"<<endl;
}


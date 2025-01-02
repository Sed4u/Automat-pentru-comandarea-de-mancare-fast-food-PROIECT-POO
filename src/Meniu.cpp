#include <iostream>
#include "Meniu.h"
#include "Mancare.h"
#include "Bautura.h"
#include "Element.h"
using namespace std;


vector<Element*>& Meniu::get_lista() {
    return lista;
}

void Meniu::afisare_meniu() const {
    cout << "------------------------------Meniu------------------------------\n";
    cout << "Mancare:\n";
    for (const auto& element : lista) {
        if (dynamic_cast<Mancare*>(element)) {
            cout << *element << endl;
        }
    }
    cout << "\nBauturi:\n";
    for (const auto& element : lista) {
        if (dynamic_cast<Bautura*>(element)) {
            cout << *element << endl;
        }
    }
    cout << "-----------------------------------------------------------------\n";
}



Meniu::~Meniu() {
    for (const auto* elem : lista) {
        delete elem;
    }
    lista.clear();
}

Meniu* Meniu::instance=nullptr;
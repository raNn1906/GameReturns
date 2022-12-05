#pragma once
#include <iostream>
#include <windows.h>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <stdlib.h>

using namespace std;

void Miecz() { cout << "MIECZ"; }

void Sztylet() { cout << "SZTYLET"; }

void HP_potion(int& hp) {
    cout << "Zostales uleczony (+20hp)\n";
    hp += 20;
}

void MANA_Potion(int& mp) {
    cout << "Zostala Ci dodana mana (+20mp)\n";
    mp += 20;
}

void Helm() { cout << "HELM"; }

void Napiersnik() { cout << "NAPIER"; }

void Spodnie() { cout << "SPODNIE"; }

void Buty() { cout << "BUTY"; }

void Luk() { cout << "LUK"; }

void Rozczka() { cout << "ROZCZKA"; }

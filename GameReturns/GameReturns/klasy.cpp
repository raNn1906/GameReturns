#include <iostream>
#include <cmath>
#include "przedmioty.h"
using namespace std;
// Glówna klasa
class Gracz {
public:
    int wsp_x, wsp_y, lvl, xp, hp, mana, zwinnosc, kasa;
    string imie;
    Gracz();
    void ruch(char interakcja, int rozmiar_map);
    void podaj_imie();
    void lvl_up();
};

Gracz::Gracz() {
    wsp_x = 0;
    wsp_y = 0;
    lvl = 1;
    xp = 0;
    mana = 0;
    imie = "";
    kasa = 200;
}

void Gracz::ruch(char interakcja, int rozmiar_map) {
    switch (interakcja) {
    case 'w': if (wsp_y > 0)wsp_y--;
            else cout << "Koniec mapy\n";
        break;
    case 's': if (wsp_y < rozmiar_map - 1)wsp_y++;
            else cout << "Koniec mapy\n";
        break;
    case 'a': if (wsp_x > 0)wsp_x--;
            else cout << "Koniec mapy\n";
        break;
    case 'd': if (wsp_x < rozmiar_map - 1)wsp_x++;
            else cout << "Koniec mapy\n";
        break;
    }
}

void Gracz::podaj_imie() {
    string nazwa;
    cout << "Podaj imie swojego bohatera: ";
    cin >> nazwa;
    imie += " " + nazwa;
}

void Gracz::lvl_up() {

    float wynik = 50 * pow(2, lvl - 1);
    if (lvl > 1) {
        if (xp >= 50 * wynik) {
            lvl++;
            xp -= 50 * wynik;
        }
    }
    else
        if (xp >= 50) {
            lvl++;
            xp -= 50;
        }
}
// Klasy postaci

// Wojownik

class Wojownik : public Gracz {
public:
    Wojownik();
};

Wojownik::Wojownik() {
    hp = 200;
    mana = 50;
    zwinnosc = 10;
    imie += "Wojownik";
}

// Mag

class Mag : public Gracz {
public:
    Mag();
};

Mag::Mag() {
    hp = 100;
    mana = 200;
    zwinnosc = 50;
    imie += "Mag";
}

// Z³odziej

class Zlodziej : public Gracz {
public:
    Zlodziej();
};

Zlodziej::Zlodziej() {
    hp = 50;
    mana = 100;
    zwinnosc = 100;
    imie += "Zlodziej";
}

// EKWIPUNEK

class Ekwipunek {
public:
    int calosc[20];
    int zalozone[5];
    int ile_calosc;
    //int ile_zal;
    Ekwipunek();
    void zbieranie();
    void wypisywanie(int& hp, int& mp);
    bool czy_pelny();
    void uzywanie(int& hp, int& mp);
};


Ekwipunek::Ekwipunek() {
    for (int i = 0; i <= 19; i++) {
        calosc[i] = 0;
    }
    for (int i = 0; i <= 4; i++) {
        zalozone[i] = 0;
    }
    ile_calosc = 0;
}

void Ekwipunek::wypisywanie(int& hp, int& mp) {
    cout << "\nEkwipunek:\n";
    string str_zawartosc = "x";
    ifstream wczytaj_bron("przedmioty.data");
    for (int i = 0; i <= 19; i++) {
        ifstream wczytaj_bron("przedmioty.data");
        for (int j = 0; j < calosc[i]; j++) {
            wczytaj_bron >> str_zawartosc;
        }
        wczytaj_bron.close();
        cout << i + 1 << ". " << str_zawartosc << "\n";
        str_zawartosc = "x";
    }
    cout << "\n";

    cout << "Zalozone: ";
    for (int i = 0; i <= 4; i++) {
        cout << str_zawartosc << " ";
    }
    cout << "\n";
    uzywanie(hp, mp);
    system("pause");
}

bool Ekwipunek::czy_pelny() {
    for (int i = 0; i <= 19; i++) {
        if (calosc[i] == 0)return true;
    }
    return false;
}

void Ekwipunek::uzywanie(int& hp, int& mp) {
    string str_zawartosc;
    int interakcja;
interakcja:
    cout << "Wybierz przedmiot lub jesli chcesz przejsc dalej wcisnij 0 :";
    cin >> interakcja;
    if (interakcja != 0) {
        switch (calosc[interakcja - 1]) {
        case 1: Miecz(); break;
        case 2: Sztylet(); break;
        case 3: HP_potion(hp); break;
        case 4: MANA_Potion(mp); break;
        case 5: Helm(); break;
        case 6: Napiersnik(); break;
        case 7: Spodnie(); break;
        case 8: Buty(); break;
        case 9: Luk(); break;
        case 10: Rozczka(); break;
        default: cout << "Nie ma takiego przedmiotu\n"; goto interakcja;
        }
        calosc[interakcja - 1] = 0;
    }
}
//CHEST

class Chest {
public:
    int zawartosc;
    void rand_chest();
    void open(int calosc[20], int& ile_calosc);
};


void Chest::rand_chest() {
    zawartosc = rand() % 4 + 3;

}

void Chest::open(int calosc[20], int& ile_calosc) {
    cout << "W skrzyni znajduje sie ";
    string str_zawartosc;
    ifstream wczytaj_bron("przedmioty.data");
    for (int i = 0; i < zawartosc; i++) {
        wczytaj_bron >> str_zawartosc;
    }
    cout << str_zawartosc << "!\n";
    Sleep(500);
    cout << "Czy chesz podniesc? (t/n)";
    char q;
    cin >> q;
    switch (q) {
    case 't':
        calosc[ile_calosc] = zawartosc;
        ile_calosc++;
        break;
    case 'n': break;

    }
    wczytaj_bron.close();

}

class Kupiec {
public:
    Kupiec();
    void sklep(int& kasa);
};

Kupiec::Kupiec() {

}

void Kupiec::sklep(int& kasa) {
    system("cls");
    cout << "Zloto: " << kasa;
    cout << "\nJestes w sklepie! :O\n";
    system("pause");
}

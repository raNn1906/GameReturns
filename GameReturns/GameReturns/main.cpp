#include <iostream>
#include <windows.h>
#include <ctime>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <conio.h>
#include <cmath>
#include "funkcje.h"
#include "klasy.h"

using namespace std;

int main() {

    //USUNAC
    int hp_przeciwnika = 20;
    //USUNAC
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    kolor(hOut, FOREGROUND_RED);
    //system("mode 650");
    bool menu = true;
    int wybranaopcja = 1, rozmiar_map = 50;
    char znak;
    char interakcja;
    srand(time(NULL));

    Ekwipunek eq;
    Chest chest;
    Gracz woj;
    Kupiec kupiec;

    menu_poczatkowe(wybranaopcja, true);
    while (menu == true) {
        wybranaopcja = 1;
        while (wybranaopcja != 7) {
            if (wybranaopcja < 1) wybranaopcja++;
            if (wybranaopcja > 5) wybranaopcja--;
            menu_poczatkowe(wybranaopcja, false);
            znak = _getch();
            switch (znak)
            {
            case 13: //enter
                if (wybranaopcja == 1) interakcja = 'n';
                if (wybranaopcja == 2) interakcja = 'w';
                if (wybranaopcja == 3) interakcja = 'h';
                if (wybranaopcja == 4) interakcja = 'u';
                if (wybranaopcja == 5) interakcja = 'q';
                wybranaopcja = 7;
                break;

            case 72: //strzalka w gore
                wybranaopcja--;
                break;
            case 80: //strzalka w dol
                wybranaopcja++;
                break;
            }
        }
        switch (interakcja) {
        case 'n': {
            system("cls");
            Sleep(500);
            SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
            cout << "Podaj klase postaci: \n\t(W)ojownik \n\tMag \n\tZlodziej ";
            system("cls");
            wybranaopcja = 1;
            while (wybranaopcja != 5) {
                if (wybranaopcja < 1) wybranaopcja++;
                if (wybranaopcja > 3) wybranaopcja--;
                menu_klasy(wybranaopcja);
                znak = _getch();
                switch (znak) {
                case 13: //enter
                    if (wybranaopcja == 1) interakcja = 'w';
                    if (wybranaopcja == 2) interakcja = 'm';
                    if (wybranaopcja == 3) interakcja = 'z';
                    wybranaopcja = 5;
                    break;
                case 72: //strzalka w gore
                    wybranaopcja--;
                    break;
                case 80: //strzalka w dol
                    wybranaopcja++;
                    break;
                }
            }
            switch (interakcja) {
            case 'w': {
                Wojownik wojownik;
                woj = wojownik;
                break; }
            case 'm': {
                Mag mag;
                woj = mag;
                break; }
            case 'z': {
                Zlodziej zlodziej;
                woj = zlodziej;
                break; }
            default:
                cout << "Zle polecenie";
                Sleep(500);
            }
            woj.podaj_imie();
            cin.ignore();
            menu = false;
            break;
        }
        case 'w':
            system("cls");
            cout << "WCZYTYWANIE...";
            Sleep(1000);
            odczyt(woj.hp, woj.wsp_x, woj.wsp_y, woj.imie, woj.mana, woj.xp, woj.zwinnosc);
            menu = false;
            break;
        case 'u':
            system("cls");
            cout << "Podaj wielkosc mapy (Domyslny rozmiar = 50): ";
            cin >> rozmiar_map;
            break;
        case 'q':
            system("cls");
            cout << "Czy chcesz wyjsc?\n(T)AK\t(N)ie\n";
            cin >> interakcja;
            if (interakcja == 't') return 1;
            else break;
        case 'h': klawiszologia();
            break;
        }
    }
    //GUFNA GRA
        //int map[50][50][2];
    int*** map;
    map = new int** [rozmiar_map];
    for (int i = 0; i < rozmiar_map; i++) {
        map[i] = new int* [rozmiar_map];
        for (int j = 0; j < rozmiar_map; j++) {
            map[i][j] = new int[2];
        }
    }
    tworzenie_mapy(map, rozmiar_map);

    while (menu == false) {
        kolor(hOut, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
        system("CLS");
        cout << "Nazywasz sie " << woj.imie << "   Poziom: " << woj.lvl << "   Zloto: " << woj.kasa << "\n\n";
        cout << "Hp: " << woj.hp << "   Mana: " << woj.mana << "   Zwinnosc: " << woj.zwinnosc << "   XP: (" << woj.xp << "/" << 50 * pow(2, woj.lvl - 1) << ")\n\n";
        cout << "X = " << woj.wsp_x << "\nY = " << woj.wsp_y << "\n\n";
        wypisywanie_pola(map, woj.wsp_x, woj.wsp_y);

        if (map[woj.wsp_x][woj.wsp_y][1] == 2) { cout << "\nZostales zaatakowany!\n"; Sleep(1000); goto walka; }
        //wypisywanie_mapy( map, rozmiar_map );
        interakcja = _getch();
        woj.ruch(interakcja, rozmiar_map);
        switch (interakcja) {
        case 'z': zapis(woj.hp, woj.wsp_x, woj.wsp_y, woj.imie, woj.mana, woj.xp, woj.zwinnosc);
        case 'e': eq.wypisywanie(woj.hp, woj.mana); break;
        case 'q': if (map[woj.wsp_x][woj.wsp_y][1] == 0) { cout << "Nie ma tutaj przeciwnika\n"; break; }
            walka:
                walka(hp_przeciwnika, woj.hp, eq.zalozone[0], woj.imie, "Szkielet", woj.xp, woj.wsp_x, woj.wsp_y, map, woj.zwinnosc, woj.wsp_x, woj.wsp_y);
                woj.lvl_up();
                break;
        case 'c':  if (map[woj.wsp_x][woj.wsp_y][0] == 2) {
            chest.rand_chest();
            chest.open(eq.calosc, eq.ile_calosc);
            map[woj.wsp_x][woj.wsp_y][0] = 1;
        }
                else { cout << "Na tm polu nie ma skrzynki!\n"; }
                break;
        case 'h':
            klawiszologia();
            break;
        case 'p': menu = true;
            break;
        case 'k': kupiec.sklep(woj.kasa);
        }
        if (woj.hp <= 0) {
            cout << " PRZEGRALES ";
            menu = true;
        }
        loading();
    }
    delete[]map;
    return 0;
}
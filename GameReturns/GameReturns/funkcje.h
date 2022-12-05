#pragma once
#include <iostream>
#include <windows.h>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <stdlib.h>

using namespace std;

void coutsleep(string s){

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Get the console handle.
    PCONSOLE_SCREEN_BUFFER_INFO lpScreenInfo = new CONSOLE_SCREEN_BUFFER_INFO(); // Create a pointer to the Screen Info pointing to a temporal screen info.
    GetConsoleScreenBufferInfo(hConsole, lpScreenInfo); // Saves the console screen info into the lpScreenInfo pointer.
    COORD NewSBSize = lpScreenInfo->dwSize; // Gets the size of the screen

    if (NewSBSize.X > s.size()){
        int newpos = ((NewSBSize.X - s.size()) / 2); // Calculate the number of spaces to center the specific text.
        for (int i = 0; i < newpos; i++) cout << " "; // Prints the spaces
    }

    for(int x = 0; x <= s.size(); x++){
        if( s[x] == '\n'){
            cout << "\n";
            continue;
        }
        cout << s[x];
        Sleep(8);
    }
}

void kolor(HANDLE hOut, WORD kolor) {
    SetConsoleTextAttribute(hOut, kolor | FOREGROUND_INTENSITY);
}

void menu_poczatkowe(int wybranaopcja, bool ktr) {
    system("cls");
    if (ktr == false) {
        cout << "            Dragon's Quest\n\n\n";

        if (wybranaopcja == 1) cout << "              (N)owa Gra\n";
        else cout << "                Nowa Gra\n";
        if (wybranaopcja == 2) cout << "              (W)czytaj\n";
        else cout << "                Wczytaj\n";
        if (wybranaopcja == 3) cout << "                (H)elp\n";
        else cout << "                  Help\n";
        if (wybranaopcja == 4) cout << "             (U)stawienia\n";
        else cout << "               Ustawienia\n";
        if (wybranaopcja == 5) cout << "               (W)yjscie\n\n\n\n";
        else cout << "                 Wyjscie\n\n\n\n";

        cout << "              Develop by\n";
        cout << "         Aleksander (raNn) Dusza\n";
        cout << "             Konrad Sniezek\n\n";
        cout << "                         PreAlpha 0.04a\n\n";

    }
    if (ktr == true) {

        coutsleep("Dragon's Quest\n\n\n");
        coutsleep("(N)owa Gra\n");
        coutsleep("Wczytaj\n");
        coutsleep("Help\n");
        coutsleep("Ustawienia\n");
        coutsleep("Wyjscie\n\n\n\n");

        coutsleep("Develop by\n");
        coutsleep("Aleksander (raNn) Dusza\n");
        coutsleep("Konrad Sniezek\n\n");
        coutsleep("         PreAlpha 0.04a\n\n");

    }

}

void menu_klasy(int wybranaopcja) {
    system("cls");
    cout << "Podaj klase postaci:\n";
    if (wybranaopcja == 1) cout << "\t(W)ojownik\n";
    else cout << "\tWojownik\n";
    if (wybranaopcja == 2) cout << "\t(M)ag\n";
    else cout << "\tMag\n";
    if (wybranaopcja == 3) cout << "\t(Z)lodziej\n";
    else cout << "\tZlodziej\n";
}

void loading() {
    for (int i = 1; i <= 80; i++)
    {
        cout << "_";
        Sleep(2);
    }
}

void klawiszologia() {
    system("CLS");
    coutsleep("KALWISZOLOGIA \n\n");
    coutsleep("w - idz w gore\n");
    coutsleep("s - idz w dol\n");
    coutsleep("a - idz w lewo\n");
    coutsleep("d - idz w prawo\n");
    coutsleep("e - otworz ekwipunek\n");
    coutsleep("q - zaatakuj przeciwnika\n");
    coutsleep("c - otworz skrzynie\n");
    coutsleep("z - zapisz i wyjdz\n\n");

    cout << "      Kliknij ENTER aby wrocic do menu";
    getchar();
}

void zapis(int hp, int wsp_x, int wsp_y, string imie, int mana, int xp, int zwinnosc) {

    ofstream zapis("save.sav");

    zapis << hp << " " << mana << " " << xp << " " << wsp_x << " " << wsp_y << " " << imie << " " << zwinnosc;
    zapis.close();
}

void odczyt(int& hp, int& wsp_x, int& wsp_y, string& imie, int& mana, int& xp, int& zwinnosc) {

    ifstream wczytywanie("save.sav");
    string pomocnicza;
    wczytywanie >> hp;
    wczytywanie >> mana;
    wczytywanie >> xp;
    wczytywanie >> wsp_x;
    wczytywanie >> wsp_y;
    wczytywanie >> imie;
    wczytywanie >> pomocnicza;
    imie += " " + pomocnicza;
    wczytywanie >> zwinnosc;
}

void random_mapy(int*** map, int rozmiar_map) {
    for (int x = 0; x <= rozmiar_map - 1; x++) {
        for (int y = 0; y <= rozmiar_map - 1; y++) {
            int skrzynka;
            skrzynka = rand() % 100 + 1;
            if (skrzynka <= 45)map[x][y][0] = 1;
            else map[x][y][0] = 2;
        }
        for (int y = 0; y <= rozmiar_map - 1; y++) {
            int potwor;
            potwor = rand() % 100 + 1;
            if (potwor <= 60)map[x][y][1] = 0;
            if (potwor <= 40)map[x][y][1] = 2;
            if (potwor <= 30)map[x][y][1] = 3;
            else map[x][y][1] = 1;
        }
    }
}

void generowanie_mapy(int*** map, int*** map1, int rozmiar_map) {
    int sciana = 0;
    for (int x = 1; x < rozmiar_map - 1; x++) {
        for (int y = 1; y < rozmiar_map - 1; y++) {
            for (int k = -1; k < 2; k++) {
                for (int j = -1; j < 2; j++) {
                    if (map[k + x][j + y][0] == 2) sciana++;
                }
            }
            if (sciana >= 4) map1[x][y][1] = 2;
            else map1[x][y][0] = 1;
            sciana = 0;
        }
    }
}

void tworzenie_mapy(int*** map, int rozmiar_map) {
    int*** map1 = new int** [rozmiar_map];
    for (int i = 0; i < rozmiar_map; i++) {
        map1[i] = new int* [rozmiar_map];
        for (int j = 0; j < rozmiar_map; j++) {
            map1[i][j] = new int[2];
        }
    }
    random_mapy(map, rozmiar_map);
    random_mapy(map1, rozmiar_map);
    for (int x = 0; x < 3; x++) {
        generowanie_mapy(map, map1, rozmiar_map);
        generowanie_mapy(map1, map, rozmiar_map);
    }
}

void wypisywanie_mapy(int*** map, int rozmiar_map) {
    cout << endl;
    for (int y = 0; y <= rozmiar_map - 1; y++) {
        for (int x = 0; x <= rozmiar_map - 1; x++) {
            if (map[x][y][0] == 1)cout << "-";
            else cout << "0";
            cout << " ";
        }
        cout << endl;
    }
}

void wypisywanie_pola(int*** map, int wsp_x, int wsp_y) {
    if (map[wsp_x][wsp_y][0] == 1) { cout << "Jestes na wolnym polu"; }
    if (map[wsp_x][wsp_y][0] == 2) { cout << "Jestes na polu ze skrzynka (c)"; }
    if (map[wsp_x][wsp_y][1] == 1) { cout << " z przeciwnikiem (q)"; }
    if (map[wsp_x][wsp_y][1] == 2) { cout << " z przeciwnikiem agresywnym"; }
    if (map[wsp_x][wsp_y][1] == 3) { cout << " na ktorym znajduje sie Kupiec (k)"; }
    cout << endl << endl;
}

void walka(int hp_przeciwnika, int& hp, int bron, string imie_postaci, string nazwa_przeciwnika, int& xp, int wsp_x, int wsp_y, int** map[], int zwinnosc, int wspx, int wspy) {
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    int dmg;
    int ucieczka;
    char czy_ucieczka;
    int losowana;
    string ktr_wiekszy;
    if (map[wspx][wspy][1] == 2) { goto atak_przeciwnika; }
    //cin.ignore();
    while (hp > 0 && hp_przeciwnika > 0) {
    atak_postaci:
        kolor(hOut, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
        losowana = 0;
        losowana = rand() % 7 + 1;
        dmg = 10;
        ucieczka = rand() % (200 / zwinnosc) + 1;

        if (hp < 0) hp = 0;
        if (hp_przeciwnika < 0) hp_przeciwnika = 0;
        //if (hp < hp_przeciwnika) ktr_wiekszy = "<";
        //if (hp == hp_przeciwnika) ktr_wiekszy = "=";
        //if (hp > hp_przeciwnika) ktr_wiekszy = ">";
        cout << "Walka czy Ucieczka (Enter/u)";
        czy_ucieczka = getchar();
        if (czy_ucieczka == 'u') {
            if (ucieczka == 1) {
                cout << "Uciekles";
                break;
            }
            else {
                cout << "\nNie Uciekles pomijajac ruch";
                Sleep(500);
                system("CLS");
                cout << imie_postaci << " " << hp << "   " << "<------" << "   " << hp_przeciwnika << " " << nazwa_przeciwnika << "\n";
                goto atak_przeciwnika;
            }
        }
        system("CLS");
        cout << imie_postaci << " " << hp << "   " << "------>" << "   " << hp_przeciwnika << " " << nazwa_przeciwnika << "\n\n";
        kolor(hOut, FOREGROUND_GREEN);
        switch (losowana)
        {
        case 1:
            cout << imie_postaci << " nie trafia!\n\n";
            break;

        case 2:
            cout << imie_postaci << " zadrapuje przeciwnika!\n\n";
            hp_przeciwnika -= (dmg * 0, 1);
            break;

        case 3:
            cout << imie_postaci << " trafia przeciwnika!\n\n";
            hp_przeciwnika -= (dmg * 0, 2);
            break;

        case 4:
            cout << imie_postaci << " zadaje srednie orazenia!\n\n";
            hp_przeciwnika -= (dmg * 0, 5);
            break;

        case 5:
            cout << imie_postaci << " obala przeciwnika!\n\n";
            hp_przeciwnika -= dmg;
            break;

        case 6:
            cout << imie_postaci << " zadaje duze obrazenia!\n\n";
            hp_przeciwnika -= (dmg * 1, 5);
            break;

        case 7:
            cout << imie_postaci << " trafia KRYYCZNIE!\n\n";
            hp_przeciwnika -= (dmg * 2);
            goto atak_postaci;
        }
    atak_przeciwnika:
        kolor(hOut, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);

        if (hp_przeciwnika < 0) hp_przeciwnika = 0;
        if (hp < 0) hp = 0;
        //if (hp < hp_przeciwnika) ktr_wiekszy = "<";
        //if (hp == hp_przeciwnika) ktr_wiekszy = "=";
        //if (hp > hp_przeciwnika) ktr_wiekszy = ">";
        if (hp_przeciwnika == 0) goto koniec_walki;
        cout << "Walka(Enter)";
        czy_ucieczka = getchar();
        system("CLS");
        cout << imie_postaci << " " << hp << "   " << "<------" << "   " << hp_przeciwnika << " " << nazwa_przeciwnika << "\n\n";


        losowana = 0;
        losowana = rand() % 7 + 1;
    nie_ucieczka:
        dmg = 5;
        kolor(hOut, FOREGROUND_RED);
        switch (losowana)
        {
        case 1:
            cout << nazwa_przeciwnika << " nie trafia!\n\n";
            break;

        case 2:
            cout << nazwa_przeciwnika << " zadrapuje przeciwnika!\n\n";
            hp -= (dmg * 0, 1);
            break;

        case 3:
            cout << nazwa_przeciwnika << " trafia przeciwnika!\n\n";
            hp -= (dmg * 0, 2);
            break;

        case 4:
            cout << nazwa_przeciwnika << " zadaje srednie orazenia!\n\n";
            hp -= (dmg * 0, 5);
            break;

        case 5:
            cout << nazwa_przeciwnika << " obala przeciwnika!\n\n";
            hp -= dmg;
            break;

        case 6:
            cout << nazwa_przeciwnika << " zadaje duze obrazenia!\n\n";
            hp -= (dmg * 1, 5);
            break;

        case 7:
            cout << nazwa_przeciwnika << " trafia KRYYCZNIE!\n\n";
            hp -= (dmg * 2);
            goto atak_przeciwnika;
        }
    }
    if (hp > 0 && ucieczka == 1) {}
    else {
        koniec_walki:
        xp += 30;
        cout << "Pokonales przeciwnika" << nazwa_przeciwnika << "!\n";
        cout << "Zdobyles 30 xp\n";
        getchar();
        map[wsp_x][wsp_y][1] = 0;
    }
    system("pause");
}


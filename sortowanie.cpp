/*
*   nazwa: sortowanie bąbelkowe
*   autor: Dominik Łempicki Kapitan
*/


#include<iostream>
#include <limits>
#include <locale>
#include <vector>
#include <fstream>
#include <string>
#define nazwa_bazy_danych "dane.txt"

using std::cout;
using std::cin;
using std::cerr;

void odczyt();
template<class T>
T wprowadz(T* ciog, ...);


template<class T>
bool posortuj(std::vector<T>& liczby, int rozmiar);
template<class T>
void zapisz(std::vector<T>& liczby, int rozmiar);



int main() {
    setlocale(LC_CTYPE, "Polish");
    cout << "Historia sortowań: \n";
    odczyt();
    int ile_liczb{ 0 };
    cout << "Ile danych liczb chcesz posortować? ";
    wprowadz(&ile_liczb);
    std::vector<int> liczby((int)ile_liczb);
    cout << "Wpisz liczby: ";
    int licznik{ 1 };
    for (auto& i : liczby) {
        cout << "Wprowadż liczbę nr." << licznik << " ";
        wprowadz(&i);
        licznik++;
    }

    posortuj(liczby, liczby.size());
    cout << "Posortowany ciąg: ";
    for (auto& i : liczby) cout << i << " ";


    return 0;
}

template<class T>
bool posortuj(std::vector<T>& liczby, int rozmiar) {
    if (rozmiar <= 1) {
        zapisz(liczby, liczby.size());
        return true;
    }
 
    bool zmiana{false};
    do {
        zmiana = false;
        for (int i{ 0 }; i < rozmiar - 1; i++) {
            try {
                if (liczby[i] < liczby[i + 1]) {
                    std::swap(liczby[i], liczby[i + 1]);
                    zmiana = true;
                }
            }
            catch (bool b) {
                std::cerr << "Błąd, poza zakresem indeksu tablicy!";
            }
        }
    } while (zmiana);
    
     
   /*
    for (int i{ 0 }; i < rozmiar - 1; i++) {
        for (int j{ 0 }; j < rozmiar - 1 - i; j++) {
            try {
                if (liczby[j] > liczby[j + 1]) {
                    std::swap(liczby[j], liczby[j + 1]);
                }
            }
            catch (bool blod) {
                cerr << "Poza indeksem!";
            }
        }
    }
    */
    zapisz(liczby, liczby.size());
}


template<class T>
void zapisz(std::vector<T>& liczby, int rozmiar) {
    std::fstream baza_danych;
    baza_danych.open(nazwa_bazy_danych, std::ios::app);
    for (auto& liczba : liczby) baza_danych << liczba << " ";
    baza_danych << '\n';
    baza_danych.close();
}

void odczyt() {
    try {
        std::fstream baza_danych;
        baza_danych.open(nazwa_bazy_danych, std::ios::in);
        if (baza_danych.is_open() && baza_danych.good()) {
            std::string txt{ "" };
            while (getline(baza_danych, txt)) {
                cout << txt << "\n";
            }
        }
    }
    catch (std::string blod) {
        cerr << "Wystąpił błąd! ";
    }
}

template<class T>
T wprowadz(T* ciog, ...) {
    while (!(cin >> *ciog)) {
        if (cin.fail()) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            cerr << "Nie walidowane dane wejściowe! Wprowadż jeszcze raz! ";
        }
    }
    return *ciog;
}

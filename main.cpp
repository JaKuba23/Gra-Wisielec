#include <bits/stdc++.h>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include <cctype>

using namespace std;

void wyswietl_abstrakcyjny_obraz(int ilosc_nieudanych_prob) {
    vector<string> nielegalnyimigrant;

    if (ilosc_nieudanych_prob == 6) {
        nielegalnyimigrant = {
            "             ",
            "             ",
            "             ",
            "             ",
            "             ",
            "______      "
        };
    } else if (ilosc_nieudanych_prob == 5) {
        nielegalnyimigrant = {
            "    _____    ",
            "   |        ",
            "   |        ",
            "   |        ",
            "   |        ",
            "___|___      "
        };
    } else if (ilosc_nieudanych_prob == 4) {
        nielegalnyimigrant = {
            "    _____    ",
            "   |     |   ",
            "   |     O   ",
            "   |         ",
            "   |         ",
            "___|___      "
        };
    } else if (ilosc_nieudanych_prob == 3) {
        nielegalnyimigrant = {
            "    _____    ",
            "   |     |   ",
            "   |     O   ",
            "   |     |   ",
            "   |         ",
            "___|___      "
        };
    } else if (ilosc_nieudanych_prob == 2) {
        nielegalnyimigrant = {
            "    _____    ",
            "   |     |   ",
            "   |     O   ",
            "   |    /|   ",
            "   |         ",
            "___|___      "
        };
    } else if (ilosc_nieudanych_prob == 1) {
        nielegalnyimigrant = {
            "    _____    ",
            "   |     |   ",
            "   |     O   ",
            "   |    /|\\ ",
            "   |         ",
            "___|___      "
        };
    } else {
        nielegalnyimigrant = {
            "    _____    ",
            "   |     |   ",
            "   |     O   ",
            "   |    /|\\ ",
            "   |    / \\ ",
            "___|___      "
        };
    }

    for (const string& linia : nielegalnyimigrant) {
        cout << linia << endl;
    }
}

vector<string> wczytaj_dane_z_pliku(const string& nazwa_pliku_z_danymi) {
    vector<string> dane_z_pliku;
    ifstream plik_z_danymi(nazwa_pliku_z_danymi);
    string linia_z_pliku;

    if (plik_z_danymi.is_open()) {
        while (getline(plik_z_danymi, linia_z_pliku)) {
            stringstream strumien_linii(linia_z_pliku);
            string pojedynczy_element;

            while (getline(strumien_linii, pojedynczy_element, ',')) {
                dane_z_pliku.push_back(pojedynczy_element);
            }
        }
        plik_z_danymi.close();
    } else {
        cout << "Error 404: File not found :(" << endl;
    }
    return dane_z_pliku;
}

int main() {
    vector<string> lista_slow = wczytaj_dane_z_pliku("wordlist.txt");

    if (lista_slow.empty()) {
        cout << "Nie udalo sie wczytac danych, koncze dzialanie :(" << endl;
        return 1;
    }

    int ilosc_slow_do_zgadniecia;
    cout << "Podaj ilosc slow do zgadniecia: ";
    cin >> ilosc_slow_do_zgadniecia;

    for (int numer_gry = 0; numer_gry < ilosc_slow_do_zgadniecia; ++numer_gry) {
        srand(time(0) + numer_gry);
        int indeks_losowego_slowa = rand() % lista_slow.size();
        string losowe_slowo = lista_slow[indeks_losowego_slowa];

        losowe_slowo.erase(remove_if(losowe_slowo.begin(), losowe_slowo.end(), [](unsigned char c) { return !isalpha(c); }), losowe_slowo.end());

        int dlugosc_losowego_slowa = losowe_slowo.length();
        string slowo_odgadniete(dlugosc_losowego_slowa, '_');
        int ilosc_prob = 6;
        vector<char> uzyte_znaki;

        while (ilosc_prob > 0 && slowo_odgadniete != losowe_slowo) {
            system("cls");
            wyswietl_abstrakcyjny_obraz(ilosc_prob);

            cout << "Slowo do zgadniecia: " << slowo_odgadniete << endl;
            cout << "Proby: " << ilosc_prob << endl;

            cout << "Uzyte znaki: ";
            for (char znak : uzyte_znaki) {
                cout << znak << " ";
            }
            cout << endl;

            string proba_uzytkownika;
            cout << "Podaj znak lub cale slowo: ";
            cin >> proba_uzytkownika;
            transform(proba_uzytkownika.begin(), proba_uzytkownika.end(), proba_uzytkownika.begin(), ::tolower);

            if (proba_uzytkownika.length() == 1) {
                char znak_uzytkownika = proba_uzytkownika[0];

                if (find(uzyte_znaki.begin(), uzyte_znaki.end(), znak_uzytkownika) != uzyte_znaki.end()) {
                    cout << "Ten znak juz byl, :(" << endl;
                    Sleep(997);
                    continue;
                }
                uzyte_znaki.push_back(znak_uzytkownika);

                bool trafiony_znak = false;
                for (int i = 0; i < dlugosc_losowego_slowa; ++i) {
                    if (tolower(losowe_slowo[i]) == znak_uzytkownika) {
                        slowo_odgadniete[i] = losowe_slowo[i];
                        trafiony_znak = true;
                    }
                }

                if (!trafiony_znak) {
                    ilosc_prob--;
                }
            } else {
                string losowe_slowo_male_litery = losowe_slowo;
                transform(losowe_slowo_male_litery.begin(), losowe_slowo_male_litery.end(), losowe_slowo_male_litery.begin(), ::tolower);

                if (proba_uzytkownika == losowe_slowo_male_litery) {
                    slowo_odgadniete = losowe_slowo;
                } else {
                    ilosc_prob = 0;
                }
            }
        }
        system("cls");
        wyswietl_abstrakcyjny_obraz(ilosc_prob);

        if (slowo_odgadniete == losowe_slowo) {
            cout << "Gratulacje, odgadles slowo: " << losowe_slowo << endl;
        } else {
            cout << "Zle, slowo to: " << losowe_slowo << endl;
        }
        Sleep(2420);
    }
    return 0;
}
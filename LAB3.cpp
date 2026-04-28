#include <iostream>
#include <string>
using namespace std;

class Osoba {
private:
    string imie, nazwisko, id, data;
    int wzrost;

public:
    Osoba() {
        imie = nazwisko = id = data = "";
        wzrost = 0;
    }

    void setImie(string v) { imie = v; }
    void setNazwisko(string v) { nazwisko = v; }
    void setId(string v) { id = v; }
    void setData(string v) { data = v; }
    void setWzrost(int v) { if (v > 0) wzrost = v; }

    string getId() { return id; }

    void wyswietl() {
        cout << id << " " << imie << " " << nazwisko
             << " " << data << " " << wzrost << "cm ";
    }

    void usun() {
        imie = nazwisko = id = data = "";
        wzrost = 0;
    }

    bool czyPuste() {
        return id == "";
    }
};

class ListaObecnosci {
private:
    Osoba* osoba;
    bool obecnosc;

public:
    ListaObecnosci() {
        osoba = nullptr;
        obecnosc = false;
    }

    void setOsoba(Osoba* o) { osoba = o; }
    void setObecnosc(bool o) { obecnosc = o; }

    Osoba* getOsoba() { return osoba; }

    bool czyPuste() {
        return osoba == nullptr;
    }

    void wyswietl() {
        if (osoba != nullptr) {
            osoba->wyswietl();
            cout << (obecnosc ? "Obecny" : "Nieobecny") << endl;
        }
    }

    void usun() {
        osoba = nullptr;
        obecnosc = false;
    }
};

class InterfejsUzytkownika {
private:
    Osoba* tablicaOsob;
    int iloscOsob;

    ListaObecnosci* tablicaList;
    int iloscList;

public:
    InterfejsUzytkownika(Osoba* o, int io, ListaObecnosci* l, int il) {
        tablicaOsob = o;
        iloscOsob = io;
        tablicaList = l;
        iloscList = il;
    }

    void dodajOsobe() {
        string imie, nazwisko, id, data;
        int wzrost;

        cin >> id >> imie >> nazwisko >> data >> wzrost;

        for (int i = 0; i < iloscOsob; i++) {
            if (tablicaOsob[i].czyPuste()) {
                tablicaOsob[i].setId(id);
                tablicaOsob[i].setImie(imie);
                tablicaOsob[i].setNazwisko(nazwisko);
                tablicaOsob[i].setData(data);
                tablicaOsob[i].setWzrost(wzrost);
                break;
            }
        }
    } 
    void dodajListe() {
        for (int i = 0; i < iloscList; i++) {
            if (tablicaList[i].czyPuste()) {
                cout << "Lista gotowa na indexie " << i << endl;
                break;
            }
        }
    }

    void dodajDoListy() {
        string id;
        int nrListy;

        cin >> id >> nrListy;

        for (int i = 0; i < iloscOsob; i++) {
            if (tablicaOsob[i].getId() == id) {
                tablicaList[nrListy].setOsoba(&tablicaOsob[i]);
                break;
            }
        }
    }
    void ustawObecnosc() {
        int nrListy;
        bool ob;

        cin >> nrListy >> ob;
        tablicaList[nrListy].setObecnosc(ob);
    }

    void usunZListy() {
        int nrListy;
        cin >> nrListy;
        tablicaList[nrListy].usun();
    }

    void edytujOsobe() {
        string id, imie, nazwisko, data;
        int wzrost;

        cin >> id >> imie >> nazwisko >> data >> wzrost;

        for (int i = 0; i < iloscOsob; i++) {
            if (tablicaOsob[i].getId() == id) {
                tablicaOsob[i].setImie(imie);
                tablicaOsob[i].setNazwisko(nazwisko);
                tablicaOsob[i].setData(data);
                tablicaOsob[i].setWzrost(wzrost);
                break;
            }
        }
    }

    void wyswietl() {
        for (int i = 0; i <= iloscList; i++) {
            tablicaList[i].wyswietl();
        }
    }

    void loop() {
        int wybor;

        do {
            cout << "\n1 dodaj osobe\n";
            cout << "2 dodaj liste\n";
            cout << "3 dodaj osobe do listy\n";
            cout << "4 ustaw obecnosc\n";
            cout << "5 usun z listy\n";
            cout << "6 edytuj osobe\n";
            cout << "7 wyswietl\n";
            cout << "0 wyjscie\n";

            cin >> wybor;

            switch (wybor) {
                case 1: dodajOsobe(); break;
                case 2: dodajListe(); break;
                case 3: dodajDoListy(); break;
                case 4: ustawObecnosc(); break;
                case 5: usunZListy(); break;
                case 6: edytujOsobe(); break;
                case 7: wyswietl(); break;
            }

        } while (wybor != 0);
    }
};

int main() {
    Osoba tablicaOsob[10];
    ListaObecnosci tablicaList[10];

    InterfejsUzytkownika ui(tablicaOsob, 10, tablicaList, 10);
    ui.loop();

    return 0;
}
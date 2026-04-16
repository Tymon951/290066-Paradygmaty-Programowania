#include <iostream>
#include <string>
using namespace std;

class Osoba {
private:
    string imie;
    string nazwisko;
    string id;
    string data;
    int wzrost;

public:
    Osoba() {
        imie = "";
        nazwisko = "";
        id = "";
        data = "";
        wzrost = 0;
    }


    void setImie(string _imie) {
        imie = _imie;
    }

    void setNazwisko(string _nazwisko) {
        nazwisko = _nazwisko;
    }

    void setId(string _id) {
        id = _id;
    }

    void setData(string _data) {
        data = _data;
    }

    void setWzrost(int _wzrost) {
        if (_wzrost > 0)
            wzrost = _wzrost;
    }

  
    string getId() {
        return id;
    }

    string getImie() {
        return imie;
    }

    string getNazwisko() {
        return nazwisko;
    }

    string getData() {
        return data;
    }

    int getWzrost() {
        return wzrost;
    }

    bool czyPuste() {
        return id == "";
    }

    void wyswietl(bool obecnosc) {
        if (id != "") {
            cout << id << " "
                 << imie << " "
                 << nazwisko << " "
                 << data << " "
                 << wzrost << "cm "
                 << (obecnosc ? "Obecny" : "Nieobecny")
                 << endl;
        }
    }

    void usun() {
        imie = "";
        nazwisko = "";
        id = "";
        data = "";
        wzrost = 0;
    }
};



void dodaj_osobe(Osoba *uczen) {
    string imie, nazwisko, id, data;
    int wzrost;

    cin >> id >> imie >> nazwisko >> data >> wzrost;

    for (int i = 0; i < 10; i++) {
        if (uczen[i].czyPuste()) {
            uczen[i].setId(id);
            uczen[i].setImie(imie);
            uczen[i].setNazwisko(nazwisko);
            uczen[i].setData(data);
            uczen[i].setWzrost(wzrost);
            break;
        }
    }
}

void ustaw_obecnosc(Osoba *uczen, bool *tabObecnosc) {
    string id;
    bool obecnosc;

    cin >> id >> obecnosc;

    for (int i = 0; i < 10; i++) {
        if (uczen[i].getId() == id) {
            tabObecnosc[i] = obecnosc;
            break;
        }
    }
}

void wyswietl(Osoba *uczen, bool *tabObecnosc) {
    for (int i = 0; i < 10; i++) {
        uczen[i].wyswietl(tabObecnosc[i]);
    }
}

void usun(Osoba *uczen, bool *tabObecnosc) {
    string id;
    cin >> id;

    for (int i = 0; i < 10; i++) {
        if (uczen[i].getId() == id) {
            uczen[i].usun();
            tabObecnosc[i] = false;
            break;
        }
    }
}

void edytuj(Osoba *uczen, bool *tabObecnosc) {
    string id, imie, nazwisko, data;
    int wzrost;
    bool obecnosc;

    cin >> id >> imie >> nazwisko >> data >> wzrost >> obecnosc;

    for (int i = 0; i < 10; i++) {
        if (uczen[i].getId() == id) {
            uczen[i].setImie(imie);
            uczen[i].setNazwisko(nazwisko);
            uczen[i].setData(data);
            uczen[i].setWzrost(wzrost);
            tabObecnosc[i] = obecnosc;
            break;
        }
    }
}



int main() {
    Osoba uczen[10];
    bool tabObecnosc[10] = {};

    int wybor;

    do {
        cout << "\n1 dodaj osobe\n";
        cout << "2 ustaw obecnosc\n";
        cout << "3 wyswietl\n";
        cout << "4 usun\n";
        cout << "5 edytuj\n";
        cout << "0 wyjscie\n";

        cin >> wybor;

        switch (wybor) {
        case 1:
            dodaj_osobe(uczen);
            break;
        case 2:
            ustaw_obecnosc(uczen, tabObecnosc);
            break;
        case 3:
            wyswietl(uczen, tabObecnosc);
            break;
        case 4:
            usun(uczen, tabObecnosc);
            break;
        case 5:
            edytuj(uczen, tabObecnosc);
            break;
        }

    } while (wybor != 0);

    return 0;
}
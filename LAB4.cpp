#include <iostream>
#include <string>
using namespace std;

class Osoba {
public:
    string imie, nazwisko, id, data;
    int wzrost;
    int typ;

    Osoba(string i, string n, string _id, string d, int w) {
        imie = i;
        nazwisko = n;
        id = _id;
        data = d;
        wzrost = w;
        typ = 0;
    }

    virtual void wyswietl() {
        cout << id << " "
             << imie << " "
             << nazwisko << " "
             << data << " "
             << wzrost << "cm ";
    }
};

class Student : public Osoba {
public:
    string indeks;

    Student(string i, string n, string _id, string d, int w, string ind)
        : Osoba(i, n, _id, d, w) {
        indeks = ind;
        typ = 1;
    }

    void wyswietl() override {
        Osoba::wyswietl();
        cout << "Indeks: " << indeks << " ";
    }
};

class Stazysta : public Osoba {
public:
    string dzial;

    Stazysta(string i, string n, string _id, string d, int w, string dz)
        : Osoba(i, n, _id, d, w) {
        dzial = dz;
        typ = 2;
    }

    void wyswietl() override {
        Osoba::wyswietl();
        cout << "Dzial: " << dzial << " ";
    }
};

class ListaObecnosci {
private:
    Osoba **tabOsob;
    bool *tabObecny;
    int ilosc;
    int max;

public:
    ListaObecnosci(int rozmiar = 10) {
        max = rozmiar;
        ilosc = 0;

        tabOsob = new Osoba*[max];
        tabObecny = new bool[max];
    }

    void dodaj(Osoba *os) {
        if (ilosc < max) {
            tabOsob[ilosc] = os;
            tabObecny[ilosc] = false;
            ilosc++;
        }
    }

    void ustawObecnosc(string id, bool stan) {
        for (int i = 0; i < ilosc; i++) {
            if (tabOsob[i]->id == id) {
                tabObecny[i] = stan;
            }
        }
    }

    void usunZListy(string id) {
        for (int i = 0; i < ilosc; i++) {
            if (tabOsob[i]->id == id) {
                for (int j = i; j < ilosc - 1; j++) {
                    tabOsob[j] = tabOsob[j + 1];
                    tabObecny[j] = tabObecny[j + 1];
                }
                ilosc--;
                break;
            }
        }
    }

    void wyswietl() {
        for (int i = 0; i < ilosc; i++) {
            tabOsob[i]->wyswietl();

            if (tabObecny[i])
                cout << "Obecny";
            else
                cout << "Nieobecny";

            cout << endl;
        }
    }
};

class InterfejsUzytkownika {
private:
    Osoba **tablicaOsob;
    int iloscOsob;

    ListaObecnosci **tablicaList;
    int iloscList;

public:
    InterfejsUzytkownika() {
        tablicaOsob = new Osoba*[100];
        iloscOsob = 0;

        tablicaList = new ListaObecnosci*[10];
        iloscList = 0;
    }

    void loop() {
        int wybor;

        do {
            cout << "\n1 dodaj osobe\n";
            cout << "2 dodaj studenta\n";
            cout << "3 dodaj stazyste\n";
            cout << "4 dodaj liste\n";
            cout << "5 dodaj osobe do listy\n";
            cout << "6 ustaw obecnosc\n";
            cout << "7 usun z listy\n";
            cout << "8 wyswietl liste\n";
            cout << "0 wyjscie\n";

            cin >> wybor;

            switch (wybor) {

            case 1: {
                string i,n,id,d;
                int w;
                cin >> i >> n >> id >> d >> w;

                tablicaOsob[iloscOsob++] =
                    new Osoba(i,n,id,d,w);
                break;
            }

            case 2: {
                string i,n,id,d,ind;
                int w;
                cin >> i >> n >> id >> d >> w >> ind;

                tablicaOsob[iloscOsob++] =
                    new Student(i,n,id,d,w,ind);
                break;
            }

            case 3: {
                string i,n,id,d,dz;
                int w;
                cin >> i >> n >> id >> d >> w >> dz;

                tablicaOsob[iloscOsob++] =
                    new Stazysta(i,n,id,d,w,dz);
                break;
            }

            case 4:
                tablicaList[iloscList++] =
                    new ListaObecnosci();
                break;

            case 5: {
                int nr;
                string id;
                cin >> nr >> id;

                if (nr < iloscList) {
                    for (int i=0;i<iloscOsob;i++) {
                        if (tablicaOsob[i]->id == id) {
                            tablicaList[nr]->dodaj(tablicaOsob[i]);
                        }
                    }
                }
                break;
            }

            case 6: {
                int nr;
                string id;
                bool stan;

                cin >> nr >> id >> stan;

                if (nr < iloscList)
                    tablicaList[nr]->ustawObecnosc(id, stan);

                break;
            }

            case 7: {
                int nr;
                string id;

                cin >> nr >> id;

                if (nr < iloscList)
                    tablicaList[nr]->usunZListy(id);

                break;
            }

            case 8: {
                int nr;
                cin >> nr;

                if (nr < iloscList)
                    tablicaList[nr]->wyswietl();

                break;
            }
            }
        }
        while (wybor != 0);
    }
};

int main() {
    InterfejsUzytkownika ui;
    ui.loop();
    return 0;
}
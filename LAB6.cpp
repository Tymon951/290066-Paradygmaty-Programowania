#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class serializable {
public:
    virtual void wyswietl() = 0;
    virtual ~serializable() {}
};

class Osoba : public serializable {
public:
    string imie, nazwisko, id, data;
    int wzrost;
    int typ;

    Osoba(string i, string n, string _id, string d, int w) {
        imie = i; nazwisko = n; id = _id; data = d; wzrost = w; typ = 0;
    }

    void wyswietl() override {
        cout << id << " " << imie << " " << nazwisko << " " << data << " " << wzrost << "cm ";
    }
    
    virtual ~Osoba() {}
};

class Student : public Osoba {
public:
    string indeks;
    Student(string i, string n, string _id, string d, int w, string ind)
        : Osoba(i, n, _id, d, w) { indeks = ind; typ = 1; }

    void wyswietl() override {
        Osoba::wyswietl();
        cout << "Indeks: " << indeks << " ";
    }
};

class Stazysta : public Osoba {
public:
    string dzial;
    Stazysta(string i, string n, string _id, string d, int w, string dz)
        : Osoba(i, n, _id, d, w) { dzial = dz; typ = 2; }

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
        max = rozmiar; ilosc = 0;
        tabOsob = new Osoba*[max];
        tabObecny = new bool[max];
    }

    ~ListaObecnosci() {
        delete[] tabOsob;
        delete[] tabObecny;
    }

    void dodaj(Osoba *os) {
        if (ilosc < max) {
            tabOsob[ilosc] = os;
            tabObecny[ilosc] = false;
            ilosc++;
        } else {
            cout << "Lista jest pelna!" << endl;
        }
    }

    void ustawObecnosc(string id, bool stan) {
        for (int i = 0; i < ilosc; i++) {
            if (tabOsob[i]->id == id) { tabObecny[i] = stan; }
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
            cout << (tabObecny[i] ? "Obecny" : "Nieobecny") << endl;
        }
    }

    void zapiszListe(string nazwaPliku) {
        ofstream plik(nazwaPliku, ios::app);
        if (!plik) return;
        for (int i = 0; i < ilosc; i++) {
            plik << tabOsob[i]->id << " " << tabOsob[i]->imie << " " << tabOsob[i]->nazwisko << " " 
                 << tabOsob[i]->data << " " << tabOsob[i]->wzrost << " " 
                 << (tabObecny[i] ? "Obecny" : "Nieobecny") << endl;
        }
        cout << "Dopisano liste do: " << nazwaPliku << endl;
    }

    // Zmiana: dodano ios::app
    void zapiszOsobe(string id, string nazwaPliku) {
        ofstream plik(nazwaPliku, ios::app);
        for (int i = 0; i < ilosc; i++) {
            if (tabOsob[i]->id == id) {
                plik << tabOsob[i]->id << " " << tabOsob[i]->imie << " " << tabOsob[i]->nazwisko << " " 
                     << tabOsob[i]->data << " " << tabOsob[i]->wzrost << " " 
                     << (tabObecny[i] ? "Obecny" : "Nieobecny") << endl;
                cout << "Dopisano osobe do: " << nazwaPliku << endl;
                return;
            }
        }
        cout << "Nie znaleziono osoby o ID: " << id << endl;
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
        tablicaOsob = new Osoba*[100]; iloscOsob = 0;
        tablicaList = new ListaObecnosci*[10]; iloscList = 0;
    }

    ~InterfejsUzytkownika() {
        for(int i=0; i<iloscOsob; ++i) delete tablicaOsob[i];
        delete[] tablicaOsob;
        for(int i=0; i<iloscList; ++i) delete tablicaList[i];
        delete[] tablicaList;
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
            cout << "9 zapisz cala liste\n";
            cout << "10 zapisz osobe\n";
            cout << "0 wyjscie\n";
            cin >> wybor;
            switch (wybor) {
                case 1: 
                { string i,n,id,d; 
                    int w; cin >> i >> n >> id >> d >> w; 
                    tablicaOsob[iloscOsob++] = new Osoba(i,n,id,d,w); 
                    break; 
                }
                case 2: 
                { string i,n,id,d,ind; 
                    int w; 
                    cin >> i >> n >> id >> d >> w >> ind; 
                    tablicaOsob[iloscOsob++] = new Student(i,n,id,d,w,ind); 
                    break; 
                }
                case 3: 
                { string i,n,id,d,dz; 
                    int w; 
                    cin >> i >> n >> id >> d >> w >> dz; 
                    tablicaOsob[iloscOsob++] = new Stazysta(i,n,id,d,w,dz); 
                    break; 
                }
                case 4: 
                tablicaList[iloscList++] = new ListaObecnosci(); 
                break;
                case 5: 
                { int nr; 
                    string id; 
                    cin >> nr >> id; 
                    for(int i=0; i<iloscOsob; i++) 
                    if(tablicaOsob[i]->id == id) 
                    tablicaList[nr]->dodaj(tablicaOsob[i]); 
                    break; 
                }
                case 6: 
                { 
                    int nr; 
                    string id; 
                    bool stan; 
                    cin >> nr >> id >> stan; 
                    tablicaList[nr]->ustawObecnosc(id, stan); 
                    break; 
                }
                case 7: 
                { 
                    int nr; 
                    string id; 
                    cin >> nr >> id; 
                    tablicaList[nr]->usunZListy(id); 
                    break; 
                }
                case 8: 
                { 
                    int nr; 
                    cin >> nr; 
                    tablicaList[nr]->wyswietl(); 
                    break; 
                }
                case 9: 
                { 
                    int nr; 
                    string n; 
                    cin >> nr >> n; 
                    tablicaList[nr]->zapiszListe(n); 
                    break; 
                }
                case 10: 
                { 
                    int nr; 
                    string id, n; 
                    cin >> nr >> id >> n; 
                    tablicaList[nr]->zapiszOsobe(id, n); 
                    break; 
                }
            }
        } while (wybor != 0);
    }
};

int main() {
    InterfejsUzytkownika ui;
    ui.loop();
    return 0;
}
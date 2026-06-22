#include <iostream>
#include <string>
#include <fstream>
#include <map>

using namespace std;

// ================= INTERFEJSY =================

class serializable {
public:
    virtual void wyswietl() = 0;
    virtual ~serializable() {}
};

class IExportowalny {
public:
    virtual map<string,string> eksportuj() = 0;
};

class IExporter {
public:
    virtual void wykonaj_export(
        IExportowalny* obiekt,
        string nazwapliku) = 0;

    virtual ~IExporter() {}
};

// ================= OSOBA =================

class Osoba : public IExportowalny {
public:
    string imie, nazwisko, id, data, wzrost;
    int typ;

    Osoba(string i, string n, string _id, string d, string w) {
        imie = i;
        nazwisko = n;
        id = _id;
        data = d;
        wzrost = w;
        typ = 0;
    }

    map<string, string> eksportuj() override {
        map<string, string> dane;

        dane["imie"] = imie;
        dane["nazwisko"] = nazwisko;
        dane["id"] = id;
        dane["data"] = data;
        dane["wzrost"] = wzrost;

        return dane;
    }

    virtual void wyswietl() {
        cout << id << " "
             << imie << " "
             << nazwisko << " "
             << data << " "
             << wzrost << "cm ";
    }

    virtual ~Osoba() {}
};

// ================= STUDENT =================

class Student : public Osoba {
public:
    string indeks;

    Student(string i, string n, string _id, string d, string w, string ind)
        : Osoba(i, n, _id, d, w) {
        indeks = ind;
        typ = 1;
    }

    map<string, string> eksportuj() override {
        map<string, string> dane = Osoba::eksportuj();
        dane["indeks"] = indeks;
        return dane;
    }

    void wyswietl() override {
        Osoba::wyswietl();
        cout << "Indeks: " << indeks << " ";
    }
};

// ================= STAŻYSTA =================

class Stazysta : public Osoba {
public:
    string dzial;

    Stazysta(string i, string n, string _id, string d, string w, string dz)
        : Osoba(i, n, _id, d, w) {
        dzial = dz;
        typ = 2;
    }

    map<string, string> eksportuj() override {
        map<string, string> dane = Osoba::eksportuj();
        dane["dzial"] = dzial;
        return dane;
    }

    void wyswietl() override {
        Osoba::wyswietl();
        cout << "Dzial: " << dzial << " ";
    }
};

// ================= EXPORTER TXT =================

class ExporterTXT : public IExporter {
public:
    void wykonaj_export(IExportowalny* obiekt,
                         string nazwapliku) override {

        ofstream plik(nazwapliku + ".txt");

        map<string,string> dane = obiekt->eksportuj();

        for(auto& para : dane) {
            plik << para.first << " " << para.second << endl;
        }

        plik.close();
    }
};

// ================= EXPORTER CSV =================

class ExporterCSV : public IExporter {
public:
    void wykonaj_export(IExportowalny* obiekt,
                         string nazwapliku) override {

        ofstream plik(nazwapliku + ".csv");

        map<string,string> dane = obiekt->eksportuj();

        // nagłówki
        for(auto& para : dane)
            plik << para.first << ",";

        plik << endl;

        // wartości
        for(auto& para : dane)
            plik << para.second << ",";

        plik << endl;

        plik.close();
    }
};

// ================= LISTA OBECNOŚCI =================

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

    ~ListaObecnosci() {
        delete[] tabOsob;
        delete[] tabObecny;
    }

    void dodaj(Osoba *os) {
        if (ilosc < max) {
            tabOsob[ilosc] = os;
            tabObecny[ilosc] = false;
            ilosc++;
        }
    }

    void ustawObecnosc(string id, bool stan) {
        for (int i = 0; i < ilosc; i++)
            if (tabOsob[i]->id == id)
                tabObecny[i] = stan;
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

        for (int i = 0; i < ilosc; i++) {
            plik << tabOsob[i]->id << " "
                 << tabOsob[i]->imie << " "
                 << tabOsob[i]->nazwisko << " "
                 << tabOsob[i]->data << " "
                 << tabOsob[i]->wzrost << " "
                 << (tabObecny[i] ? "Obecny" : "Nieobecny")
                 << endl;
        }
    }

    void zapiszOsobe(string id, IExporter* exporter, string nazwaPliku) {
        for (int i = 0; i < ilosc; i++) {
            if (tabOsob[i]->id == id) {
                exporter->wykonaj_export(tabOsob[i], nazwaPliku);
                return;
            }
        }
    }
};

// ================= INTERFEJS =================

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
            cout << "9 zapisz cala liste\n";
            cout << "10 zapisz osobe\n";
            cout << "0 wyjscie\n";

            cin >> wybor;

            switch (wybor) {

            case 1: {
                string i,n,id,d,w;
                cin >> i >> n >> id >> d >> w;
                tablicaOsob[iloscOsob++] = new Osoba(i,n,id,d,w);
                break;
            }

            case 2: {
                string i,n,id,d,w,ind;
                cin >> i >> n >> id >> d >> w >> ind;
                tablicaOsob[iloscOsob++] = new Student(i,n,id,d,w,ind);
                break;
            }

            case 3: {
                string i,n,id,d,w,dz;
                cin >> i >> n >> id >> d >> w >> dz;
                tablicaOsob[iloscOsob++] = new Stazysta(i,n,id,d,w,dz);
                break;
            }

            case 4:
                tablicaList[iloscList++] = new ListaObecnosci();
                break;

            case 5: {
                int nr;
                string id;
                cin >> nr >> id;

                for (int i = 0; i < iloscOsob; i++)
                    if (tablicaOsob[i]->id == id)
                        tablicaList[nr]->dodaj(tablicaOsob[i]);

                break;
            }

            case 6: {
                int nr;
                string id;
                bool stan;
                cin >> nr >> id >> stan;
                tablicaList[nr]->ustawObecnosc(id, stan);
                break;
            }

            case 7: {
                int nr;
                string id;
                cin >> nr >> id;
                tablicaList[nr]->usunZListy(id);
                break;
            }

            case 8: {
                int nr;
                cin >> nr;
                tablicaList[nr]->wyswietl();
                break;
            }

            case 9: {
                int nr;
                string n;
                cin >> nr >> n;
                tablicaList[nr]->zapiszListe(n);
                break;
            }

            case 10: {
                int nr;
                string id, n;
                int typ;

                cin >> nr >> id >> n >> typ;

                if (typ == 1) {
                    ExporterTXT txt;
                    tablicaList[nr]->zapiszOsobe(id, &txt, n);
                } else {
                    ExporterCSV csv;
                    tablicaList[nr]->zapiszOsobe(id, &csv, n);
                }

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
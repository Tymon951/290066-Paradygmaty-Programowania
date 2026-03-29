#include <iostream>
#include <string>
using namespace std;

void dodaj_osobe_id(string *tabNazwiska, string osoba, string *tabId, string id) {
    for (int i = 0; i < 10; i++) {
        if (tabNazwiska[i] == "" && tabId[i]=="") {
            tabId[i]=id;
            tabNazwiska[i] = osoba;
           
            break;
        }
    }
}



void ustaw_obecnosc(string *tabId, bool *tabObecnosc, string id, bool obecnosc) {
    for (int i = 0; i < 10; i++) {
        if (tabId[i] == id) {
            tabObecnosc[i] = obecnosc;
            break;
        }
    }
}

void wyswietl(string *tabNazwiska, bool *tabObecnosc, string *tabId) {
    for (int i = 0; i < 10; i++) {
        if (tabNazwiska[i] != "" && tabId[i]!= "") {
            cout << tabId[i]<<" "<< tabNazwiska[i] << " " << tabObecnosc[i] << endl;
        }
    }
}


void usun(string *tabNazwiska, string *tabId, bool *tabObecnosc, string id) {

for (int i=0; i<10; i++) {
if (tabId[i]==id) {
tabNazwiska[i]="";
tabId[i]="";
tabObecnosc[i]=false;
break;

}
}
}

void edytuj(string *tabNazwiska, string osoba, string*tabId, string id, bool*tabObecnosc, bool obecnosc) {

for (int i=0; i<10; i++) {
if (tabId[i]==id)
{

tabId[i]="";
tabId[i]=id;

tabNazwiska[i]="";
tabNazwiska[i]=osoba;

tabObecnosc[i]=false;
tabObecnosc[i]=obecnosc;
break;
}

}

}
int main() {
    string tabNazwiska[10];
    string tabId[10];
    bool tabObecnosc[10]={} ;

    string osoba;
string id;
bool obecnosc;
    int wybor;

    do {
        cout << "1 DODAJ OSOBE oraz id "<< endl;
        cout << "2 USTAW OBECNOSC" << endl;
        cout << "3 WYSWIETL" << endl;
        cout << "4 USUN osobe" <<endl;
        cout<<" 5 aby EDYTOWAC"<<endl;
        cout << "0 WYJSCIE" << endl;
        cin >> wybor;

        switch (wybor) {
            case 1:
                cin >> id>> osoba;
                dodaj_osobe_id(tabNazwiska, osoba, tabId, id);
                break; 
            case 2:
                cin >> id >> obecnosc;
                ustaw_obecnosc(tabId, tabObecnosc, id, obecnosc);
                break; 
            case 3:
                wyswietl(tabNazwiska, tabObecnosc, tabId);
                break;

            case 4:
            cin>>id;
            usun(tabNazwiska, tabId, tabObecnosc, id);
          break;

          case 5:
 cin>>id>>osoba>>obecnosc;
          edytuj(tabNazwiska, osoba, tabId, id, tabObecnosc, obecnosc);
          break;
            case 0:
                break;
            default:
                cout << "ZLE WYBRALES" << endl;
                break;
        }
    } while (wybor != 0);

    return 0;
}
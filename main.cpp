#include <iostream>
#include <fstream>
#include <string>
using namespace std;

typedef string T;
const T NULA = T{};
struct prvek{
    T data;
    prvek* dalsi;
};
struct seznam {
    prvek* hlava;
    prvek* zarazka;
};



void vytvor(seznam& s){
    s.hlava = s.zarazka = new prvek{NULA, nullptr};
}


void vloz_na_zacatek(seznam& s, T data){
    s.hlava = new prvek{data,s.hlava};
}
void vloz_na_konec(seznam& s, T data){
    s.zarazka->data = data;
    s.zarazka->dalsi = new prvek{NULA, nullptr};
    s.zarazka = s.zarazka->dalsi;
}


void vypis(seznam& s){
    for (prvek* pomocny=s.hlava; pomocny != s.zarazka; pomocny = pomocny->dalsi) {
        cout<<pomocny->data<<endl;
    }
}
bool found=false;
prvek* najdi_z_pocatku(seznam& s, T data){
    for (prvek* pomocny=s.hlava; pomocny != s.zarazka ; pomocny = pomocny->dalsi) {
        if(pomocny->data == data){
            found=1;
            return pomocny;
        }
    }
    return nullptr;

}
bool prazdny(seznam& s){
    return s.hlava->data==NULA;
}
void vloz_za_zadanou(seznam& s, prvek* zadana, T data){
    if(found==1) {
        found = 0;
        zadana->dalsi->dalsi = new prvek{zadana->dalsi->data, zadana->dalsi->dalsi};
        zadana->dalsi = new prvek{data, zadana->dalsi->dalsi};
    }
}
int zaplni_z_souboru(seznam& s){
    ifstream fin;
    fin.open("input.txt");
    if(!fin.is_open()){return -1;}
    T line;
    while (getline(fin,line)) {
        vloz_na_konec(s, line);
    }
    fin.close();
    return 0;
}
int pocet_prvku(seznam& s){
    int count=0;
    for (prvek* pomocny=s.hlava; pomocny != s.zarazka ; pomocny = pomocny->dalsi) {
        count++;

    }
    return count;
}
int zapis_do_souboru(seznam& s){
    ofstream fout;
    fout.open("output.txt");
    if(!fout.is_open()){return -1;}
    T line;
    for (prvek* pomocny=s.hlava; pomocny != s.zarazka ; pomocny = pomocny->dalsi) {
        fout<<pomocny->data<<endl;
    }
    fout.close();
    return 0;
}
bool found_before=false;
prvek* find_before(seznam& s,prvek* ktery){
    if(ktery==s.hlava){
        found_before=false;
        return nullptr;
    }
    prvek* pomocny;
    for (pomocny=s.hlava; pomocny->dalsi!=ktery; pomocny = pomocny->dalsi) {}
    found_before=true;
    return pomocny;
}
void odstran_prvni(seznam& s){
    prvek* pomocny=s.hlava;
    s.hlava = s.hlava->dalsi;
    delete pomocny;
}
int odstran(seznam& s,prvek* ktery){
    if(found!=1){return -1;}
    found=0;
    prvek* pomocny;
    if(ktery==s.hlava){
        cout<<ktery->data<<" was deleted!(was first)"<<endl;
        pomocny = s.hlava;
        s.hlava = s.hlava->dalsi;
        delete pomocny;
        return 0;
    }else if(ktery->dalsi==s.zarazka){
        cout<<ktery->data<<" was deleted!(was last)"<<endl;
        pomocny = find_before(s, ktery);
        delete s.zarazka;
        ktery->data=NULA;
        ktery->dalsi=nullptr;
        s.zarazka=ktery;

    }else{
        pomocny = find_before(s,ktery);
        pomocny->dalsi = ktery->dalsi;
        cout<<ktery->data<<" was deleted!(was in the middle)"<<endl;
        delete ktery;
        return 0;
    }
}
prvek* najdi_z_konce(seznam& s, T data){
    prvek* minuly;
    for (prvek* pomocny=s.hlava; pomocny != s.zarazka ; pomocny = pomocny->dalsi) {
        if( pomocny->data==data) {
            minuly = pomocny;
            found=1;
        }
    }
    if(!minuly){return nullptr;}else{return minuly;}//if minuly exists, returns minuly, else - nullptr
}
void zrus(seznam& s){
    /* DELETE THIS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    while(!prazdny(s)){
        odstran_prvni(s);
    }
    delete s.hlava;
    delete s.zarazka;
*/
    prvek* pomocny = s.hlava;
    while (s.hlava) {
        s.hlava = s.hlava->dalsi;
        delete (pomocny);
        pomocny = s.hlava;
    }

}
void vyprazdni(seznam& s){
    if(!prazdny(s)){
    for(prvek* pomocny = s.hlava; pomocny!=s.zarazka; pomocny = pomocny->dalsi){
        odstran_prvni(s);
        //odstran(s,pomocny);
        //cout<<"deleted "<<pomocny->data<<endl;
    }
    //s.hlava=s.zarazka = new prvek{NULA,nullptr};
    s.hlava->data = NULA;
    s.hlava->dalsi = nullptr;
    }
}
void swapni(seznam& s1,seznam& s2){
    seznam s3;
    vytvor(s3);
    for (prvek* pomocny=s1.hlava; pomocny != s1.zarazka ; pomocny = pomocny->dalsi) {
        vloz_na_konec(s3,pomocny->data);
    }
    vyprazdni(s1);
    for (prvek* pomocny=s2.hlava; pomocny != s2.zarazka ; pomocny = pomocny->dalsi) {
        vloz_na_konec(s1,pomocny->data);
    }
    vyprazdni(s2);
    for (prvek* pomocny=s3.hlava; pomocny != s3.zarazka ; pomocny = pomocny->dalsi) {
        vloz_na_konec(s2,pomocny->data);
    }
    zrus(s3);
}
int main() {
    seznam s1;
    vytvor(s1);
    T data="3rd!";
    vloz_na_zacatek(s1, data);
    data="2nd!";
    vloz_na_zacatek(s1, data);
    data="1st!";
    vloz_na_zacatek(s1, data);
    //data = "Last!";
    //vloz_na_konec(s1, data);
    //zaplni_z_souboru(s1);
    //vloz_za_zadanou(s1, najdi_z_pocatku(s1,"Last!"), "Something!");
    //vloz_za_zadanou(s1, najdi_z_pocatku(s1,"Trash2"), "Something!");


    //odstran(s1, najdi_z_pocatku(s1,"1st!"));
    //odstran(s1, najdi_z_pocatku(s1,"Something!"));
    //odstran(s1, najdi_z_pocatku(s1,"Something!"));
    //odstran(s1, najdi_z_konce(s1,"Something!"));

    //zrus(s1);

    cout<<"0 means not empty: "<<prazdny(s1)<<endl;
    cout<<"The amount of items in the list is: "<<pocet_prvku(s1)<<endl;

    //zapis_do_souboru(s1);
    cout<<"----------------THE LIST IS UNDER THE LINE----------------"<<endl;
    vypis(s1);
    //vyprazdni(s1);
    //zrus(s1);
    /*cout<<"!!!!!!!!!!!_2ND_LIST_!!!!!!!!!!!"<<endl;
    cout<<"0 means not empty: "<<prazdny(s1)<<endl;
    cout<<"----------------THE NEW LIST IS UNDER THE LINE----------------"<<endl;
    vypis(s1);
*/


    seznam s2;
    vytvor(s2);
    data="rd3!";
    vloz_na_zacatek(s2, data);
    data="nd2!";
    vloz_na_zacatek(s2, data);
    data="st1!";
    vloz_na_zacatek(s2, data);
    data = "!tsaL";
    vloz_na_konec(s2, data);
    //vyprazdni(s2);
    //cout<<"0 means not empty: "<<prazdny(s2)<<endl;
    cout<<"----------------THE LIST 2 IS UNDER THE LINE----------------"<<endl;
    //vloz_na_zacatek(s2,"Test");
    vypis(s2);

    swapni(s1,s2);
    cout<<"----------------THE MODIFIED LIST 1 IS UNDER THE LINE----------------"<<endl;
    vypis(s1);
    cout<<"----------------THE MODIFIED LIST 2 IS UNDER THE LINE----------------"<<endl;
    vypis(s2);

}

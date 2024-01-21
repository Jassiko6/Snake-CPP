#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

#define SZEROKOSC 13
#define WYSOKOSC 13

using namespace std;

bool koniec = false;
int punkty = 0;

string plansza[WYSOKOSC][SZEROKOSC] = {
    "##", "##", "##", "##", "##", "##", "##", "##", "##", "##", "##", "##", "##",
    "##", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "##",
    "##", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "##",
    "##", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "##",
    "##", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "##",
    "##", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "##",
    "##", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "##",
    "##", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "##",
    "##", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "##",
    "##", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "##",
    "##", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "##",
    "##", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "##",
    "##", "##", "##", "##", "##", "##", "##", "##", "##", "##", "##", "##", "##"
};


class Owoc {
public:
    int x;
    int y;

    void pojawienieSie() {
        do{
        x = rand() % (SZEROKOSC - 2) + 1;
        y = rand() % (WYSOKOSC - 2) + 1;
        } while(plansza[y][x]!="  "s);
        plansza[y][x] = "@@";


    }
};

struct Ogon{
    int x1,x2,y1,y2;
    Ogon* ogon=nullptr;



};

class Snake {
public:
    int x = SZEROKOSC / 2;
    int y = WYSOKOSC / 2;
    string kierunek;
    Ogon* ogon=nullptr;

    void glowaStart() {
        plansza[y][x] = "><";
            if(this->ogon!=nullptr){
                Ogon* o=this->ogon;
                plansza[o->y1][o->x1]="[]";
            while(o!=nullptr){
                plansza[o->y1][o->x1]="[]";
                o=o->ogon;
            }

    }
    plansza[0][0]="##";
    }
};

void kierunek(Snake* s) {
    plansza[s->y][s->x] = "  ";

 if(_kbhit()){
       switch(_getch()){
case 'w':
    if(s->kierunek!="dol") s->kierunek="gora";
    break;
case 's':
    if(s->kierunek!="gora") s->kierunek="dol";
    break;
case 'a':
    if(s->kierunek!="prawo") s->kierunek="lewo";
    break;
case 'd':
    if(s->kierunek!="lewo") s->kierunek="prawo";
    break;

    }
    }
}

void uderzSciana(int y, int x){
if(plansza[y][x]=="##"){
    koniec=true;
}
if(plansza[y][x]=="[]"){
    koniec=true;
}



}

void wydluzOgon(Snake* s){
    punkty++;
    if(s->ogon!=nullptr){
            Ogon* o=s->ogon;
            while(o->ogon!=nullptr)
                o=o->ogon;
            o->ogon=new Ogon();
            o->ogon->x1=o->x1;
            o->ogon->y1=o->y1;
    }
    else s->ogon=new Ogon();
    s->ogon->x1=s->x;
    s->ogon->y1=s->y;
}

bool czyOwoc(int y, int x){


return plansza[y][x]=="@@";

}

void przesunTlow(Snake* s){
    if(s->ogon!=nullptr){
            Ogon* o=s->ogon;
            plansza[o->y1][o->x1]="  ";
            o->x1=s->x;
            o->y1=s->y;
            while(o->ogon!=nullptr){
                plansza[o->ogon->y1][o->ogon->x1]="  ";
                o->ogon->x1=o->x2;
                o->ogon->y1=o->y2;
                o->x2=o->x1;
                o->y2=o->y1;
                o=o->ogon;
                }
    }
}

void ruch(Snake* s, Owoc o){


if(s->kierunek=="gora"){
    uderzSciana(s->y-1,s->x);
    if(czyOwoc(s->y-1,s->x)){
        wydluzOgon(s);
        o.pojawienieSie();
    }
    przesunTlow(s);
    s->y--;
}


else if(s->kierunek=="dol"){
    uderzSciana(s->y+1,s->x);
    if(czyOwoc(s->y+1,s->x)){
        wydluzOgon(s);
        o.pojawienieSie();
    }
    przesunTlow(s);
    s->y++;
}

else if(s->kierunek=="prawo"){
    uderzSciana(s->y,s->x+1);
    if(czyOwoc(s->y,s->x+1)){
        wydluzOgon(s);
        o.pojawienieSie();
    }
    przesunTlow(s);
    s->x++;
}
else if(s->kierunek=="lewo"){
    uderzSciana(s->y,s->x-1);
    if(czyOwoc(s->y,s->x-1)){
        wydluzOgon(s);
        o.pojawienieSie();
    }
    przesunTlow(s);
    s->x--;
}

}






int main() {
    srand(time(NULL));

    Owoc owoc;
    Snake snake;
    owoc.pojawienieSie();
    while (!koniec) {
        snake.glowaStart();
        for (int i = 0; i < WYSOKOSC; i++) {
            for (int j = 0; j < SZEROKOSC; j++) {
                cout << plansza[i][j];
            }
            cout << endl;
        }

        cout <<"\n\n"<< "                Punkty: "<<punkty;

        Sleep(100);
        kierunek(&snake);
        ruch(&snake, owoc);
        system("CLS");

    }
    cout<<"Koniec.";
    return 0;
}

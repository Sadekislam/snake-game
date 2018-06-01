#include<iostream>
#include<conio.h>
#include<stdlib.h>
using namespace std;
void run();
void printMap();
void initMap();
void move(int x,int y);
void update();
void changeDirection(char key);
void clearScreen();
void generateFood();
char getMapValue(int value);
const int mapwidth=20;
const int mapheight=20;
const int size=mapwidth*mapheight;
int map[size];
int headxpos;
int headypos;
int direction;
int food=2;
bool running;
int main()
{
    run();
    return 0;
}
void run()
{
    initMap();
    running=true;
    while (running) {
            if(kbhit()){
                changeDirection(getch());
            }
            update();
            clearScreen();
            printMap();

    }
    cout<<"\t\t!!!Game over!!!"<<std::endl<<"\t\tYour score is: "<<food;
    cin.ignore();

}
void changeDirection(char key){
    /*W
    A + D
      S

        */
        switch(key){
        case 'w':
            if(direction!=2) direction =0;
            break;
        case 'd':
            if(direction!=3) direction=1;
            break;
        case 's':
            if(direction!=4) direction=2;
            break;
        case 'a':
            if(direction!=5) direction=3;
            break;

        }
}
void move(int x,int y){
          int newx=headxpos+x;
          int newy=headypos+y;
          if(map[newx+newy*mapwidth]==-2){
                food++;
                generateFood();
          }
          else if(map[newx+newy*mapwidth]!=0){
            running=false;
          }
          headxpos=newx;
          headypos=newy;
          map[headxpos+headypos*mapwidth]=food+1;
}
void clearScreen(){
    system("cls");
}
void generateFood(){
    int a=0,b=0;
    do{
       a=rand()%(mapwidth-2)+1;
       b=rand()%(mapheight-2)+1;
    }
    while(map[a+b*mapwidth]!=0);
    map[a+b*mapwidth]=-2;
}
void update(){
    switch (direction){
       case 0: move(-1,0);
       break;
       case 1: move(0,1);
       break;
       case 2: move(1,0);
       break;
       case 3: move(0,-1);
       break;
    }
    for(int i=0;i<size;i++){
        if(map[i]>0) map[i]--;
    }
}
void initMap()
{
    headxpos=mapwidth/2;
    headypos=mapheight/2;
    map[headxpos+headypos*mapwidth]=1;
    for(int a=0;a<mapwidth;++a){
        map[a]=-1;
        map[a+(mapheight-1)*mapwidth]=-1;
    }
    for(int b=0;b<mapheight;b++){
        map[0+b*mapwidth]=-1;
        map[(mapwidth-1)+b*mapwidth]=-1;
    }
    generateFood();
}
void printMap()
{
    for(int x=0;x<mapwidth;++x){
        for(int y=0;y<mapheight;++y){
            cout<<getMapValue(map[x+y*mapwidth]);
        }
        cout<<endl;
    }
}

char getMapValue(int value)
{
    // Returns a part of snake body
    if  (value>0) return 'O';

    switch (value){
        // Return wall
    case -1: return '#';
        // Return food
    case -2: return  'F';
    }
}

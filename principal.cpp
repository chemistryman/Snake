#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>


int  x, y, n, len, i, j, dir, xa, ya, sc, sl, ac;
char tecla,arrows[2],option[]={0,0};

typedef struct player{
    char name[15];
    int score;
}player;

void print(){
     for (i=3;i<=77;i++){
         gotoxy(i,3);
         putchar(205);
         gotoxy(i,23);
         putchar(205);
     }
     for (i=4;i<=22;i++){
         gotoxy(2,i);
         putchar(186);
         gotoxy(78,i);
         putchar(186);
     }
     gotoxy(2,3);
     putchar(201);
     gotoxy(2,23);
     putchar(200);
     gotoxy(78,3);
     putchar(187);
     gotoxy(78,23);
     putchar(188);
}

void goimp(int x,int y,char string[]){
     gotoxy(x,y);
     printf("%s",string);
     return;
}

void arrowsws(int a) {
    if (arrows[0]=='w'||arrows[0]=='W')
        if(arrows[1]>0)
            arrows[1]--;
        else
            arrows[1]=a;

    if (arrows[0]=='s'||arrows[0]=='S')
        if(arrows[1]<a)
            arrows[1]++;
        else
            arrows[1]=0;
    return;
}

void menuline(int a, int b, int num, int numcmp, char cad[]){
    if (num==numcmp){
        textcolor(0);
        textbackground(15);
    }
    else{
        textcolor(15);
        textbackground(0);
    }
    goimp(a,b,cad);
    return;
}

void instructions(){
    char key;
     clrscr();
     print();

     goimp(35,5,"How to play");
     goimp(30,9,"Slice around using:");
     goimp(41,11,"W");
     goimp(41,13,"S");
     goimp(39,13,"D");
     goimp(43,13,"A");
     goimp(20,15,"Eat as many apples as you can to earn score");
     goimp(29,17,"Beware of hitting your body");
     goimp(35,21,"Good luck");
     tecla=0;
     while (key!=13)
        key=getch();
     return;
}

void savep(int body[][2]){
     body[n][0]=x;
     body[n][1]=y;
     n++;
     if(n==len)
         n=1;
}

void printb(int body[][2]){
     for(i=1;i<len;i++){
         gotoxy(body[i][0],body[i][1]);
         putchar(207);
     }
}

void deleteb(int body[][2]){
     for(i=1;i<len;i++){
         gotoxy(body[i][0],body[i][1]);
         printf(" ");
     }
}

void ctr(){
        if(kbhit()){
            tecla=getch();
            if((tecla=='w'||tecla=='W')&&dir!=2)
                dir=1;
            else if((tecla=='s'||tecla=='S')&&dir!=1)
                 dir=2;
            else if((tecla=='d'||tecla=='D')&&dir!=4)
                 dir=3;
            else if((tecla=='a'||tecla=='A')&&dir!=3)
                 dir=4;
        }
}

void avance(){
        if(dir==1)
           y--;
        else if(dir==2)
           y++;
        else if(dir==3)
           x++;
        else if(dir==4)
           x--; 
}

void limite (){
        if(x==77)
            x=3;
        if(x==2)
            x=76;
        if(y==3)
            y=22;
        if(y==23)
            y=4;
}

bool Rapple(int body[][2]){
    for(j=len-1;j>0;j--){
        if(body[j][0]==xa&&body[j][1]==ya)
            return true;
    }
    return false;
}

void apple(int body[1314][2]){
    if(len==3||(x==xa&&y==ya)){
        if(len>3)
            sc++;
        do{
           xa=(rand()%71)+4;
           ya=(rand()%18)+4;
           len++;
        }while(Rapple(body));
        gotoxy(xa,ya);
        textcolor(4);
        putchar(254);
        textcolor(15);
    }
}

bool GOver(int body[][2]){
    for(j=len-1;j>0;j--){
        if(body[j][0]==x&&body[j][1]==y)
            return true;
    }
    return false;
}

void score(){
     gotoxy(2,2);
     printf("Score:%i",sc);
     if(sc==ac*10&&sl>=30){
         sl-=10;
         ac++;
     }
}

void lose(){
     char key;
     gotoxy(35,12);
     textcolor(4);
     printf("You Lose");
     textcolor(15);
     while(key!=13)
         key=getch();
     for(i=35;i<=42;i++){
         gotoxy(i,12);
         printf(" ");
     }
}

void gimmename(char nomb[15]){
    char tecla;
    int i=0;
    while(tecla!=13 || i==0){
        tecla=getch();
        if(isalpha(tecla)!=0 && i<15){
            gotoxy(i+43,14);
            putchar(tecla);
            nomb[i]=tecla;
            i++;
            nomb[i]='\0';
        }
        if(tecla==8 && i>0){
            i--;
            gotoxy(i+43,14);
            putchar(' ');
            nomb[i]='\0';
        }
    }
    return;
}

void consulte(){
    FILE *scores;
    player play;
    int sz, row=0;
    char key;
    scores=fopen("c:\\snake\\score.snk", "rb");
    clrscr();
    print();

    if (scores==NULL){
        gotoxy(29,12);
        printf("There's no saved data");
    }
    else {
        fseek(scores,0,SEEK_END);
        sz=ftell(scores);
        fseek(scores,0,SEEK_SET);

        while(ftell(scores)<sz){
            fread(&play,sizeof(play),1,scores);
            gotoxy(35,6+row);
            printf("%s", play.name);
            gotoxy(38,8+row);
            printf("%i", play.score);

            row+=5;
        }
    }
    fclose(scores);
    gotoxy(26,22);
    printf("Press enter to continue");
    while(key!=13)
        key=getch();
    return;
}

void enterp(){
    FILE *scores;
    FILE *faux;
    player play, aux;
    int sz;

    gotoxy(24,14);
    printf("Tell me your name: ");
    gimmename(play.name);
    play.score=sc;
    scores=fopen("c:\\snake\\score.snk", "rb");
    faux=fopen("c:\\snake\\auxiliar.snk", "wb");
    
    fseek(scores,0,SEEK_END);
    sz=ftell(scores);

    fseek(scores,0,SEEK_SET);
    fread(&aux,sizeof(aux),1,scores);
    
    if(sz==0)
        fwrite(&play,sizeof(play),1,faux);
    else if(sz==sizeof(player))
    {
          if(play.score<aux.score)
          {
              fwrite(&aux,sizeof(aux),1,faux);
              fwrite(&play,sizeof(play),1,faux);
          }
          else
          {
              fwrite(&play,sizeof(play),1,faux);
              fwrite(&aux,sizeof(aux),1,faux);
          }
    }
    else if (sz==sizeof(player)*2 || sz==sizeof(player)*3)
    {
        if(play.score<aux.score)
        {
            fwrite(&aux,sizeof(aux),1,faux);
            fread(&aux,sizeof(aux),1,scores);
            if(play.score<aux.score)
            {
                fwrite(&aux,sizeof(aux),1,faux);
                fwrite(&play,sizeof(play),1,faux);
            }
            else
            {
                fwrite(&play,sizeof(play),1,faux);
                fwrite(&aux,sizeof(aux),1,faux);
            }
        }
        else
        {
            fwrite(&play,sizeof(play),1,faux);
            fwrite(&aux,sizeof(aux),1,faux);
            fread(&aux,sizeof(aux),1,scores);
            fwrite(&aux,sizeof(aux),1,faux);
        }
    }
    fclose(scores);
    fclose(faux);
    
    remove("c:\\snake\\score.snk");
    rename("c:\\snake\\auxiliar.snk", "c:\\snake\\score.snk");
    return;
}

void highscore(){
    FILE *scores;
    player play;
    char key;
    
    scores=fopen("c:\\snake\\score.snk", "rb");

    if (scores==NULL){
        scores=fopen("c:\\snake\\score.snk", "wb");
        if(scores==NULL){
            system("md c:\\snake");
            scores=fopen("c:\\snake\\score.snk", "wb");
        }
    }
    fseek(scores,0,SEEK_END);
    if(ftell(scores)!=0){
        fseek(scores,-sizeof(player),SEEK_END);
        fread(&play,sizeof(play),1,scores);
    }

    if(ftell(scores)<sizeof(player)*3 || play.score<=sc){
        gotoxy(19,10);
        printf("%cYou have reached the highest scores!",173);
        fclose(scores);
        enterp();
        consulte();
    }
    else{
        fclose(scores);
        gotoxy(18, 12);
        printf("You haven't reached the highest scores");
        gotoxy(25,18);
        printf("Press enter to return");
        
        while (key!=13)
            key=getch();
    }

    return;
}

void clearb(int body[1314][2]){
     for(j=0;j<=1313;j++){
         body[j][0]=0;
         body[j][1]=0;
     }
     return;
}

void game(){
    int body[1314][2];
    len=3;
    n=1;
    sc=0;
    x=10; 
    y=12;
    dir=3;
    sl=100;
    ac=1;
    srand(time(NULL));
    clrscr();
    print();
    clearb(body);
    while(tecla!=27&&!GOver(body)){
        score();
        apple(body);
        deleteb(body);
        savep(body);
        printb(body);
        Sleep(sl);
        ctr();
        avance();
        limite();
    }
    if(GOver(body))
        lose();
        highscore();
}

int main(){ 
    do{
        arrows[0]=0;
        arrows[1]=0;
        clrscr();
        print();
        goimp(37,5,"SNAKE");
        do{
            arrowsws(3);
            menuline(31,11,0,arrows[1],"      PLAY      ");
            menuline(31,14,1,arrows[1],"  INSTRUCTIONS  ");
            menuline(31,17,2,arrows[1],"   HIGH SCORES  ");
            menuline(31,20,3,arrows[1],"      EXIT      ");

            arrows[0]=getch();
        } while (arrows[0]!=13);

        option[1]=arrows[1];

        if (option[1]==0){
            game();
        }
        else if(option[1]==1)
            instructions();
        else if(option[1]==2)
            consulte();
    }while(option[1]!=3);
    return 0;

}


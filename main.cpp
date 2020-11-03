#include <ncurses.h>
#include <iostream>
#include<string>
#include<pthread.h>
using namespace std;
WINDOW *musicList;
  WINDOW *musicRow;
   WINDOW *music;
   WINDOW *reproShow;
   pthread_mutex_t mutex,mutex2,mutexPause=PTHREAD_MUTEX_INITIALIZER;
   pthread_t play;
   bool repoMode=true;
   bool pause=true;
   bool endMusic=true;
  int queue[25];
  int curr=1;
  int timer=0;
  int musicP;
  int count=0;
   void* thSetPlay(void* arg) {
     wmove(music, 1, 1);
     wclrtoeol(music);
     box(music,0,0);
 std::string t = std::to_string(timer);
   std::string n = std::to_string(musicP);
     string x="music_"+n+": "+t;
    mvwprintw(music,1,1,x.c_str()); 
       wrefresh(music);
  pthread_exit(NULL);
}
   void* thPlay(void* arg){
       pthread_t setPlay;
     timer =10;
    while (timer>0) { 
    while(pthread_mutex_trylock(&mutexPause));
      while(pthread_mutex_trylock(&mutex2));
     pthread_create(&setPlay,NULL,thSetPlay,NULL);
     pthread_join(setPlay,NULL);
     timer--;
     pthread_mutex_unlock(&mutex2);
        pthread_mutex_unlock(&mutexPause);
      napms(1000); 
    
   }  
    while(pthread_mutex_trylock(&mutex2));
     wmove(music, 1, 1);
     wclrtoeol(music);
     box(music,0,0);
     wrefresh(music);
       pthread_mutex_unlock(&mutex2);
   endMusic=true;
   return 0;
   } 
   void* thSetRow(void* arg){
       endMusic=false;
       if(repoMode==true){
           musicP=queue[1];
         for(int i=1;i<24;i++){
             queue[i]=queue[i+1]; 
             wmove(musicRow, i, 2);
                wclrtoeol(musicRow);
                box(musicRow, 0, 0);
                wrefresh(musicRow);
             if(queue[i]!=0){
            std::string f = std::to_string(queue[i]);
           string m="music_"+f;
                mvwprintw(musicRow, i, 2, m.c_str());
                wrefresh(musicRow);
             } else {
                break;
             }
         }
       } else {
           int i =1+ rand()%(curr-1);
           musicP=queue[i];
          for(;i<24;i++){
                queue[i]=queue[i+1];  
                wmove(musicRow, i, 2);
                wclrtoeol(musicRow);
                box(musicRow, 0, 0);
                wrefresh(musicRow);
             if(queue[i]!=0){
           std::string f = std::to_string(queue[i]);
           string m="music_"+f;
                mvwprintw(musicRow, i, 2, m.c_str());
                wrefresh(musicRow);
             } else {
                break;
             }
         }
       } curr--;
       pthread_exit(NULL);
   } 
   void* thNext(void* arg){
       musicP=queue[1];
 for(int i=1;i<24;i++){
                queue[i]=queue[i+1];
                wmove(musicRow, i, 2);
                wclrtoeol(musicRow);
                box(musicRow, 0, 0);
                wrefresh(musicRow);
             if(queue[i]!=0){
           std::string f = std::to_string(queue[i]);
             string m="music_"+f;
                mvwprintw(musicRow, i, 2, m.c_str());
                wrefresh(musicRow);
             } else {
               break;
             }
         }
         curr--;
         pthread_exit(NULL);
   }
   void* thRow(void* arg){
       pthread_t setRow;
       while(true){ 
         while(pthread_mutex_trylock(&mutex));
        if(curr>1&&endMusic==true){
        pthread_create(&setRow,NULL,thSetRow,NULL);
        pthread_join(setRow,NULL);
        pthread_create(&play,NULL,thPlay,NULL);
        } 
         pthread_mutex_unlock(&mutex);
        
       }
   } 
  
int main(int argc, char const *argv[])
{
    initscr();
    noecho();
    cbreak();
    raw();
    curs_set(0);
    pthread_t row,next;
    int xMax;
    xMax=COLS;
    musicList = newwin(30 , (xMax / 2)-1, 0, 0);
    musicRow=newwin(25,(xMax/2)-1,3,(xMax/2)+1);
    music =newwin(3,25,0,(xMax/2)+1);
    reproShow=newwin(3,25,0,(xMax/2)+26);
    refresh();
    box(musicRow,0,0);
    wrefresh(musicRow);
    box(musicList, 0, 0);
    wrefresh(musicList);
    box(music,0,0);
    wrefresh(music);
    box(reproShow,0,0);
    mvwprintw(reproShow,1,1,"Sequencial Mode"); 
     wrefresh(reproShow);
    keypad(musicList, true);
    for (int i=1;i<25;i++){
   queue[i]=0;
    } 
    int choice;
    int highlight = 1;
   bool check=false;
   mvwprintw(musicList, 1, 1, "Musics :");
   pthread_create(&row,NULL,thRow,NULL);
    while (check==false)
    {  while(pthread_mutex_trylock(&mutex));
     while(pthread_mutex_trylock(&mutex2));
    for (int i = 1; i < 28; i++)
        {   
            if (i == highlight)
            {
                wattron(musicList, A_REVERSE);
            } 
            std::string n = std::to_string(i);
            string m="music_"+n;
            mvwprintw(musicList, i + 1, 1, m.c_str());
            wattroff(musicList, A_REVERSE);
        } 
      pthread_mutex_unlock(&mutex);
         pthread_mutex_unlock(&mutex2);
       choice = wgetch(musicList);
      string m;
      std::string f = std::to_string(highlight); 
        switch (choice)
        {
        case KEY_UP:
            highlight--;
            if (highlight == 0)
                highlight = 1;
            break;
        case KEY_DOWN:
            highlight++;
            if (highlight == 28)
                highlight = 27;
                break;
        case KEY_RIGHT :
        check=true;
        break;
       case 'a':
      while(pthread_mutex_trylock(&mutex));
         while(pthread_mutex_trylock(&mutex2));
             m = "music_" + f;
             
            if (curr < 24)
            {
                queue[curr] = highlight;
                mvwprintw(musicRow, curr, 2, m.c_str());
                wrefresh(musicRow);
                curr++;
            } 
           pthread_mutex_unlock(&mutex);
            pthread_mutex_unlock(&mutex2);
            break;
            case 'd':
            while(pthread_mutex_trylock(&mutex));
              while(pthread_mutex_trylock(&mutex2));
              if (curr > 1)
            {
                wmove(musicRow, curr - 1, 2);
                wclrtoeol(musicRow);
                box(musicRow, 0, 0);
                wrefresh(musicRow);
                curr--;
                queue[curr]=0;
            }
             pthread_mutex_unlock(&mutex);
              pthread_mutex_unlock(&mutex2);
            break;
            case 'p':
            if(pause==false){
              pause=true;
                 pthread_mutex_unlock(&mutexPause);
              
            } else {
                pause=false;
                 while(pthread_mutex_trylock(&mutexPause));
            }
            break;
            case 'n':
             while(pthread_mutex_trylock(&mutex));
            if(curr>1&&pause==true){
              pthread_cancel(play);
                pthread_create(&next,NULL,thNext,NULL);
                pthread_join(next,NULL);
                pthread_mutex_unlock(&mutex2);
                pthread_mutex_unlock(&mutexPause);
                pthread_create(&play,NULL,thPlay,NULL);
            } 
             pthread_mutex_unlock(&mutex);
            break;
            case 'r':
            while(pthread_mutex_trylock(&mutex));
             while(pthread_mutex_trylock(&mutex2));
            wmove(reproShow, 1, 1);
                wclrtoeol(reproShow);
                box(reproShow, 0, 0);
            if(repoMode==true){
                repoMode =false;
                mvwprintw(reproShow,1,1,"Random Mode");
            } else {
                repoMode=true;
                mvwprintw(reproShow,1,1,"Sequencial Mode");
            } wrefresh(reproShow);
              pthread_mutex_unlock(&mutex2);
              pthread_mutex_unlock(&mutex);
            break;
        default:
            break;
        } 
    }
   
    endwin();
 
    return 0;
}
 
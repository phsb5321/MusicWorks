#include <ncurses.h>
#include <iostream>
#include<string>
#include<pthread.h>
using namespace std;
WINDOW *musicList;
  WINDOW *musicRow;
   WINDOW *music;
   bool p=false;
   int show(WINDOW *win, int* data) {
   std::string n = std::to_string(*data);
     string x="music_x: "+n;
    mvwprintw(music,1,1,x.c_str());
    wrefresh(music); 
    werase(music);
    box(music,0,0);
      napms(1000);
   return 0;
}
   void* play(void* data){
      WINDOW *win = (WINDOW*)data;
      int sec=10;
    while ( !p &&sec>=0) {
      show(win,&sec);
    sec--;
   }
   return 0;
   }
int main(int argc, char const *argv[])
{
    initscr();
    noecho();
    cbreak();
    raw();
    pthread_t th1;
    int yMax, xMax;
    yMax=LINES;
    xMax=COLS;
     std::string s = std::to_string(yMax);
    musicList = newwin(yMax , (xMax / 2)-1, 0, 0);
    musicRow=newwin(yMax-3,(xMax/2)-1,3,(xMax/2)+1);
    music =newwin(3,xMax/4,0,(xMax/2)+1);
    refresh();
    box(musicRow,0,0);
    wrefresh(musicRow);
    box(musicList, 0, 0);
    wrefresh(musicList);
    box(music,0,0);
    wrefresh(music);
    keypad(musicList, true);

int queue[yMax-5];
    for (int i=1;i<yMax-5;i++){
   queue[i]=0;
    } 
    int choice;
    int highlight = 1;
   bool check=false;
   int curr=1;
   mvwprintw(musicList, 1, 1, "Musics :");
  
    while (check==false)
    {
        for (int i = 1; i < LINES-2; i++)
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
            if (highlight == yMax-2)
                highlight = yMax-3;
                break;
        case KEY_RIGHT :
        check=true;
        break;
        case KEY_LEFT:
      // pthread_create(&th1,NULL,play,music);
       break;
       case 'a':
             m = "music_" + f;
             
            if (curr < yMax - 4)
            {queue[curr] = highlight;
                mvwprintw(musicRow, curr, 2, m.c_str());
                wrefresh(musicRow);
                curr++;
            }
            break;
            case 'd':
              if (curr > 1)
            {
                wmove(musicRow, curr - 1, 2);
                wclrtoeol(musicRow);
                box(musicRow, 0, 0);
                wrefresh(musicRow);
                curr--;
                queue[curr]=0;
            }
            break;

        default:
            break;
        }
    }

    endwin();
 
    return 0;
}
 
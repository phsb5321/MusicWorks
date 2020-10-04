#include <ncurses.h>
#include <iostream>
#include<string>
using namespace std;

int main(int argc, char const *argv[])
{

    initscr();
    noecho();
    cbreak();

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
     std::string s = std::to_string(yMax);
    WINDOW *musicList = newwin(yMax , (xMax / 2)-1, 0, 0);
    WINDOW *musicRow =newwin(yMax-3,(xMax/2)-1,3,(xMax/2)+1);
    WINDOW *music =newwin(3,xMax/4,0,(xMax/2)+1);
    refresh();
    box(musicRow,0,0);
    wrefresh(musicRow);
    box(musicList, 0, 0);
    wrefresh(musicList);
    box(music,0,0);
    wrefresh(music);
    keypad(musicList, true);
    wattroff(music, A_REVERSE);
    wrefresh(music);
    int secondsLeft = 10;
  do {
      std::string n = std::to_string(secondsLeft);
      string x="music_x:"+n;
    mvwprintw(music,1,1,x.c_str());
    wrefresh(music);
    secondsLeft--;
    werase(music);
    box(music,0,0);
    napms(1000);
    
    
  } while (secondsLeft > 0);
string musics[yMax-2] = {"Musics :"+s};
    for (int i=1;i<sizeof(musics)/sizeof(musics[0]);i++){
   std::string n = std::to_string(i);
   musics[i]="music_"+n;
    } 
    int choice;
    int highlight = 0;
   int count =20;
    while (count>0)
    {
        for (int i = 0; i < sizeof(musics)/sizeof(musics[0]); i++)
        {
            if (i == highlight)
            {
                wattron(musicList, A_REVERSE);
            }
            mvwprintw(musicList, i + 1, 1, musics[i].c_str());
            wattroff(musicList, A_REVERSE);
        }
        choice = wgetch(musicList);

        switch (choice)
        {
        case KEY_UP:
            highlight--;
            if (highlight == -1)
                highlight = 0;
            break;
        case KEY_DOWN:
            highlight++;
            if (highlight == sizeof(musics)/sizeof(musics[0]))
                highlight = (sizeof(musics)/sizeof(musics[0]))-1;
                break;
        case KEY_RIGHT :
         
        default:
            break;
        }count--;
    }

    endwin();
 
    return 0;
}

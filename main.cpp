#include <ncurses.h>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{

    initscr();
    noecho();
    cbreak();

    int yMAx, xMax;
    getmaxyx(stdscr, yMAx, xMax);

    WINDOW *musicList = newwin(yMAx - 10, xMax / 2, 0, 0);
    box(musicList, 0, 0);
    refresh();
    wrefresh(musicList);

    keypad(musicList, true);

    string musics[3] = {"musica_1", "musica_2", "musica_3"};
    int choice;
    int highlight = 0;

    while (true)
    {
        for (int i = 0; i < 3; i++)
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
            if (highlight == 3)
                highlight = 2;

        default:
            break;
        }
    }

    endwin();

    return 0;
}

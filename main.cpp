#include <ncurses.h>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    initscr();
    printw("Hello world ");
    refresh();
    getch();
    endwin();
    return 0;
}

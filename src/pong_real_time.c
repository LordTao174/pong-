#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>
#define WIN 21
#define SIZE_X 80
#define SIZE_Y 25
void display(int ball_x, int ball_y, int player_y1, int player_y2, int win1, int win2);
void congrat(int, int);
int main() {
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, 1);
    scrollok(stdscr, 1);
    int ball_x, ball_y, v_x, v_y, proig, player_y1, player_y2, win1, win2;
    char c;
    player_y1 = 12;
    player_y2 = 12;
    ball_x = SIZE_X / 2;
    ball_y = SIZE_Y / 2;
    v_x = 2;
    v_y = 1;
    while (win1 < WIN && win2 < WIN) {
        // ОТСКОК ОТ ЛЕВОЙ РАКЕТКИ
        if (ball_x == 6 && ((ball_y == player_y1 ||
                             ball_y == player_y1 - 1 || ball_y == player_y1 + 1))) {
            v_x = -1 * v_x;
            if (ball_x == 5) {
                ball_x = 6;  // НА СЛУЧАЙ ЗАЛЁТА В РАКЕТКУ СТАВИМ ПЕРЕД РАКЕТКОЙ
            }
        }
        // ОТСКОК ОТ ЛЕВОЙ РАКЕТКИ
        if (ball_x == SIZE_X - 6 && ((ball_y == player_y2 ||
                                      ball_y == player_y2 - 1 || ball_y == player_y2 + 1))) {
            v_x = -1 * v_x;
            if (ball_x == SIZE_X - 5) {
                ball_x = SIZE_X - 6;  // НА СЛУЧАЙ ЗАЛЁТА В РАКЕТКУ СТАВИМ ПЕРЕД РАКЕТКОЙ
            }
        }
        if (ball_y <= 2 || ball_y >= SIZE_Y - 1) {
            v_y = -1 * v_y;
        }
        // ПОПАДАНИЕ В ЛЕВУЮ СТЕНКУ
        if (ball_x == 2) {
            win2++;
        }
        // ПОПАДАНИЕ В ПРАВУЮ СТЕНКУ
        if (ball_x == SIZE_X - 1) {
            win1++;
        }
        // ПОПАДАНИЕ В ПРАВУЮ ИЛИ ЛЕВУЮ СТЕНКУ
        proig = win1 + win2;
        // 6 РАЗНЫХ ВАРИАНТОВ ДВИЖЕНИЯ МЯЧА ОТ ЦЕНТРА ПОСЛЕ ПРОИГРЫША + ПЕРЕНОС
        if (ball_x <= 2 || ball_x >= SIZE_X - 1) {
            if (proig % 6 == 0) {
                v_x = 2;
                v_y = 1;
            }
            if (proig % 6 == 1) {
                v_x = -1;
                v_y = 1;
            }
            if (proig % 6 == 2) {
                v_x = 1;
                v_y = 2;
            }
            if (proig % 6 == 3) {
                v_x = -2;
                v_y = 1;
            }
            if (proig % 6 == 4) {
                v_x = 1;
                v_y = 1;
            }
            if (proig % 6 == 5) {
                v_x = -1;
                v_y = 2;
            }
            // ПЕРЕНОС МЯЧА В ЦЕНТР В СЛУЧАЕ ПРОИГРЫША
            ball_y = SIZE_Y / 2 - v_y;
            ball_x = SIZE_X / 2 - v_x;
        }
        // ПЕРЕМЕЩЕНИЕ МЯЧА
        ball_x = ball_x + v_x;
        ball_y = ball_y + v_y;
        if (ball_x == 1) {
            ball_x = 2;
        }
        if (ball_x == SIZE_X) {
            ball_x = SIZE_X - 1;
        }
        if (ball_y == 1) {
            ball_y = 2;
        }
        if (ball_y == SIZE_Y) {
            ball_y = SIZE_Y - 1;
        }
        // ЧТОБЫ РАКЕТКИ НЕ ЗАЛАЗИЛИ НА ПОЛЯ
        if (player_y1 == 2) {
            player_y1 = 3;
        }
        if (player_y1 == SIZE_Y - 1) {
            player_y1 = SIZE_Y - 2;
        }
        if (player_y2 == 2) {
            player_y2 = 3;
        }
        if (player_y2 == SIZE_Y - 1) {
            player_y2 = SIZE_Y - 2;
        }
        // ЕСЛИ ПОПАЛИ ВНУТРЬ ЛЕВОЙ РАКЕТКИ, СТАВИМ МЯЧ ПЕРЕД НЕЙ
        if (ball_x == 5 && ((ball_y == player_y1 || ball_y == player_y1 - 1 || ball_y == player_y1 + 1))) {
            ball_x = 6;
        }
        // ЕСЛИ ПОПАЛИ ВНУТРЬ ПРАВОЙ РАКЕТКИ, СТАВИМ МЯЧ ПЕРЕД НЕЙ
        if (ball_x == SIZE_X - 5 && ((ball_y == player_y2 ||
                                      ball_y == player_y2 - 1 || ball_y == player_y2 + 1))) {
            ball_x = SIZE_X - 6;
        }
        display(ball_x, ball_y, player_y1, player_y2, win1, win2);
        usleep(200000);
        printf("\033c");
        c = getch();
        // ПЕРЕМЕЩЕНИЕ РАКЕТОК
        if (c != ERR) {
            switch (c) {
                case 'a': {player_y1--; break;}
                case 'z': {player_y1++; break;}
                case 'k': {player_y2--; break;}
                case 'm': {player_y2++; break;}
            }
        }
    }
    endwin();
    // ВЫВОД ПОЗДРАВЛЕНИЙ ИГРОКОВ
    congrat(win1, win2);
    return 0;
}
void display(int x_ball, int y_ball, int player_y1, int player_y2, int w1, int w2) {
    char ball = 'O';
    char space = ' ';
    char board_horiz = '-';
    char board_vertic = '|';
    char player = '|';
    for (int i = 1; i <= SIZE_Y; i++) {
        if (i == 1) {
            for (int k = 0; k < SIZE_X; k++)
                printw("%c", board_horiz);
        } else {
            for (int j = 1; j <= SIZE_X; j++) {
                if ((i == player_y1 || i == player_y1 - 1 || i == player_y1 + 1) && j == 5) {
                    printw("%c", player);
                } else if ((i == player_y2 || i == player_y2 - 1 || i == player_y2 + 1) && j == SIZE_X - 5) {
                    printw("%c", player);
                } else if (i == SIZE_Y) {
                    if (j == SIZE_X / 2 - 1) {
                        if (w1 < 10) {
                            printw("%d%c", w1, board_horiz);
                        } else {
                            printw("%d", w1);
                        }
                    } else if (j == 41) {
                        if (w2 < 10) {
                            printw("%d%c", w2, board_horiz);
                        } else {
                            printw("%d", w2);
                        }
                    } else if (j != SIZE_X && j != SIZE_X - 1) {
                        printw("%c", board_horiz);
                    }
                } else if (j == 1 || j == SIZE_X) {
                    printw("%c", board_vertic);
                } else if (j == x_ball && i == y_ball) {
                    printw("%c", ball);
                } else {
                    printw("%c", space);
                }
            }
        }
        printw("\n");
    }
}
void congrat(int w1, int w2) {
    if (w1 == WIN) {
        printf("\033c\n");
        printf("PLAYER 1 WIN!!!");
    }
    if (w2 == WIN) {
        printf("\033c\n");
        printf("PLAYER 2 WIN!!!");
    }
}













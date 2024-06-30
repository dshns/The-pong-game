#include <stdio.h>

void box(int, int, int, int, int, int);          // фунция вывода поля
int players_move(int, int, int, int, int, int);  // движение ракеткок и мяча

int main(void) {
    int player_left = 13, player_right = 13;  // позиции ракеток игроков
    int ball_x = 1, ball_y = 13;              // позиция шарика
    int score_one = 0, score_two = 0;         // счет игроков

    box(player_left, player_right, ball_x, ball_y, score_one, score_two);
    players_move(player_left, player_right, ball_x, ball_y, score_one, score_two);

    return 0;
}

// фунция вывода поля
void box(int player_left, int player_right, int ball_x, int ball_y, int score_one, int score_two) {
    int x = 79, y = 26;

    while (y >= 0) {
        for (int i = 0; i <= x; i++) {
            if ((y == 26) || (y == 0)) {
                printf("=");
            } else {
                if ((i == 0) && ((y == player_left) || (y == player_left + 1) || (y == player_left - 1))) {
                    printf("]");
                    i = i + 1;
                }
                if ((i == ball_x) && (y == ball_y)) {
                    printf("O");
                    i = i + 1;
                }
                if ((i == 79) &&
                    ((y == player_right) || (y == player_right + 1) || (y == player_right - 1))) {
                    printf("[");
                    i = i + 1;
                }
                if (i < x) printf(" ");
            }
            if ((i == 35) && (y == 26)) {
                printf("|%02d|", score_one);
                i = i + 4;
            }
            if ((i == 39) && (y == 26)) {
                printf("|%02d|", score_two);
                i = i + 4;
            }
        }
        y = y - 1;
        printf("\n");
    }
}

// движение ракеткок и мяча
int players_move(int player_left, int player_right, int ball_x, int ball_y, int score_one, int score_two) {
    int move;
    int top_down = 0;    // движение мяча вверх -> 0 вниз -> 1
    int left_rigth = 0;  // движение мяча вправо -> 0 влево -> 1
    while (score_one < 21 && score_two < 21) {
        move = getchar();
        if (move == 'a' || move == 'A') {
            if (player_left < 24) player_left++;
        } else if (move == 'z' || move == 'Z') {
            if (player_left > 2) player_left--;
        } else if (move == 'k' || move == 'K') {
            if (player_right < 24) player_right++;
        } else if (move == 'm' || move == 'M') {
            if (player_right > 2) player_right--;
        } else if (move == ' ') {
            if (ball_y == 25) top_down = 1;
            if (ball_y == 1) top_down = 0;
            if (ball_x == 78 &&
                ((ball_y == player_right) || (ball_y == player_right + 1) || (ball_y == player_right - 1)))
                left_rigth = 1;
            else if (ball_x == 78) {
                score_one = score_one + 1;
                ball_x = 79;
                ball_y = player_right;
                left_rigth = 1;
            }
            if (ball_x == 1 &&
                ((ball_y == player_left) || (ball_y == player_left + 1) || (ball_y == player_left - 1)))
                left_rigth = 0;
            else if (ball_x == 1) {
                score_two = score_two + 1;
                ball_x = 0;
                ball_y = player_left;
                left_rigth = 0;
            }
            // направления движения мяча
            if (top_down == 0 && left_rigth == 0) {
                ball_x = ball_x + 1;
                ball_y = ball_y + 1;
            } else if (top_down == 1 && left_rigth == 0) {
                ball_x = ball_x + 1;
                ball_y = ball_y - 1;
            } else if (top_down == 0 && left_rigth == 1) {
                ball_x = ball_x - 1;
                ball_y = ball_y + 1;
            } else if (top_down == 1 && left_rigth == 1) {
                ball_x = ball_x - 1;
                ball_y = ball_y - 1;
            }
        }
        printf("\033[H\033[J");  // очиcтка терминала
        box(player_left, player_right, ball_x, ball_y, score_one, score_two);
    }
    if (score_one == 21 || score_two == 21) {
        if (score_one > score_two)
            printf("ПОЗДРАВЛЯЮ С ПОБЕДОЙ: ИГРОК 1!\n");
        else
            printf("ПОЗДРАВЛЯЮ С ПОБЕДОЙ: ИГРОК 2!\n");
    }
    return 0;
}
#include <iostream>  
#include <random>  
#include <vector>  
using std::cin;
using std::cout;
using std::endl;
using std::random_device;
using std::vector;

int WS(int t_move) {
    if (t_move == 'w') {
        return -1;
    }
    else if (t_move == 's') {
        return 1;
    }
    else {
        return 0;
    }
}
int AD(int t_move) {
    if (t_move == 'd') {
        return 1;
    }
    else if (t_move == 'a') {
        return -1;
    }
    else {
        return 0;
    }
}

int main()
{
    int round_cont = 0;

    int hero = 1;
    int hero_x = 2;  //hero options  
    int hero_y = 2;

    random_device x;

    int hp = 3;

    // vector <int> shots_x;  
    // vector <int> shots_y;  
    // vector <char> shots_live;  
    int shots_num = 1;
    int reshots_num = 0;

    int shots_x[5] = {0};
    int shots_y[5] = {0};
    char shots_live[5]{}; //shot option  

    for (int i = 0; i < shots_num; i++) {
        if (x() % 16 <= 4) {
            shots_y[i] = 4;
            shots_x[i] = x() % 5;
            shots_live[i] = 'D';
        }
        else if (x() % 16 > 4 and x() % 16 <= 8) {
            shots_y[i] = 0;
            shots_x[i] = x() % 5;
            shots_live[i] = 'U';
        }
        else if (x() % 16 > 8 and x() % 16 <= 12) {
            shots_x[i] = 4;
            shots_y[i] = x() % 5;
            shots_live[i] = 'R';
        }
        else if (x() % 16 > 12 and x() % 16 <= 16) {
            shots_x[i] = 0;
            shots_y[i] = x() % 5;
            shots_live[i] = 'L';
        }
    }  //first shots options  

    char move{};

    int map[5][5]{};

    while (hp != 0) {
        if (shots_num == 0) {
            shots_num = reshots_num;
        } //shots back 

        round_cont = round_cont + 1;
        if (round_cont == 10) {
            shots_num = shots_num + 1;
        } //round counter and +number of shots V1 
        else if (round_cont == 11) {
            round_cont = 0;
        }

        for (int i = 0; i < shots_num; i++) {
            if (shots_live[i] == 'U') {
                shots_y[i] = shots_y[i] + 1;
            }
            else if (shots_live[i] == 'D') {
                shots_y[i] = shots_y[i] - 1;
            }
            else if (shots_live[i] == 'R') {
                shots_x[i] = shots_x[i] - 1;
            }
            else {
                shots_x[i] = shots_x[i] + 1;
            }
        }  //moving shots  

        for (int i = 0; i < shots_num; i++) {
            if (shots_x[i] < 0 or shots_x[i]>4 or shots_y[i] < 0 or shots_y[i]>4) {
                if (x() % 16 <= 4) {
                    shots_y[i] = 4;
                    shots_x[i] = x() % 5;
                    shots_live[i] = 'D';
                }
                else if (x() % 16 > 4 and x() % 16 <= 8) {
                    shots_y[i] = 0;
                    shots_x[i] = x() % 5;
                    shots_live[i] = 'U';
                }
                else if (x() % 16 > 8 and x() % 16 <= 12) {
                    shots_x[i] = 4;
                    shots_y[i] = x() % 5;
                    shots_live[i] = 'R';
                }
                else if (x() % 16 > 12 and x() % 16 <= 16) {
                    shots_x[i] = 0;
                    shots_y[i] = x() % 5;
                    shots_live[i] = 'L';
                }
            }
        } //rewrite shots optins  

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                map[i][j] = 0;
            }
        } //rewrite location  

        hero_y = hero_y + WS(move); //moving hero  
        hero_x = hero_x + AD(move); //moving hero  

        if (hero_x == 5 and move == 'd') {
            hero_x = hero_x - 1;
        } //zone for hero  
        else if (hero_x == -1 and move == 'a') {
            hero_x = hero_x + 1;
        } //zone for hero  

        if (hero_y == 5 and move == 's') {
            hero_y = hero_y - 1;
        } //zone for hero  
        else if (hero_y == -1 and move == 'w') {
            hero_y = hero_y + 1;
        } //zone for hero  

        for (int i = 0; i < shots_num; i++) {
            if (hero_x == shots_x[i] and hero_y == shots_y[i]) {
                hp = hp - 1;
                reshots_num = shots_num;
                shots_num = 0;
            }
        } //game over 
        if (shots_num == 0) {
            for (int i = 0; i < reshots_num; i++) {
                if (x() % 16 <= 4) {
                    shots_y[i] = 4;
                    shots_x[i] = x() % 5;
                    shots_live[i] = 'D';
                }
                else if (x() % 16 > 4 and x() % 16 <= 8) {
                    shots_y[i] = 0;
                    shots_x[i] = x() % 5;
                    shots_live[i] = 'U';
                }
                else if (x() % 16 > 8 and x() % 16 <= 12) {
                    shots_x[i] = 4;
                    shots_y[i] = x() % 5;
                    shots_live[i] = 'R';
                }
                else if (x() % 16 > 12 and x() % 16 <= 16) {
                    shots_x[i] = 0;
                    shots_y[i] = x() % 5;
                    shots_live[i] = 'L';
                }
            }
        }

        map[hero_y][hero_x] = 5; //hero  

        for (int i = 0; i < shots_num; i++) {
            map[shots_y[i]][shots_x[i]] = 3;
        } //shots  

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                cout << map[i][j] << " ";
            }
            cout << endl;
        } //visualization of all 

        cout << endl;
        cin >> move;
    }

    return 0;
}
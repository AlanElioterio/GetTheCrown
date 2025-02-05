#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <cctype>

using namespace std;

const int numero_colunas = 11;
const int numero_linhas = 11;

int matriz_labirinto[11][11] = {
        {0,0,0,0,0,2,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0},
    };

void monta_mapa(int position_x, int position_y){
    cout<<endl<<endl<<endl;

    for (int y = 0; y < numero_colunas; y++){
        cout<<"           ";
        for(int x = 0; x < numero_linhas; x++){
            if (x == position_x && y == position_y){
                cout<<"|🤢|"<<" ";
            }
            else{
                switch(matriz_labirinto[y][x]){
                    case 0:
                        cout<<"| |";
                        break;
                    case 1:
                        cout<<"|X|";
                        break;
                    case 2:
                        cout<<"|👑|";
                        break;
                    default:
                        break;
                }
                cout<<" ";
            }
        }
        cout<<endl;
    }
}
bool try_monta_mapa(int position_x, int position_y){
    if (position_x < numero_linhas && position_x >= 0){
        if (position_y < numero_colunas && position_y >= 0){
            return true;
        }
    }
    return false;
}

int main()
{
    int position_x = 5, position_y = 10;

    while(true){
        system("cls");
        monta_mapa(position_x, position_y);

        int key = getch();


        switch(key){
            case 'a':
                if (try_monta_mapa(position_x - 1, position_y))
                    position_x--;
                break;
            case 'w':
                if (try_monta_mapa(position_x, position_y - 1))
                    position_y--;
                break;
            case 'd':
                if (try_monta_mapa(position_x + 1, position_y))
                    position_x++;
                break;
            case 's':
                if (try_monta_mapa(position_x, position_y + 1))
                    position_y++;
                break;
            default:
                break;
        }

    }
    return 0;
}

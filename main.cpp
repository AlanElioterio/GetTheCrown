#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <cctype>
#include <windows.h>

using namespace std;

const int numero_colunas = 11;
const int numero_linhas = 11;
bool ganhou_o_jogo = false;


int matriz_labirinto[11][11] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1},
        {1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1},
        {1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

void monta_mapa(int position_x, int position_y){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int k = 12;
    SetConsoleTextAttribute(hConsole, k);

    cout<<endl<<endl<<endl;

    for (int y = 0; y < numero_colunas; y++){
        cout<<"           ";
        for(int x = 0; x < numero_linhas; x++){
            if (x == position_x && y == position_y){
                //cout<<k<<"";
                //cout<<"\x1B[31m@ \x1B[31m";

                cout<<"\033[32m" << "@ " << "\x1B[0m";

            }
            else{
                switch(matriz_labirinto[y][x]){
                    case 0:
                        cout<<"\x1B[0m" << "0" << "\x1B[0m";
                        //cout<<"0";
                        break;
                    case 1:
                        cout<<"\033[31m" << "X" << "\x1B[0m";
                        //cout<<"X";
                        break;
                    case 2:
                        cout<<"\x1B[0m" << "&" << "\x1B[0m";
                        //cout<<"&";
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
    bool pode_montar_o_mapa = false;

    if (position_x < numero_linhas && position_x >= 0){
        if (position_y < numero_colunas && position_y >= 0){

            switch (matriz_labirinto[position_y][position_x])
            {
                case 0:
                    pode_montar_o_mapa = true;
                    break;
                case 1:
                    pode_montar_o_mapa = false;
                    break;
                case 2:
                    ganhou_o_jogo = true;
                    pode_montar_o_mapa = true;
                    break;
                default:
                    break;
            }
        }
    }

    return pode_montar_o_mapa;
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    int position_x = 0, position_y = 0;

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

        if (ganhou_o_jogo){
            system("cls");
            cout<<"Você ganhou o jogo!"<<endl;
            cin.get();
            break;
        }
    }
    return 0;
}

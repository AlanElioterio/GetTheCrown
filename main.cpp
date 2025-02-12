#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <cctype>
#include <windows.h>

using namespace std;

const int numero_colunas = 23;
const int numero_linhas = 23;

bool ganhou_o_jogo = false;

int matriz_labirinto[23][23] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };
int monta_menu(int opcao_escolhida){
    cout<<endl<<endl<<endl;

    while(true){
        cout<<"--> Jogo do Labirinto <--\n\n";
        cout<< (opcao_escolhida == 1) ? ">>" : "  ";
        cout<<" Novo Jogo "<< endl;

        cout<< (opcao_escolhida == 2) ? ">>" : "  ";
        cout<<" Último Jogo "<< endl;

        cout<< (opcao_escolhida == 3) ? ">>" : "  ";
        cout<<" Sair "<< endl;
        cout<<endl<<endl;
    }

    Sleep(2000);

    return opcao_escolhida;
}
void monta_mapa(int position_x, int position_y){
    system("cls");
    cout<<endl<<endl<<endl;

    for (int y = 0; y < numero_colunas; y++){
        cout<<"           ";
        for(int x = 0; x < numero_linhas; x++){
            if (x == position_x && y == position_y){
                cout<<"\033[32m" << "@ " << "\x1B[0m";
            }
            else{
                switch(matriz_labirinto[y][x]){
                    case 0:
                        cout<<"\x1B[0m" << "0" << "\x1B[0m";
                        break;
                    case 1:
                        cout<<"\033[31m" << "X" << "\x1B[0m";
                        break;
                    case 2:
                        cout<<"\x1B[0m" << "&" << "\x1B[0m";
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

    int opcao_escolhida = 3;

    while (true){
        monta_menu(opcao_escolhida);

        char key = getch();

        switch(key){
            case 'w':
                opcao_escolhida++;
                break;
            case 's':
                opcao_escolhida--;
                break;
            default:
                break;
        }
    }

    if (opcao_escolhida == 3){
        int position_x = 11, position_y = 11;

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
    }


    return 0;
}

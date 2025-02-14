#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <cctype>
#include <windows.h>

#include <string>

using namespace std;

/*
  Jogo - Get the Crown

  ->> Função Monta Menu:
        Escopo: mostrar o menu de navegação para o usuário.
        Parâmetros de entrada: Opção que vai ser exibida como a atual.
        Retorno da função: Vazio (ou seja, não retorna nada)

  ->> Função Monta Mapa:
        Escopo: mostrar o labirinto para o usuário.
        Parâmetros de entrada: A posição X e posição Y real que o jogador está.
        Retorno da função: Vazio (ou seja, não retorna nada)

  ->> Função Try Monta Mapa:
        Escopo: observa a posição desejada e calcula se o jogador pode ir no espaço desejado ou não.
        Parâmetros de entrada: A posição X e posição Y desejada para ficar no mapa.
        Retorno da função: Booleano (ou seja, verdadeiro se a posição é válida, e falso se a posição é inválida)
*/

// Declarando as funções do programa antes de começar, para não ocorrer um erro de NÃO-EXISTÊNCIA das funções
void monta_menu(int opcao_escolhida);
void monta_mapa(int position_x, int position_y);
bool try_monta_mapa(int position_x, int position_y);

// Declarando a variável LOGO_GAME que seria uma logo em código ASCII
const char* LOGO_GAME = R"(

           ....        .                   s            s                                    ...
        .x88" `^x~  xH(`                  :8           :8      .uef^"                     xH88"`~ .x8X                               x=~
       X888   x8 ` 8888h                 .88          .88    :d88E                      :8888   .f"8888Hf    .u    .          u.    88x.   .e.   .e.     u.    u.
      88888  888.  %8888        .u      :888ooo      :888ooo `888E            .u       :8888>  X8L  ^""`   .d88B :@8c   ...ue888b  '8888X.x888:.x888   x@88k u@88c.
     <8888X X8888   X8?      ud8888.  -*8888888    -*8888888  888E .z8k    ud8888.     X8888  X888h       ="8888f8888r  888R Y888r  `8888  888X '888k ^"8888""8888"
     X8888> 488888>"8888x  :888'8888.   8888         8888     888E~?888L :888'8888.    88888  !88888.       4888>'88"   888R I888>   X888  888X  888X   8888  888R
     X8888>  888888 '8888L d888 '88%"   8888         8888     888E  888E d888 '88%"    88888   %88888       4888> '     888R I888>   X888  888X  888X   8888  888R
     ?8888X   ?8888>'8888X 8888.+"      8888         8888     888E  888E 8888.+"       88888 '> `8888>      4888>       888R I888>   X888  888X  888X   8888  888R
      8888X h  8888 '8888~ 8888L       .8888Lu=     .8888Lu=  888E  888E 8888L         `8888L %  ?888   !  .d888L .+   u8888cJ888   .X888  888X. 888~   8888  888R
       ?888  -:8*"  <888"  '8888c. .+  ^%888*       ^%888*    888E  888E '8888c. .+     `8888  `-*""   /   ^"8888*"     "*888*P"    `%88%``"*888Y"     "*88*" 8888"
        `*88.      :88%     "88888%      'Y"          'Y"    m888N= 888>  "88888%         "888.      :"       "Y"         'Y"         `~     `"          ""   'Y"
           ^"~====""`         "YP'                            `Y"   888     "YP'            `""***~"`
                                                                   J88"
                                                                   @%
                                                                 :"
)";

const char* FINAL_IMAGE = R"(
                                                         ;&     X$
                                                         &  & &  &
                                                        &  & XX&  &
                                                        &  &+&X&  &
                                                        &  &:X$&  &
                       &&&                              &  &&$&& ;&                              &&&
                      &   &                              &  &&&  &                              &   &
                       &  &                               &     &                               &  &
                         &&                               &    ;&                               &x;
      &&;                x &                              &     &                              & X                :&&
     &   &               & &+                            &      :&                             & &               &   &
      &  $               &  &          .+               &        :&               ;:          &  &               ;  $
        &&               &   &;       && &             &     &    ;&             & X&        &   &               &&
         &&$             &    &+       &+;            &    &:&&&   .&             x&       .&    &             ;&&
          $ &    &&&    .&     &&     &  &&         X&    &  ;&&&    &&         &&  &+    $&     &+    &&&    & &.
          &; &    &&X   &       &&  &$    ;&.      &X   X&.  X&X&&:   &&       &+    x&  &+      x&   ;&&    & X&
           &  &&   x.&& &         &&    .   +&&  &&     &  ;&&;$X&&     &&  &&X   .    &&         & &&:;:  &&  &
            &  +&  ;   &;          :&$        &&&       &  & &&$Xx&       &&&        &&           +&   .: &.  &
            &:   +&&$&&      &&       &&&&&&&X          &  &   &$+&          &&&&&&&&       &&      &&&&&    x&
            &&              &  &&                       &  &&X ;$X&                       & &&&              &&
            &&&             &X&&&X                      &  &X+&&$&&                      x&&&&&             &&&
              &              &&&&                        &&&$$$$&&                        &&&&             x&:
               &                                          $&&X&&&                                          &
              :&                                            &&&                                           +&:
              &  +&&&&&&&&&&+;:.                                                             :+$&&&&&&&&X$  &
               &&                  ;&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&:                .;&&
               x  +&&&&&&&&&;                                                             ;X&&&&&&&&&&&&   X
               &             X&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&$$+           .+&
               &                                                                                         ::&
               &              &&                                                           &&           :. &
              &&             xx +                           +&$                           +:&$          :  &&
               &&           ::   ;                         &   &                         .. + ;         ; $&
                X            &  &                          & & &                          &  &          ; $
                &             &&                            & &                            &&           ; &
                &                                            &                                            &
               & &&&;                                                                                  &&&+&:
               &        :&&&&&&&&&&&&&&&&&&&&&&&&$$$Xxx+;;:::.:..::::;+xxXX$$&&&&&&&&&&&&&&&&&&&&;         &
                 +&&&&&&;                                                                       X&&&&&&&&&;
)";

const int numero_colunas = 23;
const int numero_linhas = 23;

// Variável global que define se o usuário ganhou o jogo
bool ganhou_o_jogo = false;

// Variável da matriz do labirinto
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



// Função principal do jogo que alterna entre o menu e o jogo -------------------------------------------

int main()
{
    // Declara o encoding do programa como Português, que permite acentos, cecedilha, etc.
    //setlocale(LC_ALL, "Portuguese");

    // Escopo do Menu do jogo ---------------------------------------------------------
    int opcao_escolhida = 1;

    while (true){

        monta_menu(opcao_escolhida);

        char key = getch();
        key = (char)tolower(key);

        switch(key){
            case 'w':
                ((opcao_escolhida - 1) >= 1) ? opcao_escolhida-- : 0;
                break;
            case 's':
                ((opcao_escolhida + 1) <= 3) ? opcao_escolhida++ : 0;
                break;
            default:
                break;
        }
    }

    // Escopo do jogo ------------------------------------------------------------------s
    if (opcao_escolhida == 1){
        int position_x = 11, position_y = 11;

        while(true){
            system("cls");
            monta_mapa(position_x, position_y);

            char key = getch();
            key = (char)tolower(key);

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
                cout<<FINAL_IMAGE;
                cout<<"Você ganhou o jogo!"<<endl;
                cin.get();
                break;
            }
        }
    }

    return 0;
}

// Funções auxiliares do jogo ----------------------------------------------------------------------------

void monta_menu(int opcao_escolhida){
    system("cls");

    cout<<endl<<endl<<endl;

    cout<<"\033[35m";
    cout<<LOGO_GAME;
    cout<<"\x1B[0m";

    cout<<"     ";
    (opcao_escolhida == 1) ? cout<<">>" : cout<<"  ";
    cout<<" Novo Jogo "<< endl;

    cout<<"     ";
    (opcao_escolhida == 2) ? cout<<">>" : cout<<"  ";
    cout<<" Sair "<< endl;

    cout<<endl<<endl;
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




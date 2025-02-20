#include <iostream> // Biblioteca nativa para por exemplo imprimir textos.
#include <conio.h> // Biblioteca nativa para por exemplo ler teclas sem o CIN
#include <windows.h> // Biblioteca nativa para configurar a tela do console por exemplo

// Configuração para habilitar cores no terminal
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

// Definindo o código das teclas
#define ENTER_KEY 13
#define UP_ARROW_KEY 72
#define RIGHT_ARROW_KEY 77
#define DOWN_ARROW_KEY 80
#define LEFT_ARROW_KEY 75
#define ESC_KEY 27

using namespace std;

/*
  Jogo - Get the Crown

  ->> Função Monta Menu:
        Escopo: mostrar o menu de navega��o para o usu�rio.
        Par�metros de entrada: Op��o que vai ser exibida como a atual.
        Retorno da função: Vazio (ou seja, n�o retorna nada)

  ->> Função Monta Mapa:
        Escopo: mostrar o labirinto para o usu�rio.
        Par�metros de entrada: A posi��o X e posi��o Y real que o jogador est�.
        Retorno da função: Vazio (ou seja, n�o retorna nada)

  ->> Função Tenta Monta Mapa:
        Escopo: observa a posi��o desejada e calcula se o jogador pode ir no espa�o desejado ou n�o.
        Par�metros de entrada: A posi��o X e posi��o Y desejada para ficar no mapa.
        Retorno da função: Booleano (ou seja, verdadeiro se a posi��o � v�lida, e falso se a posi��o � inv�lida)

  ->> Função Identifica Teclas Computador:
        Escopo: recebe a tecla de entrada e retorna um número relacionado à tecla.
        Par�metros de entrada: a tecla de entrada.
        Retorno da função: Inteiro (será o código da tecla de entrada ou -1 se for uma tecla inválida)

  ->> Função Limpar Tela:
        Escopo: limpa a tela do console a cada chamada.
        Parâmetros de entrada: Nenhum.
        Retorno da função: Vazio (ou seja, não retorna nada)
*/



// Declarando as funções do programa antes de começar, para não ocorrer um erro de NÃO-EXIST�NCIA das funções
void monta_menu(int opcao_escolhida);
void monta_mapa(int position_x, int position_y);
bool tenta_montar_mapa(int position_x, int position_y);
int identifica_teclas_computador(int first_key);
void limpar_tela();

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



           __ __   ___   __ __      __    __  ____  ____       ______  __ __    ___       ____   ____  ___ ___    ___
          |  |  | /   \ |  |  |    |  |__|  ||    ||    \     |      ||  |  |  /  _]     /    | /    ||   |   |  /  _]
          |  |  ||     ||  |  |    |  |  |  | |  | |  _  |    |      ||  |  | /  [_     |   __||  o  || _   _ | /  [_
          |  ~  ||  O  ||  |  |    |  |  |  | |  | |  |  |    |_|  |_||  _  ||    _]    |  |  ||     ||  \_/  ||    _]
          |___, ||     ||  :  |    |  `  '  | |  | |  |  |      |  |  |  |  ||   [_     |  |_ ||  _  ||   |   ||   [_
          |     ||     ||     |     \      /  |  | |  |  |      |  |  |  |  ||     |    |     ||  |  ||   |   ||     |
          |____/  \___/  \__,_|      \_/\_/  |____||__|__|      |__|  |__|__||_____|    |___,_||__|__||___|___||_____|
)";

// Vari�vel global que define se o usu�rio ganhou o jogo
bool ganhou_o_jogo = false;

// Vari�vel global que define se o usuário quer encerrar o jogo
bool abortar_jogo = false;

// Vari�vel global que define a opção escolhida do usuário
int opcao_escolhida = 1;

// Vari�vel global que define se o usuário escolheu alguma opção
bool escolheu_opcao = false;


const int numero_colunas = 23;
const int numero_linhas = 23;

// Vari�vel da matriz do labirinto -----------------------------------------------------------------------
int matriz_labirinto[numero_linhas][numero_colunas] = {
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1},
    {1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1},
    {1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1},
};

// Setup da tela do Console
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO csbi;
DWORD count;
DWORD cellCount;
DWORD dwMode = 0;
COORD homeCoords = {0, 0};

void setup_console_screen(){
    if (hConsole == INVALID_HANDLE_VALUE) return;

    if (GetConsoleMode(hConsole, &dwMode)) {
        SetConsoleMode(hConsole, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    }
}

// Fun��o principal do jogo que alterna entre o menu e o jogo -------------------------------------------
int main()
{
    setup_console_screen();

    // Declara o encoding do programa como Português, que permite acentos, etc.
    setlocale(LC_ALL, "Portuguese");

    while (true){

        ganhou_o_jogo = false;
        abortar_jogo = false;

        // Escopo do Menu do jogo ---------------------------------------------------------
        escolheu_opcao = false;
        opcao_escolhida = 1;

        while (!escolheu_opcao){

            monta_menu(opcao_escolhida);

            int tecla_pressionada = identifica_teclas_computador(getch());

            switch(tecla_pressionada) {
                case ENTER_KEY:
                    escolheu_opcao = true;
                    break;
                case UP_ARROW_KEY:
                    ((opcao_escolhida - 1) >= 1) ? opcao_escolhida-- : 0;
                    // Se a opção anterior à atual for válida, então troca para a opção anterior
                    break;
                case DOWN_ARROW_KEY:
                    ((opcao_escolhida + 1) <= 2) ? opcao_escolhida++ : 0;
                    // Se a próxima opção à atual for válida, então troca para a próxima opção
                    break;
                default:
                    break;
            }
        }

        // Escopo do jogo ------------------------------------------------------------------
        if (opcao_escolhida == 1){
            int position_x = 1, position_y = 0;

            while(!ganhou_o_jogo && !abortar_jogo){
                limpar_tela();
                monta_mapa(position_x, position_y);

                int tecla_pressionada = identifica_teclas_computador(getch());


                // Esquema da matriz -----------------------------------
                // ESQUERDA -> Diminui 1 ponto em X e mantém o mesmo Y
                // CIMA -> Mantém o mesmo ponto X e diminui 1 ponto em Y
                // DIREITA -> Adiciona 1 ponto em X e mantém o mesmo Y
                // BAIXO -> Mantém o mesmo ponto X e adiciona 1 ponto em Y

                switch(tecla_pressionada) {
                    case ESC_KEY:
                        abortar_jogo = true;
                        break;
                    case LEFT_ARROW_KEY:
                        if (tenta_montar_mapa(position_x - 1, position_y))
                            position_x--;
                        break;
                    case UP_ARROW_KEY:
                        if (tenta_montar_mapa(position_x, position_y - 1))
                            position_y--;
                        break;
                    case RIGHT_ARROW_KEY:
                        if (tenta_montar_mapa(position_x + 1, position_y))
                            position_x++;
                        break;
                    case DOWN_ARROW_KEY:
                        if (tenta_montar_mapa(position_x, position_y + 1))
                            position_y++;
                        break;
                    default:
                        break;
                }
            }

            if (ganhou_o_jogo){
                limpar_tela();
                cout<<"\033[35m"; // Código da cor violeta
                cout<<FINAL_IMAGE;
                cout<<"\x1B[0m"; // Código da cor branca
                cin.get();
            }
        }

        // Finaliza o menu e o jogo ----------------------------------------------------------------
        if (opcao_escolhida == 2){
            break;
        }
    }

    return 0;
}

// Funções auxiliares do jogo ----------------------------------------------------------------------------

int identifica_teclas_computador(int first_key)
{
    if (first_key == ENTER_KEY) {  // ENTER
        return ENTER_KEY;
    }
    else if (first_key == ESC_KEY) {  // ESC
        return ESC_KEY;
    }
    else if (first_key == 'w' || first_key == 'W') {
        return UP_ARROW_KEY;
    }
    else if (first_key == 'a' || first_key == 'A') {
        return LEFT_ARROW_KEY;
    }
    else if (first_key == 's' || first_key == 'S') {
        return DOWN_ARROW_KEY;
    }
    else if (first_key == 'd' || first_key == 'D') {
        return RIGHT_ARROW_KEY;
    }
    else if (first_key == 0 || first_key == 224) {  // Se o getch enviou um segundo código...
        int second_key = getch();  // Obter o segundo código

        switch (second_key) {
            case UP_ARROW_KEY:
                return UP_ARROW_KEY;

            case LEFT_ARROW_KEY:
                return LEFT_ARROW_KEY;

            case RIGHT_ARROW_KEY:
                return RIGHT_ARROW_KEY;

            case DOWN_ARROW_KEY:
                return DOWN_ARROW_KEY;

            default:
                break;
        }
    }

    return -1;
}

void monta_menu(int opcao_escolhida){
    limpar_tela();

    cout<<endl<<endl<<endl;

    cout<<"\033[35m"; // Código da cor violeta
    cout<<LOGO_GAME;
    cout<<"\x1B[0m"; // Código da cor branca

    cout<<"     ";
    // Se a opção escolhida for igual a 1 aparece um sinalizador que é ela a escolhida, senão não aparece nada
    (opcao_escolhida == 1) ? cout<<">>" : cout<<"  ";
    cout<<" Novo Jogo "<< endl;

    cout<<"     ";
    // Se a opção escolhida for igual a 2 aparece um sinalizador que é ela a escolhida, senão não aparece nada
    (opcao_escolhida == 2) ? cout<<">>" : cout<<"  ";
    cout<<" Sair "<< endl;

    cout<<endl<<endl;
}

void monta_mapa(int position_x, int position_y){
    limpar_tela();
    cout<<endl<<endl<<endl;

    for (int y = 0; y < numero_colunas; y++){ // Para cada coluna da matriz...
        cout<<"           ";
        (y + 1 < 10) ? cout<<"0" : cout<<"";
        cout<<y+1<<" ";
        for(int x = 0; x < numero_linhas; x++){ // Para cada linha da matriz...

            if (x == position_x && y == position_y) // Se a posição X e posição Y da vez for a posição exata do jogador, então:
                cout<<"\033[32m" << "@ " << "\x1B[0m"; // Código do verde

            else{
                switch(matriz_labirinto[y][x]){
                    // Se a posição X e posição Y da vez tiver um valor específico:
                    case 0:
                        cout<<"\x1B[0m" << " " << "\x1B[0m"; // Código da cor branca
                        break;
                    case 1:
                        cout<<"\x1B[0m"<< "o" << "\x1B[0m";
                        //cout<<"\033[31m" << "X" << "\x1B[0m"; // Código da cor vermelha
                        break;
                    case 2:
                        cout<<"\x1B[33m" << "&" << "\x1B[0m"; // Código da cor amarela
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

bool tenta_montar_mapa(int position_x, int position_y){
    bool pode_montar_o_mapa = false; // Começa com o estado falso

    if (position_x < numero_linhas && position_x >= 0){ // Se a posição X desejada estiver no range de linhas e não for negativa
        if (position_y < numero_colunas && position_y >= 0){ // Se a posição Y desejada estiver no range de colunas e não for negativa

            // Se a posição (x,y) desejada estiver em um ponto específico...
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

void limpar_tela() {

    // Contar o número de células do console
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) return;
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    // Preenche as células do console
    FillConsoleOutputCharacter(hConsole, ' ', cellCount, homeCoords, &count);

    // Reseta a posição do cursor
    SetConsoleCursorPosition(hConsole, homeCoords);

}




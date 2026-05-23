#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>/*nova regra by M*/

/* === PROTOTIPO DAS FUNCOES === */
void exibirTutorial();
void exibirCreditos();
void iniciarVila();
void iniciarMasmorra1(int vidas, char nomeArma[], int alcanceArma, int jaPegouArma);
void iniciarMasmorra2(int vidas, char nomeArma[], int alcanceArma, int jaPegouArma);/*2novas funções by mario, masmorra2 e monstro*/
void moverMonstroX(char mapa[15][16], int *monstroX, int *monstroY, int jogadorX, int jogadorY);

/* === FUNCAO PRINCIPAL === */
int main() {
    int comando;
    int continuar = 1;

    srand(time(NULL));/*IA adicionou essa, mas n entendi pq by M*/

    while (continuar) {
        system("cls");

        printf("--------------------------------------\n");
        printf("        DUNGEON CRAWLER: NEOGENESE\n");
        printf("--------------------------------------\n");
        printf("1 - Jogar\n");
        printf("2 - Tutorial\n");
        printf("3 - Sair / Creditos\n");
        printf("\nEscolha seu comando (1, 2 ou 3): ");

        if (scanf("%d", &comando) != 1) {
            printf("\nErro: Digite apenas numeros!\n");
            while (getchar() != '\n');
            printf("Pressione qualquer tecla para tentar novamente...");
            getch();
            continue;
        }

        switch (comando) {
            case 1:
                iniciarVila();
                break;
            case 2:
                exibirTutorial();
                break;
            case 3:
                exibirCreditos();
                continuar = 0;
                break;
            default:
                printf("\nComando invalido!\n");
                printf("Pressione qualquer tecla para voltar...");
                getch();
                break;
        }
    }

    return 0;
}

/* === FUNCAO DA VILA === */
void iniciarVila() {
    char tecla;
    int x = 1, y = 1;
    int proxX, proxY;
    int i, j;
    int vidas = 3;
    char simbolo = '>';

    int opcaoArma;
    int alcanceArma = 0;
    char nomeArma[20];
    strcpy(nomeArma, "Nenhuma");
    int jaPegouArma = 0;

    char mapa[10][11] = {
        "**********",
        "*        *",
        "**       *",
        "*N       *",
        "**       *",
        "*        *",
        "*   * *  *",
        "*  #* *# *",
        "* #**L**#*",
        "**********"
    };

    while (1) {
        system("cls");

        char caractereOriginal = mapa[x][y];
        mapa[x][y] = simbolo;

        printf("              --- VILA DE NEOGENESE ---\n\n");
        printf("Vidas: %d | Arma: %s | Use WASD | O Ataca | M Sair\n\n", vidas, nomeArma);

        for (i = 0; i < 10; i++) {
            for (j = 0; j < 10; j++) {
                printf("%c ", mapa[i][j]);
            }
            printf("\n");
        }

        mapa[x][y] = caractereOriginal;

        tecla = getch();

        if (tecla == 'm' || tecla == 'M') {
            break;
        }

        proxX = x;
        proxY = y;

        if (tecla == 'w' || tecla == 'W') {
            proxX--;
            simbolo = '^';
        }
        else if (tecla == 's' || tecla == 'S') {
            proxX++;
            simbolo = 'v';
        }
        else if (tecla == 'a' || tecla == 'A') {
            proxY--;
            simbolo = '<';
        }
        else if (tecla == 'd' || tecla == 'D') {
            proxY++;
            simbolo = '>';
        }
        else if (tecla == 'o' || tecla == 'O') {
            if (jaPegouArma == 0) {
                printf("\n[AVISO]: Voce nao tem uma arma equipada para atacar!\n");
            } else {
                printf("\nVoce atacou!\n");
            }

            printf("Pressione qualquer tecla para continuar...");
            getch();
            continue;
        }
        else {
            continue;
        }

        if (mapa[proxX][proxY] == 'N') {
            if (jaPegouArma == 1) {
                printf("\n[NPC]: Voce ja escolheu seu equipamento, heroi!\n");
            } else {
                printf("\n[NPC]: Ola heroi! Escolha sua arma:\n");
                printf("1 - Espada\n");
                printf("2 - Cajado\n");
                printf("3 - Arco e Flecha\n");
                printf("Escolha: ");

                if (scanf("%d", &opcaoArma) != 1) {
                    opcaoArma = 0;
                }

                while (getchar() != '\n');

                switch (opcaoArma) {
                    case 1:
                        strcpy(nomeArma, "Espada");
                        alcanceArma = 1;
                        jaPegouArma = 1;
                        printf("\nVoce equipou a Espada!\n");
                        break;
                    case 2:
                        strcpy(nomeArma, "Cajado");
                        alcanceArma = 3;
                        jaPegouArma = 1;
                        printf("\nVoce equipou o Cajado!\n");
                        break;
                    case 3:
                        strcpy(nomeArma, "Arco e Flecha");
                        alcanceArma = 5;
                        jaPegouArma = 1;
                        printf("\nVoce equipou o Arco e Flecha!\n");
                        break;
                    default:
                        printf("\nEscolha invalida!\n");
                        break;
                }
            }

            printf("Pressione qualquer tecla para continuar...");
            getch();
            continue;
        }

        if (mapa[proxX][proxY] == 'L') {
            if (jaPegouArma == 0) {
                printf("\n[BLOQUEADO]: Voce precisa pegar uma arma com o NPC antes de entrar na masmorra!\n");
                printf("Pressione qualquer tecla para continuar...");
                getch();
                continue;
            }

            iniciarMasmorra1(vidas, nomeArma, alcanceArma, jaPegouArma);
            break;
        }

        if (mapa[proxX][proxY] != '*') {
            x = proxX;
            y = proxY;
        }
    }
}

/* === FUNCAO DA MASMORRA 1 === acrescentado mais detalhes da movimentação para n entrar na masmorra sem arma*/
void iniciarMasmorra1(int vidas, char nomeArma[], int alcanceArma, int jaPegouArma) {
    char tecla;
    int x = 1, y = 1;
    int proxX, proxY;
    int i, j;
    char simbolo = '>';

    int temChave = 0;

    char mapa[10][11] = {
        "**********",
        "*   k*  L*",
        "* ** *D***",
        "* #*@*k  *",
        "*D****   *",
        "*    *   *",
        "*  ###** *",
        "*  #   k *",
        "*      # *",
        "**********"
    };

    while (1) {
        system("cls");

        char caractereOriginal = mapa[x][y];
        mapa[x][y] = simbolo;

        printf("              --- MASMORRA 1 ---\n\n");
        printf("Vidas: %d | Arma: %s | Chave: %s | Use WASD | O Ataca | M Sair\n\n",
               vidas, nomeArma, temChave ? "Sim" : "Nao");

        for (i = 0; i < 10; i++) {
            for (j = 0; j < 10; j++) {
                printf("%c ", mapa[i][j]);
            }
            printf("\n");
        }

        mapa[x][y] = caractereOriginal;

        tecla = getch();

        if (tecla == 'm' || tecla == 'M') {
            break;
        }

        if (tecla == 'o' || tecla == 'O') {
            int alvoX = x;
            int alvoY = y;

            if (simbolo == '^') alvoX--;
            else if (simbolo == 'v') alvoX++;
            else if (simbolo == '<') alvoY--;
            else if (simbolo == '>') alvoY++;

            if (mapa[alvoX][alvoY] == 'k') {
                mapa[alvoX][alvoY] = ' ';
                printf("\nVoce destruiu uma caixa!\n");
            }
            else if (mapa[alvoX][alvoY] == 'X' || mapa[alvoX][alvoY] == 'Y') {
                mapa[alvoX][alvoY] = ' ';
                printf("\nVoce derrotou um monstro!\n");
            }
            else {
                printf("\nVoce atacou, mas nao acertou nada.\n");
            }

            printf("Pressione qualquer tecla para continuar...");
            getch();
            continue;
        }

        proxX = x;
        proxY = y;

        if (tecla == 'w' || tecla == 'W') {
            proxX--;
            simbolo = '^';
        }
        else if (tecla == 's' || tecla == 'S') {
            proxX++;
            simbolo = 'v';
        }
        else if (tecla == 'a' || tecla == 'A') {
            proxY--;
            simbolo = '<';
        }
        else if (tecla == 'd' || tecla == 'D') {
            proxY++;
            simbolo = '>';
        }
        else {
            continue;
        }

        if (mapa[proxX][proxY] == '*') {
            continue;
        }

        if (mapa[proxX][proxY] == '#') {
            vidas--;

            printf("\nVoce pisou em espinhos e perdeu uma vida!\n");

            if (vidas <= 0) {
                printf("Voce morreu na Masmorra 1!\n");
                printf("Pressione qualquer tecla para voltar ao menu...");
                getch();
                break;
            }

            printf("Voce voltou ao inicio da fase.\n");
            printf("Pressione qualquer tecla para continuar...");
            getch();

            x = 1;
            y = 1;
            continue;
        }

        if (mapa[proxX][proxY] == '@') {
            temChave = 1;
            mapa[proxX][proxY] = ' ';

            printf("\nVoce pegou a chave!\n");
            printf("Pressione qualquer tecla para continuar...");
            getch();
        }

        if (mapa[proxX][proxY] == 'D') {
            if (temChave == 1) {
                mapa[proxX][proxY] = '=';

                printf("\nVoce abriu a porta com a chave!\n");
                printf("Pressione qualquer tecla para continuar...");
                getch();
            } else {
                printf("\nA porta esta trancada. Encontre a chave '@'.\n");
                printf("Pressione qualquer tecla para continuar...");
                getch();
                continue;
            }
        }

        if (mapa[proxX][proxY] == 'O') {
            mapa[proxX][proxY] = ' ';
            mapa[6][2] = ' ';
            mapa[6][3] = ' ';
            mapa[6][4] = ' ';

            printf("\nVoce ativou o botao! Alguns espinhos desapareceram.\n");
            printf("Pressione qualquer tecla para continuar...");
            getch();
        }

        if (mapa[proxX][proxY] == 'X' || mapa[proxX][proxY] == 'Y') {
            vidas--;

            printf("\nUm monstro te atacou! Voce perdeu uma vida.\n");

            if (vidas <= 0) {
                printf("Voce morreu na Masmorra 1!\n");
                printf("Pressione qualquer tecla para voltar ao menu...");
                getch();
                break;
            }

            printf("Pressione qualquer tecla para continuar...");
            getch();
            continue;
        }

        if (mapa[proxX][proxY] == 'k' || mapa[proxX][proxY] == 'K') {
            printf("\nUma caixa bloqueia o caminho. Use O para atacar e destrui-la.\n");
            printf("Pressione qualquer tecla para continuar...");
            getch();
            continue;
        }

        if (mapa[proxX][proxY] == 'L') {
            iniciarMasmorra2(vidas, nomeArma, alcanceArma, jaPegouArma);
            break;
        }

        x = proxX;
        y = proxY;
    }
}

/* === MOVE O MONSTRO X DA MASMORRA 2 === feito by M*/
void moverMonstroX(char mapa[15][16], int *monstroX, int *monstroY, int jogadorX, int jogadorY) {
    int direcao = rand() % 4;
    int novoX = *monstroX;
    int novoY = *monstroY;

    if (direcao == 0) novoX--;
    else if (direcao == 1) novoX++;
    else if (direcao == 2) novoY--;
    else if (direcao == 3) novoY++;

    if (novoX == jogadorX && novoY == jogadorY) {
        return;
    }

    if (mapa[novoX][novoY] == ' ') {
        mapa[*monstroX][*monstroY] = ' ';
        *monstroX = novoX;
        *monstroY = novoY;
        mapa[*monstroX][*monstroY] = 'X';
    }
}

/* === FUNCAO DA MASMORRA 2 === feito by M*/
void iniciarMasmorra2(int vidas, char nomeArma[], int alcanceArma, int jaPegouArma) {
    char tecla;
    int x = 1, y = 1;
    int proxX, proxY;
    int i, j;
    char simbolo = '>';

    int temChave = 0;
    int monstro1X = 11;
    int monstro1Y = 1;
    int monstro2X = 12;
    int monstro2Y = 1;
    

    char mapa[15][16] = {
        "***************",
        "* *  *L*    k *",
        "* *  KKK    k *",
        "* *           *",
        "*   K#    k#  *",
        "*             *",
        "* **********  *",
        "*             *",
        "* * ##  **D****",
        "*       *   * *",
        "*       * O * *",
        "*X*@    *   *@*",
        "*X      *   * *",
        "***************",
        "***************"
    };

    while (1) {
        system("cls");

        char caractereOriginal = mapa[x][y];
        mapa[x][y] = simbolo;

        printf("              --- MASMORRA 2 ---\n\n");
        printf("Vidas: %d | Arma: %s | Chave: %s | Use WASD | O Ataca | M Sair\n\n",
               vidas, nomeArma, temChave ? "Sim" : "Nao");

        for (i = 0; i < 15; i++) {
            for (j = 0; j < 15; j++) {
                printf("%c ", mapa[i][j]);
            }
            printf("\n");
        }

        mapa[x][y] = caractereOriginal;

        tecla = getch();

        if (tecla == 'm' || tecla == 'M') {
            break;
        }

        if (tecla == 'o' || tecla == 'O') {
            int alvoX = x;
            int alvoY = y;

            if (simbolo == '^') alvoX--;
            else if (simbolo == 'v') alvoX++;
            else if (simbolo == '<') alvoY--;
            else if (simbolo == '>') alvoY++;

            if (mapa[alvoX][alvoY] == 'k' || mapa[alvoX][alvoY] == 'K') {
                mapa[alvoX][alvoY] = ' ';
                printf("\nVoce destruiu uma caixa!\n");
            }
            else if (mapa[alvoX][alvoY] == 'X') {
                mapa[alvoX][alvoY] = ' ';

                if (alvoX == monstro1X && alvoY == monstro1Y) {
                    monstro1X = -1;
                    monstro1Y = -1;
                }
                else if (alvoX == monstro2X && alvoY == monstro2Y) {
                    monstro2X = -1;
                    monstro2Y = -1;
                }

                printf("\nVoce derrotou o monstro X!\n");
            }
            else {
                printf("\nVoce atacou, mas nao acertou nada.\n");
            }

            printf("Pressione qualquer tecla para continuar...");
            getch();

            if (monstro1X != -1) {
                moverMonstroX(mapa, &monstro1X, &monstro1Y, x, y);
            }
            if (monstro2X != -1) {
                moverMonstroX(mapa, &monstro2X, &monstro2Y, x, y);
            }

            continue;
        }

        proxX = x;
        proxY = y;

        if (tecla == 'w' || tecla == 'W') {
            proxX--;
            simbolo = '^';
        }
        else if (tecla == 's' || tecla == 'S') {
            proxX++;
            simbolo = 'v';
        }
        else if (tecla == 'a' || tecla == 'A') {
            proxY--;
            simbolo = '<';
        }
        else if (tecla == 'd' || tecla == 'D') {
            proxY++;
            simbolo = '>';
        }
        else {
            continue;
        }

        if (mapa[proxX][proxY] == '*') {
            continue;
        }

        if (mapa[proxX][proxY] == '#') {
            vidas--;

            printf("\nVoce pisou em espinhos e perdeu uma vida!\n");

            if (vidas <= 0) {
                printf("Voce morreu na Masmorra 2!\n");
                printf("Pressione qualquer tecla para voltar ao menu...");
                getch();
                break;
            }

            printf("Voce voltou ao inicio da fase.\n");
            printf("Pressione qualquer tecla para continuar...");
            getch();

            x = 1;
            y = 1;
            continue;
        }

        if (mapa[proxX][proxY] == '@') {
            temChave = 1;
            mapa[proxX][proxY] = ' ';

            printf("\nVoce pegou a chave!\n");
            printf("Pressione qualquer tecla para continuar...");
            getch();
        }

        if (mapa[proxX][proxY] == 'D') {
            if (temChave == 1) {
                mapa[proxX][proxY] = '=';

                printf("\nVoce abriu a porta com a chave!\n");
                printf("Pressione qualquer tecla para continuar...");
                getch();
            } else {
                printf("\nA porta esta trancada. Encontre a chave '@'.\n");
                printf("Pressione qualquer tecla para continuar...");
                getch();
                continue;
            }
        }

        if (mapa[proxX][proxY] == 'O') {
            mapa[proxX][proxY] = ' ';

            /* Paredes  da imagem: removidas somente neste mapa 15x15 */
            mapa[8][8] = ' ';
            mapa[8][9] = ' ';
            mapa[8][11] = ' ';
            mapa[8][12] = ' ';
            mapa[8][13] = ' ';
            mapa[9][8] = ' ';
            mapa[9][12] = ' ';
            mapa[10][8] = ' ';
            mapa[10][12] = ' ';
            mapa[11][8] = ' ';
            mapa[11][12] = ' ';

            printf("\nParedes destruidas\n");
            printf("Pressione qualquer tecla para continuar...");
            getch();
        }

        if (mapa[proxX][proxY] == 'X') {
            vidas--;

            printf("\nO monstro X te atacou! Voce perdeu uma vida.\n");

            if (vidas <= 0) {
                printf("Voce morreu na Masmorra 2!\n");
                printf("Pressione qualquer tecla para voltar ao menu...");
                getch();
                break;
            }

            printf("Pressione qualquer tecla para continuar...");
            getch();
            continue;
        }

        if (mapa[proxX][proxY] == 'k' || mapa[proxX][proxY] == 'K') {
            printf("\nUma caixa bloqueia o caminho. Use O para atacar e destrui-la.\n");
            printf("Pressione qualquer tecla para continuar...");
            getch();
            continue;
        }

        if (mapa[proxX][proxY] == 'L') {
            system("cls");
            printf("--------------------------------------------\n");
            printf("         VOCE CONCLUIU A MASMORRA 2!\n");
            printf("--------------------------------------------\n\n");
            printf("Pressione qualquer tecla para voltar ao menu...");
            getch();
            break;
        }

        x = proxX;
        y = proxY;

        if (monstro1X != -1) {
            moverMonstroX(mapa, &monstro1X, &monstro1Y, x, y);
        }

        if (monstro2X != -1) {
            moverMonstroX(mapa, &monstro2X, &monstro2Y, x, y);
        }

        if ((monstro1X != -1 && ((monstro1X == x && monstro1Y == y) ||
             (abs(monstro1X - x) + abs(monstro1Y - y) == 1))) ||
            (monstro2X != -1 && ((monstro2X == x && monstro2Y == y) ||
             (abs(monstro2X - x) + abs(monstro2Y - y) == 1)))) {
            vidas--;

            printf("\nUm monstro X chegou perto e te atacou! Voce perdeu uma vida.\n");

            if (vidas <= 0) {
                printf("Voce morreu na Masmorra 2!\n");
                printf("Pressione qualquer tecla para voltar ao menu...");
                getch();
                break;
            }

            printf("Pressione qualquer tecla para continuar...");
            getch();
        }
    }
}

/* === FUNCAO TUTORIAL === */
void exibirTutorial() {
    system("cls");

    printf("--------------------------------------------\n");
    printf("                 TUTORIAL                  \n");
    printf("--------------------------------------------\n\n");

    printf("HISTORIA\n\n");
    printf("No mundo de Neogenese, um grupo de pessoas que desejavam liberar\n");
    printf("um demonio antigo com intuito de dominar o mundo vem usando os\n");
    printf("civis como fonte de energia para os seus rituais em uma torre,\n");
    printf("absorvendo suas energias vitais enquanto permanecem presos durante\n");
    printf("o periodo de preparacao para a invocacao deste demonio no mundo\n");
    printf("terreno.\n\n");
    printf("Os reinos humanos se aliaram e criaram uma base de controle para\n");
    printf("auxiliar voce: um aventureiro prestes a enfrentar o seu maior\n");
    printf("desafio.\n\n");
    printf("A base dos cultistas tem 3 niveis com entradas secretas e monstros\n");
    printf("Pegue sua arma e salve o mundo dessa ameaca Sobre-Humana!\n\n");

    printf("--------------------------------------------\n");
    printf("COMANDOS DO JOGO\n");
    printf("--------------------------------------------\n\n");

    printf(" - Use as teclas W, A, S, D para andar.\n");
    printf(" - Use a tecla O para atacar.\n");
    printf(" - Encontre o NPC 'N' para conseguir uma arma.\n");
    printf(" - Va ate a saida 'L' para progredir.\n\n");

    printf("--------------------------------------------\n");
    printf("LISTA DE SIMBOLOS\n");
    printf("--------------------------------------------\n\n");

    printf("< ^ > v : Jogador e direcao.\n");
    printf("@ : Chave.\n");
    printf("D : Porta Fechada.\n");
    printf("= : Porta Aberta.\n");
    printf("L : Escada.\n");
    printf("O : Botao.\n");
    printf("* : Parede.\n");
    printf("# : Espinho.\n");
    printf("k : Caixa.\n");
    printf("X : Monstro Tipo 1.\n");
    printf("Y : Monstro Tipo 2.\n");
    printf("Z : Boss Final.\n\n");

    printf("Pressione qualquer tecla para voltar ao menu...");
    getch();
}

/* === FUNCAO CREDITOS === */
void exibirCreditos() {
    system("cls");
    printf("--------------------------------------\n");
    printf("              CREDITOS\n");
    printf("--------------------------------------\n");
    printf("Desenvolvido por:\n");
    printf("- Jose Pedro Martins\n");
    printf("- Mario Henrique\n");
    printf("- Vinicius Carreiro\n");
    printf("\nSaindo do jogo... Obrigado por jogar!\n");
    printf("Pressione qualquer tecla para fechar...");

    getch();
}

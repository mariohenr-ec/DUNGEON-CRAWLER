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
void iniciarMasmorra2(int vidas, char nomeArma[], int alcanceArma, int jaPegouArma);/*2novas funÃƒÂ§oesÃ¢â‚¬Å¡Ãƒâ€šÃ‚Â§oes by mario, masmorra2 e monstro*/
void iniciarMasmorra3(int vidas, char nomeArma[], int alcanceArma, int jaPegouArma);
void iniciarCorredorFinal(int vidas, char nomeArma[], int alcanceArma, int jaPegouArma);
void moverMonstroX(char mapa[15][16], int *monstroX, int *monstroY, int jogadorX, int jogadorY);
void moverMonstroY(char mapa[25][26], int *monstroX, int *monstroY, int jogadorX, int jogadorY);
void trocarBossZcomY(char mapa[25][26], int *zX, int *zY, int *yX, int *yY);
int jogadorEstaDeCostasParaZ(int jogadorX, int jogadorY, int zX, int zY, char simbolo);
void criarNovoY(char mapa[25][26], int zX, int zY, int *yX, int *yY);
void criarMonstroXAleatorio(char mapa[25][26], int xMonstros[], int yMonstros[], int *qtdX);
void moverMonstrosX3(char mapa[25][26], int xMonstros[], int yMonstros[], int qtdX, int jogadorX, int jogadorY);
void imprimirCaractereColorido(char c); /* Nova funcao padrao de cores - J */
void exibirGameOver(); /* Nova funcao adicionada */
void exibirFinalJogo(); /* Tela final narrativa */
int estaNaAreaAtaque(int jogadorX, int jogadorY, char simbolo, char nomeArma[], int alvoX, int alvoY);

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

/* === FUNCAO DE CORES PADRAO === */
void imprimirCaractereColorido(char c) {
    switch (c) {
        case '*': // Parede - Cinza
            printf("\033[90m%c \033[0m", c);
            break;
        case '#': // Espinhos - Verde Escuro
            printf("\033[32m%c \033[0m", c);
            break;
        case 'D': // Porta Fechada - Dourado / Amarelo Ouro
        case '=': // Porta Aberta - Dourado / Amarelo Ouro
        case '@': // Chave - Dourado / Amarelo Ouro
            printf("\033[93m%c \033[0m", c);
            break;
        case '^': case 'v': case '<': case '>': // Jogador - Azul
            printf("\033[94m%c \033[0m", c);
            break;
        case 'L': // Escada - Branca
            printf("\033[97m%c \033[0m", c);
            break;
        case 'k': case 'K': // Caixas - Laranja terroso / Marrom
            printf("\033[38;5;130m%c \033[0m", c); 
            break;
        case 'O': // Botao
            printf("\033[95m%c \033[0m", c);
            break;
        case 'Q': // NPC do corredor final - Ciano Brilhante
        case 'F': // Ferreiro - Ciano Brilhante
            printf("\033[96m%c \033[0m", c);
            break;
        case 'X': // Monstro X - Amarelo Claro
            printf("\033[93m%c \033[0m", c);
            break;
        case 'Y': // Monstro Y - Laranja
            printf("\033[38;5;208m%c \033[0m", c);
            break;
        case 'Z': // Boss Z - Vermelho Vivo
            printf("\033[91m%c \033[0m", c);
            break;
        default: // Outros elementos e espaco vazio
            printf("%c ", c);
            break;
    }
}

/* === FUNCAO DE GAME OVER === */
void exibirGameOver() {
    system("cls");
    printf("\033[91m");
    printf("        ######      ###    ##     ## ########     #######  ##     ## ######## ########  \n");
    printf("       ##    ##    ## ##   ###   ### ##          ##     ## ##     ## ##       ##     ## \n");
    printf("       ##         ##   ##  #### #### ##          ##     ## ##     ## ##       ##     ## \n");
    printf("       ##   #### ##     ## ## ### ## ######      ##     ## ##     ## ######   ########  \n");
    printf("       ##    ##  ######### ##     ## ##          ##     ##  ##   ##  ##       ##   ##   \n");
    printf("       ##    ##  ##     ## ##     ## ##          ##     ##   ## ###   ##       ##    ##  \n");
    printf("        ######   ##     ## ##     ## ########     #######     ###     ######## ##     ## \n");
    printf("\033[0m");
    printf("\n\n");
    printf("                     Pressione qualquer tecla para voltar ao menu inicial...");
    getch();
}


/* === VERIFICA A AREA DE ATAQUE DE CADA ARMA === */
int estaNaAreaAtaque(int jogadorX, int jogadorY, char simbolo, char nomeArma[], int alvoX, int alvoY) {
    int dx = alvoX - jogadorX;
    int dy = alvoY - jogadorY;
    int dist;

    /* Cajado: atinge 1 celula ao redor do jogador, sem depender da direcao. */
    if (strcmp(nomeArma, "Cajado") == 0) {
        if (dx >= -1 && dx <= 1 && dy >= -1 && dy <= 1 && !(dx == 0 && dy == 0)) {
            return 1;
        }
        return 0;
    }

    /* Arco e Flecha: atinge ate 4 celulas na frente da visao do jogador. */
    if (strcmp(nomeArma, "Arco e Flecha") == 0) {
        for (dist = 1; dist <= 4; dist++) {
            if (simbolo == '^' && alvoX == jogadorX - dist && alvoY == jogadorY) return 1;
            if (simbolo == 'v' && alvoX == jogadorX + dist && alvoY == jogadorY) return 1;
            if (simbolo == '<' && alvoX == jogadorX && alvoY == jogadorY - dist) return 1;
            if (simbolo == '>' && alvoX == jogadorX && alvoY == jogadorY + dist) return 1;
        }
        return 0;
    }

    /* Espada: mantem o ataque de 3x2 celula na frente. */
    if (strcmp(nomeArma, "Espada") == 0) {
    /* Direita */
    if (simbolo == '>' &&
        alvoX >= jogadorX - 1 &&
        alvoX <= jogadorX + 1 &&
        alvoY >= jogadorY + 1 &&
        alvoY <= jogadorY + 2) {
        return 1;
    }
    /* Esquerda */
    if (simbolo == '<' &&
        alvoX >= jogadorX - 1 &&
        alvoX <= jogadorX + 1 &&
        alvoY >= jogadorY - 2 &&
        alvoY <= jogadorY - 1) {
        return 1;
    }
    /* Cima */
    if (simbolo == '^' &&
        alvoX >= jogadorX - 2 &&
        alvoX <= jogadorX - 1 &&
        alvoY >= jogadorY - 1 &&
        alvoY <= jogadorY + 1) {
        return 1;
    }
    /* Baixo */
    if (simbolo == 'v' &&
        alvoX >= jogadorX + 1 &&
        alvoX <= jogadorX + 2 &&
        alvoY >= jogadorY - 1 &&
        alvoY <= jogadorY + 1) {
        return 1;
    }
    return 0;
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
        "*F       *",
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
        // Coloca o sÃƒÂ­mbolo do jogador na matriz antes de imprimir
        mapa[x][y] = simbolo;

        printf("              --- VILA DE NEOGENESE ---\n\n");
        printf("Vidas: %d | Arma: %s | Use WASD | O Ataca | M Sair\n\n", vidas, nomeArma);

		 //loops para imprimir toda a matriz do mapa
        for (i = 0; i < 10; i++) {
            for (j = 0; j < 10; j++) {
                
                imprimirCaractereColorido(mapa[i][j]); /* Aplicando o padrao de cores */
            }
            printf("\n");
        }

        mapa[x][y] = caractereOriginal;

        tecla = getch(); //OBS: IA usada aqui pra aprender a como ler a tecla


        if (tecla == 'm' || tecla == 'M') {
            break;
        }

		 /* Guarda a posiÃƒÂ§ÃƒÂ£o pretendida */
    	/*aqui usa as variaveis do movimento, sao atualizadas a cada tecla
				e imprime a nova posicao na matriz */
        proxX = x;
        proxY = y;

		/* == LÃƒâ€œGICA DE MOVIMENTO E DIREÃƒâ€¡ÃƒÆ’O == */
        
        /* OBS: aqui usei um pouco de IA pra aprender essa logica de quando o X ou o Y
        	reduz ou aumenta na matriz */
        	
 	   /* COMO FUNCIONA: 
		 	X -> representa a vertical da matriz
			Y -> representa a horizontal da matriz
			exemplo -> por isso que: "proxX--" move o player pra cima, pois
			ta diminuindo uma unidade da vertical (ou seja, indo sentido a cima da matriz */
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

        if (mapa[proxX][proxY] == 'F') {
            if (jaPegouArma == 1) {
                printf("\n[Ferreiro]: Voce ja escolheu seu equipamento, heroi!\n");
            } else {
                printf("\n[Ferreiro]: Ola heroi! Escolha sua arma:\n");
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
                        alcanceArma = 1;
                        jaPegouArma = 1;
                        printf("\nVoce equipou o Cajado!\n");
                        break;
                    case 3:
                        strcpy(nomeArma, "Arco e Flecha");
                        alcanceArma = 4;
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
                printf("\n[BLOQUEADO]: Voce precisa pegar uma arma com o Ferreiro antes de entrar na masmorra!\n");
                printf("Pressione qualquer tecla para continuar...");
                getch();
                continue;
            }

            iniciarMasmorra1(vidas, nomeArma, alcanceArma, jaPegouArma);
            break;
        }
/* == VERIFICAÃƒâ€¡ÃƒÆ’O DE COLISÃƒÆ’O E LIMPEZA Do RASTRO == */
        if (mapa[proxX][proxY] != '*') {
            x = proxX;
            y = proxY;
        }
    }
}

/* === FUNCAO DA MASMORRA 1 === */
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
                imprimirCaractereColorido(mapa[i][j]); /* Aplicando o padrao de cores */
            }
            printf("\n");
        }

        mapa[x][y] = caractereOriginal;

        tecla = getch();

        if (tecla == 'm' || tecla == 'M') {
            break;
        }

        if (tecla == 'o' || tecla == 'O') {
            int alvoX = -1;
            int alvoY = -1;
            int linha, coluna;

            for (linha = 0; linha < 10; linha++) {
                for (coluna = 0; coluna < 10; coluna++) {
                    if ((mapa[linha][coluna] == 'k' || mapa[linha][coluna] == 'K' ||
                         mapa[linha][coluna] == 'X' || mapa[linha][coluna] == 'Y') &&
                        estaNaAreaAtaque(x, y, simbolo, nomeArma, linha, coluna)) {
                        alvoX = linha;
                        alvoY = coluna;
                        break;
                    }
                }
                if (alvoX != -1) break;
            }

            if (alvoX != -1 && (mapa[alvoX][alvoY] == 'k' || mapa[alvoX][alvoY] == 'K')) {
                mapa[alvoX][alvoY] = ' ';
                printf("\nVoce destruiu uma caixa!\n");
            }
            else if (alvoX != -1 && (mapa[alvoX][alvoY] == 'X' || mapa[alvoX][alvoY] == 'Y')) {
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
                exibirGameOver();
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
                exibirGameOver();
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

/* === MOVE O MONSTRO X DA MASMORRA 2 === */
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

/* === FUNCAO DA MASMORRA 2 === */
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
    

    /* MAPA ORIGINAL RESTAURADO */
    char mapa[15][16] = {
        "***************",
        "* *  *L*    k *",
        "* *  *D*    k *",
        "* *#          *",
        "*   ##    k#  *",
        "*    #        *",
        "* k*********  *",
        "*             *",
        "* * ##  **k****",
        "*       *   * *",
        "*       * O * *",
        "*X*     *   *@*",
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
                imprimirCaractereColorido(mapa[i][j]); /* Aplicando o padrao de cores */
            }
            printf("\n");
        }

        mapa[x][y] = caractereOriginal;

        tecla = getch();

        if (tecla == 'm' || tecla == 'M') {
            break;
        }

        if (tecla == 'o' || tecla == 'O') {
            int alvoX = -1;
            int alvoY = -1;
            int linha, coluna;

            for (linha = 0; linha < 15; linha++) {
                for (coluna = 0; coluna < 15; coluna++) {
                    if ((mapa[linha][coluna] == 'k' || mapa[linha][coluna] == 'K' || mapa[linha][coluna] == 'X') &&
                        estaNaAreaAtaque(x, y, simbolo, nomeArma, linha, coluna)) {
                        alvoX = linha;
                        alvoY = coluna;
                        break;
                    }
                }
                if (alvoX != -1) break;
            }

            if (alvoX != -1 && (mapa[alvoX][alvoY] == 'k' || mapa[alvoX][alvoY] == 'K')) {
                mapa[alvoX][alvoY] = ' ';
                printf("\nVoce destruiu uma caixa!\n");
            }
            else if (alvoX != -1 && mapa[alvoX][alvoY] == 'X') {
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
                exibirGameOver();
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
                exibirGameOver();
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
            iniciarMasmorra3(vidas, nomeArma, alcanceArma, jaPegouArma);
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
                exibirGameOver();
                break;
            }

            printf("Pressione qualquer tecla para continuar...");
            getch();
        }
    }
}


/* === MOVE O MONSTRO Y EM DIRECAO AO JOGADOR === */
void moverMonstroY(char mapa[25][26], int *monstroX, int *monstroY, int jogadorX, int jogadorY) {
    int novoX = *monstroX;
    int novoY = *monstroY;

    if (*monstroX == -1 || *monstroY == -1) {
        return;
    }

    if (jogadorX < *monstroX) novoX--;
    else if (jogadorX > *monstroX) novoX++;
    else if (jogadorY < *monstroY) novoY--;
    else if (jogadorY > *monstroY) novoY++;

    if (novoX == jogadorX && novoY == jogadorY) {
        return;
    }

    if (mapa[novoX][novoY] == ' ') {
        mapa[*monstroX][*monstroY] = ' ';
        *monstroX = novoX;
        *monstroY = novoY;
        mapa[*monstroX][*monstroY] = 'Y';
    }
}

/* === BOSS Z TROCA DE LUGAR COM Y === */
void trocarBossZcomY(char mapa[25][26], int *zX, int *zY, int *yX, int *yY) {
    int tempX, tempY;

    if (*yX == -1 || *yY == -1) {
        return;
    }

    mapa[*zX][*zY] = 'Y';
    mapa[*yX][*yY] = 'Z';

    tempX = *zX;
    tempY = *zY;
    *zX = *yX;
    *zY = *yY;
    *yX = tempX;
    *yY = tempY;
}

/* === VERIFICA SE O JOGADOR ESTA DE COSTAS PARA Z === */
int jogadorEstaDeCostasParaZ(int jogadorX, int jogadorY, int zX, int zY, char simbolo) {
    if (simbolo == '^' && zX > jogadorX && zY == jogadorY) return 1;
    if (simbolo == 'v' && zX < jogadorX && zY == jogadorY) return 1;
    if (simbolo == '<' && zY > jogadorY && zX == jogadorX) return 1;
    if (simbolo == '>' && zY < jogadorY && zX == jogadorX) return 1;
    return 0;
}

/* === Z CRIA UM NOVO Y === */
void criarNovoY(char mapa[25][26], int zX, int zY, int *yX, int *yY) {
    int direcoes[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
    int i, nx, ny;

    for (i = 0; i < 4; i++) {
        nx = zX + direcoes[i][0];
        ny = zY + direcoes[i][1];

        if (mapa[nx][ny] == ' ') {
            mapa[nx][ny] = 'Y';
            *yX = nx;
            *yY = ny;
            return;
        }
    }
}


/* === Z CRIA UM MONSTRO X EM LOCAL ALEATORIO === */
void criarMonstroXAleatorio(char mapa[25][26], int xMonstros[], int yMonstros[], int *qtdX) {
    int tentativa;
    int nx, ny;

    if (*qtdX >= 50) {
        return;
    }

    for (tentativa = 0; tentativa < 200; tentativa++) {
        nx = rand() % 25;
        ny = rand() % 25;

        if (mapa[nx][ny] == ' ') {
            mapa[nx][ny] = 'X';
            xMonstros[*qtdX] = nx;
            yMonstros[*qtdX] = ny;
            (*qtdX)++;
            return;
        }
    }
}

/* === MOVE OS MONSTROS X DA MASMORRA 3 ALEATORIAMENTE === */
void moverMonstrosX3(char mapa[25][26], int xMonstros[], int yMonstros[], int qtdX, int jogadorX, int jogadorY) {
    int i;

    for (i = 0; i < qtdX; i++) {
        int direcao;
        int novoX;
        int novoY;

        if (xMonstros[i] == -1 || yMonstros[i] == -1) {
            continue;
        }

        direcao = rand() % 4;
        novoX = xMonstros[i];
        novoY = yMonstros[i];

        if (direcao == 0) novoX--;
        else if (direcao == 1) novoX++;
        else if (direcao == 2) novoY--;
        else if (direcao == 3) novoY++;

        if (novoX == jogadorX && novoY == jogadorY) {
            continue;
        }

        if (mapa[novoX][novoY] == ' ') {
            mapa[xMonstros[i]][yMonstros[i]] = ' ';
            xMonstros[i] = novoX;
            yMonstros[i] = novoY;
            mapa[xMonstros[i]][yMonstros[i]] = 'X';
        }
    }
}

/* === FUNCAO DA MASMORRA 3 === */
void iniciarMasmorra3(int vidas, char nomeArma[], int alcanceArma, int jaPegouArma) {
    char tecla;
    /* Jogador nasce no corredor central do Boss Z. */
    int x = 1, y = 12;
    int proxX, proxY;
    int i, j;
    char simbolo = '>';
    int temChave = 0;
    int portasEsquerdaAbertas = 0;
    int portaEsquerda1Aberta = 0;
    int portaEsquerda2Aberta = 0;

    int monstroYX = 1;
    int monstroYY = 1;
    /* Z nasce longe do personagem, mas no mesmo corredor central. */
    int bossZX = 23;
    int bossZY = 12;
    int xMonstros[50];
    int yMonstros[50];
    int qtdX = 0;

    
    char mapa[25][26] = {
        "*************************",
        "*Y   *           *      *",
        "*    *           *      *",
        "* @  *           *      *",
        "*    *           *      *",
        "*    D           *      *",
        "*    *           *      *",
        "*    *           *      *",
        "*    * ***** *** *      *",
        "*    *           *      *",
        "*    *           *      *",
        "*    *           *      *",
        "*    *           D      *",
        "*  @ *           *      *",
        "*    *           *      *",
        "*    *           *      *",
        "*    * ***** *** *      *",
        "*    *           *      *",
        "*    D           *      *",
        "*    *           *      *",
        "*    *    @      *      *",
        "*    *           *      *",
        "*    *           *  O   *",
        "*    *           *      *",
        "*************************"
    };

    mapa[bossZX][bossZY] = 'Z';

    while (1) {
        system("cls");

        char caractereOriginal = mapa[x][y];
        mapa[x][y] = simbolo;

        printf("              --- MASMORRA 3 ---\n\n");
        printf("Vidas: %d | Arma: %s | Chave: %s | Use WASD | O Ataca | M Sair\n\n",
               vidas, nomeArma, temChave ? "Sim" : "Nao");

        for (i = 0; i < 25; i++) {
            for (j = 0; j < 25; j++) {
                imprimirCaractereColorido(mapa[i][j]);
            }
            printf("\n");
        }

        mapa[x][y] = caractereOriginal;

        tecla = getch();

        if (tecla == 'm' || tecla == 'M') {
            break;
        }

        if (tecla == 'o' || tecla == 'O') {
            int alvoX = -1;
            int alvoY = -1;
            int linha, coluna;

            for (linha = 0; linha < 25; linha++) {
                for (coluna = 0; coluna < 25; coluna++) {
                    if ((mapa[linha][coluna] == 'X' || mapa[linha][coluna] == 'Y' || mapa[linha][coluna] == 'Z') &&
                        estaNaAreaAtaque(x, y, simbolo, nomeArma, linha, coluna)) {
                        alvoX = linha;
                        alvoY = coluna;
                        break;
                    }
                }
                if (alvoX != -1) break;
            }

            if (alvoX != -1 && mapa[alvoX][alvoY] == 'Y') {
                mapa[alvoX][alvoY] = ' ';
                monstroYX = -1;
                monstroYY = -1;
                printf("\nVoce destruiu o monstro Y!\n");
                printf("Z invocou um novo Y!\n");
                criarNovoY(mapa, bossZX, bossZY, &monstroYX, &monstroYY);
            }
            else if (alvoX != -1 && mapa[alvoX][alvoY] == 'X') {
                int k;
                mapa[alvoX][alvoY] = ' ';

                for (k = 0; k < qtdX; k++) {
                    if (xMonstros[k] == alvoX && yMonstros[k] == alvoY) {
                        xMonstros[k] = -1;
                        yMonstros[k] = -1;
                    }
                }

                printf("\nVoce destruiu o monstro X!\n");
            }
            else if (alvoX != -1 && mapa[alvoX][alvoY] == 'Z') {
                printf("\nVoce atacou o Boss Z, mas ele resistiu!\n");
            }
            else {
                printf("\nVoce atacou, mas nao acertou nada.\n");
            }

            printf("Pressione qualquer tecla para continuar...");
            getch();
        }
        else {
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

            if (mapa[proxX][proxY] == '@') {
                temChave = 1;
                mapa[proxX][proxY] = ' ';
                printf("\nVoce pegou uma chave!\n");
                printf("Pressione qualquer tecla para continuar...");
                getch();
            }

            if (mapa[proxX][proxY] == 'D') {
                /* Porta da direita do corredor central: so abre depois das duas portas da esquerda. */
                if (proxX == 12 && proxY == 17 && portasEsquerdaAbertas < 2) {
                    printf("\nEsta porta so pode ser aberta depois que as duas portas da esquerda forem abertas.\n");
                    printf("Pressione qualquer tecla para continuar...");
                    getch();
                    continue;
                }

                if (temChave == 1) {
                    mapa[proxX][proxY] = '=';

                    /* Conta as duas portas da esquerda da Masmorra 3. */
                    if (proxX == 5 && proxY == 5 && portaEsquerda1Aberta == 0) {
                        portaEsquerda1Aberta = 1;
                        portasEsquerdaAbertas++;
                    }
                    else if (proxX == 18 && proxY == 5 && portaEsquerda2Aberta == 0) {
                        portaEsquerda2Aberta = 1;
                        portasEsquerdaAbertas++;
                    }

                    printf("\nVoce abriu a porta com a chave!\n");
                    printf("Pressione qualquer tecla para continuar...");
                    getch();
                } else {
                    printf("\nA porta esta trancada. Encontre uma chave '@'.\n");
                    printf("Pressione qualquer tecla para continuar...");
                    getch();
                    continue;
                }
            }

            if (mapa[proxX][proxY] == 'O') {
                int linha, coluna;

                /* Ao apertar o botao, paredes, portas e inimigos somem da tela. */
                for (linha = 0; linha < 25; linha++) {
                    for (coluna = 0; coluna < 25; coluna++) {
                        if (mapa[linha][coluna] == '*' || mapa[linha][coluna] == 'D' ||
                            mapa[linha][coluna] == '=' || mapa[linha][coluna] == 'X' ||
                            mapa[linha][coluna] == 'Y' || mapa[linha][coluna] == 'Z') {
                            mapa[linha][coluna] = ' ';
                        }
                    }
                }

                system("cls");
                mapa[x][y] = simbolo;

                printf("              --- MASMORRA 3 ---\n\n");
                printf("Vidas: %d | Arma: %s | Chave: %s | Use WASD | O Ataca | M Sair\n\n",
                       vidas, nomeArma, temChave ? "Sim" : "Nao");

                for (linha = 0; linha < 25; linha++) {
                    for (coluna = 0; coluna < 25; coluna++) {
                        imprimirCaractereColorido(mapa[linha][coluna]);
                    }
                    printf("\n");
                }

                printf("\nO botao foi ativado! Todas as paredes, portas e inimigos desapareceram.\n");
                printf("O chao se abriu e voce caiu em um novo corredor.\n");
                printf("Pressione qualquer tecla para continuar...");
                getch();

                iniciarCorredorFinal(vidas, nomeArma, alcanceArma, jaPegouArma);
                break;
            }

            if (mapa[proxX][proxY] == 'Y') {
                vidas--;
                printf("\nO monstro Y te atacou! Voce perdeu uma vida.\n");
                if (vidas <= 0) {
                    exibirGameOver();
                    break;
                }
                printf("Pressione qualquer tecla para continuar...");
                getch();
                continue;
            }

            if (mapa[proxX][proxY] == 'X') {
                vidas--;
                printf("\nO monstro X te atacou! Voce perdeu uma vida.\n");
                if (vidas <= 0) {
                    exibirGameOver();
                    break;
                }
                printf("Pressione qualquer tecla para continuar...");
                getch();
                continue;
            }

            if (mapa[proxX][proxY] == 'Z') {
                vidas--;
                printf("\nO Boss Z te atingiu! Voce perdeu uma vida.\n");
                if (vidas <= 0) {
                    exibirGameOver();
                    break;
                }
                printf("Pressione qualquer tecla para continuar...");
                getch();
                continue;
            }

            x = proxX;
            y = proxY;
        }

        /* Turno dos monstros */
        if (monstroYX != -1) {
            moverMonstroY(mapa, &monstroYX, &monstroYY, x, y);
        }

        if (monstroYX != -1) {
            trocarBossZcomY(mapa, &bossZX, &bossZY, &monstroYX, &monstroYY);
        }

        moverMonstrosX3(mapa, xMonstros, yMonstros, qtdX, x, y);

        if (jogadorEstaDeCostasParaZ(x, y, bossZX, bossZY, simbolo)) {
            criarMonstroXAleatorio(mapa, xMonstros, yMonstros, &qtdX);
            printf("\nVoce ficou de costas para o Boss Z! Um monstro X apareceu em local aleatorio.\n");
            printf("Pressione qualquer tecla para continuar...");
            getch();
        }

        if (monstroYX != -1 && abs(monstroYX - x) + abs(monstroYY - y) == 1) {
            vidas--;
            printf("\nO monstro Y chegou perto e te atacou! Voce perdeu uma vida.\n");

            if (vidas <= 0) {
                exibirGameOver();
                break;
            }
            printf("Pressione qualquer tecla para continuar...");
            getch();
        }

        for (i = 0; i < qtdX; i++) {
            if (xMonstros[i] != -1 && abs(xMonstros[i] - x) + abs(yMonstros[i] - y) == 1) {
                vidas--;
                printf("\nUm monstro X chegou perto e te atacou! Voce perdeu uma vida.\n");

                if (vidas <= 0) {
                    exibirGameOver();
                    break;
                }
                printf("Pressione qualquer tecla para continuar...");
                getch();
                break;
            }
        }

        if (vidas <= 0) {
            exibirGameOver();
            break;
        }

    }
}

/* === FUNCAO DO CORREDOR FINAL 25x26 === */
void iniciarCorredorFinal(int vidas, char nomeArma[], int alcanceArma, int jaPegouArma) {
    char tecla;
    int x = 12, y = 1;
    int proxX, proxY;
    int i, j;
    char simbolo = '>';
    int conversouQ = 0;

    
   char mapa[25][27] = {
        "**************************",
        "**************************",
        "**************************",
        "**************************",
        "**************************",
        "**************************",
        "**************************",
        "**************************",
        "**************************",
        "**************************",
        "**************************",
        "**************************",
        "*                        Q",
        "**************************",
        "**************************",
        "**************************",
        "**************************",
        "**************************",
        "**************************",
        "**************************",
        "**************************",
        "**************************",
        "**************************",
        "**************************",
        "**************************"
    };

    while (1) {
        system("cls");

        char caractereOriginal = mapa[x][y];
        mapa[x][y] = simbolo;

        printf("              --- CORREDOR DESCONHECIDO ---\n\n");
        printf("Vidas: %d | Arma: %s | Use WASD | M Sair\n\n", vidas, nomeArma);

        for (i = 0; i < 25; i++) {
            for (j = 0; j < 26; j++) {
                imprimirCaractereColorido(mapa[i][j]);
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
        else {
            continue;
        }

        if (mapa[proxX][proxY] == '*') {
            continue;
        }

        if (mapa[proxX][proxY] == 'Q') {
            exibirFinalJogo();
            conversouQ = 1;
            break;
        }

        x = proxX;
        y = proxY;

        if (conversouQ == 1) {
            break;
        }
    }
}


/* === TELA FINAL DO JOGO === */
void exibirFinalJogo() {
    int opcao;

    while (1) {
        system("cls");

        printf("\033[96m");
        printf("============================================================\n");
        printf("                    FIM DO CAPITULO 1                      \n");
        printf("============================================================\n");
        printf("\033[0m\n");

        printf("Q = Obrigado por me salvar.\n\n");
        printf("V = Quem e voce? Onde estao os outros?\n");
        printf("O Z morreu?\n\n");
        printf("Q = Z os trancafiou e os levou para uma outra vila proxima,\n");
        printf("sou o unico que restou de la.\n\n");
        printf("V = Irei atras dele e resgatarei todos, custe o que custar....\n\n");

        printf("Com a surpreendente fuga de Z, nosso heroi precisara persegui-lo\n");
        printf("e devera descobrir o que mais pode estar acontecendo e em meio\n");
        printf("a tantas incertezas, a unica coisa certa e que ele nao ira parar\n");
        printf("ate que reencontre seus companheiros, onde estiverem....\n\n");

        printf("FIM, por enquanto...\n\n");

        printf("============================================================\n");
        printf("1 - SAIR\n");
        printf("2 - MENU\n");
        printf("============================================================\n\n");
        printf("Escolha: ");

        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n');
            continue;
        }

        if (opcao == 1) {
            exit(0);
        }
        else if (opcao == 2) {
            return;
        }
        else {
            printf("\nOpcao invalida! Pressione qualquer tecla para tentar novamente...");
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
    printf(" - Encontre o Ferreiro 'F' para conseguir uma arma.\n");
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
    printf("Z : Boss Final.\n");
    printf("Q : NPC do corredor final.\n\n");

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

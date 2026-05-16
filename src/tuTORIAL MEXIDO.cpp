#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h> 
#include <math.h> 

/* === PROTÓTIPO DAS FUNÇÕES === */
void exibirTutorial();
void exibirCreditos();
void iniciarVila(); 

/* === FUNÇÃO PRINCIPAL (MENU) === */
int main() {
    int comando;
    int continuar = 1;

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

/* === FUNÇÃO DA VILA === */
void iniciarVila() {
    char tecla; 
    int x = 1, y = 1; 
    int proxX, proxY; 
    int i, j;
    int vidas = 3;
    char simbolo = '>'; 
    
    /* Variáveis da Arma */
    int opcaoArma;
    int alcanceArma = 0;
    char nomeArma[20]; 
    strcpy(nomeArma, "Nenhuma"); 
    int jaPegouArma = 0; 
    
    /* -- MAPA CORRIGIDO E NO FORMATO SOLICITADO -- */
    char mapa[10][11] = {
        "**********",
        "*        *",
        "*        *",
        "* N      *", 
        "*        *",
        "*        *",
        "*        *",
        "*        *",
        "*       L*", 
        "**********"
    };

    /* LOOP DA VILA */
    while (1) {
        system("cls");
        
        // Salva o caractere original onde o jogador está pisando (evita apagar o 'N' ou 'L')
        char caractereOriginal = mapa[x][y];
        mapa[x][y] = simbolo; 

        printf("              --- VILA DE NEOGENESE ---\n\n");
        printf("Vidas: %d | Arma: %s | Use WASD para mover | 'O' para Atacar | 'M' para Sair\n\n", vidas, nomeArma);

        /* == IMPRESSÃO DO MAPA == */
        for (i = 0; i < 10; i++) {
            for (j = 0; j < 10; j++) {
                printf("%c ", mapa[i][j]);
            }
            printf("\n");
        }

        // Restaura o chão original antes de processar o movimento
        mapa[x][y] = caractereOriginal;

        tecla = getch(); 

        if (tecla == 'm' || tecla == 'M') {
            break;
        }

        /* == LÓGICA DE ATAQUE (TECLA O) == */
        if (tecla == 'o' || tecla == 'O') {
            if (jaPegouArma == 0) {
                printf("\n[AVISO]: Voce nao tem uma arma equipada para atacar!\n");
                printf("Pressione qualquer tecla para continuar...");
                getch();
                continue;
            }

            char mapaAtaque[10][11];
            for(i = 0; i < 10; i++) {
                strcpy(mapaAtaque[i], mapa[i]);
            }

            /* 1. ATAQUE DA ESPADA: Área de 3x2 à frente do jogador */
            if (alcanceArma == 1) { 
                for (i = 0; i < 10; i++) {
                    for (j = 0; j < 10; j++) {
                        int dx = i - x;
                        int dy = j - y;

                        if (simbolo == '^' && dx >= -2 && dx <= -1 && dy >= -1 && dy <= 1) { mapaAtaque[i][j] = 'X'; }
                        else if (simbolo == 'v' && dx >= 1 && dx <= 2 && dy >= -1 && dy <= 1) { mapaAtaque[i][j] = 'X'; }
                        else if (simbolo == '<' && dy >= -2 && dy <= -1 && dx >= -1 && dx <= 1) { mapaAtaque[i][j] = 'X'; }
                        else if (simbolo == '>' && dy >= 1 && dy <= 2 && dx >= -1 && dx <= 1) { mapaAtaque[i][j] = 'X'; }
                    }
                }
            }
            /* 2. ATAQUE DO CAJADO: 8 células adjacentes ao redor */
            else if (alcanceArma == 3) {
                for (i = x - 1; i <= x + 1; i++) {
                    for (j = y - 1; j <= y + 1; j++) {
                        if (i >= 0 && i < 10 && j >= 0 && j < 10 && !(i == x && j == y)) {
                            mapaAtaque[i][j] = 'X';
                        }
                    }
                }
            }
            /* 3. ATAQUE DO ARCO E FLECHA: Linha reta de até 4 células */
            else if (alcanceArma == 5) {
                for (i = 1; i <= 4; i++) {
                    int alvoX = x;
                    int alvoY = y;

                    if (simbolo == '^') alvoX = x - i;
                    else if (simbolo == 'v' && x + i < 10) alvoX = x + i;
                    else if (simbolo == '<') alvoY = y - i;
                    else if (simbolo == '>' && y + i < 10) alvoY = y + i;

                    if (alvoX > 0 && alvoX < 9 && alvoY > 0 && alvoY < 9) {
                        mapaAtaque[alvoX][alvoY] = 'X';
                    } else {
                        break; 
                    }
                }
            }

            system("cls");
            printf("              --- EXECUTANDO ATAQUE --- \n\n");
            printf("Vidas: %d | Arma: %s | COMPUTANDO DANO...\n\n", vidas, nomeArma);
            for (i = 0; i < 10; i++) {
                for (j = 0; j < 10; j++) {
                    if (mapa[i][j] == '*' || mapa[i][j] == 'N' || mapa[i][j] == 'L') {
                        printf("%c ", mapa[i][j]);
                    } else if (mapaAtaque[i][j] == 'X') {
                        printf("X ");
                    } else {
                        printf("%c ", mapa[i][j]);
                    }
                }
                printf("\n");
            }
            printf("\nAtacou! Pressione qualquer tecla para continuar...");
            getch();
            continue; 
        }

        proxX = x;
        proxY = y;

       
        if (tecla == 'w' || tecla == 'W') { proxX--; simbolo = '^'; }
        else if (tecla == 's' || tecla == 'S') { proxX++; simbolo = 'v'; }
        else if (tecla == 'a' || tecla == 'A') { proxY--; simbolo = '<'; }
        else if (tecla == 'd' || tecla == 'D') { proxY++; simbolo = '>'; }

        /* ==  INTERAÇÃO COM NPC == */
        if (mapa[proxX][proxY] == 'N') {
            if (jaPegouArma == 1) {
                printf("\n[NPC]: Voce ja escolheu seu equipamento, heroi! Siga em frente.\n");
                printf("Pressione qualquer tecla para continuar...");
                getch();
            } 
            else {
                printf("\n[NPC]: Ola heroi! Escolha sua arma:\n");
                printf("1 - Espada (Area 3x2 a frente)\n");
                printf("2 - Cajado (8 Celulas Adjacentes)\n");
                printf("3 - Arco e Flecha (Linha reta 4 celulas)\n");
                printf("Escolha (1, 2 ou 3): ");
                
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
                        printf("\nEscolha invalida! Voce continuou sem arma.\n");
                        break;
                }
                printf("Pressione qualquer tecla para continuar...");
                getch();
            }
            proxX = x;
            proxY = y;
        }

        /* == LÓGICA DO PORTAL / SAÍDA 'L' == */
        if (mapa[proxX][proxY] == 'L') {
            system("cls");
            printf("\n-------------------------------------------------\n");
            printf("             TELEPORTANDO PERSONAGEM...             \n");
            printf("------------------------------------------------------\n\n");
            printf(" Voce atravessou o portal de Neogenese! Observe os elementos, prepare-se!\n");
            printf(" Observe as caixas, treine seu ataque, explore!\n");
            printf(" Preparando para carregar a proxima fase...\n\n");
            printf(" [INFO]: O proximo cenario sera adicionado aqui brevemente.\n\n");
            printf("Pressione qualquer tecla para retornar ao menu...");
            getch();
            break; 
        }

       
        if (mapa[proxX][proxY] != '*') {
            x = proxX; 
            y = proxY;
        }
    }
} 

/* === FUNÇÃO TUTORIAL === modifIQUEI O TUTORIAL AQUI*/
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

/* === FUNÇÃO CRÉDITOS === */
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
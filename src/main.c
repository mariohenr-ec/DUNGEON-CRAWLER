#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

/* funções pra cada ação */
void exibirTutorial();
void exibirCreditos();
void iniciarVila(); 

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
                /* pra quando fazer o codigo da vila chamar aqui */
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

/* Codigo em cada Função */

void iniciarVila() {
    system("cls");
    printf("--------------------------------------\n");
    printf("          VILA DE NEOGENESE\n");
    printf("--------------------------------------\n");
    printf("\nVoce entrou na vila. Esta area ainda esta em desenvolvimento.\n");
    printf("\nEm breve: Escolha de armas com o NPC e entrada da masmorra.\n");
    
    printf("\n\nPressione qualquer tecla para voltar ao menu principal...");
    getch();
}

void exibirTutorial() {
    system("cls");
    printf("--------------------------------------\n");
    printf("              TUTORIAL\n");
    printf("--------------------------------------\n");
    printf("\nHISTORIA: No mundo de Neogenese, salve os civis de rituais sombrios!\n");
    printf("\nCONTROLES:\n");
    printf("W - Cima | A - Esquerda | S - Baixo | D - Direita\n");
    printf("I - Interagir | O - Atacar\n");
    printf("\nSIMBOLOS PRINCIPAIS:\n");
    printf("@ : Chave   | D : Porta   | L : Escada\n");
    printf("* : Parede  | # : Espinho | k : Caixa\n");
    printf("\nPressione qualquer tecla para voltar ao menu...");
    getch();
}

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

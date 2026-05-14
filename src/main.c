#include <stdio.h>

int main()
{
    int comando;
    int continuar = 1;
    int voltar;

    while(continuar == 1)
    {
        printf("\n--------------------------------------\n");
        printf("        MENU PRINCIPAL\n");
        printf("--------------------------------------\n");
        printf("1 - Jogar\n");
        printf("2 - Tutorial\n");
        printf("3 - Sair / Creditos\n");

        printf("\nEscolha seu comando -- Numero 1, 2 ou 3: ");
        scanf("%d", &comando);

        switch(comando)
        {
            case 1:
                printf("\nOnde estara o jogo...\n");
                break;

            case 2:
                printf("\n--------------------------------------\n");
                printf("              TUTORIAL\n");
                printf("--------------------------------------\n");

                printf("\nHISTORIA DO JOGO\n\n");
                printf("No mundo de Neogenese, um grupo deseja liberar um demonio antigo.\n");
                printf("Os civis sao usados como fonte de energia para rituais em uma torre.\n");
                printf("Pegue sua arma e salve o mundo dessa ameaca sobre-humana!\n");

                printf("\nCOMO JOGAR\n");
                printf("Explore a vila, escolha sua arma, atravesse 3 andares e derrote o Boss Final Z.\n");

                printf("\nCONTROLES\n");
                printf("W - Move para cima\n");
                printf("A - Move para esquerda\n");
                printf("S - Move para baixo\n");
                printf("D - Move para direita\n");
                printf("I - Interage com objetos\n");
                printf("O - Realiza ataque\n");

                printf("\nGUIA DE SIMBOLOS\n");
                printf("^ < > v : Jogador e direcao\n");
                printf("@       : Chave\n");
                printf("D       : Porta Fechada\n");
                printf("=       : Porta Aberta\n");
                printf("L       : Escada\n");
                printf("O       : Botao\n");
                printf("*       : Parede\n");
                printf("#       : Espinho\n");
                printf("k       : Caixa destrutivel\n");
                printf("X       : Monstro Tipo 1\n");
                printf("Y       : Monstro Tipo 2\n");
                printf("Z       : Boss Final\n");

                printf("\nDigite 0 para voltar ao menu principal: ");
                scanf("%d", &voltar);
                break;

            case 3:
                printf("\n--------------------------------------\n");
                printf("              CREDITOS\n");
                printf("--------------------------------------\n");

                printf("Desenvolvedores:\n");
                printf("- Jose Pedro Martins\n");
                printf("- Mario Henrique\n");
                printf("- Vinicius Carreiro\n");

                printf("\nDigite 0 para voltar ao menu principal ou 1 para sair: ");
                scanf("%d", &voltar);

                if(voltar == 1)
                {
                    continuar = 0;
                    printf("\nSaindo do jogo...\n");
                }
                break;

            default:
                printf("\nComando invalido!\n");
                break;
        }
    }

    return 0;
}

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

// Codigos presentes em cada funcao:

void iniciarVila() {
    /* variaveis locais(essas dai são variaveis pro movimento do player*/
    char tecla; //para ler a tecla sendo usada (w a s d, etc)
    int x = 1, y = 1; // Posição inicial do jogador no mapa
    int proxX, proxY; //var para a logica de movimentação do jogador
    int i, j;
    int vidas = 3;
    char simbolo = '>'; // para onde o jogador começa olhando
    
    /* -- MAPA -- */
    char mapa[10][10] = {
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
        
        // Coloca o símbolo do jogador na matriz antes de imprimir
        mapa[x][y] = simbolo; //OBS: aqui usei IA para entender a lógica de mostrar o simbolo na matriz

        printf("              --- VILA DE NEOGENESE ---\n\n");
        printf("Vidas: %d | Use WASD para mover | 'M' para Sair\n\n", vidas);

       	 	 /* == IMPRESSÃO DO MAPA == */
        //loops para imprimir toda a matriz do mapa
        for (i = 0; i < 10; i++) {
            for (j = 0; j < 10; j++) {
                printf("%c ", mapa[i][j]);
            }
            printf("\n");
        }

        		/* == LEITURA DA TECLA == */
        tecla = getch(); //OBS: IA usada aqui pra aprender a como ler a tecla

        /* Sai da vila e volta para o menu */
        if (tecla == 'm' || tecla == 'M') break;

        /* Guarda a posição pretendida */
    		/*aqui usa as variaveis do movimento, sao atualizadas a cada tecla
				e imprime a nova posicao na matriz */
        proxX = x;
        proxY = y;

        		/* == LÓGICA DE MOVIMENTO E DIREÇÃO == */
        
        /* OBS: aqui usei um pouco de IA pra aprender essa logica de quando o X ou o Y
        	reduz ou aumenta na matriz */
        	
 	   /* COMO FUNCIONA: 
		 	X -> representa a vertical da matriz
			Y -> representa a horizontal da matriz
			exemplo -> por isso que: "proxX--" move o player pra cima, pois
			ta diminuindo uma unidade da vertical (ou seja, indo sentido a cima da matriz */
        if (tecla == 'w' || tecla == 'W') { proxX--; simbolo = '^'; }
        else if (tecla == 's' || tecla == 'S') { proxX++; simbolo = 'v'; }
        else if (tecla == 'a' || tecla == 'A') { proxY--; simbolo = '<'; }
        else if (tecla == 'd' || tecla == 'D') { proxY++; simbolo = '>'; }

        		/* == VERIFICAÇÃO DE COLISÃO E LIMPEZA Do RASTRO == */
        if (mapa[proxX][proxY] != '*') {
            
            mapa[x][y] = ' ';  //para deixar vazio a posicao depois de andar
            /* exatamente aqui nesse X e Y abaixo que a nova posição é 
			atualizada no mapa: */
            x = proxX; 
            y = proxY;
        }
        
        		/* ==  INTERAÇÃO COM NPC == */
        if (mapa[x][y] == 'N') {
            printf("\nNPC: Ola heroi! Escolha sua arma no proximo update...");
            getch();
            x++; /* OBS IA: esse x++ aqui eu aprendi com a IA pra evitar o bug
					de o player apagar o NPC do mapa depois de conversar com ele,
					ja que ele fica na mesma posição da matriz que o NPC durante a fala */
        }
        
        	/* == INTERAÇÃO COM A ESCADA == */
  	//OBS: aqui onde vai ficar o codigo pra passar pro primeiro andar quando acessar a escada na vila
    }
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

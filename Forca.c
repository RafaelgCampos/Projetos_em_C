#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define TDL 7

int main (void){

char	resposta[TDL][20] = {	/* Palavra secreta */
		"amendoim",
		"carro",
		"rato",
		"champagne",
		"ventilador",
		"tomada",
		"corrida"},
	chute,		/* Chutes feitos pelo usuário */
	chutes[26];	/* Lista de chutes feitos pelo usuário */
	
bool	venceu = false,
	enforcou = false,
	achou = false;
	
int	i,	/* Variável para análise */
	j,	/* Variável para análise */
	vidas = 4,
	acertou = 0,
	tentativas = 0,
	erros = 0,
	tamanho,
	seed;
	
srand(time(NULL));
seed = rand() % TDL;

tamanho = strlen(resposta[seed]);	/* Tamanho da palavra secreta */

printf ("Esse programa simula um jogo de forca.\n");
printf ("Insira letras para tentar formar a palavra secreta.\n");

do {
	printf("\n\nInsira uma letra:\n");
	scanf(" %c", &chute);
	printf ("\n");
	chutes[tentativas] = chute;
	tentativas++;

	for(i = 0; i < tamanho; i++){
		if(resposta[seed][i] == chute) {
			for (j = 0; j < tentativas - 1; j++){
				if (chutes[j] == chute)
					achou = true;
			}
			if (achou == false)
				acertou++;
			if(acertou == tamanho)
				venceu = true;
        	}
        	else
        		erros++;
        		
        	achou = false;
        }
	if (erros == tamanho){
		printf ("\n\nA letra inserida nao esta contida na palavra.\n");
		vidas--;
		if (vidas == 0)
			enforcou = true;
	}
	printf (" _______\n");
	printf (" |/    |\n");
	printf (" |");
	if (vidas <= 3)
		printf ("     O");
	printf ("\n");
	printf (" |");
	if (vidas <= 2)
		printf ("    \\|/");
	printf ("\n");
	printf (" |");
	if (vidas <= 1)
		printf ("     |");
	printf ("\n");
	printf (" |");
	if (vidas == 0)
		printf ("    / \\");
	printf ("\n");
	printf (" |  \n");
	printf ("_|___\n"); 
        for (i = 0; i < tamanho; i++){
        	for(j = 0; j < tentativas; j++){
			if (chutes[j] == resposta[seed][i]){
				achou = true;
				break;
			}
		}
		if (achou)
			printf ("%c ", resposta[seed][i]);		
		else
			printf ("_ ");		
		achou = false;
        }
	erros = 0;
	printf ("\n\nvidas = %d.\n", vidas);     
}while (!venceu && !enforcou); 

if (venceu)
	printf ("\n\nParabens, voce venceu!\n");
else
	printf ("\n\nQue pena, voce perdeu.\n");

return 0;
}

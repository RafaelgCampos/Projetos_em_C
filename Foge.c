#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define Linhas 8
#define Colunas 16 + 1	/* 12 colunas para escrita + Enter */
#define QntFan 4	/* Quantidade de Fantasmas */

char	mapa[Linhas][Colunas],	/* Definicao do mapa do jogo */
	objetivo = '$',
	personagem = '@',
	fantasma[QntFan];
	
int	posX = 5,	/* Coordenadas iniciais do jogador no eixo x */
	posY = 4,	/* Coordenadas iniciais do jogador no eixo y */
	objX,	/* Coordenadas iniciais do objetivo no eixo x */
	objY,	/* Coordenadas iniciais do objetivo no eixo y */
	fanX[QntFan],	/* Coordenada X do fantasma */
	fanY[QntFan],	/* Coordenada Y do fantasma */
	chegou = 0,	/* Valor para verificar condicao, 1 = venceu */
	obstaculo = 0;	/* Validar o contato entre o fantasma e a barreira */

void movimento(int* Y, int* X, char direcao);

void mundo();

void gerador();

void IAfantasma(int i);

int main (void){

char	move;	/* Variavel necessaria para definir a direcao de movimento do usuario */
	
int	i,	/* Variavel para calculo */
	venceu;
	
FILE* f;
f = fopen("Mapa.txt", "r");
memset (&fantasma, 'F', sizeof(fantasma));

for (i = 0; i < Linhas; i++)
	fscanf (f, "%s", mapa[i]);

gerador();

if (f == 0){
	printf ("Erro na leitura do Mapa.\n");
	exit(1);
}
printf ("O usuario esta representado pelo simbolo @.\n");
printf ("Insira para onde o jogador ira se movimentar com w, a, s, d.\n");
printf ("Seu objetivo: Eliminar todos os fantasmas (representados por 'F').\n");
printf ("A bomba ('$') vai te ajudar a eliminar os fantasmas\n");

while (chegou == 0){
	mundo();
	scanf (" %c", &move);
	movimento(&posY, &posX, move);
	if (chegou == 1){
		for (i = 0; i < QntFan; i++){
			if (fanY[i] == objY || fanX[i] == objX)
				fantasma[i] = '.';
			if (fantasma[i] == '.'){
				venceu++;
				if (venceu == QntFan){
					printf ("Parabens, voce alcancou seu objetivo.\n");
					return 2;
				}
			}
		}
		venceu = 0;
		mapa[objY][objX] = '.';
		do{
			objX = rand() % (Colunas - 1);
			objY = rand() % Linhas;
		}while(mapa[objY][objX] != '.');
	}
	for (i = 0; i < QntFan; i++)
		IAfantasma(i);
}
	
return 0;
}

void movimento(int* Y, int* X, char direcao){

int	i;

switch (direcao){
	case 'd':
		*X += 1;
		for (i = 0; i < QntFan; i++){
			if (fanY[i] == posY && fanX[i] == posX && fantasma[i] == 'F'){
				printf ("Que pena, voce perdeu!\n");
				exit(4);
		}
		}
		if (*Y == objY && *X == objX){
			*X -= 1;
			chegou = 1;
			break;
		}
		if (mapa[*Y][*X] != '.' && mapa[*Y][*X] != objetivo){
			obstaculo = 1;
			*X -= 1;
		}
		else {
			mapa[*Y][*X - 1] = '.';
			obstaculo = 0;
		}
		break;
	case 'a':
		*X -= 1;
		for (i = 0; i < QntFan; i++){
			if (fanY[i] == posY && fanX[i] == posX && fantasma[i] == 'F'){
				printf ("Que pena, voce perdeu!\n");
				exit(4);
		}
		}
		if (*Y == objY && *X == objX){
			*X += 1;
			chegou = 1;
			break;
		}
		if (mapa[*Y][*X] != '.' && mapa[*Y][*X] != objetivo){
			obstaculo = 1;
			*X += 1;
		}
		else {
			mapa[*Y][*X + 1] = '.';
			obstaculo = 0;
		}
		break;
	case 'w':
		*Y -= 1;
		for (i = 0; i < QntFan; i++){
			if (fanY[i] == posY && fanX[i] == posX && fantasma[i] == 'F'){
				printf ("Que pena, voce perdeu!\n");
				exit(4);
		}
		}
		if (*Y == objY && *X == objX){
			*Y += 1;
			chegou = 1;
			break;
		}
		if (mapa[*Y][*X] != '.' && mapa[*Y][*X] != objetivo){
			obstaculo = 1;
			*Y += 1;
		}
		else {
			mapa[*Y + 1][*X] = '.';
			obstaculo = 0;
		}
		break;
	case 's':
		*Y += 1;
		for (i = 0; i < QntFan; i++){
			if (fanY[i] == posY && fanX[i] == posX && fantasma[i] == 'F'){
				printf ("Que pena, voce perdeu!\n");
				exit(4);
		}
		}
		if (*Y == objY && *X == objX){
			*Y -= 1;
			chegou = 1;
			break;
		}
		if (mapa[*Y][*X] != '.' && mapa[*Y][*X] != objetivo){
			obstaculo = 1;
			*Y -= 1;
		}
		else {
			mapa[*Y - 1][*X] = '.';
			obstaculo = 0;
		}
		break;
	default:
		break;
}
}

void mundo (){

int	i = 0;

mapa[posY][posX] = personagem;
mapa[objY][objX] = objetivo;
for (i = 0; i < QntFan; i++){
	if (fantasma[i] == 'F')
		mapa[fanY[i]][fanX[i]] = fantasma[i]; 
}
for (i = 0; i < Linhas; i++)
	printf ("%s\n", mapa[i]);

}

void gerador(){

int	i = 0,
	j = 0,
	repete = 0;
	
srand(time(NULL));	

do{
	objX = rand() % (Colunas - 1);
	objY = rand() % Linhas;
}while((objY == posY && objX == posX) || mapa[objY][objX] == '|');
for (i = 0; i < QntFan; i++){
	do{
		repete = 0;
		fanX[i] = rand() % (Colunas - 1);
		fanY[i] = rand() % Linhas;
		for (j = 0; j < i; j++){
			if (fanX[i] == fanX[j] && fanY[i] == fanY[j])
				repete = 1;
		}
	}while((fanX[i] == objX && fanY[i] == objY) || (fanX[i] == posX && fanY[i] == posY) || mapa[fanY[i]][fanX[i]] != '.' || repete == 1);
}
}

void IAfantasma(int i){

char	andar;
int	random,
	igualX = 0,
	igualY = 0,
	andou = 0;
srand(time(NULL));
random = rand() % 2;
andou = 0;
do{
if (igualX == 1 && igualY == 0)
	random = 1;
if (igualX == 0 && igualY == 1)
	random = 0;
if (igualX == 1 && igualY == 1)
	random = 2;
switch (random){
	case 0:
		if (posY < fanY[i]){
			andar = 'w';
			andou = 1;
		}
		else if (posY > fanY[i]){
			andar = 's';
			andou = 1;
		}
		else if (posY == fanY[i])
			igualX = 1;
		break;
	case 1:
		if (posX < fanX[i]){
			andar = 'a';
			andou = 1;
		}
		else if (posX > fanX[i]){
			andar = 'd';
			andou = 1;
		}
		else if (posX == fanX[i])
			igualY = 1;
		break;
	default:
		andou = 1;
		obstaculo = 0;
		break;
}
}while (andou == 0);
do{
movimento(&fanY[i], &fanX[i], andar); 
if (obstaculo == 1 && fanY[i] != posY && fanX[i] != posX){
	if (andar == 'a' || andar == 'd'){
		if (posY < fanY[i]){
			if (mapa[fanY[i] - 1][fanX[i]] == '.')
				andar = 'w';
			else if (mapa[fanY[i] + 1][fanX[i]] == '.')
				andar = 's';
			else if (andar == 'a' && mapa[fanY[i]][fanX[i] + 1] == '.')
				andar = 'd';
			else if (andar == 'd' && mapa[fanY[i]][fanX[i] - 1] == '.')
				andar = 'a';
			else 
				obstaculo = 0;
		}
		if (posY > fanY[i]){
			if (mapa[fanY[i] + 1][fanX[i]] == '.')
				andar = 's';
			else if (mapa[fanY[i] - 1][fanX[i]] == '.')
				andar = 'w';
			else if (andar == 'a' && mapa[fanY[i]][fanX[i] + 1] ==  '.')
				andar = 'd';
			else if (andar == 'd' && mapa[fanY[i]][fanX[i] - 1] == '.')
				andar = 'a';
			else
				obstaculo = 0;
		}
	}	
	else if (andar == 'w' || andar == 's'){
		if (posX < fanX[i]){
			if (mapa[fanY[i]][fanX[i] - 1] == '.')
				andar = 'a';
			else if (mapa[fanY[i]][fanX[i] + 1] == '.')
				andar = 'd';
			else if (andar == 'w' && mapa[fanY[i] + 1][fanX[i]] == '.')
				andar = 's';
			else if (andar == 's' && mapa[fanY[i] - 1][fanX[i]] == '.')
				andar = 'w';
			else
				obstaculo = 0;
		}
		else if (posX > fanX[i]){
			if (mapa[fanY[i]][fanX[i] + 1] == '.')
				andar = 'd';
			else if (mapa[fanY[i]][fanX[i] - 1] == '.')
				andar = 'a';
			else if (andar == 'w' && mapa[fanY[i] + 1][fanX[i]] == '.')
				andar = 's';
			else if (andar == 's' && mapa[fanY[i] - 1][fanX[i]] == '.')
				andar = 'w';
			else
				obstaculo = 0;
		}
	}
}
if (obstaculo == 1 && fanY[i] == posY){
	if (mapa[fanY[i] - 1][fanX[i]] == '.')
		andar = 'w';
	else if (mapa[fanY[i] + 1][fanX[i]] == '.')
		andar = 's';
	else
		obstaculo = 0;
}
else if (obstaculo == 1 && fanX[i] == posX){
	if (mapa[fanY[i]][fanX[i] - 1] == '.')
		andar = 'a';
	else if (mapa[fanY[i]][fanX[i] + 1] == '.')
		andar = 'd';
	else
		obstaculo = 0;
}
}while (obstaculo == 1);
chegou = 0;
mapa[fanY[i]][fanX[i]] = fantasma[i];
}
		


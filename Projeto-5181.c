/*--------------- File: Projeto-5181.cpp  -------------------+
| Desenvolvimento do Projeto 							|
|					      								|
|					      								|
| Implementado por Luigi Miranda em 08/07/2018			|
+-------------------------------------------------------+ */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Estrutura Musica
typedef struct sMusica{
	char nomeM[100];
	int duracao;
	char compositor[100];
	char album[100];
}Musica;

//Celula de Musica
typedef struct sCellM{
	Musica info;
	struct sCellM *prox;
	struct sCellM *ant;	
}CelulaM;

//Estrutura de Artista
typedef struct sArtista{
	CelulaM *Musi;
	char nomeA[100];
	char genero[100];
	int qntAlbuns;
}Artista;

//Celula de Artista
typedef struct sCellA{
	Artista infoA;
	struct sCellA *prox;
	struct sCellA *ant;	
}CelulaA;

/*--------------------------------------M U S I C A----------------------------------------*/

//Inicialização de Musica
void inicializaListaMu(CelulaM **lista){
	(*lista) = NULL;
}


//Verificação se a Lista de Musica esta vazia
int listaVaziaMu(CelulaM **lista){
	if((*lista) == NULL){
		return 1;
	}
	return 0;
}

//Criando uma Celula de Musica
CelulaM* criarCelulaMu(){
	CelulaM *nova = (CelulaM*)malloc(sizeof(CelulaM));
	return nova;
}

//Insere uma Musica em Ordem Alfabetica
int inserirOrdenado(CelulaM **lista, Musica elemento){
	CelulaM *m = criarCelulaMu();
	if(m == NULL){
		printf("ERRO DE ALOCACAO! SEM ESPACO DE MEMORIA!\n");
		return 0;
	}
	m->info = elemento;
	m->prox = NULL;
	m->ant = NULL;
	//Se a lista estiveer vazia insere como primeiro elemento
	if(listaVaziaMu(lista)){
		m->prox = m;
		m->ant = m;
		(*lista) = m;
		return 1;
	}
	CelulaM *aux = (*lista);
	do{
		//Se a Musica inserida for menor que a musica onde o aux esta, é o luhar ideal para inserir a nova musica
		if(strcmp(elemento.nomeM, aux->info.nomeM) < 0){
			m->prox = aux;
			m->ant = aux->ant;
			(aux->ant)->prox = m;
			aux->ant = m;
			//Se o aux estiver no primeiro elemento da lista, entao o iniciona da lista tem q ser a nova celula
			if(aux == (*lista)){
				(*lista) = m;
			}
			return 1;
		}
		aux = aux->prox;
	}while(aux != (*lista));
	m->prox = (*lista);
	m->ant = (*lista)->ant;
	((*lista)->ant)->prox = m;
	(*lista)->ant = m;
	return 1;		
}

//Remove a Musica Pesquisada
void removerPesquisada(CelulaM **lista){
	CelulaM *removida;
	removida = (*lista);
	int n;
	printf("Deseja Realmente remover a Musica %s? (1 = Sim/0 = Nao)\n", removida->info.nomeM);
	do{
		scanf("%d", &n);
		if((n < 0)||(n > 1)){
			printf("VALOR INVALIDO! DIGITE UMA OPÇÃO VALIDA!\n");
		}
	}while((n != 0)&&(n != 1));
	if(n == 1){
		removida->prox = NULL;
		removida->ant = NULL;
		free(removida);
		return ;
	}else{
		printf("OPERACAO DE REMOCAO DESFEITA!\n");
		(removida->prox)->ant = removida;
		(removida->ant)->prox = removida;
	}
}

//Imprime a Musica Pesquisada
void imprimePesquisada(Musica *m){
	printf("\n-------------Informacoes da Musica-------------- \n");
	printf("Nome da Musica: %s Duracao: %d:00\n", m->nomeM, m->duracao);
	printf("Album: %s Compositor: %s\n\n", m->album, m->compositor);
}

//Imprime as Musica em Ordem
void imprimeOrdenado(CelulaM **lista){
	int i = 1;
	if(listaVaziaMu(lista)){
		printf("ERRO AO IMPRIMIR! NAO HA MUSICAS!\n");
		return ;
	}
	CelulaM *aux = (*lista);
	system("cls");
	do{
		printf("--------------TOCANDO AGORA -----------\n");
		printf("\nMusica %d:", i);
		printf("\nMusica: %s", aux->info.nomeM);
		printf(" Duracao: %d:00", aux->info.duracao);
		printf("\nAlbum: %s", aux->info.album);
		printf(" Compositor: %s\n", aux->info.compositor);
		printf("\nProxima Musica a Tocar: %s\n", aux->prox->info.nomeM);
		sleep(5);
		aux = aux->prox;
		system("cls");
		printf("\nUltima Musica Tocada: %s\n", aux->ant->info.nomeM);
		i++;
	}while(aux != (*lista));
}

//Pesquisa uma Musica
void pesquisarMusicas(CelulaM **lista, char* elemento){
	Musica Mpesquisado;
	int n;
	if(listaVaziaMu(lista)){
		printf("ERRO AO PESQUISAR! NAO HA MUSICAS!\n");
		return ;
	}
	CelulaM *aux = (*lista);
	do{
		if(strcmp(aux->info.nomeM, elemento) == 0){
			Mpesquisado = aux->info;
			imprimePesquisada(&Mpesquisado);
			printf("Deseja Remover a Musica Pesquisada? (1 = Sim/0 = Nao)\n");
			do{
				scanf("%d", &n);
				if((n < 0)||(n > 1)){
					printf("VALOR INVALIDO! DIGITE UMA OPCAO VALIDA!\n");
				}
			}while((n != 0)&&(n != 1));
			if(n == 1){
				(aux->prox)->ant = aux->ant;
				(aux->ant)->prox = aux->prox;
			 	removerPesquisada(&aux);
			}else{
				n = -1;
				printf("Deseja Ouvir apartir da Musica Pesquisada? (1 = Sim/0 = Nao)\n");
				do{
					scanf("%d", &n);
					if((n < 0)||(n > 1)){
						printf("VALOR INVALIDO! DIGITE UMA OPCAO VALIDA!\n");
					}
				}while((n != 0)&&(n != 1));
				if(n == 1){
					imprimeOrdenado(&aux);
				}
				return ;
			}
			return ;
		}
		aux = aux->prox;
	}while(aux != (*lista));
	printf("NAO EXISTE ESSA MUSICA NESSE ARTISTA!\n");
	return ;
}

//Remove Todas as Musicas
void removerTodasAsMusicas(CelulaM **lista){
	CelulaM *aux;
	if(listaVaziaMu(lista)){
		printf("ERRO NA REMOCAO! NAO HA MUSICAS!\n");
		return ;
	}
	aux = (*lista)->ant;
	do{
		//ISOLO A CELULA
		(aux->prox)->ant = aux->ant;
		(aux->ant)->prox = aux->prox;
		aux->ant = NULL;
		aux->prox = NULL;
		//REMOVO ELA
		free(aux);
		//ANDO
		aux = (*lista)->ant;
	}while(aux != NULL);
	(*lista) = NULL;
}

//Imprime Todas as Musicas
void imprimeAllMusicas(CelulaM **lista){
	int i = 1;
	if(listaVaziaMu(lista)){
		printf("ERRO AO IMPRIMIR! NAO HA MUSICAS!\n");
		return ;
	}
	CelulaM *aux = (*lista);
	do{
		printf("\nMusica %d:", i);
		printf("\nMusica: %s", aux->info.nomeM);
		printf(" Duracao: %d:00", aux->info.duracao);
		printf("\nAlbum: %s", aux->info.album);
		printf(" Compositor: %s\n", aux->info.compositor);
		aux = aux->prox;
		i++;
	}while(aux != (*lista));
}


/*---------------------------------- A R T I S T A S ----------------------------*/

//Inicialização de Artista
void inicializaListaArt(CelulaA **lista){
	(*lista) = NULL;
}

//Verificação se a Lista de Artista esta vazia
int listaVaziaArt(CelulaA **lista){
	if((*lista) == NULL){
		return 1;
	}
	return 0;
}

//Criando uma Celula de Artista
CelulaA* criarCelulaArt(){
	CelulaA *nova = (CelulaA*)malloc(sizeof(CelulaA));
	return nova;
}

//Insere um Artista em Ordem
int inserirOrdenadoArt(CelulaA **lista, Artista elemento){
	Musica entrada;
	int n;
	CelulaA *a = criarCelulaArt();
	if(a == NULL){
		printf("ERRO DE ALOCACAO! SEM ESPACO NA MEMORIA!");
		return 0;
	}
	a->infoA = elemento;
	if(listaVaziaArt(lista)){
		a->ant = a;
		a->prox = a;
		(*lista) = a;
		//Inicializa a musica
		inicializaListaMu(&a->infoA.Musi);
		printf("Deseja Inserir alguma Musica nesse artista? (1 = SIM/0 = NAO)\n");
		do{
			scanf("%d", &n);
			if((n < 0)||(n > 1)){
				printf("VALOR INVALIDO! DIGITE UMA OPCAO VALIDA!\n");
			}
		}while((n != 0)&&(n != 1));
		//Caso o 1 foi digitado sera cadastrado as musicas
		if(n == 1){
			do{
				printf("Nome da Musica: ");
				fflush(stdin);
				gets(entrada.nomeM);
				fflush(stdin);
				printf("Duracao: ");
				scanf("%d", &entrada.duracao);
				printf("Album: ");
				fflush(stdin);
				gets(entrada.album);
				fflush(stdin);
				printf("Compositor: ");
				fflush(stdin);
				gets(entrada.compositor);
				fflush(stdin);
				printf("\n");
				inserirOrdenado(&a->infoA.Musi, entrada);
				printf("Deseja inserir mais alguma Musica? (1 = SIM/0 = NAO)\n");
				do{
					scanf("%d", &n);
					if((n < 0)||(n > 1)){
						printf("VALOR INVALIDO! DIGITE UMA OPCAO VALIDA!\n");
					}
				}while((n != 0)&&(n != 1));
			}while(n != 0);
			system("cls");
		}
		return 1;
	}
	CelulaA *aux = (*lista);
	do{
		if(strcmp(elemento.nomeA, aux->infoA.nomeA) < 0){
			a->prox = aux;
			a->ant = aux->ant;
			(aux->ant)->prox = a;
			aux->ant = a;
			//Inicializa a musica
			inicializaListaMu(&a->infoA.Musi);
			if(aux == (*lista)){
				(*lista) = a;
			}
			printf("Deseja Inserir alguma Musica nesse artista? (1 = SIM/0 = NAO)\n");
			do{
				scanf("%d", &n);
				if((n < 0)||(n > 1)){
					printf("VALOR INVALIDO! DIGITE UMA OPCAO VALIDA!\n");
				}
			}while((n != 0)&&(n != 1));
			if(n == 1){
				do{
					printf("Nome da Musica: ");
					fflush(stdin);
					gets(entrada.nomeM);
					fflush(stdin);
					printf("Duracao: ");
					scanf("%d", &entrada.duracao);
					printf("Album: ");
					fflush(stdin);
					gets(entrada.album);
					fflush(stdin);
					printf("Compositor: ");
					fflush(stdin);
					gets(entrada.compositor);
					fflush(stdin);
					printf("\n");
					inserirOrdenado(&a->infoA.Musi, entrada);
					printf("Deseja inserir mais alguma Musica? (1 = SIM/0 = NAO)\n");
					do{
						scanf("%d", &n);
						if((n < 0)||(n > 1)){
							printf("VALOR INVALIDO! DIGITE UMA OPCAO VALIDA!\n");
						}
					}while((n != 0)&&(n != 1));
				}while(n != 0);
				system("cls");
			}
			return 1;
		}
		aux = aux->prox;
	}while(aux != (*lista));
	a->prox = (*lista);
	a->ant = (*lista)->ant;
	((*lista)->ant)->prox = a;
	(*lista)->ant = a;
	//Inicializa a musica
	inicializaListaMu(&a->infoA.Musi);
	printf("Deseja Inserir alguma Musica nesse artista? (1 = SIM/0 = NAO)\n");
	do{
		scanf("%d", &n);
		if((n < 0)||(n > 1)){
			printf("VALOR INVALIDO! DIGITE UMA OPCAO VALIDA!\n");
		}
	}while(n != 0);
	if(n == 1){
		do{
			printf("Nome da Musica: ");
			fflush(stdin);
			gets(entrada.nomeM);
			fflush(stdin);
			printf("Duracao: ");
			scanf("%d", &entrada.duracao);
			printf("Album: ");
			fflush(stdin);
			gets(entrada.album);
			fflush(stdin);
			printf("Compositor: ");
			fflush(stdin);
			gets(entrada.compositor);
			fflush(stdin);
			printf("\n");
			inserirOrdenado(&a->infoA.Musi, entrada);
			printf("Deseja inserir mais alguma Musica? (1 = SIM/0 = NAO)\n");
			do{
				scanf("%d", &n);
				if((n < 0)||(n > 1)){
					printf("VALOR INVALIDO! DIGITE UMA OPCAO VALIDA!\n");
				}
			}while((n != 0)&&(n != 1));
		}while(n != 0);
		system("cls");
	}
	return 1;
}

//Remove o Artista Pesquisado
void removerPesquisadaArt(CelulaA **lista){
	CelulaA *removida;
	removida = (*lista);
	int n;
	printf("Deseja Realmente remover o Artista %s? (1 = Sim/0 = Nao)\n", removida->infoA.nomeA);
	do{
		scanf("%d", &n);
		if((n < 0)||(n > 1)){
			printf("VALOR INVALIDO! DIGITE UMA OPÇÃO VALIDA!\n");
		}
	}while((n != 0)&&(n != 1));
	if(n == 1){
		removerTodasAsMusicas(&removida->infoA.Musi);
		removida->prox = NULL;
		removida->ant = NULL;
		(*lista) = NULL;
		free(removida);
		return ;
	}else{
		printf("OPERACAO DE REMOCAO DESFEITA!\n");
		(removida->prox)->ant = removida;
		(removida->ant)->prox = removida;
	}
}

//Imprime o Artista Pesquisado
void imprimirPesquisadaArt(Artista *a){
	printf("---------------Informacoes do Artista----------\n");
	printf("Nome: %s", a->nomeA);
	printf("\nGenero: %s", a->genero);
	printf("\nAlbuns: %d\n", a->qntAlbuns);
}

//Pesquisa um Artista na Lista
void pesquisarArtista(CelulaA **lista, char* elemento){
	Artista Apesquisado;
	Musica entrada;
	int n;
	if(listaVaziaArt(lista)){
		printf("ERRO AO PESQUISAR! NAO HA ARTISTAS!\n");
		return ;
	}
	CelulaA *aux = (*lista);
	do{
		if(strcmp(aux->infoA.nomeA, elemento) == 0){
			Apesquisado = aux->infoA;
			do{
				system("cls");
				imprimirPesquisadaArt(&Apesquisado);
				printf("\n----------Menu do Pesquisar----------\n");
				printf("1 - Ver todas as Musicas de %s.\n", Apesquisado.nomeA);
				printf("2 - Pesquisar uma Musica de %s.\n", Apesquisado.nomeA);
				printf("3 - Inserir uma Musica em %s.\n", Apesquisado.nomeA);
				printf("4 - Remover o %s da Lista.\n", Apesquisado.nomeA);
				printf("5 - Tocar as Musicas de %s.\n", Apesquisado.nomeA);
				printf("0 - Encerrar pesquisa.\n");
				printf("\nOperacao: ");
				do{
					scanf("%d", &n);
					if((n < 0)||(n > 5)){
						printf("VALOR INVALIDO! DIGITE UMA OPCAO VALIDA!\n");
					}
				}while((n < 0)||(n > 5));
				//Imprime Todas as Musicas do Artista
				if(n == 1){
					printf("-----------Musicas que %s Canta--------\n", Apesquisado.nomeA);
					imprimeAllMusicas(&aux->infoA.Musi);
				}
				//Pesquisa uma Musica no Artista
				else if(n == 2){
					char entrada[100];
					printf("Nome: ");
					fflush(stdin);
					gets(entrada);
					fflush(stdin);
					pesquisarMusicas(&aux->infoA.Musi, entrada);
				}
				//Insere uma Musica no Artista
				else if(n == 3){
					do{
						printf("Nome da Musica: ");
						fflush(stdin);
						gets(entrada.nomeM);
						fflush(stdin);
						printf("Duracao: ");
						scanf("%d", &entrada.duracao);
						printf("Album: ");
						fflush(stdin);
						gets(entrada.album);
						fflush(stdin);
						printf("Compositor: ");
						fflush(stdin);
						gets(entrada.compositor);
						fflush(stdin);
						printf("\n");
						inserirOrdenado(&(*lista)->infoA.Musi, entrada);
						printf("Deseja inserir mais alguma Musica? (1 = SIM/0 = NAO)\n");
						do{
							scanf("%d", &n);
							if((n < 0)||(n > 1)){
								printf("VALOR INVALIDO! DIGITE UMA OPCAO VALIDA!\n");
							}
						}while((n != 0)&&(n != 1));
					}while(n != 0);
				}
				//Remove o Artista
				else if(n == 4){
					(aux->prox)->ant = aux->ant;
					(aux->ant)->prox = aux->prox;
				 	removerPesquisadaArt(&aux);
				}
				//"Toca" as Musicas do Artista
				else if(n == 5){
					imprimeOrdenado(&aux->infoA.Musi);
				}
				//Encerra a Busca
				else if(n == 0){
					return ;
				}
				system("pause");
			}while((n >= 0)||(n <= 5));
			return ;
		}
		aux = aux->prox;
	}while(aux != (*lista));
	printf("NAO EXISTE ESSE ARTISTA NA PLATAFORMA!\n");
	return ;
}

//Remove Todos os Artistas
void removerAllArtistas(CelulaA **lista){
	CelulaA *aux;
	if(listaVaziaArt(lista)){
		printf("ERRO NA REMOCAO! NAO HA ARTISTAS!\n");
		return ;
	}
	aux = (*lista)->ant;
	do{
		removerTodasAsMusicas(&aux->infoA.Musi);
		//ISOLO A CELULA
		(aux->prox)->ant = aux->ant;
		(aux->ant)->prox = aux->prox;
		aux->ant = NULL;
		aux->prox = NULL;
		//REMOVO ELA
		free(aux);
		//ANDO
		aux = (*lista)->ant;
	}while(aux != NULL);
	(*lista) = NULL;
}

//Imprime Todos os Artistas
void imprimeAllArtistas(CelulaA **lista){
	int i = 1;
	if(listaVaziaArt(lista)){
		printf("ERRO AO IMPRIMIR! NAO HA ARTISTAS!\n");
		return ;
	}
	CelulaA *aux = (*lista);
	do{
		printf("\n----------------Artista %d-------------", i);
		printf("\nNome: %s", aux->infoA.nomeA);
		printf("\nGenero: %s", aux->infoA.genero);
		printf("\nAlbuns: %d\n", aux->infoA.qntAlbuns);
		imprimeAllMusicas(&aux->infoA.Musi);
		aux = aux->prox;
		i++;
	}while(aux != (*lista));
}

void ImprimeMenu(){
	printf("--_____------_____-----_____--_____--___________---_____--________--____------____\n");
	printf("--|---|------|---|-----|---|--|___|--|----------|--|___|--|---____|-\\---\\----/---/\n");
	printf("--|---|------|---|-----|---|--|---|--|---_______|--|---|--|---|___---\\---\\--/---/ \n");
	printf("--|---|------|---|-----|---|--|---|--|---|---____--|---|--|---____|---\\---\\/---/\n");
	printf("--|---|------|---|-----|---|--|---|--|---|  |_--|--|---|--|---|--------\\------/\n");
	printf("--|---|_____-|----\\___/----|--|---|--|---|___|--|--|---|--|---|---------|----|\n");
	printf("--|---------|-\\-----------/ --|---|--|----------|--|---|--|---|---------|----|\n");
	printf("--|_________|--\\_________/----|___|--|__________|--|___|--|___|---------|____|\n");
	printf("----------------------------------M E N U--------------------------------------\n\n");
	printf("1 - Inserir um Artista.\n");
	printf("2 - Pesquisar um Artista na Plataforma.\n");
	printf("3 - Imprimir Todos os Artistas.\n");
	printf("4 - Remover Todos os Artistas Cadastrados.\n");
	printf("0 - Sair do Programa.\n");
}

int main(){
	int menu;
	char pesquisa[100];
	CelulaA *LuigiFy;
	CelulaA *pont;
	Artista entrada;
	inicializaListaArt(&LuigiFy);
	do{
		system("cls");
		ImprimeMenu();
		printf("Digite um comando: ");
		do{
			scanf("%d", &menu);
			if((menu < 0)||(menu > 4)){
				printf("VALOR INVALIDO! DIGITE UMA OPCAO VALIDA!\n");
			}
			//printf("Menu = %d", menu);
		}while((menu < 0)||(menu > 4));
		system("cls");
		//Insere um Artista
		if(menu == 1){
			printf("Digite as informacoes do Artista:\n");
			printf("Nome do Artista: ");
			fflush(stdin);
			gets(entrada.nomeA);
			fflush(stdin);
			printf("Genero: ");
			fflush(stdin);
			gets(entrada.genero);
			fflush(stdin);
			printf("Quantidade de Albuns: ");
			scanf("%d", &entrada.qntAlbuns);
			printf("\n");
			inserirOrdenadoArt(&LuigiFy, entrada);
		}
		//Pesquisa um artista
		else if(menu == 2){
			printf("Pesquisar: ");
			fflush(stdin);
			gets(pesquisa);
			fflush(stdin);
			pesquisarArtista(&LuigiFy, pesquisa);
		}
		//Imprimir Todos os Artistas
		else if(menu == 3){
			imprimeAllArtistas(&LuigiFy);
		}
		//Remove todos os Artistas
		else if(menu == 4){
			removerAllArtistas(&LuigiFy);
		}
		system("pause");
	}while(menu != 0);
	return 0;
}

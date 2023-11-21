// Estrutura dos registros
#ifndef ATRIBUTOS_H
#define ATRIBUTOS_H

struct Atributos{
	char id[6];
	char latitude[10];
	char longitude[11];
	char descricao[100];
	char zip[7];
	char title[50];
	char timeStamp[20];
	char twp[20];
	char addr[50];
	char e[1];
    
	Atributos(){
		for(int i = 0; i < 6; i++){
			id[i] = '\0';
		}
		for(int i = 0; i < 10; i++){
			latitude[i] = '\0';
		}
		for(int i = 0; i < 11; i++){
			longitude[i] = '\0';
		}
		for(int i = 0; i < 100; i++){
			descricao[i] = '\0';
		}
		for(int i = 0; i < 7; i++){
			zip[i] = '\0';
		}
		for(int i = 0; i < 50; i++){
			title[i] = '\0';
		}
		for(int i = 0; i < 20; i++){
			timeStamp[i] = '\0';
		}
		for(int i = 0; i < 20; i++){
			twp[i] = '\0';
		}
		for(int i = 0; i < 50; i++){
			addr[i] = '\0';
		}
		for(int i = 0; i < 1; i++){
			e[i] = '\0';
		}
	}
};

#endif
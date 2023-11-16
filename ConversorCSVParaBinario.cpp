#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>

using namespace std;

ifstream arquivo_csv("call911_1.csv");
fstream arquivo_bin("call911_1.bin", ios::in | ios::binary |ios::out |ios::trunc);

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

Atributos converteStringParaChar(string dados[]){
	
	Atributos estrutura;
	
	strcpy(estrutura.id,dados[0].c_str());
	strcpy(estrutura.latitude,dados[1].c_str());
	strcpy(estrutura.longitude,dados[2].c_str());
	strcpy(estrutura.descricao,dados[3].c_str());
	strcpy(estrutura.zip,dados[4].c_str());
	strcpy(estrutura.title,dados[5].c_str());
	strcpy(estrutura.timeStamp,dados[6].c_str());
	strcpy(estrutura.twp,dados[7].c_str());
	strcpy(estrutura.addr,dados[8].c_str());
	strcpy(estrutura.e,dados[9].c_str());

	return estrutura;
}

void converteCSVParaBinario (){
	string *dados;
	Atributos estrutura = Atributos();
	dados = new string[10];
	string linha ="";
	unsigned contador = 0;
	arquivo_csv.seekg(47); // começar 47 bytes a frente para nao ler a descrição dos campos e o \n
	arquivo_bin.seekg(sizeof(contador)); // começar 4 bytes a frente para escrever o contador
	while(getline(arquivo_csv, linha)){
		stringstream inputstring(linha);
		for (int j = 0; j < 10; j++){
			getline(inputstring, dados[j], ',');
		}
		estrutura = converteStringParaChar(dados);
		arquivo_bin.write((char *)&estrutura,sizeof(Atributos));
		linha = "";
		contador++;
	}
	arquivo_csv.close();
	arquivo_bin.seekg(0);
	arquivo_bin.write((char *)&contador,sizeof(contador));
}

int main() {
	converteCSVParaBinario();
	arquivo_bin.close();
	return 0;
}
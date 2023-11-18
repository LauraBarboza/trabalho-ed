#include <cstdio>
#include <iostream>
#include <cmath>
#include <fstream>
#include <cstring>
#include "ManipulaArquivoBinario.cpp"

using namespace std;

fstream arqF1("f1.bin", ios::binary | ios::in | ios::out); //cria arquivos auxiliares para realizar a ordenação
fstream arqF2("f2.bin", ios::binary | ios::in | ios::out);
fstream arqS1("s1.bin", ios::binary | ios::in | ios::out);
fstream arqS2("s2.bin", ios::binary | ios::in | ios::out);

void unirArquivos(int etapa, int entradas);

void dividirArquivo(){
	Atributos* registroAuxiliar = new Atributos;
	fstream arquivo("call911_1.bin", ios::binary | ios::in | ios::out); // abre o arquivo a ser dividido

    unsigned totalElementos;
    arquivo.seekg(0);
    arquivo.read((char *)&totalElementos, sizeof(unsigned)); // lê o total de elementos do arquivo

    int tam1, tam2;
    if (totalElementos % 2 == 0){ // se o total de elementos for par, o tamanho de cada arquivo será igual
        tam1 = totalElementos/2;
        tam2 = tam1;
    }else{ // se o total de elementos for impar, o tamanho de cada arquivo será diferente
        tam1 = totalElementos/2;
        tam2 = tam1 + 1;
    }

    for (int i = 0 ; i < tam1 ; i++) { // copia metade dos registros para o arquivo de saida 1
        arquivo.read((char *) registroAuxiliar, sizeof(Atributos));
        arqF1.write((char *) registroAuxiliar, sizeof(Atributos));
    }
    for (int i = 0 ; i < tam2 ; i++) {// copia a outra metade dos registros para o arquivo de saida 2
        arquivo.read((char *) registroAuxiliar, sizeof(Atributos));
        arqF2.write((char *) registroAuxiliar, sizeof(Atributos));
    }

    delete registroAuxiliar; //desaloca registroAuxiliar
}


void ordenarArquivo(int etapa, int tamOriginal, int entradas){ // funcao de ordenacao externa
	int tamBloco = pow(2, etapa); // tamanho do bloco a ser ordenado
	Atributos* registroAux1 = new Atributos; // armazena registros do f1.bin ou s1.bin
	Atributos* registroAux2 = new Atributos; // armazena registros do f2.bin ou s2.bin

	// fstream arqF1; // somente declarando as variáveis de entrada e saída
	// fstream arqF2;
	// fstream arqS1;
	// fstream arqS2;

	if (entradas == 1){ // se os arquivos de entrada forem os f1 e f2
		remove( "s1.bin" ); // limpa os dados dos arquivos s1 e s2 para sua posterior escrita
		remove( "s2.bin" ); 
		arqF1.open("f1.bin", ios::binary | ios::in); // abre os arquivos f1 e f2 para leitura
		arqF2.open("f2.bin", ios::binary | ios::in); 
		arqS1.open("s1.bin", ios::binary | ios::out); // abre os arquivos s1 e s2 para escrita
		arqS2.open("s2.bin", ios::binary | ios::out);
	}
	else{
		remove( "f1.bin" ); // limpa os dados dos arquivos f1 e f2 para sua posterior escrita
		remove( "f2.bin" ); 
		arqF1.open("s1.bin", ios::binary | ios::in); // abre os arquivos s1 e s2 para leitura
		arqF2.open("s2.bin", ios::binary | ios::in); 
		arqS1.open("f1.bin", ios::binary | ios::out); // abre os arquivos f1 e f2 para escrita
		arqS2.open("f2.bin", ios::binary | ios::out);
	}

	if (!arqF1 or !arqF2){
		cout << "Nao foi possivel abrir os arquivos de entrada\n";
	}
 	else{
		int contador = 0;
		int contadorRegistroAux1 = 0; // contadores para o controle do tamanho dos blocos
		int contadorRegistroAux2 = 0;
		
		while (arqF1.read((char *) registroAux1, sizeof(Atributos)) and arqF2.read((char *) registroAux2, sizeof(Atributos))){ // entra no loop até não conseguir copiar de um dos arquivos
			contadorRegistroAux1 = 0; 
			contadorRegistroAux2 = 0;
			while(contadorRegistroAux1 < tamBloco and contadorRegistroAux2 < tamBloco and !arqF1.eof() and !arqF2.eof()){ //o loop ocorrerá enquanto os contadores forem menores que o tamanho do bloco e os arquivos não tiverem chegado ao fim 
				if (contador % 2 != 0){ // se o contador for impar, escreverá os dados no arqS1
					if (strcmp(registroAux1->descricao, registroAux2->descricao)<0){ // verifica qual descricao vem antes na ordem alfabetica entre os dois registros para assim escreve-lo no arquivo
						arqS1.write((char *) registroAux1, sizeof(Atributos)); 
						contadorRegistroAux1++;
						if (contadorRegistroAux1 < tamBloco) // se o contador registroAux1 for menor que o tamanho do bloco, copiará o próximo registro
							arqF1.read((char *) registroAux1, sizeof(Atributos));
					}else if (strcmp(registroAux1->descricao, registroAux2->descricao)>0){
						arqS1.write((char *) registroAux2, sizeof(Atributos));
						contadorRegistroAux2++;
						if (contadorRegistroAux2 < tamBloco)  // se o contador registroAux2 for menor que o tamanho do bloco, copiará o próximo registro
							arqF2.read((char *) registroAux2, sizeof(Atributos));
					}else{
						if (registroAux1->id < registroAux2->id){ // verifica qual o maior id entre os dois registros para assim escreve-lo no arquivo
							arqS1.write((char *) registroAux1, sizeof(Atributos)); 
							contadorRegistroAux1++;
							if (contadorRegistroAux1 < tamBloco) // se o contador registroAux1 for menor que o tamanho do bloco, copiará o próximo registro
								arqF1.read((char *) registroAux1, sizeof(Atributos));
						}else{
							arqS1.write((char *) registroAux2, sizeof(Atributos));
							contadorRegistroAux2++;
							if (contadorRegistroAux2 < tamBloco)  // se o contador registroAux2 for menor que o tamanho do bloco, copiará o próximo registro
								arqF2.read((char *) registroAux2, sizeof(Atributos));
						}
					}
				}else{ // se o contador for ímpar, escreverá os dados no arqS2
					if (strcmp(registroAux1->descricao, registroAux2->descricao)<0){ // verifica qual descricao vem antes na ordem alfabetica entre os dois registros para assim escreve-lo no arquivo
						arqS2.write((char *) registroAux1, sizeof(Atributos));
						contadorRegistroAux1++;
						if (contadorRegistroAux1 < tamBloco)  // se o contador registroAux1 for menor que o tamanho do bloco, copiará o próximo registro
							arqF1.read((char *) registroAux1, sizeof(Atributos));
					}else if (strcmp(registroAux1->descricao, registroAux2->descricao)>0){
						arqS2.write((char *) registroAux2, sizeof(Atributos));
						contadorRegistroAux2++;
						if (contadorRegistroAux2 < tamBloco)  // se o contador registroAux2 for menor que o tamanho do bloco, copiará o próximo registro
							arqF2.read((char *) registroAux2, sizeof(Atributos));
					}else{
						if (registroAux1->id < registroAux2->id){ // verifica qual o maior id entre os dois registros para assim escreve-lo no arquivo
							arqS2.write((char *) registroAux1, sizeof(Atributos));
							contadorRegistroAux1++;
							if (contadorRegistroAux1 < tamBloco) // se o contador registroAux1 for menor que o tamanho do bloco, copiará o próximo registro
								arqF1.read((char *) registroAux1, sizeof(Atributos));
						}else{
							arqS2.write((char *) registroAux2, sizeof(Atributos));
							contadorRegistroAux2++;
							if (contadorRegistroAux2 < tamBloco)  // se o contador registroAux2 for menor que o tamanho do bloco, copiará o próximo registro
								arqF2.read((char *) registroAux2, sizeof(Atributos));
						}
					}
				}
			}
			while (contadorRegistroAux1 < tamBloco and !arqF1.eof()){ // se ao sair do loop acima, ainda existirem registros no arqF1, eles serão escritos no arquivo definido pelo contador
				if (contador % 2 != 0){ 
					arqS1.write((char *) registroAux1, sizeof(Atributos)); 
					contadorRegistroAux1++;
					if (contadorRegistroAux1 < tamBloco)
						arqF1.read((char *) registroAux1, sizeof(Atributos));
				}else{
					arqS2.write((char *) registroAux1, sizeof(Atributos));
					contadorRegistroAux1++;
					if (contadorRegistroAux1 < tamBloco)
						arqF1.read((char *) registroAux1, sizeof(Atributos));
				}
			}
			while (contadorRegistroAux2 < tamBloco and !arqF2.eof()){ // se ao sair do loop acima, ainda existirem registros no arqF2, eles serão escritos no arquivo definido pelo contador
				if (contador % 2 != 0){
					arqS1.write((char *) registroAux2, sizeof(Atributos));
					contadorRegistroAux2++;
					if (contadorRegistroAux2 < tamBloco)
						arqF2.read((char *) registroAux2, sizeof(Atributos));
				}else{
					arqS2.write((char *) registroAux2, sizeof(Atributos));
					contadorRegistroAux2++;
					if (contadorRegistroAux2 < tamBloco)
						arqF2.read((char *) registroAux2, sizeof(Atributos));
				}
			}
			contador++;
		}
		if (!arqF1.eof()){ //Se foi o arqF2 que chegou ao final, copia o restante do arqF1 para o arquivo definido pelo contador
			if (contador % 2 !=0){
				arqS1.write((char *) registroAux1, sizeof(Atributos)); // pela lógica de curto-circuito, o registro do arqF1 já foi copiado
				while (arqF1.read((char *) registroAux1, sizeof(Atributos))){ // copiará todos os registros do arqF1 até chegar ao final
					arqS1.write((char *) registroAux1, sizeof(Atributos));
				}
			}else{
				arqS2.write((char *) registroAux1, sizeof(Atributos));
				while (arqF1.read((char *) registroAux1, sizeof(Atributos))){
					arqS2.write((char *) registroAux1, sizeof(Atributos));
				}
			}
		}
		else if (!arqF2.eof()){ //Se foi o arqF1 que chegou ao final, copia o restante do arqF2 para o arquivo definido pelo contador
			if (contador % 2 !=0){
				while (arqF2.read((char *) registroAux2, sizeof(Atributos))){ // copiará todos os registros do arqF2 até chegar ao final
					arqS1.write((char *) registroAux2, sizeof(Atributos));
				}
			}else{
				while (arqF2.read((char *) registroAux2, sizeof(Atributos))){
					arqS2.write((char *) registroAux2, sizeof(Atributos));
				}
			}
		}
		
	}
	
	arqF1.close(); // fecha todos os arquivos
	arqF2.close();
	arqS1.close();
	arqS2.close();
	delete registroAux1; // deleta os registros auxiliares
	delete registroAux2; 
	
	if (2*tamBloco < tamOriginal/2){ // se o tamanho do bloco (que agora será o dobro do começo da função) for menor do que 1/2 do tamanho original, as mesmas ações acima serão realizadas, porém com os arquivos de entrada agora sendo os de saída e vice-versa
		if(entradas == 1){
			ordenarArquivo(etapa+1, tamOriginal, 34);
		}
		else{
			ordenarArquivo(etapa+1, tamOriginal, 12);
		}
	}
	else { // se o tamanho do bloco for igual ou maior do que 1/4 do tamanho original, chegou a etapa final, ou seja, unirá os dois arquivos finais
		if(entradas == 1){
			unirArquivos(etapa+1, 2); // se as entradas da interaçao tiverem sido f1 e f2, entao os arquivos a serem unidos serao os aux3 e aux4
		}
		else{
			unirArquivos(etapa+1, 1);
		}
	}
}


void unirArquivos(int etapa, int entradas){ // funcao chamada quando os arquivos finais escritos forem o aux1 e o aux2
	double tamBloco = pow(2, etapa);
	Atributos* registroAux1 = new Atributos; // armazena registros do aux1.bin ou aux3.bin
	Atributos* registroAux2 = new Atributos; // armazena registros do aux2.bin ou aux4.bin
	remove("AtributosBin.bin"); // limpa os dados do arquivo principal dadosBin.bin para sua posterior escrita

	fstream arqF1;
	fstream arqF2;

	if(entradas == 12){ // se os arquivos de entrada forem os aux1 e aux2
		arqF1.open("aux1.bin", ios::binary | ios::in); // abre os arquivos aux1 e aux2 para leitura
		arqF2.open("aux2.bin", ios::binary | ios::in);
	}
	else{
		arqF1.open("aux3.bin", ios::binary | ios::in); // abre os arquivos aux3 e aux4 para leitura
		arqF2.open("aux4.bin", ios::binary | ios::in); 
	}

	fstream arqS1("AtributosBin.bin", ios::binary | ios::out); //abre o arquivo dadosBin.bin para escrita
	
	int i = 0; // contador registroAux1
	int j = 0; // contador registroAux2

	while (arqF1.read((char *) registroAux1, sizeof(Atributos)) and arqF2.read((char *) registroAux2, sizeof(Atributos))){ // entrara no looping de while até não conseguir copiar de um dos arquivos
		i = 0;
		j = 0;
		while(i < tamBloco and j < tamBloco and !arqF1.eof() and !arqF2.eof()){ //o looping ocorrerá enquanto os contadores forem menor que o tamanho do bloco e os arquivos não tiverem chegado ao fim 
			if (strcmp(registroAux1->descricao, registroAux2->descricao)<0){ // verifica qual descricao vem antes na ordem alfabetica entre os dois registros para assim escreve-lo no arquivo
				arqS1.write((char *) registroAux1, sizeof(Atributos));
				i++;
				if (i < tamBloco) // se o contador registroAux1 for menor que o tamanho do bloco, copiará o próximo registro
					arqF1.read((char *) registroAux1, sizeof(Atributos));
			}else if (strcmp(registroAux1->descricao, registroAux2->descricao)>0){
				arqS1.write((char *) registroAux2, sizeof(Atributos));
				j++;
				if (j < tamBloco)  // se o contador registroAux2 for menor que o tamanho do bloco, copiará o próximo registro
					arqF2.read((char *) registroAux2, sizeof(Atributos));
			}else{
				if (registroAux1->id < registroAux2->id){ // verifica qual o maior id entre os dois registros para assim escreve-lo no arquivo
					arqS1.write((char *) registroAux1, sizeof(Atributos)); 
					i++;
					if (i < tamBloco) // se o contador registroAux1 for menor que o tamanho do bloco, copiará o próximo registro
						arqF1.read((char *) registroAux1, sizeof(Atributos));
				}else{
					arqS1.write((char *) registroAux2, sizeof(Atributos));
					j++;
					if (j < tamBloco)  // se o contador registroAux2 for menor que o tamanho do bloco, copiará o próximo registro
						arqF2.read((char *) registroAux2, sizeof(Atributos));
				}
			}
		}
		while (i < tamBloco and !arqF1.eof()){ // verifica se, ao sair do looping acima, ainda existem registros no arqF1 e escreve-os no arquivo definido pelo contador
			arqS1.write((char *) registroAux1, sizeof(Atributos));
			i++;
			if (i < tamBloco)
				arqF1.read((char *) registroAux1, sizeof(Atributos));
		}
		while (j < tamBloco and !arqF2.eof()){ // verifica se, ao sair do looping acima, ainda existem registros no arqF2 e escreve-os no arquivo definido pelo contador
				arqS1.write((char *) registroAux2, sizeof(Atributos));
				j++;
				if (j < tamBloco)
					arqF2.read((char *) registroAux2, sizeof(Atributos));
		}
	}

	if (!arqF1.eof()){ //Se foi o arqF2 que chegou ao final, copia o restante do arqF1 para o arqS1
		arqS1.write((char *) registroAux1, sizeof(Atributos)); // pela lógica de curto-circuito, o registro do arqF1 foi copiado
		while (arqF1.read((char *) registroAux1, sizeof(Atributos))){ // copiará todos os registros do arqF1 até chegar ao final
			arqS1.write((char *) registroAux1, sizeof(Atributos));
		}
	}
	else if (!arqF2.eof()){ //Se foi o arqF1 que chegou ao final, copia o restante do arqF2 para o arqS1
		while (arqF2.read((char *) registroAux2, sizeof(Atributos))){ // copiará todos os registros do arqF2 até chegar ao final
			arqS1.write((char *) registroAux2, sizeof(Atributos));
		}
	}

	arqF1.close(); // fecha os arquivos
	arqF2.close();
	arqS1.close();
	delete registroAux1; // desaloca os registros auxiliares
	delete registroAux2;
	remove( "aux1.bin" ); // deleta os arquivos auxiliares
	remove( "aux2.bin" ); 
	remove( "aux3.bin" ); 
	remove( "aux4.bin" ); 
}

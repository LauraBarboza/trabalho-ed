/*****************************************************
 * Código 1: Manipulação de Arquivo Binário
 * Criadores: Laura Sarto - Matrícula: 202120154
 *            Dominique Antunes - Matrícula: 202020377
 * Descrição: Este código implementa funções para 
 *            manipular um arquivo binário, incluindo 
 *            adicionar, ler, alterar e ordenar registros.
 *****************************************************/

#include <fstream>
#include <iostream>
#include "OrdenadorArquivoBinario.cpp"
using namespace std;

fstream arquivo_bin("call911_1.bin");

void imprimirAtributo(const char *atributo, size_t tamanho) {
    for (size_t i = 0; i < tamanho; ++i) {
        if (atributo[i] != '\0') // não imprime null
        cout << atributo[i];
    }
    cout << ", ";
}

void adicionarElemento(int posicao, Atributos *dado) {
    Atributos *atual = new Atributos;
    Atributos *proximo = new Atributos;

    unsigned totalElementos;
    arquivo_bin.seekg(0);
    arquivo_bin.read((char *)&totalElementos, sizeof(unsigned));

    arquivo_bin.seekg(sizeof(unsigned) + posicao * sizeof(Atributos));
    arquivo_bin.read((char *)atual, sizeof(Atributos));

    arquivo_bin.seekg(sizeof(unsigned) + posicao * sizeof(Atributos));
    arquivo_bin.write((char *)dado, sizeof(Atributos));

    unsigned contador = posicao;
    while (contador < totalElementos - 1) {
        proximo = new Atributos;
        arquivo_bin.seekg(sizeof(unsigned) + (contador + 1) * sizeof(Atributos));
        arquivo_bin.read((char *)proximo, sizeof(Atributos));
        arquivo_bin.seekg(sizeof(unsigned) + (contador + 1) * sizeof(Atributos));
        arquivo_bin.write((char *)atual, sizeof(Atributos));
        atual = proximo;
        contador++;
    }

    arquivo_bin.seekg(sizeof(unsigned) + (contador + 1) * sizeof(Atributos));
    arquivo_bin.write((char *)atual, sizeof(Atributos));

    arquivo_bin.seekg(0);
    totalElementos++;
    arquivo_bin.write((char *)&totalElementos, sizeof(unsigned));
}

void lerElemento(int posicao) {
    Atributos linha;
    arquivo_bin.seekg(posicao * sizeof(Atributos) + sizeof(unsigned));
    arquivo_bin.read((char *)&linha, sizeof(Atributos));
    imprimirAtributo(linha.id, sizeof(linha.id));
    imprimirAtributo(linha.latitude, sizeof(linha.latitude));
    imprimirAtributo(linha.longitude, sizeof(linha.longitude));
    imprimirAtributo(linha.descricao, sizeof(linha.descricao));
    imprimirAtributo(linha.zip, sizeof(linha.zip));
    imprimirAtributo(linha.title, sizeof(linha.title));
    imprimirAtributo(linha.timeStamp, sizeof(linha.timeStamp));
    imprimirAtributo(linha.twp, sizeof(linha.twp));
    imprimirAtributo(linha.addr, sizeof(linha.addr));
    imprimirAtributo(linha.e, sizeof(linha.e));
    cout << endl;
}

void lerIntervaloElementos(int posicaoInicial, int posicaoFinal) {
    Atributos linha;
    arquivo_bin.seekg(posicaoInicial * sizeof(Atributos) + sizeof(unsigned));
    for (int i = posicaoInicial; i <= posicaoFinal; i++) {
        arquivo_bin.read((char *)&linha, sizeof(Atributos));
        imprimirAtributo(linha.id, sizeof(linha.id));
        imprimirAtributo(linha.latitude, sizeof(linha.latitude));
        imprimirAtributo(linha.longitude, sizeof(linha.longitude));
        imprimirAtributo(linha.descricao, sizeof(linha.descricao));
        imprimirAtributo(linha.zip, sizeof(linha.zip));
        imprimirAtributo(linha.title, sizeof(linha.title));
        imprimirAtributo(linha.timeStamp, sizeof(linha.timeStamp));
        imprimirAtributo(linha.twp, sizeof(linha.twp));
        imprimirAtributo(linha.addr, sizeof(linha.addr));
        imprimirAtributo(linha.e, sizeof(linha.e));
        cout << endl;
    }
}

void imprimirTodos() {
    Atributos linha;
    unsigned totalElementos;
    arquivo_bin.seekg(0);
    arquivo_bin.read((char *)&totalElementos, sizeof(unsigned));

    arquivo_bin.seekg(sizeof(unsigned));
    for (unsigned i = 0; i < totalElementos; i++) {
        arquivo_bin.read((char *)&linha, sizeof(Atributos));
        imprimirAtributo(linha.id, sizeof(linha.id));
        imprimirAtributo(linha.latitude, sizeof(linha.latitude));
        imprimirAtributo(linha.longitude, sizeof(linha.longitude));
        imprimirAtributo(linha.descricao, sizeof(linha.descricao));
        imprimirAtributo(linha.zip, sizeof(linha.zip));
        imprimirAtributo(linha.title, sizeof(linha.title));
        imprimirAtributo(linha.timeStamp, sizeof(linha.timeStamp));
        imprimirAtributo(linha.twp, sizeof(linha.twp));
        imprimirAtributo(linha.addr, sizeof(linha.addr));
        imprimirAtributo(linha.e, sizeof(linha.e));
        cout << endl;
    }
}

void alterarRegistro(int posicao, Atributos *dado) {
    arquivo_bin.seekg(posicao * sizeof(Atributos) + sizeof(unsigned));
    arquivo_bin.write((char *)dado, sizeof(Atributos));
}

void trocarRegistros(int posicaoA, int posicaoB) {
    Atributos *a = new Atributos;
    Atributos *b = new Atributos;

    arquivo_bin.seekg(posicaoA * sizeof(Atributos) + sizeof(unsigned));
    arquivo_bin.read((char *)a, sizeof(Atributos));
    arquivo_bin.seekg(posicaoB * sizeof(Atributos) + sizeof(unsigned));
    arquivo_bin.read((char *)b, sizeof(Atributos));

    arquivo_bin.seekg(posicaoA * sizeof(Atributos) + sizeof(unsigned));
    arquivo_bin.write((char *)b, sizeof(Atributos));
    arquivo_bin.seekg(posicaoB * sizeof(Atributos) + sizeof(unsigned));
    arquivo_bin.write((char *)a, sizeof(Atributos));
}

void ordenaArquivoBin(){
    dividirArquivo();
    unsigned totalElementos;
    arquivo_bin.seekg(0);
    arquivo_bin.read((char *)&totalElementos, sizeof(unsigned));
    ordenarArquivo(1, totalElementos, 1);
}

unsigned consultaQtdeRegistros(){
    unsigned totalElementos;
    arquivo_bin.seekg(0);
    arquivo_bin.read((char *)&totalElementos, sizeof(unsigned));
    return totalElementos;
}

int main() {
    int opcao;
    do {
        cout << "1 - Adicionar elemento em posicao especifica" << endl;
        cout << "2 - Ler um elemento em posicao especifica" << endl;
        cout << "3 - Ler intervalo de elementos" << endl;
        cout << "4 - Imprimir todos" << endl;
        cout << "5 - Alterar registro em posicao especifica" << endl;
        cout << "6 - Trocar registros" << endl;
        cout << "7 - Ordena os arquivos" << endl;
        cout << "0 - Sair" << endl;
        cout << "Opcao: ";
        cin >> opcao;
        switch (opcao) {
            case 1: {
                Atributos *dado = new Atributos;
                int posicao;
                cout << "Posicao: ";
                cin >> posicao;
                cout << "ID: ";
                cin >> dado->id;
                cout << "Latitude: ";
                cin >> dado->latitude;
                cout << "Longitude: ";
                cin >> dado->longitude;
                cout << "Descricao: ";
                cin >> dado->descricao;
                cout << "Zip: ";
                cin >> dado->zip;
                cout << "Title: ";
                cin >> dado->title;
                cout << "TimeStamp: ";
                cin >> dado->timeStamp;
                cout << "Twp: ";
                cin >> dado->twp;
                cout << "Addr: ";
                cin >> dado->addr;
                cout << "E: ";
                cin >> dado->e;
                adicionarElemento(posicao, dado);
                break;
            }
            case 2: {
                int posicao;
                cout << "Posicao: ";
                cin >> posicao;
                lerElemento(posicao);
                break;
            }
            case 3: {
                int posicaoInicial, posicaoFinal;
                cout << "Posicao inicial: ";
                cin >> posicaoInicial;
                cout << "Posicao final: ";
                cin >> posicaoFinal;
                lerIntervaloElementos(posicaoInicial, posicaoFinal);
                break;
            }
            case 4: {
                imprimirTodos();
                break;
            }
            case 5: {
                int posicao;
                Atributos *dado = new Atributos;
                cout << "Posicao: ";
                cin >> posicao;
                cout << "ID: ";
                cin >> dado->id;
                cout << "Latitude: ";
                cin >> dado->latitude;
                cout << "Longitude: ";
                cin >> dado->longitude;
                cout << "Descricao: ";
                cin >> dado->descricao;
                cout << "Zip: ";
                cin >> dado->zip;
                cout << "Title: ";
                cin >> dado->title;
                cout << "TimeStamp: ";
                cin >> dado->timeStamp;
                cout << "Twp: ";
                cin >> dado->twp;
                cout << "Addr: ";
                cin >> dado->addr;
                cout << "E: ";
                cin >> dado->e;
                alterarRegistro(posicao, dado);
                break;
            }
            case 6: {
                int posicaoA, posicaoB;
                cout << "Posicao A: ";
                cin >> posicaoA;
                cout << "Posicao B: ";
                cin >> posicaoB;
                trocarRegistros(posicaoA, posicaoB);
                break;
            }
            case 7: {
                unsigned qtdeRegistros = consultaQtdeRegistros();
                cout << "Ordenando " << qtdeRegistros << endl;
                ordenaArquivoBin();
                qtdeRegistros = consultaQtdeRegistros();
                cout << qtdeRegistros << " ordenados" << endl;
            }
            case 0: {
                break;
            }
            default: {
                cout << "Opcao invalida!" << endl;
                break;
            }
        }
    } while (opcao != 0);

    arquivo_bin.close();

    return 0;
}
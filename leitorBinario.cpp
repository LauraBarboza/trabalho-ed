#include <iostream>
#include <fstream>

using namespace std;

struct Atributos {
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
};

void imprimirAtributo(const char* atributo, size_t tamanho) {
    for (size_t i = 0; i < tamanho; ++i) {
        if (atributo[i] == '\0') break; // Stop if null-terminator is found
        cout << atributo[i];
    }
    cout << endl;
}

int main() {
    ifstream arquivoBinario("call911_1.bin", ios::binary);
    if (!arquivoBinario) {
        cerr << "Não foi possível abrir o arquivo!" << endl;
        return 1;
    }

    Atributos atributos;
    arquivoBinario.seekg(sizeof(int), ios::cur); // Skip the counters
    for (int i = 0; i < 5; ++i) {
        arquivoBinario.read(reinterpret_cast<char*>(&atributos), sizeof(Atributos));
        if (arquivoBinario) {
            imprimirAtributo(atributos.id, sizeof(atributos.id));
            imprimirAtributo(atributos.latitude, sizeof(atributos.latitude));
            imprimirAtributo(atributos.longitude, sizeof(atributos.longitude));
            imprimirAtributo(atributos.descricao, sizeof(atributos.descricao));
            imprimirAtributo(atributos.zip, sizeof(atributos.zip));
            imprimirAtributo(atributos.title, sizeof(atributos.title));
            imprimirAtributo(atributos.timeStamp, sizeof(atributos.timeStamp));
            imprimirAtributo(atributos.twp, sizeof(atributos.twp));
            imprimirAtributo(atributos.addr, sizeof(atributos.addr));
            imprimirAtributo(atributos.e, sizeof(atributos.e));
            cout << endl;
        } else {
            cerr << "Erro ao ler o arquivo!" << endl;
            break;
        }
    }

    arquivoBinario.close();
    system("pause");
    return 0;
}

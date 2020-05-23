#ifndef CHM_CPP
#define CHM_CPP

#include <vector>
#include <iostream>
#include <fstream>
#include <pthread.h>

#include "CargarArchivos.hpp"

using namespace std;

int cargarArchivo(HashMapConcurrente &hashMap,string filePath) {
    fstream file;
    int cant = 0;
    string palabraActual;

    // Abro el archivo.
    file.open(filePath, file.in);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo '" << filePath << "'" << endl;
        return -1;
    }
    while (file >> palabraActual) {
        // Completar (Ejercicio 4)
        hashMap.incrementar(palabraActual);
        cant++;
    }
    // Cierro el archivo.
    if (!file.eof()) {
        cerr << "Error al leer el archivo" << endl;
        file.close();
        return -1;
    }
    file.close();
    return cant;
}

struct ThreadCargaArchivoData {
    HashMapConcurrente *hashMap;
    atomic_flag *archivosProcesados;
    vector<string>* filePaths;
};

void *threadCargaArchivo(void *args) {
    ThreadCargaArchivoData params = *(ThreadCargaArchivoData*) args;

    for (unsigned int index = 0; index < params.filePaths->size(); index++) {
        if (!params.archivosProcesados[index].test_and_set()) {
            cargarArchivo(*params.hashMap, (*params.filePaths)[index]);
        }
    }

    pthread_exit(0);
}

void cargarMultiplesArchivos(HashMapConcurrente &hashMap, unsigned int cantThreads, vector<string> filePaths) {
    // Completar (Ejercicio 4)
    atomic_flag *archivosProcesados = new atomic_flag[filePaths.size()]{ATOMIC_FLAG_INIT};

    pthread_t threads[cantThreads];
    ThreadCargaArchivoData threadData[cantThreads];

    for (unsigned int index = 0; index < cantThreads; index++) {
        threadData[index].hashMap = &hashMap;
        threadData[index].archivosProcesados = archivosProcesados;
        threadData[index].filePaths = &filePaths;

        pthread_create(&threads[index], NULL, threadCargaArchivo, &threadData[index]);
    }

    for (unsigned int index = 0; index < cantThreads; index++) {
        pthread_join(threads[index], NULL);
    }

    delete[] archivosProcesados;
}

#endif

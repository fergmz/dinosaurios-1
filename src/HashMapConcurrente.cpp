#ifndef CHM_CPP
#define CHM_CPP

#include <iostream>
#include <fstream>
#include <pthread.h>

#include "HashMapConcurrente.hpp"

HashMapConcurrente::HashMapConcurrente() {
    for (unsigned int i = 0; i < HashMapConcurrente::cantLetras; i++) {
        tabla[i] = new ListaAtomica<hashMapPair>();
        mutexTabla[i] = PTHREAD_MUTEX_INITIALIZER;
    }
}

unsigned int HashMapConcurrente::hashIndex(std::string clave) {
    return (unsigned int)(clave[0] - 'a');
}

void HashMapConcurrente::incrementar(std::string clave) {
    // Completar (Ejercicio 2)
    unsigned int index = hashIndex(clave);

    pthread_mutex_lock(&mutexTabla[index]);
    int indiceLista = buscarIndice(clave);
    if (indiceLista != -1) {
        hashMapPair valor = tabla[index]->iesimo(indiceLista);
        valor.second++;
    } else {
        hashMapPair valor = std::make_pair(clave, 1);
        tabla[index]->insertar(valor);
    }
    pthread_mutex_unlock(&mutexTabla[index]);
}

int HashMapConcurrente::buscarIndice(std::string clave) {
    // Completar (Ejercicio 2)
    unsigned int index = hashIndex(clave);
    ListaAtomica<hashMapPair>::Iterador it = tabla[index]->crearIt();
    int indiceLista = 0;
    while(it.haySiguiente()) {
        hashMapPair valor = it.siguiente();
        if (valor.first == clave) {
            return indiceLista;
        }
        it.avanzar();
        indiceLista++;
    }
    return -1;
}

std::vector<std::string> HashMapConcurrente::claves() {
    // Completar (Ejercicio 2)
    std::vector<std::string> claves;

    for (int index = 0; index < cantLetras; index++) {
        pthread_mutex_lock(&mutexTabla[index]);
        ListaAtomica<hashMapPair>::Iterador it = tabla[index]->crearIt();
        while(it.haySiguiente()) {
            hashMapPair valor = it.siguiente();
            claves.push_back(valor.first);
            it.avanzar();
        }
        pthread_mutex_unlock(&mutexTabla[index]);
    }

    return claves;
}

unsigned int HashMapConcurrente::valor(std::string clave) {
    // Completar (Ejercicio 2)
    unsigned int result = 0;
    unsigned int index = hashIndex(clave);

    pthread_mutex_lock(&mutexTabla[index]);
    int listaIndex = buscarIndice(clave);
    if (listaIndex != -1) {
        result = tabla[index]->iesimo(listaIndex).second;
    }
    pthread_mutex_unlock(&mutexTabla[index]);

    return result;
}

hashMapPair HashMapConcurrente::maximo() {
    hashMapPair *max = new hashMapPair();
    max->second = 0;

    for (unsigned int index = 0; index < HashMapConcurrente::cantLetras; index++) {
        for (
            auto it = tabla[index]->crearIt();
            it.haySiguiente();
            it.avanzar()
        ) {
            if (it.siguiente().second > max->second) {
                max->first = it.siguiente().first;
                max->second = it.siguiente().second;
            }
        }
    }

    return *max;
}

hashMapPair HashMapConcurrente::maximoParalelo(unsigned int cantThreads) {
    // Completar (Ejercicio 3)
}

#endif

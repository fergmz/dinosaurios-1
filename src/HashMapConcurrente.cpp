#ifndef CHM_CPP
#define CHM_CPP

#include <iostream>
#include <fstream>
#include <pthread.h>

#include "HashMapConcurrente.hpp"

using namespace std;

HashMapConcurrente::HashMapConcurrente() {
    for (unsigned int i = 0; i < HashMapConcurrente::cantLetras; i++) {
        tabla[i] = new ListaAtomica<hashMapPair>();
        mutexTabla[i] = PTHREAD_MUTEX_INITIALIZER;
    }
}

unsigned int HashMapConcurrente::hashIndex(string clave) {
    return (unsigned int)(clave[0] - 'a');
}

void HashMapConcurrente::incrementar(string clave) {
    // Completar (Ejercicio 2)
    unsigned int index = hashIndex(clave);

    pthread_mutex_lock(&mutexTabla[index]);
    int indiceLista = buscarIndice(clave);
    if (indiceLista != -1) {
        tabla[index]->iesimo(indiceLista).second += 1;
    } else {
        hashMapPair valor = make_pair(clave, 1);
        tabla[index]->insertar(valor);
    }
    pthread_mutex_unlock(&mutexTabla[index]);
}

int HashMapConcurrente::buscarIndice(string clave) {
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

vector<string> HashMapConcurrente::claves() {
    // Completar (Ejercicio 2)
    vector<string> claves;

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

unsigned int HashMapConcurrente::valor(string clave) {
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
        pthread_mutex_lock(&mutexTabla[index]); 
    }

    for (unsigned int index = 0; index < HashMapConcurrente::cantLetras; index++) {
        for (auto it = tabla[index]->crearIt(); it.haySiguiente(); it.avanzar()) {
            if (it.siguiente().second > max->second) {
                max->first = it.siguiente().first;
                max->second = it.siguiente().second;
            }
        }
    }

    for (unsigned int index = 0; index < HashMapConcurrente::cantLetras; index++) {
        pthread_mutex_unlock(&mutexTabla[index]);
    }

    return *max;
}

struct ThreadMaximoData {
    ListaAtomica<hashMapPair>* *tabla;
    atomic<hashMapPair*> *maximo;
    atomic_flag *filasProcesadas;
    unsigned int cantFilas;
};

void *threadMaximo(void *args) {
    ThreadMaximoData params = *(ThreadMaximoData*) args;

    for (unsigned int index = 0; index < params.cantFilas; index++) {
        if (!params.filasProcesadas[index].test_and_set()) {

            hashMapPair* maximoFila = new hashMapPair("", 0);

            for (auto it = params.tabla[index]->crearIt(); it.haySiguiente(); it.avanzar()) {
                if (it.siguiente().second > maximoFila->second) {
                    maximoFila->first = it.siguiente().first;
                    maximoFila->second = it.siguiente().second;
                }
            }

            while (true) {
                hashMapPair* maximoActual = params.maximo->load();
                if (maximoFila->second > maximoActual->second && params.maximo->compare_exchange_strong(maximoActual, maximoFila)) {
                    break;
                }
                if (maximoFila->second <= maximoActual->second) {
                    break;
                }
            }
        }
    }

    pthread_exit(0);
}

hashMapPair HashMapConcurrente::maximoParalelo(unsigned int cantThreads) {
    // Completar (Ejercicio 3)
    atomic<hashMapPair*> maximo;
    maximo.store(new hashMapPair("", 0));

    atomic_flag filasProcesadas[cantLetras] = {ATOMIC_FLAG_INIT};

    pthread_t threads[cantThreads];
    ThreadMaximoData threadData[cantThreads];
   
    for (unsigned int index = 0; index < cantLetras; index++) {
        pthread_mutex_lock(&mutexTabla[index]); 
    }

    for (unsigned int index = 0; index < cantThreads; index++) {
        threadData[index].tabla = tabla;
        threadData[index].maximo = &maximo;
        threadData[index].filasProcesadas = filasProcesadas;
        threadData[index].cantFilas = cantLetras;

        pthread_create(&threads[index], NULL, threadMaximo, &threadData[index]);
    }

    for (unsigned int index = 0; index < cantThreads; index++) {
        pthread_join(threads[index], NULL);
    }

    for (unsigned int index = 0; index < cantLetras; index++) {
        pthread_mutex_unlock(&mutexTabla[index]);
    }

    hashMapPair* maxValue = maximo.load();
    return hashMapPair(maxValue->first, maxValue->second);
}

#endif

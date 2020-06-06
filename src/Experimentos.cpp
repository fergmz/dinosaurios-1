#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include "HashMapConcurrente.hpp"
#include "CargarArchivos.hpp"

using namespace std;

double loadFilesTime(vector<string> filePaths, int cantThreads);

int main() {

    // Escenario 1 - Carga de archivos
    // Mismo archivo multiples veces y vamos aumentando la cantidad de threads
    vector<string> filePaths = vector<string>();
    filePaths.push_back("data/corpus");
    filePaths.push_back("data/corpus");
    filePaths.push_back("data/corpus");
    filePaths.push_back("data/corpus");
    filePaths.push_back("data/corpus");
    filePaths.push_back("data/corpus");
    filePaths.push_back("data/corpus");
    filePaths.push_back("data/corpus");
    filePaths.push_back("data/corpus");
    filePaths.push_back("data/corpus");
    filePaths.push_back("data/corpus");
    filePaths.push_back("data/corpus");
    filePaths.push_back("data/corpus");
    filePaths.push_back("data/corpus");

    for (int i = 0; i < 100; i += 5) {
        double time = loadFilesTime(filePaths, 100);
        printf("Escenario 1 con %d threads: %lf\n", i, time);
    }
    
    return(EXIT_SUCCESS);
}

double loadFilesTime(vector<string> filePaths, int cantThreads) {
    double minTime = 99999999999999;
    int iteraciones = 30;

    for (int i = 0; i < iteraciones; i++) {
        struct timespec start, stop;

        if (clock_gettime(CLOCK_REALTIME, &start) == -1) {
            perror("clock gettime start");
            exit(EXIT_FAILURE);
        }

        HashMapConcurrente hashMap = HashMapConcurrente();
        cargarMultiplesArchivos(hashMap, cantThreads, filePaths);

        if (clock_gettime(CLOCK_REALTIME, &stop) == -1) {
            perror("clock gettime stop");
            exit(EXIT_FAILURE);
        }

        double accum = (stop.tv_sec - start.tv_sec) * 1000 + (stop.tv_nsec - start.tv_nsec) / 1000000;
        if (accum < minTime) {
            minTime = accum;
        }   
    }

    return minTime;
}
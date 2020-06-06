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
    /*filePaths.push_back("data/xaa");
    filePaths.push_back("data/xab");
    filePaths.push_back("data/xac");
    filePaths.push_back("data/xad");
    filePaths.push_back("data/xae");
    filePaths.push_back("data/xaf");
    filePaths.push_back("data/xag");
    filePaths.push_back("data/xah");
    filePaths.push_back("data/xai");
    filePaths.push_back("data/xaj");
    filePaths.push_back("data/xak");*/
    filePaths.push_back("data/set-0");
    filePaths.push_back("data/set-1");
    filePaths.push_back("data/set-2");
    filePaths.push_back("data/set-3");
    filePaths.push_back("data/set-4");
    filePaths.push_back("data/set-5");
    filePaths.push_back("data/set-6");
    filePaths.push_back("data/set-7");
    filePaths.push_back("data/set-8");
    filePaths.push_back("data/set-9");
    filePaths.push_back("data/set-10");
    filePaths.push_back("data/set-0");
    filePaths.push_back("data/set-1");
    filePaths.push_back("data/set-2");
    filePaths.push_back("data/set-3");
    filePaths.push_back("data/set-4");
    filePaths.push_back("data/set-5");
    filePaths.push_back("data/set-6");
    filePaths.push_back("data/set-7");
    filePaths.push_back("data/set-8");
    filePaths.push_back("data/set-9");
    filePaths.push_back("data/set-10");

    for (int i = 1; i <= filePaths.size() * 2; i++) {
        double time = loadFilesTime(filePaths, i);
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

        double accum = (double)(stop.tv_sec - start.tv_sec) * (double)1000 + (double)(stop.tv_nsec - start.tv_nsec) / 1000000;
        if (accum < minTime) {
            minTime = accum;
        }   
    }

    return minTime;
}
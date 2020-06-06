#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include "HashMapConcurrente.hpp"
#include "CargarArchivos.hpp"

using namespace std;

double loadFilesTime(vector<string> filePaths, int cantThreads);
double maximoParaleloTime(vector<string> filePaths, int cantThreads);

int main() {

    // Escenario 1 - Archivos de 1000 lineas
    // Multiples archivos y vamos aumentando la cantidad de threads
    vector<string> filePaths1 = vector<string>();
    filePaths1.push_back("data/set-0");
    filePaths1.push_back("data/set-1");
    filePaths1.push_back("data/set-2");
    filePaths1.push_back("data/set-3");
    filePaths1.push_back("data/set-4");
    filePaths1.push_back("data/set-5");
    filePaths1.push_back("data/set-6");
    filePaths1.push_back("data/set-7");
    filePaths1.push_back("data/set-8");
    filePaths1.push_back("data/set-9");
    filePaths1.push_back("data/set-10");

    for (int i = 1; i <= filePaths1.size() * 2; i++) {
        double time = loadFilesTime(filePaths1, i);
        printf("%lf\n", time);
    }

    // Escenario 1 - Archivos de 3700 lineas
    // Multiples archivos y vamos aumentando la cantidad de threads
    vector<string> filePaths2 = vector<string>();
    filePaths2.push_back("data/wet-0");
    filePaths2.push_back("data/wet-1");
    filePaths2.push_back("data/wet-2");
    filePaths2.push_back("data/wet-3");
    filePaths2.push_back("data/wet-4");
    filePaths2.push_back("data/wet-5");
    filePaths2.push_back("data/wet-6");
    filePaths2.push_back("data/wet-7");
    filePaths2.push_back("data/wet-8");
    filePaths2.push_back("data/wet-9");
    filePaths2.push_back("data/wet-10");

    for (int i = 1; i <= filePaths2.size() * 2; i++) {
        double time = loadFilesTime(filePaths2, i);
        printf("%lf\n", time);
    }

    // Escenario 1 - Archivos de 7500 lineas
    // Multiples archivos y vamos aumentando la cantidad de threads
    vector<string> filePaths3 = vector<string>();
    filePaths3.push_back("data/xaa");
    filePaths3.push_back("data/xab");
    filePaths3.push_back("data/xac");
    filePaths3.push_back("data/xad");
    filePaths3.push_back("data/xae");
    filePaths3.push_back("data/xaf");
    filePaths3.push_back("data/xag");
    filePaths3.push_back("data/xah");
    filePaths3.push_back("data/xai");
    filePaths3.push_back("data/xaj");
    filePaths3.push_back("data/xak");

    for (int i = 1; i <= filePaths3.size() * 2; i++) {
        double time = loadFilesTime(filePaths3, i);
        printf("%lf\n", time);
    }

    // Escenario 2 - Calculo de valor Maximo en paralelo
    int cantThreads = 50;
    for (int i = 1; i <= cantThreads; i++) {
        double time = maximoParaleloTime(filePaths2, i);
        printf("%lf\n", time);
    }

    return(EXIT_SUCCESS);
}

double loadFilesTime(vector<string> filePaths, int cantThreads) {
    double minTime = 99999999999999;
    int iteraciones = 10;

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

double maximoParaleloTime(vector<string> filePaths, int cantThreads) {
    HashMapConcurrente hmc = HashMapConcurrente();
    cargarMultiplesArchivos(hmc, 4, filePaths);
    double minTime = 99999999999999;
    int iteraciones = 10;

    for (int i = 0; i < iteraciones; i++) {
        struct timespec start, stop;

        if (clock_gettime(CLOCK_REALTIME, &start) == -1) {
            perror("clock gettime start");
            exit(EXIT_FAILURE);
        }

        hmc.maximoParalelo(cantThreads);

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
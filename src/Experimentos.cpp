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
    
    // Escenario 1 - Caso 1 - Archivos de 1000 lineas
    // Multiples archivos y vamos aumentando la cantidad de threads
    vector<string> filePaths1 = vector<string>();
    filePaths1.push_back("data/1/set-0");
    filePaths1.push_back("data/1/set-1");
    filePaths1.push_back("data/1/set-2");
    filePaths1.push_back("data/1/set-3");
    filePaths1.push_back("data/1/set-4");
    filePaths1.push_back("data/1/set-5");
    filePaths1.push_back("data/1/set-6");
    filePaths1.push_back("data/1/set-7");
    filePaths1.push_back("data/1/set-8");
    filePaths1.push_back("data/1/set-9");
    filePaths1.push_back("data/1/set-10");

    for (int i = 1; i <= filePaths1.size() * 2; i++) {
        double time = loadFilesTime(filePaths1, i);
        printf("%lf\n", time);
    }
    
    // Escenario 1 - Caso 2 - Archivos de 3700 lineas
    // Multiples archivos y vamos aumentando la cantidad de threads
    vector<string> filePaths2 = vector<string>();
    filePaths2.push_back("data/2/wet-0");
    filePaths2.push_back("data/2/wet-1");
    filePaths2.push_back("data/2/wet-2");
    filePaths2.push_back("data/2/wet-3");
    filePaths2.push_back("data/2/wet-4");
    filePaths2.push_back("data/2/wet-5");
    filePaths2.push_back("data/2/wet-6");
    filePaths2.push_back("data/2/wet-7");
    filePaths2.push_back("data/2/wet-8");
    filePaths2.push_back("data/2/wet-9");
    filePaths2.push_back("data/2/wet-10");

    for (int i = 1; i <= filePaths2.size() * 2; i++) {
        double time = loadFilesTime(filePaths2, i);
        printf("%lf\n", time);
    }

    // Escenario 1 - Archivos de 7500 lineas
    // Multiples archivos y vamos aumentando la cantidad de threads
    vector<string> filePaths3 = vector<string>();
    filePaths3.push_back("data/3/xaa");
    filePaths3.push_back("data/3/xab");
    filePaths3.push_back("data/3/xac");
    filePaths3.push_back("data/3/xad");
    filePaths3.push_back("data/3/xae");
    filePaths3.push_back("data/3/xaf");
    filePaths3.push_back("data/3/xag");
    filePaths3.push_back("data/3/xah");
    filePaths3.push_back("data/3/xai");
    filePaths3.push_back("data/3/xaj");
    filePaths3.push_back("data/3/xak");

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

    // Escenario 3 - 
    vector<string> filePaths4 = vector<string>();
    filePaths4.push_back("data/4/set-0aa");
    filePaths4.push_back("data/4/set-0ab");
    filePaths4.push_back("data/4/set-0ac");
    filePaths4.push_back("data/4/set-0ad");
    filePaths4.push_back("data/4/set-0ae");
    filePaths4.push_back("data/4/set-0af");
    filePaths4.push_back("data/4/set-0ag");
    filePaths4.push_back("data/4/set-0ah");
    filePaths4.push_back("data/4/set-0ai");
    filePaths4.push_back("data/4/set-0aj");
    filePaths4.push_back("data/4/set-1aa");
    filePaths4.push_back("data/4/set-1ab");
    filePaths4.push_back("data/4/set-1ac");
    filePaths4.push_back("data/4/set-1ad");
    filePaths4.push_back("data/4/set-1ae");
    filePaths4.push_back("data/4/set-1af");
    filePaths4.push_back("data/4/set-1ag");
    filePaths4.push_back("data/4/set-1ah");
    filePaths4.push_back("data/4/set-1aj");
    filePaths4.push_back("data/4/set-2aa");
    filePaths4.push_back("data/4/set-2ab");
    filePaths4.push_back("data/4/set-2ac");
    filePaths4.push_back("data/4/set-2ad");
    filePaths4.push_back("data/4/set-2ae");
    filePaths4.push_back("data/4/set-2af");
    filePaths4.push_back("data/4/set-2ag");
    filePaths4.push_back("data/4/set-2ah");
    filePaths4.push_back("data/4/set-2aj");
    filePaths4.push_back("data/4/set-3aa");
    filePaths4.push_back("data/4/set-3ab");
    filePaths4.push_back("data/4/set-3ac");
    filePaths4.push_back("data/4/set-3ad");
    filePaths4.push_back("data/4/set-3ae");
    filePaths4.push_back("data/4/set-3af");
    filePaths4.push_back("data/4/set-3ag");
    filePaths4.push_back("data/4/set-3ah");
    filePaths4.push_back("data/4/set-3aj");
    filePaths4.push_back("data/4/set-4aa");
    filePaths4.push_back("data/4/set-4ab");
    filePaths4.push_back("data/4/set-4ac");
    filePaths4.push_back("data/4/set-4ad");
    filePaths4.push_back("data/4/set-4ae");
    filePaths4.push_back("data/4/set-4af");
    filePaths4.push_back("data/4/set-4ag");
    filePaths4.push_back("data/4/set-4ah");
    filePaths4.push_back("data/4/set-4aj");
    filePaths4.push_back("data/4/set-5aa");
    filePaths4.push_back("data/4/set-5ab");
    filePaths4.push_back("data/4/set-5ac");
    filePaths4.push_back("data/4/set-5ad");
    filePaths4.push_back("data/4/set-5ae");
    filePaths4.push_back("data/4/set-5af");
    filePaths4.push_back("data/4/set-5ag");
    filePaths4.push_back("data/4/set-5ah");
    filePaths4.push_back("data/4/set-5aj");
    filePaths4.push_back("data/4/set-6aa");
    filePaths4.push_back("data/4/set-6ab");
    filePaths4.push_back("data/4/set-6ac");
    filePaths4.push_back("data/4/set-6ad");
    filePaths4.push_back("data/4/set-6ae");
    filePaths4.push_back("data/4/set-6af");
    filePaths4.push_back("data/4/set-6ag");
    filePaths4.push_back("data/4/set-6ah");
    filePaths4.push_back("data/4/set-6aj");
    filePaths4.push_back("data/4/set-7aa");
    filePaths4.push_back("data/4/set-7ab");
    filePaths4.push_back("data/4/set-7ac");
    filePaths4.push_back("data/4/set-7ad");
    filePaths4.push_back("data/4/set-7ae");
    filePaths4.push_back("data/4/set-7af");
    filePaths4.push_back("data/4/set-7ag");
    filePaths4.push_back("data/4/set-7ah");
    filePaths4.push_back("data/4/set-7aj");
    filePaths4.push_back("data/4/set-8aa");
    filePaths4.push_back("data/4/set-8ab");
    filePaths4.push_back("data/4/set-8ac");
    filePaths4.push_back("data/4/set-8ad");
    filePaths4.push_back("data/4/set-8ae");
    filePaths4.push_back("data/4/set-8af");
    filePaths4.push_back("data/4/set-8ag");
    filePaths4.push_back("data/4/set-8ah");
    filePaths4.push_back("data/4/set-8aj");
    filePaths4.push_back("data/4/set-9aa");
    filePaths4.push_back("data/4/set-9ab");
    filePaths4.push_back("data/4/set-9ac");
    filePaths4.push_back("data/4/set-9ad");
    filePaths4.push_back("data/4/set-9ae");
    filePaths4.push_back("data/4/set-9af");
    filePaths4.push_back("data/4/set-9ag");
    filePaths4.push_back("data/4/set-9ah");
    filePaths4.push_back("data/4/set-9aj");

    for (int i = 1; i <= 100; i++) {
        double time = loadFilesTime(filePaths4, i);
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
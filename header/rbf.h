#ifndef RBF_H
#define RBF_H

#include <iostream>
#include <vector>
#include "neurona.h"
#include "neurona_rbf.h"

using namespace std;

class RBF {
public:
    RBF (int n_entradas, int neuronas_capa_gaussiana, int neuronas_capa_salida, float eta);
    vector<float> calcular_intermedio (vector<float> & entrada);
    vector<float> calcular_salida_con_intermedio (vector<float> & intermedio);
    vector<float> calcular_salida (vector<float> & entrada);
    void read (const char *filename);
    void inicializar ();
    void entrenar_capa_gaussiana ();
    int entrenar_capa_salida (int cant_epocas, float acierto_minimo);
    int centroide_mas_cerca (vector<float> & punto);
    void graph() const;
    void prueba ();
    void imprimir_centroides ();

private:
    vector<neurona_rbf> capa_gaussiana;
    vector<neurona> capa_salida;
    vector<vector<float> > input, result;
    int entradas;
    int ncg, ncs; // numero de neuronas de cada capa
};

#endif

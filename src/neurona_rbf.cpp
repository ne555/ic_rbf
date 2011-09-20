#include <cmath>
#include <iostream>
#include "util.h"
#include "neurona_rbf.h"

using namespace std;

neurona_rbf::neurona_rbf(int size, float varianza): centroid(size), varianza(varianza) {}

float neurona_rbf::calcular (vector<float> & entrada) {
    float dist;
    vector<float> dist_vec;

    dist_vec = restar_vectores(entrada, centroid);
    dist = norma2(dist_vec);
    return gaussian(dist);
}

bool neurona_rbf::set_centroid (vector<float> & new_centroid) {
    // Devuelve falso si el nuevo centroide no es distinto al actual
    
    if (comparar_vectores(centroid, new_centroid)) {
        return false; // no cambia
    }
    centroid = new_centroid;
    return true;
}

float neurona_rbf::gaussian (float x) {
    return exp(-((x*x)/(2*varianza)));
}
    
float neurona_rbf::distancia2(vector<float> & punto) {
    vector<float> dist_vec;

    dist_vec = restar_vectores(centroid, punto);
    return norma2(dist_vec);
}

void neurona_rbf::graph() const{
	cout << centroid[0] << ' ' << centroid[1] << endl;
}

void neurona_rbf::imprimir_centroide() {
    for (int i = 0; i < centroid.size(); i++) {
        cout << centroid[i] << " ";
    }
    cout << endl;
}

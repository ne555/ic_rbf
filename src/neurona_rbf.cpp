#include <cmath>
#include <iostream>
#include "util.h"
#include "neurona_rbf.h"

using namespace std;

neurona_rbf::neurona_rbf(size_t size):centroid(size), varianza(1){}

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
    float value = exp(-((x*x)/(2*varianza)));
	cerr << x*x/(2*varianza) << ' ' << value << '\n';
	return value;
}
    
float neurona_rbf::distancia2(vector<float> & punto) {
    vector<float> dist_vec;

    dist_vec = restar_vectores(centroid, punto);
    return norma2(dist_vec);
}

void neurona_rbf::graph() const{
	cout << centroid[0] << ' ' << centroid[1] << endl;
}


#ifndef NEURONA_RBF_H
#define NEURONA_RBF_H

using namespace std;

class neurona_rbf {
public:
	neurona_rbf(size_t size);
    float calcular (vector<float> & entrada);
    bool set_centroid (vector<float> & new_centroid);
    float gaussian (float x);
    float distancia2(vector<float> & punto);

	void graph() const;
private:
    vector<float> centroid;
    float varianza;
};

#endif

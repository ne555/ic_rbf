#include <iostream>
#include <valarray>
#include <map>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include "util.h"
using namespace std;

void usage (int status)
{
	if (status != EXIT_SUCCESS)
		cerr << "Try \'-h\' for more information.\n";
	else{
		cerr << "Usage: program.bin [OPTIONS]\n";
		cerr << "Genera la entrada de datos para las redes\n" << 
		"Solo dos percepciones y dos clases\n" << 
		"-n N \t Cantidad de patrones a generar\n" << 
		"-r R \t Radio de desviacion de los puntos ({-1,1}, {-1,1})\n" <<
		"-f string \t Nombre de la funcion clasificadora\n" <<
		"-l \t Lista las funciones disponibles\n" << 
		"-h \t Imprime esta ayuda\n";
	}

	exit (status);
}

typedef std::valarray<float> vectorf;
typedef int (*clasificador)(const vectorf &v);

int XOR(const vectorf &v);
int OR(const vectorf &v);

void init();

template<class T>
void listar(const T &m);

map<string, clasificador> mapa;

int main(int argc, char **argv){
	init();
	int option;
	size_t n=0;
	const size_t p=2;
	float ratio=0;
	clasificador funcion;

	while( (option=getopt(argc, argv, "n:r:f:lh")) != -1 ){
		switch(option){
		case 'n': n=strtol(optarg,NULL,10);break;
		case 'r': ratio=strtof(optarg,NULL);break;
		case 'f': funcion = mapa[string(optarg)];break;
		case 'l': listar(mapa); return EXIT_SUCCESS;
		case 'h': usage(EXIT_SUCCESS); break;
		default: usage(EXIT_FAILURE);
		}
	}

	cout << n << endl;
	for(size_t K=0; K<n; ++K){
		vectorf percepcion(p), desvio(p);

		for(size_t L=0; L<p; ++L)
			percepcion[L] = randomize(0,1);

		percepcion *= 2;
		percepcion -= 1; //aleatoriamente -1 o 1

		for(size_t L=0; L<p; ++L)
			desvio[L] = randomize(-ratio, ratio);
		percepcion += desvio;

		for(size_t L=0; L<p; ++L)
			cout << percepcion[L] << ' ';
		cout << funcion(percepcion) << endl;
	}

	return 0;
}

void init(){
	mapa["xor"] = &XOR;
	mapa["or"] = &OR;
}

template<class T>
void listar(const T &m){
	for(typename T::const_iterator it = m.begin(); it != m.end(); ++it)
		cout << it->first << '\n';
}

int XOR(const vectorf &v){
	size_t count=0;
	for(size_t K=0; K<v.size(); ++K)
		if(v[K]>0) count++;
	
	return (count%2==0)? -1: 1;
}

int OR(const vectorf &v){
	for(size_t K=0; K<v.size(); ++K)
		if(v[K]>0) return 1;
	return -1;
}



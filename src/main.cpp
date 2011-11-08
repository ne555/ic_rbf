#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include "rbf.h"
using namespace std;

void usage (int status)
{
	if (status != EXIT_SUCCESS)
		cerr << "Try \'-h\' for more information.\n";
	else{
		cerr << "Usage: program.bin [OPTIONS]\n";
		cerr << "Clasifica entre grupos.\n" << 
		"-e string \t Nombre del archivo de entrenamiento\n" << 
		"-p string \t Nombre del archivo de prueba\n" << 
		"-E float \t Velocidad de aprendizaje (eta)\n" << 
		"-t int \t Cantidad de epocas en el entrenamiento\n" << 
		"-s float \t Porcentaje de acierto deseado\n" << 
		"-g \t Grafica la evolucion del sistema\n" << 
		"-h \t Ayuda del programa\n";
	}

	exit (status);
}

int main (int argc, char **argv) {
    int ncg, ncs, entradas;
    int epocas = 200;
    float eta = 0.05, success = 0.9;
	float acierto;
    int option, resultado_entrenamiento;
    const char *train_file, *test_file;
	FILE *out=NULL;
    while( (option=getopt(argc, argv, "e:p:E:t:s:gh")) != -1 ){
            switch(option){
            case 'e': train_file=optarg; break;
            case 'p': test_file=optarg; break;
            case 'E': eta=strtof(optarg, NULL); break;
            case 't': epocas=strtol(optarg, NULL, 10); break;
            case 's': success=strtof(optarg, NULL); break;
            case 'h': usage(EXIT_SUCCESS); break;
			case 'g': if(not out) out=popen("./bin/grapher", "w");break;
            default: usage(EXIT_FAILURE);
            }
    }

    // Leer estructura
    cin >> entradas >> ncg >> ncs;

    srand(time(NULL));

    RBF red(entradas, ncg, ncs, eta);
    red.read(train_file, out);
    red.inicializar();
    red.entrenar_capa_gaussiana(out);
    //red.imprimir_centroides(out); cout << endl;
    resultado_entrenamiento = red.entrenar_capa_salida(epocas, success, out);

	if (resultado_entrenamiento == -1) cout << "NoConvergencia "; else cout << "Convergencia ";
    acierto = red.prueba();
	cout << acierto << " " << resultado_entrenamiento << endl;

	if(out) pclose(out);
    return 0;
}


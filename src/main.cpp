#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
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
		"-h \t Ayuda del programa\n";
	}

	exit (status);
}

int main (int argc, char **argv) {
	srand(time(NULL));
	int option;
	const char *train_file, *test_file;
	while( (option=getopt(argc, argv, "e:p:h")) != -1 ){
		switch(option){
		case 'e': train_file=optarg; break;
		case 'p': test_file=optarg; break;
		case 'h': usage(EXIT_SUCCESS); break;
		default: usage(EXIT_FAILURE);
		}
	}

	RBF red(8, 1, 2, 0.05);
	red.read(train_file);
	red.inicializar();
	red.entrenar_capa_gaussiana();
	red.entrenar_capa_salida(1,0.9);


    return 0;
}


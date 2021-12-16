#include <stdio.h>
#include <string.h>
#include "psinfo.h"

#define LONGITUD_MAXIMA_CADENA 1000

int main(int argc, char* argv[])
{
	if (argc<2)
	return perror("Falta un argumento"), 1;

	char statFileName[128];   
	sprintf(statFileName, "/proc/%s/status", argv[1]);
	FILE *fd = fopen(statFileName, "r");
	if (fd == NULL)
		return perror("No puedo encontrar el proceso especificado"),1;
    

	char bufer[LONGITUD_MAXIMA_CADENA];
	char *linea, *campo, *valor;
	char *nombre, *estado;
	char voluntario[20];

	while (fgets(bufer, LONGITUD_MAXIMA_CADENA, fd))
	{
		linea = strtok(bufer, "\n");			
		campo = strtok(linea, ":\t");
		valor = strtok(NULL, ":\t");

		if(campo != NULL)
		{
					
			imprimir_datos(campo, valor, voluntario);
			      			  		
    		}
		
	}

	fclose(fd);

	return 0;
}

void imprimir_datos(char* campo, char* valor, char voluntario[]){

			if(strcmp(campo,"Name")==0) printf("Nombre del proceso: %s\n", valor);
			if(strcmp(campo,"State")==0) printf("Estado: %s\n", valor);
			if(strcmp(campo,"VmSize")==0) printf("Tamano total de la imagen de memoria: %s\n", valor);
			if(strcmp(campo,"VmExe")==0) printf("Tamano de la memoria en la region TEXT: %s\n", valor);
			if(strcmp(campo,"VmData")==0) printf("Tamano de la memoria en la region DATA: %s\n", valor);
			if(strcmp(campo,"VmStk")==0) printf("Tamano de la memoria en la region STACK: %s\n", valor);
			if(strcmp(campo,"voluntary_ctxt_switches")==0) strcpy(voluntario,valor);
			if(strcmp(campo,"nonvoluntary_ctxt_switches")==0) printf("Numero de cambios de contexto realizados (voluntarios - no voluntarios): %s - %s\n", voluntario, valor);
}

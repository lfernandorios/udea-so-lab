#include <stdio.h>
#include <string.h>

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
	char *nombre, *estado, *tamano;

	while (fgets(bufer, LONGITUD_MAXIMA_CADENA, fd))
	{
		linea = strtok(bufer, "\n");
		//printf("La ln es: %s\n", linea);
		
		campo = strtok(linea, ":\t");
		valor = strtok(NULL, ":\t");

		if(campo != NULL)
		{
			//printf("Campo: %s\n", campo);
			//printf("Valor: %s\n", valor);
			
			if(strcmp(campo,"Name")==0) printf("Nombre del proceso: %s\n", valor);
			if(strcmp(campo,"State")==0) printf("Estado: %s\n", valor);
			if(strcmp(campo,"VmSize")==0) printf("Tamaño total de la imagen de memoria: %s\n", valor);     			  		
    		}
		
	}

	fclose(fd);

	return 0;
}
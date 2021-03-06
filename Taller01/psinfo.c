#include <stdio.h>
#include <string.h>
#include "psinfo.h"
#include <stdlib.h>
#include <ctype.h>


#define LONGITUD_MAXIMA_CADENA 1000

int main(int argc, char* argv[])
{	
	
	if (argc<2)
	return perror("Falta al menos un argumento"), 1;
	
	ps_data *datos;	
	datos=(ps_data*)malloc(sizeof(ps_data));
	if(argc==2){
		validar_num(argv[1]);
		leer_archivo(argv[1],datos);	
		imprimir_datos(datos);
	}
	
	if (argc>=3){
		
		for(int i=0;i<(argc-2);i++){
			validar_num(argv[i+2]);		
		}
		int tipo_param=comprobar_parametro(argv[1]);
		parametro_especial(tipo_param, argc, argv,datos);
			
	}
	
	free(datos);

	return 0;
}

//Funcion para seleccionar el parametro especial
void parametro_especial(int tp, int argc, char *argv[], ps_data *datos){

	char buffer[LONGITUD_MAXIMA_CADENA];
	switch(tp){
			
			//caso 1 si es -l
			case 1: 				
				printf("---!Informacion!---\n");
				for(int i=0; i<(argc-2);i++){
					leer_archivo(argv[i+2],datos);
					imprimir_datos_b(datos);
					printf("------------------\n");
				}
				
				break;
			//caso 2 si es -r	
			case 2: 
			
				
				strcpy(buffer, "psinfo-report-");
				strcat(buffer, argv[2]);
				if(argc>3){
					for(int i=3;i<argc;i++){
						strcat(buffer, "-");
						strcat(buffer, argv[i]);
					}
				}
				strcat(buffer, ".info");
				
				for(int i=1; i<(argc-1);i++){
					leer_archivo(argv[i+1],datos);
					imprimir_reporte(datos,buffer);
					
				}
				printf("Archivo de salida generado: %s\n",buffer);
				
				break;
			default: printf("Parametro '%s' invalido, digite un numero de ID de proceso, o ingrese -l o -r seguido del ID de proceso\n ",argv[1]);
			printf("Ejemplo: ./psinfo -l 2031 3520\n ./psinfo -r 2031 3520 \n ./psinfo 2031\n");
			exit(EXIT_SUCCESS);
		
		}
	
}

//Funcion para escribir un archivo con la info del proceso
void imprimir_reporte(ps_data *d,char *b){
	   	
	const char* filename = b;

    	FILE* output_file = fopen(filename, "a");
    	if (!output_file) {
       	 perror("fopen");
      		  exit(EXIT_FAILURE);
   	 }
   	
	fprintf(output_file, "-------\nPid: %s\n", d->pid);
	fprintf(output_file, "Nombre del proceso: %s\n", d->name);  
    	fclose(output_file);
    	

}

//Funcion para leer el archivo
void leer_archivo(char *pid,ps_data *datos){
	
	
	char statFileName[128];   
	sprintf(statFileName, "/proc/%s/status", pid);
	
	FILE *fd = fopen(statFileName, "r");
	if (fd == NULL){
		printf("\nNo se encontro el proceso especificado\n");
		exit(EXIT_SUCCESS);
	}
    
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
			
		guardar_variables(campo, valor,datos);	
		
			      			  		
    		}
		
	}
	

	fclose(fd);
}

//Funcion guarda las variables leidas del archivo
void guardar_variables(char* c, char* v, ps_data *d){
	if(strcmp(c,"Name")==0) {strcpy(d->name,v); }
	else if(strcmp(c,"State")==0) {strcpy(d->state,v); }
	else if(strcmp(c,"Pid")==0) {strcpy(d->pid,v); }
	else if(strcmp(c,"VmSize")==0) {strcpy(d->vmSize,v); }
	else if(strcmp(c,"VmExe")==0) {strcpy(d->vmExe,v); }
	else if(strcmp(c,"VmData")==0) {strcpy(d->vmData,v); }
	else if(strcmp(c,"VmStk")==0) {strcpy(d->vmStk,v); }
	else if(strcmp(c,"voluntary_ctxt_switches")==0) {strcpy(d->voluntario,v); }
	else if(strcmp(c,"nonvoluntary_ctxt_switches")==0) {strcpy(d->noVoluntario,v); }
	
	
	
}


//Funcion devuelve 1 o 2 dependiendo del parametro
int comprobar_parametro(char* p){
	if(strcmp(p,"-l")==0) {return 1;}
	if(strcmp(p,"-r")==0) {return 2;}
	else{ return 0;}
}

//Funcion para imprimir los datos basico de un proceso
void imprimir_datos_b(ps_data *d){

	printf("Pid: %s\n", d->pid);
	printf("Nombre del proceso: %s\n", d->name);	
	

}

//Funcion para imprimir todos los datos importantes del proceso
void imprimir_datos(ps_data *d){

	printf("Nombre del proceso: %s\n", d->name);
	printf("Estado: %s\n", d->state);
	printf("Tamano total de la imagen de memoria: %s\n", d->vmSize);
	printf("Tamano de la memoria en la region TEXT: %s\n", d->vmExe);
	printf("Tamano de la memoria en la region DATA: %s\n", d->vmData);
	printf("Tamano de la memoria en la region STACK: %s\n", d->vmStk);
	printf("Numero de cambios de contexto realizados (voluntarios - no voluntarios): %s - %s\n", d->voluntario, d->noVoluntario);

}

//Funcion valida que los parametros ingresado para el ID del proceso si sean correctos
void validar_num(char n[50]){
	int i=0, j;
	j=strlen(n);
	while(i<j ){
		if(isdigit(n[i])!=0){
			i++;			
		}else{			
			printf("Parametro '%s' invalido, digite un numero de ID de proceso, o ingrese -l o -r seguido del ID de proceso\n ",n);
			printf("Ejemplo: ./psinfo -l 2031 3520\n ./psinfo -r 2031 3520 \n ./psinfo 2031\n");
			exit(EXIT_SUCCESS);
			
		}
	}
	
}





#ifndef __PSINFO_H
#define __PSINFO_H

typedef struct _data_ps ps_data;

struct _data_ps{
	char *pid;
	char *nombre;
	char *estado;
	char *vmSize;
	char *vmExe;
	char *vmData;
	char *vmStk;
	char *voluntario;
	char *noVoluntario;
};


void imprimir_datos(char* c, char* valor,char v[]);

#endif

#ifndef __PSINFO_H_
#define __PSINFO_H_

typedef struct __data_ps ps_data;

struct __data_ps{
	char pid[20];
	char name[20];
	char state[20];
	char vmSize[20];
	char vmExe[20];
	char vmData[20];
	char vmStk[20];
	char voluntario[20];
	char noVoluntario[20];
};


void leer_archivo(char *pid,ps_data *datos);
void guardar_variables(char* c, char* v, ps_data *d);
int comprobar_parametro(char* p);
void imprimir_datos(ps_data *d);
void imprimir_datos_b(ps_data *d);
void parametro_especial(int t,int argc, char *argv[],ps_data *datos);
void imprimir_reporte(ps_data *datos,char *buffer);
void validar_num(char numero[50]);
#endif

/**
 * @file global.cpp
 * @brief Implementación de las funciones y variables globales para el sistema de dinámica orbital.
 *
 * Contiene la inicialización y carga de datos de orientación terrestre, coeficientes gravitacionales,
 * efemérides y parámetros auxiliares que se utilizan de forma compartida en el sistema.
 *
 * @author Francisco Bartolome Alcalde
 */
#include "..\include\global.hpp"
Matrix eopdata;
Matrix Cnm;
Matrix Snm;
Matrix PC;
Param AuxParam;
void eop19620101(int c){
	eopdata = zeros(13,c);
	FILE *fid = fopen("../data/eop19620101.txt", "r");
	if(fid==NULL){
		printf("Fail open eop19620101.txt file\n");
		exit(EXIT_FAILURE);
	}
	for (int j = 1; j<=c; j++){
		fscanf(fid, "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",
		&(eopdata(1,j)), &(eopdata(2,j)), &(eopdata(3,j)),
		&(eopdata(4,j)), &(eopdata(5,j)), &(eopdata(6,j)),
		&(eopdata(7,j)), &(eopdata(8,j)), &(eopdata(9,j)),
		&(eopdata(10,j)), &(eopdata(11,j)), &(eopdata(12,j)),
		&(eopdata(13,j)));
	}
	fclose(fid);
}
void GGM03S(int n){ 
    Cnm = zeros(n,n);
    Snm = zeros(n,n);
	
    FILE *fid = fopen("../DATA/GGM03S.txt","r");
	
    if(fid == NULL){
        printf("Fail open GGM03S.txt file\n");
        exit(EXIT_FAILURE);
    }

    double aux;
    for(int i=1; i<=n; i++){
        for(int j=1; j<=i; j++){
            fscanf(fid,"%lf %lf %lf %lf %lf %lf",&aux,&aux,&(Cnm(i,j)),&(Snm(i,j)),&aux,&aux);
        }
    }

    fclose(fid);
}

void DE430Coeff(int f, int c){
    PC = zeros(f,c);
	
    FILE *fid = fopen("../DATA/DE430Coeff.txt","r");
	
    if(fid == NULL){
        printf("Fail open DE430Coeff.txt file\n");
        exit(EXIT_FAILURE);
    }

    for(int i=1; i<=f; i++){
        for(int j=1; j<=c; j++){
            fscanf(fid,"%lf",&(PC(i,j)));
        }
    }
}

void initializeAuxParam(){
    AuxParam.Mjd_UTC = 49746.1112847221;
    AuxParam.Mjd_TT = 49746.1170623147;
    AuxParam.n = 20;
    AuxParam.m = 20;
    AuxParam.sun = 1;
    AuxParam.moon = 1;
    AuxParam.planets = 1;
}
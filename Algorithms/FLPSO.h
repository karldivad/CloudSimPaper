#ifndef FLPSO_H
#define FLPSO_H

#include <iostream>
#include <stdio.h>
#include <vector>
#include <ctime>
#include <tuple>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include "funciones.h"

using namespace std;

typedef struct {
	vector<tuple<int,int>> v;
	vector<int> x;
	double fitness;
}ParticulaFLPSO;

void mostrar_ParticulaFLPSO_x(ParticulaFLPSO p){
	for (int i = 0; i < p.x.size(); ++i)
	{
		if (p.x[i]==0)
		{
			printf("'T1'");
		}
		else if (p.x[i]==1)
		{
			printf("'T2'");
		}
		else if (p.x[i]==2)
		{
			printf("'T3'");
		}
		else if (p.x[i]==3)
		{
			printf("'T4'");
		}
		else if (p.x[i]==4)
		{
			printf("'T5'");
		}
		else if (p.x[i]==5)
		{
			printf("'T6'");
		}
		else if (p.x[i]==6)
		{
			printf("'T7'");
		}
		else if (p.x[i]==7)
		{
			printf("'T8'");
		}
		else if (p.x[i]==8)
		{
			printf("'T9'");
		}
		else if (p.x[i]==9)
		{
			printf("'T10'");
		}
		else if (p.x[i]==10)
		{
			printf("'T11'");
		}
		else if (p.x[i]==11)
		{
			printf("'T12'");
		}

		if (i!=p.x.size()-1)
		{
			printf(", ");
		}
	}
}

void mostrar_ParticulaFLPSO_v(ParticulaFLPSO p){
	for (int i = 0; i < p.v.size(); ++i)
	{
		printf("(%d, %d)",get<0>(p.v[i]), get<1>(p.v[i]));
		if (i!=p.v.size()-1)
		{
			printf(", ");
		}
	}
	//printf("\n");
}

ParticulaFLPSO Mejor(vector<ParticulaFLPSO> Best){
	ParticulaFLPSO X;
	X=Best[0];
	for (int i = 1; i < Best.size(); ++i)
	{
		if (X.fitness>Best[i].fitness)
		{
			X=Best[i];
		}
	}
	return X;
}

class FLPSO{
public:
	FLPSO(int iteraciones,vector<double> & matrix,vector<double> & matrix2,std::vector<int> Cola,std::vector<int> & npe, std::vector<int> & Vmips);
	//~FLPSO();
	void mostrar_ParticulaFLPSOs();
	vector<int> run();
	vector<int> ValorX();
	double Function(vector<int> & x);
	void llamadita();

	ParticulaFLPSO gBest;
	ParticulaFLPSO lBest;

	vector<int> npe;
	vector<int> Vmips;
	vector<int> Cola;
	vector<double> Mciudades;
	vector<double> length;

	vector<ParticulaFLPSO> ParticulaFLPSOs;
	vector<ParticulaFLPSO> pBest;

	int cantidad_de_iteraciones=1000;
	int tam_poblacion=200;
	//int dimensiones=2;
};

void FLPSO::llamadita(){
	double sum=0;
	std::vector<Num> v={0,1,2,3,4,5,6,7,8,9};

	for (int i = 0; i < v.size()-1; ++i)
	{
		sum+=(Mciudades[v[i]]*(v.size()-i-1));
		//cout<<matrix[v[i-1]][v[i]]<<endl;
	}
	//cout<<endl;
	cout<< sum/v.size()<<endl;
}

double FLPSO::Function(vector<int> & x){
	double maxQ=0;
	double tmpQ;
	for (int j = 0; j < npe.size(); ++j)
	{
		tmpQ=0;
		for (int i = 0; i < x.size(); ++i)
		{
			tmpQ+=length[x[i]]/(npe[j]*Vmips[j]);
		}
		if (maxQ<tmpQ)
		{
			maxQ=tmpQ;
		}
	}
	return maxQ;

	/*double sum=0;
	for (int i = 0; i < x.size()-1; ++i)
	{
		sum+=(Mciudades[x[i]]*(x.size()-i-1));
		//cout<<matrix[v[i-1]][v[i]]<<endl;
	}
	//cout<<endl;
	return sum/x.size();*/
}
/*
double FLPSO::Function(vector<Num> & x){
	double sum=0;
	for (int i = 0; i < x.size()-1; ++i)
	{
		sum+=(Mciudades[x[i]]*(x.size()-i-1));
		//cout<<matrix[v[i-1]][v[i]]<<endl;
	}
	//cout<<endl;
	return sum/x.size();
}*/

vector<int> FLPSO::ValorX(){
	
	vector<int> ciudad;
	while(ciudad.size()!=Mciudades.size()){
		Num aleatorio=random(Mciudades.size());
		auto it=find (ciudad.begin(), ciudad.end(),aleatorio);
		if (it != ciudad.end()){
			;
		}
		else{
		    ciudad.push_back(aleatorio);//std::cout << "Element not found in myvector\n";			
		}
	}
	return ciudad;
}

void FLPSO::mostrar_ParticulaFLPSOs(){
	for (int i = 0; i < tam_poblacion; ++i)
	{
		printf("Actual: [");
		mostrar_ParticulaFLPSO_x(ParticulaFLPSOs[i]);
		printf("]\n");
		printf("Costo Actual: %lf \n",ParticulaFLPSOs[i].fitness);
		
		printf("Actual: [");
		mostrar_ParticulaFLPSO_x(pBest[i]);
		printf("]\n");
		printf("Costo del Mejor: %lf \n",pBest[i].fitness);

		printf("Velocidad: [");
		mostrar_ParticulaFLPSO_v(ParticulaFLPSOs[i]);
		printf("]\n\n");
	}

}

vector<int> FLPSO::run(){
	Num w,d1,d2,rand1,rand2;
	
	for (int iteraciones = 0; iteraciones < cantidad_de_iteraciones; ++iteraciones)
	{
		/*printf("Iteracion %d *************\n", iteraciones+1);
		printf("Mejor Global: [");
		mostrar_ParticulaFLPSO_x(gBest);
		printf("]\n");
		printf("Costo del mejor Global: %lf \n\n",gBest.fitness );
		*/
		//mostrar_ParticulaFLPSOs();

		w=random(1);
		d1=1.49445;
		d2=1.49445;
		//rand1=random(1);
		//rand2=random(1);
		for (int i = 0; i < tam_poblacion; ++i)
		{
	
			ParticulaFLPSOs[i].v=(((pBest[i].x)-(ParticulaFLPSOs[i].x)))+((gBest.x - ParticulaFLPSOs[i].x));
			
			ParticulaFLPSOs[i].x=SS(ParticulaFLPSOs[i].x,ParticulaFLPSOs[i].v);
			ParticulaFLPSOs[i].fitness=Function(ParticulaFLPSOs[i].x);
			if (pBest[i].fitness>ParticulaFLPSOs[i].fitness)
			{
				pBest[i]=ParticulaFLPSOs[i];
			}
		}

		lBest=Mejor(ParticulaFLPSOs);
		if (lBest.fitness<gBest.fitness)
		{
			gBest=lBest;
		}
		//mostrar_ParticulaFLPSOs();
	}
		//printf("Mejor Global: [");
		//mostrar_ParticulaFLPSO_x(gBest);
		//printf("]\n");
		printf("Costo del mejor Global: %lf \n\n",gBest.fitness );
	return gBest.x;
}

FLPSO::FLPSO(int iteraciones,vector<double> & matrix,vector<double> & matrix2,std::vector<int> Cola,std::vector<int> & npe, std::vector<int> & Vmips){
	Mciudades=matrix;
	length=matrix2;
	vector<int> ciudad;
	this->Cola=Cola;
	cantidad_de_iteraciones=iteraciones;
	this->npe=npe;
	this->Vmips=Vmips;
	
	//cout<<"HOLa";
	ParticulaFLPSO P;
	for (int i = 0; i < tam_poblacion; ++i)
	{

		while(ciudad.size()!=Cola.size()){
			Num aleatorio=random(Cola.size());
			auto it=find (ciudad.begin(), ciudad.end(),Cola[aleatorio]);
			if (it != ciudad.end()){
				;
			}
			else{
			    ciudad.push_back(Cola[aleatorio]);//std::cout << "Element not found in myvector\n";			
			
			}
		}
		P.x=ciudad;
		P.fitness=Function(P.x);
		ParticulaFLPSOs.push_back(P);
		pBest.push_back(P);
		ciudad.clear();
		//P.x.clear();
	}


	gBest=Mejor(pBest);
	//mostrar_ParticulaSAPSO(gBest);
	lBest=Mejor(pBest);
	//mostrar_ParticulaSAPSO(lBest);
	run();

}	


#endif	
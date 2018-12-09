#ifndef SAPSO_H
#define SAPSO_H

#include <iostream>
#include <stdio.h>
#include <vector>
#include <ctime>
#include <tuple>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include "funciones.h"



typedef struct {
	vector<tuple<int,int>> v;
	vector<int> x;
	double fitness;
}ParticulaSAPSO;

void mostrar_ParticulaSAPSO_x(ParticulaSAPSO p){
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

void mostrar_ParticulaSAPSO_v(ParticulaSAPSO p){
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

ParticulaSAPSO Mejor(vector<ParticulaSAPSO> Best){
	ParticulaSAPSO X;
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

class SAPSO{
public:
	SAPSO(int iteraciones,vector<double> & matrix,vector<double> & matrix2,std::vector<int> Cola,std::vector<int> & npe, std::vector<int> & Vmips);
	//~PSO();
	void mostrar_ParticulaSAPSOs();
	vector<int> run();
	vector<int> ValorX();
	double Function(vector<int> & x);
	void llamadita();

	ParticulaSAPSO gBest;
	ParticulaSAPSO lBest;


	vector<int> npe;
	vector<int> Vmips;
	vector<int> Cola;
	vector<double> Mciudades;
	vector<double> length;

	vector<ParticulaSAPSO> ParticulaSAPSOs;
	vector<ParticulaSAPSO> pBest;

	int cantidad_de_iteraciones=1000;
	int tam_poblacion=200;
	//int dimensiones=2;
};

void SAPSO::llamadita(){
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



double SAPSO::Function(vector<int> & x){
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
}

vector<int> SAPSO::ValorX(){
	
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

void SAPSO::mostrar_ParticulaSAPSOs(){
	for (int i = 0; i < tam_poblacion; ++i)
	{
		printf("Actual: [");
		mostrar_ParticulaSAPSO_x(ParticulaSAPSOs[i]);
		printf("]\n");
		printf("Costo Actual: %lf \n",ParticulaSAPSOs[i].fitness);
		
		printf("Actual: [");
		mostrar_ParticulaSAPSO_x(pBest[i]);
		printf("]\n");
		printf("Costo del Mejor: %lf \n",pBest[i].fitness);

		printf("Velocidad: [");
		mostrar_ParticulaSAPSO_v(ParticulaSAPSOs[i]);
		printf("]\n\n");
	}

}

vector<int> SAPSO::run(){
	Num w,d1,d2,rand1,rand2;
	
	for (int iteraciones = 0; iteraciones < cantidad_de_iteraciones; ++iteraciones)
	{
		/*printf("Iteracion %d *************\n", iteraciones+1);
		printf("Mejor Global: [");
		mostrar_ParticulaSAPSO_x(gBest);
		printf("]\n");
		printf("Costo del mejor Global: %lf \n\n",gBest.fitness );
		
		mostrar_ParticulaSAPSOs();
*/
		w=random(1);
		d1=1.49445;
		d2=1.49445;
		double fitnessant=0;
		int counter=0;
		ParticulaSAPSO Sbest;
		//rand1=random(1);
		//rand2=random(1);
		double Favg=0;
		for (int i = 0; i < tam_poblacion; ++i)
		{
			Favg+=ParticulaSAPSOs[i].fitness;
		}
		Favg=Favg/tam_poblacion;

		for (int i = 0; i < tam_poblacion; ++i)
		{
			Sbest=ParticulaSAPSOs[i];
			double Temperature=(Favg/Sbest.fitness)-1;
			int SAiteraciones=100;
			
			while(Temperature>0.1 or Temperature<-0.1)
			{
				for (int it = 0; it < 1000; ++it)
				{
					Temperature=(Favg/Sbest.fitness)-1;
					ParticulaSAPSO Snew;
					Snew.x=ParticulaSAPSOs[i].x;

					int posTmp=random(Snew.x.size());
					int posTmp1=random(Snew.x.size());
					while (posTmp==posTmp1)
					{
						posTmp1=random(tam_poblacion);
					}
					swap(Snew.x[posTmp],Snew.x[posTmp1]);
					Snew.fitness=Function(Snew.x);
					if (Snew.fitness<ParticulaSAPSOs[i].fitness)
					{
						Sbest.x=Snew.x;
						Sbest.fitness=Snew.fitness;
					}else if((double) rand()/RAND_MAX<exp((ParticulaSAPSOs[i].fitness-Snew.fitness)/Temperature)){
						ParticulaSAPSOs[i].x=Snew.x;
						ParticulaSAPSOs[i].fitness=Snew.fitness;
					}
				}
				Temperature=Temperature*0.9;
			}

			if (pBest[i].fitness>ParticulaSAPSOs[i].fitness)
			{
				pBest[i]=ParticulaSAPSOs[i];
			}
			
		}


		for (int i = 0; i < tam_poblacion; ++i)
		{
			ParticulaSAPSOs[i].v=(((pBest[i].x)-(ParticulaSAPSOs[i].x)))+((gBest.x - ParticulaSAPSOs[i].x));
			
			ParticulaSAPSOs[i].x=SS(ParticulaSAPSOs[i].x,ParticulaSAPSOs[i].v);
			ParticulaSAPSOs[i].fitness=Function(ParticulaSAPSOs[i].x);
			if (pBest[i].fitness>ParticulaSAPSOs[i].fitness)
			{
				pBest[i]=ParticulaSAPSOs[i];
			}
		}

		lBest=Mejor(pBest);
		if (lBest.fitness<gBest.fitness)
		{
			gBest=lBest;
		}
		if (gBest.fitness==fitnessant)
		{
			counter++;
			if (counter==5)
			{
				break;
			}
		}else{
			counter=0;
		}
		fitnessant=gBest.fitness;
		//mostrar_ParticulaSAPSOs();
	}
		//printf("Mejor Global: [");
		//mostrar_ParticulaSAPSO_x(gBest);
		//printf("]\n");
		printf("Costo del mejor Global: %lf \n\n",gBest.fitness );
	return gBest.x;
}

SAPSO::SAPSO(int iteraciones,vector<double> & matrix,vector<double> & matrix2,std::vector<int> Cola,std::vector<int> & npe, std::vector<int> & Vmips){
	Mciudades=matrix;
	length=matrix2;
	vector<int> ciudad;
	this->Cola=Cola;
	cantidad_de_iteraciones=iteraciones;
	this->npe=npe;
	this->Vmips=Vmips;
	
	//cout<<"HOLa";
	ParticulaSAPSO P;
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
		ParticulaSAPSOs.push_back(P);
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
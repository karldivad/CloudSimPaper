#ifndef PSO_H
#define PSO_H

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
	Num fitness;
}Particula;

void mostrar_particula_x(Particula p){
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

void mostrar_particula_v(Particula p){
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

Particula Mejor(vector<Particula> Best){
	Particula X;
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

class PSO{
public:
	PSO(int iteraciones,vector<double> & matrix);
	//~PSO();
	void mostrar_particulas();
	vector<int> run();
	vector<int> ValorX();
	double Function(vector<int> & x);
	void llamadita();

	Particula gBest;
	Particula lBest;

	vector<Num> Mciudades;

	vector<Particula> particulas;
	vector<Particula> pBest;

	int cantidad_de_iteraciones=100;
	int tam_poblacion=200;
	//int dimensiones=2;
};

void PSO::llamadita(){
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

double PSO::Function(vector<int> & x){
	double sum=0;
	for (int i = 0; i < x.size()-1; ++i)
	{
		sum+=(Mciudades[x[i]]*(x.size()-i-1));
		//cout<<matrix[v[i-1]][v[i]]<<endl;
	}
	//cout<<endl;
	return sum/x.size();
}

vector<int> PSO::ValorX(){
	
	vector<int> ciudad;
	while(ciudad.size()!=Mciudades.size()){
		int aleatorio=random(Mciudades.size());
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

void PSO::mostrar_particulas(){
	for (int i = 0; i < tam_poblacion; ++i)
	{
		printf("Actual: [");
		mostrar_particula_x(particulas[i]);
		printf("]\n");
		printf("Costo Actual: %lf \n",particulas[i].fitness);
		
		printf("Actual: [");
		mostrar_particula_x(pBest[i]);
		printf("]\n");
		printf("Costo del Mejor: %lf \n",pBest[i].fitness);

		printf("Velocidad: [");
		mostrar_particula_v(particulas[i]);
		printf("]\n\n");
	}

}

vector<int> PSO::run(){
	Num w,d1,d2,rand1,rand2;
	
	for (int iteraciones = 0; iteraciones < cantidad_de_iteraciones; ++iteraciones)
	{
		/*printf("Iteracion %d *************\n", iteraciones+1);
		printf("Mejor Global: [");
		mostrar_particula_x(gBest);
		printf("]\n");
		printf("Costo del mejor Global: %lf \n\n",gBest.fitness );
		*/
		//mostrar_particulas();

		w=random(1);
		d1=1.49445;
		d2=1.49445;
		//rand1=random(1);
		//rand2=random(1);
		for (int i = 0; i < tam_poblacion; ++i)
		{
	
			particulas[i].v=(((pBest[i].x)-(particulas[i].x)))+((gBest.x - particulas[i].x));
			
			particulas[i].x=SS(particulas[i].x,particulas[i].v);
			particulas[i].fitness=Function(particulas[i].x);
			if (pBest[i].fitness>particulas[i].fitness)
			{
				pBest[i]=particulas[i];
			}
		}

		lBest=Mejor(particulas);
		if (lBest.fitness<gBest.fitness)
		{
			gBest=lBest;
		}
		//mostrar_particulas();
	}
		//printf("Mejor Global: [");
		//mostrar_particula_x(gBest);
		//printf("]\n");
		printf("Costo del mejor Global: %lf \n\n",gBest.fitness );
	return gBest.x;
}

PSO::PSO(int iteraciones,vector<Num> & matrix){
	Mciudades=matrix;
	vector<int> ciudad;
	
	//cout<<"HOLa";
	Particula P;
	for (int i = 0; i < tam_poblacion; ++i)
	{
		while(ciudad.size()!=Mciudades.size()){
			int aleatorio=(int)random(Mciudades.size());
			auto it=find (ciudad.begin(), ciudad.end(),aleatorio);
			if (it != ciudad.end()){
				;
			}
			else{
			    ciudad.push_back(aleatorio);//std::cout << "Element not found in myvector\n";			
			}
		}
		P.x=ciudad;
		P.fitness=Function(P.x);
		particulas.push_back(P);
		pBest.push_back(P);
		ciudad.clear();
		//P.x.clear();
	}
	gBest=Mejor(pBest);
	//mostrar_particula(gBest);
	lBest=Mejor(pBest);
	//mostrar_particula(lBest);
	//run();

}	


#endif	
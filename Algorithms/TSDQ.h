#ifndef TSDQ_H
#define TSDQ_H

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

//typedef int Num;

double prom(vector<int> v){
	double sum=0;
	for (int i = 0; i < v.size(); ++i)
	{
		sum+=v[i];
	}
	return sum/v.size();
}


class TSDQ{
public:
	TSDQ(int Num_machineV,vector<double> & ListTask, std::vector<int> &ListTaskWTOPSO);
	//~PSO();
	vector<double> ListTask;
	vector<int> ListTaskWTOPSO;
	int limite_maximo;

	vector<std::vector<int>> ColaSplit;

	std::vector<std::vector<int>> run();

	void mostrarColaSplit();

};

void TSDQ::mostrarColaSplit(){
	for (int i = 0; i < ColaSplit.size(); ++i)
	{
		for (int j = 0; j < ColaSplit[i].size(); ++j)
		{
			if (ColaSplit[i][j]==0)
			{
				printf("|T1|");
			}
			else if (ColaSplit[i][j]==1)
			{
				printf("|T2|");
			}
			else if (ColaSplit[i][j]==2)
			{
				printf("|T3|");
			}
			else if (ColaSplit[i][j]==3)
			{
				printf("|T4|");
			}
			else if (ColaSplit[i][j]==4)
			{
				printf("|T5|");
			}
			else if (ColaSplit[i][j]==5)
			{
				printf("|T6|");
			}
			else if (ColaSplit[i][j]==6)
			{
				printf("|T7|");
			}
			else if (ColaSplit[i][j]==7)
			{
				printf("|T8|");
			}
			else if (ColaSplit[i][j]==8)
			{
				printf("|T9|");
			}
			else if (ColaSplit[i][j]==9)
			{
				printf("|T10|");
			}
			else if (ColaSplit[i][j]==10)
			{
				printf("|T11|");
			}
			else if (ColaSplit[i][j]==11)
			{
				printf("|T12|");
			}
			else if (ColaSplit[i][j]==12)
			{
				printf("|T13|");
			}
			else if (ColaSplit[i][j]==13)
			{
				printf("|T14|");
			}
			else if (ColaSplit[i][j]==14)
			{
				printf("|T15|");
			}
			
		}
		printf("\n");
	}
}

std::vector<std::vector<int>> TSDQ::run(){
	std::vector<int> MiniCola;
	//MiniCola.push_back(ListTaskWTOPSO[0]);
	int counter=1;
	for (int i = 0; i < ListTask.size(); ++i)
	{
		//cout<<counter<<"  "<<limite_maximo<<endl;
		if (counter==limite_maximo)
		{
			MiniCola.push_back(ListTaskWTOPSO[i]);
		}
		else if (MiniCola.size()==0)
		{
			MiniCola.push_back(ListTaskWTOPSO[i]);
		}
		else if (MiniCola.size()==1)
		{
			int rand=random(2);
			//cout<<rand;
			if (rand==1)
			{
				MiniCola.push_back(ListTaskWTOPSO[i]);
			}else{
				ColaSplit.push_back(MiniCola);
				MiniCola.clear();
				counter++;
				MiniCola.push_back(ListTaskWTOPSO[i]);
			}
		}else{
			if (ListTask[ListTaskWTOPSO[i]]>prom(MiniCola))
			{
				ColaSplit.push_back(MiniCola);
				MiniCola.clear();
				counter++;
				MiniCola.push_back(ListTaskWTOPSO[i]);
			}
		}
	}
	ColaSplit.push_back(MiniCola);
	//cout<<ColaSplit.size()<<endl;
	MiniCola.clear();
	//mostrarColaSplit();
	return ColaSplit;
}

TSDQ::TSDQ(int Num_machineV,vector<double> & ListTask, std::vector<int> & ListTaskWTOPSO){
	this->limite_maximo=Num_machineV;
	this->ListTask=ListTask;
	this->ListTaskWTOPSO=ListTaskWTOPSO;
	//run();
	//mostrarColaSplit();
}	




#endif	
#include <iostream>
#include <stdlib.h>   //atoi
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <tuple>
#include <algorithm>
#include <iomanip>
#include "PSO.h"
#include "TSDQ.h"
#include "SAPSO.h"
#include "FLPSO.h"
#include "colonia.h"
#include "colonia2.h"
#include "colonia3.h"
#include <vector>
using namespace std;



int main(){
	srand(time(NULL));
	vector<Num> matrix={10,30,13,19,44,4,8,36,20,50};
	vector<Num> matrix2={800,100,3500,3000,2326,3300,4000,5000,6000,7000};
	std::vector<int> npe={2,2,2,2,2};
	std::vector<int> Vmips={500,500,500,500,500};
	std::vector<int> ListTaskColonia;
	std::vector<int> ListTaskColonia2;
	std::vector<int> ListTaskColonia3;
	std::vector<int> ListTaskWTOPSO;
	std::vector<std::vector<int>> ColaSplit;
	std::vector<std::vector<Num> > matrixc;
	std::vector<std::vector<Num> > matrixc2;

	for (int i = 0; i < matrix.size(); ++i)
	{
		matrixc.push_back(matrix);
	}
	
	//printf("HOLA\n");		
		PSO a(100,matrix);
		
		ListTaskWTOPSO = a.run();
		//a.llamadita();
	   	TSDQ tsdq(5,matrix,ListTaskWTOPSO);
	   	ColaSplit=tsdq.run();
		printf("SAPSO\n");	 
	   	for (int i = 0; i < ColaSplit.size(); ++i)
	   	{
	   		SAPSO p1(1000,matrix,matrix2,ColaSplit[i],npe,Vmips);	
	   	}
	   	printf("\nFLPSO\n");
	   	for (int i = 0; i < ColaSplit.size(); ++i)
	   	{
	   		FLPSO p2(1000,matrix,matrix2,ColaSplit[i],npe,Vmips);	
	   	}
	   	

	   	printf("\nColonia v1\n");
	   	
	   	Colonia p3(100,10,matrixc);
	   	ListTaskColonia=p3.run();
		TSDQ tsdq2(5,matrix,ListTaskColonia);
	   	ColaSplit=tsdq2.run();
		printf("SAPSO\n");	 
	   	for (int i = 0; i < ColaSplit.size(); ++i)
	   	{
	   		SAPSO p1(1000,matrix,matrix2,ColaSplit[i],npe,Vmips);	
	   	}
	   	printf("\nFLPSO\n");
	   	for (int i = 0; i < ColaSplit.size(); ++i)
	   	{
	   		FLPSO p2(1000,matrix,matrix2,ColaSplit[i],npe,Vmips);	
	   	}
	   	


	   		   	printf("\nColoniav2\n");
	   	Colonia2 p4(100,10,matrixc);	
	   	ListTaskColonia2=p4.run();
	  	TSDQ tsdq3(5,matrix,ListTaskColonia2);
	   	ColaSplit=tsdq3.run();
		printf("SAPSO\n");	 
	   	for (int i = 0; i < ColaSplit.size(); ++i)
	   	{
	   		SAPSO p1(1000,matrix,matrix2,ColaSplit[i],npe,Vmips);	
	   	}
	   	printf("\nFLPSO\n");
	   	for (int i = 0; i < ColaSplit.size(); ++i)
	   	{
	   		FLPSO p2(1000,matrix,matrix2,ColaSplit[i],npe,Vmips);	
	   	}
	   	
	   		   	printf("\nColoniav3\n");
	   	Colonia3 p5(100,10,matrixc);	
	   	ListTaskColonia3=p5.run();
	   	TSDQ tsdq4(5,matrix,ListTaskColonia3);
	   	ColaSplit=tsdq4.run();
		printf("SAPSO\n");	 
	   	for (int i = 0; i < ColaSplit.size(); ++i)
	   	{
	   		SAPSO p1(1000,matrix,matrix2,ColaSplit[i],npe,Vmips);	
	   	}
	   	printf("\nFLPSO\n");
	   	for (int i = 0; i < ColaSplit.size(); ++i)
	   	{
	   		FLPSO p2(1000,matrix,matrix2,ColaSplit[i],npe,Vmips);	
	   	}

	   	cout<<ColaSplit.size()<<endl;
	   //	 a.run();*/
	    return 0;
}
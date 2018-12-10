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



int main(int argc, char ** argv){
	srand(time(NULL));
	vector<Num> matrix;
	vector<Num> matrix2;
	std::vector<int> npe;
	std::vector<int> Vmips;
	//int iteraciones = stoi(argv[1]);
	Num iteraciones=stoi(argv[1]);
	Num iteraciones2=stoi(argv[2]);
	Num num_it=50;
	Num num_it2=50;

	std::clock_t start;
    double duration;
    double duration2;

    start = std::clock();

    /* Your algorithm here */

    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;


	for (int i = 0; i < iteraciones; ++i)
	{
		matrix.push_back((Num)random(iteraciones*10)+1);
		matrix2.push_back((Num)random(iteraciones*100)+1);

	}
	/*for (int i = 0; i < iteraciones; ++i)
	{
		cout<<matrix[i]<<" ";
	}
	cout<<endl;
	for (int i = 0; i < iteraciones; ++i)
	{
		cout<<matrix2[i]<<" ";
	}
	cout<<endl;*/
	for (int i = 0; i < iteraciones2; ++i)
	{
		npe.push_back((int)random(iteraciones2)+1);
		Vmips.push_back((int)random(iteraciones2*100)+1);

	}


	//vector<Num> matrix={10,30,13,19,44,4,8,36,20,50};
	//vector<Num> matrix2={800,100,3500,3000,2326,3300,4000,5000,6000,7000};
	//std::vector<int> npe={2,2,2,2,2};
	//std::vector<int> Vmips={500,500,500,500,500};
	std::vector<int> ListTaskColonia;
	std::vector<int> ListTaskColonia2;
	std::vector<int> ListTaskColonia3;
	std::vector<int> ListTaskWTOPSO;
	std::vector<std::vector<int>> ColaSplit;
	std::vector<std::vector<Num> > matrixc;
	std::vector<std::vector<Num> > matrixc2;

	Num suma2=0;
	Num suma1=0;


	for (int i = 0; i < matrix.size(); ++i)
	{
		matrixc.push_back(matrix);
	}
	
		printf("PSO\n");	
		start = std::clock();

		PSO a(num_it,matrix);
		tuple<vector<int>,Num> pso=a.run();
		duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

		ListTaskWTOPSO = get<0>(pso);
		printf("%f\n", get<1>(pso) );
		//a.llamadita();
	   	TSDQ tsdq(iteraciones2,matrix,ListTaskWTOPSO);
	   	ColaSplit=tsdq.run();
		printf("SAPSO\n");
		suma1=0;	

		start = std::clock();
	   	for (int i = 0; i < ColaSplit.size(); ++i)
	   	{
	   		SAPSO p1(num_it2,matrix,matrix2,ColaSplit[i],npe,Vmips);	
	   		suma1+=get<1>(p1.run());
	   	
	   	}
	   	duration2 = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
	   	printf("%f , %f\n",suma1,duration+duration2 );


	   	printf("\nFLPSO\n");
	   	suma2=0;
	   	start = std::clock();
	   	for (int i = 0; i < ColaSplit.size(); ++i)
	   	{
	   		FLPSO p2(num_it2,matrix,matrix2,ColaSplit[i],npe,Vmips);	
	   		suma2+=get<1>(p2.run());
	   	}
	   	duration2 = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
	   	printf("%f, %f\n",suma2,duration+duration2);




	   	printf("\nColonia v1\n");
	   	start = std::clock();
	   	Colonia p3(num_it,10,matrixc);
	   	tuple<vector<int>,Num> colonia=p3.run();
	   	duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
	   	ListTaskColonia=get<0>(colonia);
	   	printf("%f\n", get<1>(colonia) );
		TSDQ tsdq2(iteraciones2,matrix,ListTaskColonia);
	   	ColaSplit=tsdq2.run();

		printf("SAPSO\n");
		start = std::clock();

		suma1=0;	 
	   	for (int i = 0; i < ColaSplit.size(); ++i)
	   	{
	   		SAPSO p1(num_it2,matrix,matrix2,ColaSplit[i],npe,Vmips);	
	   		suma1+=get<1>(p1.run());
	   	}
   		duration2 = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
	   	printf("%f , %f\n",suma1,duration+duration2 );
	   	
	   	printf("\nFLPSO\n");
	   	
	   	suma2=0;
	   	start = std::clock();
	   	for (int i = 0; i < ColaSplit.size(); ++i)
	   	{
	   		FLPSO p2(num_it2,matrix,matrix2,ColaSplit[i],npe,Vmips);	
	   		suma2+=get<1>(p2.run());
	   	}
	   	duration2 = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
	   	printf("%f, %f\n",suma2,duration+duration2);  	


	   	printf("\nColoniav2\n");
	   	start = std::clock();
	   	Colonia2 p4(num_it,10,matrixc);	
	   	tuple<vector<int>,Num> colonia2=p4.run();
	   	duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
	   	ListTaskColonia2=get<0>(colonia2);
	   	printf("%f\n", get<1>(colonia2));
	  	TSDQ tsdq3(iteraciones2,matrix,ListTaskColonia2);
	   	ColaSplit=tsdq3.run();
		
		printf("SAPSO\n");
		suma1=0;	 	 
	   	start = std::clock();
	   	for (int i = 0; i < ColaSplit.size(); ++i)
	   	{
	   		SAPSO p1(num_it2,matrix,matrix2,ColaSplit[i],npe,Vmips);	
	   		suma1+=get<1>(p1.run());
	   	}
	   	duration2 = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
	   	printf("%f , %f\n",suma1,duration+duration2 );
	   	
	   	printf("\nFLPSO\n");
	   	suma2=0;	 
	   	start = std::clock();
	   	for (int i = 0; i < ColaSplit.size(); ++i)
	   	{
	   		FLPSO p2(num_it2,matrix,matrix2,ColaSplit[i],npe,Vmips);	
	   		suma2+=get<1>(p2.run());
	   	}
	   	duration2 = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
	   	printf("%f, %f\n",suma2,duration+duration2);
	   	
	   	
	   	printf("\nColoniav3\n");
	   	start = std::clock();
	   	Colonia3 p5(num_it,10,matrixc);	
	   	tuple<vector<int>,Num> colonia3=p5.run();
	   	duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
	   	ListTaskColonia3=get<0>(colonia3);
	   	printf("%f\n", get<1>(colonia3) );
	   	TSDQ tsdq4(iteraciones2,matrix,ListTaskColonia3);
	   	ColaSplit=tsdq4.run();
		
		printf("SAPSO\n");	 
		suma1=0;	 
	   	start = std::clock();
	   	for (int i = 0; i < ColaSplit.size(); ++i)
	   	{
	   		SAPSO p1(num_it2,matrix,matrix2,ColaSplit[i],npe,Vmips);	
	   		suma1+=get<1>(p1.run());
	   	}
	   	duration2 = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
	   	printf("%f , %f\n",suma1,duration+duration2 );
	   	
	   	printf("\nFLPSO\n");
	   	suma2=0;	 
	   	start = std::clock();
	   	for (int i = 0; i < ColaSplit.size(); ++i)
	   	{
	   		FLPSO p2(num_it2,matrix,matrix2,ColaSplit[i],npe,Vmips);	
	   		suma2+=get<1>(p2.run());
	   	}
	   	duration2 = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
	   	printf("%f, %f\n",suma2,duration+duration2);

	   	cout<<ColaSplit.size()<<endl;
	   //	 a.run();*/
	    return 0;
}
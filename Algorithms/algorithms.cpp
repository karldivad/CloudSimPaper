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
#include <vector>
using namespace std;



int main(){
	srand(time(NULL));
	vector<double> matrix={10,30,13,19,44,4,8,36,20,50};
	vector<double> matrix2={800,100,3500,3000,2326,3300,4000,5000,6000,7000};
	std::vector<int> npe={2,2,2,2,2};
	std::vector<int> Vmips={500,500,500,500,500};
	std::vector<int> ListTaskWTOPSO;
	std::vector<std::vector<int>> ColaSplit;
	//printf("HOLA\n");		
		PSO a(100,matrix);
		
		ListTaskWTOPSO = a.run();
		a.llamadita();
	   	TSDQ tsdq(5,matrix,ListTaskWTOPSO);
	   	ColaSplit=tsdq.run();
	   	
	   	for (int i = 0; i < ColaSplit.size(); ++i)
	   	{
	   		SAPSO p1(1000,matrix,matrix2,ColaSplit[i],npe,Vmips);	
	   	}

	   	for (int i = 0; i < ColaSplit.size(); ++i)
	   	{
	   		FLPSO p2(1000,matrix,matrix2,ColaSplit[i],npe,Vmips);	
	   	}
	   	cout<<ColaSplit.size()<<endl;
	   //	 a.run();
	    return 0;
}
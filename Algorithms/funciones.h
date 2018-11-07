#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <stdio.h>
#include <vector>
#include <ctime>
#include <tuple>
#include <algorithm>
#include <iomanip>
#include <fstream>

using namespace std;

typedef int Num;


bool iguales(vector<int>& a,std::vector<int > & b){
	for (int i = 0; i < a.size(); ++i)
	{
		if (a[i]!=b[i])
		{
			return false;
		}
	}
	return true;
}
void SO(vector<int> & ciudades, tuple<int,int> p){
	swap(ciudades[get<0>(p)],ciudades[get<1>(p)]);
}
vector<int> SS(vector<int> ciudades,vector<tuple<int,int>> p){
	std::vector<int> tmp=ciudades;
	for (int i = 0; i < p.size(); ++i)
	{
		SO(tmp,p[i]);
	}
	return tmp;
}
vector<tuple<int,int>> operator +(const vector<tuple<int,int>>& a, const vector<tuple<int,int>> &b){
	vector<tuple<int,int>> c;
	for (int i = 0; i < a.size(); ++i)
	{
		c.push_back(a[i]);
	}
	for (int i = 0; i < b.size(); ++i)
	{
		c.push_back(b[i]);
	}

	return c;

}
vector<tuple<int,int>> operator -(const vector<int> p1, const std::vector<int> p2){

	vector<tuple<int,int>> r;
	vector<int> tmp=p1;
	vector<int> tmp2=p2;
	while(iguales(tmp,tmp2)==false){
		for (int i = 0; i < tmp.size(); ++i)
		{
			auto it = find(tmp2.begin(), tmp2.end(),tmp[i]);
			if (it != tmp2.end()){
				if((it-tmp2.begin())!=i){
					auto tuple=make_tuple(i,it-tmp2.begin());
					r.push_back(tuple);
					SO(tmp,tuple);
					i=0;
				}
			}
			else{
			    ;//std::cout << "Element not found in myvector\n";			
			}
		}
	}
	//cout<<"HOLAA"<<endl;
	return r;
}




Num random(Num max){
	return static_cast <Num> (rand()) / (static_cast <Num> (RAND_MAX/max));
}


#endif	

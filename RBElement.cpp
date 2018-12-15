#ifndef _RBElement_
#define _RBElement_
#include<iostream>
#include <string>

using namespace std;

class RBElement{
	
	//struct
	public:
		string key;
		string cor;
		RBElement* pai;
		RBElement* esq;
		RBElement* dir;
		
		//construtor
		RBElement(){
			key ="NIL";
			pai = NULL;
			esq = NULL;
			dir = NULL;
			cor = "BLACK";
		}
		

};
#endif

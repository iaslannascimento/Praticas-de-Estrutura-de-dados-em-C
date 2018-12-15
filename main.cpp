//autor Iaslan Nascimento
//árvore rubro negra dicionario
#include "RBTree.cpp"
#include "RBElement.cpp"
#include<iostream>
#include<fstream>
#include <string>

using namespace std;

int main(int argc, char*argv[]){
	//leitura de arquivo
	ifstream arq;
	arq.open("dicionario1.txt");
	string info;
	int op;
	
	RBTree* T = new RBTree();
	RBElement* no;
	
	while(arq>>info){
		arq >> op;
		//verificando se a opção é 1 ou 0  para decidir se vamos 
		//inserir ou deletar
		//verificar se a opção é 1 e a palavra não existe 
		if((op ==1)&&(T->TreeSearch(T->root,info)->key =="NIL")){
			cout <<"->"+info+"\n";
			cout << "-----------Inserindo a palavra no dicionario --------\n\n";
			
			no = new RBElement();
			no->key = info;
			T->RBIsert(T,no);
		}else if((op == 1)&&(T->TreeSearch(T->root,info)->key!="NIL")){
			cout <<"->"+info+"\n";		
			cout<<"-----------Palavra ja existente no dicionario---------\n\n";
			
		}else if((op == 0)&&(T->TreeSearch(T->root,info)->key!="NIL")){
			RBElement* no = T->TreeSearch(T->root,info);
			cout <<"->"+info+"\n";
			cout <<"\n-----------Deletando a palavra do dicionario -------\n\n\n";
			T->RBDelete(T,no);
			T->RBPrint(T);
			T->RBCheck(no);
		}else{
				cout <<"->"+info+"\n";			
				cout<<"-----------palavra nao existe----------- \n\n";
				
		}
	}
	
	
	T->RBPrint(T);
	
	cout <<"\n \n \n \n";
	T->RBCheck(T->root);
	return 0;
	
}


#ifndef _RBTree_
#define _RBTree_
#include <iostream>
#include <string>
#include "RBElement.cpp"

using namespace std;

class RBTree{
	public :
		
		RBElement* root;
		
		RBTree(){
			this->root = new RBElement();
		}
		
		//inserção ---------------------------------
		void RBIsert(RBTree* T, RBElement *z){
			RBElement* y = new RBElement();
			RBElement* x = T->root;
			
			while(!(x->key=="NIL")){
				y=x;
				if((z->key.compare(x->key))<0){
					x =x->esq;
				}else{
					x=x->dir;
				}
			}
			z->pai =y;
			
			if(y->key=="NIL"){
				T->root = z;
			}else if(z->key.compare(y->key)<0){
				y->esq =z;
			}else{
				y->dir=z;
			}
			
			z->esq = new RBElement();
			z->dir =new RBElement();
			z->cor = "RED";
			//chamando RBinserFixup
			RBInsertFixup(T, z);
			
			
		}
		//Insert Fixup --------------------------------------------
		void RBInsertFixup(RBTree* T, RBElement* z){
			//enquanto o pai for vermelho
			while(z->pai->cor == "RED"){
				if(z->pai->key == (z->pai->pai->esq->key)){
					RBElement* y= z->pai->pai->dir;
					//caso 1
					if(y->cor=="RED"){
						z->pai->cor = "BLACK";
						y->cor = "BLACK";
						z->pai->pai->cor="RED";
						z = z->pai->pai;
					}else{
						if((z->key)==(z->pai->dir->key)){
							//caso 2
							z =z->pai;
							LeftRotate(T,z);
						}
						//caso 3
						z->pai->cor = "BLACK";
						z->pai->pai->cor = "RED";
						RightRotate(T, z->pai->pai);
					}
				}else{
					RBElement* y = z->pai->pai->esq;
					if(y->cor =="RED"){
						z->pai->cor = "BLACK";
						y->cor = "BLACK";
						z->pai->pai->cor = "RED";
						z = z->pai->pai;
					}else{
						if(z->key == (z->pai->esq->key)){
							z =z->pai;
							RightRotate(T,z);
						}
						z->pai->cor="BLACK";
						z->pai->pai->cor="RED";
						LeftRotate(T, z->pai->pai);
					}
				}
			}
			T->root->cor ="BLACK";
		}
		//Delecao ----------------------------------------------------
		void RBDelete(RBTree* T, RBElement* z){
			RBElement* y =z;
			string OriginalColor = y->cor;
			if(z->esq->key =="NIL"){
				RBElement* x = z->dir;
				RBTransplant(T,z,z->dir);
				if(OriginalColor=="BLACK"){
				}
			}else if(z->dir->key =="NIL"){
				RBElement* x=z->esq;
				RBTransplant(T,z,z->esq);
				if(OriginalColor =="BLACK"){
					RBDeleteFixup(T,x);
				}
			}else{
				y = TreeMinimun(z->dir);
				OriginalColor = y->cor;
				RBElement* x=y->dir;
				if(y->pai->key == z->key){
					x->pai=y;
				}else{
					RBTransplant(T,y,y->dir);
					y->dir = x->dir;
					y->dir->pai =y;
				}
				RBTransplant(T,z,y);
				y->esq = z->esq;
				y->esq->pai = y;
				y->cor =z->cor;
				if(OriginalColor =="BLACK"){
					RBDeleteFixup(T,x);
				}
			}
		}
		//delete fixup-------------------------------------------------
		void RBDeleteFixup(RBTree* T, RBElement* x){
			while((!(x->key==(T->root->key)))&&x->cor=="BLACK"){
				if(x->key ==(x->pai->esq->key)){
					RBElement* w =x->pai->dir;
					//caso 1
					if(w->cor=="RED"){
						w->cor=="BLACK";
						x->pai->cor="RED";
						LeftRotate(T,x->pai);
						w = x->pai->dir;
					}
					//caso2 
					if((w->esq->cor=="BLACK")&& w->dir->cor=="BLACK"){
						w->cor ="RED";
						x=x->pai;
					//caso 3	
					}else{//caso 3
						if(w->dir->cor =="BLACK"){
							w->esq->cor = "BLACK";
							w->cor="RED";
							RightRotate(T,w);
							w = x->pai->dir;
						}
						//caso 4
						w->cor = x->pai->cor;
						x->pai->cor = "BLACK";
						w->dir->cor="BLACK";
						LeftRotate(T,x->pai);
						x = T->root;
					}
				}else{
					RBElement* w =x->pai->esq;
					if(w->cor=="RED"){
						w->cor ="BLACK";
						x->pai->cor ="RED";
						RightRotate(T,x->pai);
						w=x->pai->esq;
					}
					if((w->esq->cor=="BLACK")&&(w->dir->cor=="BLACK")){
						w->cor = "RED";
						x =x->pai;
					}else{
						if(w->esq->cor=="BLACK"){
							w->dir->cor="BLACK";
							w->cor="RED";
							LeftRotate(T,w);
							w=x->pai->esq;
						}
						w->cor = x->pai->cor;
						x->pai->cor ="BLACK";
						w->esq->cor = "BLACK";
						RightRotate(T,x->pai);
						x=T->root;
						
					}
				}
			}
			x->cor ="BLACK";
		}
		//rotação a esquerda
		void LeftRotate(RBTree* T, RBElement* x){
			RBElement* y= x->dir;
			x->dir = y->esq;
			
			if(!(y->esq->key == "NIL")){
				y->esq->pai =x;
			}
			y->pai = x->pai;
			if(x->pai->key =="NIL"){
				T->root = y;
			}else if(x->key == (x->pai->esq->key)){
				x->pai->esq = y;
			}else{
				x->pai->dir =y;
			}
			
			y->esq =x;
			x->pai =y;
		}
		
		//rotação a direita
		void RightRotate(RBTree* T, RBElement* x){
			RBElement* y =x->esq;
			x->esq = y->dir;
			if(!(y->dir->key=="NIL")){
				y->dir->pai =x;
			}
			y->pai = x->pai;
			
			if(x->pai->key =="NIL"){
				T->root = y;
			}else if(x->key == (x->pai->dir->key)){
				x->pai->dir = y;
			}else{
				x->pai->esq = y;
			}
			
			y->dir =x;
			x->pai=y;
		}
		
		//transplant
		void RBTransplant(RBTree* T, RBElement* u, RBElement* v){
			if(u->pai->key=="NIL"){
				T->root = v;
			}else if(u->key == (u->pai->esq->key)){
				u->pai->esq =v;
			}else{
				u->pai->dir = v;
			}
			v->pai = u->pai;
		}
		
		//busca o menor valor da arvore
		RBElement* TreeMinimun(RBElement* x){
			while(!(x->esq->key == "NIL")){
				x=x->esq;
			}
			return x;
		}
		
		//busca o maior 
		RBElement* TreeMaximun(RBElement* x){
			while(!(x->dir->dir->key =="NIL")){
				x=x->dir;
			}
			return x;
		}
		//busca
		RBElement* TreeSearch(RBElement* x, string info){
		
			while((x->key!="NIL")&&(info!=x->key)){
				if(info.compare(x->key)<0){
					x = x->esq;
				}else{
					x = x->dir;
				}
			}
			return x;
		
		}
		//profundida negra da arvore
		
		int RBAlturaNegra(RBElement* x){
			if(x->key =="NIL"){
				return 1;
			}else if(x->esq->cor =="BLACK"){
				return RBAlturaNegra(x->esq)+1;
			}else{
				return RBAlturaNegra(x->esq);
			}
		}
		
		//RBCheck
		void RBCheck(RBElement* x){
			if(!(x->key == "NIL")){
				int altura = RBAlturaNegra(x)-1;
				cout << "(" <<x->pai->key << ","<<    x->key  << "," << x->cor << "," << altura << "," << x->esq->key << "," << x->dir->key + ")\n";           
	            RBCheck(x->esq);
	            RBCheck(x->dir);
			}
		}
		
		//RBPrint
		void RBPrint(RBTree* T){
        
			RBElement* x = T->root;
        	InOrderTree(x);
   
    	}

//Exibição em ordenação pela raiz
	void InOrderTree(RBElement* x){
        if(!(x->key =="NIL")) {
            InOrderTree(x->esq);
            cout << x->key + " ";
            InOrderTree(x->dir);
        }
        
    }

};
#endif

#include "BST.h"
#include <iostream>
#include <vector>
#include <math.h>
#include <list>
using std::vector;


template <typename T>
BST<T>::BST() {
  root = 0;
  balance.push_back(vector<int>());
  height = 0;
  width = 0;
}

template <typename T>
BST<T>::~BST() {
  
}


template <typename T>
bool BST<T>::find(T v) {
  Node<T>** curr = &root;
  while (*curr != 0 && (*curr)->getValue() != v) {
    if (v < (*curr)->getValue()) {
      curr = &((*curr)->getLeftChild());
    } else if (v > (*curr)->getValue()) {
      curr = &((*curr)->getRightChild());
    }
  }
  if (*curr !=0)
	  return true;
  else
	  return false;
}


template <typename T>
Node<T>* BST<T>::find(int h, int w) {
  Node<T>* curr = root;
  relativeParent = curr;
  double sizer = pow(2.0, h);
  for (int i = h; i>0; --i){
	  relativeParent = curr;
	  sizer = sizer/2;
	  if (w >= sizer)
		  curr = (curr)->getRightChild();
	  else
		  curr = (curr)->getLeftChild();
	  if (w-sizer >= 0)
		  w = w-sizer;
  }
  // cant return node**
  return curr;
}



template <typename T>
void BST<T>::insert(T v) {
  Node<T>* temp = new Node<T>(v);
  Node<T>* trace = new Node<T>(v);
  Node<T>** curr = &root;
  std::list< Node<T>* >pathway;
  pathway.push_back(*curr);
  int currH = 0;
  int currW = 0;
  int critH = 0;
  int critW = 0;
  bool foundImbalance = false;
  while (*curr != 0) {
    if (v < (*curr)->getValue()) {
		curr = &((*curr)->getLeftChild());
		pathway.push_back(*curr);
		currW = 2*currW;
		currH++;
    }
	else if (v > (*curr)->getValue()) {
		curr = &((*curr)->getRightChild());
		pathway.push_back(*curr);
		currW = (2*currW)+1;
		currH++;
    }
  }
  if (currH > height){
	  // if height of tree changes, balance from root to node should be checked
	  // not true -- if imbalance is found sooner, it will be repaired
	  balance.push_back(vector<int>());
	  double sizer = pow(2.0, currH);
	  for (int i = 0; i < sizer; i++)
		balance[currH].push_back(0);
	  height = currH;
	  balance[currH][currW] = 3;
  }
  if (currH == 0)
	  balance[currH].push_back(3);
  *curr = temp;
  //if odd, currW is an RC, even is LC
  //if odd, increase balance of parent by one
  // if even, decrease balance of parent by one
  // if parent is odd, increase bal of gparent by one, etc...
  //  parent is floor of currW/2
  critW = currW;
  pathway.pop_back();
  for (int i = currH-1; i >= 0; --i){
	if (critW%2 == 0){
		critW = critW/2;
		std::cout << pathway.back() << "LIST ADDRESS\n";
		trace = pathway.back();
		trace->minusBal();
		pathway.pop_back();
		std::cout << find(i,critW) << " VECTOR FIND\n";
		balance[i][critW]--;
	}
	else {
		critW = critW/2;
		std::cout << pathway.back() << "LIST ADDRESS\n";
		trace = pathway.back();
		trace->plusBal();
		pathway.pop_back();
		std::cout << find(i,critW) << " VECTOR FIND\n";
		balance[i][critW]++;
	}

	if (balance[i][critW] < 2 || balance[i][critW] > 4){
		std::cout << "you need to fix tree at height " << i << " and width " << critW << std::endl;
		std::cout << find(i,critW) << " VECTOR FIND\n";
		critH = i;
	}
	if (trace->getBal() < 2 || trace->getBal() > 4) {
		std::cout << trace << "LIST ADDRESS for fix\n";
		foundImbalance = true;
		break;
	}
}
if (foundImbalance) {
	Node<T>* critical = find(critH, critW);
	std::cout << "the value of critical is " << critical->getValue() <<std::endl;
	std::cout << "the value of trace is " << trace->getValue() <<std::endl;
	if (trace->getBal() < 2) {
		// right rotation

	}
	else {

		for (int i = currH-1; i >= critH; --i){
			if (currW%2 == 0){
				currW = currW/2;
				balance[i][currW]+=2;
			}
			else {
				currW = currW/2;
				balance[i][currW]-=2;
			}	
		}
		leftRot(trace);	
	}
}
}

template <typename T>
void BST<T>::leftRot(Node<T>* c) {
	Node<T>* tempRC = c->getRightChild();
	tempRC->minusBal();
	c->minusBal();
	c->minusBal();
	Node<T>* tempLC = tempRC->getLeftChild();
	tempRC->setLeftChild(*c);
	if (c == root)
		root = tempRC;
	else if (relativeParent->getLeftChild() == c)
		relativeParent->setLeftChild(*tempRC);
	else
		relativeParent->setRightChild(*tempRC);
	c->setRightChild(*tempLC);
}

template <typename T>
void BST<T>::remove(T v) {
  Node<T>** curr = &root;
  while (*curr != 0 && (*curr)->getValue() != v) {
    if (v < (*curr)->getValue()) {
      curr = &((*curr)->getLeftChild());
    } else if (v > (*curr)->getValue()) {
      curr = &((*curr)->getRightChild());
    }
  }
  if (*curr == 0)
	  std::cout << "Cannot remove, not found." << std::endl;
  else{
	  if ((*curr)->getLeftChild() == 0)
		  *curr = (*curr)->getRightChild();
	  else if ((*curr)->getRightChild() == 0)
		  *curr = (*curr)->getLeftChild();
	  else{
		  Node<T>** recall = curr;
		  curr = &((*curr)->getLeftChild());
		  while (*curr != 0)
			  curr = &((*curr)->getRightChild());
		  *curr = (*recall)->getRightChild();
		  *recall = (*recall)->getLeftChild();
	  }
  }
}

template <typename T>
void BST<T>::print() {
  traversalPrint(root);
}

template <typename T>
void BST<T>::postOrder() {
  postTraversal(root);
}

template <typename T>
void BST<T>::printTree() {
  vector<vector <Node<T>*> > PrintMe;
  PrintMe.push_back(vector<Node<T>*>());
  PrintMe[0].push_back(root);
  size_t countNulls = 0;
  int level = 0;
  while (countNulls != PrintMe[level].size()){
	  countNulls = 0;
	  PrintMe.push_back(vector<Node<T>*>());
	  double sizer = pow(2.0, level);
	  for (int i = 0; i < sizer; i++){
		  if (PrintMe[level][i] == 0){
			  PrintMe[level+1].push_back(0);
			  PrintMe[level+1].push_back(0);
			  countNulls = countNulls + 2;
		  }
		  else{
			  PrintMe[level+1].push_back(PrintMe[level][i]->getLeftChild());
			  PrintMe[level+1].push_back(PrintMe[level][i]->getRightChild());
		  }
	  }
	  level++;
	}
  double spaces;
	for (int k = 0; k < level; ++k){
		// max size divided by max number of gaps (max children+1) per level minus spacing of each value
		spaces = ((((level*12)-20) / ((pow (2.0, k))+1)) - 1); 
		for (int i = 0; i < spaces; ++i)
			std::cout << " ";
		for (size_t j = 0; j < PrintMe[k].size(); ++j){
			if (PrintMe[k][j] == 0)
				std::cout << " ";
			else if (j%2 != 0)
				std::cout << "\\";
			else
				std::cout << "/";
			for (int i = 0; i < spaces; ++i)
				std::cout << " ";
		}
		std::cout << std::endl;
		for (int i = 0; i < spaces; ++i)
			std::cout << " ";
		for (size_t j = 0; j<PrintMe[k].size(); ++j){
			if (PrintMe[k][j] == 0)
				std::cout << " ";
			else
				std::cout << PrintMe[k][j]->getValue();
			for (int i = 0; i < spaces; ++i)
			std::cout << " ";
		}
		std::cout << std::endl;
	}	
}

template <typename T>
void BST<T>::traversalPrint(Node<T>* root) {
  if(root != 0) {
    traversalPrint(root->getLeftChild());
    std::cout << root->getValue() << std::endl;
    traversalPrint(root->getRightChild());
  }
}

template <typename T>
void BST<T>::postTraversal(Node<T>* root) {
  if(root != 0) {
    postTraversal(root->getLeftChild());
    postTraversal(root->getRightChild());
	std::cout << root->getValue() << std::endl;
  }
}

template class BST<int>;
template class BST<double>;
template class BST<std::string>;

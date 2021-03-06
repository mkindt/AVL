#include "BST.h"
#include <iostream>
#include <vector>
#include <math.h>
#include <list>
using std::vector;


template <typename T>
BST<T>::BST() {
  root = 0;
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
  double sizer = pow(2.0, h);
  for (int i = h; i>0; --i){
	  sizer = sizer/2;
	  if (w >= sizer)
		  curr = (curr)->getRightChild();
	  else
		  curr = (curr)->getLeftChild();
	  if (w-sizer >= 0)
		  w = w-sizer;
  }
  return curr;
}

template <typename T>
void BST<T>::insert(T v) {
  Node<T>* temp = new Node<T>(v);
  Node<T>* trace = new Node<T>(v);
  Node<T>* relativeParent = new Node<T>(v);
  Node<T>** curr = &root;
  std::list< Node<T>* >pathway;
  pathway.push_back(*curr);
  int currH = 0;
  int currW = 0;
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
  *curr = temp;
  critW = currW;
  pathway.pop_back();
  for (int i = currH-1; i >= 0; --i){
	if (critW%2 == 0){
		critW = critW/2;
		if (trace->getLeftChild() != 0 && trace->getRightChild() != 0 && currH <= height){
			trace = pathway.back();
			pathway.pop_back();
		}
		else{
			trace = pathway.back();
			trace->minusBal();
			pathway.pop_back();
		}
	}
	else {
		critW = critW/2;
		if (trace->getLeftChild() != 0 && trace->getRightChild() != 0 && currH <= height){
			trace = pathway.back();
			pathway.pop_back();
		}
		else{
			trace = pathway.back();
			trace->plusBal();
			pathway.pop_back();
		}
	}

	if (trace->getBal() < 2 || trace->getBal() > 4) {
		if (trace != root)
			relativeParent = pathway.back();
		foundImbalance = true;
		break;
	}
  }
  if (foundImbalance) {
	if (trace->getBal() < 2){
		// left children have to exist for this balance
		if ((trace->getLeftChild())->getBal() == 4){
			leftRot(trace->getLeftChild(), trace);
			rightRot(trace, relativeParent);
		}
		else
			rightRot(trace, relativeParent);
	}
	else if(trace->getBal() > 4){
		if ((trace->getRightChild())->getBal() == 2){
			rightRot(trace->getRightChild(), trace);
			leftRot(trace, relativeParent);
		}
	else
		leftRot(trace, relativeParent);
	}
  }
  if (currH > height && !foundImbalance){
	height = currH;
  }
}

template <typename T>
void BST<T>::leftRot(Node<T>* c, Node<T>* p) {
	Node<T>* tempRC = c->getRightChild();
	tempRC->minusBal();
	c->minusBal();
	c->minusBal();
	Node<T>* tempLC = tempRC->getLeftChild();
	tempRC->setLeftChild(*c);
	if (c == root)
		root = tempRC;
	else if (p->getLeftChild() == c)
		p->setLeftChild(*tempRC);
	else
		p->setRightChild(*tempRC);
	c->setRightChild(*tempLC);
}

template <typename T>
void BST<T>::rightRot(Node<T>* c, Node<T>* p) {
	Node<T>* tempLC = c->getLeftChild();
	tempLC->plusBal();
	c->plusBal();
	c->plusBal();
	Node<T>* tempRC = tempLC->getRightChild();
	tempLC->setRightChild(*c);
	if (c == root)
		root = tempLC;
	else if (p->getRightChild() == c)
		p->setRightChild(*tempLC);
	else
		p->setLeftChild(*tempLC);
	c->setLeftChild(*tempRC);
}

template <typename T>
void BST<T>::remove(T v) {
  std::list< Node<T>* >pathway;
  std::list< int >LR;
  Node<T>* trace = new Node<T>(v);
  Node<T>* relativeParent = new Node<T>(v);
  Node<T>** curr = &root;
  pathway.push_back(*curr);
  LR.push_back(0);
  int currH = 0;
  int currW = 0;
  int critW = 0;
  bool foundImbalance = false;
  while (*curr != 0 && (*curr)->getValue() != v) {
    if (v < (*curr)->getValue()) {
      curr = &((*curr)->getLeftChild());
	  pathway.push_back(*curr);
	  LR.push_back(1);
	  currW = (2*currW);
	  currH++;
    } else if (v > (*curr)->getValue()) {
      curr = &((*curr)->getRightChild());
	  pathway.push_back(*curr);
	  LR.push_back(2);
	  currW = (2*currW)+1;
	  currH++;
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
		  pathway.push_back(*curr);
		  LR.push_back(1);
	      currW = (2*currW);
		  currH++;
		  while (*curr != 0){
			  curr = &((*curr)->getRightChild());
			  pathway.push_back(*curr);
			  LR.push_back(2);
			  currW = (2*currW)+1;
			  currH++;
		  }
		  *curr = (*recall)->getRightChild();
		  *recall = (*recall)->getLeftChild();
	  }
  }
  critW = currW;
  trace = pathway.back();
  pathway.pop_back();
  LR.pop_back();
  while (trace != root){
	if (LR.back() == 1){
		critW = critW/2;
		LR.pop_back();
		trace = pathway.back();
		if (trace->getLeftChild() != 0 && trace->getRightChild() != 0 && currH <= height){
			pathway.pop_back();
		}
		else{
			trace->minusBal();
			pathway.pop_back();
		}
	}
	else {
		LR.pop_back();
		trace = pathway.back();
		if (trace->getLeftChild() != 0 && trace->getRightChild() != 0 && currH <= height){
			pathway.pop_back();
		}
		else{
			trace->plusBal();
			pathway.pop_back();
		}
	}

	if (trace->getBal() < 2 || trace->getBal() > 4) {
		if (trace != root)
			relativeParent = pathway.back();
		foundImbalance = true;
		break;
	}
  }
  if (foundImbalance) {
	if (trace->getBal() < 2){
		// left children have to exist for this balance
		if ((trace->getLeftChild())->getBal() == 4){
			leftRot(trace->getLeftChild(), trace);
			rightRot(trace, relativeParent);
		}
		else
			rightRot(trace, relativeParent);
	}
	else if(trace->getBal() > 4){
		if ((trace->getRightChild())->getBal() == 2){
			rightRot(trace->getRightChild(), trace);
			leftRot(trace, relativeParent);
		}
	else
		leftRot(trace, relativeParent);
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

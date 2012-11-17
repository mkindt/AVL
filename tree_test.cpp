#include "BST.h"
#include <iostream>

int main() {
  BST<int>* bst = new BST<int>();

  bst->insert(10);
  bst->printTree();
  bst->insert(12);
  bst->printTree();
  bst->insert(14);
  bst->printTree();
  bst->insert(153);
 
  bst->printTree();

  bst->insert(154);
  bst->printTree();

  bst->insert(155);
  bst->printTree();
  
  bst->insert(4);
  bst->printTree();
  bst->insert(2);
  bst->printTree();
  bst->insert(3);
  bst->printTree();
  bst->insert(1);
  bst->printTree();
  bst->insert(15);
  bst->printTree();
  bst->remove(14);
  bst->printTree();

  BST<int>* bst2 = new BST<int>();
 
  bst2->insert(4);
  bst2->insert(7);
  bst2->insert(6);
  bst2->printTree();

 return 0;

}

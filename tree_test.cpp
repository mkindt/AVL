#include "BST.h"
#include <iostream>

int main() {
  BST<int>* bst = new BST<int>();

  bst->insert(10);
  bst->insert(12);
  bst->insert(14);
  bst->insert(153);
  
  bst->printTree();
  
  bst->insert(154);
  bst->printTree();
  
  bst->insert(155);
  
  bst->printTree();

  /* bst->insert(4);
  bst->insert(1);
  bst->insert(7);
  bst->insert(6);
  bst->insert(5);
  bst->insert(8);
  bst->insert(15);
  bst->insert(12);

  bst->printTree();
  bst->remove(12);
  bst->remove(20);
  bst->remove(7);
  bst->printTree();
  std::cout << bst->find(11) << std::endl;
  std::cout << bst->find(12) << std::endl;
  */

 return 0;

}

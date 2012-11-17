#ifndef __BST_H__
#define __BST_H__

#include "Node.h"
#include <string>
#include <vector>
#include <math.h>
using std::vector;


template <typename T>
class BST {
 private:
  Node<T>* root;
  void traversalPrint(Node<T>* root);
  void postTraversal(Node<T>* root);
  int height, width;

 public:
  BST<T>();
  ~BST<T>();
  bool find(T v);
  Node<T>* find(int h, int w);
  void remove(T v);
  void insert(T v);
  void print(); //inorder traversal
  void printTree();
  void leftRot(Node<T>* c, Node<T>* p);
  void rightRot(Node<T>* c, Node<T>* p);
  void postOrder();
};


#endif
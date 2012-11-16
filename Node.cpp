#include <string>
#include "Node.h"

template <typename T>
Node<T>::Node(T v) {
  value = v;
  leftChild = 0;
  rightChild = 0;
  bal = 3;
}

template <typename T>
T Node<T>::getValue() {
  return value;
}

template <typename T>
Node<T>*& Node<T>::getLeftChild() {
  return leftChild;
}

template <typename T>
void Node<T>::setLeftChild(Node<T>& lc) {
  leftChild = &lc;
}

template <typename T>
Node<T>*& Node<T>::getRightChild() {
  return rightChild;
}

template <typename T>
void Node<T>::setRightChild(Node<T>& rc) {
  rightChild = &rc;
}

template <typename T>
void Node<T>::plusBal() {
  bal++;
}

template <typename T>
void Node<T>::minusBal() {
  bal--;
}

template <typename T>
int Node<T>::getBal() {
  return bal;
}


template class Node<int>;
template class Node<double>;
template class Node<std::string>;


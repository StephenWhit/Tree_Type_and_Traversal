#ifndef TREETYPE_H
#define TREETYPE_H

#include <string>
#include <fstream>

template <class ItemType>
struct TreeNode;

#include "QueType.h"
#include "QueType.cpp"

enum OrderType {PRE_ORDER, IN_ORDER, POST_ORDER};
//#1 WORKS!
template <class ItemType>
class TreeType {
 public:
  TreeType();                     // constructor
  TreeType(const TreeType<ItemType>& originalTree);
  ~TreeType();                    // destructor

  void operator=(const TreeType<ItemType>& originalTree);
  // copy constructor

  void MakeEmpty();
  bool IsEmpty() const;
  bool IsFull() const;
  int GetLength() const; 
  ItemType GetItem(ItemType item, bool& found);
  void PutItem(ItemType item);
  void DeleteItem(ItemType item);
  void ResetTree(OrderType order); 
  ItemType GetNextItem(OrderType order, bool& finished);
  void Print(std::ofstream& outFile) const;

  //#2
  void LevelOrderPrint() const;

  //#3
  void PreOrderPrint(std::ofstream& outFile) const; 
  void InOrderPrint(std::ofstream& outFile) const;
  void PostOrderPrint(std::ofstream& outFile) const;

  //#5
  void Ancestors(std::ofstream& outFile, ItemType value);

 private:
  TreeNode<ItemType>* root;
  QueType<ItemType> preQue;
  QueType<ItemType> inQue;
  QueType<ItemType> postQue;

};

#endif

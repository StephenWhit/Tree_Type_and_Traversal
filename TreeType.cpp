#include<iostream>
#include<fstream>

using namespace std;

#include "TreeType.h"

template <class ItemType>
struct TreeNode {
  ItemType info;
  TreeNode<ItemType>* left;
  TreeNode<ItemType>* right;
};

template <class ItemType>
bool TreeType<ItemType>::IsFull() const
// Returns true if there is no room for another item 
//  on the free store; false otherwise.
{
  TreeNode<ItemType>* location;
  try
  {
    location = new TreeNode<ItemType>;
    delete location;
    return false;
  }
  catch(std::bad_alloc exception)
  {
    return true;
  }
}

template <class ItemType>
bool TreeType<ItemType>::IsEmpty() const
// Returns true if the tree is empty; false otherwise.
{
  return root == NULL;
}


inline int CountNodes(TreeNode<ItemType>* tree);

template <class ItemType>
int TreeType<ItemType>::GetLength() const
// Calls recursive function CountNodes to count the 
// nodes in the tree.
{
  return CountNodes(root);
}


inline int CountNodes(TreeNode<ItemType>* tree)
// Post: returns the number of nodes in the tree.
{
  if (tree == NULL)
    return 0;
  else 
    return CountNodes(tree->left) + CountNodes(tree->right) + 1;
}



inline void Retrieve(TreeNode<ItemType>* tree, ItemType& item, bool& found);

template <class ItemType>
ItemType TreeType<ItemType>::GetItem(ItemType item, bool& found)
// Calls recursive function Retrieve to search the tree for item.
{
  Retrieve(root, item, found);
  return item;
}


inline void Retrieve(TreeNode<ItemType>* tree, ItemType& item, bool& found)
// Recursively searches tree for item.
// Post: If there is an element someItem whose key matches item's,
//       found is true and item is set to a copy of someItem; 
//       otherwise found is false and item is unchanged.
{
  if (tree == NULL)
    found = false;                     // item is not found.
  else if (item < tree->info)      
    Retrieve(tree->left, item, found); // Search left subtree.
  else if (item > tree->info)
    Retrieve(tree->right, item, found);// Search right subtree.
  else
  {
    item = tree->info;                 // item is found.
    found = true;
   }
} 


inline void Insert(TreeNode<ItemType>*& tree, ItemType item);

template <class ItemType>
void TreeType<ItemType>::PutItem(ItemType item)
// Calls recursive function Insert to insert item into tree.
{
  Insert(root, item);
}


inline void Insert(TreeNode<ItemType>*& tree, ItemType item)
// Inserts item into tree.
// Post:  item is in tree; search property is maintained.
{
  if (tree == NULL)
  {// Insertion place found.
    tree = new TreeNode<ItemType>;
    tree->right = NULL;
    tree->left = NULL;
    tree->info = item;
  }
  else if (item < tree->info)
    Insert(tree->left, item);    // Insert in left subtree.
  else
    Insert(tree->right, item);   // Insert in right subtree.
}


inline void DeleteNode(TreeNode<ItemType>*& tree);
inline void Delete(TreeNode<ItemType>*& tree, ItemType item);

template <class ItemType>
void TreeType<ItemType>::DeleteItem(ItemType item)
// Calls recursive function Delete to delete item from tree.
{
  bool found = false;
  GetItem(item, found);
  if (found)
    Delete(root, item);
  else
    cout << item << "is not in tree\n";
}

inline void Delete(TreeNode<ItemType>*& tree, ItemType item)
// Deletes item from tree.
// Post:  item is not in tree.
{
  if (item < tree->info)
    Delete(tree->left, item);   // Look in left subtree.
  else if (item > tree->info)
    Delete(tree->right, item);  // Look in right subtree.
  else
    DeleteNode(tree);           // Node found; call DeleteNode.
}   

inline void GetPredecessor(TreeNode<ItemType>* tree, ItemType& data);

inline void DeleteNode(TreeNode<ItemType>*& tree)
// Deletes the node pointed to by tree.
// Post: The user's data in the node pointed to by tree is no 
//       longer in the tree.  If tree is a leaf node or has only 
//       non-NULL child pointer the node pointed to by tree is 
//       deleted; otherwise, the user's data is replaced by its 
//       logical predecessor and the predecessor's node is deleted.
{
  ItemType data;
  TreeNode<ItemType>* tempPtr;

  tempPtr = tree;
  if (tree->left == NULL)
  {
    tree = tree->right;
    delete tempPtr;
  }
  else if (tree->right == NULL)
  {
    tree = tree->left;
    delete tempPtr;
  }
  else
  {
    GetPredecessor(tree->left, data);
    tree->info = data;
    Delete(tree->left, data);  // Delete predecessor node.
  }
}

inline void GetPredecessor(TreeNode<ItemType>* tree, ItemType& data)
// Sets data to the info member of the right-most node in tree.
{
  while (tree->right != NULL)
    tree = tree->right;
  data = tree->info;
}

inline void PrintTree(ofstream& outFile, TreeNode<ItemType>* tree) 
// Prints info member of items in tree in sorted order on screen.
{
  if (tree != NULL)
  {
    PrintTree(outFile, tree->left);   // Print left subtree.
    outFile << tree->info<<"  ";
    PrintTree(outFile, tree->right);  // Print right subtree.
  }
}

template <class ItemType>
void TreeType<ItemType>::Print(ofstream& outFile) const
// Calls recursive function Print to print items in the tree.
{
  PrintTree(outFile, root);
}

template <class ItemType>
void TreeType<ItemType>::LevelOrderPrint() const {

}

template <class ItemType>
TreeType<ItemType>::TreeType()
{
  root = NULL;
}






inline void Destroy(TreeNode<ItemType>*& tree);

template <class ItemType>
TreeType<ItemType>::~TreeType()
// Calls recursive function Destroy to destroy the tree.
{
  Destroy(root);
}


inline void Destroy(TreeNode<ItemType>*& tree)
// Post: tree is empty; nodes have been deallocated.
{
  if (tree != NULL)
  {
    Destroy(tree->left);
    Destroy(tree->right);
    delete tree;
  }
}


template <class ItemType>
void TreeType<ItemType>::MakeEmpty()
{
  Destroy(root);
  root = NULL;
}


inline void CopyTree(TreeNode<ItemType>*& copy, const TreeNode<ItemType>* originalTree);

template <class ItemType>
TreeType<ItemType>::TreeType(const TreeType<ItemType>& originalTree)
// Calls recursive function CopyTree to copy originalTree 
//  into root.
{
  CopyTree(root, originalTree.root);
}

template <class ItemType>
void TreeType<ItemType>::operator= (const TreeType<ItemType>& originalTree)
// Calls recursive function CopyTree to copy originalTree 
// into root.
{
  {
    if (&originalTree == this)
      return;             // Ignore assigning self to self
    Destroy(root);      // Deallocate existing tree nodes
    CopyTree(root, originalTree.root);
  }
}

inline void CopyTree(TreeNode<ItemType>*& copy, const TreeNode<ItemType>* originalTree)
// Post: copy is the root of a tree that is a duplicate 
//       of originalTree.
{
  if (originalTree == NULL)
    copy = NULL;
  else
  {
    copy = new TreeNode<ItemType>;
    copy->info = originalTree->info;
    CopyTree(copy->left, originalTree->left);
    CopyTree(copy->right, originalTree->right);
  }
}
// Function prototypes for auxiliary functions.

inline void PreOrder(TreeNode<ItemType>*, QueType<ItemType>&);
// Enqueues tree items in preorder.


inline void InOrder(TreeNode<ItemType>*, QueType<ItemType>&);
// Enqueues tree items in inorder.


inline void PostOrder(TreeNode<ItemType>*, QueType<ItemType>&);
// Enqueues tree items in postorder.

template <class ItemType>
void TreeType<ItemType>::ResetTree(OrderType order)
// Calls function to create a queue of the tree elements in 
// the desired order.
{
  switch (order)
  { 
  case PRE_ORDER:    preQue.MakeEmpty();
                 PreOrder(root, preQue);
                     break;
  case IN_ORDER:     inQue.MakeEmpty();
           InOrder(root, inQue);
                     break;
  case POST_ORDER:  postQue.MakeEmpty();
          PostOrder(root, postQue);
                     break;
  }
}


inline void PreOrder(TreeNode<ItemType>* tree, QueType<ItemType>& preQue)
// Post: preQue contains the tree items in preorder.
{
  if (tree != NULL)
  {
    preQue.Enqueue(tree->info);
    PreOrder(tree->left, preQue);
    PreOrder(tree->right, preQue);
  }
}

inline void printPre(ofstream& outFile, TreeNode<ItemType>* tree);

template <class ItemType>
void TreeType<ItemType>::PreOrderPrint(ofstream& outFile) const {
  outFile << "Pre Order: ";
  printPre(outFile, root);
}

inline void printPre(ofstream& outFile, TreeNode<ItemType>* tree) {
  if (tree != NULL) {
    outFile << tree -> info << " ";
    printPre(outFile, tree->left);
    printPre(outFile, tree->right);
  }
}


inline void InOrder(TreeNode<ItemType>* tree, QueType<ItemType>& inQue)
// Post: inQue contains the tree items in inorder.
{
  if (tree != NULL)
  {
    InOrder(tree->left, inQue);
    inQue.Enqueue(tree->info);
    InOrder(tree->right, inQue);
  }
}

inline void printIn(ofstream& outFile, TreeNode<ItemType>* tree);

template <class ItemType>
void TreeType<ItemType>::InOrderPrint(ofstream& outFile) const {
  outFile << "In Order: ";
  printIn(outFile, root);
}

inline void printIn(ofstream& outFile, TreeNode<ItemType>* tree) {
  if (tree != NULL) {
    printIn(outFile, tree->left);
    outFile << tree -> info << " ";
    printIn(outFile, tree->right);
  }
}

inline void PostOrder(TreeNode<ItemType>* tree, QueType<ItemType>& postQue)
// Post: postQue contains the tree items in postorder.
{
  if (tree != NULL)
  {
    PostOrder(tree->left, postQue);
    PostOrder(tree->right, postQue);
    postQue.Enqueue(tree->info);
  }
}

inline void printPost(ofstream& outFile, TreeNode<ItemType>* tree);

template <class ItemType>
void TreeType<ItemType>::PostOrderPrint(ofstream& outFile) const {
  outFile << "Post Order: ";
  printPost(outFile, root);
}

inline void printPost(ofstream& outFile, TreeNode<ItemType>* tree) {
  if (tree!= NULL) {
    printPost(outFile, tree->left);
    printPost(outFile, tree->right);
    outFile << tree->info << " ";
  }
}



template <class ItemType>
ItemType TreeType<ItemType>::GetNextItem(OrderType order, bool& finished)
// Returns the next item in the desired order.
// Post: For the desired order, item is the next item in the queue.
//       If item is the last one in the queue, finished is true; 
//       otherwise finished is false.
{
  finished = false;
  ItemType item;
  switch (order)
  {
    case PRE_ORDER  : preQue.Dequeue(item);
                      if (preQue.IsEmpty())
                        finished = true;
                      break;
    case IN_ORDER   : inQue.Dequeue(item);
                      if (inQue.IsEmpty())
                        finished = true;
                      break;
    case  POST_ORDER: postQue.Dequeue(item);
                      if (postQue.IsEmpty())
                        finished = true;
                      break;
  }
  return item;
}

template <class ItemType>
void TreeType<ItemType>::Ancestors(ofstream& outFile, ItemType value) {
  TreeNode<ItemType>* temp;
  temp = root;
  bool found = false;
  outFile << "Ancestors of " << value << ": ";
  if (value != temp->info) {
    while (temp != NULL && !found) {
      if (value < temp->info) {
	outFile << temp->info << " ";
	temp = temp->left;
      }
      else if (value > temp->info) {
	outFile << temp->info << " ";
	temp = temp->right;
      }
      else if (value == temp->info) {
	temp = NULL;
	found = true;
      }
    }
  }
  outFile << endl;  
}

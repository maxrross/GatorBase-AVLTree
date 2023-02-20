#include <string>

#include <queue>

#include <iostream>

#include <iomanip>

using namespace std;

class TreeNode {
  public: string name;
  int ufid;
  TreeNode * left;
  TreeNode * right;
  TreeNode(string name, int ufid) {
    this -> name = name;
    this -> ufid = ufid;
    this -> left = nullptr;
    this -> right = nullptr;
  }
};

class AVLTree {
  private: TreeNode * root;
  public: TreeNode * getRoot();
  void setRoot(TreeNode * root);
  AVLTree();
  TreeNode * rotateLeft(TreeNode * root);
  TreeNode * rotateRight(TreeNode * root);
  TreeNode * rotateRightLeft(TreeNode * root);
  TreeNode * rotateLeftRight(TreeNode * root);
  TreeNode * insert(TreeNode * root, string name, int ufid);
  TreeNode * remove(TreeNode * root, int ufid);
  TreeNode * removeInorder(TreeNode * root, int n);
  TreeNode * search(TreeNode * root, int ufid);
  bool checkInorder(string n);
  bool checkName(string name);
  bool searchName(TreeNode * root, string name);
  int checkUFID(string ufid);
  int getHeight(TreeNode * root);
  int getBalance(TreeNode * root);
  void Postorder(TreeNode * root, vector < TreeNode * > & nodes);
  void Inorder(TreeNode * root, vector < TreeNode * > & nodes);
  void Preorder(TreeNode * root, vector < TreeNode * > & nodes);
  void printPostorder(TreeNode * root);
  void printPreorder(TreeNode * root);
  void printInorder(TreeNode * root);
  void printLevelCount(TreeNode * root);
};

//getters and setters of root pointer
TreeNode * AVLTree::getRoot() {
  return root;
}

void AVLTree::setRoot(TreeNode * root) {
  this -> root = root;
}

//creates an empty tree with root pointer as nullptr
AVLTree::AVLTree() {
  root = nullptr;
}

// rotation functions
TreeNode * AVLTree::rotateLeft(TreeNode * root) {
  TreeNode * newParent = root -> right;
  root -> right = newParent -> left;
  newParent -> left = root;
  return newParent;
}

TreeNode * AVLTree::rotateRight(TreeNode * root) {
  TreeNode * newParent = root -> left;
  root -> left = newParent -> right;
  newParent -> right = root;
  return newParent;
}

TreeNode * AVLTree::rotateRightLeft(TreeNode * root) {
  root -> right = rotateRight(root -> right);
  return rotateLeft(root);
}

TreeNode * AVLTree::rotateLeftRight(TreeNode * root) {
  root -> left = rotateLeft(root -> left);
  return rotateRight(root);
}

// insertion function
TreeNode * AVLTree::insert(TreeNode * root, string name, int ufid) {
  //if the tree is empty, create a new node
  if (root == nullptr) {
    cout << "successful" << endl;
    root = new TreeNode(name, ufid);
    //else if the ufid is less than the root's ufid, insert node to the left of root
  } else if (ufid < root -> ufid) {
    root -> left = insert(root -> left, name, ufid);
    //else if the ufid is greater than the root's ufid, insert node to the right of root
  } else if (ufid > root -> ufid) {
    root -> right = insert(root -> right, name, ufid);
    //return unsuccessful if the ufid is already in the tree
  } else {
    cout << "unsuccessful" << endl;
    return root;
  }
  //calculating balance of node
  int balance = getBalance(root);
  // if tree is left heavy
  if (balance > 1) {
    //if ufid is greater than left child's ufid, rotate left right and update height
    if (ufid > root -> left -> ufid) {
      return rotateLeftRight(root);
      // if ufid is less than left child's ufid, rotate right and update height
    } else if (ufid < root -> left -> ufid) {
      return rotateRight(root);
    }
  }
  //if tree is right heavy
  if (balance < -1) {
    //if ufid is less than right child's ufid, rotate right left and update height
    if (ufid < root -> right -> ufid) {
      return rotateRightLeft(root);
      //if ufid is greater than right child's ufid, rotate left and update height
    } else if (ufid > root -> right -> ufid) {
      return rotateLeft(root);
    }
  }
  return root;
}

//removal function
TreeNode * AVLTree::remove(TreeNode * root, int ufid) {
  //if tree is empty, return nullptr
  if (root == nullptr) {
    return nullptr;
  }
  //if ufid is greater than root's ufid, call remove function on the right of root with recursion
  if (ufid > root -> ufid)
    root -> right = remove(root -> right, ufid);
  //if ufid is less than root's ufid, call remove function on the left of root with recursion
  else if (ufid < root -> ufid)
    root -> left = remove(root -> left, ufid);
  //if ufid is not less than or greater than root's ufid, then the node has been found
  else {
    //if node has no children, delete node and set root to nullptr, then return the root
    if (root -> left == nullptr && root -> right == nullptr) {
      delete root;
      root = nullptr;
      return root;
    }
    //if the node has only a right child, delete node and set root to the right child, then return the root
    else if (root -> left == nullptr) {
      TreeNode * temp = root;
      root = root -> right;
      delete temp;
      return root;
    }
    //if the node has only a left child, delete node and set root to the left child, then return the root
    else if (root -> right == nullptr) {
      TreeNode * temp = root;
      root = root -> left;
      delete temp;
      return root;
    }
    //if the node has two children, find the root's inorder successor, set the root's ufid and name to the inorder successor's ufid and name, then call remove function on the right of root with recursion
    else {
      TreeNode * successor = root -> right;
      while (successor -> left != nullptr){
        successor = successor -> left;
      }
      root -> ufid = successor -> ufid;
      root -> name = successor -> name;
      root -> right = remove(root -> right, successor -> ufid);
    }
  }
  return root;
}

//removing inorder through inorder traversal
TreeNode * AVLTree::removeInorder(TreeNode * root, int n) {
  //if tree is empty, return nullptr
  if (root == nullptr) {
    cout << "unsuccessful" << endl;
    return nullptr;
  }
  //creating a vector of TreeNodes to store the nodes in inorder
  vector < TreeNode * > nodes;
  //calling inorder function to store the nodes in the vector
  Inorder(root, nodes);
  //if n is greater than the size of the vector, return unsuccessful
  if (n > nodes.size() - 1) {
    cout << "unsuccessful" << endl;
    return root;
    //if n is less than the size of the vector, therefore valid, call remove function on the node at index n
  } else {
    TreeNode * temp = remove(root, nodes[n] -> ufid);
    cout << "successful" << endl;
    return temp;
  }
}

//search function
TreeNode * AVLTree::search(TreeNode * root, int ufid) {
  //if tree is empty, return nullptr
  if (root == nullptr) {
    return nullptr;
    //if ufid is less than root's ufid, call search function on the left of root with recursion
  } else if (ufid < root -> ufid) {
    return search(root -> left, ufid);
    //if ufid is greater than root's ufid, call search function on the right of root with recursion
  } else if (ufid > root -> ufid) {
    return search(root -> right, ufid);
  } else {
    return root;
  }
}

//searching for all occurrences of the name in the tree
bool AVLTree::searchName(TreeNode * root, string name) {
  vector < TreeNode * > matches;
  vector < TreeNode * > nodes;
  Preorder(root, nodes);
  //searching for the name in the tree
  for (int i = 0; i < nodes.size(); i++) {
    //if name matches, push to corresponding vector
    if (nodes[i] -> name == name) {
      matches.push_back(nodes[i]);
      //if ID has less than 8 digits, print with leading zeros
      if (nodes[i] -> ufid < 10000000) {
        cout << setw(8) << setfill('0') << nodes[i] -> ufid << endl;
      } else {
        //if ID has 8 digits, print normally
        cout << nodes[i] -> ufid << endl;
      }
    }

  }
  //if vector is empty, print unsuccessful
  if (matches.empty()) {
    cout << "unsuccessful" << endl;
    return false;
  } else {
    return true;
  }
}

//checking if the string n is a number
bool AVLTree::checkInorder(string n) {
  bool flag = true;
  for (int i = 0; i < n.length(); i++) {
    if (isdigit(n.at(i)))
      continue;
    else {
      flag = false;
      break;
    }
  }
  return flag;
}

//checking if the string name is a name of only letters and spaces
bool AVLTree::checkName(string name) {
  bool flag = true;
  for (int i = 0; i < name.length(); i++) {
    if (isalpha(name[i]) || name[i] == ' ') {
      continue;
    } else {
      flag = false;
      break;
    }
  }
  return flag;
}

//checking if the string ufid is only numbers and is 8 digits long else return -1
int AVLTree::checkUFID(string ufid) {
  int flag = true;
  int ufidInt = 0;
  //checks if greater than 7 digits and less than 9 digits
  if (ufid.length() > 7 && ufid.length() < 9) {
    for (int i = 0; i < ufid.length(); i++) {
      //if element is a digit, flag is true
      if (isdigit(ufid[i])) {
        flag = true;
      } else {
        //if element is not a digit, flag is false
        flag = false;
      }
    }
    if (flag == true) {
      ufidInt = stoi(ufid);
      return ufidInt;
    } else {
      return -1;
    }
  } else {
    return -1;
  }

}

//getting the height of the node
int AVLTree::getHeight(TreeNode * root) {
  if (root == nullptr) {
    return 0;
  } else {
    int left = 0;
    int right = 0;
    left = getHeight(root -> left);
    right = getHeight(root -> right);
    return 1 + max(left, right);
  }
}

//getting the balance of the node
int AVLTree::getBalance(TreeNode * root) {
  //if root is nullptr, return 0
  if (root == nullptr) {
    cout << "unsuccessful" << endl;
    return 0;
    //else return balance of the node between the left and right subtree
  } else {
    return getHeight(root -> left) - getHeight(root -> right);
  }
}

//organizing the tree in preorder
void AVLTree::Preorder(TreeNode * root, vector < TreeNode * > & nodes) {
  if (root == nullptr) {
    return;
  }
  nodes.push_back(root);
  Preorder(root -> left, nodes);
  Preorder(root -> right, nodes);
}

//organizing the tree in postorder
void AVLTree::Postorder(TreeNode * root, vector < TreeNode * > & nodes) {
  if (root == nullptr) {
    return;
  }
  Postorder(root -> left, nodes);
  Postorder(root -> right, nodes);
  nodes.push_back(root);
}

//organizing the tree in inorder
void AVLTree::Inorder(TreeNode * root, vector < TreeNode * > & nodes) {
  if (root == nullptr) {
    return;
  }
  Inorder(root -> left, nodes);
  nodes.push_back(root);
  Inorder(root -> right, nodes);
}

//printing the tree in postorder
void AVLTree::printPostorder(TreeNode * root) {
  vector < TreeNode * > nodes;
  Postorder(root, nodes);
  for (int i = 0; i < nodes.size(); i++) {
    if (i != nodes.size() - 1)
      cout << nodes[i] -> name << ", ";
    else
      cout << nodes[i] -> name << endl;
  }
}

//printing the tree in preorder
void AVLTree::printPreorder(TreeNode * root) {
  vector < TreeNode * > nodes;
  Preorder(root, nodes);
  for (int i = 0; i < nodes.size(); i++) {
    if (i != nodes.size() - 1)
      cout << nodes[i] -> name << ", ";
    else
      cout << nodes[i] -> name << endl;
  }
}

//printing the tree in inorder
void AVLTree::printInorder(TreeNode * root) {
  vector < TreeNode * > nodes;
  Inorder(root, nodes);
  for (int i = 0; i < nodes.size(); i++) {
    if (i != nodes.size() - 1)
      cout << nodes[i] -> name << ", ";
    else
      cout << nodes[i] -> name << endl;
  }
}

//printing the level count of the tree
void AVLTree::printLevelCount(TreeNode * root) {
  cout << getHeight(root) << endl;
}
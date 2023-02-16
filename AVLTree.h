#include <string>

#include <queue>

#include <iostream>

using namespace std;

class TreeNode {
  public: string name;
  int ufid;
  int height;
  TreeNode * left;
  TreeNode * right;
  TreeNode(string name, int ufid) {
    this -> name = name;
    this -> ufid = ufid;
    this -> height = 0;
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
  TreeNode * updateHeight(TreeNode * root);
  TreeNode * insert(TreeNode * root, string name, int ufid);
  TreeNode * remove(TreeNode * root, int ufid);
  TreeNode * removeInorder(TreeNode * root, int n);
  TreeNode * search(TreeNode * root, int ufid);
  vector < string > searchName(TreeNode * root, string name, vector < string > & names);
  bool checkInorder(string n);
  bool checkName(string name);
  int checkUFID(string ufid);
  int getHeight(TreeNode * root);
  int getBalance(TreeNode * root);
  void printPreorder(TreeNode * root, vector < string > & names);
  void printPostorder(TreeNode * root, vector < string > & names);
  void printLevelCount(TreeNode * root);
  void printInorder(TreeNode * root, vector < string > & names);
  void Inorder(TreeNode * root, vector < TreeNode * > & nodes);
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

//rotation functions
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

//updating height of a node
TreeNode * AVLTree::updateHeight(TreeNode * root) {
    //if there's a left and right node, height is the max of the two
  if (root -> left != nullptr && root -> right != nullptr) {
    root -> height = max(getHeight(root -> left), getHeight(root -> right));
    //if there's only a left node, height is 1 + the height of the left node
  } else if (root -> left != nullptr) {
    root -> height = 1 + getHeight(root -> left);
    //if there's only a right node, height is 1 + the height of the right node
  } else if (root -> right != nullptr) {
    root -> height = 1 + getHeight(root -> right);
    //if there's no left or right node, height is 0
  } else {
    root -> height = 0;
  }
  return root;
}

//insertion function
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

  //updating height before balance calculation
  
  //if root has a left and right node, height is the max of the two + 1
  if (root -> left != nullptr && root -> right != nullptr) {
    root -> height = 1 + max(getHeight(root -> left), getHeight(root -> right));
    //if root has only a left node, height is 1 + the height of the left node
  } else if (root -> left != nullptr) {
    root -> height = 1 + getHeight(root -> left);
    //if root has only a right node, height is 1 + the height of the right node
  } else if (root -> right != nullptr) {
    root -> height = 1 + getHeight(root -> right);
    //if root has no left or right node, height is 0
  } else {
    root -> height = 0;
  }

 //calculating balance of node
  int balance = getBalance(root);


  //if tree is right heavy
  if (balance < -1) {
    //if right child is left heavy, rotate right left and update height
    if (getBalance(root -> right) > 1) {
      root = rotateRightLeft(root);
      root = updateHeight(root);
      return root;
    } else {
    //if right child is right heavy, rotate left and update height
      root = rotateLeft(root);
      root = updateHeight(root);
      return root;
    }
  }
  //if tree is left heavy
  if (balance > 1) {
    //if left child is right heavy, rotate left right and update height
    if (getBalance(root -> left) < -1) {
      root = rotateLeftRight(root);
      root = updateHeight(root);
      return root;
      //if left child is left heavy, rotate right and update height
    } else {
      root = rotateRight(root);
      root = updateHeight(root);
      return root;
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
    else
    {
      TreeNode * successor = root -> right;
      while (successor -> left != nullptr)
        successor = successor -> left;
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
vector < string > AVLTree::searchName(TreeNode * root, string name, vector < string > & names) {
    //if tree is empty, return the vector names
  if (root == nullptr) {
    return names;
  }
  //searching for the name in the left subtree
  searchName(root -> left, name, names);
  //if name is equal to root's name, push the root's ufid to the vector names
  if (root -> name == name) {
    names.push_back(to_string(root -> ufid));
  }
  //searching for the name in the right subtree
  searchName(root -> right, name, names);

  return names;
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
    return -1;
  } else {
    return root -> height;
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

//printing the tree in preorder
void AVLTree::printPreorder(TreeNode * root, vector < string > & names) {
  if (root == nullptr) {
    return;
  }
  names.push_back(root -> name);
  printPreorder(root -> left, names);
  printPreorder(root -> right, names);
}

//printing the tree in postorder
void AVLTree::printPostorder(TreeNode * root, vector < string > & names) {
  if (root == nullptr) {
    return;
  }
  printPostorder(root -> left, names);
  printPostorder(root -> right, names);
  names.push_back(root -> name);
}

//printing the level count of the tree
void AVLTree::printLevelCount(TreeNode * root) {
  cout << getHeight(root) << endl;
}

//printing the tree in inorder as a vector of strings
void AVLTree::printInorder(TreeNode * root, vector < string > & names) {
  if (root == nullptr) {
    return;
  }
  printInorder(root -> left, names);
  names.push_back(root -> name);
  printInorder(root -> right, names);
}

//inorder traversal that returns a vector of TreeNodes
void AVLTree::Inorder(TreeNode * root, vector < TreeNode * > & nodes) {
  if (root == nullptr)
    return;
  Inorder(root -> left, nodes);
  nodes.push_back(root);
  Inorder(root -> right, nodes);
}
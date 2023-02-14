#include <iostream>

#include <string>

#include <sstream>

#include <queue>

using namespace std;

/* Note: 
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope. 
*/

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
    this -> left = NULL;
    this -> right = NULL;
  }
};

TreeNode * rotateLeft(TreeNode * root) {
  TreeNode * newParent = root -> right;
  root -> right = newParent -> left;
  newParent -> left = root;
  return newParent;
}

TreeNode * rotateRight(TreeNode * root) {
  TreeNode * newParent = root -> left;
  root -> left = newParent -> right;
  newParent -> right = root;
  return newParent;
}

TreeNode * rotateRightLeft(TreeNode * root) {
  root -> right = rotateRight(root -> right);
  return rotateLeft(root);
}

TreeNode * rotateLeftRight(TreeNode * root) {
  root -> left = rotateLeft(root -> left);
  return rotateRight(root);
}

int getHeight(TreeNode * root) {
  if (root == NULL) {
	return -1;
  } else {
	return root -> height;
  }
}

int getBalance(TreeNode * root) {
  if (root == NULL) {
	cout << "Error: getBalance() called on NULL node." << endl;
    return 0;
  } else {
    return getHeight(root -> left) - getHeight(root -> right);
  }
}

TreeNode* updateHeight (TreeNode* root) {
	if (root->left != NULL && root->right != NULL) {
  		root -> height = max(getHeight(root -> left), getHeight(root -> right));
	} else if (root->left != NULL) {
		root -> height = 1 + getHeight(root -> left);
	} else if (root->right != NULL) {
		root -> height = 1 + getHeight(root -> right);
	} else {
		root -> height = 0;
	}
	return root;
}


TreeNode * insert(TreeNode * root, string name, int ufid) {
  if (root == NULL) {
	cout << "successful" << endl;
    root = new TreeNode(name, ufid);
    if (root == NULL) {
      cout << "Error: Memory allocation failed." << endl;
      return NULL;
    }
  } else if (ufid < root -> ufid) {
    root -> left = insert(root -> left, name, ufid);
    if (root -> left == NULL) {
      cout << "Error: Insertion failed for the left child." << endl;
      return root;
    }
  } else if (ufid > root -> ufid) {
    root -> right = insert(root -> right, name, ufid);
    if (root -> right == NULL) {
      cout << "Error: Insertion failed for the right child." << endl;
      return root;
    }
  } else {
    cout << "unsuccessful" << endl;
    return root;
  }

  //update height
	if (root->left != NULL && root->right != NULL) {
  		root -> height = 1 + max(getHeight(root -> left), getHeight(root -> right));
	} else if (root->left != NULL) {
		root -> height = 1+ getHeight(root -> left);
	} else if (root->right != NULL) {
		root -> height = 1+ getHeight(root -> right);
	} else {
		root -> height = 0;
	}
	// cout << "Height of " << root->name << " is " << root->height << endl;
  int balance = getBalance(root);

  //TESTING
//   cout << "Root is: "<< root->name <<" balance: " << balance << endl;
//   if (root->left != NULL) {
//   cout << "Left child is: "<< root->left->name <<" balance: " << getBalance(root->left) << endl;
//   }
//   if (root->right != NULL) {
//   cout << "Right child is: "<< root->right->name <<" balance: " << getBalance(root->right) << endl;
//   }

  //if tree is right heavy
  if (balance < -1) {
	// cout << "right heavy" << endl;
	//if right child is left heavy
	if (getBalance(root -> right) > 1) {
		// cout << "performing right left rotation" << endl << endl;
	    root = rotateRightLeft(root);
		root = updateHeight(root);
		return root;
	} else {
		// cout << "performing left rotation" <<endl << endl;
		root = rotateLeft(root);
		root = updateHeight(root);
		return root;
	}
  }
  //if tree is left heavy
  	if (balance > 1) {
		// cout << "left heavy" << endl;
		//if left child is right heavy
		if (getBalance(root -> left) < -1) {
			// cout << "performing left right rotation" <<endl  << endl;
			root = rotateLeftRight(root);
			root = updateHeight(root);
			return root;
		} else {
			// cout << "performing right rotation" <<endl  << endl;
			root = rotateRight(root);
			root = updateHeight(root);
			// cout << "Height of " << root->name << " is " << root->height << endl;
			return root;
		}
	}
  return root;
}

TreeNode* remove(TreeNode* root, int ufid)
    {
        if (root == nullptr)
        {
            return nullptr;
        }

        if (ufid > root->ufid)
            root->right = remove(root->right, ufid);
        else if (ufid < root->ufid)
            root->left = remove(root->left, ufid);
        else {
            //when there is no children
            if (root->left == nullptr && root->right == nullptr)
            {
                delete root;
                root = nullptr;
                return root;
            }
                //only has right children
            else if(root->left == nullptr)
            {
                TreeNode* temp = root;
                root = root->right;
                delete temp;
                return root;
            }
                //only has left children
            else if(root->right == nullptr)
            {
                TreeNode* temp = root;
                root = root->left;
                delete temp;
                return root;
            }
            else
                //have two children
                //copy the inorder successor's value to the root
                //remove the duplicate from right subtree
            {
                TreeNode* temp = root->right;
				while(temp->left != nullptr)
				temp = temp->left;
				root->ufid = temp->ufid;
				root->name = temp->name;
				root->right = remove(root->right, temp->ufid);
            }
        }
        return root;
    }

void printInorder(TreeNode * root, vector < string > & names) {
  if (root == NULL) {
    return;
  }
  printInorder(root -> left, names);
  names.push_back(root -> name);
  printInorder(root -> right, names);
}

void Inorder(TreeNode* root, vector<TreeNode*>& nodes)
{
	if (root == nullptr)
		return;
	Inorder(root->left, nodes);
	nodes.push_back(root);
	Inorder(root->right, nodes);
}

TreeNode* removeInorder(TreeNode* root, int n){
	if (root == nullptr)
	{
		cout << "unsuccessful" << endl;
		return nullptr;
	}
	vector<TreeNode*> nodes;
    Inorder(root, nodes);
    if( n > nodes.size()-1)
        {
            cout << "unsuccessful" << endl;
            return root;
        }
        else{
            TreeNode* temp = remove(root, nodes[n]->ufid);
            cout << "successful" << endl;
            return temp;
		}
}

void printPreorder(TreeNode * root, vector < string > & names) {
  if (root == NULL) {
    return;
  }
  names.push_back(root -> name);
  printPreorder(root -> left, names);
  printPreorder(root -> right, names);
}

void printPostorder(TreeNode * root, vector < string > & names) {
  if (root == NULL) {
    return;
  }
  printPostorder(root -> left, names);
  printPostorder(root -> right, names);
  names.push_back(root -> name);
}

void printLevelCount(TreeNode* root) {
	// cout << "root is: " << root->name << endl;
	// if (root->left != NULL) {
	// 	cout << "Left child is: "<< root->left->name << endl;
	// }
	// if (root->right != NULL) {
	// 	cout << "Right child is: "<< root->right->name << endl;
	// }
  cout << getHeight(root) << endl;
}

int checkUFID(string ufid) {
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

TreeNode * search(TreeNode * root, int ufid) {
  if (root == NULL) {
    return NULL;
  } else if (ufid < root -> ufid) {
    return search(root -> left, ufid);
  } else if (ufid > root -> ufid) {
    return search(root -> right, ufid);
  } else {
    return root;
  }
}

vector<string> searchName(TreeNode * root, string name, vector <string> & names) {
  if (root == NULL) {
	return names;
  }
  searchName(root -> left, name, names);
  if (root -> name == name) {
	names.push_back(to_string(root -> ufid));
  }
  searchName(root -> right, name, names);
  return names;
}

bool checkInorder (string n)
{
    bool flag = true;
    for(int i = 0; i < n.length(); i++)
    {
        if (isdigit(n.at(i)))
            flag = true;
        else
        {
            flag = false;
            break;
        }
    }
    return flag;
}

bool checkName(string name) {

  bool flag = true;
  for (int i = 0; i < name.length(); i++) {
    if (isalpha(name[i]) || name[i] == ' ') {
      continue;
    } else {
      flag = false;
    }
  }
  return flag;
}

int main() {
  string command = "";
  string name = "";
  string line = "";
  string ufid = "";
  string ufidOrName;
  int ufidInt = 0;
  int numcommands = 0;
  string n = "";
  int nInt = 0;
  TreeNode * root = NULL;
  vector < string > names;

  cin >> numcommands;

  // cout << "numcommands: " << numcommands << endl;
  for (int i = 0; i < numcommands; i++) {

    cin >> command;
    if (command == "insert") {
      string space = "";
      getline(cin, line);
      istringstream in (line);
      getline(in, space, '"');
      getline(in, name, '"');
      in >> ufid;

	  //the root is not changing

    //   cout << "name: " << name << endl;
    //   cout << "ufid: " << ufid << endl;

      if (checkName(name) && checkUFID(ufid) != -1) {
        ufidInt = checkUFID(ufid);
		if (search(root, ufidInt) != NULL) {
			cout << "unsuccessful" << endl;
		} else {
			root = (insert(root, name, ufidInt));
		}
      } else {
        cout << "unsuccessful" << endl;
      }
    } else if (command == "search") {
      cin >> ufidOrName;
      //finding out if UFID or Name
      if (checkUFID(ufidOrName) != -1) {
        //ufid is an int
        ufidInt = checkUFID(ufidOrName);
        if (search(root, ufidInt) != NULL) {
          cout << search(root, ufidInt) -> name << endl;
        } else {
          cout << "unsuccessful" << endl;
        }

      } else if (checkName(ufidOrName.substr(1, ufidOrName.length() - 2))) {
		names = searchName(root, ufidOrName.substr(1, ufidOrName.length() - 2), names);
        if (names.empty() == false) {
          for (int i = 0; i < names.size(); i++) {
			  cout << names[i] << endl;
		  }
        } else {
          cout << "unsuccessful" << endl;
        }
		names.clear();
      }
    } else if (command == "printInorder") {
      printInorder(root, names);
      for (int i = 0; i < names.size(); i++) {
        if (i == names.size() - 1) {
          cout << names[i] << endl;
        } else
          cout << names[i] << ", ";
      }
      names.clear();
    } else if (command == "printPreorder") {
      printPreorder(root, names);
      for (int i = 0; i < names.size(); i++) {
        if (i == names.size() - 1) {
          cout << names[i] << endl;
        } else
          cout << names[i] << ", ";
      }
      names.clear();
    } else if (command == "printPostorder") {
      printPostorder(root, names);
      for (int i = 0; i < names.size(); i++) {
        if (i == names.size() - 1) {
          cout << names[i] << endl;
        } else
          cout << names[i] << ", ";
      }
      names.clear();
    } else if (command == "printLevelCount") {
      printLevelCount(root);
    } else if (command == "remove") {
      cin >> ufid;
      if (checkUFID(ufid) != -1) {
        ufidInt = checkUFID(ufid);
		// cout << "removing: \"" << ufidInt << "\"" << endl;
		// cout << "root: " << root -> ufid << " name: " << root -> name << endl;
        root = remove(root, ufidInt);
		// cout << "root after call: " << root -> ufid << " name: " << root -> name << endl;
		cout << "successful" << endl;
      } else {
        cout << "unsuccessful" << endl;
      }
    } else if (command == "removeInorder") {
      cin >> n;
	  if (root != NULL){
		if(checkInorder(n))
			{
				nInt = stoi(n);
				// cout << "root: " << root -> ufid << " name: " << root -> name << endl;
				root = removeInorder(root, nInt);
				// cout << "root after call: " << root -> ufid << " name: " << root -> name << endl;
			}
			else
				cout << "unsuccessful" << endl;
	  } else {
		  cout << "unsuccessful" << endl;
		}
	}
    //resetting values
    ufidOrName = "";
    name = "";
    command = "";
    ufid = "";
	ufidInt = 0;
	n = "";
  }
}
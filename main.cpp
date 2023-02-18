#include <iostream>

#include <string>

#include <sstream>

#include <queue>

#include "AVLTree.h"

using namespace std;

int main() {
  //defining variables
  string command = "";
  string name = "";
  string line = "";
  string ufid = "";
  string ufidOrName;
  int ufidInt = 0;
  int numcommands = 0;
  string n = "";
  int nInt = 0;
  vector < string > names;
  AVLTree tree;

  //taking in number of commands
  cin >> numcommands;

  //for loop to take in commands
  for (int i = 0; i < numcommands; i++) {
    cin >> command;
    //insert function
    if (command == "insert") {
      //taking input for insert function, gets name and ufid
      string space = "";
      getline(cin, line);
      istringstream in (line);
      getline(in, space, '"');
      getline(in, name, '"');
      in >> ufid;

      //if name and ufid are valid, insert into tree
      if (tree.checkName(name) && tree.checkUFID(ufid) != -1) {
        ufidInt = tree.checkUFID(ufid);
        //if the ufid is already in the tree, print unsuccessful, else insert it into tree
        if (tree.search(tree.getRoot(), ufidInt) != NULL) {
          cout << "unsuccessful" << endl;
        } else {
          tree.setRoot((tree.insert(tree.getRoot(), name, ufidInt)));
        }
      } else {
        cout << "unsuccessful" << endl;
      }
      //search function
    } else if (command == "search") {
      cin >> ufidOrName;
      //finding out if UFID or Name
      if (tree.checkUFID(ufidOrName) != -1) {
        //ufid is an int
        ufidInt = tree.checkUFID(ufidOrName);
        //if ufid is found in tree, print name, else print unsuccessful
        if (tree.search(tree.getRoot(), ufidInt) != NULL) {
          cout << tree.search(tree.getRoot(), ufidInt) -> name << endl;
        } else {
          cout << "unsuccessful" << endl;
        }
        //if ufid is a name, search for the name in the tree and store results in vector names
      } else if (tree.checkName(ufidOrName.substr(1, ufidOrName.length() - 2))) {
        tree.searchName(tree.getRoot(), ufidOrName.substr(1, ufidOrName.length() - 2));
      }
      //if command is print inorder, preorder, or postorder, call the respective function and print the vector, then clear the vector
    } else if (command == "printInorder") {
      tree.printInorder(tree.getRoot());
    } else if (command == "printPreorder") {
      tree.printPreorder(tree.getRoot());
    } else if (command == "printPostorder") {
      tree.printPostorder(tree.getRoot());
      //printing the level count of the tree
    } else if (command == "printLevelCount") {
      tree.printLevelCount(tree.getRoot());
      //remove function
    } else if (command == "remove") {
      //taking in ufid
      cin >> ufid;
      //if the ufid exists in the tree, remove it, else print unsuccessful
      if (tree.checkUFID(ufid) != -1) {
        ufidInt = tree.checkUFID(ufid);
        if (tree.search(tree.getRoot(), ufidInt) == NULL) {
          cout << "unsuccessful" << endl;
        } else {
          //setting root to the new root after removing the node
          tree.setRoot(tree.remove(tree.getRoot(), ufidInt));
          cout << "successful" << endl;
        }
      } else {
        cout << "unsuccessful" << endl;
      }
    } else if (command == "removeInorder") {
      //taking in the element number to remove, n
      cin >> n;
      //if the tree has a root
      if (tree.getRoot() != NULL) {
        //if the element number is valid, remove the node, else print unsuccessful
        if (tree.checkInorder(n)) {
          nInt = stoi(n);
          tree.setRoot(tree.removeInorder(tree.getRoot(), nInt));
        } else
          cout << "unsuccessful" << endl;
      } else {
        cout << "unsuccessful" << endl;
      }
    } else {
      getline(cin, line);
      //if the command is not valid, print unsuccessful
      cout << "unsuccessful" << endl;
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
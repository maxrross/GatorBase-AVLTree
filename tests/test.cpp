#include "../main.cpp"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

/*
	To check output (At the Project1 directory):
		g++ -std=c++14 -Werror -Wuninitialized -o build/test test-unit/test.cpp && build/test
*/

TEST_CASE("BST Search Name", "[flag]"){
		AVLTree tree;
		vector<string> names;
		string name = "Joe";
		int ufid = 11111111;
		tree.setRoot((tree.insert(tree.getRoot(), name, ufid)));
		name = "Johnson";
		ufid = 22222222;
		tree.setRoot((tree.insert(tree.getRoot(), name, ufid)));
		name = "Jack";
		ufid = 33333333;
		tree.setRoot((tree.insert(tree.getRoot(), name, ufid)));

		TreeNode * node = tree.search(tree.getRoot(), 11111111);
		int actualOutput = node->ufid;
		int expectedOutput = 11111111;
		REQUIRE(expectedOutput == actualOutput);
	REQUIRE(1 == 1);
}

TEST_CASE("BST Search UFID", "[flag]"){
		AVLTree tree;
		vector<string> names;
		string name = "Joe";
		int ufid = 11111111;
		tree.setRoot((tree.insert(tree.getRoot(), name, ufid)));
		name = "Johnson";
		ufid = 22222222;
		tree.setRoot((tree.insert(tree.getRoot(), name, ufid)));
		name = "Jack";
		ufid = 33333333;
		tree.setRoot((tree.insert(tree.getRoot(), name, ufid)));
		TreeNode * node = tree.search(tree.getRoot(), 11111111);
		string actualOutput = node->name;
		string expectedOutput = "Joe";
		REQUIRE(expectedOutput == actualOutput);
	REQUIRE(1 == 1);
}

TEST_CASE ("BST Preorder" , "[flag]"){
		AVLTree tree;
		vector <TreeNode * > nodes;
		vector < string > names;
		string name = "Joe";
		int ufid = 11111111;
		tree.setRoot((tree.insert(tree.getRoot(), name, ufid)));
		name = "Johnson";
		ufid = 22222222;
		tree.setRoot((tree.insert(tree.getRoot(), name, ufid)));
		name = "Jack";
		ufid = 33333333;
		tree.setRoot((tree.insert(tree.getRoot(), name, ufid)));
		tree.Preorder(tree.getRoot(), nodes);
		for (int i = 0; i < nodes.size(); i++){
			names.push_back(nodes[i]->name);
		}
		vector<string> actualOutput = names;
		vector<string> expectedOutput = {"Johnson", "Joe", "Jack"};
		REQUIRE(expectedOutput.size() == actualOutput.size());
		REQUIRE(actualOutput == expectedOutput);
	REQUIRE(1 == 1);
}


TEST_CASE ("BST Height", "[flag]"){
		AVLTree tree; 
		vector<string> names;
		string name = "Joe";
		int ufid = 11111111;
		tree.setRoot((tree.insert(tree.getRoot(), name, ufid)));
		name = "Johnson";
		ufid = 22222222;
		tree.setRoot((tree.insert(tree.getRoot(), name, ufid)));
		name = "Jack";
		ufid = 33333333;
		tree.setRoot((tree.insert(tree.getRoot(), name, ufid)));
		int actualOutput = tree.getHeight(tree.getRoot());
		int expectedOutput = 2;
		REQUIRE(expectedOutput == actualOutput);
	REQUIRE(1 == 1);
}

TEST_CASE ("BST Inorder", "[flag]"){
		AVLTree tree;
		vector <TreeNode * > nodes;
		vector < string > names;
		string name = "Joe";
		int ufid = 11111111;
		tree.setRoot((tree.insert(tree.getRoot(), name, ufid)));
		name = "Johnson";
		ufid = 22222222;
		tree.setRoot((tree.insert(tree.getRoot(), name, ufid)));
		name = "Jack";
		ufid = 33333333;
		tree.setRoot((tree.insert(tree.getRoot(), name, ufid)));
		tree.Inorder(tree.getRoot(), nodes);
		for (int i = 0; i < nodes.size(); i++){
			names.push_back(nodes[i]->name);
		}
		vector<string> actualOutput = names;
		vector<string> expectedOutput = {"Joe", "Johnson", "Jack"};
		REQUIRE(expectedOutput.size() == actualOutput.size());
		REQUIRE(actualOutput == expectedOutput);
	REQUIRE(1 == 1);
}
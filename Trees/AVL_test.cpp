#include <iostream>
#include <queue>
#include <sstream>
#include <string>

#include "BinarySearchTrees.h"
#include "AVLTrees.h"

using namespace std;

// Assert Macros for test cases.
#define ASSERT_TRUE(T) \
    if (!(T))          \
        return false;
#define ASSERT_FALSE(T) \
    if ((T))            \
        return false;

string get_status_str(bool status) {
    return status ? "PASSED" : "FAILED";
}

// Function for getting the tree as a string
std::string breadthFirstTraversal(BinarySearchTree::Node* root) {

    // If no nodes, return an empty string.
    if (root == nullptr) {
        return "";
    }

    // Init a string buffer, and queue for traversal.
    stringstream ss;
    queue<BinarySearchTree::Node*> queue;

    // Seed the traversal.
    queue.push(root);

    // Walk through the tree, looking at each level inorder.
    bool first = true;
    while (!queue.empty()) {

        // Get the node.
        BinarySearchTree::Node* cur = queue.front();
        queue.pop();

        // Push this value into the string buffer.
        ss << (first ? "" : " ") << cur->val;
        first = false;

        // Add the left and right children if they exist.
        if (cur->left) {
            queue.push(cur->left);
        }
        if (cur->right) {
            queue.push(cur->right);
        }
    }

    string level_order_str = ss.str();
    return level_order_str;
}

class AVLTreeTest {
private:
    bool test_result[6] = {0,0,0,0,0,0};
    string test_description[6] = {
            "Test1: Test single left rotation",
            "Test2: Test single right rotation",
            "Test3: Test double left-right rotation",
            "Test4: Test double right-left rotation",
            "Test5: Test multiple rotations on insert",
            "Test6: Test multiple rotations on remove"
    };

public:
    string getTestDescription(int test_num);
    void runAllTests();
    void printReport();

    bool test1();
    bool test2();
    bool test3();
    bool test4();
    bool test5();
    bool test6();
};


//======================================================================
//================================ MAIN ================================
//======================================================================
int main() {

    // The test suite has some tests implemented for you,
    // and place holders for where you can put your own.
/*    BinarySearchTreeTest bst_test;

    // You can check the description for each test to see
    // what we will be testing for with the following method.
    // Alternatively, you can also navigate to the line above
    // where the test description is stored to read it.
    cout << bst_test.getTestDescription(1) << endl;

    // Tests can be run one at a time to get their result
    bool result = bst_test.test1();
    cout << "Test1: " << get_status_str(result) << endl;

    // Or you can run all of the tests at once and generate a report.
    bst_test.runAllTests();
    bst_test.printReport();*/

    // Uncomment and use this for lab 3.2 when it is released.
    AVLTreeTest avl_test;
    avl_test.runAllTests();
    avl_test.printReport();

    return 0;
}


string AVLTreeTest::getTestDescription(int test_num) {
    if (test_num < 1 || test_num > 6) { // check range.
        return "";
    }
    return test_description[test_num-1];
}

void AVLTreeTest::runAllTests() {
    test_result[0] = test1();
    test_result[1] = test2();
    test_result[2] = test3();
    test_result[3] = test4();
    test_result[4] = test5();
    test_result[5] = test6();
}

void AVLTreeTest::printReport() {
    cout << "  AVL TREE TEST RESULTS  \n"
         << " ^^^^^^^^^^^^^^^^^^^^^^^ \n";
    for (int idx = 0; idx < 6; ++idx) {
        cout << test_description[idx] << "\n  " << get_status_str(test_result[idx]) << endl << endl;
    }
    cout << endl;
}

// Test 1: Test single left rotation
bool AVLTreeTest::test1() {

    // Test set up.
    AVLTree avl;

    // Insert a some nodes into the tree in the following order.
    BinarySearchTree::DataType in[3] = {1, 2, 3};
    for (auto val : in) {
        ASSERT_TRUE(avl.insert(val))
    }

    // Check that a left rotation occurred.
    string expected_tree1 = "2 1 3";
    string tree_level_order1 = breadthFirstTraversal(avl.root_);
    ASSERT_TRUE(tree_level_order1.compare(expected_tree1) == 0)

    // Add additional nodes and check that another left rotation occurred.
    ASSERT_TRUE(avl.insert(7) && avl.insert(11))

    // Check the new tree representation.
    string expected_tree2 = "2 1 7 3 11";
    string tree_level_order2 = breadthFirstTraversal(avl.root_);
    ASSERT_TRUE(tree_level_order2.compare(expected_tree2) == 0)

    // Return true to signal all tests passed.
    return true;
}

// Test 2: Test single right rotation
bool AVLTreeTest::test2() {

    // Test set up.
    AVLTree avl;

    // Insert a some  nodes into the tree in the following order.
    BinarySearchTree::DataType in[3] = {7, 4, 1};
    for (auto val : in) {
        ASSERT_TRUE(avl.insert(val))
    }

    // Check that a right rotation occurred.
    string expected_tree1 = "4 1 7";
    string tree_level_order1 = breadthFirstTraversal(avl.root_);
    ASSERT_TRUE(tree_level_order1.compare(expected_tree1) == 0)

    // Add additional nodes and check that another right rotation occurred.
    ASSERT_TRUE(avl.insert(6) && avl.insert(5))

    // Check the new tree representation.
    string expected_tree2 = "4 1 6 5 7";
    string tree_level_order2 = breadthFirstTraversal(avl.root_);
    ASSERT_TRUE(tree_level_order2.compare(expected_tree2) == 0)

    // Return true to signal all tests passed.
    return true;
}

// Test 3: Test double left-right rotation
bool AVLTreeTest::test3() {

    // Test set up.
    AVLTree avl;

    // Insert a some  nodes into the tree in the following order.
    BinarySearchTree::DataType in[3] = {8, 1, 3};
    for (auto val : in) {
        ASSERT_TRUE(avl.insert(val))
    }

    // Check that a left-right rotation occurred.
    string expected_tree1 = "3 1 8";
    string tree_level_order1 = breadthFirstTraversal(avl.root_);
    ASSERT_TRUE(tree_level_order1.compare(expected_tree1) == 0)

    // Add additional nodes and check that another rotation occurred.
    ASSERT_TRUE(avl.insert(5) && avl.insert(6))

    // Check the new tree representation.
    string expected_tree2 = "3 1 6 5 8";
    string tree_level_order2 = breadthFirstTraversal(avl.root_);
    ASSERT_TRUE(tree_level_order2.compare(expected_tree2) == 0)

    // Return true to signal all tests passed.
    return true;
}

// Test 4: Test double right-left rotation
bool AVLTreeTest::test4() {

    // Test set up.
    AVLTree avl;

    // Insert a some  nodes into the tree in the following order.
    BinarySearchTree::DataType in[3] = {1, 7, 4};
    for (auto val : in) {
        ASSERT_TRUE(avl.insert(val))
    }

    // Check that a right-left rotation occurred.
    string expected_tree1 = "4 1 7";
    string tree_level_order1 = breadthFirstTraversal(avl.root_);
    ASSERT_TRUE(tree_level_order1.compare(expected_tree1) == 0)

    // Add additional nodes and check that another rotation occurred.
    ASSERT_TRUE(avl.insert(11) && avl.insert(9))

    // Check the new tree representation.
    string expected_tree2 = "4 1 9 7 11";
    string tree_level_order2 = breadthFirstTraversal(avl.root_);
    ASSERT_TRUE(tree_level_order2.compare(expected_tree2) == 0)

    // Return true to signal all tests passed.
    return true;
}

// Test 5: Test multiple rotations on insert
bool AVLTreeTest::test5() {

    // Test set up.
    AVLTree avl;

    // Insert a some  nodes into the tree in the following order.
    BinarySearchTree::DataType in[10] = {11, 15, 26, 87, 40, 82, 69, 21, 23, 42};
    for (auto val : in) {
        ASSERT_TRUE(avl.insert(val))
    }

    // Check the new tree representation.
    string expected_tree = "40 15 82 11 23 69 87 21 26 42";
    string tree_level_order = breadthFirstTraversal(avl.root_);
    ASSERT_TRUE(tree_level_order.compare(expected_tree) == 0)

    // Return true to signal all tests passed.
    return true;
}

// Test 6: Test multiple rotations on remove
bool AVLTreeTest::test6() {

    // Test set up.
    AVLTree avl;

    // Insert a some  nodes into the tree in the following order.
    BinarySearchTree::DataType in[10] = {11, 15, 26, 87, 40, 82, 69, 21, 23, 42};
    for (auto val : in) {
        ASSERT_TRUE(avl.insert(val))
    }
    string dis = breadthFirstTraversal(avl.root_);

    // Try removing some nodes to see how the balance changes.
    ASSERT_TRUE(avl.remove(87))

    ASSERT_TRUE(avl.remove(82))

    ASSERT_TRUE(avl.remove(69))

    // Check the resulting tree.
    string expected_tree1 = "23 15 40 11 21 26 42";
    string tree_level_order1 = breadthFirstTraversal(avl.root_);
    ASSERT_TRUE(tree_level_order1.compare(expected_tree1) == 0)

    // Remove additional nodes.
    ASSERT_TRUE(avl.remove(11))
    string dis2 = breadthFirstTraversal(avl.root_);
    ASSERT_TRUE(avl.remove(15))
    string dis3 = breadthFirstTraversal(avl.root_);
    ASSERT_TRUE(avl.remove(21))

    // Check the resulting tree.
    string expected_tree2 = "40 23 42 26";
    string tree_level_order2 = breadthFirstTraversal(avl.root_);
    ASSERT_TRUE(tree_level_order2.compare(expected_tree2) == 0)

    // Remove the ``right sub-tree`` and force a left-right rotation.
    ASSERT_TRUE(avl.remove(42))
    string expected_tree3 = "26 23 40";
    string tree_level_order3 = breadthFirstTraversal(avl.root_);
    ASSERT_TRUE(tree_level_order3.compare(expected_tree3) == 0)

    // Remove the remaining nodes in the tree, causing the root node to change each time.
    ASSERT_TRUE(avl.remove(26))
    string disp = breadthFirstTraversal(avl.root_);
    ASSERT_TRUE(avl.remove(23))
    string disp5 = breadthFirstTraversal(avl.root_);
    ASSERT_TRUE(avl.remove(40))

    // Check that the tree is now empty.
    string expected_tree4 = "";
    string tree_level_order4 = breadthFirstTraversal(avl.root_);
    ASSERT_TRUE(tree_level_order4.compare(expected_tree4) == 0)

    // Return true to signal all tests passed.
    return true;
}

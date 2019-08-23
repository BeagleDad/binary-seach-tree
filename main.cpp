#include <iostream>
#include <cstdlib>
#include <vector>
#include "BST.cpp"

using namespace std;

int main()
{
    std::vector<int> TreeKeys = {50, 76, 21, 4, 32, 64, 15, 52, 14, 100, 83, 2, 3, 70, 87, 80};

    BST myTree;

    cout << "Printing the tree in order, before adding any numbers" << endl;

    myTree.PrintInOrder();

    for (int key : TreeKeys)
    {
        myTree.AddLeaf(key);
    }
    cout << "\nPrinting the tree in order, after adding numbers" << endl;
    myTree.PrintInOrder();
    cout << endl;

    // for (int i = 0; i < 16; i++)
    // {
    //     myTree.PrintChildren(TreeKeys[i]);
    //     cout << endl;
    // }

    std::cout << "The smallest value in the tree is " << myTree.FindSmallest() << endl;

    myTree.PrintInOrder();
    cout << endl;

    std::cout << "Enter a key value to remove from tree. ";
    int input = 0;
    while (input != -1)
    {
        cout << "\ndelete Node: ";
        std::cin >> input;
        if (input != -1)
        {
            std::cout << std::endl;
            myTree.RemoveNode(input);
            myTree.PrintInOrder();
        }
    }
    return 0;
}
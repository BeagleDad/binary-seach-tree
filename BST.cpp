#include <iostream>
#include <cstdlib>
#include "BST.h"

BST::BST()
{
    root = nullptr;
}

BST::node *BST::CreateLeaf(int key)
{
    node *n = new node;
    n->key = key;
    n->left = nullptr;
    n->right = nullptr;

    return n;
}

void BST::AddLeaf(int key)
{
    // always start at the root
    AddLeafPrivate(key, root);
}

void BST::AddLeafPrivate(int key, node *Ptr)
{
    // special case for empty tree
    if (root == nullptr)
    {
        root = CreateLeaf(key);
    }
    else if (key < Ptr->key)
    {
        // key is less than current key, so go left, but need to see if there is a node or not
        if (Ptr->left != nullptr)
        {
            AddLeafPrivate(key, Ptr->left);
        }

        else
        {
            // left pointer empty
            Ptr->left = CreateLeaf(key);
        }
    }
    else if (key > Ptr->key)
    {
        // Key is greater than current key, go right, but need to see if there is a node or not
        if (Ptr->right != nullptr)
        {
            AddLeafPrivate(key, Ptr->right);
        }

        else
        {
            // right pointer empty
            Ptr->right = CreateLeaf(key);
        }
    }
    else
    {
        // Node keys are equal
        std::cout << "The key " << key << " already has been added to tree" << std::endl;
    }
}

void BST::PrintInOrder()
{
    PrintInOrderPrivate(root);
}

void BST::PrintInOrderPrivate(node *Ptr)
{
    if (root != nullptr)
    {
        // Step 1: Go left, if possible.
        if (Ptr->left != nullptr)
        {
            // Recursively go left to end
            PrintInOrderPrivate(Ptr->left);
        }
        // Step 2: Print this node's data if reached end of branch
        std::cout << Ptr->key << " ";
        // Step 1: Go left, if possible.
        if (Ptr->right != nullptr)
        {
            // Recursively go left to end
            PrintInOrderPrivate(Ptr->right);
        }
    }
    else
    {
        std::cout << "The tree is empty" << std::endl;
    }
}

BST::node *BST::ReturnNode(int key)
{
    return ReturnNodePrivate(key, root);
}

BST::node *BST::ReturnNodePrivate(int key, node *Ptr)
{
    if (Ptr != nullptr)
    {
        // see if found the node matching passed in key
        if (Ptr->key == key)
        {
            // If so return this node's pointer
            return Ptr;
        }
        else
        {
            if (key < Ptr->key)
            {
                return ReturnNodePrivate(key, Ptr->left);
            }
            else
            {
                return ReturnNodePrivate(key, Ptr->right);
            }
        }
    }
    else
    {
        return nullptr;
    }
}

int BST::ReturnRootKey()
{
    if (root != nullptr)
    {
        return root->key;
    }
    else
    {
        return -1000;
    }
}

void BST::PrintChildren(int key)
{
    node *Ptr = ReturnNode(key);

    if (Ptr != nullptr)
    {
        std::cout << "Parent node " << Ptr->key << std::endl;

        Ptr->left == nullptr ? std::cout << "Left Child = NULL\n" : std::cout << "Left Child = " << Ptr->left->key << std::endl;

        Ptr->right == nullptr ? std::cout << "Right Child = NULL\n" : std::cout << "Right Child = " << Ptr->right->key << std::endl;
    }
    else
    {
        std::cout << "The key " << key << " is not in the tree" << std::endl;
    }
}

int BST::FindSmallest()
{
    return FindSmallestPrivate(root);
}
int BST::FindSmallestPrivate(node *Ptr)
{
    if (root == nullptr)
    {
        std::cout << "Tree is empty\n";
        return -1000;
    }
    else
    {
        if (Ptr->left != nullptr)
        {
            return FindSmallestPrivate(Ptr->left);
        }
        else
        {
            return Ptr->key;
        }
    }
}

void BST::RemoveNode(int key)
{
    RemoveNodePrivate(key, root);
}
void BST::RemoveNodePrivate(int key, node *Parent)
{
    if (root != nullptr)
    {
        if (root->key == key)
        {
            RemoveRootMatch();
        }

        else if (key < Parent->key && Parent->left != nullptr)
        {
            Parent->left->key == key ? RemoveMatch(Parent, Parent->left, true) : RemoveNodePrivate(key, Parent->left);
        }
        else if (key > Parent->key && Parent->right != nullptr)
        {
            Parent->right->key == key ? RemoveMatch(Parent, Parent->right, false) : RemoveNodePrivate(key, Parent->right);
        }
        else
        {
            std::cout << "The key " << key << " was not found in the tree\n";
        }
    }
    else
    {
        std::cout << "the tree is empty\n";
    }
}

void BST::RemoveRootMatch()
{
    if (root != nullptr)
    {
        node *delPtr = root;
        int rootKey = root->key;
        int smallestKeyInRightSubtree;

        // Case 0 - root has no children
        if (root->left == nullptr && root->right == nullptr)
        {
            root = nullptr;
            delete delPtr;
        }
        // Case 1 - root has only one child: left or right
        else if (root->left == nullptr && root->right != nullptr)
        {
            root = root->right;
            delPtr->right = nullptr;
            delete delPtr;
            std::cout << "The root node with key " << rootKey << " was deleted. "
                      << "The new root contains key " << root->key << std::endl;
        }
        else if (root->left != nullptr && root->right == nullptr)
        {
            root = root->left;
            delPtr->left = nullptr;
            delete delPtr;
            std::cout << "The root node with key " << rootKey << " was deleted. "
                      << "The new root contains key " << root->key << std::endl;
        }
        // Case 2 - root has 2 children
        else
        {
            // find and save the smallest key in right subtree.
            smallestKeyInRightSubtree = FindSmallestPrivate(root->right);
            // Remove smallest
            RemoveNodePrivate(smallestKeyInRightSubtree, root);
            // keep node, but replace key with smallest
            root->key = smallestKeyInRightSubtree;
            std::cout << "The root key " << rootKey << " was overwritten with key " << root->key << std::endl;
        }
    }
    else
    {
        std::cout << "Cannot remove the root, the tree is empty" << std::endl;
    }
}

void BST::RemoveMatch(node *parent, node *match, bool left)
{
    if (root != nullptr)
    {
        node *delPtr;
        int matchKey = match->key;
        // Case 0 - match has no children
        if (match->left == nullptr && match->right == nullptr)
        {
            delPtr = match;
            left == true ? parent->left = nullptr : parent->right = nullptr;
            delete delPtr;
            std::cout << "The node containing key " << matchKey << " was removed." << std::endl;
        }
        // Case 1 - one child
        else if (match->left == nullptr && match->right != nullptr)
        {
            left == true ? parent->left = match->right : parent->right = match->right;
            match->right = nullptr;
            delPtr = match;
            delete delPtr;
            std::cout << "The node containing key " << matchKey << " was removed." << std::endl;
        }
        else if (match->left != nullptr && match->right == nullptr)
        {
            left == true ? parent->left = match->left : parent->right = match->left;
            match->left = nullptr;
            delPtr = match;
            delete delPtr;
            std::cout << "The node containing key " << matchKey << " was removed." << std::endl;
        }
        // Case 2 - match has two children
        else
        {
            int smallestKeyInRightSubtree = FindSmallestPrivate(match->right);
            RemoveNodePrivate(smallestKeyInRightSubtree, match);
            // Overrwrite key of matching node.
            match->key = smallestKeyInRightSubtree;
            std::cout << "The node containing key " << matchKey << " was removed." << std::endl;
        }
    }
    else
    {
        std::cout << "Can not remove match. Tree is empty.";
    }
}

BST::~BST()
{
    RemoveSubtree(root);
}

void BST::RemoveSubtree(node *Ptr)
{
    if (Ptr != nullptr)
    {
        if (Ptr->left != nullptr)
        {
            RemoveSubtree(Ptr->left);
        }
        if (Ptr->right != nullptr)
        {
            RemoveSubtree(Ptr->right);
        }
        std::cout << "Deleting the node containing key " << Ptr->key << std::endl;
        delete Ptr;
    }
}
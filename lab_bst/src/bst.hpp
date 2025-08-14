/**
 * @file bst.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include <algorithm>
using namespace std;


template <class K, class V>
V BST<K, V>::find(const K& key)
{
    // your code here
    if(find(root, key) == nullptr){
        return V();
    }else{
        return find(root, key) -> value;
    }
    

}

template <class K, class V>
struct BST<K, V>::Node* & BST<K, V>::find(Node* & subtree, const K& key)
{
    // Your code here
    if((subtree == nullptr) || ((subtree -> key) == key)){
        return subtree;
    }

    if((subtree -> key) < key){
        return find((subtree -> right), key);
    }
    return find((subtree -> left), key);

}

template <class K, class V>
void BST<K, V>::insert(const K & key, const V & value)
{
    // your code here
    insert(root, key, value);

}

template <class K, class V>
void BST<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here

    // return if already exist
    if(find(key) != V()){
        return;
    }

    Node* adding = new Node(key, value);
    Node*& leaf = find(subtree, key);
    leaf = adding;

}



template <class K, class V>
void BST<K, V>::swap(Node*& first, Node*& second)
{
    // your code here

    // swaping values
    K tempkey = first -> key;
    V tempvalue = first -> value;
    first -> key = second -> key;
    first -> value = second -> value;
    second -> key = tempkey;
    second -> value = tempvalue;
}

template <class K, class V>
struct BST<K, V>::Node* & BST<K, V>::IOP(Node* & subtree)
{

    if(subtree -> right == nullptr){
        return subtree;
    }

    return IOP(subtree -> right);    
}

template <class K, class V>
void BST<K, V>::remove(const K& key)
{
    // your code here
    Node*& temp = find(root, key);
    if((temp -> left == nullptr) && (temp -> right == nullptr)){
        delete temp;
        temp = nullptr;
        return;
    }
    if((temp -> left == nullptr) && (temp -> right != nullptr)){
        Node* holder = temp;
        temp = temp -> right;
        delete holder;
        return;
    }
    if((temp -> left != nullptr) && (temp -> right == nullptr)){
        Node* holder = temp;
        temp = temp -> left;
        delete holder;
        return;
    }
    if((temp -> left != nullptr) && (temp -> right != nullptr)){
        Node*& iop = IOP(temp -> left);
        if((iop -> left == nullptr) && (iop -> right == nullptr)){
            swap(temp, iop);
            delete iop;
            iop = nullptr;
            return;
        }else if((iop -> left != nullptr) && (iop -> right == nullptr)){
            swap(temp, iop);
            // temp -> left = temp -> left ->left;
            iop = iop -> left;
            return;
        }
    }
}

template <class K, class V>
void BST<K, V>::remove(Node*& subtree, const K& key)
{
    // your code here
    remove(key);
}

template <class K, class V>
BST<K, V> listBuild(std::vector<std::pair<K, V>> inList){
    // your code here
    BST<K, V> output;
    int size = inList.size();
    for(int i = 0; i < size; i++){
        output.insert(inList[i].first, inList[i].second);
    }
    return output;
}


template <class K, class V>
std::vector<int> allBuild(std::vector<std::pair<K, V>> inList){
    // your code here

    std::sort(inList.begin(), inList.end());

    vector<int> output(inList.size(), 0);
    do {
        BST<K, V> subtree= listBuild(inList); 
        int height = subtree.height(); 
        output[height] = output[height] + 1; 
    } while (std::next_permutation(inList.begin(), inList.end())); 

    return output;
}


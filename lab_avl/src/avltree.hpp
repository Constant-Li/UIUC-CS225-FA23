/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node* temp = t;
    t = t -> right;
    temp -> right = t -> left;
    t -> left = temp;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node* temp = t;
    t = t -> left;
    temp -> left = t -> right;
    t -> right = temp;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);

}





template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if(height(subtree) < 2){
        traverse(root);
    }

    int balance = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
    if(balance == -2){
        int leftbalance = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
        if(leftbalance == -1){
            rotateRight(subtree);
        }else{
            rotateLeftRight(subtree);
        }
    }else if(balance == 2){
        int rightbalance = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
        if(rightbalance == 1){
            rotateLeft(subtree);
        }else{
            rotateRightLeft(subtree);
        }
    }
    traverse(root);
}




template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}




template <class K, class V>
void AVLTree<K, V>::traverse(Node*& subtree)
{
    if(subtree == nullptr){
        return;
    }
    traverse(subtree -> left);
    subtree -> height = height(subtree);
    traverse(subtree -> right);
}




template <class K, class V>
int AVLTree<K, V>::height(Node* subroot){
  if(subroot == nullptr){
    return -1;
  }
  if(height(subroot->left) > height(subroot->right)){
    return 1 + height(subroot->left);
  }

  return 1 + height(subroot->right);
}



template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if(subtree == nullptr){
        subtree = new Node(key, value);
    }else if(key < subtree -> key){
        insert(subtree -> left, key, value);
    }else if(key > subtree -> key){
        insert(subtree -> right, key, value);
    }
    rebalance(subtree);
}









template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree -> left, key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree -> right, key);

    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = nullptr;
            return;

        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node* iop = subtree -> left;
            while(iop -> right != nullptr){
                iop = iop -> right;
            }
            swap(subtree, iop);
            remove(subtree->left, key);
            rebalance(subtree);
        } else if (subtree->left == NULL && subtree->right != NULL){
            Node* holder = subtree;
            subtree = subtree ->right;
            delete holder;
            rebalance(subtree);
            return;

        } else if (subtree->left != NULL && subtree->right == NULL){
            Node* holder = subtree;
            subtree = subtree ->left;
            delete holder;
            rebalance(subtree);
            return;
        }
        // your code here

    }
    rebalance(subtree);
}


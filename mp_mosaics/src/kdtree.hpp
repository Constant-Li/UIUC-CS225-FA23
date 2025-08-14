/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <deque>

using namespace std;

template <int Dim>
bool smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim)
{
    /**
     * @todo Implement this function!
     */
    if(first[curDim] < second[curDim]){
      return true;
    }else if(first[curDim] > second[curDim]){
      return false; 
    }else{
      return (first < second);
    }
}

template <int Dim>
bool shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential)
{
    /**
     * @todo Implement this function!
     */
    int curBest = 0;
    int potBest = 0;
    for(int i = 0; i < Dim; i++){
      curBest = curBest + (currentBest[i] - target[i]) * (currentBest[i] - target[i]);
      potBest = potBest + (potential[i] - target[i]) * (potential[i] - target[i]);
    }
    if(curBest < potBest){
      return false;
    }else if(curBest > potBest){
      return true;
    }else{
      return !(currentBest < potential);
    }
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    vector<Point<Dim>> temp = newPoints;
    root = buildkdtree(temp, 0, temp.size() - 1 , 0);

}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::buildkdtree(vector<Point<Dim>>& list, int left, int right, int dim){
  if(left < 0 || right < 0 || right < left){
    return nullptr;
  }
  int median = ((left + right) - (left + right) % 2) / 2;
  KDTreeNode* adding = new KDTreeNode(*(select(list.begin() + left, list.begin() + right + 1  , list.begin() + median, [dim] (Point<Dim> first, Point<Dim> second) {
                                                                                                                                                                      return smallerDimVal(first, second, dim);
                                                                                                                                                                    })));
  dim = dim + 1;
  size = size + 1;
  adding -> left = buildkdtree(list, left, median - 1, dim % Dim);
  adding -> right = buildkdtree(list, median + 1, right, dim % Dim);
  return adding;
} 


template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other){
  /**
   * @todo Implement this function!
   */
  copy(this -> root, other -> root);
  this -> size = other -> size;
}

template <int Dim>
void KDTree<Dim>::copy(KDTreeNode* current, KDTreeNode* other){
  if(other == nullptr){
    current = nullptr;
    return;
  }
  current = new KDTreeNode(other -> point);
  copy(current -> left, other -> left);
  copy(current -> right, other -> right);
}



template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  Delete(root);
  copy(this -> root, rhs -> root);

  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  Delete(root);
}

template <int Dim>
void KDTree<Dim>::Delete(KDTreeNode* node){
  if(node == nullptr){
    return;
  }
  Delete(node -> left);
  Delete(node -> right);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */

    vector<Point<Dim>> nodes;
    inorder(root, nodes);
    Point<Dim> curbest = nodes[0];
    for(int i = 1; i < (int)(nodes.size()); i++){
      if(shouldReplace(query, curbest, nodes[i])){
        curbest = nodes[i];
      }
    }
    return curbest;


}

template <int Dim>
void KDTree<Dim>::inorder(KDTreeNode* treenode, vector<Point<Dim>>& result) const{
  if(treenode == nullptr){
    return;
  }
  inorder(treenode->left, result);
  result.push_back(treenode -> point);
  inorder(treenode->right, result);
}





template <typename RandIter, typename Comparator>
RandIter select(RandIter start, RandIter end, RandIter k, Comparator cmp)
{
    /**
     * @todo Implement this function!
     */    
    if(start == end){
      return start;
    }
    RandIter pivotIndex = partition(start, end, k, cmp);
    if(k == pivotIndex){
      return k;
    }else if(cmp(*k, *pivotIndex)){
      return select(start, pivotIndex, k, cmp);
    }else{
      return select(pivotIndex, end, k, cmp);
    }

    
}

template <typename RandIter, typename Comparator>
RandIter partition(RandIter left, RandIter right, RandIter pivotIndex, Comparator cmp)
{

  auto pivotValue = *pivotIndex;
  iter_swap(pivotIndex, right - 1);
  RandIter storeindex = left;
  for(RandIter i = left; i != (right - 1); ++i){
    if(cmp(*i, pivotValue)){
      iter_swap(storeindex, i);
      storeindex = storeindex + 1;
    }
  }
  iter_swap(right - 1, storeindex);
  return storeindex;
}
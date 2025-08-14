
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */
#include <cstddef>

template <class T, class Compare>
class heap;

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    // @TODO Update to return the index you are choosing to be your root.
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the left child.
    return 2 * currentIdx;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the right child.
    return 2 * currentIdx + 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    // @TODO Update to return the index of the parent.
    size_t mod = currentIdx % 2;
    return (currentIdx - mod) / 2;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    // @TODO Update to return whether the given node has a child
    if(2 * currentIdx < _elems.size()){
        return true;
    }
    return false;
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
    T left = _elems[leftChild(currentIdx)];
    if(rightChild(currentIdx) >= _elems.size()){
        return leftChild(currentIdx);
    }
    T right = _elems[rightChild(currentIdx)];
    if(higherPriority(left, right)){
        return leftChild(currentIdx);
    }
    return rightChild(currentIdx);
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    // @TODO Implement the heapifyDown algorithm.
    if(hasAChild(currentIdx)){
        size_t minChildIndex = maxPriorityChild(currentIdx);
        if(higherPriority(_elems[minChildIndex], _elems[currentIdx])){
            std::swap(_elems[minChildIndex], _elems[currentIdx]);
            heapifyDown(minChildIndex);
        }
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    // @TODO Depending on your implementation, this function may or may
    ///   not need modifying
    _elems.push_back(T());
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems) 
{
    // @TODO Construct a heap using the buildHeap algorithm

    _elems.resize(elems.size() + 1);
    for (size_t i = 1; i < elems.size() + 1; i++) {
        _elems[i] = elems[i - 1];
    }
    // for(size_t j = 1; j < _elems.size(); j++){
    //     heapifyUp(j);
    // }
    for(size_t j = _elems.size(); j > 0; j--){
        heapifyDown(j - 1);
    }



}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    // @TODO Remove, and return, the element with highest priority
    T minValue = _elems[1];
    std::swap(_elems[1], _elems.back());
    _elems.pop_back();
    heapifyDown(1);
    return minValue;

}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    // @TODO Return, but do not remove, the element with highest priority
    return _elems[1];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    // @TODO Add elem to the heap
    _elems.push_back(elem);
    heapifyUp(_elems.size() - 1);
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
{
    // @TODO In-place updates the value stored in the heap array at idx
    // Corrects the heap to remain as a valid heap even after update
    T origin = _elems[idx];
    _elems[idx] = elem;
    if(higherPriority(origin, elem)){
        if(hasAChild(idx)){
            heapifyDown(idx);
        }
    }else{
        heapifyUp(idx);
    }
}


template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    // @TODO Determine if the heap is empty
    return _elems.size() <= 1;
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}

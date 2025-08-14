/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

# include<cmath>

template <class T>
List<T>::List() { 
  // @TODO: graded in mp_lists part 1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in mp_lists part 1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in mp_lists part 1
  return List<T>::ListIterator(tail_->next);
}

template <typename T>
typename List<T>::ListIterator List<T>::tail() const {
  // @TODO: graded in mp_lists part 1
  return List<T>::ListIterator(tail_);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in mp_lists part 1

  ListNode * temp;
  tail_ = nullptr;

  while(head_ != nullptr){
    head_ -> prev = nullptr;
    temp = head_->next;

    delete head_;
    head_ = temp;
  }
  length_ = 0;
    
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in mp_lists part 1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = head_;
  newNode -> prev = nullptr;

  // if list is not empty
  if (head_ != nullptr) {
    head_ -> prev = newNode;
    head_ = newNode;
  }
  // if list is empty
  if (tail_ == nullptr) {
    tail_ = newNode;
    head_ = newNode;
  }

  length_++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in mp_lists part 1

  ListNode * newNode = new ListNode(ndata);
  newNode -> next = nullptr;
  newNode -> prev = tail_;

  // if list is not empty
  if (tail_ != nullptr) { 
    tail_ -> next = newNode;
    tail_ = newNode;
  }
  // if list is empty
  if (head_ == nullptr) {
    tail_ = newNode;
    head_ = newNode;
  }

  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  // @todo Graded in mp_lists part 1
  ListNode * curr = start;

  // if split length exceed length_
  if(splitPoint >= length_){
    return nullptr;
  }
  if(splitPoint <= 0){
    return start; 
  }

  for (int i = 0; (i < splitPoint) && (curr != nullptr); i++) {
    curr = curr->next;
  }
  if (curr != nullptr) {
    // tail_ = curr -> prev;
    curr->prev->next = nullptr;
    curr->prev = nullptr;
    return curr;
  }
  return nullptr;
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
  // @todo Graded in part 1

  int count = 1;
  ListNode* temp = head_;
  // loop until tail or null
  while(temp != tail_ && temp != nullptr){
    ListNode *temp2 = temp->next;
    // determine if skip or not
    if(count % 2 == 0){
      // insert at back
      insertBack(temp->data);
      // delete the current
      (temp->prev)->next = temp->next;
      (temp->next)->prev = temp->prev;
      delete temp;
    }
    temp = temp2;
    count = count + 1;
  }

}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */

template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  // @todo Graded in mp_lists part 2
  ListNode* start = startPoint;
  ListNode* end = endPoint;
  // condition to keep reversing
  while(start != end && start != nullptr && end != nullptr){
    ListNode *temp;
    // if start is not head
    if(start != head_){
      start = start -> next;
      temp = start->prev;
      (temp->prev)->next = temp->next;
      (temp->next)->prev = temp->prev;
    // if start is head
    }else{
      start = start -> next;
      head_ = start;
      temp = start->prev;
      head_->prev = nullptr;
    }

    // if end is not tail
    if(end != tail_){
      temp->next = end->next;
      (end->next)->prev = temp;
      end->next = temp;
      temp->prev = end;
    // if end is tail       
    }else{
      temp->next = nullptr;
      tail_ -> next = temp;
      temp->prev = tail_;
      tail_ = temp;
      end = tail_->prev;
    }
  }
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  // @todo Graded in mp_lists part 2

  // numbers of reverse needs to be called
  int count = ceil((double)length_/n);
  if(count == 1){
    reverse();
  }else{
    ListNode* temp = head_;
    ListNode* temp2 = head_;
    for(int i = 0; i < count; i++){
      for(int j = 1; (j < n) && (temp2->next != nullptr); j++){
        temp2 = temp2->next;
      }
      reverse(temp, temp2);
      temp = temp->next;
      temp2 = temp;
    }
  }

}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  // @todo Graded in mp_lists part 2
  //head is a new list head
  ListNode* head;
  // updating the first element of head
  if(first->data < second->data){
    head = first;
    first = first->next;
  }else{
    head = second;
    second = second->next;
  }

  ListNode* cur = head;
  // updating all element of first&second
  while(first != nullptr && second != nullptr){
    if((first->data) < (second->data)){
        ListNode* temp = first;
        first = first->next;
        cur->next = temp;
        temp->prev = cur;
        cur = cur->next;
    }else{
        ListNode* temp2 = second;
        second = second->next;
        cur->next = temp2;
        temp2->prev = cur;
        cur = cur->next;    
    }
  }

  // concatenate residual list
  if(first != nullptr){
    cur->next = first;
    first->prev = cur;
  }else{
    cur->next = second;
    second->prev = cur;
  }

  return head;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  // @todo Graded in mp_lists part 2

  // base case
  if(chainLength == 1){
    return start;
  }

  // divid the list to two smaller one
  int length = chainLength / 2;
  ListNode* temp = split(start, length);
  return merge(mergesort(start, length), mergesort(temp, chainLength - length));
}

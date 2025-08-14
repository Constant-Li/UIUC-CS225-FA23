# include "List.h"

class ListIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
  private:
    // @TODO: graded in mp_lists part 1
    ListNode* position_;
    ListNode* before_;

  public:
    ListIterator() : position_(NULL), before_(NULL) { }
    ListIterator(ListNode* x){
        if(x == nullptr){
            position_ = nullptr;
            before_ = nullptr;
        }else{
            position_ = x;
            before_ = x->prev;
        }
     }


    // Pre-Increment, ++iter
    ListIterator& operator++() {
        // @TODO: graded in mp_lists part 1
        if(position_ == nullptr && before_ != nullptr){
            return *this;
        }
        if(position_ == nullptr && before_ == nullptr){
            return *this;
        }
        if(position_ != nullptr && before_ != nullptr){
            position_ = position_->next;
            before_ = before_->next;
            return *this;
        }
        if(position_ != nullptr && before_ == nullptr){
            before_ = position_;
            position_ = position_->next;
            return *this;
        }
        return *this;
    }
    
    // Post-Increment, iter++
    ListIterator operator++(int) {
        // @TODO: graded in mp_lists part 1
        ListNode* temp = position_;
        if(position_ == nullptr && before_ != nullptr){
            return ListIterator(temp);
        }
        if(position_ == nullptr && before_ == nullptr){
            return ListIterator(temp);
        }
        if(position_ != nullptr && before_ != nullptr){
            position_ = position_->next;
            before_ = before_->next;
            return ListIterator(temp);
        }
        if(position_ != nullptr && before_ == nullptr){
            before_ = position_;
            position_ = position_->next;
            return ListIterator(temp);
        }
        return ListIterator(temp);
    }

    // Pre-Decrement, --iter
    ListIterator& operator--() {
        // @TODO: graded in mp_lists part 1
        if(position_ == nullptr && before_ != nullptr){
            before_ = before_->prev;
            position_ = before_->next;
            return *this;
        }
        if(position_ == nullptr && before_ == nullptr){
            return *this;
        }
        if(position_ != nullptr && before_ != nullptr){
            position_ = position_->prev;
            before_ = before_->prev;
            return *this;
        }
        if(position_ != nullptr && before_ == nullptr){
            position_ = position_->prev;
            return *this;
        }
        return *this;

    }

    // Post-Decrement, iter--
    ListIterator operator--(int) {
        // @TODO: graded in mp_lists part 1
        ListNode* temp = position_;
        if(position_ == nullptr && before_ != nullptr){
            before_ = before_->prev;
            position_ = before_->next;
            return ListIterator(temp);
        }
        if(position_ == nullptr && before_ == nullptr){
            return ListIterator(temp);
        }
        if(position_ != nullptr && before_ != nullptr){
            position_ = position_->prev;
            before_ = before_->prev;
            return ListIterator(temp);
        }
        if(position_ != nullptr && before_ == nullptr){
            position_ = position_->prev;
            return ListIterator(temp);
        }
        return ListIterator(temp);


    }

    bool operator!=(const ListIterator& rhs) {
        // @TODO: graded in mp_lists part 1
        return (position_ != rhs.position_);
    }

    bool operator==(const ListIterator& rhs) {
        return !(*this != rhs);
    }

    const T& operator*() {
        return position_->data;
    }

    const T* operator->() {
        return &(position_->data);
    }
};
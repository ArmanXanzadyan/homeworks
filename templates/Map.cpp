#include "headers/Map.hpp"
#include <queue>
#include <stack>
#include <limits>
#include <iomanip>
#include <cassert>

template <typename Key1, typename Data1> std::ostream& operator<<(std::ostream& out, const std::pair<Key1, Data1> rhv)
{
    out << rhv.first << ":" << rhv.second;
    return out;
}

template <typename Key, typename Data>
std::ostream&
operator<<(std::ostream& out, const Map<Key, Data>& rhv) 
{
    rhv.outputTree(rhv.root_, out);
    return out;
}

template <typename Key, typename Data>
Map<Key, Data>::Map()
    : root_(NULL)
{}

template <typename Key, typename Data>
Map<Key, Data>::Map(const Map& rhv)
    : root_(NULL)
{
    insertMapHelper(rhv.root_);
}

template <typename Key, typename Data>
template <typename InputIt>
Map<Key, Data>::Map(InputIt first, InputIt last)
    : root_(NULL)
{
    insert(first, last);
}

template <typename Key, typename Data>
Map<Key, Data>::~Map()
{
    clear();
}

template <typename Key, typename Data>
const Map<Key, Data>&
Map<Key, Data>::operator=(const Map& rhv)
{
    if (this == &rhv) { return *this; }
    clear();
    insertMapHelper(rhv.root_);
    return *this;
}

template <typename Key, typename Data>
void 
Map<Key, Data>::insertMapHelper(Node* root)
{
    std::queue<Node*> que;
    que.push(root);
    iterator it; 
    while (!que.empty()) {
        Node* temp = que.front();
        it = (it ? insert(it, temp->value_) 
                 : insert(temp->value_).first);
        if (temp->left_)  { que.push(temp->left_);  }
        if (temp->right_) { que.push(temp->right_); }
        que.pop();
    }
}


template <typename Key, typename Data>
void 
Map<Key, Data>::swap(Map& rhv)
{
    std::swap(root_, rhv.root_);
}

template <typename Key, typename Data>
typename Map<Key, Data>::size_type 
Map<Key, Data>::size() const
{
    int counter = 0;
    const_iterator it = begin();
    while (it != end()) {
        ++it;
        ++counter;
    }
    return counter;
}

template <typename Key, typename Data>
typename Map<Key, Data>::size_type 
Map<Key, Data>::max_size() const
{
    return std::numeric_limits<size_t>::max() / sizeof(Node*); 
}

template <typename Key, typename Data>
bool 
Map<Key, Data>::empty() const
{
    return NULL == root_;
}

template <typename Key, typename Data>
void 
Map<Key, Data>::clear()
{
    clearHelper(root_);
}

template <typename Key, typename Data>
void
Map<Key, Data>::clearHelper(Node* root) 
{
    if (NULL == root) { return; }
    clearHelper(root->left_);
    clearHelper(root->right_);
    delete root;
    root = NULL;
}

template <typename Key, typename Data>
typename Map<Key, Data>::iterator 
Map<Key, Data>::begin()
{
    return iterator(getLeftMost(root_));
}

template <typename Key, typename Data>
typename Map<Key, Data>::iterator 
Map<Key, Data>::end()
{
    return iterator(NULL);
}

template <typename Key, typename Data>
typename Map<Key, Data>::const_iterator 
Map<Key, Data>::begin() const
{
    return iterator(getLeftMost(root_));
}

template <typename Key, typename Data>
typename Map<Key, Data>::const_iterator 
Map<Key, Data>::end() const
{
    return const_iterator(NULL);
}

template <typename Key, typename Data>
typename Map<Key, Data>::reverse_iterator 
Map<Key, Data>::rbegin()
{
    return reverse_iterator(getRightMost(root_));
}

template <typename Key, typename Data>
typename Map<Key, Data>::reverse_iterator 
Map<Key, Data>::rend()
{
    return reverse_iterator(NULL);
}

template <typename Key, typename Data>
typename Map<Key, Data>::const_reverse_iterator 
Map<Key, Data>::rbegin() const
{
    return const_reverse_iterator(getRightMost(root_));
}

template <typename Key, typename Data>
typename Map<Key, Data>::const_reverse_iterator 
Map<Key, Data>::rend() const
{
    return const_reverse_iterator(NULL);
}

template <typename Key, typename Data>
typename Map<Key, Data>::data_type& 
Map<Key, Data>::operator[](const key_type& x)
{
    return insert(std::make_pair(x, data_type())).first->second;
}

template <typename Key, typename Data>
std::pair<typename Map<Key, Data>::iterator, bool>
Map<Key, Data>::insert(const value_type& x)
{
    return insertHelper(iterator(root_), x);
}

template <typename Key, typename Data>
typename Map<Key, Data>::iterator
Map<Key, Data>::insert(iterator it, const value_type& x)
{
    return insertHelper(it, x).first;
}

template <typename Key, typename Data>
std::pair<typename Map<Key, Data>::iterator, bool>
Map<Key, Data>::insertHelper(iterator it, const value_type& x)
{
    if (empty()) { root_ = new Node(x.first, x.second); return std::make_pair(begin(), true); }
    goUp(it, x);
    const std::pair<iterator, bool> isAdded = goDownAndInsert(it, x);
    if (isAdded.second) { balance(isAdded.first); }
    return isAdded;
}

template <typename Key, typename Data>
void 
Map<Key, Data>::goUp(iterator& it, const value_type& x)
{
    if (!it.parent() || x.first == it->first) { return; }
    const const_iterator temp = (x.first < it->first) 
                              ? it.firstLeftParent()
                              : it.firstRightParent();
    if (isRoot(temp)) { return; }
    const bool isRightPlace = (x.first < it->first) 
                            ? (temp->first < x.first) 
                            : (temp->first > x.first);
    if (isRightPlace) { return; }
    it.ptr_ = temp.ptr_;
    goUp(it, x);
}

template <typename Key, typename Data>
std::pair<typename Map<Key, Data>::iterator, bool>
Map<Key, Data>::goDownAndInsert(iterator it, const value_type& x) 
{
    if (it && x.first < it->first) {
        if (!it.left()) { it.createLeft(x); return std::make_pair(it.left(), true); }
        return goDownAndInsert(it.goLeft(), x);
    }
    if (it && x.first > it->first) {
        if (!it.right()) { it.createRight(x); return std::make_pair(it.right(), true); }
        return goDownAndInsert(it.goRight(), x);
    }
    return std::make_pair(it, false);
}

template <typename Key, typename Data>
void 
Map<Key, Data>::balance(iterator it)
{
    if (!it) { return; }
    const int factor = it.balance();
    if (factor > 1) {
        iterator itLeft = it.left();
        if (itLeft.balance() < 0) { rotateRight(itLeft); }
        rotateLeft(it);
        return;
    } 
    if (factor < -1) {
        iterator itRight = it.right();
        if (itRight.balance() > 0) { rotateLeft(itRight); }
        rotateRight(it);
        return;
    }
    balance(it.goParent()); 
} 

template <typename Key, typename Data>
void 
Map<Key, Data>::rotateRight(iterator& it)
{
    iterator itParent = it.parent(), itRight = it.right();
    const bool isRightParent = it.isRightParent();
    it.setRight(itRight.left());
    if (itRight.left()) { itRight.left().setParent(it); }
    itRight.setLeft(it);
    it.setParent(itRight);
    itRight.setParent(itParent);
    if (itParent) {
        isRightParent ? itParent.setLeft(itRight)
                      : itParent.setRight(itRight);
    } else { root_ = itRight.getPtr(); }
    it = itRight;
}

template <typename Key, typename Data>
void 
Map<Key, Data>::rotateLeft(iterator& it)
{
    iterator itParent = it.parent(), itLeft = it.left();
    const bool isLeftParent = it.isLeftParent();
    it.setLeft(itLeft.right());
    if (itLeft.right()) { itLeft.right().setParent(it); }
    itLeft.setRight(it);
    it.setParent(itLeft);
    itLeft.setParent(itParent);
    if (itParent) {
        isLeftParent ? itParent.setRight(itLeft)
                     : itParent.setLeft(itLeft);
    } else { root_ = itLeft.getPtr(); }
    it = itLeft;
}

template <typename Key, typename Data>
template <typename InputIt>
void 
Map<Key, Data>::insert(InputIt first, InputIt last)
{
    while (first != last) { insert(*first); ++first; }
}

template <typename Key, typename Data>
void 
Map<Key, Data>::erase(iterator pos)
{
    assert(pos != end());
    Node* posNode = pos.getPtr();
    Node* replaceNode = getRightMost(posNode->left_);
    iterator posParent = pos.parent();
    if (NULL == replaceNode) {
        if (posParent) {
            pos.isRightParent() ? posNode->parent_->left_   = posNode->right_
                                : posNode->parent_->right_  = posNode->right_;
            if (posNode->right_) { posNode->right_->parent_ = posNode->parent_; } 
            delete posNode; 
            balance(posParent);
            return; 
        }
        Node* temp = root_; 
        root_ = root_->right_; 
        if (root_) { root_->parent_ = NULL; } 
        delete temp; 
        balance(posParent);
        return;
    }
    if (posParent) {
        pos.isRightParent() ? posNode->parent_->left_  = replaceNode
                            : posNode->parent_->right_ = replaceNode;
    }
    iterator(replaceNode).isRightParent() ? replaceNode->parent_->left_  = replaceNode->left_
                                          : replaceNode->parent_->right_ = replaceNode->left_;

    if (replaceNode->left_) { replaceNode->left_->parent_ = replaceNode->parent_; }
    replaceNode->parent_ = posNode->parent_;
    replaceNode->right_ = posNode->right_;
    if (posNode->right_) { posNode->right_->parent_ = replaceNode; }
    replaceNode->left_ = posNode->left_;
    if (posNode->left_)  { posNode->left_->parent_  = replaceNode; }
    if (posNode == root_) { root_ = replaceNode; }
    delete posNode;
    balance(posParent);
}

template <typename Key, typename Data>
typename Map<Key, Data>::size_type 
Map<Key, Data>::erase(const key_type& k)
{
    iterator temp = find(k);
    if (temp != end()) {
        erase(temp);
        return 1;
    }
    return 0;
}

template <typename Key, typename Data>
void 
Map<Key, Data>::erase(iterator first, iterator last)
{
    while (first != last) { 
        iterator temp = first;
        ++first; 
        erase(temp); 
    }
}

template <typename Key, typename Data>
typename Map<Key, Data>::iterator 
Map<Key, Data>::find(const key_type& key) const
{
    return findHelper(iterator(root_), key); 
}

template <typename Key, typename Data>
typename Map<Key, Data>::iterator 
Map<Key, Data>::findHelper(iterator root, const key_type& key) const
{
    if (!root || key == root->first) { return root; }
    if (key < root->first) { return findHelper(root.left(), key);  } 
    if (key > root->first) { return findHelper(root.right(), key); }
    assert(false);
    return root; 
}

template <typename Key, typename Data>
typename Map<Key, Data>::size_type 
Map<Key, Data>::count(const key_type& key) const
{
    return end() == find(key) ? 0 : 1;
}

template <typename Key, typename Data>
typename Map<Key, Data>::const_iterator 
Map<Key, Data>::lower_bound(const key_type& key) const
{
    return boundHelper(const_iterator(root_), key).first;
}

template <typename Key, typename Data>
typename Map<Key, Data>::const_iterator 
Map<Key, Data>::upper_bound(const key_type& key) const
{
    std::pair<iterator, bool> p = boundHelper(const_iterator(root_), key);
    return p.second ? ++p.first : p.first;
}

template <typename Key, typename Data>
typename Map<Key, Data>::iterator 
Map<Key, Data>::lower_bound(const key_type& key)
{
    return boundHelper(iterator(root_), key).first;
}

template <typename Key, typename Data>
typename Map<Key, Data>::iterator 
Map<Key, Data>::upper_bound(const key_type& key)
{
    std::pair<iterator, bool> p = boundHelper(iterator(root_), key);
    return p.second ? ++p.first : p.first;
}

template <typename Key, typename Data>
std::pair<typename Map<Key, Data>::const_iterator, typename Map<Key, Data>::const_iterator> 
Map<Key, Data>::equal_range(const key_type& k) const
{
    return std::make_pair(lower_bound(k), upper_bound(k));
}

template <typename Key, typename Data>
std::pair<typename Map<Key, Data>::iterator, typename Map<Key, Data>::iterator> 
Map<Key, Data>::equal_range(const key_type& k)
{
    return std::make_pair(lower_bound(k), upper_bound(k));
}

template <typename Key, typename Data>
std::pair<typename Map<Key, Data>::iterator, bool>
Map<Key, Data>::boundHelper(iterator root, const key_type& key) const
{
    if (!root) { return std::make_pair(root, false); }
    if (root->first == key) { return std::make_pair(root, true); }
    if (key < root->first) { 
        if (root.left()) { return boundHelper(root.left(), key); }
        return std::make_pair(root, false);
    } 
    if (key > root->first) { 
        if (root.right()) { return boundHelper(root.right(), key); }
        return std::make_pair(++root, false);
    }
    assert(false);
    return std::make_pair(root, false);
}

template <typename Key, typename Data>
bool 
Map<Key, Data>::isRoot(const const_iterator& temp) const
{
    return temp == const_iterator(root_);
}
    
template <typename Key, typename Data>
bool 
Map<Key, Data>::operator==(const Map& rhv) const
{
    const_iterator first1 = begin();
    const_iterator first2 = rhv.begin();
    while (first1 && first2) {
        if (*first1 != *first2) { return false; }
        ++first1;
        ++first2;
    }
    return first1 == end() && first2 == rhv.end();
}

template <typename Key, typename Data>
bool 
Map<Key, Data>::operator!=(const Map& rhv) const
{
    return !(*this == rhv);
}

template <typename Key, typename Data>
bool 
Map<Key, Data>::operator<(const Map& rhv) const
{
    const_iterator first1 = begin();
    const_iterator first2 = rhv.begin();
    while (first1 && first2) {
        if (*first1 >= *first2) { return false; }
        ++first1;
        ++first2;
    }
    return first1 == end() && first2 != rhv.end();
}

template <typename Key, typename Data>
bool 
Map<Key, Data>::operator<=(const Map& rhv) const
{
    return !(rhv < *this);
}

template <typename Key, typename Data>
bool
Map<Key, Data>::operator>(const Map& rhv) const
{
    return rhv < *this;
}

template <typename Key, typename Data>
bool 
Map<Key, Data>::operator>=(const Map& rhv) const
{
    return !(*this < rhv);
}

template <typename Key, typename Data>
void 
Map<Key, Data>::preOrderIter(std::ostream& out) const
{
    std::stack<Node*> st;
    Node* temp = root_;
    st.push(root_);
    while (!st.empty()) {
        out << *iterator(temp) << " ";
        if (temp->right_) { st.push(temp->right_); }
        if (temp->left_)  { 
            temp = temp->left_; 
            continue; 
        }
        temp = st.top(); 
        st.pop(); 
    }
}

template <typename Key, typename Data>
void 
Map<Key, Data>::preOrderRec(std::ostream& out) const
{
    preOrderHelper(root_, out);
}

template <typename Key, typename Data>
void 
Map<Key, Data>::preOrderHelper(Node* root, std::ostream& out) const
{
    if (NULL == root) { return; }
    out << *iterator(root) << " ";
    preOrderHelper(root->left_, out);
    preOrderHelper(root->right_, out);
}

template <typename Key, typename Data>
void 
Map<Key, Data>::inOrderIter(std::ostream& out) const
{
    for (const_iterator it = begin(); it != end(); ++it) {
        out << *it << " ";
    }
}

template <typename Key, typename Data>
void 
Map<Key, Data>::inOrderRec(std::ostream& out) const
{
    inOrderHelper(root_, out);
}

template <typename Key, typename Data>
void 
Map<Key, Data>::inOrderHelper(Node* root, std::ostream& out) const
{
    if (NULL == root) { return; }
    inOrderHelper(root->left_, out);
    out << *iterator(root) << " ";
    inOrderHelper(root->right_, out);
}

template <typename Key, typename Data>
void 
Map<Key, Data>::postOrderIter(std::ostream& out) const
{
    std::stack<Node*> stk1, stk2;
    stk1.push(root_);
    Node* current;

    while (!stk1.empty()) {
        current = stk1.top();
        stk1.pop();
        stk2.push(current);
        if (current->left_)  { stk1.push(current->left_);  }
        if (current->right_) { stk1.push(current->right_); }
    }

    while (!stk2.empty()) {
        current = stk2.top();
        stk2.pop();
        out << *iterator(current) << " ";
    }
}

template <typename Key, typename Data>
void 
Map<Key, Data>::postOrderRec(std::ostream& out) const
{
    postOrderHelper(root_, out);
}

template <typename Key, typename Data>
void 
Map<Key, Data>::postOrderHelper(Node* root, std::ostream& out) const
{
    if (NULL == root) { return; }
    postOrderHelper(root->left_, out);
    postOrderHelper(root->right_, out);
    out << *iterator(root) << " ";
}

template <typename Key, typename Data>
void 
Map<Key, Data>::levelOrderIter(std::ostream& out) const
{
    std::queue<Node*> que;
    que.push(root_);
    while (!que.empty()) {
        Node* temp = que.front();
        out << *iterator(temp) << ' ';
        if (temp->left_)  { que.push(temp->left_);  }
        if (temp->right_) { que.push(temp->right_); }
        que.pop();
    }
}

template <typename Key, typename Data>
void 
Map<Key, Data>::outputTree(Node* ptr, std::ostream& out, const int totalSpaces) const
{
    if (NULL == ptr) { return; }
    outputTree(ptr->right_, out, totalSpaces + 5);
    out << std::setw(totalSpaces) << *iterator(ptr) << std::endl;
    outputTree(ptr->left_, out, totalSpaces + 5);
}

template <typename Key, typename Data>
void
Map<Key, Data>::print(std::ostream& out) const
{
    out << "{ ";
    inOrderIter(out);
    out << "}";
}

template <typename Key, typename Data>
typename Map<Key, Data>::Node* 
Map<Key, Data>::getRightMost(Node* rhv)
{
    if (NULL == rhv) { return rhv; }
    while (rhv->right_ != NULL) { rhv = rhv->right_; }
    return rhv;
}


template <typename Key, typename Data>
typename Map<Key, Data>::Node* 
Map<Key, Data>::getLeftMost(Node* rhv)
{
    if (NULL == rhv) { return rhv; }
    while (rhv->left_ != NULL) { rhv = rhv->left_; }
    return rhv;
}

/// const_iterator

template <typename Key, typename Data>
Map<Key, Data>::const_iterator::const_iterator()
    : ptr_(NULL)
{}

template <typename Key, typename Data>
Map<Key, Data>::const_iterator::const_iterator(Node* ptr)
    : ptr_(ptr)
{}

template <typename Key, typename Data>
Map<Key, Data>::const_iterator::const_iterator(const const_iterator& rhv)
    : ptr_(rhv.ptr_)
{}

template <typename Key, typename Data>
Map<Key, Data>::const_iterator::~const_iterator()
{
    destroy();
}

template <typename Key, typename Data>
void 
Map<Key, Data>::const_iterator::destroy()
{
    ptr_ = NULL;
}

template <typename Key, typename Data>
const typename Map<Key, Data>::const_iterator& 
Map<Key, Data>::const_iterator::operator=(const const_iterator& rhv)
{
    ptr_ = rhv.ptr_;
    return *this;
}

template <typename Key, typename Data>
typename Map<Key, Data>::const_reference
Map<Key, Data>::const_iterator::operator*() const
{
    return ptr_->value_;
}

template <typename Key, typename Data>
const typename Map<Key, Data>::value_type*
Map<Key, Data>::const_iterator::operator->() const
{
    return &ptr_->value_;
}

template <typename Key, typename Data>
typename Map<Key, Data>::const_iterator 
Map<Key, Data>::const_iterator::operator++()
{
    /*if (NULL == ptr_->right_) { 
        while (isLeftParent()) {
            goParent();
        }
        goParent();
        return *this;
    }
    ptr_ = getLeftMost(ptr_->right_);
    return *this;
    */
    ptr_ = inOrderIter(ptr_);
    return *this;
}

template <typename Key, typename Data>
typename Map<Key, Data>::const_iterator 
Map<Key, Data>::const_iterator::operator++(int)
{
    Node* temp = ptr_;
    if (NULL == ptr_->right_) { 
        while (isLeftParent()) {
            goParent();
        }
        goParent();
        return const_iterator(temp);
    }
    ptr_ = getLeftMost(ptr_->right_);
    return const_iterator(temp);
}

template <typename Key, typename Data>
typename Map<Key, Data>::const_iterator 
Map<Key, Data>::const_iterator::operator--()
{
    if (NULL == ptr_->left_) { 
        while (isRightParent()) {
            goParent();
        }
        goParent();
        return *this;
    }
    ptr_ = getRightMost(ptr_->left_);
    return *this;
}

template <typename Key, typename Data>
typename Map<Key, Data>::const_iterator 
Map<Key, Data>::const_iterator::operator--(int)
{
    Node* temp = ptr_;
    if (NULL == ptr_->left_) { 
        while (isRightParent()) {
            goParent();
        }
        goParent();
        return const_iterator(temp);
    }
    ptr_ = getRightMost(ptr_->left_);
    return const_iterator(temp);
}

template <typename Key, typename Data>
bool
Map<Key, Data>::const_iterator::isLeftParent() const
{
    return ptr_->parent_ != NULL && ptr_->parent_->right_ == ptr_;
}

template <typename Key, typename Data>
bool
Map<Key, Data>::const_iterator::isRightParent() const
{
    return ptr_->parent_ != NULL && ptr_->parent_->left_ == ptr_;
}

template <typename Key, typename Data>
bool 
Map<Key, Data>::const_iterator::operator==(const const_iterator& rhv) const
{
    return ptr_ == rhv.ptr_;
}

template <typename Key, typename Data>
bool 
Map<Key, Data>::const_iterator::operator!=(const const_iterator& rhv) const
{
    return !(*this == rhv);
}

template <typename Key, typename Data>
bool 
Map<Key, Data>::const_iterator::operator!() const
{
    return NULL == ptr_;
}

template <typename Key, typename Data>
typename Map<Key, Data>::Node* 
Map<Key, Data>::const_iterator::getPtr() const
{
    return ptr_;
}

template <typename Key, typename Data>
void 
Map<Key, Data>::const_iterator::setPtr(Node* temp)
{
    ptr_ = temp;
}

template <typename Key, typename Data>
typename Map<Key, Data>::const_iterator 
Map<Key, Data>::const_iterator::parent() const
{
    return const_iterator(ptr_->parent_);
}

template <typename Key, typename Data>
typename Map<Key, Data>::const_iterator 
Map<Key, Data>::const_iterator::left() const
{
    return const_iterator(ptr_->left_);
}

template <typename Key, typename Data>
typename Map<Key, Data>::const_iterator 
Map<Key, Data>::const_iterator::right() const
{
    return const_iterator(ptr_->right_);
}

template <typename Key, typename Data>
const typename Map<Key, Data>::const_iterator& 
Map<Key, Data>::const_iterator::goParent()
{
    ptr_ = ptr_->parent_;
    return *this;
}

template <typename Key, typename Data>
const typename Map<Key, Data>::const_iterator& 
Map<Key, Data>::const_iterator::goLeft()
{
    ptr_ = ptr_->left_;
    return *this;
}

template <typename Key, typename Data>
const typename Map<Key, Data>::const_iterator& 
Map<Key, Data>::const_iterator::goRight()
{
    ptr_ = ptr_->right_;
    return *this;
}

template <typename Key, typename Data>
typename Map<Key, Data>::const_iterator 
Map<Key, Data>::const_iterator::firstLeftParent() const
{
    if (!this->parent()) { return const_iterator(NULL); }
    const_iterator p = this->parent();
    if (p.right() == *this) { return p; }
    return p.firstLeftParent(); 
}

template <typename Key, typename Data>
typename Map<Key, Data>::const_iterator 
Map<Key, Data>::const_iterator::firstRightParent() const
{
    if (!this->parent()) { return const_iterator(NULL); }
    const_iterator p = this->parent();
    if (p.left() == *this) { return p; }
    return p.firstRightParent(); 
}

template <typename Key, typename Data>
void 
Map<Key, Data>::const_iterator::createLeft(const value_type& x)
{
    ptr_->left_ = new Node(x.first, x.second, ptr_);
}

template <typename Key, typename Data>
void 
Map<Key, Data>::const_iterator::createRight(const value_type& x)
{
    ptr_->right_ = new Node(x.first, x.second, ptr_);
}

template <typename Key, typename Data>
void
Map<Key, Data>::const_iterator::setParent(const_iterator it)
{
    ptr_->parent_ = it.getPtr();
}

template <typename Key, typename Data>
void
Map<Key, Data>::const_iterator::setLeft(const_iterator it)
{
    ptr_->left_ = it.getPtr();
}

template <typename Key, typename Data>
void
Map<Key, Data>::const_iterator::setRight(const_iterator it)
{
    ptr_->right_ = it.getPtr();
}

template <typename Key, typename Data>
int 
Map<Key, Data>::const_iterator::balance() const
{
    return left().depth() - right().depth();
}

template <typename Key, typename Data>
int
Map<Key, Data>::const_iterator::depth() const
{
    if (NULL == ptr_) { return 0; }
    const int leftDepth = left().depth();
    const int rightDepth = right().depth();
    return std::max(leftDepth, rightDepth) + 1;
}

template <typename Key, typename Data>
Map<Key, Data>::const_iterator::operator bool() const
{
    return NULL != ptr_;
}

/// iterator

template <typename Key, typename Data>
Map<Key, Data>::iterator::iterator()
    : const_iterator()
{}

template <typename Key, typename Data>
Map<Key, Data>::iterator::iterator(Node* ptr)
    : const_iterator(ptr)
{}

template <typename Key, typename Data>
Map<Key, Data>::iterator::iterator(const iterator& rhv)
    : const_iterator(rhv)
{}

template <typename Key, typename Data>
Map<Key, Data>::iterator::~iterator()
{
    this->destroy();
}

template <typename Key, typename Data>
const typename Map<Key, Data>::iterator& 
Map<Key, Data>::iterator::operator=(const iterator& rhv)
{
    this->setPtr(rhv.getPtr());
    return *this;
}

template <typename Key, typename Data>
typename Map<Key, Data>::reference 
Map<Key, Data>::iterator::operator*()
{
    return this->getPtr()->value_;
}

template <typename Key, typename Data>
typename Map<Key, Data>::value_type*
Map<Key, Data>::iterator::operator->()
{
    return &this->getPtr()->value_;
}

template <typename Key, typename Data>
typename Map<Key, Data>::iterator 
Map<Key, Data>::iterator::operator++()
{
    if (NULL == this->getPtr()->right_) { 
        while (this->isLeftParent()) {
            this->goParent();
        }
        this->goParent();
        return *this;
    }
    this->setPtr(getLeftMost(this->getPtr()->right_));
    return *this;
}

template <typename Key, typename Data>
typename Map<Key, Data>::iterator 
Map<Key, Data>::iterator::operator++(int)
{
    Node* temp = this->getPtr();
    if (NULL == temp->right_) { 
        while (this->isLeftParent()) {
            this->goParent();
        }
        this->goParent();
        return iterator(temp);
    }
    this->setPtr(getLeftMost(this->getPtr()->right_));
    return iterator(temp);
}

template <typename Key, typename Data>
typename Map<Key, Data>::iterator 
Map<Key, Data>::iterator::operator--()
{
    if (NULL == this->getPtr()->left_) { 
        while (this->isRightParent()) {
            this->goParent();
        }
        this->goParent();
        return *this;
    }
    this->setPtr(getRightMost(this->getPtr()->left_));
    return *this;
}

template <typename Key, typename Data>
typename Map<Key, Data>::iterator 
Map<Key, Data>::iterator::operator--(int)
{
    Node* temp = this->getPtr();
    if (NULL == this->getPtr()->left_) { 
        while (this->isRightParent()) {
            this->goParent();
        }
        this->goParent();
        return iterator(temp);
    }
    this->setPtr(getRightMost(this->getPtr()->left_));
    return iterator(temp);
}

template <typename Key, typename Data>
typename Map<Key, Data>::iterator 
Map<Key, Data>::iterator::parent()
{
    Node* temp = this->getPtr();
    return NULL == temp ? iterator(temp) : iterator(temp->parent_);
}

template <typename Key, typename Data>
typename Map<Key, Data>::iterator 
Map<Key, Data>::iterator::left()
{
    Node* temp = this->getPtr();
    return NULL == temp ? iterator(temp) : iterator(temp->left_);
}

template <typename Key, typename Data>
typename Map<Key, Data>::iterator 
Map<Key, Data>::iterator::right()
{
    Node* temp = this->getPtr();
    return NULL == temp ? iterator(temp) : iterator(temp->right_);
}

template <typename Key, typename Data>
typename Map<Key, Data>::iterator& 
Map<Key, Data>::iterator::goParent()
{
    const_iterator::goParent();
    return *this;
}

template <typename Key, typename Data>
typename Map<Key, Data>::iterator& 
Map<Key, Data>::iterator::goLeft()
{
    const_iterator::goLeft();
    return *this;
}

template <typename Key, typename Data>
typename Map<Key, Data>::iterator&
Map<Key, Data>::iterator::goRight()
{
    const_iterator::goRight();
    return *this;
}

/// const_reverse_iterator

template <typename Key, typename Data>
Map<Key, Data>::const_reverse_iterator::const_reverse_iterator()
    : ptr_(NULL)
{}

template <typename Key, typename Data>
Map<Key, Data>::const_reverse_iterator::const_reverse_iterator(Node* ptr)
    : ptr_(ptr)
{}

template <typename Key, typename Data>
Map<Key, Data>::const_reverse_iterator::const_reverse_iterator(const const_reverse_iterator& rhv)
    : ptr_(rhv.ptr_)
{}

template <typename Key, typename Data>
Map<Key, Data>::const_reverse_iterator::~const_reverse_iterator()
{
    destroy();
}

template <typename Key, typename Data>
void 
Map<Key, Data>::const_reverse_iterator::destroy()
{
    ptr_ = NULL;
}

template <typename Key, typename Data>
const typename Map<Key, Data>::const_reverse_iterator& 
Map<Key, Data>::const_reverse_iterator::operator=(const const_reverse_iterator& rhv)
{
    ptr_ = rhv.ptr_;
    return *this;
}

template <typename Key, typename Data>
typename Map<Key, Data>::const_reference
Map<Key, Data>::const_reverse_iterator::operator*() const
{
    return ptr_->value_;
}

template <typename Key, typename Data>
const typename Map<Key, Data>::value_type*
Map<Key, Data>::const_reverse_iterator::operator->() const
{
    return &ptr_->value_;
}

template <typename Key, typename Data>
typename Map<Key, Data>::const_reverse_iterator 
Map<Key, Data>::const_reverse_iterator::operator++()
{
    if (NULL == ptr_->left_) { 
        while (isRightParent()) {
            goParent();
        }
        goParent();
        return *this;
    }
    ptr_ = getRightMost(ptr_->left_);
    return *this;
}

template <typename Key, typename Data>
typename Map<Key, Data>::const_reverse_iterator 
Map<Key, Data>::const_reverse_iterator::operator++(int)
{
    Node* temp = ptr_;
    if (NULL == ptr_->right_) { 
        while (isLeftParent()) {
            goParent();
        }
        goParent();
        return const_reverse_iterator(temp);
    }
    ptr_ = getLeftMost(ptr_->right_);
    return const_reverse_iterator(temp);
}

template <typename Key, typename Data>
typename Map<Key, Data>::const_reverse_iterator 
Map<Key, Data>::const_reverse_iterator::operator--(int)
{
    Node* temp = ptr_;
    if (NULL == ptr_->right_) { 
        while (isLeftParent()) {
            goParent();
        }
        goParent();
        return const_reverse_iterator(temp);
    }
    ptr_ = getLeftMost(ptr_->right_);
    return const_reverse_iterator(temp);
}

template <typename Key, typename Data>
bool
Map<Key, Data>::const_reverse_iterator::isLeftParent() const
{
    return ptr_->parent_ != NULL && ptr_->parent_->right_ == ptr_;
}

template <typename Key, typename Data>
bool
Map<Key, Data>::const_reverse_iterator::isRightParent() const
{
    return ptr_->parent_ != NULL && ptr_->parent_->left_ == ptr_;
}

template <typename Key, typename Data>
bool 
Map<Key, Data>::const_reverse_iterator::operator==(const const_reverse_iterator& rhv) const
{
    return ptr_ == rhv.ptr_;
}

template <typename Key, typename Data>
bool 
Map<Key, Data>::const_reverse_iterator::operator!=(const const_reverse_iterator& rhv) const
{
    return !(*this == rhv);
}

template <typename Key, typename Data>
bool 
Map<Key, Data>::const_reverse_iterator::operator!() const
{
    return NULL == ptr_;
}

template <typename Key, typename Data>
typename Map<Key, Data>::Node* 
Map<Key, Data>::const_reverse_iterator::getPtr() const
{
    return ptr_;
}

template <typename Key, typename Data>
void 
Map<Key, Data>::const_reverse_iterator::setPtr(Node* temp)
{
    ptr_ = temp;
}

template <typename Key, typename Data>
const typename Map<Key, Data>::const_reverse_iterator&
Map<Key, Data>::const_reverse_iterator::goParent()
{
    ptr_ = ptr_->parent_;
    return *this;
}

/// reverse_iterator

template <typename Key, typename Data>
Map<Key, Data>::reverse_iterator::reverse_iterator()
    : const_reverse_iterator()
{}

template <typename Key, typename Data>
Map<Key, Data>::reverse_iterator::reverse_iterator(Node* ptr)
    : const_reverse_iterator(ptr)
{}

template <typename Key, typename Data>
Map<Key, Data>::reverse_iterator::reverse_iterator(const reverse_iterator& rhv)
    : const_reverse_iterator(rhv)
{}

template <typename Key, typename Data>
Map<Key, Data>::reverse_iterator::~reverse_iterator()
{
    this->destroy();
}

template <typename Key, typename Data>
const typename Map<Key, Data>::reverse_iterator& 
Map<Key, Data>::reverse_iterator::operator=(const reverse_iterator& rhv)
{
    this->setPtr(rhv.getPtr());
    return *this;
}

template <typename Key, typename Data>
typename Map<Key, Data>::reference 
Map<Key, Data>::reverse_iterator::operator*()
{
    return this->getPtr()->value_;
}

template <typename Key, typename Data>
typename Map<Key, Data>::value_type*
Map<Key, Data>::reverse_iterator::operator->()
{
    return &this->getPtr()->value_;
}

template <typename Key, typename Data>
typename Map<Key, Data>::reverse_iterator 
Map<Key, Data>::reverse_iterator::operator++()
{
    if (NULL == this->getPtr()->left_) { 
        while (this->isRightParent()) {
            this->goParent();
        }
        this->goParent();
        return *this;
    }
    this->setPtr(getRightMost(this->getPtr()->left_));
    return *this;
}

template <typename Key, typename Data>
typename Map<Key, Data>::reverse_iterator 
Map<Key, Data>::reverse_iterator::operator++(int)
{
    Node* temp = this->getPtr();
    if (NULL == this->getPtr()->left_) { 
        while (this->isRightParent()) {
            this->goParent();
        }
        this->goParent();
        return reverse_iterator(temp);
    }
    this->setPtr(getRightMost(this->getPtr()->left_));
    return reverse_iterator(temp);
}

template <typename Key, typename Data>
typename Map<Key, Data>::reverse_iterator 
Map<Key, Data>::reverse_iterator::operator--()
{
    if (NULL == this->getPtr()->right_) { 
        while (this->isLeftParent()) {
            this->goParent();
        }
        this->goParent();
        return *this;
    }
    this->setPtr(getLeftMost(this->getPtr()->right_));
    return *this;
}

template <typename Key, typename Data>
typename Map<Key, Data>::reverse_iterator 
Map<Key, Data>::reverse_iterator::operator--(int)
{
    Node* temp = this->getPtr();
    if (NULL == temp->right_) { 
        while (this->isLeftParent()) {
            this->goParent();
        }
        this->goParent();
        return reverse_iterator(temp);
    }
    this->setPtr(getLeftMost(this->getPtr()->right_));
    return reverse_iterator(temp);
}

template <typename Key, typename Data>
typename Map<Key, Data>::reverse_iterator& 
Map<Key, Data>::reverse_iterator::goParent()
{
    const_reverse_iterator::goParent();
    return *this;
}




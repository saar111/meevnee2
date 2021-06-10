#ifndef WET01_AVLNODE_H
#define WET01_AVLNODE_H

template<class T>
class AVLRankedNode {
private:
    T *data;
    AVLRankedNode<T> *parent;
    AVLRankedNode<T> *left;
    AVLRankedNode<T> *right;
    int height;
    int children;
public:
    AVLRankedNode<T>(T *data) : data(data), left(nullptr), parent(nullptr), right(nullptr), height(0), children(1) {}

    AVLRankedNode<T>() : data(nullptr), left(nullptr), parent(nullptr), right(nullptr), height(0), children(1) {}

    void SetParent(AVLRankedNode<T> *node);
    void SetLeft(AVLRankedNode<T> *node);
    void SetRight(AVLRankedNode<T> *node);
    void SetHeight(int height);
    void SetData(T *data);
    void SetChildren(int children);

    int GetHeight();
    AVLRankedNode<T> *GetLeft();
    AVLRankedNode<T> *GetRight();
    AVLRankedNode<T> *GetParent();
    T *GetData();
    int GetChildren() const;
};


template<class T>
void AVLRankedNode<T>::SetParent(AVLRankedNode<T> *node) {
    parent = node;
}

template<class T>
void AVLRankedNode<T>::SetLeft(AVLRankedNode<T> *node) {
    left = node;
}

template<class T>
void AVLRankedNode<T>::SetRight(AVLRankedNode<T> *node) {
    right = node;
}

template<class T>
void AVLRankedNode<T>::SetHeight(int height) {
    this->height = height;
}


template<class T>
void AVLRankedNode<T>::SetData(T *data) {
    this->data = data;
}

template<class T>
AVLRankedNode<T> *AVLRankedNode<T>::GetLeft() {
    return left;
}

template<class T>
AVLRankedNode<T> *AVLRankedNode<T>::GetRight() {
    return right;
}

template<class T>
AVLRankedNode<T> *AVLRankedNode<T>::GetParent() {
    return parent;
}

template<class T>
int AVLRankedNode<T>::GetHeight() {
    return height;
}

template<class T>
T *AVLRankedNode<T>::GetData() {
    return data;
}

template<class T>
int AVLRankedNode<T>::GetChildren() const {
    return children;
}

template<class T>
void AVLRankedNode<T>::SetChildren(int children) {
    AVLRankedNode::children = children;
}


#endif //WET01_AVLNODE_H

#ifndef WET02_UNIONFIND_H
#define WET02_UNIONFIND_H

#include "DynamicArray.h"

template<class T>
class UnionNode {
private:
    T *data;
    UnionNode *papa;
    int children_count;
public:
    explicit UnionNode(T *data);
    UnionNode *GetPapa() const;
    int GetChildrenCount() const;
    T *GetData() const;
    void SetPapa(UnionNode *parent);
    void SetChildrenCount(int childrenCount);
};

template<class T>
UnionNode<T>::UnionNode(T *data) : papa(nullptr), data(data), children_count(1) {}

template<class T>
T *UnionNode<T>::GetData() const {
    return data;
}

template<class T>
UnionNode<T> *UnionNode<T>::GetPapa() const {
    return papa;
}

template<class T>
void UnionNode<T>::SetPapa(UnionNode *parent) {
    UnionNode::papa = parent;
}

template<class T>
int UnionNode<T>::GetChildrenCount() const {
    return children_count;
}

template<class T>
void UnionNode<T>::SetChildrenCount(int childrenCount) {
    children_count = childrenCount;
}

const int ARRAY_START_SIZE = 10;

template<class T>
class UnionFind {
private:
    DynamicArray<UnionNode<T>> nodes;

public:
    UnionFind();
    ~UnionFind();
    template<typename DataUniter>
    UnionNode<T> *Union(int serial1, int serial2, DataUniter data_uniter);
    UnionNode<T> *Find(int serial);
    UnionNode<T> *MakeSet(T *data);
    void DeleteInnerData();


};

template<class T>
UnionFind<T>::UnionFind() : nodes(DynamicArray<UnionNode<T>>()) {}

template<class T>
template<typename DataUniter>
UnionNode<T> *UnionFind<T>::Union(int serial1, int serial2, DataUniter data_uniter) {
    UnionNode<T> *q = this->Find(serial1);
    UnionNode<T> *p = this->Find(serial2);

    UnionNode<T> *smaller = q;
    UnionNode<T> *bigger = p;
    if (p->GetChildrenCount() < q->GetChildrenCount()) {
        smaller = p;
        bigger = q;
    }

    smaller->SetPapa(bigger);
    bigger->SetChildrenCount(bigger->GetChildrenCount() + smaller->GetChildrenCount());
    data_uniter(bigger->GetData(), smaller->GetData());

    return bigger;
}

template<class T>
UnionNode<T> *UnionFind<T>::Find(int serial) {
    if (serial >= nodes.elements_count) {
        return nullptr;
    }

    UnionNode<T> *target = nodes.pointers[serial];

    UnionNode<T> *current = target;
    while (current->GetPapa() != nullptr) {
        current = current->GetPapa();
    }
    UnionNode<T> *root = current;

    current = target;
    while (current != root) {
        current->SetPapa(root);
        current = current->GetPapa();
    }

    return root;
}

template<class T>
UnionNode<T> *UnionFind<T>::MakeSet(T *data) {
    UnionNode<T> *new_set = new UnionNode<T>(data);
    nodes.Push(new_set);
    return new_set;
}

template<class T>
UnionFind<T>::~UnionFind() {
    for (int i = 0; i < nodes.elements_count; i++) {
        delete nodes.pointers[i];
    }
}

template<class T>
void UnionFind<T>::DeleteInnerData() {
    for (int i = 0; i < nodes.elements_count; i++) {
        delete nodes.pointers[i]->GetData();
    }

}


#endif //WET02_UNIONFIND_H

#ifndef WET01_AVLTREE_H
#define WET01_AVLTREE_H

#include <iostream>
#include "AVLRankedNode.h"
#include <cassert>

using namespace std;
#define COUNT 5

int max(int num1, int num2);


template<class T>
class AVLRankedTree {
private:

    AVLRankedNode<T> *root = nullptr;
    AVLRankedNode<T> *smallest_node = nullptr;
    AVLRankedNode<T> *biggest_node = nullptr;

    int GetBF(AVLRankedNode<T> *node);
    void BalanceNode(AVLRankedNode<T> *node);
    void BalanceFromLeaf(AVLRankedNode<T> *node);
    void RRCase(AVLRankedNode<T> *node);
    void RLCase(AVLRankedNode<T> *node);
    void LRCase(AVLRankedNode<T> *node);
    void LLCase(AVLRankedNode<T> *node);
    void RotateRight(AVLRankedNode<T> *node);
    void RotateLeft(AVLRankedNode<T> *node);

    void UpdateEdgeNodes();
    AVLRankedNode<T> *GetSmallestNode(AVLRankedNode<T> *node);
    AVLRankedNode<T> *GetBiggestNode(AVLRankedNode<T> *node);

    int CountChildren(AVLRankedNode<T> *node);
    void UpdateHeight(AVLRankedNode<T> *node);
    void UpdateChildren(AVLRankedNode<T> *node);
    void UpdateInformation(AVLRankedNode<T> *node);
    void InsertNode(AVLRankedNode<T> *new_node, AVLRankedNode<T> *current);

    void RemoveLeaf(AVLRankedNode<T> *target_node);
    void RemoveSingleChildNode(AVLRankedNode<T> *target_node);
    void SwapNodesData(AVLRankedNode<T> *node, AVLRankedNode<T> *successor);
    void RemoveNode(AVLRankedNode<T> *target_node);
    bool Remove(const T *data, AVLRankedNode<T> *current);
    void InsertionToCopyTree(AVLRankedNode<T> *node, AVLRankedNode<T> *parent, char flag);
    AVLRankedNode<T> *SelectAux(int rank, AVLRankedNode<T> *current);

    void DestroyTree(AVLRankedNode<T> *current);


    template<typename Callback>
    void InOrderFromNode(Callback cb, AVLRankedNode<T> *node, int &cb_threshold, AVLRankedNode<T> *referrer = nullptr);

public:
    class TreeIterator {
    private:
        AVLRankedNode<T> *current;

        bool IsLeaf(AVLRankedNode<T> *node) {
            assert(node != nullptr);

            return node->GetLeft() == nullptr && node->GetRight() == nullptr;
        }

        void AscendUntilRight() {
            AVLRankedNode<T> *prev = nullptr;
            while (current->GetRight() == prev) {
                prev = current;
                current = current->GetParent();

                if (current == nullptr) {
                    return;
                }
            }
        }

        void DescendToNext() {
            current = current->GetRight();
            while (current->GetLeft() != nullptr) {
                current = current->GetLeft();
            }
        }

    public:
        explicit TreeIterator(AVLRankedNode<T> *start) : current(start) {}

        TreeIterator &operator++() {
            if (current == nullptr) {
                return *this;
            }

            if (IsLeaf(current)) {
                AscendUntilRight();
            } else {
                if (current->GetRight() != nullptr) {
                    DescendToNext();
                } else {
                    AscendUntilRight();
                }
            }
            return *this;
        }

        T *operator*() {
            if (current == nullptr) {
                return nullptr;
            }
            return current->GetData();
        }

        bool operator==(TreeIterator &other) {
            return current == other.current;
        }

        bool operator!=(TreeIterator &other) {
            return current != other.current;
        }

    };

    AVLRankedTree();
    AVLRankedTree(T **sorted_array, int size);
    void BuildTree(T **sorted_array, int size, AVLRankedNode<T> *current);
    AVLRankedNode<T> *Insert(T *data);
    T *Find(const T *data) const;
    T *RecursiveFind(const T *data, AVLRankedNode<T> *current) const;
    bool Remove(const T *data);
    int GetTreeSize();

    AVLRankedNode<T> *GetSmallestNode() const;
    AVLRankedNode<T> *GetBiggestNode() const;
    template<typename Callback>
    void InOrderFromSmallest(Callback cb, int cb_threshold = -1);
    void ClearTree();
    AVLRankedNode<T> *Select(int rank);

    TreeIterator BeginFromSmallest() {
        return AVLRankedTree::TreeIterator(GetSmallestNode());
    }

    AVLRankedTree<T> &operator=(AVLRankedTree<T> const &);
    ~AVLRankedTree();


};


template<class T>
AVLRankedTree<T>::AVLRankedTree(T **sorted_array, int size) {
    BuildTree(sorted_array, size, this->root);
    UpdateEdgeNodes();
}


template<class T>
void AVLRankedTree<T>::BuildTree(T **sorted_array, int size, AVLRankedNode<T> *current) {
    if (size <= 0) {
        return;
    }

    int mid = (size / 2);
    int left_size = mid;
    int right_size = size - (mid + 1);
    T *new_data = sorted_array[mid];
    AVLRankedNode<T> *new_node = new AVLRankedNode<T>(new_data);

    if (current == nullptr) {
        root = new_node;
    } else {
        if (*new_data < *(current->GetData())) {
            current->SetLeft(new_node);
        } else {
            current->SetRight(new_node);
        }
        new_node->SetParent(current);
    }

    BuildTree(sorted_array, left_size, new_node);
    BuildTree(sorted_array + mid + 1, right_size, new_node);

    UpdateInformation(new_node);
}

template<class T>
AVLRankedTree<T> &AVLRankedTree<T>::operator=(const AVLRankedTree<T> &rhs) {
    if (this == &rhs) {
        return *this;
    }
    if (this->root != nullptr) {
        this->ClearTree();
    }
    if (rhs.root == nullptr) {
        return *this;
    }
    AVLRankedNode<T> *node_to_insert = new AVLRankedNode<T>(rhs.root->GetData());
    this->root = node_to_insert;
    if (rhs.root->GetLeft() == nullptr && rhs.root->GetRight() == nullptr) {
        UpdateEdgeNodes();
        return *this;
    }
    if (rhs.root->GetLeft() != nullptr) {
        InsertionToCopyTree(rhs.root->GetLeft(), this->root, 'l');
    }
    if (rhs.root->GetRight() != nullptr) {
        InsertionToCopyTree(rhs.root->GetRight(), this->root, 'r');
    }

    UpdateEdgeNodes();
    return *this;
}


template<class T>
void AVLRankedTree<T>::InsertionToCopyTree(AVLRankedNode<T> *node, AVLRankedNode<T> *current, char flag) {
    if (node == nullptr) {
        return;
    }
    AVLRankedNode<T> *node_to_insert = new AVLRankedNode<T>(node->GetData());
    if (flag == 'l') {
        current->SetLeft(node_to_insert);
        UpdateInformation(current);
        node_to_insert->SetParent(current);
        current = current->GetLeft();
        InsertionToCopyTree(node->GetLeft(), current, 'l');
        InsertionToCopyTree(node->GetRight(), current, 'r');
    } else if (flag == 'r') {
        current->SetRight(node_to_insert);
        UpdateInformation(current);
        node_to_insert->SetParent(current);
        current = current->GetRight();
        InsertionToCopyTree(node->GetLeft(), current, 'l');
        InsertionToCopyTree(node->GetRight(), current, 'r');
    }
    /*if (node->GetLeft() != nullptr) {
        InsertionToCopyTree(node->GetLeft(), current->GetLeft(), 'l');
    }
    if (node->GetRight() != nullptr) {
    }*/
}

template<class T>
AVLRankedTree<T>::AVLRankedTree():root(nullptr), smallest_node(nullptr), biggest_node(nullptr) {

}

template<class T>
void AVLRankedTree<T>::UpdateEdgeNodes() {
    this->smallest_node = this->GetSmallestNode(this->root);
    this->biggest_node = this->GetBiggestNode(this->root);
}

template<class T>
template<typename Callback>
void AVLRankedTree<T>::InOrderFromSmallest(Callback cb, int cb_threshold) {
    InOrderFromNode(cb, GetSmallestNode(), cb_threshold, nullptr);
}

template<class T>
template<typename Callback>
void
AVLRankedTree<T>::InOrderFromNode(Callback cb, AVLRankedNode<T> *node, int &cb_threshold, AVLRankedNode<T> *referrer) {
    if (node == nullptr || cb_threshold == 0) {
        return;
    }
    if (referrer != node->GetLeft()) {
        InOrderFromNode(cb, node->GetLeft(), cb_threshold, node);
    }

    cb(node->GetData());
    cb_threshold--;

    if (referrer != node->GetRight()) {
        InOrderFromNode(cb, node->GetRight(), cb_threshold, node);
    }
    if (referrer != node->GetParent()) {
        InOrderFromNode(cb, node->GetParent(), cb_threshold, node);
    }
}

template<class T>
AVLRankedNode<T> *AVLRankedTree<T>::GetSmallestNode() const {
    return smallest_node;
}

template<class T>
AVLRankedNode<T> *AVLRankedTree<T>::GetBiggestNode() const {
    return biggest_node;
}

template<class T>
AVLRankedNode<T> *AVLRankedTree<T>::Insert(T *data) {
    if (data == nullptr) {
        return nullptr;
    }
    AVLRankedNode<T> *new_node = new AVLRankedNode<T>(data);
    if (root == nullptr) {
        root = new_node;
        UpdateEdgeNodes();
        return root;
    }
    InsertNode(new_node, root);
    UpdateEdgeNodes();

    return new_node;
}

template<class T>
void AVLRankedTree<T>::InsertNode(AVLRankedNode<T> *new_node, AVLRankedNode<T> *current) {
    if (*(new_node->GetData()) < *(current->GetData())) {
        if (current->GetLeft() == nullptr) {
            current->SetLeft(new_node);
            new_node->SetParent(current);
        } else {
            InsertNode(new_node, current->GetLeft());
        }
    } else {
        if (current->GetRight() == nullptr) {
            current->SetRight(new_node);
            new_node->SetParent(current);
        } else {
            InsertNode(new_node, current->GetRight());
        }
    }

    UpdateInformation(current);
    BalanceNode(current);
}

template<class T>
AVLRankedNode<T> *AVLRankedTree<T>::GetSmallestNode(AVLRankedNode<T> *node) {
    if (node == nullptr) {
        return nullptr;
    }
    while (node->GetLeft() != nullptr) {
        node = node->GetLeft();
    }
    return node;
}

template<class T>
AVLRankedNode<T> *AVLRankedTree<T>::GetBiggestNode(AVLRankedNode<T> *node) {
    if (node == nullptr) {
        return nullptr;
    }
    while (node->GetRight() != nullptr) {
        node = node->GetRight();
    }
    return node;
}

template<class T>
T *AVLRankedTree<T>::Find(const T *data) const {
    if (data == nullptr || this->root == nullptr) {
        return nullptr;
    }
    if (*(root->GetData()) == *(data)) {
        return root->GetData();
    }
    T *target_data = nullptr;
    //AVLNode<T>* target_node= nullptr;
    if (*(data) < *(root->GetData())) {
        target_data = RecursiveFind(data, root->GetLeft());
    } else /*if(*(data) > *(root->GetData()))*/
    {
        target_data = RecursiveFind(data, root->GetRight());
    }
    return target_data;

}

template<class T>
T *AVLRankedTree<T>::RecursiveFind(const T *data, AVLRankedNode<T> *current) const {
    if (current == nullptr) {
        return nullptr;
    }
    if (*(current->GetData()) == *(data)) {
        return current->GetData();
    }
    T *target_data = nullptr;
    if (*(data) < *(current->GetData())) {
        target_data = RecursiveFind(data, current->GetLeft());
    } else /*if(*(data) > *(current->GetData()))*/
    {
        target_data = RecursiveFind(data, current->GetRight());
    }
    return target_data;
}

template<class T>
bool AVLRankedTree<T>::Remove(const T *data) {
    if (data == nullptr || root == nullptr) {
        return false;
    }
    bool res = Remove(data, root);
    UpdateEdgeNodes();
    return res;
}

template<class T>
bool AVLRankedTree<T>::Remove(const T *data, AVLRankedNode<T> *current) {
    if (current == nullptr) {
        return false;
    }
    bool res_left = false, res_right = false;
    if (*data < *(current->GetData())) {
        res_left = Remove(data, current->GetLeft());
    } else if (*data == *(current->GetData())) {
        RemoveNode(current);
        return true;
    } else {
        res_right = Remove(data, current->GetRight());
    }

    UpdateInformation(current);
    BalanceNode(current);
    return res_left || res_right;
}

template<class T>
void AVLRankedTree<T>::RemoveNode(AVLRankedNode<T> *target_node) {
    if (CountChildren(target_node) == 0) {
        RemoveLeaf(target_node);
    } else if (CountChildren(target_node) == 1) {
        RemoveSingleChildNode(target_node);
    } else {
        AVLRankedNode<T> *target_successor = GetSmallestNode(target_node->GetRight());
        AVLRankedNode<T> *target_successor_parent = target_successor->GetParent();
        SwapNodesData(target_node, target_successor);
        RemoveNode(target_successor);
        BalanceFromLeaf(target_successor_parent);
        return;
    }
    delete target_node;
}

template<class T>
void AVLRankedTree<T>::RemoveLeaf(AVLRankedNode<T> *target_node) {
    if (target_node == root) {
        root = nullptr;
    } else {
        if (target_node->GetParent()->GetLeft() == target_node) {
            target_node->GetParent()->SetLeft(nullptr);
        } else {
            target_node->GetParent()->SetRight(nullptr);
        }
    }
}

template<class T>
void AVLRankedTree<T>::RemoveSingleChildNode(AVLRankedNode<T> *target_node) {
    AVLRankedNode<T> *target_child =
            target_node->GetLeft() != nullptr ? target_node->GetLeft() : target_node->GetRight();
    if (target_node == root) {
        root = target_child;
    } else {
        if (target_node->GetParent()->GetLeft() == target_node) {
            target_node->GetParent()->SetLeft(target_child);
        } else {
            target_node->GetParent()->SetRight(target_child);
        }
    }
    target_child->SetParent(target_node->GetParent());
}

template<class T>
void AVLRankedTree<T>::SwapNodesData(AVLRankedNode<T> *node, AVLRankedNode<T> *successor) {
    T *temp_data = successor->GetData();
    successor->SetData(node->GetData());
    node->SetData(temp_data);
}

template<class T>
int AVLRankedTree<T>::CountChildren(AVLRankedNode<T> *node) {
    return (node->GetLeft() != nullptr) + (node->GetRight() != nullptr);
}


template<class T>
void AVLRankedTree<T>::UpdateInformation(AVLRankedNode<T> *node) {
    UpdateHeight(node);
    UpdateChildren(node);
}

template<class T>
void AVLRankedTree<T>::LLCase(AVLRankedNode<T> *node) {
    RotateRight(node);
}

template<class T>
void AVLRankedTree<T>::LRCase(AVLRankedNode<T> *node) {
    RotateLeft(node->GetLeft());
    RotateRight(node);
}

template<class T>
void AVLRankedTree<T>::RRCase(AVLRankedNode<T> *node) {
    RotateLeft(node);
}

template<class T>
void AVLRankedTree<T>::RLCase(AVLRankedNode<T> *node) {
    RotateRight(node->GetRight());
    RotateLeft(node);
}

template<class T>
void AVLRankedTree<T>::RotateLeft(AVLRankedNode<T> *node) {
    AVLRankedNode<T> *old_node_parent = node->GetParent();
    AVLRankedNode<T> *new_semi_root = node->GetRight();

    node->SetRight(new_semi_root->GetLeft());
    if (node->GetRight() != nullptr) {
        node->GetRight()->SetParent(node);
    }

    new_semi_root->SetLeft(node);
    node->SetParent(new_semi_root);
    new_semi_root->SetParent(old_node_parent);

    UpdateInformation(node);
    UpdateInformation(new_semi_root);

    // Update parent
    if (old_node_parent == nullptr) {
        root = new_semi_root;
    } else {
        if (old_node_parent->GetLeft() == node) {
            old_node_parent->SetLeft(new_semi_root);
        } else {
            old_node_parent->SetRight(new_semi_root);
        }
    }
}

template<class T>
void AVLRankedTree<T>::RotateRight(AVLRankedNode<T> *node) {
    AVLRankedNode<T> *old_node_parent = node->GetParent();
    AVLRankedNode<T> *new_semi_root = node->GetLeft();

    node->SetLeft(new_semi_root->GetRight());
    if (node->GetLeft() != nullptr) {
        node->GetLeft()->SetParent(node);
    }

    new_semi_root->SetRight(node);
    node->SetParent(new_semi_root);
    new_semi_root->SetParent(old_node_parent);

    UpdateInformation(node);
    UpdateInformation(new_semi_root);

    // Update parent
    if (old_node_parent == nullptr) {
        root = new_semi_root;
    } else {
        if (old_node_parent->GetLeft() == node) {
            old_node_parent->SetLeft(new_semi_root);
        } else {
            old_node_parent->SetRight(new_semi_root);
        }
    }
}

template<class T>
int AVLRankedTree<T>::GetBF(AVLRankedNode<T> *node) {
    if (node == nullptr) {
        return 0;
    }
    int left_height = node->GetLeft() != nullptr ? node->GetLeft()->GetHeight() : -1;
    int right_height = node->GetRight() != nullptr ? node->GetRight()->GetHeight() : -1;
    return left_height - right_height;
}

template<class T>
void AVLRankedTree<T>::BalanceNode(AVLRankedNode<T> *node) {
    int first_bf = GetBF(node);
    if (first_bf == 2) {
        int second_bf = GetBF(node->GetLeft());
        if (second_bf >= 0) {
            LLCase(node);
        }
        if (second_bf == -1) {
            LRCase(node);
        }
    }
    if (first_bf == -2) {
        int second_bf = GetBF(node->GetRight());
        if (second_bf <= 0) {
            RRCase(node);
        }
        if (second_bf == 1) {
            RLCase(node);
        }
    }
}

template<class T>
AVLRankedTree<T>::~AVLRankedTree() {
    ClearTree();
}

template<class T>
void AVLRankedTree<T>::ClearTree() {
    DestroyTree(root);
    root = nullptr;
    smallest_node = nullptr;
    biggest_node = nullptr;
}

template<class T>
void AVLRankedTree<T>::DestroyTree(AVLRankedNode<T> *current) {
    if (current == nullptr) {
        return;
    }
    DestroyTree(current->GetLeft());
    DestroyTree(current->GetRight());
    delete current;
}

template<class T>
void AVLRankedTree<T>::BalanceFromLeaf(AVLRankedNode<T> *node) {
    while (node != nullptr) {
        UpdateInformation(node);
        BalanceNode(node);
        node = node->GetParent();
    }
}

template<class T>
void AVLRankedTree<T>::UpdateHeight(AVLRankedNode<T> *node) {
    if (CountChildren(node) == 0) {
        node->SetHeight(0);
    } else {
        int left_height = node->GetLeft() != nullptr ? node->GetLeft()->GetHeight() : 0;
        int right_height = node->GetRight() != nullptr ? node->GetRight()->GetHeight() : 0;

        node->SetHeight(max(left_height, right_height) + 1);
    }
}

template<class T>
void AVLRankedTree<T>::UpdateChildren(AVLRankedNode<T> *node) {
    int left_children = 0;
    int right_children = 0;

    if (node->GetLeft()) {
        left_children = node->GetLeft()->GetChildren();
    }

    if (node->GetRight()) {
        right_children = node->GetRight()->GetChildren();
    }

    node->SetChildren(left_children + right_children + 1);
}

template<class T>
AVLRankedNode<T> *AVLRankedTree<T>::Select(int rank) {
    if (rank <= 0) {
        return nullptr;
    }
    return SelectAux(rank, root);
}

template<class T>
AVLRankedNode<T> *AVLRankedTree<T>::SelectAux(int rank, AVLRankedNode<T> *current) {
    if (current == nullptr) {
        return nullptr;
    }

    int left_children = 0;
    if (current->GetLeft()) {
        left_children = current->GetLeft()->GetChildren();
    }

    if (left_children == rank - 1) {
        return current;
    } else if (left_children > rank - 1) {
        return SelectAux(rank, current->GetLeft());
    } else {
        return SelectAux(rank - (left_children + 1), current->GetRight());
    }
}

template<class T>
int AVLRankedTree<T>::GetTreeSize() {
    if(!root) {
        return 0;
    }

    return root->GetChildren();
}


#endif //WET01_AVLTREE_H













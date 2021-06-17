#include "Agency.h"

Agency::Agency(int id) : id(id), sales(AVLRankedTree<TypeId>()),
                         car_types(AVLRankedTree<TypeIdById>()) {} //edited by ben: initialize the second tree

void Agency::SellCar(int type_id, int sales_count) {

    TypeIdById temp_type_by_id(type_id);
    TypeIdById *target_type_by_id = car_types.Find(
            &temp_type_by_id); //TODO::find target car in id tree, need to check if need to find by num of sales too
    TypeId *target_type_by_sale = nullptr; //TODO:: find target car in sales tree

    if (target_type_by_id == nullptr) { //TODO:: car doesn't exist in ids tree
        target_type_by_id = new TypeIdById(type_id); //TODO:: creating nodes for both trees
        target_type_by_sale = new TypeId(type_id);
    } else {
        TypeId temp_type_id_by_sale(type_id, target_type_by_id->getSalesCount());
        target_type_by_sale = sales.Find(&temp_type_id_by_sale);

        sales.Remove(target_type_by_sale);
        car_types.Remove(target_type_by_id);
    }

    target_type_by_id->Sell(sales_count);
    target_type_by_sale->Sell(sales_count);
    car_types.Insert(target_type_by_id);
    sales.Insert(target_type_by_sale);
}

template<class T>
AVLRankedTree<T> *unite_trees(AVLRankedTree<T> &tree1, AVLRankedTree<T> &tree2) {
    int united_tree_size = tree1.GetTreeSize() +
                           tree2.GetTreeSize();
    T **sorted_united_ts = new T *[united_tree_size];
    typename AVLRankedTree<T>::TreeIterator iterator1 = tree1.BeginFromSmallest();
    typename AVLRankedTree<T>::TreeIterator iterator2 = tree2.BeginFromSmallest();

    int current_index = 0;
    while (*iterator1 != nullptr && *iterator2 != nullptr) {
        if (*(*iterator1) < *(*iterator2)) {
            sorted_united_ts[current_index] = *iterator1;
            ++iterator1;
        } else {
            sorted_united_ts[current_index] = new T(*(*iterator2));
            ++iterator2;
        }
        current_index++;
    }

    while (*iterator1 != nullptr) {
        sorted_united_ts[current_index] = *iterator1;
        ++iterator1;
        current_index++;
    }

    while (*iterator2 != nullptr) {
        sorted_united_ts[current_index] = new T(*(*iterator2));
        ++iterator2;
        current_index++;
    }
    try {
        auto new_tree = new AVLRankedTree<T>(sorted_united_ts, united_tree_size);
        delete[] sorted_united_ts;
        return new_tree;
    } catch (std::bad_alloc &err) {
        delete[] sorted_united_ts;
        throw err;
    }
}

void Agency::unite_agencies(Agency *bigger_agency, Agency *smaller_agency) {
    AVLRankedTree<TypeId> *new_sales_tree = nullptr;
    AVLRankedTree<TypeIdById> *new_ids_tree = nullptr;
    try {
        new_sales_tree = unite_trees(bigger_agency->sales, smaller_agency->sales);
        new_ids_tree = unite_trees(bigger_agency->car_types, smaller_agency->car_types);

        bigger_agency->sales = *new_sales_tree;
        bigger_agency->car_types = *new_ids_tree;

        delete new_sales_tree;
        delete new_ids_tree;
    } catch (std::bad_alloc &err) {
        delete new_sales_tree;
        delete new_ids_tree;
        throw err;
    }
}

template<class T>
void FreeElements(T *element) {
    delete element;
}

Agency::~Agency() {
    sales.InOrderFromSmallest(FreeElements<TypeId>);
    car_types.InOrderFromSmallest(FreeElements<TypeIdById>);

}

int Agency::GetIthSellerId(int i) {
    AVLRankedNode<TypeId> *target_node = sales.Select(i + 1);
    if (!target_node) {
        throw IthSellerDoesNotExist();
    }
    return target_node->GetData()->GetId();
}

/*int Agency::GetWorstSellerId() {
    AVLRankedNode<TypeId> *target_node = sales.GetSmallestNode();
    if (!target_node) {
        throw IthSellerDoesNotExist();
    }
    return target_node->GetData()->GetId();
}*/


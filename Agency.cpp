#include "Agency.h"

Agency::Agency(int id) : id(id), sales(AVLRankedTree<TypeId>()) {}

void Agency::SellCar(int type_id, int sales_count) {
    TypeId temp_type_id(type_id);
    TypeId *target_type_id = sales.Find(&temp_type_id);
    if (target_type_id == nullptr) {
        target_type_id = new TypeId(type_id);
    } else {
        sales.Remove(target_type_id);
    }

    target_type_id->Sell(sales_count);
    sales.Insert(target_type_id);
}

void Agency::unite_agencies(Agency *bigger_agency, Agency *smaller_agency) {
    int united_tree_size = bigger_agency->sales.GetTreeSize() +
                           smaller_agency->sales.GetTreeSize();
    TypeId **sorted_united_type_ids = new TypeId *[united_tree_size];
    AVLRankedTree<TypeId>::TreeIterator bigger_iterator = bigger_agency->sales.BeginFromSmallest();
    AVLRankedTree<TypeId>::TreeIterator smaller_iterator = smaller_agency->sales.BeginFromSmallest();

    int current_index = 0;
    while (*bigger_iterator != nullptr && *smaller_iterator != nullptr) {
        if (*(*bigger_iterator) < *(*smaller_iterator)) {
            sorted_united_type_ids[current_index] = *bigger_iterator;
            ++bigger_iterator;
        } else {
            sorted_united_type_ids[current_index] = *smaller_iterator;
            ++smaller_iterator;
        }
        current_index++;
    }

    while (*bigger_iterator != nullptr) {
        sorted_united_type_ids[current_index] = *bigger_iterator;
        ++bigger_iterator;
        current_index++;
    }

    while (*smaller_iterator != nullptr) {
        sorted_united_type_ids[current_index] = *smaller_iterator;
        ++smaller_iterator;
        current_index++;
    }


    try {
        bigger_agency->sales = AVLRankedTree<TypeId>(sorted_united_type_ids, united_tree_size);
    } catch (std::bad_alloc &err) {
        delete[] sorted_united_type_ids;
        throw err;
    }
    delete[] sorted_united_type_ids;
}

template<class T>
void FreeElements(T *element) {
    delete element;
}

Agency::~Agency() {
    sales.InOrderFromSmallest(FreeElements<TypeId>);
}


int Agency::GetIthSellerId(int i) {
    return sales.Select(sales.GetTreeSize() - i + 1)->GetData()->GetId();
}

int Agency::GetWorstSellerId() {
    return sales.GetSmallestNode()->GetData()->GetId();
}


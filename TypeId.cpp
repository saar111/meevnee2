#include "TypeId.h"

TypeId::TypeId(int id) : id(id), sales_count(0) {}

void TypeId::Sell(int sales_count) {
    this->sales_count += sales_count;
}

bool TypeId::operator<(const TypeId &rhs) const {
    if (sales_count < rhs.sales_count) {
        return true;
    } else if (sales_count == rhs.sales_count) {
        if (id < rhs.id) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool TypeId::operator==(const TypeId &rhs) const {
    return id == rhs.id;
}

int TypeId::GetId() const {
    return id;
}


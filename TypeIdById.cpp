
#include "TypeIdById.h"

TypeIdById::TypeIdById(int id) : id(id), sales_count(0) {}

void TypeIdById::Sell(int sales_count) {
    this->sales_count += sales_count;
}

bool TypeIdById::operator<(const TypeIdById &rhs) const {
    if (id < rhs.id) {
        return true;
    } else {
        return false;
    }
}

bool TypeIdById::operator==(const TypeIdById &rhs) const {
    return id == rhs.id;
}

int TypeIdById::GetId() const {
    return id;
}

int TypeIdById::getSalesCount() const {
    return sales_count;
}

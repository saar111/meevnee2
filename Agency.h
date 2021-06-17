#ifndef WET02_AGENCY_H
#define WET02_AGENCY_H

#include "AVLRankedTree.h"
#include "TypeId.h"
#include <exception>
#include "TypeIdById.h"

class IthSellerDoesNotExist : public std::exception {
};

class Agency {
private:
    int id;
    AVLRankedTree<TypeId> sales;
    AVLRankedTree<TypeIdById> car_types; //TODO::edited by ben: the second sorted by car_types AVL tree
public:
    explicit Agency(int id);
    ~Agency();
    void SellCar(int type_id, int sales_count);
    int GetIthSellerId(int i);
//    int GetWorstSellerId();

    static void unite_agencies(Agency *bigger_agency, Agency *smaller_agency);
};


#endif //WET02_AGENCY_H

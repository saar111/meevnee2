#ifndef WET02_DSW_H
#define WET02_DSW_H

#include "library2.h"
#include "UnionFind.h"
#include "Agency.h"

class DSW {
private:
    UnionFind<Agency> agencies;
    int agencies_count;
public:
    DSW();
    ~DSW();

    StatusType AddAgency();
    StatusType SellCar(int agency_id, int type_id, int k);
    StatusType UniteAgencies(int agency_id1, int agency_id2);
    StatusType GetIthSoldType(int agency_id, int i, int* res);

};


#endif //WET02_DSW_H

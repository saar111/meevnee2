#include "library2.h"
#include "DSW.h"


void *Init() {
    DSW *DS;
    try {
        DS = new DSW();
    } catch (std::bad_alloc &) {
        return NULL;
    }
    return (void *) DS;
}

StatusType AddAgency(void *DS) {
    if (DS == NULL) {
        return INVALID_INPUT;
    }
    return ((DSW *) DS)->AddAgency();
}

StatusType SellCar(void *DS, int agencyID, int typeID, int k) {
    if (DS == NULL) {
        return INVALID_INPUT;
    }
    return ((DSW *) DS)->SellCar(agencyID, typeID, k);
}

StatusType UniteAgencies(void *DS, int agencyID1, int agencyID2) {
    if (DS == NULL) {
        return INVALID_INPUT;
    }
    return ((DSW *) DS)->UniteAgencies(agencyID1, agencyID2);
}

StatusType GetIthSoldType(void *DS, int agencyID, int i, int *res) {
    if (DS == NULL) {
        return INVALID_INPUT;
    }
    return ((DSW *) DS)->GetIthSoldType(agencyID, i, res);
}

void Quit(void **DS) {
    DSW *DSSimple = *(DSW **) DS;
    delete DSSimple;
    *((DSW **) DS) = NULL;
}

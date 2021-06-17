#include <exception>
#include "DSW.h"


DSW::DSW() : agencies(UnionFind<Agency>()), agencies_count(0) {}

StatusType DSW::AddAgency() {
    Agency *new_agency = nullptr;
    try {
        new_agency = new Agency(agencies_count);
        agencies.MakeSet(new_agency);
    } catch (std::bad_alloc &) {
        delete new_agency;
        return ALLOCATION_ERROR;
    }

    agencies_count++;
    return SUCCESS;
}

StatusType DSW::SellCar(int agency_id, int type_id, int k) {
    if (k <= 0 || agency_id < 0) {
        return INVALID_INPUT;
    }

    UnionNode<Agency> *target_agency = agencies.Find(agency_id);
    if (!target_agency) {
        return FAILURE;
    }

    target_agency->GetData()->SellCar(type_id, k);
    return SUCCESS;
}


StatusType DSW::UniteAgencies(int agency_id1, int agency_id2) {
    if (agency_id1 < 0 || agency_id2 < 0) { // TODO: add to library2.cpp relevant INVALID_INPUT part
        return INVALID_INPUT;
    }

    UnionNode<Agency> *target_agency1 = agencies.Find(agency_id1);
    UnionNode<Agency> *target_agency2 = agencies.Find(agency_id2);
    if (!target_agency1 || !target_agency2) {
        return FAILURE;
    }

    agencies.Union(agency_id1, agency_id2, Agency::unite_agencies);

    return SUCCESS;
}

StatusType DSW::GetIthSoldType(int agency_id, int i, int *res) {
    if (agency_id < 0 || res == NULL || i < 0) {
        return INVALID_INPUT;
    }

    UnionNode<Agency> *target_agency_set = agencies.Find(agency_id);
    if (!target_agency_set) {
        return FAILURE;
    }

    try {
        *res = target_agency_set->GetData()->GetIthSellerId(i);
    } catch (IthSellerDoesNotExist &) {
        return FAILURE;
    }
    return SUCCESS;
}

DSW::~DSW() {
    agencies.DeleteInnerData();
}

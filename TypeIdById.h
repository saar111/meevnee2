#ifndef DSW_CPP_TYPEIDBYID_H
#define DSW_CPP_TYPEIDBYID_H


class TypeIdById {
private:
    int sales_count;
    int id;
public:
    explicit TypeIdById(int id);
    void Sell(int sales_count);
    int GetId() const;
    int getSalesCount() const;

    bool operator<(const TypeIdById &rhs) const;
    bool operator==(const TypeIdById &rhs) const;
};


#endif //DSW_CPP_TYPEID_BYID_H

#ifndef WET02_TYPEID_H
#define WET02_TYPEID_H

class TypeId {
private:
    int sales_count;
    int id;
public:
    explicit TypeId(int id);
    TypeId(const TypeId &) = default;
    TypeId(int id, int sales_count);
    void Sell(int sales_count);
    int GetId() const;

    bool operator<(const TypeId &rhs) const;
    bool operator==(const TypeId &rhs) const;
};


#endif //WET02_TYPEID_H

#include <iostream>

#include <iostream>
#include "UnionFind.h"
#include "AVLRankedTree.h"
#include "DSW.h"
#include "library2.h"

void unite_int(int *a, int *b) {
    std::cout << "INSIDE" << std::endl;
}

/*int main() {

    UnionFind<int> bla;
    int a = 5;
    bla.MakeSet(&a);
    int b = 6;
    bla.MakeSet(&b);
    auto k = bla.Find(0);
    auto l = bla.Find(1);
    int c = 7;
    bla.MakeSet(&c);
    int d = 8;
    bla.MakeSet(&d);
    auto aa = bla.Find(3);
    auto ab = bla.Find(4);
    auto ac = bla.Find(5);
    bla.Union(0, 1, unite_int);
    bla.Union(2, 3, unite_int);
    bla.Union(1, 3, unite_int);
    bla.Find(0);


    int x[] = {1, 2, 3, 4, 5};

    AVLRankedTree<int> tree;
    for (int i = 0; i < 6; i++) {

        auto pp = new int(i);
        tree.Insert(pp);
    }

    auto j0 = tree.Select(0);
    auto j1 = tree.Select(1);
    auto j2 = tree.Select(2);
    auto j3 = tree.Select(3);
    auto j4 = tree.Select(4);
    auto j5 = tree.Select(5);
    auto j6 = tree.Select(6);
    auto j7 = tree.Select(7);

    int stop = 1;

    return 0;
}*/

int main() {
    auto dsw = DSW();
    dsw.AddAgency();
    dsw.AddAgency();
    dsw.AddAgency();
    dsw.SellCar(0, 15, 10);
    dsw.SellCar(0, 18, 8);
    dsw.SellCar(1, 25, 2);
    dsw.UniteAgencies(0,1);
    int a;
    int b;
    int c;
    dsw.GetIthSoldType(0, 1, &a);
    dsw.GetIthSoldType(1, 0, &b);
    dsw.GetIthSoldType(1, 1, &c);


    return 0;
}
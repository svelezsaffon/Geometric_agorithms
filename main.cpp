#include <iostream>

#include "math_problems.h"

using namespace std;

int main() {


    line a(point(1,2),point(3,2));
    line b(point(2,2),point(6,2));


    printf("%s\n",(a.intersect(b)==1? "Intersect":"Not Intersect"));





    return 0;
}
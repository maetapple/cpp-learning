#include <stdio.h>
#include <iostream>

int main()
{
    int  origin = 100;
    int& ref    = origin;
    
    std::cout << "ref は origin の参照" << std::endl;
    printf("origin\t %p\t %d\n", &origin, origin);
    printf("ref\t %p\t %d\n", &ref, ref);
    
    
    std::cout << std::endl << "refへの変更はoriginを変更すことと同じ" << std::endl;
    ref = 200;
    
    printf("origin\t %p\t %d\n", &origin, origin);
    printf("ref\t %p\t %d\n", &ref, ref);
    
    return 0;
}
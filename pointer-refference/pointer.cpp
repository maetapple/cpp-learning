#include <stdio.h>
#include <iostream>

int main()
{
    char  memory[4] = {0x1, 0x2, 0x4, 0x8};
    char* p = 0;

    std::cout << "memory[]" << std::endl;
    
    for ( int i=0; i < sizeof(memory)/sizeof(memory[0]); i++ ) {
        
        printf("[%d] %p = %d\n", i, &memory[i], memory[i]);
    }
    
    
    std::cout << std::endl;
    std::cout << "memory[0], [2] にアクセス" << std::endl;
    
    p = &memory[0];
    printf("p=%p\t *p=%d\n", p, *p);
    
    p = &memory[2];
    printf("p=%p\t *p=%d\n", p, *p);

    
    std::cout << std::endl << "先頭から順にアクセス. アドレスは整数だからインクリメントも可能" << std::endl;
    
    for ( p = &memory[0]; p != &memory[4]; p++ ) {
        
        printf("p=%p\t *p=%d\n", p, *p);
    }
    
    return 0;
}
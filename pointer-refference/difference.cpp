#include <stdio.h>
#include <iostream>


struct Parameter
{
    int value;
};


/**
 *  引数がポインタ
 *  nullチェックが必要
 *  アロー演算子でアクセス
 */
void addValue( Parameter* param )
{
    if ( param == 0 ) {
        
        return;
    }
    
    param->value += 100;
}

/**
 *  引数が参照
 *  必ず初期化されている
 *  アクセス方法が変わらない
 */
void addValue( Parameter& param )
{
    param.value += 100;
}


int main()
{
    /**
     *  初期化
     */
    // ポインタは初期化なしで作れる
    int* ptr;
    
    // 参照は必ず参照先の変数で初期化しなければいけない
    int  origin = 100;
    int& ref    = origin;

    // int& ref;        error
    // int& ref = 100;  error
    
    printf("ptr=%p\n", ptr);
    printf("origin\t %p\t %d\n", &origin, origin);
    printf("ref\t %p\t %d\n", &ref, ref);
    std::cout << std::endl;

    
    /**
     *  変数の更新
     */
    // ポインタはアドレスを変更できる
    int dummy = 10;
    
    ptr = &dummy;
    printf("ptr = &dummy\t %p\t %d\n", ptr, *ptr);

    ptr = &origin;
    printf("ptr = &origin\t %p\t %d\n", ptr, *ptr);
    
    // 参照は初期化したら参照先は変更できない
    // これは ref に dummy の値を代入して origin == dummy となる
    ref = dummy;
    printf("ref = dummy\t %p\t %d\n", &ref, ref);
    std::cout << std::endl;

    /**
     *  アクセス方法
     */
    // ポインタは配列インデックスや演算によってアドレスを変更できる
    ptr[3] = 5;
    ptr   += 3;
    printf("ptr\t %p\t %d\n", ptr, *ptr);

    // 参照はできない
    //ref[3] = 5;   error
    ref += 3;    // refの参照先に 3が足される
    printf("ref\t %p\t %d\n", &ref, ref);
    std::cout << std::endl;


    /**
     *  引数としてポインタで渡す
     */
    Parameter param;
    param.value = 0;
    printf("value\t %d\n", param.value);
    
    addValue(&param);
    printf("addValue(Parameter*)\nvalue\t %d\n", param.value);
    
    /**
     *  引数として参照で渡す
     */
    addValue(param);
    printf("addValue(Parameter)\nvalue\t %d\n", param.value);
    
    return 0;
}
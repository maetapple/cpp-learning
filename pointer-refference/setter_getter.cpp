#include <stdio.h>
#include <iostream>


class DataSource
{
public:
    DataSource( int initValue ) : value(0)
    {
        value = initValue;
    };
    
    virtual ~DataSource()
    {};
    
    int* getValuePtr()
    {
        return &value;
    }
    
    int& getValueRef()
    {
        return value;
    }
    
    int value;
};


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
 *  ドット演算子でアクセス
 */
void addValue( Parameter& param )
{
    param.value += 100;
}


/**
 *  むりやりな例
 */
void addValue( int* val )
{
    // 2つ先のアドレスに対して処理しちゃう
    val += 2;
    *val = 100;
}


int main()
{
    // 引数としてポインタで渡す
    Parameter param;
    param.value = 0;
    printf("value\t %d\n", param.value);
    
    addValue(&param);
    printf("addValue(Parameter*)\n value\t %d\n", param.value);
    
    // 引数として参照で渡す
    addValue(param);
    printf("addValue(Parameter)\n value\t %d\n", param.value);
    
    // むりやりな例. [0]を変更したつもりが[2]を変更される
    int values[5] = {0, 0, 0, 0, 0};
    addValue(&values[0]);
    printf("addValue(int*)\n values[0] = %d\n values[2] = %d\n", values[0], values[2]);
    std::cout << std::endl;
    
    
    // ポインタでもらう
    DataSource *source = new DataSource(111);
    printf("new DataSource(111)\n value\t %p\t %d\n", &(source->value), source->value);
    
    int* ptr = source->getValuePtr();
    *ptr += 111;
    printf("getValuePtr()\n ptr\t %p\t %d\n", ptr, *ptr);

    // 参照でもらう
    int& ref = source->getValueRef();
    ref += 111;
    printf("getValueRef()\n ref\t %p\t %d\n", &ref, ref);

    // 受け取る変数が参照じゃないとコピーとなる
    int notRef = source->getValueRef();
    printf("getValueRef()\n notRef\t %p\t %d\n", &notRef, notRef);
    
    delete source;
    
    return 0;
}
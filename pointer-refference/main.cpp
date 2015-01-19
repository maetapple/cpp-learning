#include <stdio.h>
#include <iostream>


class TestData
{
public:
    TestData();
    virtual ~TestData();
    
    void setValue( int val );
    int  getValue();
    int* getValuePointer();
    void printValue();

public:
    int value;
};


TestData::TestData()
: value(0)
{}

TestData::~TestData()
{}

void TestData::setValue( int val )
{
    printf("arg-val \t= %d\t [%p]\n", val, &val);
    
    this->value = val;
}

int TestData::getValue()
{
    return this->value;
}

int* TestData::getValuePointer()
{
    return &(this->value);
}

void TestData::printValue()
{
    printf("TestData::value\t= %d\t [%p]\n", this->value , &this->value);
}


int main()
{
    int value1 = 100;
    
    TestData *data = new TestData();
    
    // 引数としてコピーを作成して渡す
    data->setValue(value1);

    // コピーとして新しいメモリに置く
    int copy = data->getValue();
    
    // アドレスを受け取るのでポインタの分だけメモリに置く
    int* pointer = data->getValuePointer();
    
    printf("value1  \t= %d\t [%p]\n", value1 , &value1);
    printf("copy    \t= %d\t [%p]\n", copy   , &copy);
    printf("pointer \t= %d\t [%p]\n", *pointer, pointer);
    data->printValue();
    
    delete(data);
    
    return 0;
}


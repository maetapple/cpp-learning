ポインター(Pointer)と参照(Refference)
どっちをどう使うのかはその場面によって様々ですが、それを考えるためのヒントとするため２つの違いをメインに記載します。

## Pointer
メモリのアドレス（メモリという配列のインデックス）を扱う型

```cpp:pointer
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
```

```bash:出力結果
memory[]
[0] 0x7fff50763698 = 1
[1] 0x7fff50763699 = 2
[2] 0x7fff5076369a = 4
[3] 0x7fff5076369b = 8

memory[0], [2] にアクセス
p=0x7fff50763698	 *p=1
p=0x7fff5076369a	 *p=4

先頭から順にアクセス. アドレスは整数だからインクリメントも可能
p=0x7fff50763698	 *p=1
p=0x7fff50763699	 *p=2
p=0x7fff5076369a	 *p=4
p=0x7fff5076369b	 *p=8
```


## Refference
ある変数への参照、別名として扱う型

```cpp:refference
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
```

```bash:出力結果
ref は origin の参照
origin	 0x7fff56bcd6a8	 100
ref		 0x7fff56bcd6a8	 100

refへの変更はoriginを変更すことと同じ
origin	 0x7fff56bcd6a8	 200
ref		 0x7fff56bcd6a8	 200
```

## 違い 
#### 初期化
```cpp
// ポインタは初期化なしで作れる
int* ptr;
    
// 参照は必ず参照先の変数で初期化しなければいけない
int  origin = 100;
int& ref    = origin;
// int& ref;		error
// int& ref = 100;	error
```


#### 変数への更新
```cpp
// ポインタはアドレスを変更できる
int dummy = 10;
ptr = &dummy;
ptr = &origin;
    
// 参照は初期化したら参照先は変更できない
// これは ref に dummy の値を代入して origin == dummy となる
ref = dummy;
```

#### アクセス
```cpp
// ポインタは配列インデックスや演算によってアドレスを変更できる
ptr[3] = 5;
ptr   += 3;	// ptr のアドレスを ptr[3] に変更

// 参照はできない
//ref[3] = 5;   error
ref += 3;    // refの参照先に 3が足される
```


## 引数にする
```cpp
struct Parameter
{
    int value;
};

void addValue( Parameter* param )
{
    if ( param == 0 ) {
        
        return;
    }
    
    param->value += 100;
}

void addValue( Parameter& param )
{
    param.value += 100;
}

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
    printf("addValue(Parameter&)\n value\t %d\n", param.value);
    
    // むりやりな例. [0]を変更したつもりが[2]を変更される
    int values[5] = {0, 0, 0, 0, 0};
    addValue(&values[0]);
    printf("addValue(int*)\n values[0] = %d\n values[2] = %d\n", values[0], values[2]);

    return 0;
}
```

```bash:出力結果
value	 0
addValue(Parameter*)
 value	 100
addValue(Parameter)
 value	 200
addValue(int*)
 values[0] = 0
 values[2] = 100
```

* ポインタはNULLチェックが必要
* ポインタはゴニョゴニョできちゃう
* 構造体を引数にする場合、参照だと関数内でアクセス方法が変わらない。
* 引数に`&`をつけなくてもいい => addValue(param)
* でも、呼び出し側だけ見ても参照で渡してるかどうかわからない => addValue(param)


## 戻り値でもらう
```cpp
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

int main()
{
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
```

```bash:出力結果
new DataSource(111)
 value	 0x7fa292404c48	 111
getValuePtr()
 ptr	 0x7fa292404c48	 222
getValueRef()
 ref	 0x7fa292404c48	 333
getValueRef()
 notRef	 0x7fff5700768c	 333
```

* ポインタはNULLを返すことも可能
* 参照なら参照で受けないとコピーになる
* 戻り値が参照かどうか宣言を見ないとわからない？
* 呼び出し側で参照をもらうかコピーしてもらうか選択できる？

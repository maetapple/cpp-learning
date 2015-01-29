## c++実行環境

### Mac
XcodeをインストールすればGCCというコンパイラが入るのでterminalでコンパイルと実行ができる。

### Windows
こんな感じです

http://ringoon.jp/2010/06/16/windows-7-cc.html


## Hello World
*main.cpp*

```cpp:
#include <iostream>

int main() 
{
	std::cout << "Hello World." << std::endl;

	return 0;
}
```

## gcc でコンパイル
terminalを起動して、HelloWorldのファイルmain.cppを保存したディレクトリまで移動

main.cppをコンパイル

```
$ g++ main.cpp -o helloworld
```

helloworldという名前で出力される

```
$ ls
# helloworld	main.cpp
```

## 実行
コンパイルしたファイルを実行

```
$ ./helloworld
# Hello World.
```

## g++ コマンドについて
コンパイルの各オプションなど詳細については以下参照
http://kaworu.jpn.org/cpp/g++

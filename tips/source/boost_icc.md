
# インテルコンパイラーで boost

## boost のコンパイル ##

大体[ここ][1]や[ここ][2]に載っている通り。
`~/boost_***` にファイルを展開した後、 64bit マシンで、

``` shell
source /opt/intel/compilers_and_libraries_***/mac/bin/compilervars.sh intel64
cd ~/boost_***/tools/build
./bootstrap.sh
./b2 install --prefix=~/boost_***
export PATH=$PATH:~/boost_***/bin
cd ~/boost_***
b2 --build-dir=~/boost_***/lib/address-model=64 toolset=intel stage
```

ヘッダーやライブラリを別のところにおいておきたかったので、

``` shell
sudo mkdir -p /opt/boost_***/include
sudo cp -pr ~/boost_***/boost /opt/boost_1_59_0/include/
sudo cp -pr ~/boost_***/stage/lib /opt/boost_1_59_0/
```

## 使う ##

Boost を使う際に、

``` makefile
BOOSTFLAGS = -I/opt/boost_***/include -L/opt/boost_***/lib
```

を用いる。最初 `-std=c++17` のフラグを立ててコンパイルしていたら、`std::align_val_t` の定義がぶつかって
エラーになったので、`-std=c++11` に変更した。多分何かの理解が足りていない。

[1]:https://software.intel.com/en-us/articles/building-boost-with-intel-c-compiler-150
[2]:https://seriousdeveloper.wordpress.com/2015/08/18/building-boost-with-intel-c-compiler-15-0-2/

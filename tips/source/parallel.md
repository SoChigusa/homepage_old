# 並列計算

## for ループで同じ処理を何度も繰り返す場合

シェルスクリプト ＋ c++ のコスパがもっとも良いという結論に至った。
ループが進むごとに異なる入力パラメータを用いて計算したい状況を考慮して、まず以下の下準備をする。

### 実行オプションの設定（boost を使用）

``` c++
#include <boost/program_options.hpp>

using namespace boost::program_options;

int main(const int arg_c, const char *const *const arg_v)
{
  // define options
  options_description description("option");
  description.add_options()
  ("option1", "description of option 1")
  ("option2,o", value<int>()->default_value(0), "description of option 2")
  ...
  ("help,h","help");

  // extract option values
  variables_map vm;
  store(parse_command_line(arg_c, arg_v, description), vm);
  notify(vm);

  if (vm.count("help"))
  {
    std::cout << description << std::endl;
    return 1;
  }
  if (vm.count("option1"))
  {
    ...
  }
  auto o2 = vm["option2"].as<int>();
  ...

  return 0;
}
```

などと書いておけば、 `./a.out --help` で

``` text
option:
  --option1                  description of option 1
  -o [ --option2 ] arg (=0)  description of option 2
  -h [ --help ]            help
```

とヘルプが参照でき、実行時は `./a.out --option1 -o 1` のようにできる。

### 実行オプションを変えつつ複数スレッドで実行

ここからがシェルスクリプトの出番。例えば 4スレッド使ってオプション `-o` に 0~99 の値を渡す計算をしたい場合には、

```shell
#!/bin/bash
if [ $1 -eq 1 ]; then
  LB=0
  UB=24
elif [ $1 -eq 2 ]; then
  LB=25
  UB=49
elif [ $1 -eq 3 ]; then
  LB=50
  UB=74
elif [ $1 -eq 4 ]; then
  LB=75
  UB=99
fi

for o in $(seq $LB $UB)
do
  ./a.out -o $o
done
```

と書いた `run_all.sh` を作っておく。
`$1` はシェルスクリプトに渡された 1つ目の引数なので、1~4 の引数を渡して `run_all.sh` を 4つ同時に走らせれば並列計算が可能。
これを簡単にやるには

```shell
seq 4 | xargs -P 4 -I{} sh ./run_all.sh {}
```

とすれば良い。

## もう少し複雑な計算の場合

まだこれが必要な状況に当たったことがないが、c++ 内部でスレッドを複数立てて完結させることも当然できる。
`std::thread` を使うと良いらしい。
そういえば15年くらい前に[猫でもわかるプログラミングシリーズ](http://www.kumei.ne.jp/c_lang/)で C言語を勉強していた際、なんの役に立つかもわからずにスレッドを複数使って丸をたくさん描くコードを書いたなぁと思い出すなど。多分[この回](http://www.kumei.ne.jp/c_lang/sdk/sdk_87.htm)だね。

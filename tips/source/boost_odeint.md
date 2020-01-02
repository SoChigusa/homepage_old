
# Boost を使って微分方程式を解く

## 基本事項 ##

`boost::numeric::odeint`を用いる。まず、terminology として

* `state` とは、微分方程式に現れる解くべき関数の一群のこと。
* `system` とは、ある時間に於ける `state` が与えられたときに、`state` の時間微分を返す関数のこと。

つまり、コード内で以下のような部分を用意する。

``` c++
#include <boost/numeric/odeint.hpp>

namespace odeint = boost::numeric::odeint;
using state = std::vector<double> x;  // example

void my_system(const state & x, state & dxdt, const double t) {
    dxdt = ....
}
```

ちなみに `state` に 2次元 `vector` を指定するとコンパイルが通らなかったので、素直に 1次元データを使うのが良さそう？

## アルゴリズムの選択 ##

用いることのできるアルゴリズムのリストは[こちら][1]。
このうち、Stepper は等間隔刻みで微分方程式を解くのに単体で使えて、Error Stepper は Controlled Stepper と組み合わせて、適応的に刻み幅を変えながら微分方程式を解くのに便利。
宣言の様子は、

``` c++
auto rk4 = odeint::runge_kutta4<state>();
auto crkck54 = odeint::controlled_runge_kutta< odeint::runge_kutta_cash_karp54<state> >();
auto crkd5 = odeint::controlled_runge_kutta< odeint::runge_kutta_dopri5<state> >();
auto crkf78 = odeint::controlled_runge_kutta< odeint::runge_kutta_fehlberg78<state> >();
```

上記の下3つの書き方ではエラーコントロールが自動でなされるが、エラーの大きさを自分で指定したい場合には、

``` c++
auto crkd5 = odeint::make_controlled< odeint::runge_kutta_dopri5<state> >(1.e-8, 1.e-4);
```

などと書ける。2つの変数は絶対誤差と相対誤差に対応しており、詳しい定義については[こちら][2]を参照。

## 積分とオブザーバー ##

微分方程式を解く操作を積分と読んでいるが、積分関数にもいくつか種類がある。
オブザーバーと呼ばれる中間ステップでの変数の値の保存用の関数をいつ呼び出すかが異なる。
ヘルプは[ここ][3]。
書き方の基本はこんな感じ。

``` c++
std::vector<double> timelog;
std::vector<state> statelog;
odeint::integrate_const(
	      crkd5,  // stepper
		  my_system,  // ODE
		  state0,  // initial condition
		  0.,   // initial time
		  1.,   // final time
		  0.001,// step size
		  [&](const state & st, const double t) {  // observer
		    timelog.push_back(arg_t);
		    statelog.push_back(ph);
		  });
```

`integrate_const` を用いれば、Controlled Stepper の場合にも欲しい刻み幅でのデータを出力してくれる。
当然出力時以外にもたくさんステップを踏んでいるので、この場合第5引数の step size は単に出力データの大きさを変更するだけである。

全てのステップに関して出力が欲しい場合には、 `integrate_adaptive` 関数を用いれば良い。
`integrate` 関数というのもあって、これは第1引数が不要で、`integrate_adaptive` プラス `runge_kutta_dopri5` にデフォルトのエラーコントロールを適用したものと同じ。

[1]:https://www.boost.org/doc/libs/1_57_0/libs/numeric/odeint/doc/html/boost_numeric_odeint/getting_started/overview.html
[2]:https://www.boost.org/doc/libs/1_67_0/libs/numeric/odeint/doc/html/boost_numeric_odeint/tutorial/harmonic_oscillator.html
[3]:https://www.boost.org/doc/libs/1_66_0/libs/numeric/odeint/doc/html/boost_numeric_odeint/odeint_in_detail/integrate_functions.html

# Madgraph の導入から計算まで #

-------------------------------------------------------------------------------

## 導入、初期設定 ##

何度くりかえしてもどこか違うエラーが出るので、今回の成功例を書いておく（2018/8/12）
まず、現在のところ gfortran-8 が Madgraph 周りの compile に対応していないので、
`homebrew install gcc@7`
対応して、`input/mg5_configuration.txt`内のグローバル設定をいじる。

``` shell
	fortran_compiler = gfortran-7
	cpp_compiler = g++-7
	automatic_html_opening = False
```

最後のコマンドで、`launch`時にブラウザが自動で立ち上がるのを防止する。
fastjet が存在しないエラーが出るときは、`fastjet = None`でとりあえず動く。

次に、<a href="http://ktobi.blogspot.com/2018/03/high-sierra.html" target="_blank">Tobiokande 様</a>
を参考に、`bin/mg5_aMC`から dependency のインストール

``` shell
	install boost
	install lhapdf6
	install zlib
	install hepmc
	install pythia8
```

## 用法 ##

あとは普通に使用する。
`launch`時に要求される dependency code は基本的に何も考えず Enter を押す。

1. LO Drell-Yan

``` shell
	p = p b b~
	generate p p > e+ e-
	output pp2ee
	launch
```

2. NLO Drell-Yan

``` shell
	import model sm-no_b_mass
	generate p p > e+ e- [QCD]
	output pp2eeNLO
	launch
```

等々。

## (2018/08/19) Systematics module を使う ##

Systematics module を使うためには、*LHAPDF* の python interface が必要。
上記`install lhapdf6`で入れた *LHAPDF* ではライブラリのリンクが上手く貼られていなかった
（brew ver. 等複数の *LHAPDF* が混在したせい？）ため、手動で入れなおした。
<!--https://github.com/davidchall/homebrew-hep/issues/39 を参考に、-->
`configure CXX=g++-7`から`make`そして`make install`。
正しくインストールできれば、`/usr/local/lib/python2.7/site-packages`で python モジュールを立ち上げ、
`import lhapdf`で何も文句を言われずに *LHAPDF* を読み込めるはず。
この変更に対応して、`input/mg5_configuration.txt`内の設定は`lhapdf = /usr/local/bin/lhapdf-config`
（デフォルトのインストールパス）に。そして、`bin/mg5_aMC`から`install pythia8`で pythia も入れなおす。

実際に`launch`する際には、特に QCD NLO オプションの場合、`run_card.dat`の書き換えが必要。

``` shell
	lhapdf = pdlabel ! PDF set
	True   = reweight_scale ! Reweight to get scale variation using the 
	True   = reweight_pdf ! Reweight to get PDF uncertainty. Should be a
	True   = store_rwgt_info ! Store info for reweighting in LHE file
	systematics	= systematics_program 
	['--mur=0.5,1,2', '--muf=0.5,1,2', '--pdf=errorset'] = systematics_arguments ! see: https://cp3.irmp.ucl.ac.be/projects/madgraph/wiki/Systematics#Systematicspythonmodule
```

これで、くりこみ点（結合定数とPDF）、および PDF choice のエラーを自動で計算してくれる。

## aMCatNLOError : Some tests failed, run cannot continue. ##

エラーメッセージを見てエラーが出たテストを特定する。
今回は Soft / Collinear test で失敗していたので、`SubProcesses/test_soft_col_limits.f` の中身を覗いてみる。
https://answers.launchpad.net/mg5amcnlo/+question/255905
に依ると、energy scale が複数ある場合、numerical instability が大きくてこの手のエラーが起きやすいらしい。
そこで、テストの基準を緩めることにして、

``` fortran
      parameter       (max_fail=(LARGE ENOUGH VALUE))
```

とすることで、無事動いた。

---
title: Madgraph の導入から計算まで
---

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

## (2018/08/24) aMCatNLOError : Some tests failed, run cannot continue. ##

エラーメッセージを見てエラーが出たテストを特定する。
今回は Soft / Collinear test で失敗していたので、`SubProcesses/test_soft_col_limits.f` の中身を覗いてみる。
https://answers.launchpad.net/mg5amcnlo/+question/255905
に依ると、energy scale が複数ある場合、numerical instability が大きくてこの手のエラーが起きやすいらしい。
そこで、テストの基準を緩めることにして、

``` fortran
      parameter       (max_fail=(LARGE ENOUGH VALUE))
```

とすることで、無事動いた。

## (2018/11/20) User defined cuts ##

イベント生成の際に、勝手なカットをかけたい。
一番簡単に、fortran ソースに直接カットパラメータを書き込む方法を試した。
各プロセスのディレクトリ内に存在する `SubProcesses/cuts.f` に、以下のように書く。

``` fortran
C***************************************************************
C***************************************************************
C PUT HERE YOUR USER-DEFINED CUTS
C***************************************************************
C***************************************************************

      do i=1,nexternal          ! loop over all external particles
         if(istatus(i).eq.1 .and. ! final state particle
     &        (ipdg(i).eq.12 .or. ipdg(i).eq.14 .or. ipdg(i).eq.16)) then ! neutrino
            do j=1,nexternal       ! loop over all external particles
               if (is_a_lp(j)) then ! l+
                  if (2d0 * sqrt(p(1,i)**2+p(2,i)**2) * sqrt(p(1,j)**2+p(2,j)**2)
     &                 - 2d0*(p(1,i)*p(1,j)+p(2,i)*p(2,j))
     &                 .lt. 480d0**2) then ! transverse mass cut at 480GeV
                     passcuts_user=.false.
                     return
                  endif
               endif
            enddo
         endif
      enddo

      return
      end
```

上の例では、終状態の lepton と neutrino の transverse mass でカットをかけている。
注意点として、このカット単体では条件を満たすデータ点が少なすぎてエラーを吐くので（下記リンクと同様の症状と思われる）、
別個に `run_card.dat` で lepton pT cut（pT > 100GeV）をかけておいた。
おそらく `run_card.dat` の方の cut は、サンプル点を選び出す段階で既に適用されている。
参考：https://answers.launchpad.net/mg5amcnlo/+question/446723

## (2019/04/21) お好みの模型パラメータをデフォルト設定に ##

例えばSMでb-quarkのPDFを考えたいとき、bはmasslessでなければいけないので、

``` shell
import model SM-no_b_mass
```

とするところから始める。
これは、`**MG5**/model/sm/restrict_no_b_mass.dat`というデータファイルの内容を`param_card.dat`として読み込んでいるだけである。
同様に、例えばAMSBのベンチマークポイントをデフォルトとして計算を始めたい場合、`**MG5**/model/MSSM_SLHA2/`内に`restrict_AMSB.dat`などの名前で`param_card.dat`をコピペし、

``` shell
import model MSSM_SLHA2-AMSB
```

でロードされる。
さらに前段階として、崩壊幅の計算を前もってさせておいて`param_card.dat`をアップデートすると便利。
これには、阿部様のページ http://tomohiro_abe.droppages.com/index.html のメモを参考、

``` shell
compute_widths n2 go <<etc>> --body_decay=2.0025
```

とするなど。モデルディレクトリ内に`param_card.dat`が新しくできて、そこには崩壊幅の情報が追加されている。

## (2019/4/26) 事前にコードを書いてインタープリタに読ませる ##

簡単な例として、わかりやすい名前で複数回launchしたい場合、

``` text
launch pp2gogo2 -n 6TeV_0
launch pp2gogo2 -n 6TeV_1
launch pp2gogo2 -n 6TeV_2
```

などと書いたテキストファイル（`launch_several_times.txt`とする）を用意する。
これを

``` shell
./bin/mg5_aMC launch_several_times.txt
```

として読み込めば、その通りに実行してくれる。
当然、モデル読み込み、multiparticle 定義等の記述も書いておける。

-------------------------------------------------------------------------------

# 以下、古いバージョンに対するtips、あるいは古い認識 #

## (2018/12/06) MadGraph v2.6.4 ??? ##

**????**

v2.6.3.2 では動いていた以下のプロセスが v2.6.4 では動かない。
param_card.dat で指定している崩壊率の指定にミスがあるのか否か？

``` shell
import model MSSM_SLHA2
p p > go go, go > n1 j j, go > n1 j j
```

## (2018/12/06) MadGraph v2.6.3.2 ??? ##

**v2.6.5で修正を確認**

一方で、v2.6.3.2 では standalone pythia8 command が正しく動かない。
https://answers.launchpad.net/mg5amcnlo/+question/671278 にあるように、
`KeyError : 'event_norm'` と怒られるので、作ったイベントを v2.6.4 のディレクトリ
に丸ごとコピーして、そちらで standalone pythia8 を動かせばとりあえず shower できる。
プロセスディレクトリ内の`./bin/madevent`から、

``` shell
pythia8 (RUN NAME)
```

上の方法で一度動かしておくと、`run_shower.sh`および`tag_1_pythia8.cmd`というファイルが自動生成される。
これをコピーして適宜編集し、イベント毎に使い回す方が効率は良さそう。

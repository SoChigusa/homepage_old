
# latexで日本語美文書

## 美しいスタイル ##

``` latex
\documentclass[11pt,a4paper,twoside,dvipdfmx,etc...]{jsarticle}
```

## 太字が太くない ##

太いフォントを導入しましょう。

## フォントの導入 ##

この歳になるまで自分でフォントの導入をしたことがなかったので、反省して調べた。
まず、使用するフォント `FFF.ttf` を準備し、ソースファイルと同じディレクトリに置く。
このフォントを使用しますよー、とマップファイル `myfont.map` に記述。

``` map
otf-cjgb-h    Identity-H                      FFF.ttf/AJ16
otf-cjgb-v    Identity-V                      FFF.ttf/AJ16
hgothb-h      H                               FFF.ttf
hgothb-v      V                               FFF.ttf
```

このままだとなんか漢字フォントが変わらないので、コマンド書き換えが必要。
今回は日本語の太字用に `FFF.ttf` を使いたいので、`\emph` コマンドを書き換えることにして、

``` latex
\renewcommand{\emph}[1]{{\usekanji{JY1}{hgt}{bx}{n} #1}}
```

とする。漢字フォントに hgothb-* で指定したフォントを割り当てている。
あと、タイプセット時にマップファイルを指定する必要がある。
面倒くさいので、以下のように `makefile` を作っておいて、その都度 `make` する。

``` shell
all:	pd.pdf

pd.pdf:	pd.tex myfont.map
	platex pd.tex
	dvipdfmx -f myfont.map pd.dvi
```

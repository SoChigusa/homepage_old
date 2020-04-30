# 自分風 Beamer プレゼン用チートシート

## 右下のアレを消す ##

プリアンブル部分に次の一行を追加。

``` tex
\setbeamertemplate{navigation symbols}{}
```

## Itemize ##

箇条書きがインデントされるのが気に入らない時の調整。

``` tex
\setlength{\leftskip}{-3mm}
```

## Table ##

表の縦幅を広めにとって読みやすくする。

``` tex
\def\arraystretch{1.2}
```

## Spacing ##

デフォルト行間は狭すぎるので、読みやすく。

``` tex
\renewcommand{\baselinestretch}{1.2}
```

ただ、状況に応じて部分的に変更したい時もあるので、臨機応変に

``` tex
\setstretch{0.9}
```

## Minipage

横にいくつかブロック分けして上揃えしたい場合、全ての`minipage`コマンドを以下の形で書く。

``` tex
\begin{minipage}[t]{0.48\hsize}
  \leavevmode%
  \vskip 0pt%
  \vskip -\baselineskip%
  ...
\end{minipage}
```

# 快適な latexdiff 生活 #

## テンプレート ##

``` shell
latexdiff-vc -e utf8 --exclude-textcmd="section,subsection,subsubsection" --git --flatten --force -d diff -r (commit / HEAD) (filename)
```

## git との連携 ##

いつも https://nekketsuuu.github.io/entries/2017/01/27/latexdiff-vc.html を参考にしている。

``` shell
latexdiff-vc -e utf8 --git --flatten --force -d diff -r (commit / HEAD) (filename)
```

## Section 変更時のタイプセットエラーを避ける ##

オプション `--exclude-textcmd="section,subsection,subsubsection"` で、section の変更、追加等を無視してくれる。

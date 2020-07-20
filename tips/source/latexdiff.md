
# 快適な latexdiff 生活

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

## 複雑な数式を変更した際のエラーを避ける

オプション `--math-markup=whole` で、変更のある数式は全体を色付けする対応をとる。これでもエラーが避けられない場合もあり、数式の変更点を諦めても良いなら `--math-markup=off` が使える。

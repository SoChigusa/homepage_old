---
title: Mac OS Mojave アップデートとアフターケア
---

-------------------------------------------------------------------------------

## emacs ダークモード ##

ダークモードを使用するように変更し、それに合わせて emacs のテーマを変更した。
ダーク系のテーマを選択し、 `~/.emacs.el` の末尾に以下のように追加。

``` emacs-lisp
;;====================================
;;; Theme
;;====================================
(load-theme 'manoj-dark t)
```

## c++ 開発環境 ##

理由をよく理解していない、`math.h` が見つからないエラーが出たので、以下の URL を参考に修正。

* https://github.com/RcppCore/Rcpp/issues/922

ターミナルから、

``` shell
sudo installer -pkg \
/Library/Developer/CommandLineTools/Packages/macOS_SDK_headers_for_macOS_10.14.pkg \
-target /
```

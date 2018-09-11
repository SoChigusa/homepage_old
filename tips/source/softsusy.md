# SOFTSUSY の導入 #

#### （ほぼ `automake` の勉強と同義） ####

ひとまず、環境に存在しなかった `autoconf` および `automake` を導入。

``` shell
brew install autoconf
brew install automake
```

問題なのは、SOFTSUSY の要求する `automake` のバージョンと上記で導入した
`automake` のバージョンがしばしばずれていること。
典型的には、"automake-1.14: command not found" とか言われる。（2018/09/12）
これを避けるために、暫定的に Makefile の "automake-1.14" をマシンに存在する
バージョン番号に書き換えて `make` を通している。

（もっと `automake` の勉強をすればより根本的な解決法がある気がする。
`./configure` 前に `aclocal` という方法を試したけれど、とりあえず上手くいかなかった）

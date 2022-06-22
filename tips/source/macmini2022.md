
# Macbook Air (2020) M1チップ

## 序説

ポスドクとして雇われ始めた当初はコロナ禍真っ只中で通勤もままならず、オフィスではデスクトップPC派の自分がパソコンを買ってもらうまでに実に1年半も要してしまった。
ともあれ、今回買ってもらったものは Mac mini (2022) M1チップ搭載モデル、macOS 12 Monterey、16GBメモリ、512GB SSD。
これはその際の環境構築の自分用メモである。

[2年前のM1 macの環境構築](macbookair2020.html)の際と比べて、ほとんどのアプリがデフォルトで M1 チップに対応するようになっている分、環境構築は非常に簡単だと感じた。

## 環境構築

### ワイヤレスキーボード、トラックパッド、マウスの接続

logicool製のキーボード・マウスを使用しているので[Logicool Options](https://www.logicool.co.jp/ja-jp/product/options)をインストール。

### Xcode

App Storeからインストールする。
その後、以下の通り Command Line tools をインストール。

``` shell
xcode-select --install
```

### Rosetta

インテルプロセッサー用のアプリを実行するためのエミュレーターである Rosetta 2。
今のところ必要な状況に直面していない。

### Homebrew

[公式サイト](https://brew.sh/index_ja)の言うとおり、

``` shell
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

でインストールできる！　
2年前の苦労が嘘のような簡単さ。

### Homebrewを使って色々インストール

#### root

Homebrew で以下の通り

``` shell
brew install root
```

してインストールできる v6.26/04 が問題なく動く。

#### MacTeX

今回は GUI 無しバージョンを Homebrew で入れてみた。

``` shell
brew install mactex-no-gui --cask
```

#### Inkscape

``` shell
brew install inkscape
```

そして[設定を行う](inkscape.html)。

### Anaconda

python のバージョン管理、および JupyterLab などを使うために Anaconda を導入している。
[公式サイト](https://www.anaconda.com/products/distribution#Downloads)にある通り、M1 チップ用の GUI 版のディストリビューションがあるのでそれをインストールする。問題なく動く。

### Mathematica

ライセンスが新しいコンピューターで利用可能か確認中。

### VSCode

環境構築のタイミングに乗じて VSCode を使い始めた。
[公式サイト](https://code.visualstudio.com/download)の Mac OS X 用インストーラーは M1 チップにも対応している。問題なく動く。

### SNS

* [Zoom](https://zoom.us/download)をインストール、動く。
* [Skype](https://www.skype.com/ja/get-skype/)をインストール、動く。
* [slack](https://slack.com/downloads/mac)をインストール、動く。

### その他便利ツール

* [DeepL](https://www.deepl.com/app)、動く。
* [Grammarly](https://www.grammarly.com/desktop/mac)、動く。

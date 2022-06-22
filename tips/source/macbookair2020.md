
# Macbook Air (2020) M1チップ

## 注意

M1 mac のセットアップについて、最新版の記事は→[Mac mini (2022) M1チップ](macmini2022.html)。
この記事から2年の時を経て、あらゆるアプリが M1 チップにデフォルトで対応しており、セットアップは比較的簡単になっていた。
最新版の記事のやり方で上手くいかなければ、古い方のこちらの記事に何らかのヒントがある、かも？

## 序説

M1の頃に購入した2015年モデルMacbook Airから、5年ぶりにノートパソコンを買い替えた。
購入したものはMacbook Air(2020) M1チップ搭載モデル、macOS 11 Big Sur、8GBメモリ、256GB SSD。
これはその際の環境構築の自分用メモと動作・不具合報告、および5年分の進化に対する感想。
環境構築の部分に関しては時系列で記してあり、ものによっては上から順にクリアすることが必要。

## 環境構築

### ワイヤレスキーボード、トラックパッド、マウスの接続

古いMacbook Airの方の接続を切って、新しい方に接続し直し。
logicool製のマウスを使用しているので[Logicool Options](https://www.logicool.co.jp/ja-jp/product/options)もインストール。

### Xcode

[こちら](https://qiita.com/aiorange19/items/5ffaefc85f912f60c2fa)のQiitaを参考に、App Storeからインストールする。
Xcode起動後のメニューから[この](https://developer.apple.com/download/more/?=for%20Xcode)サイトに飛び、Command Line tools for Xcode 12.3をインストール。

### Rosetta

インテルプロセッサー搭載Mac用のアプリを実行するためにRosetta 2が[必要](https://support.apple.com/en-us/HT211861)。
該当のアプリ（例えばXcode）の起動時にRosettaが必要だというメッセージが出てくるので、インストールボタンをクリックするだけ。

### Homebrew

[公式サイト](https://brew.sh/2020/12/01/homebrew-2.6.0/)によると、12/1リリースのHomebrew 2.6.0からmacOS Big Surに対応したとのこと。
[こちら](https://qiita.com/shira-shun/items/0f6213f4923cb5544367)の「対策1」を元に、まずターミナルをRosettaを使用して起動するように設定する。
（このステップにかなり本末転倒の感があるので、おいおい後述の「対策2」のやり方が確立すると良いな、とは思う。）
そのあと[公式サイト](https://brew.sh/index_ja)の言うとおり、

```
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

でインストールできる。

#### Rosettaを使わない方法（未解決）

macOS ARMでは`/opt/homebrew`へのインストールが要請されているので、数ステップ必要。
[こちら](https://qiita.com/aiorange19/items/5ffaefc85f912f60c2fa)そのまんまだが、まとめると

```
cd /opt
sudo mkdir homebrew
sudo chown -R $USER /opt/homebrew
curl -L https://github.com/Homebrew/brew/tarball/master | tar xz --strip 1 -C homebrew
cd
echo 'export PATH=/opt/homebrew/bin:$PATH' >> .zshrc
source .zshrc
```

これでインストールは完了して使えるようになるのだが、僕の場合は`root`のインストールで詰まった。
そのとき返ってきたエラーメッセージいわく、macOS ARMにはまだ対応していないからRosettaを使って`brew`をインストールしなおしなさい、とのこと。

### Homebrewを使って色々インストール

#### root

v.6.22/06がmacOS ARMに[対応している](https://root-forum.cern.ch/t/root-v6-22-06-release/42575)。
このバージョンを`brew`でインストール可能。
インストールしたものを動かそうとすると、`Command Line tools`がないと怒られる。
原因はパスの情報の食い違いで、そのうちXcode側のアップデートで修正が期待されるが、対症療法としては[こちら](https://developer.apple.com/forums/thread/667561)にあるとおり（でもこのリンクのコマンド間違ってない？）

```
sudo ln -s /Library/Developer/CommandLineTools/SDKs/MacOSX11.1.sdk /Library/Developer/CommandLineTools/SDKs/MacOSX11.0.sdk
```

無事に起動できることを確認。

#### その他

* [boost](https://formulae.brew.sh/formula/boost)、動作確認。

### LaTeX環境

#### MacTeX

[公式サイト](https://www.tug.org/mactex/aboutarm.html)にあるとおり、現行の2020年版はRosetta上での動作を保証、2021年4月にリリース予定の次期バージョンでARMがサポートされるよう。
[ここ](https://www.tug.org/mactex/mactex-download.html)からインストーラーを手に入れてインストールする。

#### TeXShop

12/11にリリースされたv 4.55がmacOS ARMにも[対応している](https://pages.uoregon.edu/koch/texshop/)。
動作確認済み。

### python

デフォルトで`python3`を使いたいので、

```
echo 'alias python=python3' >> ~/.zshrc
source ~/.zshrc
```

よく使うパッケージ`numpy`や`matplotlib`等のインストール。
上記のとおりターミナルをRosettaを使って起動した上で、

```
sudo pip3 install numpy
sudo pip3 install --upgrade setuptools
sudo pip3 install matplotlib
```

など。動作確認済み。

#### Rosettaを使わない方法（未解決）

この場合、`numpy`等のパッケージのビルドの段階でエラーが出て先に進まない。
詳しくは[こちら](https://github.com/scipy/scipy/issues/13102)で議論されているとおりで、wheelをマニュアルダウンロードしてきて名前を変更して使うなどの小細工はあれど、根本的な解決法は12/11時点でまだなさそう。
僕の環境では小細工でインストールは完了したが、実行時にエラーが出た。
`pip`のアップデートによってmacOS ARMに対応すれば、改善するかも？

### Mathematica

ライセンスが新しいコンピューターで利用可能か確認中。

### Atom

[公式サイト](https://atom.io)から、v1.53.0をインストール。
問題なく動く。
[自分のメモ](atom.html)を参考にお気に入りのパッケージも揃える。

### Inkscape

`homebrew`を使って最新版をインストール。
[自分のメモ](inkscape.html)を参考にパッケージを導入してLaTeXの入力も可能になる。

### SNS

* [Zoom](https://zoom.us/download)をインストール、動く。
* [Skype](https://www.skype.com/ja/get-skype/)をインストール、動く。
* [slack](https://slack.com/downloads/mac)をインストール、全てのワークスペースを一括でアプリに追加する方法がわからずたくさんクリックする、面倒だったが動く。
* [Sococo](https://app.sococo.com/a/download)（バーチャルオフィスアプリケーション）をインストール、動く。
* [Line](https://apps.apple.com/us/app/line/id539883307?mt=12)をインストール、動く。

### カレンダー

環境設定からアカウントを追加し、Googleカレンダーと同期して使っている。

### git remote

#### Bitbucket

リモートリポジトリからクローンしてくる際に、SSH認証鍵の設定が必要。
[こちら](https://qiita.com/0084ken/items/e763c85054a5a1e2cc6c)を参考に、鍵を作って公開鍵をアカウントと紐付ける。

### その他便利ツール

翻訳ツールの[DeepL for Mac](https://www.deepl.com/app)、英語の文法チェックツールの[Grammarly for Mac](https://www.grammarly.com/native/mac)

### Parallels Desktop

dualboot用にParallels Desktopを使っている。
現在のバージョンではM1チップ搭載のMacに[対応していないよう](https://www.parallels.com/blogs/parallels-desktop-apple-silicon-mac/)で、残念ながらまだ動作させられていない。
新バージョンが鋭意開発中とのこと。

## 不具合？

* c++の`std::mktime`関数の挙動がおかしい。ランダムに数年単位で日付がズレるように見える。

## 買い替えた感想

* 5年前と比べて、同じ値段でメモリもストレージも倍のものが手に入るようになっている。決して物価が下がったわけではない。
* 起動音が古いMacbook Airのものより3音くらい低くてびっくりした。
* 存在すら知らなかった最新OS（macOS Big Sur）がデフォルト搭載。
* いちいちパスコードを入力しなくて良いTouch IDが便利。
* USB Aの端子がないせいで色んなものが接続できない。
* iMacも持っていて知ってはいたけど、やはりRetinaディスプレイは綺麗。
* zshとbashの違いとは？ と思っていたら、カレントディレクトリ名の後に表示される % がすごく気になる。
* 電池めっちゃもつ。

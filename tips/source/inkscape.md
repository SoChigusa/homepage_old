
# Inkscape w/ LaTeX

Inkscape はフリーのドローソフトの最高峰である（自分比）。
知名度の高さから多くのextensionも用意されており、その中の一つである`EqTeXSVG`を用いることで、LaTeX形式で入力した数式を図に書き込める。

## インストール for Mac

アプリケーションディレクトリに放り込むだけのインストール方法も可能だが、extensionフォルダの場所がわからなかったので、`homebrew`で入れ直した。

```shell
brew update
brew cask install inkscape
```

## EqTeXSVGの導入

前準備として`pstoedit`が必要になるのでインストール。

```shell
brew install pstoedit
```

これでパスも通っているはず。`EqTeXSVG`の[公式サイト](https://www.julienvitard.eu/en/eqtexsvg_en.html)にある通り、extensionのファイルをcloneしてきてextensionフォルダにコピーする。

```shell
git clone https://github.com/julienvitard/eqtexsvg.git
cp eqtexsvg/eqtexsvg.* ~/.config/inkscape/extensions/
```

extensionフォルダの場所が非自明だったが、自分の環境では[このページ](https://tesselace.com/2017/10/31/inkscape-on-mac-os-x/)の情報と同じだった。
動かしたいときは、Inkscapeのメニューの`Extensions>Render>LaTeX formula`から。

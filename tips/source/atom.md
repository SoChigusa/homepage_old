# Atom の導入とカスタマイズ

個人的には、プレビューも含めてエディター内で完結させることができ、環境の構築が楽なところが大きなメリットだと思う。
使い勝手に関しては随時検証しつつ報告する。

## Shell

全ての作業をエディター内で完結させることを目指す。[この辺](https://blanche-toile.com/web/atom-platformio-ide-terminal)を参考に、platformio-ide-terminalを用いた。

## Markdown 環境の構築

[このQiita](https://qiita.com/kouichi-c-nakamura/items/5b04fb1a127aac8ba3b0)によくまとまっている。
リストされた必要な、あるいは便利そうなパッケージをインストールして、環境が出来上がった。欲を言えば数式環境を使いたかったり、
`pandoc`と連携して欲しかったりしたので、ちょうど良いプレビューパッケージを探して、`markdown-preview-enhanced`に辿り着いた。
便利さは、例えば[ここ](https://qiita.com/tomo_makes/items/da4e8fe7d8cf168b545f)参照。
こちらのパッケージだと、`markdown-scroll-sync`を入れなくても原稿とプレビューのスクロールを同期してくれるのも便利。

## html 環境の構築

htmlを編集するための環境、特に自動補完はデフォルトで備わっている機能が十分優秀である。
編集と同時にプレビューしながら作業を進めるために、`atom-html-preview`を導入。

## Latex 環境の構築

latex をタイプセットできる環境が整っていれば、特にやることはない。
[ここ](https://qiita.com/kurohune538/items/6c1e48f6380b87fd8161) や
[ここ](https://qiita.com/ken0nek/items/f98f88c9c45d8499786e)
から自分に必要なパッケージを選択し、インストールした。

さらに、BibTeX環境も含めた自動コンパイルのために、今回は`latexmk`を活用した。
例えば[ここ](http://joban.wp.xdomain.jp/archives/151)にあるように、`.latexmkrc`を作成しておき、

```shell
latexmk -c $(FILENAME)
```

とするか、ディレクトリ内にlatexファイルが1つしかなければファイル名は省略可。

また、PDFの閲覧もatom内で完結させるために`pdf-view`を導入する。
**（2021/12/6 追記）** ある時期から2枚目以降のPDFが表示されない（black screenになる）バグに悩まされていたが、[こちら](https://github.com/izuzak/atom-pdf-view/issues/239)のissueに従って"fit to width on open"のオプションをオフにすることで解決した。

## c / c++ 開発環境の構築

最低限の環境は初めから揃っている（`langauge-c`）が、`clang-format`を用いたソースの整形が自動でなされるようにしておくと便利。
`clang-format`は[ここ](http://yasuharu519.hatenablog.com/entry/2015/12/13/210825)を参考にインストール。
ソースコードの保存と同時に整形されるよう、`atom-beautify`パッケージを導入して設定する。
インストールされたソース内に仕様変更に基づくエラーが1箇所あるので、[ここ](https://github.com/Glavin001/atom-beautify/issues/2290)に従って書き換えた。
つまり、Atom > 環境設定 > 設定フォルダを開くから参照できる`packages/atom-beutify/src/beautifiers/clang-format.coffee`の84行目（周辺）を

```shell
return @exe("clang-format").run([
  @dumpToFile(dumpFile, text)
  ["--style=file"]
  ]).finally( ->
    fs.unlink(dumpFile, ->)
  )
```

とすれば良い。
ここら辺の話やその他便利なパッケージは[こちら](https://qiita.com/prickle/items/2a8f87fba7f6e1d8f051)を参考にした。
`autocomplete-clang`（補完）、`atom-ctags`（定義箇所へのジャンプ）、`docblockr`（ブロックコメント）、`indent-guide-improved`（eye guide）、`jumpy`（コード内移動）を試している。

## python 開発環境の構築

[こちら](https://www.sejuku.net/blog/76158)を参考に、python 実行用の `atom-runner` を導入。
`atom-beauty` が python でも使用可能だが、そもそもインデントに厳しい言語で auto beautify は鬱陶しいだけなので off にする。
`Hydrogen` パッケージを用いて `jupyter` カーネルも使えるようになるらしいが、まだ活用できていない。

## その他便利なパッケージ

ファイルの種類をアイコンで区別できるようになる`file-icons`や、編集中の箇所がわかりやすくなる`minimap`。
矩形選択を可能にする`sublime-style-column-selection`。

## アンインストールの方法

いろいろな設定ファイルがいろいろな場所に散らばっているので存外面倒くさい。
アプリケーションフォルダ内のアプリを消去するのに加えて、例えば[ここ](https://qiita.com/ishizukih/items/9467473e5562ba940c65)にあるように

```shell
rm -rf ~/.atom
rm -rf /usr/local/bin/atom
rm -rf /usr/local/bin/apm
rm -rf /Applications/Atom.app
rm -rf ~/Library/Preferences/com.github.atom.plist
rm -rf ~/Library/Application\ Support/com.github.atom.ShipIt
rm -rf ~/Library/Application\ Support/Atom
rm -rf ~/Library/Saved\ Application\ State/com.github.atom.savedState
rm -rf ~/Library/Caches/com.github.atom
rm -rf ~/Library/Caches/com.github.atom.Shipit
rm -rf ~/Library/Caches/Atom
```

とする。

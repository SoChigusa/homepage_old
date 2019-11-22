
# Atom の導入とカスタマイズ

個人的には、プレビューも含めてエディター内で完結させることができ、環境の構築が楽なところが大きなメリットだと思う。
使い勝手に関してはこれから検証する。

## Shell

全ての作業をエディター内で完結させることを目指す。[この辺](https://blanche-toile.com/web/atom-platformio-ide-terminal)を参考に、platformio-ide-terminalを用いた。

## Markdown 環境の構築

[このQiita](https://qiita.com/kouichi-c-nakamura/items/5b04fb1a127aac8ba3b0)によくまとまっている。
リストされた必要な、あるいは便利そうなパッケージをインストールして、環境が出来上がった。欲を言えば数式環境を使いたかったり、
`pandoc`と連携して欲しかったりしたので、ちょうど良いプレビューパッケージを探して、`markdown-preview-enhanced`に辿り着いた。
便利さは、例えば[ここ](https://qiita.com/tomo_makes/items/da4e8fe7d8cf168b545f)参照。
こちらのパッケージだと、`markdown-scroll-sync`を入れなくても原稿とプレビューのスクロールを同期してくれるのも便利。

## Latex 環境の構築

latex をタイプセットできる環境が整っていれば、特にやることはない。
[ここ](https://qiita.com/kurohune538/items/6c1e48f6380b87fd8161) や
[ここ](https://qiita.com/ken0nek/items/f98f88c9c45d8499786e)
から自分に必要なパッケージを選択し、インストールした。

さらに、BibTeX環境も含めた自動コンパイルのために、今回は`latexmk`を活用した。
例えば[ここ](http://joban.wp.xdomain.jp/archives/151)にあるように、`.latexmkrc`を作成しておき、

``` shell
latexmk -c $(FILENAME)
```

とするか、ディレクトリ内にlatexファイルが1つしかなければファイル名は省略可。

## c / c++ 開発環境の構築

最低限の環境は初めから揃っている（`langauge-c`）が、`clang-format`を用いたソースの整形が自動でなされるようにしておくと便利。
`clang-format`は[ここ](http://yasuharu519.hatenablog.com/entry/2015/12/13/210825)を参考にインストール、設定する。
インストールされたソース内に仕様変更に基づくエラーが1箇所あるので、[ここ](https://github.com/Glavin001/atom-beautify/issues/2290)に従って書き換えた。
つまり、`clang-format.coffee`の84行目（周辺）を

``` shell
return @exe("clang-format").run([
  @dumpToFile(dumpFile, text)
  ["--style=file"]
  ]).finally( ->
    fs.unlink(dumpFile, ->)
  )
```

とすれば良い。
ソースコードの保存と同時に整形されるよう、`atom-beautify`パッケージを導入して設定する。
ここら辺の話やその他便利なパッケージは[こちら](https://qiita.com/prickle/items/2a8f87fba7f6e1d8f051)を参考にした。
`autocomplete-clang`（補完）、`atom-ctags`（定義箇所へのジャンプ）、`docblockr`（ブロックコメント）、`indent-guide-improved`（eye guide）、`jumpy`（コード内移動）を試している。

## python 開発環境の構築

[こちら](https://www.sejuku.net/blog/76158)を参考に、python 実行用の `atom-runner` を導入。
`atom-beauty` が python でも使用可能だが、そもそもインデントに厳しい言語で auto beautify は鬱陶しいだけなので off にする。
`Hydrogen` パッケージを用いて `jupyter` カーネルも使えるようになるらしいが、まだ活用できていない。

## その他便利なパッケージ

ファイルの種類をアイコンで区別できるようになる`file-icons`や、編集中の箇所がわかりやすくなる`minimap`。


# VS Code の環境構築とチートシート

##　経緯

[GitHub 社が Atom の開発終了をお知らせした](https://forest.watch.impress.co.jp/docs/news/1415735.html#:~:text=%E7%B1%B3Microsoft%E5%82%98%E4%B8%8B%E3%81%AEGitHub,%E3%83%97%E3%83%AD%E3%82%B8%E3%82%A7%E3%82%AF%E3%83%88%E3%81%AF%E3%82%A2%E3%83%BC%E3%82%AB%E3%82%A4%E3%83%96%E3%81%95%E3%82%8C%E3%82%8B%E3%80%82)のを良いタイミングだと思って、VS Code に乗り換えることにした。

## VS Code

`homebrew` でインストールが可能。

``` shell
brew install visual-studio-code --cask
```

### 基本操作

Atom と操作が似ている部分が多くて馴染みやすかった（どっちが真似したんだ？）。

- `Cmd + Shift + p` でコマンドパレットを開ける。
- 画面下部から引き出してこれるウィンドウでターミナルの操作や各種エラーログの確認が可能。
- グローバル設定は `Cmd + ,` の設定画面、あるいはその右上をクリックして開く `settings.json` で編集する。
- キーバインド設定は `Cmd + k` + `Cmd + s` のキーボードショートカット画面、あるいはその右上をクリックして開く `keybindings.json` で編集する。
- 左側のサイドバーから git リポジトリの操作が可能。
- 左側のサイドバーから拡張機能メニューを開いて色々とインストールしていく。

### 設定

`settings.json` （あるいは設定画面）を使ってエディターの共通設定をいくつか変更。

``` json
"editor.mouseWheelScrollSensitivity": 0.6,
"editor.tabSize": 2,
"editor.wordWrap": "on",
"editor.formatOnSave": true,
```

上から順に
- スクロールを少し遅くした。
- タブに対応するスペースの数は2つ。
- エディター画面の右端で折り返す。
- 保存するたびに整形する。

### チートシート

- 折り返し設定のファイルごと変更 `Alt + z`

## スペル・文法チェック

スペルチェック用に `Code Spell Checker` を導入した。
スペルミスした部分が青波線で表示され、以下の操作により修正できるようになる。

### チートシート

- スペル修正 `Cmd + .` 出現するダイアログから正しい単語を選ぶ。
- プロジェクト辞書・ユーザー辞書の更新：上記のダイアログの最後２つの選択肢。

## LaTeX 環境構築

`latexmk` を使用する場合、（未設定ならば）設定ファイルを作成する。
今回は `upLaTeX` 用のグローバル設定を `~/.latexmkrc` に作って

``` .latexmkrc
$latex = 'uplatex %O %S';
$bibtex = 'upbibtex %O %B';
$dvipdf = 'dvipdfmx %O -o %D %S';
$max_repeat = 10;
```

としておいた。

VS Code 側では、最も有名な拡張機能である `LaTeX Workshop` をインストールする。
`settings.json` の内容は [ここ](https://qiita.com/rainbartown/items/d7718f12d71e688f3573)や[ここ](https://qiita.com/t_kemmochi/items/dd38bbf2b823c770d1ec)を参考に、こんな感じ。

``` json
// ---------- Language ----------
"[tex]": {
    // スニペット補完中にも補完を使えるようにする
    "editor.suggest.snippetsPreventQuickSuggestions": false
},
"[latex]": {
    // スニペット補完中にも補完を使えるようにする
    "editor.suggest.snippetsPreventQuickSuggestions": false
},
// ---------- LaTeX Workshop ----------
// 使用パッケージのコマンドや環境の補完を有効にする
"latex-workshop.intellisense.package.enabled": true,
// 生成ファイルを削除するときに対象とするファイル
"latex-workshop.latex.clean.fileTypes": [
    "*.aux",
    // "*.bbl",
    "*.blg",
    "*.idx",
    "*.ind",
    "*.lof",
    "*.lot",
    "*.out",
    "*.toc",
    "*.acn",
    "*.acr",
    "*.alg",
    "*.glg",
    "*.glo",
    "*.gls",
    "*.ist",
    "*.fls",
    "*.log",
    "*.fdb_latexmk",
    "*.snm",
    "*.nav",
    "*.dvi",
    // "*.synctex.gz"
],
// ビルドのレシピ
"latex-workshop.latex.recipes": [
    {
        "name": "pdflatex ➞ bibtex ➞ pdflatex x 2",
        "tools": [
            "pdflatex",
            "bibtex",
            "pdflatex",
            "pdflatex"
        ]
    },
    {
        "name": "latexmk (uplatex)",
        "tools": [
            "latexmk-uplatex"
        ]
    }
],
// ビルドのレシピに使われるパーツ
"latex-workshop.latex.tools": [
    {
        "name": "latexmk-uplatex",
        "command": "latexmk",
        "args": [
            "-synctex=1",
            "-interaction=nonstopmode",
            "-file-line-error",
            "-pdfdvi",
            "%DOC%"
        ],
        "env": {}
    },
    {
        "name": "pdflatex",
        "command": "pdflatex",
        "args": [
            "-synctex=1",
            "-interaction=nonstopmode",
            "-file-line-error",
            "%DOC%"
        ]
    },
    {
        "name": "bibtex",
        "command": "bibtex",
        "args": [
            "%DOCFILE%"
        ]
    }
],
```

クリーン時に削除されるファイルのリストでは、`latexdiff-vc` や論文の投稿に必要な `*.bbl` ファイルと、sync に必要な `*.synctex.gz` ファイルは除外している。
`recipes` は `*.tex` ファイルのビルドに使われるコマンド群を指定しており、各コマンドの詳細を `tools` が指定している。
デフォルトでは一番上のレシピである `pdflatex` が使われ、コマンドパレットから `Build with recipe` を選ぶことで `latexmk + uplatex` も使えるようになっている。

### スニペットの登録

左下の歯車から、ユーザースニペットの構成、`latex` と進み、`latex.json` を作成する。
この中にテンプレートを登録しておくことで、次回から簡単に呼び出せるようになる。ひとまず Referee report への返答中だったので、これを登録してみる。

``` json
"Referee Reply": {
  "prefix": "reply",
  "body": [
    "\\documentclass[12pt]{article}",
    "\\begin{document}",
    "",
    "We thank the referee very much for careful reading and useful comments that help to improve our draft.",
    "Replies to the comments are listed below.",
    "",
    "\\begin{enumerate}",
    "\t\\item ...",
    "",
    "\textbf{Reply}",
    "",
    "...",
    "\\end{enumerate}",
    "",
    "We hope that we have addressed the referee's questions to their satisfaction and that the revised manuscript is suitable for publication.\\\\",
    "",
    "Sincerely,\\\\",
    "",
    "\\noindent",
    "So Chigusa\\\\",
    "...",
    "",
    "\\end{document}"
  ],
  "description": "reply to referee report"
}
```

任意の `*.tex` ファイル内で `reply + Tab` とすると返答のテンプレートができる。

### その他の設定

- `latex-workshop.latex.autoBuild.run` = `onSave` （保存のたびに自動でビルド）
- `latex-workshop.latex.autoClean.run` = `onBuilt` （ビルドのたびに自動でクリーン）
- `latex-workshop.synctex.afterBuild.enabled` = `true`（ビルド後のプレビュー画面がカーソル位置まで飛ぶ）
- `latex-workshop.latex.recipe.default` = `lastUsed`（ビルドのレシピは最後に使用したものを使用）

### チートシート

- ビルド `Cmd + Alt + b`
- プレビュー `Cmd + Alt + v`
- クリーン `Cmd + Alt + c`
- sync tex → pdf `Cmd + Alt + j`
- sync pdf → tex `Cmd + Click`
- 環境の展開 `\align + Tab` 等
- ギリシア文字の展開 `@a + Tab` 等

## Markdown 環境構築

以下の拡張機能を使用。

- Markdown All in One（さまざまな機能がオールインワンでほぼ必須）
- Markdown PDF（html 等へのエクスポート用。`pandoc` の代わり）
- markdownlint（書式チェック）
- Markdown Preview Github Styling（GitHub 風のプレビュー表示）

### チートシート（個人設定含む）

- プレビュー `Cmd + Alt + v`
- html 出力 `Cmd + Shift + p` （コマンドパレット）から Export (html)
- インラインコード `Ctrl + q`
- コードブロック `Ctrl + Alt + q`
- **ボールド** `Cmd + b`
- *イタリック* `Cmd + i`
- ~~打ち消し線~~ `Ctr + s`
- 書式エラーの修正 `Cmd + .`

## html 環境構築

開発者ツールが使用できる優秀な html ビューアー、`Live Preview` を導入した。

### チートシート（個人設定）

- プレビュー `Cmd + Alt + v`
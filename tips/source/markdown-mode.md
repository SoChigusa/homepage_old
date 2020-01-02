
# Emacs で markdown-mode を使用した編集、プレビュー環境を整える

## markdown-mode の導入 ##

Emacs のパッケージインストーラを利用する記事が多いけれど、markdown-mode が見つからなかったため、GitHub から clone した。

``` shell
git clone git://jblevins.org/git/markdown-mode.git
```

`~/.emacs.el` に以下を追加する。

``` emacs-lisp
(load "path-to-markdown-mode/markdown-mode/markdown-mode.el")
(setq auto-mode-alist (cons '("\\.md" . gfm-mode) auto-mode-alist))
```

## プレビュー環境の構築 ##

pandoc を使用することにした。

``` shell
brew install pandoc
```

表示に使用するスタイルシートを見つけてくる。
GitHub Flavored Markdown (gfm) が見栄え良い。
今回は`~/.pandoc/github.css`に該当ファイルを置いている。
`~/.emacs.el` に以下を追加することで、`C-c C-c p` で html を自動生成し、プレビュー画面が立ち上がる。

``` emacs-lisp
(setq markdown-command "pandoc -s -c ~/.pandoc/github.css")
```

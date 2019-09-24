---
title: Atom の導入とカスタマイズ
<!-- author: So Chigusa -->
---

# Atom の導入とカスタマイズ

-------------------------------------------------------------------------------

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

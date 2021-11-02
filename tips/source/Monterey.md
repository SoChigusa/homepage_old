# macOS Monterey 12 アップデート日記

<img src="https://dl.dropboxusercontent.com/s/4s2nkqcebcqa80n/monterey.jpeg?dl=0" style="max-width:100%;">
<center><i>2021 Summer, 17-Mile Drive @ Monterey</i></center>

## 環境

2017年頃購入の iMac でテスト。クリーンインストールではなく OS アップデートを選択。
macOS Mojave 10.14 からのアップデート。

## アップデート、終わらん。。

ありがちなやつ。進捗バーが 95% あたりでスタックしてそれ以上進まないまま 2日が経過。
調べてみると、セーフモードで起動してディスクの修復を行ってから、OSを再インストールのが典型的な解決法らしい。
この方法で無事アップデートが完了した。

ちなみに無線キーボードを使っている場合のセーフブートのタイミングは割と非自明で、まず電源ボタンを押して起動音が鳴ったのを確認してから`⌘＋R`を押下、林檎のマークが出るまでそのままホールド。
電源ボタンを押す前からキーを押さえていると通常起動になってしまうので注意。

## 管理者がいない！？

アップデートが終わって管理者権限の必要な操作が様々と要求される段になって、どう頑張ってもログインができないことで悩んでいるうちに気づく。
**アレ、管理者いなくね？**

<center>
  <img src="https://dl.dropboxusercontent.com/s/z0qas1qqp27o3dk/screenshot-2021-11-01-16-47-58.png?dl=0" style="max-width:50%;">

  <i>かつて管理者であったであろう「管理者」という通常ユーザー</i>
</center>

[このページ](https://present-nani-suru.com/mac/how-to-recreate-admin-user-on-mac/)に従って裏技感の強い方法で解決。（実行する場合は当然、自己責任で）

セーフモードで起動したのち、メニューバーのユーティリティからターミナルを起動する。
そして以下のコマンドを実行。

``` shell
rm /Volumes/Macintosh\ HD/var/db/.AppleSetupDone
```

コレ多分、macの初期設定が未完了であるように偽装してるんだろうね。
この状態で再起動すると、新品のmacを起動したときのようにユーザーの作成と初期設定を求められる。
Siriがめちゃデカい声でしゃべるので注意。
で、一番最初に作った（とmacが認識している）ユーザーは自動的に管理者になるので、万事解決ってわけ。
もちろん初めから存在していたユーザーのデータは消えないので問題なし。

<center>
  <img src="https://dl.dropboxusercontent.com/s/qyq8b45t7c4wq2a/screenshot-2021-11-01-17-59-21.png?dl=0" style="max-width:50%;">

  <i>無事新しい管理者アカウントが増えている</i>
</center>

うーん、なんだコレ。

<img src="https://dl.dropboxusercontent.com/s/o15k2n8yjc0ccqb/LWScreenShot-2021-11-01-18-02-48.png?dl=0" style="max-width:100%;">
<center><i>Monty Hall "Which of these is the administrator account?"</i></center>

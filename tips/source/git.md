
# ひとりでもgit、みんなでもgit

## latexdiffを使う

gitに対応した`latexdiff-vc`を用いてgitレポジトリの任意のバージョンとのdiffが取れる。より詳しくは[別記事](latexdiff.html)を参照のこと。

## mergeの活用

gitを使用していない多人数プロジェクトで原稿を同時編集する際など、原稿の変更点を途中で合体させるためにmergeが活用できる。

簡単のため、最初にローカルmasterの変更点は全てpushしておく。

```shell
git push origin master
```

次にmasterのバージョンを同時編集が始まった時期に戻す。

```shell
git reset --hard (commit)
```

ブランチを切って、新しいブランチ上に別の人が編集した原稿を更新する。

```shell
git branch (branch name)
git checkout (branch name)
cp (new draft) (old draft)
```

masterも最新のバージョンに戻し、変更点をmerge。

```shell
git checkout master
git pull origin master
git merge (branch name)
```

## コミット履歴をファイル単位で消去・修正する

### 起きたこと

リモートリポジトリとして最初は [bitbucket](https://bitbucket.org/) を使っていたのだが、あるときに [github](https://github.com/) に乗り換えて必要になったリポジトリから順次移行作業を行っていた。
該当のリポジトリでは 100MB を超えるサイズのファイルをコミットしてしまっており、最新のコミットからはすでに削除済みではあるものの、コミット履歴中にそのファイルの情報が残っていた。
この点が bitbucket では問題にならなかったのだが、github に移行した際に 100MB のファイルサイズ制限に引っかかってしまい、コミット履歴からこのデカいファイルの情報全てをコンシステントに消し去る必要が生じた。

### やったこと

[こちら](https://medium.com/eureka-engineering/git%E3%83%AA%E3%83%9D%E3%82%B8%E3%83%88%E3%83%AA%E3%81%8B%E3%82%89%E5%AE%B9%E9%87%8F%E3%81%AE%E5%A4%A7%E3%81%8D%E3%81%84%E3%83%95%E3%82%A1%E3%82%A4%E3%83%AB%E3%82%92%E5%B1%A5%E6%AD%B4%E3%81%8B%E3%82%89%E6%8A%B9%E6%B6%88%E3%81%99%E3%82%8B-b6bb526d670f)の記事を参考にさせていただいた。
履歴にあるサイズが大きいファイルは Atlassian が提供している [git_find_big.sh](https://confluence.atlassian.com/bitbucket/files/321848291/321979854/1/1360604134990/git_find_big.sh) というシェルスクリプトで探し出せる。
リポジトリの root で

``` shell
./git_find_big.sh
```

消すべきファイルが特定できたら、以下を実行する。

``` shell
#!/bin/bash

TARGETS=(
  "[target file name]"
)
target=$(printf " %s" "${TARGETS[@]}")
target=${target:1}
git filter-branch --index-filter "git rm -r --cached --ignore-unmatch ${target}" -- --all
```

もちろんリポジトリのバックアップ（この場合は元のリモートリポジトリで十分）はしっかり取っておくこと！

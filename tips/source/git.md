
# ひとりでもgit、みんなでもgit

## latexdiffを使う

gitに対応した`latexdiff-vc`を用いてgitレポジトリの任意のバージョンとのdiffが取れる。より詳しくは[別記事](latexdiff.html)を参照のこと。

## mergeの活用

gitを使用していない多人数プロジェクトで原稿を同時編集する際など、原稿の変更点を途中で合体させるためにmergeが活用できる。

簡単のため、最初にローカルmasterの変更点は全てpushしておく。

```
git push origin master
```

次にmasterのバージョンを同時編集が始まった時期に戻す。

```
git reset --hard (commit)
```

ブランチを切って、新しいブランチ上に別の人が編集した原稿を更新する。

```
git branch (branch name)
git checkout (branch name)
cp (new draft) (old draft)
```

masterも最新のバージョンに戻し、変更点をmerge。

```
git checkout master
git pull origin master
git merge (branch name)
```

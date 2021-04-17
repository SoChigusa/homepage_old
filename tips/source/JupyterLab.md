# JupyterLab の導入から機能拡張、便利な応用まで

JupyterLab は Python がインタラクティブに書ける Jupyter Notebook の進化版、らしい。
(デフォルトで) markdown 記法を使って綺麗なノートが作れることが個人的な推しポイント。
あと拡張機能。

## 導入

[こちらのサイト](https://ai-inter1.com/jupyter-lab/#st-toc-h-2)を参考にした。
今回は Anaconda と一緒に導入することに決めて、[ダウンロードページ](https://www.anaconda.com/download/)から GUI 版をダウンロード。
インストールが終わったら Anaconda.Navigator を使って即 JupyterLab が launch できるようになっている。便利。

## 拡張機能の導入

[上と同じサイト](https://ai-inter1.com/jupyter-lab/#st-toc-h-2)を参考に、まず `node.js` をインストールする必要がある。
`brew` でもインストールできるのだが、JupyterLab との連携がうまく行かなかったので、`conda` を推奨。

``` shell
conda install nodejs
```

これでノートブック左側のメニューから拡張機能の検索・導入ができるようになる。

### 拡張機能1: Variable Inspector

上記サイトでオススメされているこれを導入した。
導入には GUI から行う方法の他に、shellで

```
jupyter labextension install @lckr/jupyterlab_variableinspector
```

などとすることも可能。

### 拡張機能2: git(hub) との連携

`@jupyterlab/git` を導入する。拡張機能の他に、以下のインストールが必要らしい。

```
conda install -c conda-forge jupyterlab-git
```

使い方の手順は[こちら](https://qiita.com/cleeeear/items/2fa90aded84e90f9bff5)にある通り。
正しくインストールが完了すれば、GUIの左側に git のメニューが存在して、そこから `stage` や `commit` や `push` ができるようになる

## matplotlib を使う

ちょっとハマったのが、コードの先頭（`import matplotlib` より前）におまじないが必要（以下1行目）。
これがないとノート内で図を表示してくれない。
また、おまじないがあれば `plt.show()` は不要で、特にこのコマンドがあると図をファイルに保存するとき正しく出力されなかったので、書かない。
さらに、全てのコマンドを1つのセル内に書かないと図は正しく作られなかった。
以下ミニマルなサンプルコード。

``` python
%matplotlib inline

import numpy as np
import matplotlib.pyplot as plt

# figure settings
fig = plt.figure()

# subfigure
ax = fig.add_subplot(1,1,1)

# random variables
x = np.random.rand(100)
y = np.random.rand(100)

# plot
ax.scatter(x, y)

# show
plt.tight_layout()

# save figure
plt.savefig('../figure/plot.pdf', bbox_inches='tight')
```

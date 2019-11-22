
# Matplotlib を使いこなす

## 基本構文 ##

`matplotlib` を読み込んで、図を描く準備をする部分。

``` python
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt

fig = plt.figure()
ax  = fig.add_subplot(1,1,1)
```

`matplotlib.axes.Axes` クラスのインスタンスである `ax` を用いて図を描いたら（下部参照）、図の設定は以下のように可能。

``` python
ax.set_title(r'title $\LaTeX$', size=25)
ax.set_xlabel('xlabel', size=25)
ax.set_ylabel('ylabel', size=25)
ax.legend(loc="lower right", fontsize=20)
ax.tick_params(labelsize=20)
```

最後に PDF に保存し、確認のためにファイルを開く。

``` python
plt.tight_layout()
plt.show()
plt.savefig('hoge.pdf')
commands.getoutput('open hoge.pdf')
```

## 描画データの準備 ##

CSV のような構造のデータが与えられていることをイメージする。
これを `numpy` で読み込んで使用する場合、

``` python
data = np.loadtxt('hoge.dat', skiprows=1, usecols=range(2))
x = data[:,0]
y = data[:,1]
```

などとする。`skiprows` オプションを使用することで、好きな数のヘッダー行を読み込み範囲から外せる。
また、`pandas` を用いる場合には、区切り文字が空白かタブかに応じて、

``` python
data = pd.read_csv('hoge.dat')
data = pd.read_table('hoge.dat')
```

とする。このとき、各データ列のヘッダーに変数名を書いておいて、`data['name']` で参照できる。
このデータを `numpy` リストにも変換できる。

``` python
nplist = data.values
```

## 基本の1D plot ##

x,y 両軸のデータのリストをそれぞれ用意して、`plot` 関数を用いる。

``` python
ax.plot(xlist, ylist, color='r', linestyle='-', linewidth=2, label='hoge')
```

`label` オプションの文字列がレジェンドとして使用される。軸の範囲の設定は

``` python
ax.set_xbound(xmin, xmax)
ax.set_ybound(ymin, ymax)
```

対数目盛りの設定は

``` python
ax.set_xscale('log')
ax.set_yscale('log')
```

のように可能。軸の目盛りの位置と対応する文字列も必要に応じて指定できる。

``` python
ax.set_xticks([0, 0.5, 1, 1.5])
ax.set_yticks([0, 0.5, 1, 1.5])
ax.set_yticklabels(['0.0', '0.5', '1.0', '1.5'])
```

また、補助線を引きたい時は `numpy` を使って

``` python
x = np.linspace(xmin, xmax, npts)
y = np.linspace(ymin, ymax, npts)
```

として作ったリストが使える。

## 等高線 ##

`matplotlib` で等高線をプロットするには、2次元リストに格納された x,y,z の値が必要。
もし用意されたデータが 1次元で、ただし秩序を保って並んでいるなら、

``` python
x,y,z = data[:,1].reshape(ny,nx), data[:,2].reshape(ny,nx), data[:,3].reshape(ny,nx)
```

などと、`ndarray.reshape` 関数が使える。
さて、これを用いて等高線プロットは

``` python
cs = ax.contour(x, y, z, levels=[z1, z2, z3], colors='b', linestyles='-')
h,_   = cs.legend_elements()
ax.legend([h[0]], ['legend'], fontsize=20)
```

などとして描ける。レジェンドの他に、等高線の途中に対応する z の値を描くことも出来る。

``` python
ax.clabel(cs, fmt='%d')
ax.clabel(cs2, fmt='%.1E')
```

別の種類のプロットとして、等高線間の塗りつぶしも可能。そのためには

``` python
ax.contourf(x, y, z, levels=[zmin,zmax], alpha=0.3, colors='gray')
```

などとすると、`zmin < z < zmax` の領域を指定された色で塗りつぶす。
この時、場合によっては背景色を白以外の色にしておくと便利。

``` python
ax.set_axis_bgcolor('green')
```

## ヒストグラム ##

ヒストグラムの描画のためには、1次元のデータリストを用意して、

``` python
ax.hist(data, bins=nbin, range=(xmin, xmax), color='m', ec='black', label='legend')
```

とする。
`ec` オプションは、python3 で描くとデフォルトの枠線が白色で幸薄い感じになるので必須。
各データを違うウェイトで足し合わせたい時は、データと同じ順序で同じ数のウェイトを格納したリスト `weights` を用意し、オプションを追加： `weights=weights`。

横軸が log scale のヒストグラムを描きたいときは少々変更が必要で、

``` python
ax.hist(prob, bins=np.logspace(-6, 0, 50), color='b', ec='black', log=True)
ax.set_xscale('log')
```

のような感じ。

## アスペクト比を変更する ##

図の高さを幅の `aspect` 倍に変更したいとする。以下のようにすれば良い。

``` python
xmin, xmax = ax.get_xlim()
ymin, ymax = ax.get_ylim()
ax.set_aspect(abs((xmax-xmin)/(ymax-ymin))*aspect, adjustable='box-forced')
```

## 座標軸の描画 ##

以下のサンプルはどこぞからの拾い物。

``` python
# removing the default axis on all sides:
for side in ['bottom','right','top','left']:
    ax.spines[side].set_visible(False)

# removing the axis ticks
plt.xticks([]) # labels
plt.yticks([])
ax.xaxis.set_ticks_position('none') # tick markers
ax.yaxis.set_ticks_position('none')

# get width and height of axes object to compute
# matching arrowhead length and width
dps = fig.dpi_scale_trans.inverted()
bbox = ax.get_window_extent().transformed(dps)
width, height = bbox.width, bbox.height

# manual arrowhead width and length
hw = 1./20.*(ymax-ymin)
hl = 1./20.*(xmax-xmin)
lw = 1. # axis line width
ohg = 0.3 # arrow overhang

# compute matching arrowhead length and width
yhw = hw/(ymax-ymin)*(xmax-xmin)* height/width
yhl = hl/(xmax-xmin)*(ymax-ymin)* width/height

# draw x and y axis
ax.arrow(xmin, 0, xmax-xmin, 0., fc='k', ec='k', lw = lw,
         head_width=hw, head_length=hl, overhang = ohg,
         length_includes_head= True, clip_on = False)
ax.arrow(0, ymin, 0., ymax-ymin, fc='k', ec='k', lw = lw,
         head_width=yhw, head_length=yhl, overhang = ohg,
         length_includes_head= True, clip_on = False)
```

上のコマンドで座標軸を作ったら、そこに `ax.plot` で関数を描画したり、

``` python
phi = patches.Circle(xy=(x, y), radius=r, fc='green')
ax.add_patch(phi)
```

で円を描いたり出来る。

## 図への書き込み ##

プレゼン用に図に星印などつけたい場合は、

``` python
ax.plot(x, y, '*', markersize=15, color='black', clip_on=False)
```

とする。`clip_on=False` を指定すると、点が図の領域からはみ出た場合も、はみ出た部分を含めて全て描画してくれる。
また、矢印付き、なしの文字の書き込みが

``` python
ax.annotate('Text', xy=[x, y], xytext=[xtext, ytext], arrowprops=dict(width=4, color='b'), fontsize=30, color='b')
ax.annotate('Text', xy=(xtext, ytext), fontsize=20)
```

などで可能。

## 図を分割 ##

`matplotlib.axes.Axes` インスタンスを準備する部分を

``` python
ax1  = fig.add_subplot(N,x,y)
```

などと変更する。ここで `N` は図の総数で、`x`, `y` が `ax1` の図の座標に対応する。

## 漫画風のプロット ##

``` python
plt.xkcd()
```

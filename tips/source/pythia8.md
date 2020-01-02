
# pythia8 を使いこなす

基本的に、Madgraph と連携して pythia8 を動かすことを想定する。

## Master Switches ##

http://home.thep.lu.se/Pythia/pythia82html/MasterSwitches.html を参照する。
今回は initial state radiation (ISR) を切りたかったので、

``` dat
PartonLevel:ISR = off
```

を`pythia8\_card(\_default).dat`へ追加。

## 出力ファイルのイベント数が想定より少ない ##

https://answers.launchpad.net/mg5amcnlo/+question/200766 を参考にした。
ほぼ on-shell の粒子が s-channel に飛んでいるなどで、amplitude が発散し、
数値計算が不安定になったときにこういう振る舞いを起こすらしい。
今回は long-lived particle の decay を扱おうとしたせいで問題が起きた。
今の所の対処法としては、ピークの smearing が大きくなることは度外視して、
適度に大きな崩壊率を`param_card.dat`で指定しておくことくらい。

## 新粒子が detector simulation で悪さをすることを防ぎたい ##

https://answers.launchpad.net/mg5amcnlo/+question/222285 にあるように、
Delphes を通す際、気にしている粒子の particle ID を neutralino(1000022) にしておくというチートが可能。


# Delphes の応用

## そもそも ##

Delphes の detector card は tcl というスクリプト言語で書かれているらしい（拡張子から自明だが）。
emacs の markdown-mode が tcl の存在を知っていたので、教えられた形になった。

## FastJet の動作をカスタマイズ ##

FastJet の外部呼び出しの[ページ][1]が参考になる。
基本的には `ExternalFastJetHepMC.cpp` を元に編集して使えば良いが、
１番の問題は External FastJet に対応したカードがデフォルトで CMS のもの `cards/delphes_card_CMS_NoFastJet.tcl​` しかないこと。
今回は FCC-hh 用のカードを使いたかったので、`cards/FCC/FCChh.tcl​` を元に書き換えていく。

当然 Jet に関する module 群は不要（というか FastJet がないと実行時エラー）なので、宣言と定義を消す。具体的には、

``` tcl
  GenJetFinder02
  GenJetFinder04
  GenJetFinder08

  FastJetFinder02
  FastJetFinder04
  FastJetFinder08

  CaloJetFinder02
  CaloJetFinder04
  CaloJetFinder08

  TrackJetFinder02
  TrackJetFinder04
  TrackJetFinder08

  JetEnergyScale

  JetFlavorAssociation

  BTagging
  CTagging
  TauTagging
```

これらが不要。あとよくわからないけど、`TreeWriter` という module も消しておく必要がある。
これは `cards/delphes_card_CMS_NoFastJet.tcl​` にも存在しないので consistent。

[1]:https://cp3.irmp.ucl.ac.be/projects/delphes/wiki/WorkBook/ExternalFastJet

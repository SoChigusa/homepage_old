# SLHA を用いた SUSY-HIT から MadGraph への連携 #

SUSY LesHouches Accord (SLHA) 形式を用いて、超対称粒子スペクトルの情報に
崩壊率の情報を付け加えて、MadGraph (+Pythia, etc..) が使えるようにする。
SLHA を扱える decay package の例として、SUSY-HIT（その内部の SDECAY および HDECAY）
を用いることにする。（https://www.itp.kit.edu/~maggie/SUSY-HIT/）
ちなみに SDECAY 自体の webpage は更新が止まっているのか、コンパイルに問題があったので、
後継である SUSY-HIT を使っている。

SUSY-HIT はデフォルトで SuSpect を用いてスペクトル計算を行うが、今回の目的では
使わないので、`susyhit.in` の最初のオプションで切る。
切ると、SLHA -> SLHA の最小限の機能を持った decay package になる。

出力された SLHA がほぼ MadGraph の `param_card.dat` に対応するが、
以下の二点の修正が必要。

* 不足する情報を加える。具体的には `import model MSSM_SLHA2` して作ったプロセスに自動で作られる `param_card.dat` 内の
  * BLOCK MASS および BLOCK DECAY の一部、標準模型粒子の情報
  * BLOCK QNUMBERS : 超対称性粒子の量子数
* SLHA -> SLHA2 形式への変換。面倒なので、SLHA をそのまま突っ込んで `./bin/generate_events` すると、文句を言いながら変換してくれる。

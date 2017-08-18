yasuna
======

[![version](http://img.shields.io/github/tag/sasairc/yasuna.svg?style=flat&label=version)](https://github.com/sasairc/yasuna/releases)
[![license](https://img.shields.io/badge/License-WTFPL2-blue.svg?style=flat)](http://www.wtfpl.net/txt/copying/)
[![issues](http://img.shields.io/github/issues/sasairc/yasuna.svg?style=flat)](https://github.com/sasairc/yasuna/issues)
[![build](https://img.shields.io/travis/sasairc/yasuna.svg?style=flat)](https://travis-ci.org/sasairc/yasuna)
[![yasuna](https://img.shields.io/badge/yasuna-kawaii-orange.svg?style=flat)](http://houbunsha.co.jp/comics/detail.php?p=%A5%AD%A5%EB%A5%DF%A1%BC%A5%D9%A5%A4%A5%D9%A1%BC)

![default](https://raw.githubusercontent.com/sasairc/yasuna/master/img/screenshot.png)

折部やすなちゃんの名言をランダムで表示します。  
誤字脱字等あれば、issueやtwitterで報告して頂けると嬉しいです。		

※ 参考もといパクリ元　[844196/Renge](https://github.com/844196/Renge)

## Requirements

* GNU Make
* gcc or clang

## Install

### Debian/GNU Linux or Debian based system.(amd64)

```shellsession
# echo 'deb http://ssiserver.moe.hm/debian ./' >> /etc/apt/sources.list
# apt-get update
# apt-get install yasuna
```

### Mac OS X / Homebrew

```shellsession
% brew tap 844196/Renge    # Tap
% brew install yasuna      # Install
```

### Other systems.

```shellsession
% git clone --recursive https://github.com/sasairc/yasuna.git && cd yasuna
% make PREFIX=/foo/bar	# デフォルトでは、PREFIX=/usr/localです
# make install PREFIX=/foo/bar
```

その他のオプションに関しては、`INSTALL.ja`をご覧下さい。


## zshでの補完

`$(PREFIX)/share/yasuna/compdef/_yasuna.zsh`を`_yasuna`として、`$fpath`の通ったディレクトリにコピーして下さい。


## Usage

### Basic usage

```shellsession
% yasuna
なーんてね！うそだよー！　釣られた？釣られた？
% yasuna
100円払うから喋らせて
% yasuna -l | headtail --pretty	# print all quotes list
   0 100円くらいはもらえると思ったのに！
   1 100円払うから喋らせて
   2 DVD！？
   3 GO!
   4 UFO…とか…
 :
 :
 :
4797 （重くて打てない球に泣くが良い）
4798 （間違った遊び方を笑ってやる…グフフ）
4799 ？
4800 ﾋｯｸ ﾋｯｸ ﾋｯｸ ﾌﾟﾊ
4801 ﾋﾋﾋﾋ… ﾌﾋｬﾋ… ｹﾞﾍﾍﾍﾍ
% yasuna -n 4226    # specify quote number
本当はこうやって…
```

### Polyaness dictionary

```
% head ~/trio_the_techno.ltsv
filetype:polyaness_dict	author:sasairc	description:トリオ・ザ・テクノ
speaker:高橋幸宏	quote:元、YMOでドラムをしておりました、高橋でございます
speaker:坂本龍一	quote:元、YMOでキーボードをやっておりました、坂本です
speaker:細野晴臣	quote:えー、元、YMOでベースを弾いてました、細野です
speaker:高橋幸宏	quote:僕たち
speaker:高橋幸宏	quote:トリオ・ザ・テクノです
speaker:坂本龍一	quote:トリオ・ザ・テクノです
speaker:細野晴臣	quote:トリオ・ザ・テクノです
speaker:坂本龍一	quote:それでは先日、フジテレビの夜のヒットスタジオに、RCサクセションの忌野清志郎君が出まして、本番で1カメさんに舌を出した所をやります
speaker:坂本龍一	quote:ちょっと失礼
% yasuna -f ~/trio_the_techno.ltsv -s 細野晴臣 -l    # specify speaker
*** speaker = 細野晴臣, 13 quotes ***
   0 えー、元、YMOでベースを弾いてました、細野です
   1 トリオ・ザ・テクノです
   2 えー、故・林家三平師匠が中国に行った時に公演した時の模様をやります
   3 えー、正月に坊主が二人やって来てこれがホントの「和尚がツー」
   4 えー、ですから、パンダがうー？何食ってんだ？パンだ
   5 えー、故・柳家金語楼師匠が、あー、雲の上を歩いている所をご覧にかけま…かけましょう
   6 えー、故・大河内傳次郎さんの、んぁ物真似をします
   7 よおおっ およよおっ およよよおよっ よおよっ およようおっ およおおうよっ およよよぅあぁ
   8 かわいい
   9 かわいい(2度目)
  10 元、YMOの坂本龍一がですね。スタジオでシンセサイザーを弾いていまして、えー、ドアの向こうから可愛い子が来た時の顔ちょっとやりましょう
  11 えー、僕たち
  12 どうも失礼しました
% yasuna -f ~/trio_the_techno.ltsv -s 坂本龍一 -n 6  # specify quote number
北海道のヒロミちゃんをやります
% yasuna -f ~/trio_the_techno.ltsv -s 高橋幸宏
えー、僕の家のお父さんの真似をします
```

### Additional usage

```shellsession
% yasuna -n 1337 | clangsay -f debian
 __________________________________
< さあ、出てゆくが良い お前は自由だ >
 ----------------------------------
  \
   \
          _,met$$$$$gg.
       ,g$$$$$$$$$$$$$$$P.
     ,g$$P""       """Y$$.".
    ,$$P'              `$$$. 
  ',$$P       ,ggs.     `$$b:
  `d$$'     ,$P"'   .    $$$
   $$P      d$'     ,    $$P
   $$:      $$.   -    ,d$$'
   $$;      Y$b._   _,d$P'
   Y$$.    `.`"Y$$$$P"' 
   `$$b      "-.__
    `Y$$b
     `Y$$.
       `$$b.
         `Y$$b.
           `"Y$b._
               `""""
% yasuna --file=/proc/cpuinfo
cpu MHz         : 2933.470
```

詳しい使い方に関しては、`--help`または`yasuna.6`を参照して下さい。

## Note

Twitter: [@sasairc_yasuna](https://twitter.com/sasairc_yasuna)にて本プログラムを使用しています。	
`-n, --number`オプション同等の機能も実装していますので、興味があればプレビューとして使ってみて下さい。


## Thanks

* [Masaya Tk](https://github.com/844196)	
	Homebrew用のリポジトリを提供して頂きました。ありがとうございます。
 
* [kadopoly](https://github.com/kadopoly)	
	`yasuna-quotes`の誤字修正をして頂きました。ありがとうございます。

## License

[WTFPL version 2](https://raw.githubusercontent.com/sasairc/yasuna/master/LICENSE)


## Author

sasairc (https://github.com/sasairc)

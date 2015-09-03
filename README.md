yasuna
======
[![version](http://img.shields.io/github/tag/sasairc/yasuna.svg?style=flat&label=version)](https://github.com/sasairc/yasuna/releases)
[![license](https://img.shields.io/badge/License-WTFPL2-blue.svg?style=flat)](http://www.wtfpl.net/txt/copying/)
[![issues](http://img.shields.io/github/issues/sasairc/yasuna.svg?style=flat)](https://github.com/sasairc/yasuna/issues)
[![build](https://img.shields.io/travis/sasairc/yasuna.svg?style=flat)](https://travis-ci.org/sasairc/yasuna)
[![yasuna](https://img.shields.io/badge/yasuna-kawaii-orange.svg?style=flat)](http://houbunsha.co.jp/comics/detail.php?p=%A5%AD%A5%EB%A5%DF%A1%BC%A5%D9%A5%A4%A5%D9%A1%BC)

![default](http://41.media.tumblr.com/78dd1ad58e3c540b7a769d0d107a12e7/tumblr_ntaaaw5uqk1u2jamko1_1280.png)

折部やすなちゃんの名言をランダムで表示します。  
誤字脱字等あれば、issueやtwitterで報告して頂けると嬉しいです。		

※ 参考もといパクリ元　[844196/Renge](https://github.com/844196/Renge)

## Install
#### Debian/GNU Linux or Debian based system.(amd64)
```shellsession
# echo 'deb http://ssiserver.moe.hm/debian ./' >> /etc/apt/sources.list
# apt-get update
# apt-get install yasuna
```

#### Mac OS X / Homebrew
```shellsession
$ brew tap 844196/Renge    # Tap
$ brew install yasuna      # Install
```

#### Other systems.
```shellsession
$ make PREFIX=/foo/bar	# デフォルトでは、PREFIX=/usr/localです
# make install PREFIX=/foo/bar
```

## zshでの補完
`$(PREFIX)/share/yasuna/compdef/_yasuna.zsh`を`_yasuna`として、`$fpath`の通ったディレクトリにコピーして下さい。

## Usage
* Basic usage	
	```shellsession
	$ yasuna
	なーんてね！うそだよー！　釣られた？釣られた？
	$ yasuna
	100円払うから喋らせて
	```

* Additional usage	
	```shellsession
	$ yasuna | clangsay
	 _______________________________________________
	< だがこんな物で、私を封じられると思っているのか >
	 -----------------------------------------------
	        \   ^__^
	         \  (oo)\_______
	            (__)\       )\/\
	                ||----w |
	                ||     ||
	  $ yasuna --file=/proc/cpuinfo
	  cpu MHz         : 2933.470
	```

## Thanks
* [Masaya Tk](https://github.com/844196)  
	Homebrew用のリポジトリを提供して頂き、ありがとうございます！
 
## License
[WTFPL version 2](http://www.wtfpl.net/txt/copying/)

## Author
sasairc (https://github.com/sasairc)

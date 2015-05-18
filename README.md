yasuna
======
[![version](https://img.shields.io/badge/tag-0.4.0-orange.svg?style=flat)](https://github.com/sasairc/yasuna/releases)
[![license](https://img.shields.io/badge/License-WTFPL2-blue.svg?style=flat)](http://www.wtfpl.net/txt/copying/)

![default](http://40.media.tumblr.com/07da53a3d6945721a4ca8aa4513b8277/tumblr_nizi5dPpPK1u2jamko1_1280.png)

折部やすなちゃんの名言をランダムで表示します。  
誤字脱字等あれば、issueやtwitterで報告して頂けると嬉しいです。		

※ 参考もといパクリ元　[844196/Renge](https://github.com/844196/Renge)


### install

* Debian/GNU Linux or Debian based system.(amd64)
  ```shellsession
  # echo 'deb http://ssiserver.moe.hm/debian ./' >> /etc/apt/sources.list
  # apt-get update
  # apt-get install yasuna
  ```
  
* Debian/GNU Linux or Debian based system.(not amd64) 
  ```shellsession
  $ cat info.txt
  注意 : バージョンは、適時置き換えて下さい。
  $ wget -O - http://ssiserver.moe.hm/debian/yasuna_0.3-1.tar.gz | tar zxvf -
  $ cd yasuna 
  $ dpkg-buildpackage -uc -us 
  # dpkg -i ../yasuna_*.deb 
  ```

* Mac OS X / Homebrew
  ```shellsession
  $ brew tap 844196/Renge    # Tap
  $ brew install yasuna      # Install
  ```

* Other systems.
  ```shellsession
  $ make PREFIX=/foo/bar	# デフォルトでは、PREFIX=/usr/localです
  # make install PREFIX=/foo/bar
  ```

### Usage
*  Basic usage
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

### Thanks
* [Masaya Tk](https://github.com/844196)  
  Homebrew用のリポジトリを提供して頂き、ありがとうございます！
 
#### License
[WTFPL version 2](http://www.wtfpl.net/txt/copying/)

### Author
sasairc (https://github.com/sasairc)

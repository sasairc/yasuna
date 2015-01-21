yasuna
======

![default](http://36.media.tumblr.com/6a85c9b9713ad1b578728e2df964e955/tumblr_nihzltGEMm1u2jamko1_1280.png)

折部やすなちゃんの名言をランダムで表示します。  
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
  $ wget -O - http://ssiserver.moe.hm/debian/yasuna_0.1-1.tar.gz | tar zxvf -	# バージョンに注意  
  $ cd yasuna 
  $ dpkg-buildpackage -uc -us 
  # dpkg -i ../yasuna_*.deb 
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
  $ yasuna | cowsay
   ______________
  < オカシダ オカシヲヨコセ >
   --------------
          \   ^__^
           \  (oo)\_______
              (__)\       )\/\
                  ||----w |
                  ||     ||
                  
  $ yasuna --dict=/proc/cpuinfo
  cpu MHz         : 2933.470
  ```

#### License
[WTFPL version 2](http://www.wtfpl.net/txt/copying/)

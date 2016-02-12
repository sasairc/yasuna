# Polyaness 辞書ファイル標準仕様（ドラフト）

本仕様は、辞書ファイルの利便性および相互利用性の確保、ならびに、普及拡大に寄与することを目的とする。



## 文字コード

- **[MUST]** 文字コードはBOMなしUTF-8とする。



## 改行コード

- **[MUST]** 改行コードはLFとする。



## ファイル書式

- **[MUST]** 辞書ファイル全体の書式は[LTSV](http://ltsv.org/)とする。
    - 各列の並びは問わない。

- **[MUST]** 辞書ファイルの先頭行には、ファイル識別子`filetype:polyaness_dict`がなければならない。

  ```text
  filetype:polyaness_dict
  speaker:れんげ<TAB>quote:にゃんぱす〜
   :
   :
   :
  ```

    - **[SHOULD]** 先頭行には`filetype`以外の任意のメタ情報を付与してもよいが、特段の事情がない限り`author`と`description`は必須とする。

      ```text
      filetype:polyaness_dict<TAB>author:844196<TAB>description:Great Dictionary
      ```

- **[MUST]** 辞書ファイル内の各レコードは、以下の列を必ず備えるものとする:
    - `speaker`: 発言者
    - `quote`: 発言内容

- **[OPTIONAL]** 開発者は必要に応じて、必要列以外の列を辞書ファイルの任意のレコードに付与することができる。



## speaker列

台詞の発言者を格納する。

- **[MUST]** 名前の表記は、辞書ファイル内において統一されていること。

  ```text
  # Good
  speaker:れんげ<TAB>quote:にゃんぱす〜
  speaker:れんげ<TAB>quote:もしかしてウチ 田舎に住んでるのん…？
  ```

  ```text
  # Good
  speaker:れんちょん<TAB>quote:にゃんぱす〜
  speaker:れんちょん<TAB>quote:もしかしてウチ 田舎に住んでるのん…？
  ```

  ```text
  # Bad
  speaker:れんげ<TAB>quote:にゃんぱす〜
  speaker:れんちょん<TAB>quote:もしかしてウチ 田舎に住んでるのん…？
  ```

- **[MUST]** 複数の人物が同じ台詞を発した場合は、人物ごとに発言を別けること。なお、別けた際の記述の順序は問わない。

  ```text
  # Good
  speaker:唯<TAB>quote:全然反省してない…
  speaker:縁<TAB>quote:全然反省してない…
  ```

  ```text
  # Good
  speaker:縁<TAB>quote:全然反省してない…
  speaker:唯<TAB>quote:全然反省してない…
  ```

  ```text
  # Bad
  speaker:唯・縁<TAB>quote:全然反省してない…
  ```



## quote列

発言内容を格納する。

- **[MUST]** 吹き出し内の改行は半角スペースに置き換えること。結合・句読点を加える等の操作を行ってはいけない。

  ```text
  # Good
  speaker:ゆずこ<TAB>quote:マジカルって つけると なんでも グレードアップ するよね
  ```

  ```text
  # Bad
  speaker:ゆずこ<TAB>quote:マジカルってつけると、なんでもグレードアップするよね。
  ```

    - ただし、吹き出しの大きさの都合上、単語の途中で強制的に折り返されている場合は、これを改行として扱わなくてもよい。

      ```text
      # Good
      speaker:唯<TAB>quote:電波だとのせられねーぞ？

      # Good
      speaker:唯<TAB>quote:電波だとのせ られねーぞ？
      ```

- **[MUST]** 感嘆符および疑問符、ならびに、その他記号全般は全角とする。ただし、読点の代わりに用いられたと推定されるスペースは、これを半角スペースとする。

  ```text
  # Good
  speaker:唯<TAB>quote:オイ！ 開けろアホッ！！ なにやってんだ！
  ```

  ```text
  # Bad
  speaker:唯<TAB>quote:オイ! 開けろアホッ!! なにやってんだ!
  ```

- **[MUST]** 三点リーダは`…`で統一する。`・・・`や`...`に置換する操作を行ってはいけない。

  ```text
  # Good
  speaker:縁<TAB>quote:なんだっけ… 死刑？
  ```

  ```text
  # Bad
  speaker:縁<TAB>quote:なんだっけ... 死刑？
  ```

- **[MUST]** 吹き出し内の長音符は、見た目の長さに関わらず一つのみとする。波形長音符も同様とする。

  ```text
  # Good
  speaker:ゆずこ<TAB>quote:ガシーン！！
  ```

  ```text
  # Bad
  speaker:ゆずこ<TAB>quote:ガシーーーン！！
  ```

- **[OPTIONAL]** 一人の発言者に付与された二つの吹き出しが、一つの文として成立すると推定される際は、これを一つとして扱ってもよい。

  ```text
  # Good
  speaker:ゆずこ<TAB>quote:つまり 超能力者とかが パワーアップする！
  speaker:ゆずこ<TAB>quote:それどころか 私達も超能力者に なれるかもしれない！

  # Good
  speaker:ゆずこ<TAB>quote:つまり 超能力者とかが パワーアップする！ それどころか 私達も超能力者に なれるかもしれない！
  ```

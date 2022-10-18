# Sequence
C++で使えるシーケンス制御のためのヘッダオンリーなライブラリ。

## OverView
enum class SequenceStatus, SeqFunc, Sequenceクラスがある。

SequenceStatusはシーケンスの状態を示す値である。
```
// シーケンスの状態
enum class SequenceStatus {
  proceed,  // 継続
  next,     // 次へ
  reset,    // 最初へ
  end,      // 最後へ
};
```
SeqFuncは引数を取らずStatusを返す関数型の別名である。
```
// 引数を取らずStatusを返す関数型
using SeqFunc = std::function<SequenceStatus()>;
```
Sequenceクラスに関数(SeqFunc)を渡せば、前から実行されていく。
関数(SeqFunc)の返り値に応じてシーケンスの継続、進行、リセット、終了を行う。

## 使い方
1. ライブラリをインクルード。
```
#include <Sequence.h>
```

2. インスタンスの生成。
```
  Sequence seq = {{[] {
                     printf("hoge\n");
                     return SequenceStatus::next;
                   },
                   [] {
                     printf("fuga\n");
                     return SequenceStatus::next;
                   },
                   [] {
                     printf("piyo\n");
                     return SequenceStatus::next;
                   }}};
```

シーケンスの実行。
```
  while(seq.get_index() < seq.size()) {
    seq();
  }
```

### License
Copyright (c) 2022 Yoshikawa Teru
This code is released under the MIT License, see LICENSE.

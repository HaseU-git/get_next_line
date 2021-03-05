# get_next_line

## 概要
このプロジェクトは、C言語を使用してファイルの読み取りを行うという42tokyoの課題をコーディングしたプロジェクトです。

簡単に課題内容をまとめると、以下の通りでした。  
- 使用して良い関数は、read、malloc、freeの3つのみ。  
- 第一引数にファイルディスクリプタ、第二引数に読み込んだ文字列を格納するためのポインタを受け取る
- 正常に読み取りが完了したら1、終端文字まで読み込んだら0、エラーが発生したら-1を戻り値として返す
- コンパイル時に一回に読み込むバッファーサイズを指定する  
- 使用して良い関数の数は、1ファイルにつき5つまでで最大使用可能ファイル数は2つまで。  
- 関数の行数は25行以内におさめること。  

## 目的
事前にファイルのサイズがわかっていない状態で、read関数を使用しファイルの内容をどのように読みこんでくるかを考えるのが目的の一つでした。  
また、使用できる関数が限られている中で、C言語のメモリ管理についての理解を深めメモリリークなどをしないようにしながらプログラムを完成させるのが大きさの目的の一つでした。  
プログラムのチェックでは、lldbを利用したデバッグを行いlldbの使い方についても理解を深めた。  

## 使い方
get_next_line関数を使用したmainファイルを作成し、printfを用いて標準出力力にファイルを読み込んだ情報を格納した文字列を出力することが必要になります。  
ここでは、任意の数のコマンドライン引数を受け取ることができ、コマンドライン引数がない場合には標準入力から文字列を受け取り、コマンドライン引数が指定されている場合には、カレントディレクトリに存在する指定されたファイルの読みこみを試みるようなmain関数を作成します。  
以下のコマンドを順次実行してください。  

```shell
git clone https://github.com/HaseU-git/get_next_line
cd get_next_line

echo '#include "get_next_line_bonus.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

# define BAR1 "=============================="
# define BAR2 "------------------------------"
# define END "EOF :)"
# define ERR "ERR :("

int main(int argc, char **argv)
{
    int		fd[argc];
    int		ret;
    int		line_count;
    char	*line;

    if (argc >= 2)
    {
		for (int i = 1; i < argc; i++)
        {
            line_count = 0;
            fd[i] = open(argv[i], O_RDONLY);

            printf("%s\\nFD=%d: %s\\n%s\\n\\n", BAR1, fd[i], argv[i], BAR1);
			do
			{
				ret = get_next_line(fd[i], &line);
                printf("[Return: %d] Line#%4d: %s\\\n\\n", ret, ++line_count, line);
			} while(ret == 1);

            if (ret == -1)
                printf("%s\\n%s\\n", BAR2, ERR);
            else
                printf("%s\\n%s\\n\\n", BAR2, END);
        }
    }
    else
    {
		line_count = 0;

		printf("%s\\nFD=0: STDIN\\n%s\\n\\n", BAR1, BAR1);
        while ((ret = get_next_line(0, &line)) == 1)
            printf("[Return: %d] Line#%4d: %s\\n", ret, ++line_count, line);

        if (ret == -1)
            printf("%s\\n%s\\n", BAR2, ERR);
        else
            printf("%s\\n%s\\n", BAR2, END);
    }

	while (argc >= 0)
	{
        close(fd[argc]);
		argc--;
	}
	return (0);
}' > main.c
```

次に、Cファイルをコンパイルし実行ファイルを作成します。  
この際に、課題の内容で`BUFFER_SIZE`を定義するという指定がありました。  
そのため、`-D`オプションで`BUFFER_SIZE`を定義します。  
また、複数ファイルの読み込みに対応しているのは、`bonus`のついているファイルであるため、これらのファイルをコンパイルしていきます。  

```shell
gcc *bonus*.c main.c -D BUFFER_SIZE=1
```

次に、読み込むためのファイルを作成し、実際に実行ファイルを実行していきます。  
ここでは、`this is a test file.`と`hello world!!`の2つのファイルを作成しテストしていきます。  

```shell
echo -n 'this
is
a
test
file.' > test1.txt

echo -n 'hello
world!!' > test2.txt

./a.out test1.txt test2.txt
```

以下のような表示になっていれば、正常に動作しています。  

```
==============================
FD=3: test1.txt
==============================

[Return: 1] Line#   1: this
[Return: 1] Line#   2: is
[Return: 1] Line#   3: a
[Return: 1] Line#   4: test
[Return: 0] Line#   5: file.
------------------------------
EOF :)

==============================
FD=4: test2.txt
==============================

[Return: 1] Line#   1: hello
[Return: 0] Line#   2: world!!
------------------------------
EOF :)
```

`FD`がファイルディスクリプターを示していて、その右にそれぞれのファイルディスクリプターに対応したファイル名です。  
`Return`の横に書いてあるのが、`get_next_line`の戻り値を示しており、`1`であれば改行文字を正常に読み込んだ、`0`であれば、終端文字を正常に読み込んだ、`-1`であればエラーが発生したことを意味します。  

次に標準入力についてテストしてきます。  
次のコマンドを実行すると、標準入力のための画面になります。  
待機画面に移行したところで、文字列を入力後エンターキーを押すと`get_next_line`が作動します。  
入力待ち画面から抜けたい場合には、`ctrl + D`を入力すると入力を終了することができます。  

最後に、エラー処理についてのテストを行います。  
カレントディレクトリに存在しないファイル名を指定して見ます。  

```shell
./a.out err_test
```

上記のコードを実行し、以下のような表示になれば正常にエラー処理が行われています。  

```
==============================
FD=-1: err_test
==============================

[Return: -1] Line#   1: (null)
------------------------------
ERR :(
```

## 開発環境
- MacBook Pro (15-inch, 2018)
- macOS Big Sur Version 11.2.1
- Apple clang version 12.0.0 (clang-1200.0.32.29)

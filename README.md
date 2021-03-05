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

echo '#include "get_next_line.h"
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

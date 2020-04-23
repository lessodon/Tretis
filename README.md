# Tretis
"that game of bricks"

Este jogo é inspirado no jogo famoso do Brick Game, um dispositivo de jogos eletrônicos portátil que você deve conhecer se nasceu antes de meados de 2010.
Por "inspirado", quero dizer que o Tretis não é um "clone" do jogo original nem almeija ser.


## COMPILANDO E INSTALANDO

0. Clone o jogo com o git ou baixe o pacote zip;
1. Instale no seu Debian-based distro (Ubuntu, Mint, etc.) os pacotes:
-> "gcc", "make" e "libncurses-dev";
2. Execute o comando "make" (sem aspas) na raiz do diretório do jogo descompactado (/bla/bla/bla/Tretis), dentro do terminal.
3. Se compilou, a última linha do make mostra como executar o jogo.


## PERGUNTAS E PROBLEMAS COMUNS

### Como jogo no Android?

Praticamente os mesmos passos, utilizando o Termux (um terminal e portátil shell de Linux).
Mas substitua "gcc" por "clang", e "libncurses-dev" por apenas "ncurses".
Exemplo de instalação dos pacotes anteriores com o Termux, no seu dispositivo Android:

```$ pkg install clang make ncurses```

Você pode alterar o tamanho das fontes no Termux com o gesto de pinça/zoom, assim como faria com uma imagem ou página da web.
Note que se o tamanho da fonte for muito grande, o jogo não vai executar, avisando que a janela do terminal é pequena.
Note que após aberto o jogo, não interessa o tamanho da tela, mas o tijolo vai causar um estrago no seu jogo.


### O jogo/terminal não recebe os comandos do meu teclado!!! (ANDROID)

Considere trocar de teclado. O teclado virtual de várias fabricantes que vem instalado por padrão em seus dispositivos móveis possui um péssimo problema de fazer "buffer" (segurar as teclas até você digitar espaço ou outro símbolo separador) no que não deveria ser "bufferizado" (apps em geral que usam o teclado como controle).

Sugestão: instale o Hacker's Keyboard, ou o troque pelo teclado oficial do Android.

Divirta-se!

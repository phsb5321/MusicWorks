# MusicWorks
Dupla : Mateus Costa Beltrão Tavares, Pedro Henrique Souza Balbino

Como configurar o player: baixar os arquivos em um diretório no terminal , e nele digitar " ./main " (fazer isso com a janela do terminal cheia!!!).

Interface: São 3 janelas. Sendo a da esquerda a janela com todas as musicas disponiveis para ouvir (musicList), a da direita de baixo a fila de reprodução (musicRow) e a outra 
janela a música sendo tocada no momento (music).

Instruções: 
- ↑,↓ : Alternar entre as músicas
- → : Encerrar o programa
- ← : -Ignorar comando-
- 'A' : Adicionar música a fila de reprodução
- 'D' : Remover música da fila de reprodução

Funcionamento do Código : 
- As músicas são referenciadas por um valor inteiro maior que zero. 
- Todos os comandos do programa tem como parâmetro a fila de reprodução que é representado por um array de inteiros "Queue[]", sendo assim, a um limite de músicas na fila.
- A quantidade de zeros no array representa o espaço sobrando na fila.
- A variável Curr guarda a proxima posição livre da fila.
- A variável Highlight armazena a musica que o cursor está apontando.

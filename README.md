# MusicWorks
Dupla : Mateus Costa Beltrão Tavares, Pedro Henrique Souza Balbino

Como configurar o player: baixar os arquivos em um diretório no terminal, digitar make, digitar " ./main " (fazer isso com a janela do terminal cheia!!!).

Interface: São 4 janelas. Sendo a da esquerda a janela com todas as musicas disponiveis para ouvir (musicList), a da direita de baixo a fila de reprodução (musicRow) , a janela acima da "musicRow" , e a primeira a direita, a  música sendo tocada no momento (music) e a do lado mostra o modo de reprodução atual(reproShow).

Instruções: 
- '↑','↓' : Alternar entre as músicas da lista
- '→' : Encerrar o programa
- 'A' : Adicionar música a fila de reprodução
- 'D' : Remover música da fila de reprodução
- 'P' : Play/Pause
- 'N' : Pular para próxima música
- 'R' : Alternar entre modo de reprodução Sequencial/Aleatório

Funcionamento do Código : 
- As músicas são referenciadas por um valor inteiro maior que zero. 
- Todos os comandos do programa tem como parâmetro a fila de reprodução que é representado por um array de inteiros "Queue[]", sendo assim, a um limite de músicas na fila.
- A quantidade de zeros no array representa o espaço sobrando na fila.
- A variável Curr guarda a proxima posição livre da fila e só muda caso alguma música seja adicionada a fila('A') ou removida('D').
- Para adicionar uma música, como há um limite para a fila então curr < 24. E para remover tem que ter música na fila, ou seja, curr >1. 
- A variável Highlight armazena a musica que o cursor está apontando e é atualizada pelos comandos '↑' (caso  highlight > 1) que a decrementa  e '↓' (caso highlight < 27) que a incrementa. 
- A variável repoMode pode assumir valores entre true e false, representando o modo Sequencial e Aleatório, respectivamente. Sendo o modo default o Sequencial.
- Quando o botão 'R' é pressionado se repoMode for true ele vira false e vice-versa.
- A variável endMusic indica se a musíca sendo executada no momento acabou. True se a música acabou e se não false.Ela é iniciada como true porque quando o programa inicia não há nenhuma música tocando("música encerrada"). 
- A variável pause indica se a música atual está em Pause(false) ou Play(true).
- Quando o botão 'P' é pressionado se pause for true ele vira falso e vice-versa.
- Quando 'N' for pressionado o código só vai pular para próxima se Curr > 1, ou seja, se houver música na fila e se  pause = true (música "despausada").
- A variável timer indica quanto tempo (em segundos) resta a música sendo tocada no momento.
- Todas as músicas possuem 10 segundos de duração.
- A variável musicP indica a música sendo tocada no momento.
- O programa encerra quando o loop do main acaba, loop esse que irá rodar enquanto check = false. Ao pressionar '→', check vira true e o loop acaba, encerrando o programa.

Threads :
- Além do main o programa possui 5 threads : play, setPlay, next, row e setRow. Sendo o main, play e row concorrentes entre si e as outras 3 não preemptíveis.
- A thread main é responsável por receber os comandos do teclado, atualizar as janelas "musicList" e "reproShow",inicializar a thread row e chamar a thread next.
- A thread row consiste de um loop infinito que confere se a música sendo tocada acabou (endMusic = true) e se há músicas na fila. Caso hája, ela chama a thread setRow e reinicia o play de novo com a próxima música da fila.
- A thread setRow é chamada pela row para atualizar a queue[], a janela "musicRow", a próxima música a ser tocada(musicP), e curr. SetRow consiste de um if-else que checha  o valor de repoMode. Se o modo for Sequencial(repoMode = true), a próxima música a ser tocada é a primeira da fila (musicP=queue[1]), caso contrário (repoMode = false), a próxima música a ser tocada é decidida de forma aléatória (musicP = queue[1 + rand()%(curr-1)]). O resto do código atualiza a queue[] e a musicRow a partir da posição da música escolhida e no final curr é atualizado(já que será uma música a menos na fila).
- A thread next faz o mesmo que setRow em modo sequencial com a diferença de que ela é chamada pelo main  quando 'N' é pressionado, dependendo apenas de háver música na fila(curr>1) e da músca estar "dispausada",como dito acima. Após ela ser chamada, ainda no main, o play é reiniciado e a próxima música será executada, que será a próxima da fila (musicP = queue[1]).
- A thread play consiste de um loop que para quando o timer acabar (timer = 0), caso o timer acabe ela chama a thread setPlay e espera por 1 segundo(napms(1000)). Após o término do loop ela apaga o que estiver na janela "music" e sinaliza que a música acabou (endMusic = true).
- A thread setPlay pega o timer e o musicP e atualiza a janela "music".

Mutexes : 
- O programa cóntem 2 mutexes para manter a coerência do código : "mutex", "mutex2". E um mutex para implementar o play/pause : "mutexPause".
- Para o "mutexPause" excutar o play/pause ele é auxiliado pela variável pause. Quando  o 'P' for pressionado, se estiver em play (pause = true) o main trava o "mutexPause" e o pause vira false, caso contrário (pause = false) o main libera o "mutexPause" e o pause vira true. Dito isso, a thread play precisa travar o "mutexPause" para prosseguir.
- O "mutex" garante a coerência entre o main e row.
- O "mutex2" garante a coerência entre o main e o play.



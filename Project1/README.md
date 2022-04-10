## Documentação

O nosso objetivo inicial era emular um jogo parecido com o [Letreco](https://www.gabtoschi.com/letreco/), um jogo de adivinhar palavras, que pudesse ser jogado no terminal e faria o uso de threads para a comparação das letras, uma para cada. No entanto, devido ao requerimento de usar multiplas threads, algumas medidas não otimizadas foram tomadas.

- Uma delas é o código utilizado das linhas 118 a 146:
  - O código se faz necessário para que não haja o caso de uma letra já estar na palavra, se ela for digitada novamente em outra posição, não apareça para o jogador que haja multiplas da mesma letra.

Quando lidando com muitas threads e em C, é necessário tomar cuidado com a alocação de memória para as variáveis, como por exemplo, a variavél attempts, que se alocada implicitamente com:

~~~C
attemps = 0
~~~

Era modificada devido a alguma thread invadir o seu espaço de memória e modificar seu valor de volta para 0, colocando o programa num loop infinito até o usuário acertar a palavra.

Portanto foi necessário reservar um endereço de memória para essa variável com o malloc e colocar os valores lá acessando o endereço através da variável ponteiro attempts.

~~~C
int *attempts = malloc(sizeof(int *));

*attempts = 1;
~~~

Como dito anteriormente, a aplicação de threads ao projeto é com o fim realizar as comparações das letras todas ao mesmo tempo. Cada palavra possui 5 letras, portanto, 5 threads foram usadas.

Por fim, foi conveniente, mas não essencial, colocar as estruturas que representam cada caracter (char_block) com a keyword register, para que o compilador salvasse tais variáveis no registro, que é mais rápido de acessar, já que essas variáveis são acessadas diversas vezes ao decorrer do programa.
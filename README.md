## Repositório MC504

Repositório para a disciplina de MC504 - Sistemas Operacionais lecionada por Islene Calciolari Garcia no primeiro semestre de 2022.

## Grupo
- Enrico Piovesana Fernandes **RA:** 233895
- José Augusto Nascimento Afonso Marcos **RA:** 200025

## Documentação
- O nosso objetivo inicial era emular um jogo parecido com o Letreco, no entanto, devido ao requerimento de usar multiplas threads, algumas medidas não optimizadas foram tomadas.
- Uma delas é o código utilizado das linhas 118 a 146:
  - O código se faz necessário para que não haja o caso de uma letra já estar na palavra, se ela for digitada novamente em outra posição, não apareça para o jogador que haja multiplas da mesma letra.
- Quando lidando com muitas threads e em C, é necessário tomar cuidado com a alocação de memória para as variáveis, como por exemplo, a variavél attempts, que se alocada implicitamente com:
>attemps = 0

- Ela era modificada devido a alguma thread invadir o espaço de memória dela e ficava modificando o valor dele de volta para 0, colocando o programa num loop infinito até o usuário acertar a palavra.
- Portanto foi necessário reservar um endereço de memória para essa variável com o malloc e colocar os valores lá acessando o endereço através da variável ponteiro attempts.
>int *attempts = malloc(sizeof(int *));
>
>*attempts = 1;

- Foi conveniente, mas não essencial, colocar as variáveis char com a keyword register, para que o compilador salvasse tais variáveis no registro, que é mais rápido de acessar, já que essas variáveis são acessadas diversas vezes ao decorrer do programa.
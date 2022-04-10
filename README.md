## Repositório MC504

Repositório para a disciplina de MC504 - Sistemas Operacionais lecionada por Islene Calciolari Garcia no primeiro semestre de 2022.

## Grupo
- Enrico Piovesana Fernandes **RA:** 233895
- José Augusto Nascimento Afonso Marcos **RA:** 200025

## Documentação
- Quando lidando com muitas threads e em C, é necessário tomar cuidado com a alocação de memória para as variáveis, como por exemplo, a variavél attempts, que se alocada implicitamente com:
>attemps = 0

- Ela era modificada devido a alguma thread invadir o espaço de memória dela e ficava modificando o valor dele de volta para 0, colocando o programa num loop infinito até o usuário acertar a palavra.
- Portanto foi necessário reservar um endereço de memória para essa variável com o malloc e colocar os valores lá acessando o endereço através da variável ponteiro attempts.
>int *attempts = malloc(sizeof(int *));
>
>*attempts = 1;

- Foi conveniente, mas não essencial, colocar as variáveis char com a keyword register, para que o compilador salvasse tais variáveis no registro, que é mais rápido de acessar, já que essas variáveis são acessadas diversas vezes ao decorrer do programa.


     
     

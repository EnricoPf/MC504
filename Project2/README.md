## Documentação

O objetivo desse projeto era a implementação de uma aplicação multithread utilizando sincronização via semáforos e uma animação para a visualização do progresso da aplicação em tempo real

O problema escolhido veio do livro [Little Book of Semaphores](https://greenteapress.com/wp/semaphores/), o problema escolhido foi o problema apresentado na paǵina 127, o **Problema dos Selvagens Jantando**

## **Problema dos Selvagens Jantando**

    O problema involve um grupo de S selvagens sentados em volta de um pote que pode conter até R refeições. Quando um selvagem quer comer, ele come do pote, a não ser que o pote esteja vazio. Se o pote estiver vazio, o selvagem acorda o cozinheiro, e aí espera até o cozinheiro repor a comida do pote.

## **Questão principal: Como evitar que mais de um selvagem pegue comida do pote (região crítica) ao mesmo tempo?**

    Utilizamos a estratégia de Mutex para evitar o acesso à mesma variável (pote) já que é um caso de exclusão mútua, ou seja, apenas um selvagem por vez tem acesso à variável.

## **Link Para vídeo da explicação**

[Link](https://www.youtube.com/watch?v=mAv3EpJ49L4)


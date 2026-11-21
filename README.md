# Dado Burger
Trabalho final da displina INF01203 - Estruturas de Dados 2026/2, orientado pelo Prof. Dennis Giovani Balreira

---

## Estruturas de Dados

 - `Card`: Lista Duplamente Encadeada com compartamento de pilha (inserções e remoções ocorrem no topo)
 - `cards`: Lista Duplamente Encadeada + HashTable auxiliar (indice da carta representa sua posição no eixo z, em relação às outras cartas)
 - `Recipe`: Lista Simplesmente Encadeada
 - `costumerQueue`: Fila, implementado como Lista Simplesmente Encadeada
 - `AVL`: Arvore Binária de Pesquisa AVL, ordenada por dificuldade
 - `history`: Lista Contigua Dinâmica (Vetor dinâmico), implementado em `dynamic_vector.h`

## Limitações Conhecidas

 - `InitAVL` leva ~2 segundos de execução por conta da geração de números aleatórios, se possível tentar otimizar.
 - Ao comprar uma nova carta se o usuário não a arrastar para um lugar válido ela volta para cima da área da loja
 - Ao inserir uma carta emcima de outra ela vai para o fim da CardList e não para frente da carta onde foi inserido o que causa alguns bugs visuais
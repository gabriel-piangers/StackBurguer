# Dado Burger
Trabalho final da displina INF01203 - Estruturas de Dados 2026/2, orientado pelo Prof. Dennis Giovani Balreira

---

## Estruturas de Dados

 - `Card`: Lista Duplamente Encadeada com compartamento de pilha (inserções e remoções ocorrem no topo)
 - `cards`: Lista Contigua Estática (Vetor)
 - `Recipe`: Lista Simplesmente Encadeada
 - `costumerQueue`: Fila, implementado como Lista Simplesmente Encadeada
 - `AVL`: Arvore Binária de Pesquisa AVL, ordenada por dificuldade
 - `history`: Lista Contigua Dinâmica (Vetor dinâmico), implementado em `dynamic_vector.h`

## Limitações Conhecidas

 - `cards` não tem uma lógica para controlar qual carta está acima (usar uma estrutura similar à LRU cache)
 - `InitAVL` leva ~2 segundos de execução por conta da geração de números aleatórios, se possível tentar otimizar.
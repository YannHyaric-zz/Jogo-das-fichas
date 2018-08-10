# Jogo-das-fichas
# Regras:
Tabuleiro: lista com 2N+1 espaços
Peças: N peças brancas a esquerda e N pretas a direta e um espaço no meio vazio
Objetivo: Inverter a posição das 2 cores

Movimentos:
R1 - Branca com espaço livre a direita, move
R2 - Branca pula uma peça a direita caso possivel
R3 - Preta com espaço livre a esquerda, move
R4 - Preta pula uma peça a esquerda caso possivel

Estrutura:
Vetor estado de tamanho 2N+1;
Peças brancas representadas por 1 a N;
Peças pretas representadas por -N a -1;
Espaço vazio representadas por 0.
Métodos:
Backtraking, Largura, Profundidade, Ordenada:
Lista
Gulosa, A*, IDA*:
Lista, Heurística

Heurística:
Quantas peças fora do lugar;
Quantidade de peças pretas presentes nas N primeiras casas;
Distância da solução podendo haver varias peças em uma casa;
Estrutura da Lista

No:
Ponteito para pai, filho e estado anterior;
Profundidade;
ID;
Vetor estado;

Lista:
Raiz
Tamanho

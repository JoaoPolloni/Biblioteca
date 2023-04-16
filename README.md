# Biblioteca
Gerenciamento de uma biblioteca
Uma biblioteca precisa implementar um sistema eficiente para gerenciar seus livros, que são
representados como nós com informações como título, autor, ano de publicação, entre outros.
A biblioteca precisa permitir a busca rápida de livros por título, autor ou ano de publicação, e
também precisa garantir a integridade dos dados, evitando duplicação de livros.
Requisitos:
1. Busca eficiente: a biblioteca precisa permitir a busca de livros de forma eficiente,
possibilitando a recuperação dos livros em tempo próximo de O(1)em média. Os
principais critérios de busca são título, autor e ano de publicação.
2. Sem duplicação de livros: a biblioteca não pode permitir a inclusão de livros duplicados
em seu acervo, garantindo a integridade dos dados.
3. Manutenção da ordenação: a biblioteca precisa manter os livros ordenados por título,
autor e ano de publicação para facilitar a busca e recuperação dos livros.
4. Inclusão e remoção eficientes: a inclusão e remoção de livros devem ser eficientes em
termos de tempo de execução, para garantir um bom desempenho do sistema.
Solução proposta:
Utilizar uma tabela hash para indexar os livros com base em seus atributos (título, autor e ano
de publicação). Cada entrada na tabela hash irá apontar para uma árvore binária balanceada
que irá armazenar os livros com base no atributo escolhido para indexação. A tabela hash
permitirá a busca rápida de livros com tempo próximo de O(1) em média, enquanto a árvore
binária balanceada garantirá a manutenção da ordenação dos livros e a eficiência na inclusão e
remoção de livros, com tempo de execução próximo de O(log n), onde n é o número de livros
armazenados. Além disso, a tabela hash também garantirá que não haja duplicação de livros,
uma vez que as chaves da tabela hash serão os atributos únicos dos livros. 
Desenvolvido por João Vitor Polloni
RA: 21120606-2     ESOFT5S

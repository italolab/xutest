# Projeto xutest

A xutest é uma biblioteca de testes unitários que pode ser integrada a um projeto C++ para 
realização de testes de unidade. A biblioteca dispõe de macros de assert para verificações e comparações de valores e descobre os casos de teste definidos nos arquivos de código fonte de testes e os carrega numa estrutura de informações das funções de teste.

Logo, para utilizar, basta incluir os cabeçalhos na compilação dos arquivos de teste e carregar a static library do xutest que tem o nome "libxutest.a".

Para uma documentação de uso, você pode acessar: [documentação de uso](https://italolab.github.io/xutest)

## A classe SourceCodeManager

A classe SourceCodeManager definida na pasta "test/sourcecode" é responsável por fazer uma busca nos arquivos de código fonte de teste, a começar pelo programa principal, e, dados os includes do arquivo de código, procurar também nos arquivos de código fonte correspondentes aos includes. Esta função é recursiva. Um arquivo pode ter vários includes para outros arquivos e, estes, podem ter também includes para outros arquivos.

O método de carregamento das informações das funções de teste lê os arquivos e busca neles os includes, os trata, e extrai também as informações dos casos de teste presentes no arquivo. Ignora os comentários.

Atenção: Se tentar executar o executável de testes em outro local, não vai funcionar. Isso porque o método de carregamento de informações dos casos de teste recebe como parâmetro o nome do arquivo de código fonte onde a macro RUN_ALL_TEST_CASES ou RUN_TEST_CASES_MENU é chamada. Essa macro pega o nome do arquivo de código fonte com __FILE__ e passa como parâmetro para as informações dos casos de teste serem carregadas com o processamento desse arquivo e os arquivos inclusos.

Em resumo, a execução do executável de testes depende da presença do código fonte dele!

## O arquivo xutest.h

O arquivo xutest.h da pasta "test/" tem as macros de definição de casos de testes, as macros de assert (ASSERT_EQUALS, ASSERT_TRUE, ...) e as macros de execução de testes e execução do menu de testes onde se pode selecionar mostrar todos os testes ou apenas os testes de uma determinada classe de testes.

## Compilando os testes

Para compilar os testes, se estiver no linux, é necessário informar as seguintes opções no linker: 

```
-ldl -rdynamic
```

Exemplo supondo que os cabeçalhos estão na pasta "include" e a lib está no diretório corrente ("."):

```
g++ -o test main.cpp -L. -lxutest -Iinclude -ldl -rdynamic
```

Isso porque, para descoberta dos casos de testes automaticamente, é necessário executar as funções de teste correspondentes aos casos de teste pelo nome (string) da função. E, para tanto, é necessário utilizar funções da biblioteca "ldfcn.h" (no linux) e (windows.h) no windows, para carregar o programa como se fosse uma shared library e executar as funções de teste como funções da shared library.
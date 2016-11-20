# mpproj
Informações Gerais
==========================
	1. Execute antes make clear para remover arquivos intermediários gerados na compilação e execução do programa;
	2. Compile e rode o programa com make run;
	3. Execute make move para adicionar arquivos necessários para o gconv;
	4. Nunca rode o makefile após uma execução com make run sem antes utilizar make clear; 
	5. Abra index.hmtl na pasta html para ver a documentação em Doxygen.
	
Maiores informações em ``README.txt``.

Installation
---------------
Faça o checkout do projeto
 
        $ git clone https://github.com/swallville/mpproj.git

Instale as bibliotecas de sistema necessárias para usar o programa:
--------------------------------------------------------------------
(vide [https://github.com/google/googletest]), (vide [https://cmake.org]), (vide [https://cmake.org/cmake/help/v3.0/manual/ccmake.1.html])

Getting Help
-----------------

Siga as instruções em https://github.com/google/googletest passo a passo. Além disso, siga os passos abaixo na pasta lib:
  ```
$ cd googletest-master/
$ cd googletest/
$ mkdir build
$ cd build
$ cmake -Dgtest_build_tests=ON -Dgtest_build_samples=ON full_path/lib/googletest-master/googletest
$ make
$ make test
$ ./sample1_unittest
  ```
Contributing
-----------------
1. Fork it.
2. Create a branch (`git checkout -b my_project`)
3. Commit your changes (`git commit -am "Added new feature"`)
4. Push to the branch (`git push origin my_project`)
5. Open a [Pull Request] [1]

Copyright (c) 2016 Lukas Ferreira Machado

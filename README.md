# PROJETO FINAL: OFICINA MECÂNICA (TEMA 2)

###Matheus Filipe de Melo Bispo
– UC16101760 
###Gabriel Messias de Moura Ilha –UC16101214

##Índice 

- Especificação
- Structs
- Diagrama de esquema
- Implementação 


##Especificação

Esse projeto tem o objetivo de administrar e controlar os dados gerados em uma oficina mecânica. O programa será criado em cima de 3 “pilares” ( ** Proprietario, Veiculo e Manutencao ** ), onde esses serão as structs principais do programa, tendo mais 4 structs ( ** Endereço, Telefone, Data e Oficina ** ) “auxiliares”. 
O programa em questão será responsável por cadastrar, alterar e excluir um proprietário e/ou um veículo, onde a manutenção terá apenas a função cadastrar e excluir, respeitando as possíveis regras de alteração e exclusão.
Tendo essas funcionalidades ativas, o programa terá algumas funcionalidades a mais, como, por exemplo, apresentação de todos os dados (proprietários, veículos e manutenções) e pesquisas filtradas, onde serão dadas, pelo usuário, as informações chaves de cada struct principal para suas respectivas pesquisas.

##Structs 

-  ** Proprietario  : **  

````
typedef struct{
	     char nome[TAM_NOME]; // Nome do proprietário 
	     char cpf[TAM_CPF];   // CPF do proprietário ##(chave)##
	     Endereco endereco;   // Endereço do proprietário
	     Telefone telefone;   // Telefone do proprietário
}Proprietario;
````

> A struct do tipo Proprietario é responsável por manipular o arquivo binário “ ** dbProp.dat ** ”, onde será salvo os dados lido por essa struct, para futuros cadastros, alterações, exclusões ou pesquisas.


-	  ** Veiculo:  ** 
```
typedef struct{
	        char placa[TAM_PLACA];     // A placa do veículo ##(chave)##
	        char modelo[TAM_MODELO];   // O modelo do veiculo
	        char fabricante[TAM_FABRICANTE]; // O fabricante do veiculo
	        char chassi[TAM_CHASSI];   // O chassi do veiculo
	        char ano[TAM_ANO];         // O ano de fabricação do veiculo
}Veiculo;
```

> A struct do tipo Veiculo é responsável por manipular o arquivo binário “ ** dbVeic.dat ** ”, onde será salvo os dados lido por essa struct, para futuros cadastros, alterações, exclusões ou pesquisas.



-  ** Manutenção: **
```
typedef struct{
	        char placa[TAM_PLACA];  // A placa do veículo ##(chave)##
	        char cpf[TAM_CPF];      // O cpf do proprietário ##(chave)##
	        char descricao[TAM_DESCRICAO]; // A descrição da manutenção
	        float valorPecas;       // O valor das peças da manutenção
	        float valorObra         //  O valor da mão-de-obra da manut.
	        Data data;              //  A data da manutenção ##(chave)##
}Manutencao;

```

> A struct do tipo Manutenção é responsável por manipular o arquivo binário “ ** dbManut.dat ** ”, onde será salvo os dados lido por essa struct, para futuros cadastros, exclusões ou pesquisas.

- 	 ** Endereço: ** 

```
 typedef struct endereco{
	        char descricao[TAM_DESCRICAO]; // A descrição do endereço
	        char cidade[TAM_CIDADE];       // A cidade do endereço
	        char estado[TAM_ESTADO];       // O estado do endereço
}Endereco;
```	

>	A struct do tipo Endereço é responsável por manipular o endereço ultilizado na  struct **  Proprietario.
 ** 

-  ** 	Telefone: ** 
```
typedef struct telefone{
	        char ddd[TAM_DDD];     // O DDD do telefone
	        char telefone[TAM_TEL];// O telefone
}Telefone;

```

>A struct do tipo Telefone é responsável por manipular o telefone que será utilizado na 
struct de  ** Proprietario ** .

-  ** 	Data: ** 

```
typedef struct data{
	      int dia, mes, ano; 
//Informações acerca da data
}Data;
```

>A struct Data é responsável por manipular a data que será utilizada na struct de 
Manutenção




- 	 ** Oficina: ** 

```
typedef struct oficina{
	char nome[TAM_NOME];                      // Nome da oficina
	char endereco[TAM_NOME];                // Endereço da oficina
}Oficina;
```

>A struct Oficina é responsável por receber os dados da oficina ao inicializar o programa, apresentando o nome e o endereço da oficina durante a execução do programa.

## Diagrama de Esquema

O diagrama de esquema a seguir mostra todos os componentes utilizados nas structs desse projeto, além das informações chaves em destaque

|Proprietário|
|:----------:||:----------:||:----------:||:----------:||:----------:|
|Proprietário| nome|cpf|	endereco|	telefone	|

|Veiculo|
|:----------:|
|placa|	modelo|	fabricante|	chassi|	ano|

|Manutenção|
|:----------:|
|placa	|cpf	|descrição	|valorPecas	|valorObra	|data|

|Endereço|
|:----------:|
|descricao	|cidade|	estado|

|Telefone|
|:----------:|
|ddd|	telefone|

|Data|
|:----------:|
|dia	|mes	|ano|

|Oficina|
|:----------:|
|nome	|endereco|


##Implementação

Esse projeto está sendo desenvolvido por meio da Linguagem de Programação C, utilizando como base a biblioteca windows.h no segundo semestre de 2016. Seu código fonte está disponível com o nome físico  ** Main.c **
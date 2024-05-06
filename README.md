<h1 align="center">Projeto da UC de Sistemas Operativos - 2023/2024</h1>
<h2 align="center">Orquestrador de Tarefas</h2>

## Definição
Serviço de orquestração (i.e., execução e escalonamento) de tarefas num computador.

## Cliente e Servidor
### Cliente:
- O programa cliente é de execução imediata, sendo que não espera por respostas das tarefas executadas pelo servidor (além do comando ```status```).
- Este envia pedidos ao servidor e termina a sua execução.
- O resultado das tarefas é guardado e pode ser consultado na pasta [out](https://github.com/Pedrosilva03/so-orchestrator/tree/main/out)
### Servidor:
- O servidor é executado infinitamente, esperando de forma persistente por pedidos de clientes.
- Para cada pedido, cria processos para lidarem com eles e devolve ao cliente o ID atribuído.
- O ID de cada tarefa é um número entre 1 e 100000 gerado aleatoriamente
- Este faz também a gestão da fila de espera de tarefas.

## Funcionalidades
Nota: Todos os comandos listados assumem que o ```PWD``` é a raiz do repositório ```so-orchestrator```

### Compilação
- O código deve ser compilado usando o comando
```console
make
```
- Os artifactos de compilação podem ser removidos com o comando
```console
make clean
```
- E os resultados das tarefas com o comando
```console
make cleanout
```

### Cliente:
- O cliente pode pedir por uma execução de uma tarefa, uma pipeline de programas ou por um estado do servidor.
- As instruções listadas a seguir podem também ser obtidas ao executar o cliente sem argumentos ```./bin/client```

#### Execução
Um pedido de execução pode ser feito através do argumento execute:
- Programa individual:
```console
./bin/client execute time -u "programa [args]"
```
- Pipeline:
```console
./bin/client execute time -p "programa1 [args] | programa2 [args] | programa3 [args] | ..."
```
- ```time``` Representa o tempo estimado de execução da tarefa e será levado em conta pelo servidor para aplicação das políticas de escalonamento.
- ```flag``` Que pode ser ```-u``` ou ```-p``` dependendo se se pretende executar um programa ou uma pipeline de programas.
- Os programas devem ser escritos entre aspas exatamente como mostrado nos comandos.
- A pipeline pode executar ```N``` programas, sendo considerada como uma única tarefa aos olhos do servidor.
- São incluidos alguns programas de teste na pasta [programs](https://github.com/Pedrosilva03/so-orchestrator/tree/main/programs) mas qualquer programa pode ser usado desde que seja enviado o seu caminho correto.

#### Status
Um pedido de status pode ser feito para consultar o estado das tarefas enviadas para o servidor.
```console
./bin/client status
```
O servidor responderá com uma lista das tarefas em execução, em espera e executadas, junto com os seus IDs e nomes.

### Servidor:
O servidor deve ser executado com 3 argumentos:
```console
./bin/orchestrator output_folder parallel_tasks sched_policy
```
- ```output_folder``` Representa o local onde os resultados das tarefas serão guardadas.
- ```parallel_tasks``` Representa o número máximo de tarefas que podem ser executadas pelo servidor ao mesmo tempo.
- ```sched_policy``` Representa a política de escalonamento a utilizar pelo servidor para executar as tarefas.

## Mais sobre as políticas de escalonamento
O servidor essencialmente consegue executar com duas políticas de escalonamento que devem ser passadas como argumento.
### ```FCFS``` (First Come, First Serve):
- O servidor escolhe a tarefa no topo da fila de espera para executar.
- As tarefas são executadas por ordem de chegada.
- O seu tempo previsto não tem influência na escolha do servidor.
### ```SJF``` (Shortest Job First):
- O servidor escolhe as tarefas com tempo estimado de execução menor.
- Não garante que as tarefas mais rápidas vão ser executadas primeiro, simplismente confia no tempo estimado.

## Testes
É possível testar os tempos de execução das várias políticas com as mesmas tarefas
```console
make test
```
- O programa será compilado e ambas as políticas serão aplicadas junto com um conjunto de tarefas aleatórias.
- Será também medido o tempo de execução de cada uma.

## Conclusão
Trabalho realizado por Pedro Silva, António Silva e Duarte Leitão no âmbito da UC de Sistemas Operativos.

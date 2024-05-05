#!/bin/bash

# Defina o diretório de saída e o número de execuções
output_dir="../so-orchestrator/out/"
tmp_dir="../so-orchestrator/tmp/"
num_execucoes=1

make clean
make cleanout
make

# Defina a lista de políticas de escalonamento
politicas=("FCFS" "SJF")

# Defina os comandos do cliente
comando_executar="./bin/client execute 1000 -u"
comando_pipeline="./bin/client execute 10 -p"
comando_status="./bin/client status"

# Função para executar o servidor com uma política de escalonamento específica
executar_servidor() {
    truncate -s 0 $tmp_dir/finished.txt 
    politica="$1"
    echo "Iniciando o servidor com política de escalonamento: $politica"
    
    # Início da medição do tempo
    start_time=$(date +%s)
    
    ./bin/orchestrator "$output_dir" "$num_execucoes" "$politica" &
    servidor_pid=$!

    # Aguarde um breve momento para o servidor iniciar completamente
    sleep 0.1

    # Envie os mesmos pedidos para o servidor
    echo "Enviando pedidos para o servidor..."
    for ((i = 0; i < num_execucoes; i++)); do
        # Envie os pedidos para o servidor
        $comando_executar "../so-orchestrator/programs/hello 3" >/dev/null
        $comando_pipeline "cat "../so-orchestrator/programs/file.txt" | grep "palavra" | wc -l" >/dev/null
        $comando_executar "../so-orchestrator/programs/hello 3" >/dev/null
        $comando_pipeline "cat "../so-orchestrator/programs/file.txt" | grep "palavra" | wc -l" >/dev/null
        $comando_executar "../so-orchestrator/programs/hello 3" >/dev/null
        $comando_pipeline "cat "../so-orchestrator/programs/file.txt" | grep "palavra" | wc -l" >/dev/null
        $comando_executar "../so-orchestrator/programs/hello 3" >/dev/null
        $comando_pipeline "cat "../so-orchestrator/programs/file.txt" | grep "palavra" | wc -l" >/dev/null
        ./bin/client close
    done

    # Aguarde até que todos os pedidos tenham sido processados
    while ! grep -q "All tasks finished" "$tmp_dir/finished.txt"; do
        sleep 0.1
    done

    # Fim da medição do tempo
    end_time=$(date +%s)

    # Calcular o tempo de execução
    execution_time=$((end_time - start_time))

    # Exibir o tempo de execução
    echo -e "\nTempo de execução com política $politica: $execution_time segundos\n"

    # Encerre o servidor
    kill $servidor_pid
    wait $servidor_pid 2>/dev/null
}

# Iterar sobre as diferentes políticas de escalonamento
for politica in "${politicas[@]}"; do
    executar_servidor "$politica"
done

make clean
make cleanout

all: folders orchestrator client

orchestrator: bin/orchestrator
client: bin/client

folders:
	@mkdir -p src obj bin tmp obj/orchestrator obj/client obj/utils

# SERVER

bin/orchestrator: obj/orchestrator/orchestrator.o obj/utils/utils.o obj/orchestrator/handler.o obj/orchestrator/task.o obj/orchestrator/db.o obj/orchestrator/escalonador.o obj/orchestrator/program.o
	gcc -g obj/orchestrator/orchestrator.o obj/utils/utils.o obj/orchestrator/handler.o obj/orchestrator/task.o obj/orchestrator/db.o obj/orchestrator/escalonador.o obj/orchestrator/program.o -o bin/orchestrator

obj/orchestrator/orchestrator.o: src/orchestrator/orchestrator.c
	gcc -Wall -g -c src/orchestrator/orchestrator.c -o obj/orchestrator/orchestrator.o

obj/orchestrator/handler.o: src/orchestrator/handler.c
	gcc -Wall -g -c src/orchestrator/handler.c -o obj/orchestrator/handler.o

obj/orchestrator/task.o: src/orchestrator/task.c
	gcc -Wall -g -c src/orchestrator/task.c -o obj/orchestrator/task.o

obj/orchestrator/db.o: src/orchestrator/db.c
	gcc -Wall -g -c src/orchestrator/db.c -o obj/orchestrator/db.o

obj/orchestrator/escalonador.o: src/orchestrator/escalonador.c
	gcc -Wall -g -c src/orchestrator/escalonador.c -o obj/orchestrator/escalonador.o

obj/orchestrator/program.o: src/orchestrator/program.c
	gcc -Wall -g -c src/orchestrator/program.c -o obj/orchestrator/program.o

# CLIENT

bin/client: obj/client/client.o obj/utils/utils.o
	gcc -g obj/client/client.o obj/utils/utils.o -o bin/client

obj/client/client.o: src/client/client.c
	gcc -Wall -g -c src/client/client.c -o obj/client/client.o

# UTILS

obj/utils/utils.o: src/utils/utils.c
	gcc -Wall -g -c src/utils/utils.c -o obj/utils/utils.o

clean:
	rm -f obj/orchestrator/* obj/client/* obj/utils/* tmp/* bin/*
	@rmdir bin obj/client obj/orchestrator obj/utils obj tmp

# Apaga todos os ficheiros de output de tarefas

cleanout:
	rm -f out/*.txt
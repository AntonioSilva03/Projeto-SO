all: folders orchestrator client

orchestrator: bin/orchestrator
client: bin/client

folders:
	@mkdir -p src obj bin tmp obj/orchestrator obj/client

bin/orchestrator: obj/orchestrator/orchestrator.o
	gcc -g obj/orchestrator/orchestrator.o -o bin/orchestrator

obj/orchestrator/orchestrator.o: src/orchestrator/orchestrator.c
	gcc -Wall -g -c src/orchestrator/orchestrator.c -o obj/orchestrator/orchestrator.o

bin/client: obj/client/client.o
	gcc -g obj/client/client.o -o bin/client

obj/client/client.o: src/client/client.c
	gcc -Wall -g -c src/client/client.c -o obj/client/client.o

clean:
	rm -f obj/orchestrator/* obj/client/* tmp/* bin/*
	@rmdir bin obj/client obj/orchestrator obj tmp
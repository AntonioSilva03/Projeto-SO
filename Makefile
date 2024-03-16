all: folders orchestrator client

orchestrator: bin/orchestrator
client: bin/client

folders:
	@mkdir -p src obj bin tmp obj/orchestrator obj/client obj/utils

bin/orchestrator: obj/orchestrator/orchestrator.o obj/utils/utils.o
	gcc -g obj/orchestrator/orchestrator.o obj/utils/utils.o -o bin/orchestrator

obj/orchestrator/orchestrator.o: src/orchestrator/orchestrator.c
	gcc -Wall -g -c src/orchestrator/orchestrator.c -o obj/orchestrator/orchestrator.o

bin/client: obj/client/client.o obj/utils/utils.o
	gcc -g obj/client/client.o obj/utils/utils.o -o bin/client

obj/client/client.o: src/client/client.c
	gcc -Wall -g -c src/client/client.c -o obj/client/client.o

obj/utils/utils.o: src/utils/utils.c
	gcc -Wall -g -c src/utils/utils.c -o obj/utils/utils.o

clean:
	rm -f obj/orchestrator/* obj/client/* obj/utils/* tmp/* bin/*
	@rmdir bin obj/client obj/orchestrator obj/utils obj tmp
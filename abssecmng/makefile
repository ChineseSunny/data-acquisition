.PHONY:clean all

WORKDIR=.
VPATH = ./src

CC=g++
CFLGS= -Wall -g -I$(WORKDIR)/inc/
LIBFLAG = -L$(HOME)/lib

# 
BIN = keymngclient  keymngserver

all:$(BIN)

keymngclient:keymngclient.o keymngclientapp.o keymngclientop_sunny.o keymngclientop_wxy.o keymnglog.o myipc_shm.o keymng_shmop.o
	$(CC) $(LIBFLAG) -lpthread -litcastsocket -lmessagereal $^ -o $@ 

keymngserver:keymngserver.o  keymnglog.o keymngserverapp.o keymngserverop_lisi.o   myipc_shm.o  keymng_shmop.o keymng_dbop.o 
	$(CC) $(LIBFLAG) $^ -o $@ -lpthread -litcastsocket -lmessagereal  -lclntsh  -licdbapi
 
#testdbapi:testdbapi.o  
#	$(CC) $(LIBFLAG) $^ -o $@ -lpthread  -lclntsh  -licdbapi
		
%.o:%.cpp
	$(CC) $(CFLGS) -c $< -o $@	

clean:
	rm -f *.o $(BIN)
	
	
	





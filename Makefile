CC=g++

APP=curlfoo

$(APP): $(APP).o
	$(CC) -o $(APP) $(APP).o  -larchive -lcurl

$(APP).o: $(APP).cpp
	$(CC) -O3 -o $(APP).o -c $(APP).cpp 

clean:
	rm -f $(APP) *.o 

CC=g++

APP=dbupdate

$(APP): $(APP).o lensfun_dbupdate.o
	$(CC) -o $(APP) $(APP).o lensfun_dbupdate.o  -larchive -lcurl

$(APP).o: $(APP).cpp
	$(CC) -O3 -o $(APP).o -c $(APP).cpp 
	
lensfun_dbupdate.o: lensfun_dbupdate.cpp
	$(CC) -O3 -o lensfun_dbupdate.o -c lensfun_dbupdate.cpp

clean:
	rm -f $(APP) *.o 

#include <iostream>
#include "lensfun_dbupdate.h"

//print error and exit:

void err(std::string msg)
{
	printf("Error: %s\n",msg.c_str());
	exit(0);
}


int main(int argc, char ** argv)
{
	int dbversion = 1;
	if (argc >= 2) dbversion = atoi(argv[1]);
	
	switch (lensfun_dbupdate(dbversion)) {
		case LENSFUN_DBUPDATE_OK: std::cout << "database updated" << std::endl; break;
		case LENSFUN_DBUPDATE_NOVERSION: std::cout << "no version available" << std::endl; break;
		case LENSFUN_DBUPDATE_CURRENTVERSION: std::cout << "local database is latest" << std::endl; break;
		case LENSFUN_DBUPDATE_RETRIEVFAIL: std::cout << "database retrieve failed" << std::endl; break;
	}
	
}


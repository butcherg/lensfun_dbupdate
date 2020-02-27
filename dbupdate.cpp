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
	lf_db_return result; 

	if (argc == 2 && std::string(argv[1]) == "help") {
		std::cout << "\nUsage: dbupdate [version] [localpath] [url]\n\n";
		std::cout << "Where:\n";
		std::cout << "\tversion:\tlensfun database version to be retrieved.\n\t\t\tDefault=1\n\n";
		std::cout << "\tlocalpath:\talready-existing path in which to install version_x directory\n\t\t\tcontaining the lensfun XMl files and timestamp.txt.\n\t\t\tDefault=cwd\n\n";
		std::cout << "\turl:\t\tURL of the lensfun database repository.\n\t\t\tDefault=http://lensfun.sourceforge.net/db/\n\n";
		std::cout << "Note: using any of the above parameters requires specifying the preceding parameters.\n\n"; 
		exit(1);
	}

	if (argc == 1) result = lensfun_dbupdate(1); //defaults
	else if (argc == 2) result = lensfun_dbupdate(atoi(argv[1])); //version
	else if (argc == 3) result = lensfun_dbupdate(atoi(argv[1]), std::string(argv[2])); //version + localpath
	else if (argc >= 4) result = lensfun_dbupdate(atoi(argv[1]), std::string(argv[2]), std::string(argv[3]));//version + localpath + url
	
	switch (result) {
		case LENSFUN_DBUPDATE_OK: std::cout << "database updated" << std::endl; break;
		case LENSFUN_DBUPDATE_NOVERSION: std::cout << "no version available" << std::endl; break;
		case LENSFUN_DBUPDATE_CURRENTVERSION: std::cout << "local database is latest" << std::endl; break;
		case LENSFUN_DBUPDATE_RETRIEVFAIL: std::cout << "database retrieve failed" << std::endl; break;
	}
	
}


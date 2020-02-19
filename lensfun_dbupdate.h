#ifndef LENSFUN_DBUPDATE_H
#define LENSFUN_DBUPDATE_H

enum lf_db_return {
	LENSFUN_DBUPDATE_OK,
	LENSFUN_DBUPDATE_NOVERSION,
	LENSFUN_DBUPDATE_CURRENTVERSION,
	LENSFUN_DBUPDATE_RETRIEVFAIL
};

lf_db_return lensfun_dbupdate(int argc, char ** argv);

#endif

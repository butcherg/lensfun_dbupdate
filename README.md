# lensfun_dbupdate
Cross-platform C++ program to update lensfun databases.  All code in this repository is licensed GPL2.

A quite-hacky command line program that'll access lensfun.sourceforge.net to check timestamps, check available versions, 
download a specified version, and unpack it in the relevant directory.   Behavior is roughly equivalent to the 
lensfun-update-data python script in the lensfun source tree.

Of note is that all the guts of the program are implemented in the lensfun_dbupdate.h/cpp source.  There's one exposed 
function:

<pre>lf_db_return lensfun_dbupdate(int version, std::string dbpath=std::string());</pre>

which does all the work, and is ready for incorporation in other software.

# Dependencies:

- libcurl: does the file retrieval
- libarchive: unpacks the tar.bz2 database packages

These are available in most package libraries, including MSYS2.  In Ubuntu/Debian:

<pre>$ sudo apt-get install libcurl-dev libarchive-deb</pre>

# Compiling

<pre>$ make</pre>

(there's no make install... put the executable in a directory covered by your PATH.)

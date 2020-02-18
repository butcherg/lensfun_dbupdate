#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <curl/curl.h>
//#include "json.hpp"

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>


#include <string>
#include <vector>
#include <iostream>
#include <algorithm>


std::vector<std::string> filelist()
{
	std::vector<std::string> files;
        DIR *dir = NULL;
        struct dirent *drnt = NULL;

        dir=opendir(".");
        if(dir)
        {
                while(drnt = readdir(dir))
                {
			std::string file = std::string(drnt->d_name);
			if (file == "." | file == "..") continue;
			files.push_back(file);
                }
                closedir(dir);
        }
	return files;
}

std::string string_format(const std::string fmt, ...) 
{
    int size = ((int)fmt.size()) * 2 + 50;   // Use a rubric appropriate for your code
    std::string str;
    va_list ap;
    while (1) {     // Maximum two passes on a POSIX system...
        str.resize(size);
        va_start(ap, fmt);
        int n = vsnprintf((char *)str.data(), size, fmt.c_str(), ap);
        va_end(ap);
        if (n > -1 && n < size) {  // Everything worked
            str.resize(n);
            return str;
        }
        if (n > -1)  // Needed size returned
            size = n + 1;   // For null char
        else
            size *= 2;      // Guess at a larger size (OS specific)
    }
    return str;
}

//from https://stackoverflow.com/questions/8520560/get-a-file-name-from-a-path, Pixelchemist:
template<class T>
T base_name(T const & path, T const & delims = "/\\")
{
  return path.substr(path.find_last_of(delims) + 1);
}
template<class T>
T remove_extension(T const & filename)
{
  typename T::size_type const p(filename.find_last_of('.'));
  return p > 0 && p != T::npos ? filename.substr(0, p) : filename;
}

std::vector<std::string> split(std::string s, std::string delim)
{
        std::vector<std::string> v;
        if (s.find(delim) == std::string::npos) {
                v.push_back(s);
                return v;
        }
        size_t pos=0;
        size_t start;
        while (pos < s.length()) {
                start = pos;
                pos = s.find(delim,pos);
                if (pos == std::string::npos) {
                        v.push_back(s.substr(start,s.length()-start));
                        return v;
                }
                v.push_back(s.substr(start, pos-start));
                pos += delim.length();
        }
        return v;
}


std::string removeall(std::string str, char c)
{
	std::string out = str;
	out.erase(std::remove(out.begin(), out.end(), c), out.end());
	return out;
}

//std::vector<std::string> parseLensfunVersions(std::string json)
//{
//	json.
//
//}






struct MemoryStruct {
  char *memory;
  size_t size;
};
 
static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;
 
  char *ptr = (char *) realloc(mem->memory, mem->size + realsize + 1);
  if(ptr == NULL) {
    /* out of memory! */ 
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }
 
  mem->memory = ptr;
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;
 
  return realsize;
}

std::string getAsString(std::string url)
{
	std::string out;
	CURL *curl_handle;
	CURLcode res;
 
	struct MemoryStruct chunk;
 
	chunk.memory = (char *) malloc(1);  /* will be grown as needed by the realloc above */ 
	chunk.size = 0;    /* no data at this point */ 
 
	curl_global_init(CURL_GLOBAL_ALL);
 
	curl_handle = curl_easy_init();
	curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
	curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
	res = curl_easy_perform(curl_handle);
 
	if(res != CURLE_OK) {
		fprintf(stderr, "curl_easy_perform() failed: %s\n",
			curl_easy_strerror(res));
	}
	else {
		out.assign(chunk.memory,chunk.size);
		printf("%lu bytes retrieved\n", (unsigned long)chunk.size);
	}
 
	curl_easy_cleanup(curl_handle);
	free(chunk.memory);
	curl_global_cleanup();

	return out;

}


bool getAndSaveFile(std::string url)
{
	bool result = true;
	CURL *curl;
	CURLcode res;
	std::string dbfile = base_name(url);
	printf("dbfile: %s\n",dbfile.c_str());
 
	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");

		FILE *f = fopen(dbfile.c_str(), "wb");
		if (f) {
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, f);
			res = curl_easy_perform(curl);
			if(res != CURLE_OK) {
				fprintf(stderr, "Error: %s\n",curl_easy_strerror(res));
				result = false;
			}
			fclose(f);
		}
		else result = false;
		curl_easy_cleanup(curl);
	}
	else result = false;

	curl_global_cleanup();
	return result;
}





int main(int argc, char ** argv)
{
	int dbversion = 1;

	std::string versions = getAsString("http://lensfun.sourceforge.net/db/versions.json");
	std::cout << versions << "\n";

	std::string foo = removeall(versions,'[');
	foo = removeall(foo,']');
	std::vector<std::string> fields = split(foo,",");
	int timestamp = atoi(fields[0].c_str());
	bool versionavailable = false;
	for (int i=0; i<fields.size(); i++) if (atoi(fields[i].c_str()) == dbversion) versionavailable = true;
	
	 
	std::cout << "timestamp:" << timestamp << "  versionavailable:" << (versionavailable ? "true" : "false")  << "\n";
	
	std::string dburl = string_format("http://lensfun.sourceforge.net/db/version_%d.tar.bz2",dbversion);

	if (!getAndSaveFile(dburl))
		printf("Error: retrive %s failed.\n",dburl.c_str());
}


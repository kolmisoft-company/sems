#ifndef _msg_logger_h_
#define _msg_logger_h_

#include "atomic_types.h"
#include "AmThread.h"
#include "cstring.h"

#include <set>
#include <string>
using std::set;
using std::string;


struct sockaddr_storage;

class msg_logger
  : public atomic_ref_cnt
{
public:
  msg_logger() {}
  virtual ~msg_logger() {}
  virtual int log(const char* buf, int len,
		  sockaddr_storage* src_ip,
		  sockaddr_storage* dst_ip,
		  cstring method, int reply_code=0)=0;
};

class file_msg_logger
  : public msg_logger
{
  int      fd;
  AmMutex  fd_mut;

  std::set<string> known_destinations;

  int write_src_dst(const string& obj);

public:
  file_msg_logger() : fd(-1) {}
  ~file_msg_logger();

  int  open(const char* filename);
  int log(const char* buf, int len,
	  sockaddr_storage* src_ip,
	  sockaddr_storage* dst_ip,
	  cstring method, int reply_code=0);
};


#endif

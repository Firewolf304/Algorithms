#pragma once
#include <cerrno>
#include <cstring>
#include <fcntl.h>
#include <fuse3/fuse.h>
#include <string>

namespace firewolf::fs {
class TestFS {
public:
  const std::string file_name = "test.inode";
  const std::string file_context = "hello from cpp";

  int getattr(const char *path, struct stat *stbuf, struct fuse_file_info *fi);
  int readdir();
  int open();
  int read();
}
} // namespace firewolf::fs
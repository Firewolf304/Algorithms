module;

#include <cerrno>
#include <cstddef>
#include <cstring>
#include <fcntl.h>
#include <fuse3/fuse.h>
#include <map>
#include <memory>
#include <sstream>
#include <string>

export module firewolf.fs.lib;

import firewolf.fs.types;

namespace firewolf::fs {

export template <typename FileType> class TestFS {
public:
  std::map<std::string, std::shared_ptr<FileType>> files;

  TestFS() {}

  int getattr(const char *path, struct stat *stbuf, struct fuse_file_info *fi) {
    (void)fi;
    std::memset(stbuf, 0, sizeof(struct stat));
    std::string p(path);
    if (p == "/") {
      stbuf->st_mode = S_IFDIR | 0755;
      stbuf->st_nlink = 2;
      return 0;
    }
    return -ENOENT;
  }

  int release(const char *path, struct fuse_file_info *fi) {
    if (fi->fh) {
      auto *kept_ptr =
          reinterpret_cast<std::shared_ptr<firewolf::fs::types::BaseVFile> *>(
              fi->fh);
      delete kept_ptr;
    }
    return 0;
  }

  int open(const char *path, struct fuse_file_info *fi) {
    std::string filename(path + 1);
    if (files.find(filename) == files.end())
      return -ENOENT;
    auto *kept_ptr =
        new std::shared_ptr<firewolf::fs::types::BaseVFile>(files[filename]);
    fi->fh = reinterpret_cast<uint64_t>(kept_ptr);
    return 0;
  }

  int read(const char *path, char *buf, size_t size, off_t offset,
           struct fuse_file_info *fi) {

    auto *kept_ptr =
        reinterpret_cast<std::shared_ptr<firewolf::fs::types::BaseVFile> *>(
            fi->fh);

    std::string content = (*kept_ptr)->getContext();

    if (static_cast<size_t>(offset) >= content.size())
      return 0;
    if (offset + size > content.size())
      size = content.size() - offset;

    std::memcpy(buf, content.c_str() + offset, size);
    return size;
  }
};
} // namespace firewolf::fs
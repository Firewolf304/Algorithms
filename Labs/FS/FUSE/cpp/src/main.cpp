#define FUSE_USE_VERSION 31
#include <fuse3/fuse.h>

#include <algorithm>
#include <filesystem>
#include <fmt/base.h>
#include <iostream>
#include <memory>
#include <string>

// libs
#include "../include/dotenv-cpp.hpp"

// local libs
import firewolf.fs.lib;
import firewolf.fs.types;

struct MyDataType : public firewolf::fs::types::BaseVFile {
  std::string content = "Данные из модульного C++23 шаблона!\n";
  std::string getName() const override { return "my_file.txt"; }
  std::string getContext() override { return content; }
};

using ConcreteFS = firewolf::fs::TestFS<MyDataType>;

static ConcreteFS &get_fs() {
  static ConcreteFS instance;
  return instance;
}

static int fuse_getattr(const char *path, struct stat *stbuf,
                        struct fuse_file_info *fi) {
  return get_fs().getattr(path, stbuf, fi);
}

static int fuse_open(const char *path, struct fuse_file_info *fi) {
  return get_fs().open(path, fi);
}

static int fuse_read(const char *path, char *buf, size_t size, off_t offset,
                     struct fuse_file_info *fi) {
  return get_fs().read(path, buf, size, offset, fi);
}

static int fuse_release(const char *path, struct fuse_file_info *fi) {
  return get_fs().release(path, fi);
}

static int fuse_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
                        off_t offset, struct fuse_file_info *fi,
                        enum fuse_readdir_flags flags) {
  (void)offset;
  (void)fi;
  (void)flags;
  if (std::string(path) != "/")
    return -ENOENT;

  filler(buf, ".", nullptr, 0, FUSE_FILL_DIR_PLUS);
  filler(buf, "..", nullptr, 0, FUSE_FILL_DIR_PLUS);

  for (const auto &[name, file_ptr] : get_fs().files) {
    filler(buf, name.c_str(), nullptr, 0, FUSE_FILL_DIR_PLUS);
  }
  return 0;
}

int main(int argc, char *argv[]) {
  fmt::print("Filepath {}\n", std::filesystem::current_path().c_str());
  dotenv::init(".env");

  struct fuse_operations fs_ops = {};
  fs_ops.getattr = fuse_getattr;
  fs_ops.open = fuse_open;
  fs_ops.read = fuse_read;
  fs_ops.release = fuse_release;
  fs_ops.readdir = fuse_readdir;

  auto test_data = std::make_shared<MyDataType>();
  get_fs().files["testfile.txt"] = test_data;

  fmt::print("Starting FUSE");

  return fuse_main(argc, argv, &fs_ops, nullptr);
}
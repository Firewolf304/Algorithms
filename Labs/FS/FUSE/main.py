import os, stat, errno, sys, pyfuse3, trio, argparse
from pyfuse3 import Operations, default_options


from args import argParams


class TestFS(Operations):
    def __init__(self):
        super().__init__()
        self.file_inode = pyfuse3.ROOT_INODE + 1
        self.file_name = b"hello.txt"
        self.file_context = b"hello, world!"
        
    # output attrs
    async def getattr(self, inode : pyfuse3.InodeT, ctx):
        entry = pyfuse3.EntryAttributes()
        if inode == pyfuse3.ROOT_INODE:
            entry.st_mode = (stat.S_IFDIR | 0o755)
            entry.st_size = 0
        elif inode == self.file_inode:
            entry.st_mode = (stat.S_IFREG | 0o644)
            entry.st_size = len(self.file_content)
        else:
            raise pyfuse3.FUSEError(errno.ENOENT)
        
        # Common required metadata attributes
        entry.st_atime_ns = 0
        entry.st_mtime_ns = 0
        entry.st_ctime_ns = 0
        entry.st_gid = os.getgid()
        entry.st_uid = os.getuid()
        entry.st_ino = inode
        
        return entry
    
    # check file
    async def lookup(self, parent_inode, name, ctx=None):
        if parent_inode != pyfuse3.ROOT_INODE or name != self.file_name:
            raise pyfuse3.FUSEError(errno.ENOENT)
        return await self.getattr(self.file_inode)
    
    # read dir entities for an open dir handle
    async def readdir(self, fh : pyfuse3.InodeT, start_id : int, token : pyfuse3.ReaddirToken):
        if fh != pyfuse3.ROOT_INODE:
            return
        dir_entries = [
            (b'.', pyfuse3.ROOT_INODE),
            (b'..', pyfuse3.ROOT_INODE),
            (self.file_name, self.file_inode)
        ]
        for entry_id, (name, entry_inode) in enumerate(dir_entries[start_id:], start=start_id):
            attr = await self.getattr(entry_inode)
            if not pyfuse3.readdir_reply(token, name, attr, entry_id + 1):
                break
            
    async def open(self, fh : pyfuse3.InodeT, flags, ctx=None):
        if fh != self.file_inode:
            raise pyfuse3.FUSEError(errno.ENOENT)
        if flags & os.O_ACCMODE != os.O_RDONLY:
            raise pyfuse3.FUSEError(errno.EACCES)
        return pyfuse3.FileInfo(fh=fh)
    
    async def read(self, fh : pyfuse3.InodeT, off, size):
        if fh != self.file_inode:
            raise pyfuse3.FUSEError(errno.EBADF)
        return self.file_context[off:off+size]
    async def create(self, parent_fh, name, mode, flags, ctx=None):
        pass
    
    # stat info
    async def statfs(self, ctx=None):
        # no real mount point, fake it
        stat_ = pyfuse3.StatvfsData()
        
        # blocksize
        stat_.f_bsize = 4096
        stat_.f_frsize = 4096
        
        # total stat
        stat_.f_blocks = 1024 * 1024
        stat_.f_bfree = 512 * 1024 
        stat_.f_bavail = 512 * 1024 
        
        # inode stat
        stat_.f_files = 10000
        stat_.f_ffree = 9999
        stat_.f_favail = 9999
        
        stat_.f_namemax = 255
        return stat_

if __name__ == "__main__":
    args = argParams.parse_args()
    
    options = set(default_options)
    options.add("fsname=pyfuse3_dev")
    options.add("auto_unmount")
    
    if args.read_only:
        options.add("ro")
    if args.allow_other:
        options.add("allow_other")
    
    fs = TestFS()
    pyfuse3.init(fs, mountpoint=args.mountpoint, options=options)
    try:
        trio.run(pyfuse3.main)
    except Exception:
        pyfuse3.close()
        print("Umount mountpoint")
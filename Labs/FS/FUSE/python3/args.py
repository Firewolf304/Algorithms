from argparse import ArgumentParser

argParams = ArgumentParser(description="Test FS")
argParams.add_argument("mountpoint", type=str, help="Mount point path")
argParams.add_argument("--allow-other", action="store_true", help="Full access mount point")
argParams.add_argument("--read-only", action="store_true", help="Read only mount point")
argParams.add_argument("--fs-name", type=str, default="my_dev_fs", help="Fs name")
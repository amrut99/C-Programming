
const FILE_NAME_SIZE = 128;
const BUFFER_SIZE = 1024;

typedef string filename_t<FILE_NAME_SIZE>;
typedef long position_t;
typedef long nbytes_t;

struct data_t{
        long n;
        char buffer[BUFFER_SIZE];
};

struct readargs{
        filename_t filename;
        position_t position;
        nbytes_t nbytes;
};

struct writeargs{
        filename_t filename;
        position_t position;
        nbytes_t nbytes;
        data_t towrite;
};
program STATELESS_FS_PROG{
  version STATELESS_FS_VERSION{
	data_t READ(readargs) = 1;
	nbytes_t WRITE(writeargs) = 2;
  } = 1;
} = 0x21234568;

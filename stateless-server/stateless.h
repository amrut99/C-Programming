/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _STATELESS_H_RPCGEN
#define	_STATELESS_H_RPCGEN

#include <rpc/rpc.h>
#define	FILE_NAME_SIZE 128
#define	BUFFER_SIZE 1024

typedef char *filename_t;

typedef long position_t;

typedef long nbytes_t;

struct data_t {
	long n;
	char buffer[BUFFER_SIZE];
};
typedef struct data_t data_t;

struct readargs {
	filename_t filename;
	position_t position;
	nbytes_t nbytes;
};
typedef struct readargs readargs;

struct writeargs {
	filename_t filename;
	position_t position;
	nbytes_t nbytes;
	data_t towrite;
};
typedef struct writeargs writeargs;

#define	STATELESS_FS_PROG	0x21234568
#define	STATELESS_FS_VERSION	1
#define	READ	1
extern  data_t * read_1();
#define	WRITE	2
extern  nbytes_t * write_1();
extern int stateless_fs_prog_1_freeresult();

/* the xdr functions */
extern bool_t xdr_filename_t();
extern bool_t xdr_position_t();
extern bool_t xdr_nbytes_t();
extern bool_t xdr_data_t();
extern bool_t xdr_readargs();
extern bool_t xdr_writeargs();

#endif /* !_STATELESS_H_RPCGEN */

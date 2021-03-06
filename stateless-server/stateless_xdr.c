/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "stateless.h"

bool_t
xdr_filename_t(xdrs, objp)
	register XDR *xdrs;
	filename_t *objp;
{

#if defined(_LP64) || defined(_KERNEL)
	register int *buf;
#else
	register long *buf;
#endif

	if (!xdr_string(xdrs, objp, FILE_NAME_SIZE))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_position_t(xdrs, objp)
	register XDR *xdrs;
	position_t *objp;
{

#if defined(_LP64) || defined(_KERNEL)
	register int *buf;
#else
	register long *buf;
#endif

	if (!xdr_long(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_nbytes_t(xdrs, objp)
	register XDR *xdrs;
	nbytes_t *objp;
{

#if defined(_LP64) || defined(_KERNEL)
	register int *buf;
#else
	register long *buf;
#endif

	if (!xdr_long(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_data_t(xdrs, objp)
	register XDR *xdrs;
	data_t *objp;
{

#if defined(_LP64) || defined(_KERNEL)
	register int *buf;
#else
	register long *buf;
#endif

	int i;
	if (!xdr_long(xdrs, &objp->n))
		return (FALSE);
	if (!xdr_vector(xdrs, (char *)objp->buffer, BUFFER_SIZE,
		sizeof (char), (xdrproc_t) xdr_char))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_readargs(xdrs, objp)
	register XDR *xdrs;
	readargs *objp;
{

#if defined(_LP64) || defined(_KERNEL)
	register int *buf;
#else
	register long *buf;
#endif

	if (!xdr_filename_t(xdrs, &objp->filename))
		return (FALSE);
	if (!xdr_position_t(xdrs, &objp->position))
		return (FALSE);
	if (!xdr_nbytes_t(xdrs, &objp->nbytes))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_writeargs(xdrs, objp)
	register XDR *xdrs;
	writeargs *objp;
{

#if defined(_LP64) || defined(_KERNEL)
	register int *buf;
#else
	register long *buf;
#endif

	if (!xdr_filename_t(xdrs, &objp->filename))
		return (FALSE);
	if (!xdr_position_t(xdrs, &objp->position))
		return (FALSE);
	if (!xdr_nbytes_t(xdrs, &objp->nbytes))
		return (FALSE);
	if (!xdr_data_t(xdrs, &objp->towrite))
		return (FALSE);
	return (TRUE);
}

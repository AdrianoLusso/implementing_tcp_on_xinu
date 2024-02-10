/* tcpcksum.c  -  cksum, tcpcksum */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  localcksum  -  compute a checksum given an address and length
 *------------------------------------------------------------------------
 */
static	uint32	localcksum(
	  char		*addr,		/* Address of items to checksum	*/
	  int32		len		/* Length of items in bytes	*/
	)
{
	uint16	*hptr;			/* Ptr to 16-bit items		*/ 
	int32	i;			/* Counts 16-bit values		*/
	uint16	word;			/* one 16-bit word		*/
	uint32	sum;			/* computed value of checksum	*/

	hptr= (uint16 *) addr;
	sum = 0;
	len = len >> 1;
	for (i=0; i<len; i++) {
		word = *hptr++;
		sum += (uint32) htons(word);
	}

	return sum;
	/*
	sum += 0xffff & (sum >> 16);
	sum = 0xffff & ~sum;
	if (sum == 0xffff) {
		sum = 0;
	}
	return (uint16) (0xffff & sum);
	*/
}

/*------------------------------------------------------------------------
 *  tcpcksum  -  compute the TCP checksum for a packet with IP header
 *		 in host byte order and TCP in network byte order
 *------------------------------------------------------------------------
 */
uint16	tcpcksum(
	struct netpacket *pkt		/* Pointer to packet	*/
	)
{
	uint32	sum;			/* Computed checksum		*/
	uint16	*ptr;			/* Walks along the segment	*/
	uint16	len;			/* Length of the TCP segment	*/
	int32	i;			/* Counts 16-bit items in IP	*/
					/*   source and dest. addrs.	*/
	struct {			/* Pseudo header		*/
		uint32	ipsrc;
		uint32	ipdst;
		byte	zero;
		byte	ipproto;
		uint16	tcplen;
	}	pseudo;

	/* Compute the length of the TCP segment,	*/
	/*   adding a zero byte if the length is odd	*/

	len = pkt->net_iplen - IP_HLEN(pkt);
	kprintf("-------------------------------\n");
	kprintf("................................\n");
	kprintf("EMPIEZA EL CKSUM\n");
	kprintf("-------------------------------\n");
	kprintf("1. Obtiene los datos del ip pseudoheader\n");
	kprintf("len of tcp segment: %x,%d\n",len,len);

	/* Form a pseudo header */

	pseudo.ipsrc   = pkt->net_ipsrc;
	kprintf("pseudo.ipsrc: %x\n",pseudo.ipsrc,pseudo.ipsrc);
	pseudo.ipdst   = pkt->net_ipdst;
	kprintf("pseudo.ipdst: %x\n",pseudo.ipdst,pseudo.ipdst);
	pseudo.zero    = 0;
	kprintf("pseudo.zero: %x\n",pseudo.zero,pseudo.zero);
	pseudo.ipproto = pkt->net_ipproto;
	kprintf("pseudo.ipproto: %x\n",pseudo.ipproto,pseudo.ipproto);
	pseudo.tcplen  = len;
	kprintf("pseudo.tcplen: %x,%d\n",pseudo.tcplen,pseudo.tcplen);


	/* Adjust the length to an even number for the computation */

	if (len % 2) {
		*( ((char *)&pkt->net_tcpsport) + len ) = NULLCH;
		len++;
	}
	kprintf("len of tcp after adjust: %x,%d\n",len,len);
	/* Start the checksum at zero */

	sum = 0;
	kprintf("-------------------------------\n");
	kprintf("2. Suma los datos del ip pseudoheader\n");
	kprintf("segunda parte del ipsrc: %x \n",(pseudo.ipsrc & 0xFFFF));
	sum += (pseudo.ipsrc & 0xFFFF);

	kprintf("primera parte del ipsrc: %x \n",((pseudo.ipsrc >> 16) & 0xFFFF));
	sum += ((pseudo.ipsrc >> 16) & 0xFFFF);

	kprintf("segunda parte del ipdst: %x \n",(pseudo.ipdst & 0xFFFF));
	sum += (pseudo.ipdst & 0xFFFF);

	kprintf("primera parte del ipdst: %x \n",((pseudo.ipdst >> 16) & 0xFFFF));
	sum += ((pseudo.ipdst >> 16) & 0xFFFF);

	kprintf("iprotocol: %x \n",pseudo.ipproto);
	sum += pseudo.ipproto;

	kprintf("tcplen: %x \n",pseudo.tcplen);
	sum += pseudo.tcplen,

	kprintf("pseudoheader sum: %x\n",sum);
	kprintf("-------------------------------\n");
	kprintf("................................\n");
	/* Add in the "pseudo header" values */

	/*
	ptr = (uint16 *)&pseudo;
	for (i = 0; i < 6; i++) {
		kprintf(" ITERACION %d PARA SUMAR PSEUDO HEADER: %x, %d\n",i,*ptr,*ptr);
		//sum += *ptr;
		sum += *ptr;
		ptr++;
	}
	*/

	/* Compute the checksum over the TCP segment */

	//sum += ~localcksum ((char *)&pkt->net_tcpsport, len) & 0xffff;
	sum += localcksum ((char *)&pkt->net_tcpsport, len);

	/* Add overflow */

	sum = (sum & 0xffff) + (sum >> 16);

	/* return 16 bits of the value */

	return ~((sum & 0xffff) + (sum >> 16)) & 0xffff;
}

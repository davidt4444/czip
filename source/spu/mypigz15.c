#define MAXSEG_64K
/* included headers and what is expected from each */
#include <stdio.h>      
						/* fflush(), fprintf(), fputs(), getchar(), putc(), */
                        /* puts(), printf(), vasprintf(), stderr, EOF, NULL,
                           SEEK_END, size_t, off_t */
#include <errno.h>      
						/* errno, EEXIST */
#include <signal.h>     
						/* signal(), SIGINT */

#include "zlib.h"       
						/* deflateInit2(), deflateReset(), deflate(), */
                        /* deflateEnd(), deflateSetDictionary(), crc32(),
                           Z_DEFAULT_COMPRESSION, Z_DEFAULT_STRATEGY,
                           Z_DEFLATED, Z_NO_FLUSH, Z_NULL, Z_OK,
                           Z_SYNC_FLUSH, z_stream */
#include "../zipinfo.h"
#include <spu_mfcio.h>
#include <assert.h>

#define PUT4(a,b) (*(a)=(b),(a)[1]=(b)>>8,(a)[2]=(b)>>16,(a)[3]=(b)>>24)

control_block cb __attribute__ ((aligned (128)));
unsigned char data[65536+32768] __attribute__ ((aligned (128)));

int main(unsigned long long id, addr64 argp)
{
	int i, j, CHUNK;
	//tag mask is 31 
	spu_writech(MFC_WrTagMask, 1 << 31);
	//spu_mfcdma64 has upper and lower address, while spu_mfcdma32 holds just unsigned long long cast as unsigned int	
	spu_mfcdma64(&cb, argp.ui[0], argp.ui[1], sizeof(cb), 31,MFC_GET_CMD);
	(void)spu_mfcstat(2);

	while(1){
		//Wait to start
		i = 0;
		while((i = spu_readch(SPU_RdInMbox)) != cb.id);

		while((CHUNK = spu_readch(SPU_RdInMbox)) == cb.id);
		//Get data
		for(j = 0; j < 4; j++)
		{
			spu_writech(MFC_WrTagMask, 1<<31);
			spu_mfcdma64(&data[(16384*j+32768)], 0, cb.address.ui[1]+(16384*j), 16384, 31, MFC_GET_CMD);
			(void)spu_mfcstat(2);
		}

		//Begin zipping portion
		int ret, flush;
    		unsigned have;
    		z_stream strm;
		unsigned long crc;

		strm.zalloc = Z_NULL;
    		strm.zfree = Z_NULL;
    		strm.opaque = Z_NULL;
    	
		crc = crc32(0L, Z_NULL, 0);
		
		ret = deflateInit(&strm, 6);
		if (ret != Z_OK){
			printf("error %d\n", ret);
        		return ret;
		}
    		// compress until end of file 
	
    		do {
        		strm.avail_in = CHUNK;
				if(CHUNK<65536)
				{
  					flush = Z_FINISH;
				}
				else
				{
					flush = Z_SYNC_FLUSH;
				}
        		strm.next_in = &data[32768];
				crc = crc32(crc, strm.next_in, strm.avail_in);
        		// run deflate() on input until output buffer not full, finish
           		//compression if all of source has been read in 
        		do {
            			strm.avail_out = (CHUNK+32768);
            			strm.next_out = &data[0];
            			ret = deflate(&strm, flush);    // no bad return value 
            			assert(ret != Z_STREAM_ERROR);  // state not clobbered 
            			have = CHUNK - strm.avail_out;
        		} while (strm.avail_out == 0);
        		assert(strm.avail_in == 0);     // all input will be used 
				if(flush == Z_SYNC_FLUSH || flush == Z_FINISH)
					break;
   			} while (1);
		if(CHUNK<65536)
		{
	   		assert(ret == Z_STREAM_END);        // stream will be complete 
		}
		deflateEnd(&strm);

		//Write the crc and total file size to the array
		while((i = spu_readch(SPU_RdInMbox)) != (cb.id));
		spu_writech(SPU_WrOutMbox, 0x12);	
		spu_writech(SPU_WrOutMbox, (strm.total_out));

		while ((i = spu_readch(SPU_RdInMbox)) != 0x9) ;	

		for(j = 0; j < 6; j++){
			mfc_put(&data[j*16384], cb.address.ui[1]+(j*16384), 16384, 20, 0, 0);
			mfc_write_tag_mask(1<<20);
			mfc_read_tag_status_all();
		}


		if(strm.total_out > 98304){
			printf("error");
		}
		spu_writech(SPU_WrOutMbox, 0x10);

		while ((i = spu_readch(SPU_RdInMbox)) != 0x32) ;	
		
		spu_writech(SPU_WrOutMbox, crc);

		while((i = spu_readch(SPU_RdInMbox)) != 0x21);
	        while((i = spu_readch(SPU_RdInMbox)) == 0x21);

		if( i == 0x23){
			break;	
		}
	}

	return 0;
}

	


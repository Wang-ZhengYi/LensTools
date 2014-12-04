#include <stdio.h>
#include "gadget.h"

/*this routine writes particle positions and velocities to a snapshot in Gadget's default
binary file format*/
int writeSnapshot(FILE *fp,struct io_header_1 *header,float *positions,float *velocities,int firstID,int NumPart,char writeVel){

	int k,id,garbage=256;

	//the first 4 bytes are for endianness check
	if(fwrite(&garbage,sizeof(int),1,fp)!=1) return -1;

	//the header comes next
	if(fwrite(header,sizeof(struct io_header_1),1,fp)!=1) return -1;

	//the next 8 bytes are garbage
	if(fwrite(&garbage,sizeof(int),1,fp)!=1) return -1;
	if(fwrite(&garbage,sizeof(int),1,fp)!=1) return -1;

	//positions come next
	if(fwrite(positions,sizeof(float)*3,NumPart,fp)!=NumPart) return -1;

	//if writeVel is set, only the positions are written, and we stop here
	if(!writeVel) return 0;

	//the next 8 bytes are garbage
	if(fwrite(&garbage,sizeof(int),1,fp)!=1) return -1;
	if(fwrite(&garbage,sizeof(int),1,fp)!=1) return -1;

	//velocities come next
	if(fwrite(velocities,sizeof(float)*3,NumPart,fp)!=NumPart) return -1;

	//the next 8 bytes are garbage
	if(fwrite(&garbage,sizeof(int),1,fp)!=1) return -1;
	if(fwrite(&garbage,sizeof(int),1,fp)!=1) return -1;

	//particle IDs come next
	for(k=0;k<NumPart;k++){
		id = firstID + k;
		if(fwrite(&id,sizeof(int),1,fp)!=1) return -1;
	}

	//the next 4 bytes are garbage
	if(fwrite(&garbage,sizeof(int),1,fp)!=1) return -1;


	return 0;
	
}
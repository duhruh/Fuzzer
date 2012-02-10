// Program: Fuzzer
// Authors: David Rivera & Harrison Phillips 
// Date: 2-10-2012

#include <stdio.h>
#include <stdlib.h>



int main(){

    	FILE *ifp;
    	long len=0;
	unsigned char* image;
    	ifp=fopen("image.jpg","rb");
    	fseek(ifp,0,SEEK_END);
    	len = ftell(ifp);

	//Reads in the file and prints out the size
    	image =(unsigned char*) malloc(sizeof(char)*len);	
    	fseek(ifp,0,SEEK_SET);
    	fread(image,1,len,ifp);
    	fclose(ifp);
    	printf("the size is %ld\n",len);
	
	//Converts the special characters to HEX characters
	//then prints them out
	char* buf_str = (char*)malloc(2*len+1);
	char* buf_ptr = buf_str; 
	int i = 0;
	
	for(i = 0; i < len; i++){
		buf_ptr += sprintf(buf_ptr,"%02X",image[i]);		
	}
	
	sprintf(buf_ptr,"\n");
	*(buf_ptr + 1) = '\0';
	printf("%s\n", buf_str);
	
	//Loop the number of generations

	//Mutate the file

	//Execute the mutation   

	//Record the mutation

	return 0;
}

#include <stdio.h>
#include <stdlib.h>



int main(){

    //unsigned char image[];
    FILE *ifp;
    long len=0;
    ifp=fopen("image.jpg","rb");


    fseek(ifp,0,SEEK_END);
    len = ftell(ifp);
unsigned char* image;
    image =(unsigned char*) malloc(sizeof(char)*len);	
    fseek(ifp,0,SEEK_SET);
    fread(image,1,len,ifp);
    fclose(ifp);
    printf("the size is %ld\n",len);
	
	char* buf_str = (char*)malloc(2*len+1);
	char* buf_ptr = buf_str; 
	int i = 0;
	for(i = 0; i < len; i++){
		buf_ptr += sprintf(buf_ptr,"%02X",image[i]);		
	//printf("'%s'",image);	}
	}
sprintf(buf_ptr,"\n");
*(buf_ptr + 1) = '\0';
printf("%s\n", buf_str);
   
return 0;


}

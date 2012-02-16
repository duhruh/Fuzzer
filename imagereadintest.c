// Program: Fuzzer
// Authors: David Rivera & Harrison Phillips 
// Date: 2-10-2012

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>



int main(){

    	FILE *ifp;
	FILE *result;
	FILE *seeds;
    	long len=0;
	unsigned char* image;
	char* fileName = "bug.jpg";
	char fileNum[10];
	int fileCounter = 1;
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
	int i, k = 0;
	
	for(i = 0; i < len; i++){
		buf_ptr += sprintf(buf_ptr,"%02X",image[i]);		
	}
//printf("%s this is the buf_ptr........................\n",buf_ptr);	
	sprintf(buf_ptr,"\n");
	*(buf_ptr + 1) = '\0';
	//printf("%s\n", buf_str);
	//system("PAUSE");	
//printf("%02x this is image at the 2 position......................", image[1]);
	//Loop the number of generations
	for(k = 0; k < 1000; k++){
		//Mutate the file
		int seed = time(NULL);
		srand(seed % 100);
		image[rand()%len]+=rand() %len;
		//Write the file
		//image[3] += 10;
		result = fopen(fileName,"w+");
		for(i = 0; i < len; i++){
			fprintf(result,"%c",image[i]);
		}
		fclose(result);
		//Execute the mutation
		printf("hug-_-");
		//char* systemCall = strcat("./jpegconv -ppm ", fileName);
		//printf("%s",systemCall);
		//long bug = system("./jpegconv -ppm bug.jpg");
		printf("got to the bug line");
		//printf("%ld\n",bug);
		//system("pause");
		//Record the mutation
		if(system("./jpegconv -ppm bug.jpg") < 9999999){
			printf("Bug found!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
			seeds = fopen("seeds.txt","w+");
			fprintf(seeds,"%d",seed);
			//itoa(fileCounter,fileNum,10);
			sprintf(fileNum,"%d",fileCounter);
			//fileName = strcat(strcat("bug",fileNum),".jpg");
			//fileName = strcat("bug",".jpg");
			fileCounter++;
		}
	}

	return 0;
}

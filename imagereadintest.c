// Program: Fuzzer
// Authors: David Rivera & Harrison Phillips 
// Date: 2-10-2012

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void mutate(int seed,int len,unsigned char* image);

int main(){

    	FILE *ifp;
	FILE *result;
	FILE *seeds;
	//FILE *stderr;
    	long len=0;
	unsigned char* image;
	unsigned char* bugedImage;
	char* fileName = "bug.jpg";
	char fileNum[10];
	int fileCounter = 10;
    	ifp=fopen("image.jpg","rb");
    	fseek(ifp,0,SEEK_END);
    	len = ftell(ifp);

	//Reads in the file and prints out the size
    	image =(unsigned char*) malloc(sizeof(char)*len);
	//bugedImage =(unsigned char*) malloc(sizeof(char)*len);	
    	fseek(ifp,0,SEEK_SET);
    	fread(image,1,len,ifp);
    	fclose(ifp);
	seeds = fopen("seeds.txt","w+");
	result = fopen(fileName, "w+");
    	//printf("the size is %ld\n",len);


	//Converts the special characters to HEX characters
	//then prints them out //EDIT not sure what this does
	char* buf_str = (char*)malloc(2*len+1);
	char* buf_ptr = buf_str; 
	int i, k = 0;
	
	for(i = 0; i < len; i++){
		buf_ptr += sprintf(buf_ptr,"%02X",image[i]);		
	}
	
	sprintf(buf_ptr,"\n");
	*(buf_ptr + 1) = '\0';
	/////////////////////////////////////////////////////
	
		
	//Loop the number of generations
	for(k = 0; k < 10; k++){
		
		bugedImage =(unsigned char*) malloc(sizeof(char)*len);	
    		 int q = 0;
		for(q = 0; q < len;q++){
			bugedImage[q] =  image[q];
	//		printf("This is bugedImage: %02X  This image: %02X\n",bugedImage[q],image[q]);
		}	
		
		//Mutate the file
		int seed = abs(time(NULL)*rand());
		srand(seed);
		mutate(seed,len,bugedImage);
		//image[rand()%len] = (image[rand()%len]+rand()) % 5;
		//bugedImage[rand()%len] = (image[rand()%len]+rand())%5;
		//PRINT TO SEEDS IF X ROUNDS HAVE OCCURES
		/*if(k == 5){
			seeds = fopen("seeds.txt","+w");
			fprintf(seeds,"%d",seed);
			fclose(seeds);
		}	*/

		//Write the file
		//result = fopen(fileName,"w+");
		for(i = 0; i < len; i++){
			fprintf(result,"%c",bugedImage[i]);
		}
		free(bugedImage);
		//fclose(result);
		
		//Execute the mutation
		int returnVal = system("./jpegconv -ppm bug.jpg > out.txt");
		//fprintf(stderr, "%d",returnVal);
		//long bug = system("./jpegconv -ppm bug.jpg");
		//Record the mutation
		//printf("This is the returnVal: %d\n",returnVal);
		if(returnVal != 0){
			printf("This is the bugged returnVal: %d\n",returnVal);
			//seeds = fopen("seeds.txt","w+");
			fprintf(seeds,"%d\n",seed);
			sprintf(fileNum,"%d\n",fileCounter);
			//fileName = strcat(strcat("bug",fileNum),".jpg");
			//fileName = strcat("bug",".jpg");
			//fclose(seeds);
			fileCounter++;
		}
	}
	fclose(result);
	fclose(seeds);
	return 0;
}


void mutate(int seed,int len, unsigned char* image){
	int u = 0;
	seed++;
	for(u=abs(seed%len-20); u < len-20; u++){
		//image[u] = image[u] >> 1;
		//printf("This is image: %02X\n", image[u]+1);
		image[u] = image[u]+'F';
		//image[(abs(seed%len-20))+u]=image[u]%5;
	}
}

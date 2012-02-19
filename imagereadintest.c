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
	unsigned char* bugedImage;
	char* fileName = "bug.jpg";
	char fileNum[10];
	int fileCounter = 10;
    	ifp=fopen("image.jpg","rb");
    	fseek(ifp,0,SEEK_END);
    	len = ftell(ifp);

	//Reads in the file and prints out the size
    	image =(unsigned char*) malloc(sizeof(char)*len);
	bugedImage =(unsigned char*) malloc(sizeof(char)*len);	
    	fseek(ifp,0,SEEK_SET);
    	fread(image,1,len,ifp);
    	fclose(ifp);
    	printf("the size is %ld\n",len);


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
    		unsigned int q = 0;
		for(q = 0; q < sizeof(image)/sizeof(char*);q++){
			bugedImage[q] =  image[q];
			printf("This is bugedImage: %02X  This image: %c\n",bugedImage[q],image[q]);
		}	
		
		//Mutate the file
		int seed = time(NULL);
		srand(seed % 100);
		//image[rand()%len] = (image[rand()%len]+rand()) % 5;
		bugedImage[rand()%len] = (image[rand()%len]+rand())%5;
		//PRINT TO SEEDS IF X ROUNDS HAVE OCCURES
		if(k == 5){
			seeds = fopen("seeds.txt","+w");
			fprintf(seeds,"%d",seed);
			fclose(seeds);
		}	

		//Write the file
		result = fopen(fileName,"w+");
		for(i = 0; i < len; i++){
			fprintf(result,"%c",bugedImage[i]);
		}
		free(bugedImage);
		fclose(result);
		
		//Execute the mutation
		int returnVal = system("./jpegconv -ppm bug.jpg > out.txt");
		//long bug = system("./jpegconv -ppm bug.jpg");
		printf("%d\n",returnVal);
		//Record the mutation
		if(2 <1){
			printf("Bug found!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
			seeds = fopen("seeds.txt","w+");
			fprintf(seeds,"%d\n",seed);
			sprintf(fileNum,"%d",fileCounter);
			//fileName = strcat(strcat("bug",fileNum),".jpg");
			//fileName = strcat("bug",".jpg");
			fclose(seeds);
			fileCounter++;
		}
	}

	return 0;
}

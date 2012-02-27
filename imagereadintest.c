// Program: Fuzzer
// Authors: David Rivera & Harrison Phillips 
// Date: 2-10-2012

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

void mutate_new(int len, unsigned char* image);
void mutate(int seed,int len,unsigned char* image);
int myPow(int x, int p){
	int result = 1;
	int inc;
	for(inc = 0; inc < p; ++inc){
		result *= x;
	}
	printf("made it in the pow function!");
	return result;
}

int main(int arge,char** argv){
	if(arge == 0){
		printf("No arge was inputed to program!:%d",arge);
	}
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
    	ifp=fopen("image.jpg","r");
    	fseek(ifp,0,SEEK_END);
    	len = ftell(ifp);
	 int q = 0;
	//Reads in the file and prints out the size
    	image =(unsigned char*) malloc(sizeof(char)*len);
	//bugedImage =(unsigned char*) malloc(sizeof(char)*len);	
    	fseek(ifp,0,SEEK_SET);
    	fread(image,1,len,ifp);
    	fclose(ifp);
	seeds = fopen("seeds.txt","w+");
	result = fopen(fileName, "w");
    	//printf("the size is %ld\n",len);
	int k =0;

	//Converts the special characters to HEX characters
	//then prints them out //EDIT not sure what this does
	/*char* buf_str = (char*)malloc(2*len+1);
	char* buf_ptr = buf_str; 
	int i, k = 0;
	
	for(i = 0; i < len; i++){
		buf_ptr += sprintf(buf_ptr,"%02X",image[i]);		
	}
	
	sprintf(buf_ptr,"\n");
	*(buf_ptr + 1) = '\0';*/
	/////////////////////////////////////////////////////
	int seed = atoi(argv[1]);	
	int loop = atoi(argv[2]);	
	//Loop the number of generations
	for(k = 0; k < loop; k++){
		result = fopen(fileName, "w");
		bugedImage =(unsigned char*) malloc(sizeof(unsigned char)*len);	
		for(q = 0; q < len;q++){
			bugedImage[q] =  image[q];
		//	printf("This is bugedImage: %02X  This image: %02X\n",bugedImage[q],image[q]);
		}	
		//Mutate the file
		//int seed = atoi(argv[1]);
		//int seed = abs(rand());
		srand(seed);
		mutate_new(len, image);
		//mutate(seed,len,bugedImage);
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
		fwrite(bugedImage, 1, len, result);
		/*for(i = 0; i < len; i++){
			fwrite(bugedImage[i], 1, result);
		}*/
		free(bugedImage);
		fclose(result);
		//free(bugedImage);
		//fclose(result);
		
		//Execute the mutation
		int returnVal = system("./jpegconv -ppm bug.jpg 1> out.txt");
		//fprintf(stderr, "%d",returnVal);
		//long bug = system("./jpegconv -ppm bug.jpg");
		//Record the mutation
		//printf("This is the returnVal: %d\n",returnVal);
		if(returnVal != 0){
		//	printf("This is the bugged returnVal: %d\n",returnVal);
			//seeds = fopen("seeds.txt","w+");
			fprintf(seeds,"%d\n",seed);
			sprintf(fileNum,"%d\n",fileCounter);
			//fileName = strcat(strcat("bug",fileNum),".jpg");
			//fileName = strcat("bug",".jpg");
			//fclose(seeds);
			fileCounter++;
			seed = rand();
		}else{
			seed = rand();
		}
	}
	free(image);
	fclose(seeds);
	return 0;
}

void mutate_new(int len, unsigned char* image){
	int i = 0;
	int rand = rand();
	for(i = 0; i < len; ++i){
		if((rand()%100) < 25 && i > 4){
			image[i] = ((int)pow(-1, rand()))*rand()%256;
			image[i] %= 256;
		}else if((rand()%100) > 25 && (rand()%100)< 50 && i > 4){
			image[i] = (image[i] >> rand()) %256;
		}else if((rand()%100) > 50 && (rand()%100)< 75 && i > 4){
			//image[i] += rand()%256;
		}else if((rand()%100) > 75 && (rand()%100)<=100 && i > 4){
			//image[i] = (image[i] << rand())%256;
		}
	}
}

void mutate(int seed,int len, unsigned char* image){
	int u = 5+rand()%len;
	int loop = 5+rand()%len;
	seed++;
	seed--;
	len++;
	len--;
	//image[10] = 100;
	if((loop+5)%len != 0){
		for(u = loop; u < loop+5; u++){
			//image[u] = image[u] >> 1;
			//printf("This is image: %02X\n", image[u]+1);
			//image[u] = (image[u]+(seed%256));
			image[u] = 100;
			//image[(abs(seed%len-20))+u]=image[u]%5;
		}
	}else if((loop+5)%len == 0){
		loop = loop-10;
		for(u = loop; u < loop+5; u++){
			image[u] = 100;
		}
	}
}

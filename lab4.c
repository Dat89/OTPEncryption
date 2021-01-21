#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
 
long int findFileSize(char *file_name)
{
	// opening the file in read mode
	FILE* fp = fopen(file_name, "rb");
   
	// checking if the file exist or not
	if (fp == NULL) {
    	return -1;
	}
	fseek(fp, 0L, SEEK_END);
 
	// calculating the size of the file
	long int sz = ftell(fp);
   
	// closing the file
	fclose(fp);
   
	return sz;
}
//create random key and put into key file
void makeKey(long int size){
    int c = 0;
    int random;
    srand(time(NULL));
	char *keyFile = "key.txt";
	//FILE *keyfp = fopen(keyFile,"r");
    
    FILE *cryptF;
    cryptF=fopen(keyFile,"wb");
    
    for(c=0;c<size-1;c++){
   	 random = rand()%256;
   	 fprintf(cryptF,"%c",random);
    }
    fclose(cryptF);
}
 //write to file, with message, and of similar length
void write_to_file(char* key,long int length){
	char *keyFile = "key.txt";
	FILE *keyfp = fopen(keyFile,"wb");
	fprintf(keyfp,"%s",key);
	fclose(keyfp);
}
 //read through original and key (randomed) XOR them and write to result
void encrypting(char* original,char* key){
    FILE *result = fopen("result.txt","w");
    FILE *originF = fopen(original,"rb");
    FILE *keyFile = fopen(key,"rb");
    
    //size for loop
    long int size = findFileSize(original);
    
    int c; //origin
    int k; //key
    int output;//xor
    
    int i;
    for(i=0;i<size;i++){
   	 c = fgetc(originF);
   	 k = fgetc(keyFile);
   	 output = (c^k);
   	 fprintf(result,"%c",output); //write to result
    }
    fclose(result);
    fclose(originF);
    fclose(keyFile);
}
//using the resultFile (that contain encrypted message) and keyFile XOR it back to and PRINT ONLY
void decrypting(){
	char* keyFile = "key.txt";
	char* resultFile = "result.txt";
    FILE *result = fopen(resultFile,"rb");
    FILE *key = fopen(keyFile,"rb");
	FILE *fourth = fopen("resultingFile.txt","w");
    
    int c; //origin
    int k; //key
    int output;//xor
    
    long int size = findFileSize(keyFile);
    int i;
    printf("DECRYPTED MESSAGE: "); // FIX: WRITE TO THE FILE
    for(i=0;i<size+1;i++){
   	 c = fgetc(result);
   	 k = fgetc(key);
   	 output = (c^k);
   	fprintf(fourth,"%c",output); //a 4th file
	printf("%c",output);
    }
    printf("\n");
	fclose(fourth);
	fclose(key);
	fclose(result);
}
 //read through file and return a string (char*)
char *read_file(char *fileName, long int fileSize){
	FILE *fp = fopen(fileName,"rb");
	//openable
	if(fp == NULL){
    	printf("CANNOT OPEN FILE");
    	exit(0);
	}
	fseek(fp,0,SEEK_END);
	fileSize = ftell(fp);
	//char *item = malloc(fileSize*sizeof(*item)-1);
	char *item = malloc(((int) fileSize)+1); // FIX: Need to check if malloc is successful (null or not)
	if(item == NULL){
		printf("MALLOC FAILED");
	}
	rewind(fp);

	char c;
	int i =0;
	while(c!=EOF){
    	c = getc(fp);
    	item[i] = c;
    	i++;
   }
	return item;
}
 int getInput(char *str){
	printf("Input the read file name: ");
	fgets(str,20,stdin);
	char *p;
	//remove extra trailing newline
	if ((p = strchr(str, '\n')) != NULL) { 
    	*p = '\0'; /* remove newline */
	}
	return 0;	
}
int main(int argc, char *argv[]){
	//char readFile[20];
	char* readFile = "read.txt";
	//getInput(readFile);
	
	char *item = read_file(readFile,findFileSize(readFile)); //get stuff from original file
	//write_to_file("key.txt",item,findFileSize(readFile)); //copy original to key
	free(item); //erase content we read from original file
    
  	 
   //MENU SECTIONW
	int run = 1;
	int input;
	printf("Encypt file: 1\n");
	printf("Decrypt file: 2\n");
	printf("Exit: 3\n");
	while(run == 1){
    	printf("enter choice: ");
    	scanf("%d", &input);
    	if(input == 3){
        	run = 0;
        	printf("EXIT \n");
    	}
		//encrypting
    	else if(input == 1){
        	printf("Encript selected\n");
			//write_to_file(item,findFileSize(readFile)); //copy original to key
        	makeKey(findFileSize(readFile));
        	encrypting(readFile,"key.txt");
			
       	//decrypting
    	}else if(input == 2){
   		 decrypting();
   		 
    	}else{
   		 printf("choice invalid");
   		 break; //weird how C doesn't goes back to scanf hence we need to break completely
    	}
	}
   return 0;
}
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define BUF_SIZE 1024

bool is_vowel(char c) { 
    /* 
     * Returns true if c is a vowel (upper or lower case), and 
     * false otherwise. 
     */

	//here we list the vowel case to verify if a charactor is a vowel or not.	
	switch(c){
		case 'a':
		case 'A':
		case 'e':
		case 'E':
		case 'i':
		case 'I':
		case 'o':
		case 'O':
		case 'u':
		case 'U':
			return true;
		default:
			return false;
	}

}

int copy_non_vowels(int num_chars, char* in_buf, char* out_buf) {
    /*
     * Copy all the non-vowels from in_buf to out_buf. 
     * num_chars indicates how many characters are in in_buf, 
     * and this function should return the number of non-vowels that
     * that were copied over.
     */
	//set a variable to store the number of non vowels.
	int notVowel = 0;

	for(int i=0; i<num_chars; i++){                       //for loop to go through each charactor
		if(!(is_vowel(in_buf[i]))){                   //if it is not a vowel      
			out_buf[notVowel] = in_buf[i];        //we put that charactor in to the out_buf array
			notVowel = notVowel+1;                //increase 1 of the number of not vowels.
		}
	}
	//return the number of not vowels.
	return notVowel;
}

void disemvowel(FILE* inputFile, FILE* outputFile) { 
    /*
     * Copy all the non-vowels from inputFile to outputFile.
     * Create input and output buffers, and use fread() to repeatedly read
     * in a buffer of data, copy the non-vowels to the output buffer, and
     * use fwrite to write that out. 
     */

	// create two buffers to store the input and output, respectively.
	char* inbuf = calloc(BUF_SIZE, sizeof(char));
	char* outbuf = calloc(BUF_SIZE, sizeof(char));
	
	int size;
	int chaNum;

	//need a flag to tell us if goes to the end of the file.
	bool flag;

	flag = true;
	while(flag){
		chaNum = fread(inbuf, 1, BUF_SIZE, inputFile);   //read the input file
		if (chaNum == 0){                                //when we goes to the end of the file
			flag = false;                            //turn our flag into false
		}
		size = copy_non_vowels(chaNum, inbuf, outbuf);
		
		fwrite(outbuf,1,size,outputFile);  //write output file
	}
	
	//free to not have leaking
	free(inbuf);
	free(outbuf);
	//close these files.
	fclose(inputFile);
    	fclose(outputFile);



}

int main(int argc, char *argv[]) { 
    FILE *inputFile; 
    FILE *outputFile;

    // Code that processes the command line arguments 
    // and sets up inputFile and outputFile.
    
    //based on the requirement, we have 3 situations:
    if(argc ==1){   
    	inputFile = stdin;
	outputFile = stdout;
    }else if(argc == 2){
    	inputFile = fopen(argv[1],"r");
	outputFile = stdout;
    }else if(argc ==3){
    	inputFile = fopen(argv[1],"r");
	outputFile = fopen(argv[2],"w");
    }else{
    	printf("Sorry, please try again.");
	return -1;
    }

    disemvowel(inputFile, outputFile);

    return 0; 
}





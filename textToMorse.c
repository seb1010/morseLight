#include <stdio.h>

void makeOutputFile(unsigned char[], int);
void toMorse(char [], unsigned int [], int);
void inputTextFile(char fileName[], char inputChars[]);
int getNumInputChars(char fileName[]);
int createMorseBytes(unsigned int [], unsigned char [], int);
void toUpperCase(char[], int);

int main(int argc, char *argv[]){ 

int numInputChars;


  if (argc == 2){
    numInputChars = getNumInputChars(argv[1]);
    if(numInputChars > 0){
      char inputFileArray[numInputChars + 3];
      unsigned int morseLetterArray[numInputChars + 3];
      unsigned char morseBytes[numInputChars * 4];
      int numMorseBytes;
 
      inputTextFile(argv[1], inputFileArray);
      toUpperCase(inputFileArray, numInputChars);
      toMorse(inputFileArray, morseLetterArray, numInputChars);
      numMorseBytes = createMorseBytes(morseLetterArray, morseBytes, numInputChars);
      makeOutputFile(morseBytes, numMorseBytes);
    }
  }
  else if(argc > 2){
    printf("only one file plz");
  }
  else{
    printf("you forgot to enter the name of the input file\n\n");
  }

}

void makeOutputFile(unsigned char bytesIn[], int length){
  int i = 0;
  FILE *outputFile;

  outputFile = fopen("morseTable.asm", "w");

  fprintf(outputFile, "morseTable:\n");
  for(i=0;i<length; i+=2){

    fprintf(outputFile, ".dw $");

    if(bytesIn[i + 1] < 0x10)
      fprintf(outputFile, "0");
    fprintf(outputFile, "%x", bytesIn[i + 1]);

    if(bytesIn[i] < 0x10)
      fprintf(outputFile, "0");
    fprintf(outputFile, "%x\n", bytesIn[i]);

}
  fclose(outputFile);

}

int createMorseBytes( unsigned int lettersIn[], unsigned char bytesOut[], int numLetters){
  int i = 0;
  int j = 0;
  int bitsLeftInChar = 8;
  int bitsInLetter;
  int letterToMod;
  int oldLetterToMod;
  int numShifts;
  int twoToTheShift;

  for(i=0; i < numLetters * 4; i++)
    bytesOut[i] = 0;

  for(i=0; i < numLetters - 1 ; i++){
    oldLetterToMod = lettersIn[i];
//printf("\n\ni = %d\n", i);
    letterToMod = lettersIn[i];
    bitsInLetter = 0;
    while(letterToMod > 0){
      bitsInLetter++;
      letterToMod /= 2;
    }
    if(bitsInLetter == 0){
      if(bitsLeftInChar > 4){
        bitsLeftInChar -= 4;
      }
      else{
        j++;
        bitsLeftInChar = bitsLeftInChar + 8 - 4;
      }
    }
    else{
      letterToMod = lettersIn[i];
      if(bitsLeftInChar > bitsInLetter){
//printf("bits in char %d, bits in letter %d, letterToMod %x (1)\n",bitsLeftInChar, bitsInLetter, letterToMod);
        numShifts = 0;
        while(bitsInLetter + numShifts < bitsLeftInChar){
          numShifts++;
          letterToMod *= 2;
        }
        bitsLeftInChar -= bitsInLetter;
//printf("bytesOut[%d] += %x (char bigger)\n", j, letterToMod);
          bytesOut[j] += letterToMod;
        }
        else{
//printf("bits in char %d, bits in letter %d, letterToMod %x (letter > char)\n",bitsLeftInChar, bitsInLetter, letterToMod);
          while(bitsInLetter >= bitsLeftInChar){
            numShifts = 0;
            twoToTheShift = 1;
            while(bitsLeftInChar < bitsInLetter - numShifts){
              numShifts++;
              letterToMod /= 2;
              twoToTheShift *= 2;
            }
            bitsInLetter -= bitsLeftInChar;
//printf("bytesOut[%d] += %x (2)\n", j, letterToMod);
            bytesOut[j] += letterToMod;
            j++;
            bitsLeftInChar = 8;
            letterToMod = oldLetterToMod - twoToTheShift * letterToMod;
            oldLetterToMod = letterToMod;
          }
//printf("bits in char %d, bits in letter %d, letterToMod %x (3)\n",bitsLeftInChar, bitsInLetter, letterToMod);
          numShifts = 0;
          twoToTheShift = 1;
          while(bitsInLetter + numShifts < bitsLeftInChar){
            numShifts++;
            letterToMod *= 2;
            twoToTheShift *= 2;
          }
//printf("bytesOut[%d] += %x (3)\n", j, letterToMod);
          bytesOut[j] += letterToMod;
          letterToMod = oldLetterToMod - letterToMod * twoToTheShift;
          oldLetterToMod = letterToMod;
          bitsLeftInChar -= bitsInLetter; 
          if(bitsLeftInChar == 0){
            bitsLeftInChar = 8;
            j++;
          }        
      }
    }    
  }
//  for(i=0;i < j;i++)
  //  printf("%x\n",bytesOut[i]);
  return j;
}

void toMorse(char inputChars[], unsigned int outputCode[], int numChars){
  int i;

  for(i=0; i<numChars; i++){
    switch (inputChars[i]) {
      case 0x0a:
	    outputCode[i] = 0b101110101110000000;
        break;
	  case 0x20:
        outputCode[i] = 0;
        break;
      case 0x30:
        outputCode[i] = 0b1110111011101110111000;
        break;
      case 0x31:
        outputCode[i] = 0b10111011101110111000;
        break;
      case 0x32:
        outputCode[i] = 0b101011101110111000;
        break;
      case 0x33:
        outputCode[i] = 0b1010101110111000;
        break;
      case 0x34:
        outputCode[i] = 0b10101010111000;
        break;
      case 0x35:
        outputCode[i] = 0b101010101000;
        break;
      case 0x36:
        outputCode[i] = 0b11101010101000;
        break;
      case 0x37:
        outputCode[i] = 0b1110111010101000;
        break;
      case 0x38:
        outputCode[i] = 0b1110111011101110101000;
        break;
      case 0x39:
        outputCode[i] = 0b111011101110111101000;
        break;
      case 0x41:
        outputCode[i] = 0b10111000;
        break;
      case 0x42:
        outputCode[i] = 0b111010101000;
        break;
      case 0x43:
        outputCode[i] = 0b11101011101000;
        break;
      case 0x44:
        outputCode[i] = 0b1110101000;
        break;
      case 0x45:
        outputCode[i] = 0b1000;
        break;
      case 0x46:
        outputCode[i] = 0b101011101000;
        break;
     case 0x47:
        outputCode[i] = 0b111011101000;
        break;
      case 0x48:
        outputCode[i] = 0b1010101000;
        break;
      case 0x49:
        outputCode[i] = 0b101000;
        break;
      case 0x4a:
        outputCode[i] = 0b1011101110111000;
        break;
      case 0x4b:
        outputCode[i] = 0b111010111000;
        break;
      case 0x4c:
        outputCode[i] = 0b101110101000;
        break;
      case 0x4d:
        outputCode[i] = 0b1110111000;
        break;
      case 0x4e:
        outputCode[i] = 0b11101000;
        break;
      case 0x4f:
        outputCode[i] = 0b11101110111000;
        break;
      case 0x50:
        outputCode[i] = 0b10111011101000;
        break;
      case 0x51:
        outputCode[i] = 0b1110111010111000;
        break;
      case 0x52:
        outputCode[i] = 0b1011101000;
        break;
      case 0x53:
        outputCode[i] = 0b10101000;
        break;
      case 0x54:
        outputCode[i] = 0b111000;
        break;
      case 0x55:
        outputCode[i] = 0b1010111000;
        break;
      case 0x56:
        outputCode[i] = 0b101010111000;
        break;
      case 0x57:
        outputCode[i] = 0b101110111000;
        break;
      case 0x58:
        outputCode[i] = 0b11101010111000;
        break;
      case 0x59:
        outputCode[i] = 0b1110101110111000;
        break;
      case 0x5a:
        outputCode[i] = 0b11101110101000;
        break;
      default:
      outputCode[i] = 0;
      printf("error unknown symbol. will be become space \n");
    }
 }

}

void inputTextFile(char fileName[], char inputChars[]){
  int i = 0;
  FILE *inputFile;
  inputFile = fopen(fileName, "r");

  while(!feof(inputFile)){
    fscanf(inputFile, "%c", &inputChars[i]);
    i++;
  }
  
  fclose(inputFile);
}

int getNumInputChars(char fileName[]){
  int fileLength = 0;
  FILE  *filePointer;
  if((filePointer = fopen(fileName, "r"))){
    printf("file opened\n");
      fseek(filePointer, 0 ,SEEK_END);
      fileLength = ftell(filePointer);
    fclose(filePointer);
  }
  else{
    printf("Could not find file :(\n");
  }

  return fileLength;
}

void toUpperCase(char charArray[], int length){
  int i;

  for(i=0; i < length; i++){
    if(charArray[i] <= 122 && charArray[i] >=97)
      charArray[i] -= 0x20;
  }
 

}

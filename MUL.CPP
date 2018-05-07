/*
 program to multiply two very large numbers (length of the no.s is atleast 200)

 programmed by Abhishek Raj on 18-08-2017.
*/

#include"conio.h"
#include"stdio.h"
#include"stdlib.h"
#include"string.h"


// prototyping
void stringToNum(char *, int *,int);
int convert(char);
void multiply(int *, int *, int , int);
void addToResultArr(int *, int, int, int *, int);



// function to conver string into Number
void stringToNum(char *str, int *numArr, int len)
{
 int i;
 for(i=0;i<len;i++)
 {
  int num = convert(str[i]);
  numArr[i] = num;
 }
}

// function to get the integer equivalent of a character.
int convert(char ch)
{
 int charValue = ch;
 if(ch >= 48 && ch <= 57)
 {
   return(charValue - 48);
 }
 else
 {
  printf("Please enter a valid number!");
  getch();
//  return 0;
  exit(1);
 }

}


// main function
int startIndex; // for print the actual answer of resultArr without including initial 0's
void main()
{
 int len1, len2, i, firstNumLen, secNumLen;
 char *str1, *str2;
 int *firstNum, *secNum;

 clrscr();
 printf("\nEnter the length of the 1st number: ");
 scanf("%d",&len1);
 str1 = (char *)malloc((len1+1) * sizeof(char));

 printf("\nEnter 1st number: ");
 scanf("%s",str1);

 printf("\nEnter the length of the 2nd number: ");
 scanf("%d",&len2);

 str2 = (char *)malloc((len2 + 1) * sizeof(char));
 printf("\nEnter 2nd number: ");
 scanf("%s",str2);

 firstNumLen = strlen(str1);
 secNumLen = strlen(str2);
 //printf("\nfirstNumLen = %d",firstNumLen);
 //printf("\nSecNumLen = %d",secNumLen);

 // allocate memory dynamically
 firstNum = (int *)malloc(len1 * sizeof(int));
 secNum = (int *)malloc(len2 * sizeof(int));

 stringToNum(str1, firstNum, firstNumLen);
 stringToNum(str2, secNum, secNumLen);

 multiply(firstNum , secNum, firstNumLen, secNumLen);

 // free all memory
 free(str1);
 free(str2);
 free(firstNum);
 free(secNum);

 getch();

} // end of main function




// multiplication logic

void multiply(int *firstNum, int *secNum, int firstNumLen, int secNumLen)
{
 int i;
 int outArrSize , *outArr, res, j, ones=0, tens=0, tempSize, mulResArr;
 int *resultArr, resultSize;


 // give the size of the outarr
 if(firstNumLen > secNumLen)
 {
  outArrSize=firstNumLen + 50;
 }
 else
 {
  outArrSize=secNumLen + 50;
 }

 // allocating memory to outArr dynamically
 outArr=(int *)malloc(outArrSize*sizeof(int));
 tempSize=outArrSize-1;

 // give the size of the array resultArr
 resultSize = firstNumLen + secNumLen + 10;

 //allocating memory for the array resultArr
 resultArr = (int *)malloc(resultSize * sizeof(int));
 //set every elements to zero(0).
 for(j=0;j < resultSize;j++)
  resultArr[j] = 0;


 // this for loop is for multiplication
 for(i=secNumLen-1;i>=0;i--)
 {
  // set every elements to zero (0)
  for(j = 0;j < outArrSize;j++)
   outArr[j] = 0;

  tempSize = outArrSize -1;

  for(j=firstNumLen-1;j >= 0;j--)
  {
   res= secNum[i] * firstNum[j];
   res=res+tens;
   if(res > 9)
   {
    ones = res % 10;
    tens = res / 10;
   }
   else
   {
    ones = res;
    tens = 0;
   }
   outArr[tempSize--] = ones;
  } // end of for loop

  // if tens has any carry value
  if(tens > 0)
   outArr[tempSize--] = tens;

  ones = 0;tens = 0;

  // call this function to add after multiplication
  // (tempSize + 1) is the value of index from where the numbers start
  addToResultArr(outArr, (tempSize+1), outArrSize-1, resultArr, resultSize);

 }


 printf("\nResult Array:\n");
 for(j = startIndex;j < resultSize;j++)
 {
  printf("%d",resultArr[j]);
 }

 free(outArr);
 free(resultArr);

}

void addToResultArr(int *outArr, int start, int end, int * resultArr, int resultSize)
{
 static int k = resultSize-1;
 int sum = 0, ones = 0, tens = 0, i;
 startIndex = k;
 //logic of add
 for(i=end;i>=start;i--)
 {
  sum = outArr[i] + resultArr[startIndex--];
  sum += tens;
  if(sum > 9)
  {
   ones = sum % 10;
   tens = sum / 10;
  }
  else
  {
   ones = sum;
   tens = 0;
  }
  resultArr[startIndex+1] = ones;
 } // end of for

 if(tens > 0)
  resultArr[startIndex] += tens;
 k--;
}
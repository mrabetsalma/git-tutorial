#include <stdio.h> 
#include "espl_lib.h" 

int main ()  

{ 
  int c= 1;

do{
  unsigned int number;
  char Text;
  printf("Hello ESPL\n");
  printf("Enter a number \n");
  scanf("%d",&number);
  getchar();
  printf("%c", num_to_words(number) );
  printf("\n Do you wish to continue?(Y) for yes and (N) for No? \n");
  scanf("%c",&Text);
  if(Text == 'N'){

    c = 0;
}
}while(c== 1);
  
}
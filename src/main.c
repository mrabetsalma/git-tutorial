#include <stdio.h> 
#include <espl_lib.h> 
int continue=1;
int main () 
{ int number;
  char Text;
do{
  printf("Hello ESPL\n");
  printf("Enter a number \n");
  scanf("%d",&number);
  getchar();
  printf("%s",num_to_words(number));
  printf("\n Do you wish to continue?(Y) for yes and (N) for No? \n");
  scanf("%c",&Text);
  if(Text=='N')
    continue=0;
}while(continue==1);
  
}
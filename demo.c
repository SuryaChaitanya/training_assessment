#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct bird{

  unsigned short id ;
  unsigned char length;
  char *name;
};

struct observation{
  unsigned int observed:16;
  unsigned int id:16;
  unsigned int day:5;
  unsigned int month:4;
  unsigned int year:11;
  unsigned int freeBits:12;
};

int main(){
  FILE *fbird;
  FILE *fobs;
  struct bird input;
  struct observation obs;

  fobs=fopen("observations.bin", "rb");
      fbird = fopen("birds.bin", "rb");

  if(fbird == NULL){
    fprintf(stderr, "\nError opening file birds");
    exit(1);
  }
  if(fobs==NULL){
    fprintf(stderr, "\nError opening file observations");
    exit(1);
  }
  int i=1;

  unsigned short id[2144];

  while(fread(&input.id, sizeof(unsigned short), 1, fbird)){
    id[i]=input.id;
    fread(&input.length, sizeof(unsigned char), 1, fbird);
    int leng=(int)input.length;
    input.name = (unsigned char*)malloc(sizeof(unsigned char) * leng +1);
    int size=sizeof(unsigned char) * leng  ;
    printf("%d : id= %hu len= %u size=%d ", i, input.id, input.length, size);
    fread(input.name, size,1, fbird );
    printf("  name= %s\n",input.name);
    i++;
    free(input.name);
  }


  int j=1;
  while(fread(&obs, sizeof(struct observation), 1, fobs) ){
    printf("%d : Free = %d Year= %d Month = %d day = %d id = %d  NO: %d\n", j, obs.freeBits, obs.year, obs.month, obs.day, obs.id, obs.observed);
    j++;
  }


  fclose(fbird);
  fclose(fobs);
  return 0;

}

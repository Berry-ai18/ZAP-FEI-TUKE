#include <stdio.h>

int main(int argc, char *argv[]){

    //kontrola ARGc ak != 3 error
    if(argc != 3){
        return 1;
    }

    //deklaracia filov + premennch
    int c = 0;
    int isStop = 0;
    int posNowStart = 0;
    int posNowStop = 0;
    int doCopy = 0;
    int i = 0;
    int isFirstSpace = 0;
    int isStart = 0;
    char output[50000];
    char start[] = "START";
    char stop[] = "STOP";
    FILE *fp;
    FILE *out;
    
    //vynulovanie pola na zapisovanie
    for (int i = 0; i < 50000; i++){
      output[i] = '\0';
    }
    
    //otvaranie filov
    fp = fopen(argv[1],"r");
    out = fopen(argv[2],"w");
    
    //ak sa nepodarilo otvorit err
    if(fp == NULL){
      return 1;
    }

    //ak sa nepodarilo otvorit err
    if(out == NULL){
      return 1;
    }

    //hlavny cyklus dokym nedojde na koniec
    while((c = fgetc(fp)) != EOF){
      
      //hlada start
      if(c == start[0] || c == start[posNowStart]){
        if(posNowStart == 4){
          posNowStart = 0;
          isStart = 1;
        }
        
        if(c == start[0]){
          posNowStart = 0;
        }
        
        posNowStart++;
      }else{
        posNowStart = 0;
      }
      
      //hlada stop
      if(c == stop[0] || c == stop[posNowStop]){
        if(posNowStop == 3){
          posNowStop = 0;
          isStop = 1;
          isStart = 0;
          if(doCopy == 2){
            output[i] = '\0';
            output[i-1] = '\0';
            output[i-2] = '\0';
            output[i-3] = '\0';
            output[i-4] = '\0';
          }
        }
        
        if(c == stop[0]){
          posNowStop = 0;
        }
        
        posNowStop++;
      }else{
        posNowStop = 0;
        if(isStart == 1){
          isStop = 0;
        }
      }

      //tu zacina zistovat co kopiruje kazdu 2 medzeru hlada
      if(isStart == 1 && isStop == 0){
        if(c == ' '){
          doCopy++;
          if(doCopy == 3){
            doCopy = 1;
          }
        }
        if(doCopy == 2){
          if(isFirstSpace == 0){
            isFirstSpace = 1;
          }else{
            output[i] = c;
            i++;
          }
        }
      }
    }
    
    i = 0;
    
    //vypis
    while(output[i] != '\0'){
      fputc(output[i],out);
      i++;
    }
    
    fclose(fp);
    fclose(out);
    return 0;
}

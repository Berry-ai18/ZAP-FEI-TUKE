#include <stdio.h>

//main
int main(int argc, char *argv[]){

    //pocet argumentov ak je > 2 vyhodi error
    if(argc != 2){
        return 1;
    }
    
    //otvorenie filu + deklaracia premmench
    FILE *fp;
    fp = fopen(argv[1],"r");
    int counter = 0;
    int c = 0;
    char ananas[] = "ananas";
    char ANANAS[] = "ANANAS";
    int posNowStart = 0;
    
    //ak sa nepodarilo otvorit err
    if(fp == NULL){
      return 1;
    }

    //hlavny cyklus
    while((c = fgetc(fp)) != EOF){

      //hlada ananas/ANANAS alebo hociaku ich kombinaciu ak najde counter++
      if(c == ananas[0] || c == ananas[posNowStart] || c == ANANAS[0] || c == ANANAS[posNowStart]){
        if(posNowStart == 5){
          posNowStart = 0;
          counter++;
        }

        //ak najde AA/aa
        if((c == 'a' || c == 'A') && posNowStart < 2){
          posNowStart = 0;
        }

        posNowStart++;
      }else{
        posNowStart = 0;
      }
    }

    //uzavretie suboru
    fclose(fp);

    //pomoc
    char help[3];
    //otvorenie filu na write
    fp = fopen(argv[1],"w");
    
    //vynulovanie helpu
    for (int i = 0; i < 3; i++){
      help[i] = '\0';
    }


    if(counter > 99){
      help[2] = counter % 10 + '0';
      counter /= 10;
    }
    
    if(counter > 9){
      help[1] = counter % 10 + '0';
      counter /= 10;
    }

    help[0] = counter % 10 + '0';

    //vypis do output suboru
    for (int i = 0; i < 3; i++)
    {
      if(help[i] != '\0'){
        fputc(help[i],fp);
      }
    }

    fclose(fp);
    
    return 0;
}

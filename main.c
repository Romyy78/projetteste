
#include "header.h"


int main() {
 const char* filePath = "logo.txt";
    includeFile(filePath);

 save_user();
   
    print_menu();
  char board[MAX_SIZE][MAX_SIZE];
   
    int verif;
  int size_col;
int size_row;
  int num_symbols;
struct Time initial_time, final_time, difference;



  do{
     printf("Entrez l'heure initiale (format 24 heures) : ");
    scanf("%d", &initial_time.hour);

    // Saisie des minutes initiales
    printf("Entrez les minutes initiales : ");
    scanf("%d", &initial_time.minute);
    
    printf(" Choisie le nombre de lignes entre 3 et 26  : \n");
       verif=  scanf("%d",&size_row);
    vide_buffer();
    if ((size_row<3) || (size_row>MAX_SIZE) ) {
        printf("Le nombre de lignes n'est pas valable \n");
    }
  }while( (size_row <3) || (verif!=1) || (size_row>MAX_SIZE) );
      
  do{
    printf("Choisie le nombre de colonnes entre 3 et 26 :\n");
   verif= scanf("%d", &size_col);
        vide_buffer();
    if ((size_col <3) || (size_col>MAX_SIZE)  ) {
        printf("Le nombre de colonnes n'est pas valable \n");
    }
  }while( (size_col <3) || (verif!=1) || (size_col>MAX_SIZE) );
  
    do{
      printf("Choisie le nombre de symboles (entre 4 et 6) : \n");
     verif= scanf("%d", &num_symbols);
        vide_buffer();
      if ((num_symbols < MIN_SYMBOLS) || (num_symbols>MAX_SYMBOLS) ) {
          printf("Le nombre de symboles n'est pas valable\n");
          
      }
    }while(((num_symbols < MIN_SYMBOLS) || (num_symbols>MAX_SYMBOLS)) || (verif!=1)  );

    
    

    int score = play_game(size_row,size_col,num_symbols);
    printf("Votre score final: %d\n", score);
// Saisie de l'heure finale
    printf("Entrez l'heure finale (format 24 heures) : ");
    scanf("%d", &final_time.hour);

    // Saisie des minutes finales
    printf("Entrez les minutes finales : ");
    scanf("%d", &final_time.minute);

    difference = calculate_time_difference(initial_time, final_time);

    // Affichage de la différence
    printf("Différence : %02d:%02d\n", difference.hour, difference.minute);

   

    return 0;
}

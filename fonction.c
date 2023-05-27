#include "header.h"





// Fonction pour calculer la différence entre deux horaires
struct Time calculate_time_difference(struct Time initial_time, struct Time final_time) {
    struct Time difference;

    // Conversion des heures en minutes
    int initial_minutes = initial_time.hour * 60 + initial_time.minute;
    int final_minutes = final_time.hour * 60 + final_time.minute;

    // Calcul de la différence en minutes
    int time_difference = final_minutes - initial_minutes;

    // Conversion de la différence en heures et minutes
    difference.hour = time_difference / 60;
    difference.minute = time_difference % 60;

    return difference;
}





void vide_buffer(){
while(getchar()!='\n'){}
}


void includeFile(const char* filePath) {
    FILE* fichier = fopen(filePath, "r"); // Ouvrir le fichier en mode lecture

    if (fichier != NULL) {
        int caractere;

        // Lire et afficher chaque caractère du fichier
        while ((caractere = fgetc(fichier)) != EOF) {
            putchar(caractere);
        }

        fclose(fichier); // Fermer le fichier
    } else {
        printf("Erreur lors de l'ouverture du fichier.\n");
    }
}

void save_user() {
    char nomUtilisateur[100];
    
    printf("\n\n\n\nEntrez votre nom d'utilisateur : \n");
    fgets(nomUtilisateur, sizeof(nomUtilisateur), stdin);
    
    // Supprimer le saut de ligne final généré par fgets
    size_t longueurNom = strlen(nomUtilisateur);
    if (longueurNom > 0 && nomUtilisateur[longueurNom - 1] == '\n') {
        nomUtilisateur[longueurNom - 1] = '\0';
    }
    
    // Sauvegarder le nom dans un fichier (par exemple)
    FILE *fichier = fopen("nom_utilisateur.txt", "w");
    if (fichier == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier pour la sauvegarde.\n");
        return;
    }
    
    fprintf(fichier, "%s", nomUtilisateur);
    fclose(fichier);
    
    printf("Le nom d'utilisateur a été sauvegardé avec succès.\n");
}





void print_menu() {
    int choice;
    int verif;
    
    do {
        printf("╔═══════════════════════ Menu ═══════════════════════╗\n");
        printf("║                                                    ║\n");
        printf("║                1. Jouer et rejoindre               ║\n");
        printf("║                   notre aventure                   ║\n");
        printf("║                                                    ║\n");
        printf("║                2. Sauvegarde de votre              ║\n");
        printf("║                       partie                       ║\n");
        printf("║                                                    ║\n");
        printf("║                       3. Sortie                    ║\n");
        printf("║                                                    ║\n");
        printf("╚════════════════════════════════════════════════════╝\n");
        printf("\nVeuillez entrer votre choix : ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Saisie invalide.\n");
            vide_buffer();
            continue;
        }
        
        switch (choice) {
            case 1:
                printf("Vous avez choisi de lancer le jeu.\n\n");
                // pour accéder au jeu
                break;
            
            case 2:
                printf("Vous avez choisi de voir la sauvegarde.\n\n");
                // pour accéder à la sauvegarde
                break;
            
            case 3:
                printf("Vous avez choisi de quitter le jeu.\n\n");
                exit(7);
                break;
            
            default:
                printf("Choix invalide. Veuillez refaire votre choix.\n\n");
                break;
        }
        
    } while (choice != 1 && choice != 2 && choice != 3);
}

char board[MAX_SIZE][MAX_SIZE];
// cette matrice est le plateau du jeu :

// la taille du tableau
// le nombre de symbole dans le tableau

int aléatoire(int min, int max) {
    return min + rand() % (max - min + 1);
}
// fonction pour genere aleatoirement et l'utiliser a chaque fois


void init_board(int size_row,int size_col,int num_symbols) {
    int i, j;
    char tiles[MAX_SYMBOLS] = {'A','B','C','D','E','F'};
  //  un tableau qui contient les caraactere et qui prend en variable max symbole 6
  
    srand(time(NULL));
  // pour generer une variable aleatoire 

    for (i = 0; i < size_row; i++) {
      // parcourir les lignes
      
      for (j = 0; j < size_col; j++) {
          // parcourir les colones
        
            char symbole;
          // variable symbole pour stocker les symboles
            do {
                symbole = tiles[aléatoire(0, num_symbols- 1)];
              // elle genere un symbole aleatoire et le stock dans symbole
            } while ((i > 1 && board[i-1][j] == symbole) ||
                     (j > 1 && board[i][j-1] == symbole)||
              (j > 1 && board[i-1][j-1] == symbole));// change le  symbole si les deux symboles avant au dessus et à gauche de lui sont les mêmes 
            board[i][j] = symbole;
        }
    }
}

const char* get_fruit_emoji(char fruit) {
    switch (fruit) {
        case 'A':
            return "\U0001F34E"; // pomme
        case 'B':
            return "\U0001F347"; // raisin
        case 'C':
            return "\U0001F34C"; // banane
        case 'D':
            return "\U0001F34A"; // orange
        case 'E':
            return "\U0001F346"; // aubergine
        case 'F':
            return "\U0001F353"; // fraise
        default:
            return " ";
    }
}

void print_board(int size_col,int size_row) {
    printf("    ");
    for (int col = 0; col < size_col; col++) {
        printf(" %c ", 'A' + col);
    }
    printf("\n");
    for (int row = 0; row < size_row; row++) {
        printf("%2d│", row + 1);
        for (int col = 0; col < size_col; col++) {
            
            printf(" %2s", get_fruit_emoji(board[row][col]));
        }
        printf("\n");
    }
}

// cette fonction est utiliser pour afficher le tableau de jeu board et les couleurs dans le tableau 

      
int is_valid_move(char board[MAX_SIZE][MAX_SIZE], int size_row, int size_col, int x1, int y1, int x2, int y2) {
    if (x1 < 0 || x1 >= size_row || y1 < 0 || y1 >= size_col ||
        x2 < 0 || x2 >= size_row || y2 < 0 || y2 >= size_col ||
        (abs(x1 - x2) + abs(y1 - y2) != 1)) {
        return 0;
    }

    char temp = board[x1][y1];
    board[x1][y1] = board[x2][y2];
    board[x2][y2] = temp;

    if ((board[x1][y1] == board[x1][y1+1]) && (board[x1][y1] == board[x1][y1+2])) {
    return 1;
}
else if ((board[x1][y1] == board[x1][y1-1]) && (board[x1][y1] == board[x1][y1-2])) {
    return 1;
}
else if ((board[x1][y1] == board[x1][y1-1]) && (board[x1][y1] == board[x1][y1+1])) {
    return 1;
}
else if ((board[x1][y1] == board[x1+1][y1]) && (board[x1][y1] == board[x1+2][y1])) {
    return 1;
}
else if ((board[x1][y1] == board[x1-1][y1]) && (board[x1][y1] == board[x1-2][y1])) {
    return 1;
}
else if ((board[x1][y1] == board[x1-1][y1]) && (board[x1][y1] == board[x1+1][y1])) {
    return 1;
}
else if ((board[x1][y1] == board[x1+1][y1+1]) && (board[x1][y1] == board[x1+2][y1+2])) {
    return 1;
}
else if ((board[x1][y1] == board[x1-1][y1-1]) && (board[x1][y1] == board[x1-2][y1-2])) {
    return 1;
}
else if ((board[x1][y1] == board[x1-1][y1-1]) && (board[x1][y1] == board[x1+1][y1+1])) {
    return 1;
}
else if ((board[x1][y1] == board[x1-1][y1+1]) && (board[x1][y1] == board[x1-2][y1+2])) {
    return 1;
}
else if ((board[x1][y1] == board[x1+1][y1-1]) && (board[x1][y1] == board[x1+2][y1-2])) {
    return 1;
}
else if ((board[x1][y1] == board[x1+1][y1-1]) && (board[x1][y1] == board[x1+1][y1-1])) {
    return 1;
}
else if ((board[x2][y2] == board[x2][y2+1]) && (board[x2][y2] == board[x2][y2+2])) {
    return 1;
}
else if ((board[x2][y2] == board[x2][y2-1]) && (board[x2][y2] == board[x2][y2-2])) {
    return 1;
}
else if ((board[x2][y2] == board[x2][y2-1]) && (board[x2][y2] == board[x2][y2+1])) {
    return 1;
}
else if ((board[x2][y2] == board[x2+1][y2]) && (board[x2][y2] == board[x2+2][y2])) {
    return 1;
}
else if ((board[x2][y2] == board[x2-1][y2]) && (board[x2][y2] == board[x2-2][y2])) {
    return 1;
}
else if ((board[x2][y2] == board[x2-1][y2]) && (board[x2][y2] == board[x2+1][y2])) {
    return 1;
}
else if ((board[x2][y2] == board[x2+1][y2+1]) && (board[x2][y2] == board[x2+2][y2+2])) {
    return 1;
}
else if ((board[x2][y2] == board[x2-1][y2-1]) && (board[x2][y2] == board[x2-2][y2-2])) {
    return 1;
}
else if ((board[x2][y2] == board[x2-1][y2-1]) && (board[x2][y2] == board[x2+1][y2+1])) {
    return 1;
}
else if ((board[x2][y2] == board[x2-1][y2+1]) && (board[x2][y2] == board[x2-2][y2+2])) {
    return 1;
}
else if ((board[x2][y2] == board[x2+1][y2-1]) && (board[x2][y2] == board[x2+2][y2-2])) {
    return 1;
}
else if ((board[x2][y2] == board[x2+1][y2-1]) && (board[x2][y2] == board[x2+1][y2-1])) {
    return 1;
}
    
        temp = board[x1][y1];
        board[x1][y1] = board[x2][y2];
        board[x2][y2] = temp;
        return 0;
    
}

int remove_matches(char board[MAX_SIZE][MAX_SIZE], int size_row, int size_col) {
    int i, j, k;
    int removed = 0;

    // Suppression des lignes horizontales
    for (i = 0; i < size_row; i++) {
        j = 0;
        while (j < size_col - 2) {
            if (board[i][j] != ' ' && board[i][j] == board[i][j+1] && board[i][j] == board[i][j+2]) {
                char symbol = board[i][j];
                k = j;
                while (k < size_col && board[i][k] == symbol) {
                    board[i][k] = ' ';
                    k++;
                    removed++;
                }
                j = k; // On passe à la colonne suivante pour éviter les doublons
            } else {
                j++;
            }
        }
    }

    // Suppression des lignes verticales
    for (j = 0; j < size_col; j++) {
        i = 0;
        while (i < size_row - 2) {
            if (board[i][j] != ' ' && board[i][j] == board[i+1][j] && board[i][j] == board[i+2][j]) {
                char symbol = board[i][j];
                k = i;
                while (k < size_row && board[k][j] == symbol) {
                    board[k][j] = ' ';
                    k++;
                    removed++;
                }
                i = k; // On passe à la ligne suivante pour éviter les doublons
            } else {
                i++;
            }
        }
    }

    // Suppression des diagonales ascendantes
    for (i = 0; i < size_row - 2; i++) {
        for (j = 0; j < size_col - 2; j++) {
            if (board[i][j] != ' ' && board[i][j] == board[i+1][j+1] && board[i][j] == board[i+2][j+2]) {
                char symbol = board[i][j];
                k = 0;
                while (i+k < size_row && j+k < size_col && board[i+k][j+k] == symbol) {
                    board[i+k][j+k] = ' ';
                    k++;
                    removed++;
                }
            }
        }
    }

    // Suppression des diagonales descendantes
    for (i = size_row - 1; i >= 2; i--) {
        for (j = 0; j < size_col - 2; j++) {
            if (board[i][j] != ' ' && board[i][j] == board[i-1][j+1] && board[i][j] == board[i-2][j+2]) {
                char symbol = board[i][j];
                k = 0;
                while (i-k >= 0 && j+k < size_col && board[i-k][j+k] == symbol) {
                    board[i-k][j+k] = ' ';
                    k++;
                    removed++;
                }
            }
        }
    }

    return removed;
}

void apply_gravity(int size_col, int size_row, char board[MAX_SIZE][MAX_SIZE]) {
    int i, j, k;
    for (j = 0; j < size_col; j++) {
        k = size_row - 1;
        for (i = size_row - 1; i >= 0; i--) {
            if (board[i][j] != ' ') {
                board[k][j] = board[i][j];
                k--;
            }
        }
        for (; k >= 0; k--) {
            board[k][j] = ' ';
        }
    }
}

int play_game(int size_row, int size_col, int num_symbols) {
    int score = 0;
    init_board(size_row, size_col, num_symbols);
    for(int i=0;i<100;i++){
    printf("Votre score: %d\n", score);
    print_board(size_col, size_row);

    int x1, y1, x2, y2;

    printf("Quelle case voulez-vous déplacer ? (ex. A1 B2): ");
    char col1, col2;
    int row1, row2;
    scanf(" %c%d %c%d", &col1, &row1, &col2, &row2);
    col1 = toupper(col1);
    col2 = toupper(col2);
    x1 = row1 - 1;
    y1 = col1 - 'A';
    x2 = row2 - 1;
    y2 = col2 - 'A';
    printf("%d", is_valid_move(board, size_row, size_col, x1, y1, x2, y2));

    char temp = board[x1][y1];
    board[x1][y1] = board[x2][y2];
    board[x2][y2] = temp;
    temp = board[x1][y1];
    board[x1][y1] = board[x2][y2];
    board[x2][y2] = temp;

    int removed = remove_matches(board, size_row, size_col);
    while (removed) {
        score += removed;
        apply_gravity(size_col, size_row, board);
        remove_matches(board, size_row, size_col);
        apply_gravity(size_col, size_row, board);
        print_board(size_col, size_row);
        printf("Votre score est : %d\n", score);
        printf("Nombre de correspondances supprimées : %d\n", removed);
        removed = remove_matches(board, size_row, size_col);
        print_board(size_col, size_row);
        
    }
    }
    return score;
}
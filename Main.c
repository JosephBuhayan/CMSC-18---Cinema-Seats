#include <stdio.h>
#include <string.h>
#define MAX_MOVIES 5
#define MAX_TITLE_LENGTH 100
#define ROWLOWERBOX 20
#define COLUMNLOWERBOX 12
#define ROWSUPPERBOX 7
#define COLUMNSUPPERBOX 15

char movies[MAX_MOVIES][MAX_TITLE_LENGTH];
int seatsLowerBox[ROWLOWERBOX][COLUMNLOWERBOX] = {
        {1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12},
        {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24},
        {25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36},
        {37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48},
        {49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60},
        {61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72},
        {73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84},
        {85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96},
        {97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108},
        {109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120},
        {121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132},
        {133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144},
        {145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156},
        {157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168},
        {169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180},
        {181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192},
        {193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204},
        {205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216},
        {217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228},
        {229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240}};
int seatsUpperBox[ROWSUPPERBOX][COLUMNSUPPERBOX] = {
        {1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30},
        {31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45},
        {46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60},
        {61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75},
        {76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90},
        {91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105}
};
int movie_count = MAX_MOVIES;
int movie_to_watch;


void get_movie_titles(char movies[][MAX_TITLE_LENGTH], int count) {
    for (int i = 0; i < count; i++) {
        printf("Enter title for movie %d: ", i + 1);
        fgets(movies[i], MAX_TITLE_LENGTH, stdin);
        
        // Remove newline character from the input if present
        size_t length = strlen(movies[i]);
        if (length > 0 && movies[i][length - 1] == '\n') {
            movies[i][length - 1] = '\0';
        }
    }
}

void print_with_dash(const char *str) {
    int maxLength = 40;
    int strLength = strlen(str);
    
    // Ensure the string length does not exceed max length for fitting
    if (strLength >= maxLength) {
        printf("String too long to fit within 30 characters.\n");
        return;
    }
    
    int totalDash = maxLength - strLength;
    int leftDash = totalDash / 2;
    int rightDash = totalDash - leftDash;

    // Print left Dash
    for (int i = 0; i < leftDash; i++) {
        printf("-");
    }
    
    // Print the input string
    printf("%s", str);
    
    // Print right asterisks
    for (int i = 0; i < rightDash; i++) {
        printf("-");
    }
    
    printf("\n");
}

void print_movie(char movies[]){
    printf("----------------------------------------\n");
    printf("Movie Title: %s\n", movies);
    printf("Genre: Whatever the genre of this movie\n");
    printf("Rating: G\n");
    print_with_dash("Cinema Seats");
}

int print_movie_seats_upperBox(){
    for (int i = 0; i < ROWLOWERBOX; i++) {
        for (int j = 0; j < COLUMNLOWERBOX; j++) {
            printf("[L%d]", seatsLowerBox[i][j]);
        }
        printf("\n");
    }
}

int print_movie_seats_lowerBox(){
    for (int i = 0; i < ROWSUPPERBOX; i++) {
        for (int j = 0; j < COLUMNSUPPERBOX; j++) {
            printf("[U%d]", seatsUpperBox[i][j]);
        }
        printf("\n");
    }
}


int main(){

    get_movie_titles(movies, movie_count);// if admin rani

    print_with_dash("Good Day Costumer");
    print_with_dash("Welcome to Group 2 Cinema");
    printf("The Movies Showing Today Are:\n");
    for (int i = 0; i < movie_count; i++) {// print movie list
        printf("[%d] %s\n", i + 1, movies[i]);
    }
    printf("What are you watching today?\n");
    scanf(" %d", &movie_to_watch);
    switch (movie_to_watch){
    case 1:
        print_movie(movies[0]);
        print_movie_seats_lowerBox();
        print_movie_seats_upperBox();
        break;
    case 2:
        print_movie(movies[1]);
        print_movie_seats_lowerBox();
        print_movie_seats_upperBox();
        break;
    case 3:
        print_movie(movies[2]);
        print_movie_seats_lowerBox();
        print_movie_seats_upperBox();
        break;
    case 4:
        print_movie(movies[3]);
        print_movie_seats_lowerBox();
        print_movie_seats_upperBox();
        break;
    case 5:
        print_movie(movies[4]);
        print_movie_seats_lowerBox();
        print_movie_seats_upperBox();
        break;        
    }


}
#include <stdio.h>
#include <string.h>
#define MAX_MOVIES 5
#define MAX_TITLE_LENGTH 100
#define ROWLOWERBOX 15
#define COLUMNLOWERBOX 10
#define ROWSUPPERBOX 8
#define COLUMNSUPPERBOX 14

char movies[MAX_MOVIES][MAX_TITLE_LENGTH];
int seatsLowerBox[ROWLOWERBOX][COLUMNLOWERBOX] = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
        {21, 22, 23, 24, 25, 26, 27, 28, 29, 30},
        {31, 32, 33, 34, 35, 36, 37, 38, 39, 40},
        {41, 42, 43, 44, 45, 46, 47, 48, 49, 50},
        {51, 52, 53, 54, 55, 56, 57, 58, 59, 60},
        {61, 62, 63, 64, 65, 66, 67, 68, 69, 70},
        {71, 72, 73, 74, 75, 76, 77, 78, 79, 80},
        {81, 82, 83, 84, 85, 86, 87, 88, 89, 90},
        {91, 92, 93, 94, 95, 96, 97, 98, 99, 100},
        {101, 102, 103, 104, 105, 106, 107, 108, 109, 110},
        {111, 112, 113, 114, 115, 116, 117, 118, 119, 120},
        {121, 122, 123, 124, 125, 126, 127, 128, 129, 130},
        {131, 132, 133, 134, 135, 136, 137, 138, 139, 140},
        {141, 142, 143, 144, 145, 146, 147, 148, 149, 150}};
int seatsUpperBox[ROWSUPPERBOX][COLUMNSUPPERBOX] = {
        {1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14},
        {15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28},
        {29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42},
        {43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56},
        {57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70},
        {71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84},
        {85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98},
        {99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112}
};
int movie_count = MAX_MOVIES;
int movie_to_watch;
int UserNumberOfSeats, UserChosenUpperBoxSeats[150], UserChosenlowerBoxSeats[150];
char UserChosenBox[20];

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
}

int print_movie_seats_lowerBox(){
    printf("                             ");
    print_with_dash("Cinema Seats Lower Box");
    for (int i = 0; i < ROWLOWERBOX; i++) {
        printf("              "); // Add padding here for left alignment
        for (int j = 0; j < COLUMNLOWERBOX; j++) {
            printf("[L%-3d] ", seatsLowerBox[i][j]); // %-3d pads to 3 characters
        }
        printf("\n");
    }
    printf("\n");
}

int print_movie_seats_upperBox() {
    printf("                             ");
    print_with_dash("Cinema Seats Upper Box");
    for (int i = 0; i < ROWSUPPERBOX; i++) {
        for (int j = 0; j < COLUMNSUPPERBOX; j++) {
            printf("[U%-3d] ", seatsUpperBox[i][j]); // %-3d pads to 3 characters
        }
        printf("\n");
    }
    printf("\n");
}

void user_choose_seats_lower(){
    printf("How many seats are you buying?\n"); //lowerbox
    scanf(" %d", &UserNumberOfSeats);
    for (int i = 0; i < UserNumberOfSeats; i++){
        printf("Seat #%d: \n", i+1);
        scanf(" %d", &UserChosenlowerBoxSeats[i]);
    }
    printf("You chose seat/s: ");
    for(int i = 0; i < UserNumberOfSeats; i++){
        printf("%d ", UserChosenlowerBoxSeats[i]);
    }
}

void user_choose_seats_upper(){
    printf("How many seats are you buying?\n"); //lowerbox
    scanf(" %d", &UserNumberOfSeats);
    for (int i = 0; i < UserNumberOfSeats; i++){
        printf("Seat #%d: \n", i+1);
        scanf(" %d", &UserChosenUpperBoxSeats[i]);
    }
    printf("You chose seat/s: ");
    for(int i = 0; i < UserNumberOfSeats; i++){
        printf("%d ", UserChosenlowerBoxSeats[i]);
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
        choose:
        printf("Where do you wanna go? Lower Box or Upper Box?\n");
        scanf(" %19s", &UserChosenBox);
        if (strcmp(UserChosenBox, "Lower") == 0) {
            user_choose_seats_lower();
        }
        else if(strcmp(UserChosenBox, "Lower Box")){
            user_choose_seats_lower();
        }
        else if(strcmp(UserChosenBox, "Upper")){
            user_choose_seats_upper();
        }   
        else if(strcmp(UserChosenBox, "Upper Box")){
            user_choose_seats_upper();
        }
        else{
            printf("Choose Again");
            goto choose;
        }        
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
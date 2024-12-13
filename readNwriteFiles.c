#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define MAX_MOVIES 5
#define MAX_TITLE_LENGTH 100
#define ROWLOWERBOX 15
#define COLUMNLOWERBOX 10
#define ROWSUPPERBOX 8
#define COLUMNSUPPERBOX 14
#define MAX_SEATS 200

typedef struct{
    char titles[MAX_TITLE_LENGTH];
    char genres[MAX_TITLE_LENGTH];
    char description[1000];
    int seatsLowerBox[ROWLOWERBOX][COLUMNLOWERBOX];
    int seatsUpperBox[ROWSUPPERBOX][COLUMNSUPPERBOX];
    int occupiedSeatsLowerBox[MAX_SEATS];
    int occupiedSeatsUpperBox[MAX_SEATS];
    int price;
    int startHour;
    int startMinute;
    int ticketSold;
    int profit;

}Movie;

Movie movies[MAX_MOVIES];

void admin_mode();
void fund_management( int count);
void movie_management(Movie movies[], int count) ;
void print_GUI ();
void print_menu ();
void print_with_dash(const char *str);
void print_movie(char movies[], char genres[], int price, int hour, int minute, char description[]);
int find_the_first_index_with_zero_lowerbox(int OccupiedSeatsLowerBox[]);
int find_the_first_index_with_zero_upperbox(int OccupiedSeatsUpperBox[]);
int print_movie_seats_lowerBox(int movieIndex);
int print_movie_seats_upperBox(int movieIndex);
void timer(int scheduledTime);
void startScheduledMovies(int i) ;
void user_choose_seats_lower(int movieIndex);
void user_choose_seats_upper(int movieIndex);
void readFiles(FILE *file, char stored[MAX_TITLE_LENGTH], int index);
void readFilesDescription(FILE *file, char stored[1000], int index);
void readFilesPrice(FILE *file, int *stored, int index);
void readFiles2Int(FILE *file, int *stored,int *anotherStored, int index);
void writeFundsToFile();


int seatsLowerBox[ROWLOWERBOX][COLUMNLOWERBOX] = {// the seats for lowerbox
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
int seatsUpperBox[ROWSUPPERBOX][COLUMNSUPPERBOX] = {// the seats for upperbox
        {1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14},
        {15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28},
        {29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42},
        {43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56},
        {57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70},
        {71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84},
        {85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98},
        {99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112}
};
int movie_count = MAX_MOVIES; // movie count
int UserNumberOfSeats, UserChosenUpperBoxSeats[MAX_SEATS], UserChosenlowerBoxSeats[MAX_SEATS]; // user number of seats is how many seats the user wanna buy/chose. The others is the array of all occupied seats
char UserChosenBox[20]; // Upperbox or Lower box


int main()
{
    FILE *movie = fopen("movieTitles.txt", "r");
    FILE *genre = fopen("genres.txt", "r");
    FILE *synopsis = fopen("synopsis.txt", "r");
    FILE *price = fopen("price.txt", "r");
    FILE *schedule = fopen("schedule.txt", "r");
    
    int movie_to_watch;// the user inputted choice of movie is saved here

	int option, i, password = 123, password_try, leave, loop;

    if (movie == NULL || genre == NULL || synopsis == NULL || price == NULL || schedule == NULL) {
        printf("Error opening one or more files.\n");
        return 1;
    }
    
    for (i = 0; i < MAX_MOVIES; i++) {
        readFiles(movie, movies[i].titles, i);
        readFiles(genre, movies[i].genres, i);
        readFilesDescription(synopsis, movies[i].description, i);
        readFilesPrice(price, &movies[i].price, i);
        readFiles2Int(schedule, &movies[i].startHour, &movies[i].startMinute, i);
    }


    do{
        print_GUI();
        print_menu();
        printf("> ");
        scanf(" %d", &option);
        
        while (getchar() != '\n');

        switch(option){

            					//MENU LOGIC
            case 1:
                printf("Admin Password: "); //Password is 123
                scanf(" %d", &password_try);

                while (getchar() != '\n');
                
               		//sleep(1);
                if(password == password_try){
                    admin_mode();
                } else{
                    puts("Wrong Password");
                    //sleep(2);
                    system("cls");
                }
                break;
            case 2:
                do{
                    system("cls");	
                    print_GUI();
                    printf("The Movies Showing Today Are:\n");
                    for (i = 0; i < movie_count; i++) {// print movie list
                        printf("[%d] %s\n", i + 1, movies[i].titles);
                    }
                    printf("\n[%d] Go back", i + 1);

                    printf("\nWhat are you watching today?\nOption: ");
                    scanf(" %d", &movie_to_watch);
                    while (getchar() != '\n');

                    if(!(movie_to_watch<=MAX_MOVIES+1 && movie_to_watch>0)){
                        printf("\nInvalid input! Try again");
                        sleep(1);
                    }else{
                        break;
                    }
                }while(1);

                if(movie_to_watch == MAX_MOVIES + 1){//when user choose option go back
                    system("cls");
                    continue;
                }

                
                print_movie(movies[movie_to_watch-1].titles, movies[movie_to_watch-1].genres, movies[movie_to_watch-1].price, movies[movie_to_watch-1].startHour, movies[movie_to_watch-1].startMinute, movies[movie_to_watch-1].description);
                print_movie_seats_lowerBox(movie_to_watch-1);
                print_movie_seats_upperBox(movie_to_watch-1);

                do{
                    printf("\nWhere do you wanna go?\n[Lower Box] or [Upper Box]?\nOption: ");
                    fgets(UserChosenBox, sizeof(UserChosenBox), stdin);
                    UserChosenBox[strcspn(UserChosenBox, "\n")] = 0;

                    for(i = 0; i<strlen(UserChosenBox); i++){
                        UserChosenBox[i] = tolower(UserChosenBox[i]);
                    }

                    if (strcmp(UserChosenBox, "lower") == 0 || strcmp(UserChosenBox, "lower box" ) == 0) {
                        user_choose_seats_lower(movie_to_watch-1);
                        writeFundsToFile();
                        break;
                    }
                    else if(strcmp(UserChosenBox, "upper") == 0 || strcmp(UserChosenBox, "upper box") == 0){
                        user_choose_seats_upper(movie_to_watch-1);
                        writeFundsToFile();
                        break;
                    }
                    else{
                        printf("\nChoose Again");
                    }
                }while(1);
                break;
                
            case 3:
                system("cls");
                print_GUI();
                printf("The Movies Showing Today Are:\n");
                for (i = 0; i < movie_count; i++) {// print movie list
                    printf("[%d] ---------------------------------- %-40s ----------------------------------\n\tGenre: %s\n\tPrice: P %d\n\tMovie shows on [%02d:%02d]\n\n\tSynopsis: %s\n\n", i + 1, movies[i].titles, movies[i].genres,movies[i].price, movies[i].startHour, movies[i].startMinute, movies[i].description);
                }

                while (1) {
                    printf("===================================================================================");
                    printf("\n\n[1] Leave \nOptions: ");
                    scanf("%d", &leave);

                    if (leave == 1) {
                        printf("You entered 1. Exiting the loop.\n");
                        break; // Exit the loop when input is 1
                    } else {
                        printf("You entered %d. Try again.\n", leave);
                    }
                }
                system("cls");
                break;
                
            case 4:
                printf("Exiting program.");
                sleep(1);
				printf(".");
				sleep(1);
                printf(".");
                sleep(2);
                return 0;
                break;
                
            default:
                puts("Invalid Input!");
                sleep(2);
                system("cls");
                break;
            }
    }while(1);
    
    fclose(movie);	fclose(genre);	fclose(synopsis);	fclose(price);	fclose(schedule);

    return 0;
}


//----------------------------------------- ADMIN OPTONS ----------------------------------------------
void admin_mode()
{
    int choice;
    do{
            system("cls");
            printf("MENU OPTIONS AS AN ADMIN:\n");
            printf("\t[1]Manage Movies\n\t[2]Manage Funds\n\t[3]Exit admin mode\nOption: ");
            scanf(" %d", &choice);
            system("cls");

            while (getchar() != '\n');

        switch(choice)
		{
            case 1:
                movie_management(movies, movie_count);// if admin 
                break;
            case 2:
                fund_management(movie_count);
                break;
            case 3:
                printf("Exiting admin mode...");
                return;
                break;
        }
    }while(1);
}

void fund_management( int count) 
{
    int i;
    int choice;
    int price_input;
    int totalProfit = 0;
    FILE *funds;

    funds = fopen("funds.txt", "r");
    if (funds == NULL) {
        printf("Error opening funds.txt .\n");
        return;
    }
    
    for (i = 0; i < MAX_MOVIES; i++) readFiles2Int(funds, &movies[i].ticketSold, &movies[i].profit, i);
    fclose(funds);

    do{
        do{
            printf("FUND MANAGEMENT:\n");
            printf("\t[1]Check funds\n\t[2]Reset funds\n\t[3]Exit fund management\nOption: ");
            scanf(" %d", &choice);

            while (getchar() != '\n');

            if(!(choice>0 && choice <4)){
                printf("Invalid input! Please try again...\n");
            }

        }while(!(choice>0 && choice <4));

            
        switch(choice){
            case 1:
                system("cls");
                for(i = 0; i<MAX_MOVIES; i++){
                    printf("\nMovie [%d] %-25s Tickets' sold: %-6d|\tProfit: P %-d", i + 1, movies[i].titles, movies[i].ticketSold, movies[i].profit);
                    totalProfit += movies[i].profit;
                }
                printf("\nTotal Profit: P %d", totalProfit);
                printf("\nPress Enter to continue...");
                getchar();
                break;
            case 2:
                printf("\nReseting the funds...");
                Sleep(2000);
                funds = fopen("funds.txt", "w");
                for (i = 0; i < MAX_MOVIES; i++) {//reseting all tickets and profit
                    fprintf(funds, "0:0\n");
                }
                fclose(funds);


                funds = fopen("funds.txt", "r");// saving the reset
                for (i = 0; i < MAX_MOVIES; i++) readFiles2Int(funds, &movies[i].ticketSold, &movies[i].profit, i);
                fclose(funds);


                totalProfit = 0;
                break;
            case 3:
                printf("Exiting fund management...");
                // Sleep(1000);
                return;
                break;
        }
        system("cls");
    }while(1);

}

void movie_management(Movie movies[], int count) 
{
    int i;
    int choice;
    int price_input;

    FILE *movie, *genre, *synopsis, *price, *schedule;

    do{
        do{
            printf("MOVIE MANAGEMENT:\n");
            printf("\t[1]Edit movie titles\n\t[2]Edit movie genres\n\t[3]Edit movie description\n\t[4]Edit ticket price\n\t[5]Edit movie schedule\n\t[6]Exit movie management\nOption: ");
            scanf(" %d", &choice);

            while (getchar() != '\n');

            if(!(choice>0 && choice <7)){
                printf("Invalid input! Please try again...\n");
            }

        }while(!(choice>0 && choice <7));

        switch(choice){
            case 1:
                movie = fopen("movieTitles.txt", "w"); 
                if (movie == NULL) {
                    perror("Error opening file");
                    break;
                }
                // Ensure input is handled correctly for each movie
                for (i = 0; i < count; i++) {
                    printf("\tEnter title for movie [%d]: ", i + 1);

                    // Read input safely using fgets
                    if (fgets(movies[i].titles, MAX_TITLE_LENGTH, stdin) != NULL) {
                        // Remove newline character from the input if present
                        size_t length = strlen(movies[i].titles);
                        if (length > 0 && movies[i].titles[length - 1] == '\n') {
                            movies[i].titles[length - 1] = '\0';
                        }

                        fprintf(movie, "%s\n", movies[i].titles);
                    } else {
                        printf("Error reading movie title. Please try again.\n");
                        i--; // Repeat this iteration if input fails
                    }
                }
                fclose(movie);
                break;
            case 2:
                genre = fopen("genres.txt", "w"); 
                if (genre == NULL) {
                    perror("Error opening file");
                    break;
                }
                for(i = 0; i < count; i++){
                    printf("Enter genre for movie [%d] %s: ", i + 1, movies[i].titles);

                    if (fgets(movies[i].genres, MAX_TITLE_LENGTH, stdin) != NULL) {
                        size_t length = strlen(movies[i].genres);
                        if (length > 0 && movies[i].genres[length - 1] == '\n') {
                            movies[i].genres[length - 1] = '\0';
                        }

                        fprintf(genre, "%s\n", movies[i].genres);

                    } else {
                        printf("Error reading genre description. Please try again.\n");
                        i--; // Repeat this iteration if input fails
                    }
                }
                fclose(genre);
                break;
            case 3:
                synopsis = fopen("synopsis.txt", "w"); 
                if (synopsis == NULL) {
                    perror("Error opening file");
                    break;
                }

                for(i = 0; i < count; i++){
                    printf("Enter description for movie [%d] %s: ", i + 1, movies[i].titles);


                    if (fgets(movies[i].description, 1000, stdin) != NULL) {
                        size_t length = strlen(movies[i].description);
                        if (length > 0 && movies[i].description[length - 1] == '\n') {
                            movies[i].description[length - 1] = '\0';
                        }
                        fprintf(synopsis, "%s\n", movies[i].description);
                    } else {
                        printf("Error reading synopsis. Please try again.\n");
                        i--; // Repeat this iteration if input fails
                    }
                }
                fclose(synopsis);   
                break;
            case 4:
                price = fopen("price.txt", "w"); 
                if (price == NULL) {
                    perror("Error opening file");
                    break;
                }

                for(i = 0; i < count; i++){
                    printf("Enter price ticket for movie [%d] %s: ", i + 1, movies[i].titles);

                    if (scanf(" %d", &price_input) == 1 && price_input >= 0) {
                            movies[i].price = price_input; 
                            fprintf(price, "%d\n", movies[i].price);
                    } else {
                        printf("Error reading price ticket. Please try again.\n");
                        i--; // Repeat this iteration if input fails
                    }
                }
                fclose(price);   
                break;
            case 5:
                schedule = fopen("schedule.txt", "w"); 
                if (schedule == NULL) {
                    perror("Error opening file");
                    break;
                }
                for(i = 0; i < count; i++){
                	redo_time:
                    printf("Enter schedule(hour minute, 24-hour format) for movie [%d] %s: ", i + 1, movies[i].titles);
						
                    if (scanf("%d %d", &movies[i].startHour, &movies[i].startMinute) == 2) {
	                        if (&movies[i].startHour>24 || &movies[i].startMinute>60)
							{
								puts("INVALID INPUT: PLEASE TRY AGAIN!");
								goto redo_time;
							}
                        fprintf(schedule, "%d:%d\n", movies[i].startHour, movies[i].startMinute);
                    } else {
                        printf("Error reading movie schedule. Please try again.\n");
                        i--; // Repeat this iteration if input fails
                        while (getchar() != '\n');
                    }
                }
                fclose(schedule);
                break;
            case 6:
                printf("Exiting movie management...");
                // Sleep(1000);
                return;
                break;
        }
        system("cls");
    }while(1);

}

//------------------------------------------- UI -----------------------------------------------
void print_GUI ()
{
	puts("        Welcome to CINEMA SEATS");
	puts("=========================================");
	puts("|By Adeva - Aquino - Buhayan - Lo Priego|");
	puts("=========================================");
}
void print_menu ()
{ 
	puts("MENU OPTIONS:");
	puts("\t[1] Enter as ADMIN");
	puts("\t[2] Enter as CUSTOMER");
	puts("\t[3] View Available Movies");
	puts("\t[4] Exit program");
}
void print_with_dash(const char *str) 
{										//just prints the entered string with dashes ex. --hello--
    int maxLength = 40;
    int strLength = strlen(str);
    int i;
    
    // Ensure the string length does not exceed max length for fitting
    if (strLength >= maxLength) {
        printf("String too long to fit within 30 characters.\n");
        return;
    }
    
    int totalDash = maxLength - strLength;
    int leftDash = totalDash / 2;
    int rightDash = totalDash - leftDash;

    // Print left Dash
    for (i = 0; i < leftDash; i++) {
        printf("-");
    }
    
    // Print the input string
    printf("%s", str);
    
    // Print right asterisks
    for (i = 0; i < rightDash; i++) {
        printf("-");
    }
    
    printf("\n");
}

void print_movie(char movies[], char genres[], int price, int hour, int minute, char description[])
{ //prints the header kumbaga
    printf("----------------------------------------\n");
    printf("Movie Title: %s\n", movies);
    printf("Genre: %s\n", genres);
    printf("Price: P %d\n", price);
    printf("Movie shows on [%02d:%02d]\n\n", hour, minute);
    printf("Synopsis: %s\n\n", description);


}

int print_movie_seats_lowerBox(int movieIndex)
{ //prints the movies seats for lowerbox
    int i, j, k;
	printf("                             ");
    print_with_dash("Cinema Seats Lower Box");
    for (i = 0; i < ROWLOWERBOX; i++) { // row loop
    printf("              ");
        for (j = 0; j < COLUMNLOWERBOX; j++) { // column loop
            int isOccupied = 0; // Flag to check if seat is occupied
            for (k = 0; k < 151; k++) { // Check if seat is in occupied array
                if (movies[movieIndex].occupiedSeatsLowerBox[k] == seatsLowerBox[i][j]) {
                    isOccupied = 1;
                    break;
                }
            }
            if (isOccupied == 1) {
                printf("[ XX ]");
            } else {
                printf("[L%-3d]", seatsLowerBox[i][j]);
            }
        }
        printf("\n");
    }
}

int print_movie_seats_upperBox(int movieIndex) 
{//prints the movies seats for upperbox
    int i, j, k;
	printf("                             ");
    print_with_dash("Cinema Seats Upper Box");
    for (i = 0; i < ROWSUPPERBOX; i++) { // row loop
    printf("              ");
        for (j = 0; j < COLUMNSUPPERBOX; j++) { // column loop
            int isOccupied = 0; // Flag to check if seat is occupied
            for (k = 0; k < 113; k++) { // Check if seat is in occupied array
                if (movies[movieIndex].occupiedSeatsUpperBox[k] == seatsUpperBox[i][j]) {
                    isOccupied = 1;
                    break;
                }
            }
            if (isOccupied == 1) {
                printf("[ XX ]");
            } else {
                printf("[U%-3d]", seatsUpperBox[i][j]);
            }
        }
        printf("\n");
    }
}

//------------------------------------------ scheduling ----------------------------
void timer(int scheduledTime)
{
    int seconds = scheduledTime;
    int h, m, s;
    
    while(seconds>0){
        h = seconds/3600;
        m = (seconds%3600)/60;
        s = seconds % 60;
        char key;

        system("cls");
        printf("Movie starts in about...\n");
        printf("==========================\n");
        printf("        %02d:%02d:%02d", h, m, s);
        printf("\n==========================");
        printf("\n[Press Enter to leave]");
    

        fflush(stdout);

        clock_t stop = clock() + CLOCKS_PER_SEC;
        while(clock()<stop){
            if (kbhit()) {
                key = getch(); 
                if (key == '\r') { 
                    printf("\nExiting the countdown...\n");
                    return;
                }
            }

        }

        seconds--;
        

    }

    system("cls");
    printf("The movie is starting right now~!\n");
    printf("=====================================================");
    printf("\nPress Enter to leave");
    getchar();
    
}

void startScheduledMovies(int i) 
{
    time_t t = time(NULL);
    struct tm currentTime = *localtime(&t);
    
    t = time(NULL);
    currentTime = *localtime(&t);
    
    // Calculate the time difference between the current time and the movie start time
        int movieStartInSeconds = movies[i].startHour * 3600 + movies[i].startMinute * 60;
        int currentTimeInSeconds = currentTime.tm_hour * 3600 + currentTime.tm_min * 60 + currentTime.tm_sec;
        int timeDifference = movieStartInSeconds - currentTimeInSeconds;
        
        timer(timeDifference);
        
}

//----------------------------------------- Algorithm for seats ---------------------------------
void user_choose_seats_lower(int movieIndex)
{// where the user inputs his/her chosen seats in the lower box
    int i, index, count = 0, loop, profit, seatAvailable = 0;
    printf("How many seats are you buying?\n"); // lowerbox
    scanf(" %d", &UserNumberOfSeats);
	int j;
    for (i = 0; i < UserNumberOfSeats; i++){// loops through and gets all the seats the costumer want
        do{
            loop = 0;
            printf("Seat #%d: \n", i+1);
            scanf(" %d", &UserChosenlowerBoxSeats[i]); 
            if (UserChosenlowerBoxSeats[i] <= 0 || UserChosenlowerBoxSeats[i] >= 151){// checks if the seat input is within range
                printf("There is no seat %d\n", UserChosenlowerBoxSeats[i]);
                printf("Enter a new seat"); 
                loop = 1;
            } else {
                for (j = 0; j < 151; j++) {
                    if (movies[movieIndex].occupiedSeatsLowerBox[j] == UserChosenlowerBoxSeats[i]) {
                        printf("Seat %d is already taken. Please choose another seat.\n", UserChosenlowerBoxSeats[i]);
                        loop = 1;
                        break;
                    }
                }
            }
        }while(loop);
    }

    system("cls");
    printf("Your total is P %d!\n", movies[movieIndex].price * UserNumberOfSeats);
    profit = movies[movieIndex].price * UserNumberOfSeats;
    movies[movieIndex].profit += profit;
    movies[movieIndex].ticketSold += UserNumberOfSeats;

    printf("You chose seat/s: ");
    for(i = 0; i < UserNumberOfSeats; i++){
        printf("%d ", UserChosenlowerBoxSeats[i]); // output chosen seats. for checking, pwede tanggalin or hindi sa final code
    }

    index = find_the_first_index_with_zero_lowerbox(movies[movieIndex].occupiedSeatsLowerBox); // append() function. gina find niya ang index na may 0. or the index next to that last number/seat
    for (i = index; i < (index + UserNumberOfSeats); i++){
        movies[movieIndex].occupiedSeatsLowerBox[i] = UserChosenlowerBoxSeats[count];
        count++;
    }

    printf("Occupied seat/s are: ");
    for(i = 0; i < index + count; i++){
        printf("%d ", movies[movieIndex].occupiedSeatsLowerBox[i]); // output occupied seats. for checking, pwede tanggalin or hindi sa final code
    }
    printf("\n"); 

    index = find_the_first_index_with_zero_lowerbox(movies[movieIndex].occupiedSeatsLowerBox);
    printf("index is %d", index);// output index seats. for checking, tanggalin ito sa final code

    printf("\nPress Enter to continue...");
    getchar();
    getchar();
    system("cls");

    startScheduledMovies(movieIndex);

    system("cls");
}

void user_choose_seats_upper(int movieIndex)
{// where the user inputs his/her chosen seats in the upper box
    int i, index, count = 0, loop, profit, seatAvailable = 0;
    printf("How many seats are you buying?\n"); // upperbox
    scanf(" %d", &UserNumberOfSeats);
	int j;
    for (i = 0; i < UserNumberOfSeats; i++){// loops through and gets all the seats the costumer want
        do{
            loop = 0;
            printf("Seat #%d: \n", i+1);
            scanf(" %d", &UserChosenUpperBoxSeats[i]); 
            if (UserChosenUpperBoxSeats[i] <= 0 || UserChosenUpperBoxSeats[i] >= 112){// checks if the seat input is within range
                printf("There is no seat %d\n", UserChosenUpperBoxSeats[i]);
                printf("Enter a new seat"); 
                loop = 1;
            } else {
                for (j = 0; j < 112; j++) {
                    if (movies[movieIndex].occupiedSeatsUpperBox[j] == UserChosenUpperBoxSeats[i]) {
                        printf("Seat %d is already taken. Please choose another seat.\n", UserChosenUpperBoxSeats[i]);
                        loop = 1;
                        break;
                    }
                }
            }
        }while(loop);
    }

    system("cls");
    printf("Your total is P %d!\n", movies[movieIndex].price * UserNumberOfSeats);
    profit = movies[movieIndex].price * UserNumberOfSeats;
    movies[movieIndex].profit += profit;
    movies[movieIndex].ticketSold += UserNumberOfSeats;

    printf("You chose seat/s: ");
    for(i = 0; i < UserNumberOfSeats; i++){
        printf("%d ", UserChosenUpperBoxSeats[i]); // output chosen seats. for checking, pwede tanggalin or hindi sa final code
    }

    index = find_the_first_index_with_zero_upperbox(movies[movieIndex].occupiedSeatsUpperBox); // append() function. gina find niya ang index na may 0. or the index next to that last number/seat
    for (i = index; i < (index + UserNumberOfSeats); i++){
        movies[movieIndex].occupiedSeatsUpperBox[i] = UserChosenUpperBoxSeats[count];
        count++;
    }

    printf("Occupied seat/s are: ");
    for(i = 0; i < index + count; i++){
        printf("%d ", movies[movieIndex].occupiedSeatsUpperBox[i]); // output occupied seats. for checking, pwede tanggalin or hindi sa final code
    }
    printf("\n"); 

    index = find_the_first_index_with_zero_upperbox(movies[movieIndex].occupiedSeatsUpperBox);
    printf("index is %d", index);// output index seats. for checking, tanggalin ito sa final code

    printf("\nPress Enter to continue...");
    getchar();
    getchar();
    system("cls");

    startScheduledMovies(movieIndex);

    system("cls");
}

int find_the_first_index_with_zero_lowerbox(int OccupiedSeatsLowerBox[]) 
{ // this basically functions as the append() function, mag start og add numbers sa first index na may 0 or sa last item. safe ni kay wala may 0 na seat number 
    int i;
	for (i = 0; i < 151; i++) {
        if (OccupiedSeatsLowerBox[i] == 0) {
            return i;  // Return the index of the first 0 found
        }
    }
}

int find_the_first_index_with_zero_upperbox(int OccupiedSeatsUpperBox[]) 
{ // this basically functions as the append() function, mag start og add numbers sa first index na may 0 or sa last item. safe ni kay wala may 0 na seat number 
    int i;
	for (i = 0; i < 151; i++) {
        if (OccupiedSeatsUpperBox[i] == 0) {
            return i;  // Return the index of the first 0 found
        }
    }
}

//--------------------------------- reading files -----------------------------------------------------------
void readFiles(FILE *file, char stored[MAX_TITLE_LENGTH], int index) 
{
    if (fgets(stored, MAX_TITLE_LENGTH, file)) {
        size_t len = strlen(stored);
        if (len > 0 && stored[len - 1] == '\n') {
            stored[len - 1] = '\0';
        }
    }
}

void readFilesDescription(FILE *file, char stored[1000], int index)
{
    if (fgets(stored, 1000, file)) {  // Read only one line per call
        size_t len = strlen(stored);
        if (len > 0 && stored[len - 1] == '\n') {
            stored[len - 1] = '\0';  // Remove the trailing newline
        }
    }
}

void readFilesPrice(FILE *file, int *stored, int index){
    if(file != NULL){
        fscanf(file, "%d", stored);
    }
}

void readFiles2Int(FILE *file, int *stored,int *anotherStored, int index)
{
    char currentLine[100];
    
    if (fgets(currentLine, sizeof(currentLine), file)) {
        // Use sscanf to parse the hour and minute from the line
        if (sscanf(currentLine, "%d:%d", stored, anotherStored) != 2) {
            printf("Error: Failed to parse the integers from line: %s\n", currentLine);
        }
    }
}

//Writes down the current funds into funds.txt
void writeFundsToFile() 
{
    FILE *funds = fopen("funds.txt", "w");
    if (!funds) {
        printf("Error opening funds.txt for writing.\n");
        return;
    }
	int i;
    for (i = 0; i < MAX_MOVIES; i++) {
        fprintf(funds, "%d:%d\n", movies[i].ticketSold, movies[i].profit);
    }

    fclose(funds);
}

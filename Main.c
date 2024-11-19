#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define MAX_MOVIES 5
#define MAX_TITLE_LENGTH 100
#define ROWLOWERBOX 15
#define COLUMNLOWERBOX 10
#define ROWSUPPERBOX 8
#define COLUMNSUPPERBOX 14

char movies[MAX_MOVIES][MAX_TITLE_LENGTH];

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
int movie_to_watch;// the user inputted choice of movie is saved here
int UserNumberOfSeats, UserChosenUpperBoxSeats[200], UserChosenlowerBoxSeats[200]; // user number of seats is how many seats the user wanna buy/chose. The others is the array of all occupied seats
int OccupiedSeatsLowerBox[200], OccupiedSeatsUpperBox[200];// Array of all occupied seats on both boxes
char UserChosenBox[20]; // Upperbox or Lower box

void get_movie_titles(char movies[][MAX_TITLE_LENGTH], int count) {
    int i;
    
    // Ensure input is handled correctly for each movie
    for (i = 0; i < count; i++) {
        printf("Enter title for movie %d: ", i + 1);

        // Clear stdin before reading (useful if called after scanf)
        fflush(stdin);

        // Read input safely using fgets
        if (fgets(movies[i], MAX_TITLE_LENGTH, stdin) != NULL) {
            // Remove newline character from the input if present
            size_t length = strlen(movies[i]);
            if (length > 0 && movies[i][length - 1] == '\n') {
                movies[i][length - 1] = '\0';
            }
        } else {
            printf("Error reading movie title. Please try again.\n");
            i--; // Repeat this iteration if input fails
        }
    }
    
}


void print_GUI (){
	printf("        Welcome to CINEMA SEATS\n");
	printf("=======================================\n");
	printf("By Adeva - Aquino - Buhayan - Lo Priego\n");
	printf("=======================================\n");
}

void print_menu (){
	printf("MENU OPTIONS:\n");
	printf("[1] Enter as ADMIN\n");
	printf("[2] Enter as CUSTOMER\n");
	printf("[3] View Available Movies\n");
}

void print_with_dash(const char *str) {//just prints the entered string with dashes ex. --hello--
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

void print_movie(char movies[]){ //prints the header kumbaga
    printf("----------------------------------------\n");
    printf("Movie Title: %s\n", movies);
    printf("Genre: Whatever the genre of this movie\n");
    printf("Rating: G\n");
}

int find_the_first_index_with_zero_lowerbox(int OccupiedSeatsLowerBox[]) {
    int i;
	for (i = 0; i < 151; i++) {
        if (OccupiedSeatsLowerBox[i] == 0) {
            return i;  // Return the index of the first 0 found
        }
    }
}

int find_the_first_index_with_zero_upperbox(int OccupiedSeatsUpperBox[]) {
    int i;
	for (i = 0; i < 151; i++) {
        if (OccupiedSeatsUpperBox[i] == 0) {
            return i;  // Return the index of the first 0 found
        }
    }
}

int print_movie_seats_lowerBox(){ //prints the movies seats for lowerbox
    int i, j, k;
	printf("                             ");
    print_with_dash("Cinema Seats Lower Box");
    for (i = 0; i < ROWLOWERBOX; i++) { // row loop
    printf("              ");
        for (j = 0; j < COLUMNLOWERBOX; j++) { // column loop
            int isOccupied = 0; // Flag to check if seat is occupied
            for (k = 0; k < 151; k++) { // Check if seat is in occupied array
                if (OccupiedSeatsLowerBox[k] == seatsLowerBox[i][j]) {
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

int print_movie_seats_upperBox() {//prints the movies seats for upperbox
    int i, j, k;
	printf("                             ");
    print_with_dash("Cinema Seats Upper Box");
    for (i = 0; i < ROWSUPPERBOX; i++) { // row loop
    printf("              ");
        for (j = 0; j < COLUMNSUPPERBOX; j++) { // column loop
            int isOccupied = 0; // Flag to check if seat is occupied
            for (k = 0; k < 113; k++) { // Check if seat is in occupied array
                if (OccupiedSeatsUpperBox[k] == seatsUpperBox[i][j]) {
                    isOccupied = 1;
                    break;
                }
            }
            if (isOccupied == 1) {
                printf("[ XX ]");
            } else {
                printf("[L%-3d]", seatsUpperBox[i][j]);
            }
        }
        printf("\n");
    }
    
    /*int i, j;
	printf("                             ");
    print_with_dash("Cinema Seats Upper Box");
    for (i = 0; i < ROWSUPPERBOX; i++) {
        for (j = 0; j < COLUMNSUPPERBOX; j++) {
            printf("[U%-3d] ", seatsUpperBox[i][j]); // %-3d pads to 3 characters
        }
        printf("\n");
    }
    printf("\n");*/
}

void user_choose_seats_lower(){// where the user inputs his/her chosen seats in the lower box
    int i, index, count = 0;
    printf("How many seats are you buying?\n"); // lowerbox
    scanf(" %d", &UserNumberOfSeats);
    for (i = 0; i < UserNumberOfSeats; i++){// loops through and gets all the seats the costumer want
        EnterASeat1:
        printf("Seat #%d: \n", i+1);
        scanf(" %d", &UserChosenlowerBoxSeats[i]); 
        if (UserChosenlowerBoxSeats[i] <= 0 || UserChosenlowerBoxSeats[i] >= 151){// checks if the seat input is within range
            printf("There is no seat %d\n", UserChosenlowerBoxSeats[i]);
            printf("Enter a new seat");
            goto EnterASeat1; 
        }
    }

    printf("You chose seat/s: ");
    for(i = 0; i < UserNumberOfSeats; i++){
        printf("%d ", UserChosenlowerBoxSeats[i]);
    }
    
    index = find_the_first_index_with_zero_lowerbox(OccupiedSeatsLowerBox);
    for (i = index; i < (index + UserNumberOfSeats); i++){
        OccupiedSeatsLowerBox[i] = UserChosenlowerBoxSeats[count];
        count++;
    }

    printf("Occupied seat/s are: ");
    for(i = 0; i < index + count; i++){
        printf("%d ", OccupiedSeatsLowerBox[i]);
    }
    printf("\n"); 

    index = find_the_first_index_with_zero_lowerbox(OccupiedSeatsLowerBox);
    printf("index is %d", index);
}

void user_choose_seats_upper(){// where the user inputs his/her chosen seats in the upper box
    int i, index, count = 0;
    printf("How many seats are you buying?\n"); // uperbox
    scanf(" %d", &UserNumberOfSeats);
    for (i = 0; i < UserNumberOfSeats; i++){// loops through and gets all the seats the costumer want
        EnterASeat2:
        printf("Seat #%d: \n", i+1);
        scanf(" %d", &UserChosenUpperBoxSeats[i]); 
        if (UserChosenUpperBoxSeats[i] <= 0 || UserChosenUpperBoxSeats[i] >= 112){// checks if the seat input is within range
            printf("There is no seat %d\n", UserChosenUpperBoxSeats[i]);
            printf("Enter a new seat");
            goto EnterASeat2; 
        }
    }

    printf("You chose seat/s: ");
    for(i = 0; i < UserNumberOfSeats; i++){
        printf("%d ", UserChosenUpperBoxSeats[i]);
    }
    
    index = find_the_first_index_with_zero_upperbox(OccupiedSeatsUpperBox);
    for (i = index; i < (index + UserNumberOfSeats); i++){
        OccupiedSeatsUpperBox[i] = UserChosenUpperBoxSeats[count];
        count++;
    }

    printf("Occupied seat/s are: ");
    for(i = 0; i < index + count; i++){
        printf("%d ", OccupiedSeatsUpperBox[i]);
    }
    printf("\n"); 

    index = find_the_first_index_with_zero_upperbox(OccupiedSeatsUpperBox);
    printf("index is %d", index);
    
    
    
    /*int i, count = 0, index;
    printf("How many seats are you buying?\n"); // upperbox
    scanf(" %d", &UserNumberOfSeats);
    for (i = 0; i < UserNumberOfSeats; i++){ // loops through and gets all the seats the costumer want
        EnterASeat2:
        printf("Seat #%d: \n", i+1);
        scanf(" %d", &UserChosenUpperBoxSeats[i]);
        if (UserChosenUpperBoxSeats[i] <= 0 || UserChosenUpperBoxSeats[i] >= 113){// checks if the seat input is within range
            printf("There is no seat %d\n", UserChosenlowerBoxSeats[i]);
            printf("Enter a new seat");
            goto EnterASeat2; 
        }
    }
    
    printf("You chose seat/s: ");
    for(i = 0; i < UserNumberOfSeats; i++){
        printf("%d ", UserChosenUpperBoxSeats[i]);
    }
 
    index = find_the_first_index_with_zero_upperbox(OccupiedSeatsUpperBox);
    for (i = index; i < UserNumberOfSeats; i++){
        OccupiedSeatsUpperBox[i] = UserChosenUpperBoxSeats[0 + count];
        count++;
    }
    printf("Occupied seat/s are: ");
    for(i = 0; i < UserNumberOfSeats; i++){
        printf("%d ", OccupiedSeatsUpperBox[i]);
    }*/
}

int main(){
	invalid_option:
	start:
	print_GUI();
	print_menu();
	int option, i, password = 123, password_try, leave;
	printf("Option: ");
	scanf(" %d", &option);
	
	//MENU LOGIC
	if(option == 1){
		printf("Admin Password: "); //Password is 123;
		scanf(" %d", &password_try);
		//sleep(1);
		if(password == password_try)
		{
			
	get_movie_titles(movies, movie_count);// if admin 
			system("cls");
			goto start;
		} else
		{
			puts("Wrong Password");
			//sleep(2);
			system("cls");
			goto invalid_option;
		}
		
	} else if (option == 2)
	{
		    goto buy_tickets;
		    
	} else if (option ==3)
	{
				system("cls");
			    print_GUI();
			    printf("The Movies Showing Today Are:\n");
			    for (i = 0; i < movie_count; i++) {// print movie list
			        printf("[%d] %s\n", i + 1, movies[i]);
			    }
	
				    while (1) {
				   	printf("========================");
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
				goto start;
		
	} else {
		puts("Invalid Input!");
		sleep(2);
		system("cls");
		
		goto invalid_option;
	}
	
	
    buy_tickets:
    
    system("cls");	
    print_GUI();
    printf("The Movies Showing Today Are:\n");
    for (i = 0; i < movie_count; i++) {// print movie list
        printf("[%d] %s\n", i + 1, movies[i]);
    }
    printf("\nWhat are you watching today?\nOption: ");
    scanf(" %d", &movie_to_watch);
    
    
    switch (movie_to_watch){
    case 1:
        print_movie(movies[0]);
        print_movie_seats_lowerBox();
        print_movie_seats_upperBox();
        choose1:
        printf("\nWhere do you wanna go?\n[Lower Box] or [Upper Box]?\nOption: ");
        scanf(" %19s", &UserChosenBox);
        
        
        if (strcmp(UserChosenBox, "Lower") == 0) {
            user_choose_seats_lower();
        }
        else if(strcmp(UserChosenBox, "Lower Box" ) == 0){
            user_choose_seats_lower();
        }
        else if(strcmp(UserChosenBox, "Upper") == 0){
            user_choose_seats_upper();
        }   
        else if(strcmp(UserChosenBox, "Upper Box") == 0){
            user_choose_seats_upper();
        }
        else{
            printf("\nChoose Again");
            goto choose1;
        }     
        goto start;   
        break;
    case 2:
        print_movie(movies[1]);
        print_movie_seats_lowerBox();
        print_movie_seats_upperBox();
        choose2:
        printf("\nWhere do you wanna go?\n[Lower Box] or [Upper Box]?\nOption: ");
        scanf(" %19s", &UserChosenBox);
        if (strcmp(UserChosenBox, "Lower") == 0) {
            user_choose_seats_lower();
        }
        else if(strcmp(UserChosenBox, "Lower Box" ) == 0){
            user_choose_seats_lower();
        }
        else if(strcmp(UserChosenBox, "Upper") == 0){
            user_choose_seats_upper();
        }   
        else if(strcmp(UserChosenBox, "Upper Box") == 0){
            user_choose_seats_upper();
        }
        else{
            printf("\nChoose Again");
            goto choose2;
        }     
        goto start;   
        break;
    case 3:
        print_movie(movies[2]);
        print_movie_seats_lowerBox();
        print_movie_seats_upperBox();
        choose3:
        printf("\nWhere do you wanna go?\n[Lower Box] or [Upper Box]?\nOption: ");
        scanf(" %19s", &UserChosenBox);
        if (strcmp(UserChosenBox, "Lower") == 0) {
            user_choose_seats_lower();
        }
        else if(strcmp(UserChosenBox, "Lower Box" ) == 0){
            user_choose_seats_lower();
        }
        else if(strcmp(UserChosenBox, "Upper") == 0){
            user_choose_seats_upper();
        }   
        else if(strcmp(UserChosenBox, "Upper Box") == 0){
            user_choose_seats_upper();
        }
        else{
            printf("\nChoose Again");
            goto choose3;
        }     
        goto start;   
        break;
    case 4:
        print_movie(movies[3]);
        print_movie_seats_lowerBox();
        print_movie_seats_upperBox();
        choose4:
        printf("\nWhere do you wanna go?\n[Lower Box] or [Upper Box]?\nOption: ");
        scanf(" %19s", &UserChosenBox);
        if (strcmp(UserChosenBox, "Lower") == 0) {
            user_choose_seats_lower();
        }
        else if(strcmp(UserChosenBox, "Lower Box" ) == 0){
            user_choose_seats_lower();
        }
        else if(strcmp(UserChosenBox, "Upper") == 0){
            user_choose_seats_upper();
        }   
        else if(strcmp(UserChosenBox, "Upper Box") == 0){
            user_choose_seats_upper();
        }
        else{
            printf("\nChoose Again");
            goto choose4;
        }     
        goto start;   
        break;
    case 5:
        print_movie(movies[4]);
        print_movie_seats_lowerBox();
        print_movie_seats_upperBox();
        choose5:
        printf("\nWhere do you wanna go?\n[Lower Box] or [Upper Box]?\nOption: ");
        scanf(" %19s", &UserChosenBox);
        if (strcmp(UserChosenBox, "Lower") == 0) {
            user_choose_seats_lower();
        }
        else if(strcmp(UserChosenBox, "Lower Box" ) == 0){
            user_choose_seats_lower();
        }
        else if(strcmp(UserChosenBox, "Upper") == 0){
            user_choose_seats_upper();
        }   
        else if(strcmp(UserChosenBox, "Upper Box") == 0){
            user_choose_seats_upper();
        }
        else{
            printf("\nChoose Again");
            goto choose5;
        }     
        goto start;   
        break;        
    }

	goto start;
}



// Carpark
//
// This program was written by [Alina Cui] (z5416104)
// on [10/07/23]
//
// TODO: Description of program

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>


// Provided constants
#define CARPARK_ROWS 8
#define CARPARK_COLUMNS 6
#define NORMAL_PARKING_RATE 10
#define EMPTY -1

// Your constants here (i changed lol)
#define TOTAL_CARSPACE 48
#define PREMIUM_PARKING_RATE 50

// Provided enums
enum space_type {
    NORMAL,
    PREMIUM,
    CARWASH_BAY,
    ELECTRIC_CHARGING_STATION
};


// Provided structs
struct car_space {
    enum space_type type;
    int parking_rate;
    int licence_plate;
    int occupied_since;

    //below i included:
    int normal_parking_rate;
    int premium_parking_rate;
};



////////////////////////////////////////////////////////////////////////////////
////////////////////////  YOUR FUNCTION PROTOTYPE  /////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// TODO: Put your function prototypes here

////////////////////////////////////////////////////////////////////////////////
////////////////////// PROVIDED FUNCTION PROTOTYPE  ////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void initialise_carpark(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]);
void print_carpark(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]);
void print_car_space(struct car_space space);

///MY FUNCTIONSSSS
void checking_carspace(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]);
int number_of_car_space (struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]);
void print_available_spaces(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]);
void normal_discount (struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]);
void premium_discount (struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]);
void discounted (struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS], double discount);
void find_a_car (struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]);
void parking_car (struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS],
                 int licence_plate_no, int row, int col, int time_of_entry);
void leaving_the_carpark(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]);
void find_car(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS], int licence_plate_no, int time_of_exit, double discount);
void remove_car(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS], int row, int col);
int calculate_price(enum space_type type, int parking_rate, int total_time);



int main(void) {

    struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS];

    initialise_carpark(carpark);
    // TODO: Start writing code here!

    // TODO: Stage 1.1 
    printf("Welcome to CS Carpark!\n\n");
    printf("Which row of the carpark would you like to reserve for premium parking? ");
    int row_premium;
    int col = CARPARK_COLUMNS;
    int row = CARPARK_ROWS;

    float discount = 0.1;

    scanf("%d", &row_premium);

    while (col > 0) {
        carpark[row_premium][col-1].type = PREMIUM;
        col--;
    }
    print_carpark(carpark);

    // TODO: Stage 1.2 - Scan in the initial cars.
    printf("Add all current cars to the carpark. How many cars would you like to add? ");
    

    int add_car;
    scanf("%d", &add_car);
    assert(add_car <= 48);
    printf("Where would you like to park each car? \n");

    int i = 0;
    int licence_plate_no;

    while (i < add_car) {
        if (i == 0) {
            // printf("Where would you like to park each car? \n");
        }
        scanf("%4d %d %d", &licence_plate_no, &row, &col);
        i++;
        
        if (row < CARPARK_ROWS && col < CARPARK_COLUMNS) {
            carpark[row][col].licence_plate = licence_plate_no;   
        } else {  
            printf("Invalid car space! \n");
        }
    }

    print_carpark(carpark);

    printf("The carpark is now ready for business! \n");

    //Stage 1.3 & 1.4 & 1.5
    char command; 
    printf("Enter a command: ");

    while (scanf(" %c", &command) == 1) {
        if (command == 'P') {
            print_carpark(carpark);
            printf("Enter a command: ");

            // if p - parking
        } else if (command == 'p') {
            
            bool carspace_occupied;
            bool carspace_not_occupied;
            int time_of_entry;

            int scan_result = scanf(" %4d %d %d %d", &licence_plate_no, &row, &col, 
                        &time_of_entry);

            carspace_occupied = ((row >= 0 && row < CARPARK_ROWS && col >= 0 
                && col < CARPARK_COLUMNS) && (carpark[row][col].licence_plate != EMPTY));

            carspace_not_occupied = ((row >= 0 && row < CARPARK_ROWS && col >= 0 
                && col < CARPARK_COLUMNS) && (carpark[row][col].licence_plate == EMPTY));


            if ((scan_result == 4) && (carspace_not_occupied)) {
                parking_car(carpark, licence_plate_no, row, col, time_of_entry);

            } else if (carspace_occupied) {
                printf("Car space is already occupied!\n");

            } else {
                printf("Invalid car space!\n");

            }
            printf("Enter a command: ");
            
            // ' o' COMMAND
        } else if (command == 'o') {
            int number_of_total_car = number_of_car_space (carpark);
            int number_of_empty_space = TOTAL_CARSPACE - number_of_total_car;

            printf("There are currently %d cars and %d empty car spaces in the carpark.",
                    number_of_total_car, number_of_empty_space); 
            printf("\n");

            printf("Enter a command: "); 

            // 'F' Command
        } else if (command == 'F') {
            print_available_spaces(carpark);
            printf("\n");
            printf("Enter a command: "); 

            //'d' Operation
        } else if (command == 'd') {
            discounted(carpark, discount);
            printf("\n");
            printf("Enter a command: "); 

            //'f' Operation
        } else if (command == 'f') {
            find_a_car(carpark);
            printf("\n");
            printf("Enter a command: ");

        } else if (command == 'l') {
            leaving_the_carpark(carpark);
            printf("\n");
            printf("Enter a command: ");
        }
    }

    if (scanf(" %c", &command) == EOF) {
        printf("The carpark is now closed. Bye!\n");
    }
}


////////////////////////////////////////////////////////////////////////////////
/////////////////////////////  YOUR FUNCTIONS //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// TODO: Put your functions here

//'e' Operation

// 'p' Operation
void parking_car (struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS],
                 int licence_plate_no, int row, int col, int time_of_entry) {
    if (row < CARPARK_ROWS && col < CARPARK_COLUMNS) {
        if (carpark[row][col].licence_plate == EMPTY) {
            carpark[row][col].licence_plate = licence_plate_no;
            carpark[row][col].occupied_since = time_of_entry;
            printf("Car %4d was added into car space (%d, %d) at time %d!\n",
                licence_plate_no, row, col, time_of_entry);
        } else {
            printf("Car space is already occupied! \n");
        }
    } else {
        printf("Invalid car space!\n");
    }

}

//'l' Operation
void leaving_the_carpark(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]) {
    int licence_plate_no = 0;
    int time_of_exit;
    double discount = 0;

    scanf(" %4d %d", &licence_plate_no, &time_of_exit);

    find_car(carpark, licence_plate_no, time_of_exit, discount);
}


void find_car(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS],
                int licence_plate_no, int time_of_exit, double discount) {
    for (int row = 0; row < CARPARK_ROWS; row++) {
        for (int col = 0; col < CARPARK_COLUMNS; col++) {
            if (carpark[row][col].licence_plate == licence_plate_no) {
                // int parking_rate = carpark[row][col].parking_rate;

                int total_time = 0;

                if (carpark[row][col].occupied_since == EMPTY) {
                    carpark[row][col].occupied_since = 0;
                }
                total_time = (time_of_exit - carpark[row][col].occupied_since);

                if (discount) {
                    normal_discount(carpark);
                    premium_discount(carpark);
                }

                int price;
                if (carpark[row][col].type == NORMAL) {
                    int parking_rate = carpark[row][col].normal_parking_rate;
                    price = parking_rate * total_time;
                } else if (carpark[row][col].type == PREMIUM) {
                    int parking_rate = carpark[row][col].premium_parking_rate;
                    price = parking_rate * total_time;
                } else {
                    price = 0;  

                } 
                
                if (total_time <= 0 || (total_time > time_of_exit)) {
                    printf("The time of exit provided is invalid.");

                    return;
                }

                remove_car(carpark, row, col);

                printf("Car %4d was parked for %d hours.", licence_plate_no, total_time);
                printf(" The total price for this duration is $%d.", price);
                return;
            }
        }
    }

    printf("No car with licence plate number %4d could be found.", licence_plate_no);
}


void remove_car(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS], 
                int row, int col) {
    carpark[row][col].licence_plate = EMPTY;
    carpark[row][col].occupied_since = EMPTY;
    if (carpark[row][col].type == NORMAL) {
        carpark[row][col].normal_parking_rate = NORMAL_PARKING_RATE;
    } else if (carpark[row][col].type == PREMIUM) {
        carpark[row][col].premium_parking_rate = PREMIUM_PARKING_RATE;
    }
}



//'p' Operation

void find_a_car (struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]){
    int licence_plate_no;
    scanf(" %4d", &licence_plate_no);

    bool car_find = false;

    for (int row = 0; row < CARPARK_ROWS; row++) {
        for (int col = 0; col < CARPARK_COLUMNS; col++) {
            if (carpark[row][col].licence_plate == licence_plate_no) {
                printf("Car %4d is parked in car space (%d, %d).",
                         licence_plate_no, row, col);
                car_find = true;
            } 
        } 
    }
    if (!car_find) {
        printf("No car with licence plate number %4d could be found.", licence_plate_no);
    }
}

// 'd' normal
void normal_discount (struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]){

    double normal_rate;

    for (int row = 0; row < CARPARK_ROWS; row++) {
        for (int col = 0; col < CARPARK_COLUMNS; col++) {
            bool carspace_not_occupied = (carpark[row][col].licence_plate == EMPTY);
            if (carspace_not_occupied && (carpark[row][col].type == NORMAL)) {
                double rate = (carpark[row][col].normal_parking_rate);
                normal_rate = ((0.95) * rate);
                carpark[row][col].normal_parking_rate = normal_rate;
            }
        }
    }       
}

// 'd' premium 
void premium_discount (struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]){
    double premium_rate;

    for (int row = 0; row < CARPARK_ROWS; row++) {
        for (int col = 0; col < CARPARK_COLUMNS; col++) {
            bool carspace_not_occupied = (carpark[row][col].licence_plate == EMPTY);
            if (carspace_not_occupied && (carpark[row][col].type == PREMIUM)) {
                double rate = (carpark[row][col].premium_parking_rate);
                premium_rate = ((0.9) * rate);
                carpark[row][col].premium_parking_rate = premium_rate;
            }
        }
    }       
}
// 'd' Operation

void discounted(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS],
                double discount) {
    if (discount) {
        printf("A 10%% discount has been applied to all empty spaces!");

        normal_discount(carpark);
        premium_discount(carpark);
    }
}

// 'F' Operation

void print_available_spaces(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]) {


    bool normal_available_space = false;
    bool premium_available_space = false;
    bool carspace_not_occupied; 
    bool carspace_normal;
    bool carspace_premium;
    int premium_parking_rate;
    int normal_parking_rate;

    printf("The normal car spaces that are still available are:\n");
    for (int row = 0; row < CARPARK_ROWS; row++) {
        for (int col = 0; col < CARPARK_COLUMNS; col++) {
            normal_parking_rate = carpark[row][col].normal_parking_rate;
            carspace_not_occupied = (carpark[row][col].licence_plate == EMPTY);
            carspace_normal = (carpark[row][col].type == NORMAL);

            if (carspace_not_occupied && carspace_normal) {
                printf("(%d, %d): $%d\n", row, col, normal_parking_rate);
                normal_available_space = true;

            }
        }
    }

    if (!normal_available_space) {
        printf("NONE\n");

    }
    printf("\n");
    printf("The premium car spaces that are still available are:\n");
    for (int row = 0; row < CARPARK_ROWS; row++) {
        for (int col = 0; col < CARPARK_COLUMNS; col++) {
            // premium_parking_rate = (normal_parking_rate * 5);
            premium_parking_rate = (carpark[row][col].premium_parking_rate);
            carspace_not_occupied = (carpark[row][col].licence_plate == EMPTY);
            carspace_premium = (carpark[row][col].type == PREMIUM);

            if (carspace_not_occupied && carspace_premium) {
                printf("(%d, %d): $%d\n", row, col, premium_parking_rate);
                premium_available_space = true;
            }
        }
    }
    

    if (!premium_available_space) {
        printf("NONE\n");

    }
}


//'o' Operation
int number_of_car_space (struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]) {
    int number_of_total_car = 0;
    for (int row = 0; row < CARPARK_ROWS; row++) {
        for (int col = 0; col < CARPARK_COLUMNS; col++) {
            if (carpark[row][col].licence_plate != EMPTY) {
                number_of_total_car++;
            }
        }
    }
    return number_of_total_car;
}    



///////////////////////////////////////////////////////////////////////////////
/////////////////////////// PROVIDED FUNCTIONS  ///////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/**
 * Initialises carpark spaces as NORMAL spaces with NORMAL_PARKING_RATE that are
 * initially EMPTY.
 * 
 * Parameters:
 *     carpark - The carpark to initialise.
 * Returns:
 *     Nothing.
 */

 //those that i changed:

void initialise_carpark(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]) {
    for (int row = 0; row < CARPARK_ROWS; row++) {
        for (int col = 0; col < CARPARK_COLUMNS; col++) {
            carpark[row][col].type = NORMAL;
            carpark[row][col].normal_parking_rate = NORMAL_PARKING_RATE;
            carpark[row][col].premium_parking_rate = PREMIUM_PARKING_RATE;
            carpark[row][col].licence_plate = EMPTY;
            carpark[row][col].occupied_since = EMPTY;
        }
    }
}

// original below
/*void initialise_carpark(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]) {
    for (int row = 0; row < CARPARK_ROWS; row++) {
        for (int col = 0; col < CARPARK_COLUMNS; col++) {
            carpark[row][col].type = NORMAL;
            carpark[row][col].parking_rate = NORMAL_PARKING_RATE;
            carpark[row][col].licence_plate = EMPTY;
            carpark[row][col].occupied_since = EMPTY;
        }
    }
}
*/

/**
 * Prints all carpark spaces, displaying their type and the licence plate of 
 * any cars parked in the carpark.
 * 
 * Parameters:
 *     carpark   - The carpark to be printed
 * Returns:
 *     Nothing.
 */
void print_carpark(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]) {
    printf("-------------------------------------------------------------------\n");
    for (int row = 0; row < CARPARK_ROWS; row++) {
        for (int col = 0; col < CARPARK_COLUMNS; col++) {
            print_car_space(carpark[row][col]);
        }
        printf("|\n");
        printf("-------------------------------------------------------------------\n");
    }
    printf("\n");
}

/**
 * Prints the type of a particular car space, as well as the licence plate of 
 * the car located at that car space.
 * 
 * Parameters:
 *     car_space         - The car space to print.
 *
 * Returns:
 *     Nothing.
 */
void print_car_space(struct car_space car_space) {
    printf("|");
    if (car_space.type == NORMAL) {
        printf(" N :");
    } else if (car_space.type  == PREMIUM) {
        printf(" P :");
    } else if (car_space.type  == CARWASH_BAY) {
        printf(" W :");
    } else if (car_space.type  == ELECTRIC_CHARGING_STATION) {
        printf(" CHARGER  ");
    }
    if (car_space.type != ELECTRIC_CHARGING_STATION) {
        if (car_space.licence_plate == EMPTY) {
            printf("      ");
        } else {
            printf(" %04d ", car_space.licence_plate);
        }
    }
    
}

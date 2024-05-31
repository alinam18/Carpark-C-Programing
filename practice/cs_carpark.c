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
#include <string.h> 
#include <limits.h>



// Provided constants
#define CARPARK_ROWS 8
#define CARPARK_COLUMNS 6
#define NORMAL_PARKING_RATE 10
#define EMPTY -1

// Your constants here (i changed lol)
#define TOTAL_CARSPACE 48
#define PREMIUM_PARKING_RATE 50
#define CHARGER -1
#define CABLE_LENGTH 0
#define CARWASH_PRICE 15
#define PREVIOUS_COST 0
#define OCCUPIED_SINCE 0
#define CHARGE_COST 7
// #define CARWASH 2


//I am assigning the the carwash_bay here in term of type 
// #define CARWASH_BAY 2

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
    int normal_parking_rate;
    int premium_parking_rate;
    int charger;
    int cable_length;
    int cable_space;
    int normal_occupied_since;
    int premium_occupied_since;
    int normal_time;
    int premium_time;
    int normal_price;
    int premium_price;
    int total_fee;
    int time_of_move;
    int previous_cost;
    bool carwash_spaces;
    bool currently_charging;
    
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
void discounted (struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS], 
                    double discount);
void find_a_car (struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]);
void parking_car (struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS],
                 int licence_plate_no, int row, int col, int time_of_entry);
void leaving_the_carpark(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]);
void find_car(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS], 
                int licence_plate_no, int time_of_exit, double discount);
void remove_car(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS], 
                int row, int col);
int calculate_price(enum space_type type, int parking_rate, int total_time);

void build_electric_station(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]);
int is_charger(enum space_type type);

void carwash_bays (struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]);
void moving_cars (struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]);
bool carwash_space_available ( struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS],
                                 int row, int col);
bool surrounding_is_carwash (struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS],   
                                int row, int col);
bool if_all_carpark_is_carwash (struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS], 
                        int row, int col);
void carwash_function(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS],
              int licence_plate_no, int row, int col, int time_of_entry);

void charge_car(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]);
int calculate_distance(int row, int col, 
                        struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]);
bool cable_length (struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS],
                    int car_row, int car_col);
double distance_of_two (int row_1, int col_1, int row_2, int col_2);
void (calculate_price_of_one (struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS],
     int row, int col, int licence_plate_no, 
     int time_of_exit, int total_time, int total_price, double discount));

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

            
            // 'l'Operation
        } else if (command == 'l') {
            leaving_the_carpark(carpark);
            printf("\n");
            printf("Enter a command: ");

            //'e' Operation

        } else if (command == 'e') {
            build_electric_station (carpark);
            printf("\n");
            printf("Enter a command: ");

            //'c' Operation
        } else if (command == 'c') {

            charge_car(carpark);

            printf("\n");
            printf("Enter a command: ");

            //'w' Operation
            
        } else if (command == 'w') {

            carwash_bays(carpark);
            printf("\n");
            printf("Enter a command: ");

            //'m' Operation
        } else if (command == 'm') {
            moving_cars(carpark);
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

//'w' Operation


void carwash_bays (struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]){
    int build_time;
    int row = 0;
    int col = 0;
    bool checking_spaces_around = false;

    scanf(" %d %d %d", &row, &col, &build_time);

    if (row >= 0 && row < CARPARK_ROWS) {
        if (col >= 0 && col < CARPARK_COLUMNS) {

            if (((row == 0 || carpark[row - 1][col].licence_plate == EMPTY) ||
            (row == 0 || carpark[row - 1][col].type == CARWASH_BAY)) &&
            ((row == CARPARK_ROWS - 1 || carpark[row + 1][col].licence_plate == EMPTY) || 
            (row == CARPARK_ROWS - 1 || carpark[row + 1][col].type == CARWASH_BAY)) &&
            ((col == 0 || carpark[row][col - 1].licence_plate == EMPTY) || 
            (col == 0 || carpark[row][col - 1].type == CARWASH_BAY)) &&
            ((col == CARPARK_COLUMNS - 1 || 
            carpark[row][col + 1].licence_plate == EMPTY) ||
            (col == CARPARK_COLUMNS - 1 || carpark[row][col + 1].type == CARWASH_BAY))) {

                checking_spaces_around = true;
            } 
            
            if (checking_spaces_around) {
                carpark[row][col].type = CARWASH_BAY;
                printf("Carwash bay has been built on space (%d, %d) at time %d.",
                         row, col, build_time);
                carwash_space_available(carpark, row, col);


            } else {
                printf("This carwash bay cannot be built as one or more of the ");
                printf("surrounding spaces are currently occupied.");
            }
        }
    }
}


bool carwash_space_available (struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS],
                                 int row, int col) {
    
    carpark[row][col].carwash_spaces = true;

    if ((row + 1) < CARPARK_ROWS) {
        carpark[row + 1][col].carwash_spaces = true;

    }
    if (((row + 1) < CARPARK_ROWS )&& ((col + 1) < CARPARK_COLUMNS)) {
        carpark[row + 1][col + 1].carwash_spaces = true;

    }
    if (((row + 1) < CARPARK_ROWS) && ((col - 1) >= 0 )) {
        carpark[row + 1][col - 1].carwash_spaces = true;
    }

    if (((col + 1) < CARPARK_COLUMNS)) {
        carpark[row][col + 1].carwash_spaces = true;
    }
    
    if ((col - 1) >= 0 ) {
        carpark[row][col - 1].carwash_spaces = true;
    }

    if (((row - 1) >= 0 )) {
        carpark[row - 1][col].carwash_spaces = true;
    }

    if (((col - 1) >= 0 ) && ((row - 1) >= 0 )) {
        carpark[row - 1][col - 1].carwash_spaces = true;
    }

    for (int inner_row = 0; inner_row < CARPARK_ROWS; inner_row++) {
        for (int inner_col = 0; inner_col < CARPARK_COLUMNS; inner_col++) {
            if (carpark[inner_row][inner_col].type == CARWASH_BAY 
                && !carpark[inner_row][inner_col].carwash_spaces) {

                // Car wash space available
                return true;  
            }
        }
    }
    // No car wash space available
    return false; 
}

bool surrounding_is_carwash(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS],
                             int row, int col) {
                                
    if (row > 0 && carpark[row - 1][col].type == CARWASH_BAY) {
        return true;
    }
    if (col > 0 && carpark[row][col - 1].type == CARWASH_BAY) {
        return true;
    }
    if (row < CARPARK_ROWS - 1 && carpark[row + 1][col].type == CARWASH_BAY) {
        return true;
    }
    if (col < CARPARK_COLUMNS - 1 && carpark[row][col + 1].type == CARWASH_BAY) {
        return true;
    }

    return false;
}


bool if_all_carpark_is_carwash (struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS],
                                 int row, int col) {
    for (int inner_row = 0; inner_row < CARPARK_ROWS; inner_row++) {
        for (int inner_col = 0; inner_col < CARPARK_COLUMNS; inner_col++) {
            if (surrounding_is_carwash(carpark, row, col))
            return false;
        }
    }
    return true;
         
}



//'m' Operation

void moving_cars (struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]){
    int licence;
    int new_row = 0;
    int new_col = 0;
    int time_of_move = 0;

    scanf(" %4d %d %d %d", &licence, &new_row, &new_col, &time_of_move);

    if (new_row < 0 || new_row >= CARPARK_ROWS || new_col < 0 || new_col >= CARPARK_COLUMNS) {
        printf("Car %4d cannot be moved to an invalid car space.", licence);
        return;
    }

    if (carpark[new_row][new_col].type == ELECTRIC_CHARGING_STATION) {
        printf("Car %4d cannot be moved to an electric charging station.\n", licence);
        return;
    }

    if (carpark[new_row][new_col].licence_plate == EMPTY &&
        carpark[new_row][new_col].type != ELECTRIC_CHARGING_STATION) {


        // //defining
        carpark[new_row][new_col].occupied_since = time_of_move;
        carpark[new_row][new_col].time_of_move = time_of_move;


        for (int row = 0; row < CARPARK_ROWS; row++) {
            for (int col = 0; col < CARPARK_COLUMNS; col++) {
                if (carpark[row][col].licence_plate == licence) {
                    if ((time_of_move <= carpark[row][col].occupied_since)||
                    (time_of_move <= (carpark[row][col].normal_occupied_since + carpark[row][col].premium_occupied_since))) {
                        printf("The move time provided is invalid.");
                        return;
                    }

                    if (carpark[row][col].type == NORMAL) {
                        carpark[row][col].previous_cost = (time_of_move * carpark[row][col].normal_parking_rate);
                        carpark[new_row][new_col].previous_cost = carpark[row][col].previous_cost;

                    } else if (carpark[row][col].type == PREMIUM) {
                        carpark[row][col].previous_cost = (time_of_move * carpark[row][col].premium_parking_rate);
                        carpark[new_row][new_col].previous_cost = carpark[row][col].previous_cost;
                    }

                    if (carpark[new_row][new_col].type == NORMAL) {
                        carpark[new_row][new_col].licence_plate = licence;
                    } else if (carpark[new_row][new_col].type == PREMIUM) {
                        carpark[new_row][new_col].licence_plate = licence;
                    } else if (carpark[new_row][new_col].type == CARWASH_BAY) {
                        carpark[new_row][new_col].licence_plate = licence;
                    }



                    if (surrounding_is_carwash(carpark, new_row, new_col) && carpark[new_row][new_col].type != CARWASH_BAY) {
                        if (!carwash_space_available(carpark, new_row, new_col)) {
                            printf("Cannot park next to a carwash bay. There are still other spaces available in the carpark.");
                            return;
                        } else if (carwash_space_available(carpark, new_row, new_col)) {
                            printf("This carwash bay cannot be used as one or more of the surrounding spaces are currently occupied.\n");
                            return;

                        }
                    }  
                        
                    if (carpark[new_row][new_col].type == CARWASH_BAY ) {
                        // if (if_all_carpark_is_carwash(carpark, new_row, new_col) && carpark[new_row][new_col].licence_plate == EMPTY){
                        if (if_all_carpark_is_carwash(carpark, new_row, new_col)) {
                            printf("Car %4d is now using the carwash bay located at (%d, %d).", licence, new_row, new_col);
                            remove_car(carpark, row, col);
                            return;
                        } else {    
                            printf("This carwash bay cannot be used as one or more of the surrounding spaces are currently occupied.");
                            remove_car(carpark, new_row, new_col);
                            return;
                        }
                    

                    printf("Car %4d has been moved to space (%d, %d).", licence, new_row, new_col);
                    remove_car(carpark, row, col);
                    return;
                    }
             
                }
            }
        }

        printf("No car with licence plate number %4d could be found.", licence);


    } else {
        printf("Car %4d could not be moved to space (%d, %d) as car %4d is already parked there.",
               licence, new_row, new_col, carpark[new_row][new_col].licence_plate);
    }
}
          

// 'p' Operation

void carwash_function(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS],
              int licence_plate_no, int row, int col, int time_of_entry) {
    if ((!if_all_carpark_is_carwash(carpark, row, col)) && 
        (!carwash_space_available(carpark, row, col))) {
        carpark[row][col].licence_plate = licence_plate_no;
        carpark[row][col].occupied_since = time_of_entry;
        printf("Car %4d was added into car space (%d, %d) at time %d!\n",
               licence_plate_no, row, col, time_of_entry);
    } else if (!carwash_space_available(carpark, row, col)) {
        printf("Cannot park next to a carwash bay. There are still ");
        printf("other spaces available in the carpark.\n");
        return;
    } else {
        printf("This carwash bay cannot be used as one or more of the ");
        printf("surrounding spaces are currently occupied.\n");
        return;
    }
}


void parking_car (struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS],
                 int licence_plate_no, int row, int col, int time_of_entry) {
    if (row < CARPARK_ROWS && col < CARPARK_COLUMNS) {

        if (carpark[row][col].licence_plate == EMPTY &&
         (carpark[row][col].type != ELECTRIC_CHARGING_STATION) && 
         (carpark[row][col].type != CARWASH_BAY) &&
         (!surrounding_is_carwash (carpark, row, col))) {
            carpark[row][col].licence_plate = licence_plate_no;
            carpark[row][col].occupied_since = time_of_entry;
            printf("Car %4d was added into car space (%d, %d) at time %d!\n",
                    licence_plate_no, row, col, time_of_entry);

            if (carpark[row][col].type == NORMAL) {
                carpark[row][col].normal_occupied_since = time_of_entry;

            } else if (carpark[row][col].type == PREMIUM) {
                carpark[row][col].premium_occupied_since = time_of_entry;
            }
        } else if (carpark[row][col].type == ELECTRIC_CHARGING_STATION) {
            printf("Cannot park on a space occupied by an electric charging station.\n");

        } else if (carpark[row][col].type == CARWASH_BAY) {
            carpark[row][col].licence_plate = licence_plate_no;
            carpark[row][col].occupied_since = time_of_entry;
            printf("Car %4d is now using the carwash bay located at (%d, %d).\n", 
                licence_plate_no, row, col);


        } else if (surrounding_is_carwash (carpark, row, col)) {

            if (!if_all_carpark_is_carwash(carpark, row, col && 
                !carwash_space_available(carpark, row, col))) {
                carpark[row][col].licence_plate = licence_plate_no;
                carpark[row][col].occupied_since = time_of_entry;
                printf("Car %4d was added into car space (%d, %d) at time %d!\n", 
                    licence_plate_no, row, col, time_of_entry);
            }
            else if (!carwash_space_available(carpark, row, col)) {
                printf("Cannot park next to a carwash bay. There are still");
                printf(" other spaces available in the carpark.\n");
                return;

            } else {
                printf("This carwash bay cannot be used as one or more of the");
                printf(" surrounding spaces are currently occupied.\n");
                return;
            }
                    
        } else {
            printf("Car space is already occupied! \n");
        }
    } else {
        printf("Invalid car space!\n");
    }

}


//'c' Operation


void charge_car(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]) {
    int licence_plate_no;
    int charge_from;
    int charge_till;

    scanf(" %4d %d %d", &licence_plate_no, &charge_from, &charge_till);

    int charge_row = 0;
    int charge_col = 0;

    int car_row = 0;
    int car_col = 0;

    double min_distance = 99;
    // bool currently_charging = false;


    for (int row = 0; row < CARPARK_ROWS; row++) {
        for (int col = 0; col < CARPARK_COLUMNS; col++) {
            if (carpark[row][col].licence_plate == licence_plate_no) {
                car_row = row;
                car_col = col;
            }   
        }
    }   


    //comparing the arrays and find the min_distance
    for (int row = 0; row < CARPARK_ROWS; row++) {
        for (int col = 0; col < CARPARK_COLUMNS; col++) {
            if (carpark[row][col].type == ELECTRIC_CHARGING_STATION
            && (min_distance > distance_of_two(row, col, car_row, car_col))) {
                min_distance = distance_of_two(row, col, car_row, car_col);
                charge_row = row;
                charge_col = col;
            }
        }
    }


    //caculating the cost
    int charge_time = charge_till - charge_from;
    int charge_cost = (charge_time * CHARGE_COST);

    int cable_length = (carpark[charge_row][charge_col].cable_length);

    if (carpark[car_row][car_col].licence_plate == licence_plate_no) {

        if (min_distance <= cable_length) {
            //can charge

            carpark[car_row][car_col].previous_cost = charge_cost;


            printf("Car %4d is being charged by the charging", licence_plate_no);

            printf(" station located at (%d, %d).", charge_row, charge_col);
        
            carpark[car_row][car_col].currently_charging = charge_time;

        } else {
            //cannot charge
            printf("Too far away to be charged, move closer to a charging ");
            printf("station.");
            return;
        }

    } else {
        // (carpark[car_row][car_col].licence_plate != licence_plate_no) 
        printf("No car with licence plate number %4d could be found.", 
            licence_plate_no);
        return;
    }

}

double distance_of_two (int row_1, int col_1, int row_2, int col_2) {
    //calcualting two object's distance

    double distance = 0;

    if (row_1 >= 0 && col_1 >= 0 ) {
        if (row_2 >= 0 && col_2 >= 0) {
            int row = 0;
            int col = 0;

            row = (pow((row_2 - row_1), 2));

            col = (pow((col_1 - col_2), 2));

            distance = sqrt(col + row);
        }
    } 
    return distance;

}


//'e' Operation

void build_electric_station(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]){
    int build_time, cable_length;
    
    int row = 0;
    int col = 0;

    scanf(" %d %d %d %d", &row, &col, &build_time, &cable_length);

    if (row < CARPARK_ROWS && col < CARPARK_COLUMNS) {
        if (carpark[row][col].licence_plate == EMPTY || 
            carpark[row][col].type == NORMAL || 
            carpark[row][col].type == PREMIUM) {

            carpark[row][col].type = ELECTRIC_CHARGING_STATION;
            carpark[row][col].occupied_since = build_time;
            carpark[row][col].cable_length = cable_length;
            printf("Electric charging station has been built on space ");
            printf("(%d, %d) at time %d with cable length of %d.",
                    row, col, build_time, cable_length);

        }
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

//CALCULATE_PRICE AND FIND_CAR DOES NOT WORK NOW - old ver in stage3draft

void find_car(struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS],
                int licence_plate_no, int time_of_exit, double discount) {
    for (int row = 0; row < CARPARK_ROWS; row++) {
        for (int col = 0; col < CARPARK_COLUMNS; col++) {
            if (carpark[row][col].licence_plate == licence_plate_no) {

                int total_time = 0;
                int total_price = 0;
                int difference_time = 0;
                int normal_price;
                int premium_price;

                if (carpark[row][col].total_fee != EMPTY) {
                    total_price += carpark[row][col].total_fee;
                }
                //THE TIME

                if (carpark[row][col].previous_cost == PREVIOUS_COST) {
                    total_time = time_of_exit - carpark[row][col].occupied_since;
                } else {
                    difference_time = time_of_exit - carpark[row][col].occupied_since;
                    total_time = time_of_exit;
                }

                //THE PRICES
                if (carpark[row][col].type != CARWASH_BAY){
                    if (carpark[row][col].type == NORMAL) {
                        int normal_parking_rate = carpark[row][col].normal_parking_rate;
                        if (difference_time != 0) {
                            normal_price = normal_parking_rate * difference_time;
                        } else {
                            normal_price = normal_parking_rate * total_time;
                        }
                        total_price = carpark[row][col].previous_cost + normal_price;


                    } else if (carpark[row][col].type == PREMIUM) {
                        int premium_parking_rate = carpark[row][col].premium_parking_rate;
                        
                        if (difference_time != 0) {
                            premium_price = premium_parking_rate * difference_time;
                        } else {
                            premium_price = premium_parking_rate * total_time;
                        }
                        total_price = carpark[row][col].previous_cost + premium_price;

                    }
                } else if (carpark[row][col].type == CARWASH_BAY) {

                    total_price = carpark[row][col].previous_cost + CARWASH_PRICE;


                } else {
                    total_price = 0; 
                } 

                if (discount) {
                    normal_discount(carpark);
                    premium_discount(carpark);
                }

                if (total_time <= 0 || (total_time > time_of_exit)) {
                    printf("The time of exit provided is invalid.");

                    return; 
                }

                remove_car(carpark, row, col);

                printf("Car %4d was parked for %d hours.", licence_plate_no, total_time);
                printf(" The total price for this duration is $%d.", total_price);
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
    carpark[row][col].normal_occupied_since = EMPTY;
    carpark[row][col].premium_occupied_since = EMPTY;


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
            carpark[row][col].licence_plate = CHARGER;
            carpark[row][col].occupied_since = OCCUPIED_SINCE;
            carpark[row][col].normal_occupied_since = EMPTY;
            carpark[row][col].premium_occupied_since = EMPTY;
            carpark[row][col].total_fee = EMPTY;
            carpark[row][col].cable_length = CABLE_LENGTH;
            carpark[row][col].time_of_move = EMPTY;
            carpark[row][col].previous_cost = PREVIOUS_COST;
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



              
//z5416104 ALina Cui

// have not done m 

//find_car have not done
/*
void moving_cars (struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]){
    int licence;
    int new_row = 0;
    int new_col = 0;
    int time_of_move = 0;

    scanf(" %4d %d %d %d", &licence, &new_row, &new_col, &time_of_move);

    if (new_row < 0 || new_row >= CARPARK_ROWS 
        || new_col < 0 || new_col >= CARPARK_COLUMNS) {
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

        if (car_found(carpark,intintint)) {
            car_found(carpark,intintint)
            return;

        } else {
            printf("No car with licence plate number %4d could be found.", licence);


    } else {
        printf("Car %4d could not be moved to space (%d, %d) as car %4d is ",
               licence, new_row, new_col, carpark[new_row][new_col].licence_plate);
        printf("already parked there.");
    }
}

void car_found (struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS], int new_row, int new_col, int licence, int time_of_move) {
    for (int row = 0; row < CARPARK_ROWS; row++) {
        for (int col = 0; col < CARPARK_COLUMNS; col++) {
            if (carpark[row][col].licence_plate == licence) {
                if ((time_of_move <= carpark[row][col].occupied_since)||
                (time_of_move <= (carpark[row][col].normal_occupied_since 
                            + carpark[row][col].premium_occupied_since))) {
                    printf("The move time provided is invalid.");
                    return;
                }

                if (carpark[row][col].type == NORMAL) {
                    carpark[row][col].previous_cost = 
                    (time_of_move * carpark[row][col].normal_parking_rate);
                    int new_previous_cost = carpark[row][col].previous_cost;
                    carpark[new_row][new_col].previous_cost = new_previous_cost;

                } else if (carpark[row][col].type == PREMIUM) {
                    carpark[row][col].previous_cost =   
                    (time_of_move * carpark[row][col].premium_parking_rate);
                    int new_previous_cost = carpark[row][col].previous_cost;
                    carpark[new_row][new_col].previous_cost = new_previous_cost;
                }

                if (carpark[new_row][new_col].type == NORMAL) {
                    carpark[new_row][new_col].licence_plate = licence;
                } else if (carpark[new_row][new_col].type == PREMIUM) {
                    carpark[new_row][new_col].licence_plate = licence;
                } else if (carpark[new_row][new_col].type == CARWASH_BAY) {
                    carpark[new_row][new_col].licence_plate = licence;
                }



                if (surrounding_is_carwash(carpark, new_row, new_col)
                    && carpark[new_row][new_col].type != CARWASH_BAY) {
                    if (!carwash_space_available(carpark, new_row, new_col)) {
                        printf("Cannot park next to a carwash bay. There are ");
                        printf("still other spaces available in the carpark.");
                        return;
                    } else if (carwash_space_available(carpark, new_row, new_col)) {
                        printf("This carwash bay cannot be used as one or more of ");
                        printf("the surrounding spaces are currently occupied.\n");
                        return;

                    }
                }  
                    
                if (carpark[new_row][new_col].type == CARWASH_BAY ) {
                    if (if_all_carpark_is_carwash(carpark, new_row, new_col)) {
                        printf("Car %4d is now using the carwash bay located at "
                        , licence);
                        printf("(%d, %d).", new_row, new_col);
                        remove_car(carpark, row, col);
                        return;
                    } else {    
                        printf("This carwash bay cannot be used as one or more of");
                        printf(" the surrounding spaces are currently occupied.");
                        remove_car(carpark, new_row, new_col);
                        return;
                    }
                

                printf("Car %4d has been moved to space (%d, %d).",
                    licence, new_row, new_col);
                remove_car(carpark, row, col);
                return;
                }
            
            }
        }
    }
}*/



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
                if (carpark[row][col].type != CARWASH_BAY) {
                    normal_or_premium(carpark, row, col, difference_time,
                     normal_price, premium_prices, total_time);

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

void normal_prices (struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS],
    int row, int col, int difference_time, int normal_price, int total_time) {
    int normal_parking_rate = carpark[row][col].normal_parking_rate;
    if (difference_time != 0) {
        normal_price = normal_parking_rate * difference_time;
    } else {
        normal_price = normal_parking_rate * total_time;
    }
    total_price = carpark[row][col].previous_cost + normal_price;
}

void premium_prices (struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS],
    int row, int col, int difference_time, int premium_price, int total_time) {
    int premium_parking_rate = carpark[row][col].premium_parking_rate;
    
    if (difference_time != 0) {
        premium_price = premium_parking_rate * difference_time;
    } else {
        premium_price = premium_parking_rate * total_time;
    }
    total_price = carpark[row][col].previous_cost + premium_price;

}

void normal_or_premium (struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS], 
    int row, int col, int difference_time, int normal_price,
    int premium_prices, int total_time){

    if (carpark[row][col].type == NORMAL) {
        normal_prices(carpark, row, col, difference_time, normal_price, total_time );

    } else if (carpark[row][col].type == PREMIUM) {
        premium_prices(carpark, row, col, difference_time, premium_price, total_time);
    
    }
}
void conditions (struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS], )

/*
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
}*/

void moving_cars (struct car_space carpark[CARPARK_ROWS][CARPARK_COLUMNS]) {
    int licence;
    int new_row = 0;
    int new_col = 0;
    int time_of_move = 0;

    scanf(" %4d %d %d %d", &licence, &new_row, &new_col, &time_of_move);

    if (new_row < 0 || new_row >= CARPARK_ROWS 
        || new_col < 0 || new_col >= CARPARK_COLUMNS) {
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
                    if ((time_of_move <= carpark[row][col].occupied_since) ||
                    (time_of_move <= (carpark[row][col].normal_occupied_since 
                                + carpark[row][col].premium_occupied_since))) {
                        printf("The move time provided is invalid.");
                        return;
                    }

                    if (carpark[row][col].type == NORMAL) {
                        carpark[row][col].previous_cost = 
                        (time_of_move * carpark[row][col].normal_parking_rate);
                        int new_previous_cost = carpark[row][col].previous_cost;
                        carpark[new_row][new_col].previous_cost = new_previous_cost;

                    } else if (carpark[row][col].type == PREMIUM) {
                        carpark[row][col].previous_cost =   
                        (time_of_move * carpark[row][col].premium_parking_rate);
                        int new_previous_cost = carpark[row][col].previous_cost;
                        carpark[new_row][new_col].previous_cost = new_previous_cost;
                    }

                    if (carpark[new_row][new_col].type == NORMAL) {
                        carpark[new_row][new_col].licence_plate = licence;
                    } else if (carpark[new_row][new_col].type == PREMIUM) {
                        carpark[new_row][new_col].licence_plate = licence;
                    } else if (carpark[new_row][new_col].type == CARWASH_BAY) {
                        carpark[new_row][new_col].licence_plate = licence;
                    }



                    if (surrounding_is_carwash(carpark, new_row, new_col)
                     && carpark[new_row][new_col].type != CARWASH_BAY) {
                        if (!carwash_space_available(carpark, new_row, new_col)) {
                            printf("Cannot park next to a carwash bay. There are ");
                            printf("still other spaces available in the carpark.");
                            return;
                        } else if (carwash_space_available(carpark, new_row, new_col)) {
                            printf("This carwash bay cannot be used as one or more of ");
                            printf("the surrounding spaces are currently occupied.\n");
                            return;

                        }
                    }  
                        
                    if (carpark[new_row][new_col].type == CARWASH_BAY ) {
                        if (if_all_carpark_is_carwash(carpark, new_row, new_col)) {
                            printf("Car %4d is now using the carwash bay located at "
                            , licence);
                            printf("(%d, %d).", new_row, new_col);
                            remove_car(carpark, row, col);
                            return;
                        } else {    
                            printf("This carwash bay cannot be used as one or more of");
                            printf(" the surrounding spaces are currently occupied.");
                            remove_car(carpark, new_row, new_col);
                            return;
                        }
                    

                        printf("Car %4d has been moved to space (%d, %d).",
                            licence, new_row, new_col);
                        remove_car(carpark, row, col);
                        return;
                    }
             
                }
            }
        }

        printf("No car with licence plate number %4d could be found.", licence);


    } else {
        printf("Car %4d could not be moved to space (%d, %d) as car %4d is ",
               licence, new_row, new_col, carpark[new_row][new_col].licence_plate);
        printf("already parked there.");
    }
}
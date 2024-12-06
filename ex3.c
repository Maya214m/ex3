/******************
Name:Maya Mattar
ID:213510407
Assignment: ex3
*******************/

#include <stdio.h>

// Definitions
#define NUM_OF_BRANDS 5
#define BRANDS_NAMES 15
#define NUM_OF_TYPES 4
#define TYPES_NAMES 10
#define DAYS_IN_YEAR 365

// Menu Options
#define addOne  1
#define addAll  2  
#define stats  3
#define print  4
#define insights  5
#define deltas  6
#define done  7

// Brand and Type Names
char brands[NUM_OF_BRANDS][BRANDS_NAMES] = {"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};
char types[NUM_OF_TYPES][TYPES_NAMES] = {"SUV", "Sedan", "Coupe", "GT"};

// Function Definitions
void printMenu(){
    printf("Welcome to the Cars Data Cube! What would you like to do?\n"
           "1.Enter Daily Data For A Brand\n"
           "2.Populate A Day Of Sales For All Brands\n"
           "3.Provide Daily Stats\n"
           "4.Print All Data\n"
           "5.Provide Overall (simple) Insights\n"
           "6.Provide Average Delta Metrics\n"
           "7.exit\n");
}
// Functions Prototypes
void enterDailyDataForBrands(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int days[NUM_OF_BRANDS]);
void populateDayOfSales(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int days[NUM_OF_BRANDS], int *currentDay);
void provideDailyStats(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int currentDay);
void printAllData(int cube[DAYS_IN_YEARS][NUM_OF_BRANDS][NUM_OF_TYPES], int days[NUM_OF_BRANDS]);
void provideOverallInsights(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int days[NUM_OF_BRANDS]);
void provideAverageDeltaMetrics(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int days[NUM_OF_BRANDS]);

// Main Function
int main() {
    // A 3D array to store sales data
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES] = {{{-1}}};
    int days[NUM_OF_BRANDS] = {0};
    int currentDay = 0; // Tracks the overall current day
    int choice;
    printMenu();
    scanf("%d", &choice);
    // Menu Loop: Continue until the user enters 7 to exit 
    while(choice != done){
        switch(choice){
            case addOne: // Enter data for a single brand
                enterDailyDataForBrand(cube, days);
                break;
            case addAll: // Populate data for all brands in a single day
                populateDayOfSales(cube, days, &currenetDay);
                break;
            case stats: // Provide daily statistics
                 provideDailyStats(cube, currenetDay);
                 break;
            case print: // Print all stored data
                 printAllData(cube, days);
                 break;
            case insights: // Provide overall insights
                 provideOverallInsights(cube, days);
                 break;
            case deltas: // Calculate and display average delta metrics
                 provideAverageDeltaMetrics(cube, days);
                 break;
              
            default:
                printf("Invalid input\n");
        }
        printMenu();
        scanf("%d", &choice);
    }
    printf("Goodbye!\n");
    return 0;
}



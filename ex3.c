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
void enterDailyDataForBrand(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int days[NUM_OF_BRANDS]);
void populateDayOfSales(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int days[NUM_OF_BRANDS], int *currentDay);
void provideDailyStats(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int currentDay);
void printAllData(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int days[NUM_OF_BRANDS]);
void provideOverallInsights(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int days[NUM_OF_BRANDS]);
void provideAverageDeltaMetrics(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int days[NUM_OF_BRANDS]);


// Main Function
int main() {
  // A 3D array to store sales data
  int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES] = {{{-1}}};
  int days[NUM_OF_BRANDS] = {0};
  int currentDay = 0; // Tracks the overall current day
  int choice;
  while (1) {
  // Print the menu initially
  printMenu();
  scanf("%d", &choice);
    // Process the choice
    switch(choice){
      case addOne: // Enter data for a single brand
        enterDailyDataForBrand(cube, days);
      break;
      case addAll: // Populate data for all brands in a single day
        populateDayOfSales(cube, days, &currentDay);
      break;
      case stats: // Provide daily statistics
        provideDailyStats(cube, currentDay);
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
      case done:
        printf("Goodbye!\n");
        return 0;
      break;
      default:
        printf("Invalid input\n");
    }
  }
}
    // Function Definitions

    // enterDailyDataForBrand function
    void enterDailyDataForBrand(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int days[NUM_OF_BRANDS]) {
        int brandIndex, sales[NUM_OF_TYPES];

        // Input brand index and sales data for SUV, Sedan, Coupe, GT
        scanf("%d %d %d %d %d", &brandIndex, &sales[0], &sales[1], &sales[2], &sales[3]);

        // Validate the brand index
        if (brandIndex < 0 || brandIndex >= NUM_OF_BRANDS) {
            printf("This brand is not valid\n");
            return;
        }

        // Insert sales data into the cube for the next availabe day
        int currentDay = days[brandIndex];
        for (int i = 0; i < NUM_OF_TYPES; i++) {
            cube[currentDay][brandIndex][i] = sales[i];
        }
        // Update the day tracker for the brand
        days[brandIndex]++;
    }
    // populateDayOfSales function, to populate sales data for all brands in a single day
    void populateDayOfSales(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int days[NUM_OF_BRANDS], int *currentDay) {
        int completedBrands = 0;

        while (completedBrands < NUM_OF_BRANDS) {
          int missingBrands = 0;

          // Print missing brands
          printf("No data for brands ");
          for (int i = 0; i < NUM_OF_BRANDS; i++) {
            if (days[i] == *currentDay) { // Checks if data for the current day is missing
              printf("%s ", brands[i]);
              missingBrands++;
            }
          }
          // All brands have data for the current day
          if (missingBrands == 0) {
            break;
        }

      printf("\nPlease complete the data\n");

       // Prompt the user to enter data for a missing brand
      enterDailyDataForBrand(cube, days);
          completedBrands++;
      }
      // Increment the overall day counter if all brands are completed
      (*currentDay)++;
    }
    // provideDailyStats function to calculate and display daily stats
    void provideDailyStats(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int currentDay) {
      int day;
      // Ask user to enter a day to analyze
      while (1) {
        printf("What day would you like to analyze?\n");
        scanf("%d", &day);

        // In case the user entered a bad day ask to enter a valid day
        if (day < 0 || day >= currentDay) {
          printf("Please enter a valid day.\n");
        } else {
          break; // Exit the loop once a valid day is entered
        }
      }
      // Calculate statistics for the valid day
      int totalSales = 0, bestBrand = -1, bestBrandSales = 0;
      int bestType = -1, bestTypeSales = 0;
      int brandSales[NUM_OF_BRANDS] = {0};
      int typeSales[NUM_OF_TYPES] = {0};

      // Process sales data for the given day
      for (int brand = 0; brand < NUM_OF_BRANDS; brand++) {
        for (int type = 0; type < NUM_OF_TYPES; type++) {
          int sales = cube[day][brand][type];
          totalSales += sales;
          brandSales[brand] += sales;
          typeSales[type] += sales;
        }
      }

       // Find the best-selling brand and type
       for (int brand = 0; brand < NUM_OF_BRANDS; brand++) {
         if (brandSales[brand] > bestBrandSales) {
           bestBrand = brand;
           bestBrandSales = brandSales[brand];
         }
       }
       for (int type = 0; type < NUM_OF_TYPES; type++) {
         if (typeSales[type] > bestTypeSales) {
           bestType = type;
           bestTypeSales = typeSales[type];
         }
       }

      // Print the results
      printf("In day number %d:\n", day);
      printf("The sales total was %d\n", totalSales);
      printf("The best sold brand with %d sales was %s\n", bestBrandSales, brands[bestBrand]);
      printf("The best sold type with %d sales was %s\n ", bestTypeSales, types[bestType]);
      printf("\n");
      }

    // printAllData function to print the data cube
    void printAllData(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int days[NUM_OF_BRANDS]) {
        printf("*****************************************\n");

        // Loop through all brands
        for (int brand = 0; brand < NUM_OF_BRANDS; brand++) {
          printf("Sales for %s:\n", brands[brand]);

        // Loop through all days up to the latest day for this brand
        for (int day = 0; day < days[brand]; day++) {
          printf("Day %d -", day + 1);

          // Print sales for each type of car
          for (int type = 0; type < NUM_OF_TYPES; type++) {
            printf("%s: %d", types[type], cube[day][brand][type]);
          }
          printf("\n");
        }
         printf("\n");
        }
        printf("*****************************************\n");
    }

    // provideOverallInsights function to calculate overall insights
    void provideOverallInsights(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int days[NUM_OF_BRANDS]) {
    int totalBrandSales[NUM_OF_BRANDS] = {0};
    int totalTypeSales[NUM_OF_TYPES] = {0};
    int totalDaySales[DAYS_IN_YEAR] = {0};

    // Variables to track best brand, type, and day
    int bestBrandIndex = -1, bestBrandSales = 0;
    int bestTypeIndex = -1, bestTypeSales = 0;
    int bestDayIndex = -1, bestDaySales = 0;

    // Calculate total sales for each brand, type, and day
    for (int day = 0; day < DAYS_IN_YEAR; day++) {
      for (int brand = 0; brand < NUM_OF_BRANDS; brand++) {
        for (int type = 0; type < NUM_OF_TYPES; type++) {
          int sales = cube[day][brand][type];

          // Add sales to brand, type, and day totals
          totalBrandSales[brand] += sales;
          totalTypeSales[type] += sales;
          totalDaySales[day] += sales;
        }
      }
    }
    for (int brand = 0; brand < NUM_OF_BRANDS; brand++) {
      if (totalBrandSales[brand] > bestBrandSales) {
        bestBrandSales = totalBrandSales[brand];
        bestBrandIndex = brand;
      }
    }
    // Determine the best selling car type
    for (int type = 0; type < NUM_OF_TYPES; type++) {
      if (totalTypeSales[type] > bestTypeSales) {
        bestTypeSales = totalTypeSales[type];
        bestTypeIndex = type;
      }
    }
    // Determine the most profitable day
    for (int day = 0; day < DAYS_IN_YEAR; day++) {
      if (totalDaySales[day] > bestDaySales) {
        bestDaySales = totalDaySales[day];
        bestDayIndex = day;
      }
    }
    // Print the results
    printf("The best-selling brand overall is %s: %d$\n", brands[bestBrandIndex], bestBrandSales);
    printf("The best-selling type of car is %s: %d$\n", types[bestTypeIndex], bestTypeSales);
    printf("The most profitable day was day number %d: %d$\n", bestDayIndex + 1, bestDaySales);
}

    // provideAverageDeltaMetrics function to calculates the average change in sale from one day to next
    void provideAverageDeltaMetrics(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int days[NUM_OF_BRANDS]) {
  // Loop through all brands
  for (int brand = 0; brand < NUM_OF_BRANDS; brand++) {
    int totalDelta = 0;
    int numDays = days[brand];

    // If there is only one day or no data, the delta is 0
    if (numDays < 2) {
      printf("Brand: %s, Average Delta: 0.000000\n", brands[brand]);
      continue;
    }
    // Compute total sales difference between consecutive days
    for (int day = 0; day < numDays; day++) {
      int saleDay1 = 0, saleDay2 = 0;

      // Calculate total sales for the brand in two consecutive days
      for (int type = 0; type < NUM_OF_TYPES; type++) {
        saleDay1 += cube[day - 1][brand][type];
        saleDay2 += cube[day][brand][type];
      }
      totalDelta += (saleDay2 - saleDay1); // Add difference to total delta
    }
    // Calculate average delta
    float averageDelta = (float)totalDelta / (numDays - 1);

    // Print result for this brand
    printf("Brand: %s, Average Delta: %.6f\n", brands[brand], averageDelta);
  }
}

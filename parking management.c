9#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

#define MAX_MOTORCYCLE 50
#define MAX_LIGHT 25
#define MAX_HEAVY 10

float PRICE_MOTO = 30.00;
float PRICE_LIGHT = 50.00;
float PRICE_HEAVY = 80.00;

char vehicleType[][20] = {"Motorcycle", "Light Vehicle", "Heavy Vehicle"};

typedef struct{
    char vehicleNumber[12];
    int vehicleType;
    time_t entryTime;
} vehicle;

int total = MAX_MOTORCYCLE + MAX_HEAVY + MAX_LIGHT;
int numMoto = 0;
int numLight = 0;
int numHeavy = 0;
int index = 0;
vehicle newVehicle[100];

// Function to convert a string to uppercase
void convertToUppercase(char* inputString) {
    int length = strlen(inputString);
    for (int i = 0; i < length; i++) {
        inputString[i] = toupper(inputString[i]);
    }
}

// Convert vehicle number to uppercase
void vehicleNumberConvert() {
    convertToUppercase(newVehicle[index].vehicleNumber);
}

// Function to display successful vehicle entry
void successfulEntry(time_t entryTime) {
    int temp1 = newVehicle[index].vehicleType - 1;
    printf("\nVehicle Entered Successfully!\n");
    printf("Vehicle Number: %s\n", newVehicle[index].vehicleNumber);
    printf("Vehicle Category: %s\n", vehicleType[temp1]);

    // Display the entry time using the correct format specifiers
    struct tm* localTimeInfo = localtime(&entryTime);
    printf("Vehicle Entry Time: %04d-%02d-%02d %02d:%02d:%02d\n",
           localTimeInfo->tm_year + 1900, localTimeInfo->tm_mon + 1, localTimeInfo->tm_mday,
           localTimeInfo->tm_hour, localTimeInfo->tm_min, localTimeInfo->tm_sec);
}

// Function for entering a motorcycle in the parking lot
void enteringMotorcycle() {
    printf("\n\n---------------------------------------------------------------------------\n");
    printf("|                              ENTERING                                   |\n");
    printf("|                           - Motorcycle -                                |\n");
    printf("---------------------------------------------------------------------------\n\n");
    if (numMoto >= MAX_MOTORCYCLE) {
        printf("\nParking lot is full! Cannot accept more motorcycles\n");
        return;
    }
    printf("\nEnter vehicle number:  ");
    scanf("%s", newVehicle[index].vehicleNumber);
    newVehicle[index].vehicleType = 1;
    newVehicle[index].entryTime = time(NULL);
    numMoto++;
    vehicleNumberConvert();
    successfulEntry(newVehicle[index].entryTime);
    index++;
}

// Function for entering a light vehicle in the parking lot
void enteringLightVehicle() {
    printf("\n\n---------------------------------------------------------------------------\n");
    printf("|                              ENTERING                                   |\n");
    printf("|                          - Light Vehicle -                              |\n");
    printf("---------------------------------------------------------------------------\n\n");
    if (numMoto >= MAX_LIGHT) {
        printf("\nParking lot is full! Cannot accept more light vehicles\n");
        return;
    }
    printf("\nEnter vehicle number:  ");
    scanf("%s", newVehicle[index].vehicleNumber);
    newVehicle[index].vehicleType = 2;
    newVehicle[index].entryTime = time(NULL);
    numLight++;
    vehicleNumberConvert();
    successfulEntry(newVehicle[index].entryTime);
    index++;
}

// Function for entering a heavy vehicle in the parking lot
void enteringHeavyVehicle() {
    printf("\n\n---------------------------------------------------------------------------\n");
    printf("|                              ENTERING                                   |\n");
    printf("|                          - Heavy Vehicle -                              |\n");
    printf("---------------------------------------------------------------------------\n\n");
    if (numMoto >= MAX_HEAVY) {
        printf("\nParking lot is full! Cannot accept more heavy vehicles\n");
        return;
    }
    printf("\nEnter vehicle number:  ");
    scanf("%s", newVehicle[index].vehicleNumber);
    newVehicle[index].vehicleType = 3;
    newVehicle[index].entryTime = time(NULL);
    numHeavy++;
    vehicleNumberConvert();
    successfulEntry(newVehicle[index].entryTime);
    index++;
}

// Function to handle entering a vehicle in the parking lot
void enterParkingLot() {
    printf("\n\n---------------------------------------------------------------------------\n");
    printf("\n|                              ENTERING                                   |\n");
    printf("\n---------------------------------------------------------------------------\n\n");
    printf("\nEnter the vehicle type\n");
    printf("1. Motorcycle\n");
    printf("2. Light Vehicle\n");
    printf("3. Heavy Vehicle\n");
    printf("\nEnter your choice: ");
    int vehicleTNum;
    scanf("%d", &vehicleTNum);

    switch (vehicleTNum) {
        case 1:
            enteringMotorcycle();
            break;
        case 2:
            enteringLightVehicle();
            break;
        case 3:
            enteringHeavyVehicle();
            break;
        default:
            printf("\nInvalid choice for the Vehicle Type! Please try again\n");
            enterParkingLot();
    }
}

// Function to remove a vehicle from memory after exiting
void memorySave(int i) {
    for (int j = i; j < index; j++) {
        strcpy(newVehicle[j].vehicleNumber, newVehicle[j + 1].vehicleNumber);
        newVehicle[j].vehicleType = newVehicle[j + 1].vehicleType;
        newVehicle[j].entryTime = newVehicle[j + 1].entryTime;
    }
}

// Function to save exiting vehicle information to a file
void saveExitingInfoToFile(const char* vehicleNumber, const char* vehicleType, int hoursParked, float fee, time_t entryTime, time_t tempTime) {
    FILE* file;

    // Open the file in append mode to add the exiting information at the end
    file = fopen("record.txt", "a");
    if (file == NULL) {
        printf("** Error opening file!\n");
        return;
    }

    // Write the exiting information to the file
    fprintf(file, "Vehicle Number: %s\n", vehicleNumber);
    fprintf(file, "Vehicle Type: %s\n", vehicleType);
    fprintf(file, "No of hours parked: %d\n", hoursParked);
    fprintf(file, "Fee: %.2f\n", fee);

    struct tm* localTimeInfo = localtime(&entryTime);
    fprintf(file, "Vehicle Entry Time: %04d-%02d-%02d %02d:%02d:%02d\n",
            localTimeInfo->tm_year + 1900, localTimeInfo->tm_mon + 1, localTimeInfo->tm_mday,
            localTimeInfo->tm_hour, localTimeInfo->tm_min, localTimeInfo->tm_sec);

    struct tm* localTimeInfo1 = localtime(&tempTime);
    fprintf(file, "Vehicle Exit Time: %04d-%02d-%02d %02d:%02d:%02d\n",
            localTimeInfo1->tm_year + 1900, localTimeInfo1->tm_mon + 1, localTimeInfo1->tm_mday,
            localTimeInfo1->tm_hour, localTimeInfo1->tm_min, localTimeInfo1->tm_sec);
    fprintf(file, "-------------------\n");

    fclose(file);

    printf("**  Exiting vehicle information logged successfully.  **\n");
}

// Function to handle the case when the vehicle is not found in the parking lot
void failedToFind() {
    printf("\nEntered Vehicle is not in the Parking Lot!\n");
    printf("Please try again.\n");
    exitingParkingLot();
}

// Function to display exiting vehicle information
void exitingDisplay(float fee, int i, int d) {
    int temp = newVehicle[i].vehicleType - 1;
    int tempTime = time(NULL);

    printf("\n\n                    Vehicle Exited Successfully!\n");
    printf("---------------------------------------------------------------------------\n\n");
    printf("Vehicle Number: %s\n", newVehicle[i].vehicleNumber);
    printf("Vehicle Type: %s\n", vehicleType[temp]);
    printf("No of hours parked : %d\n", d);
    struct tm* localTimeInfo = localtime(&newVehicle[i].entryTime);
    printf("Vehicle Entry Time: %04d-%02d-%02d %02d:%02d:%02d\n",
           localTimeInfo->tm_year + 1900, localTimeInfo->tm_mon + 1, localTimeInfo->tm_mday,
           localTimeInfo->tm_hour, localTimeInfo->tm_min, localTimeInfo->tm_sec);
    printf("Fee %.2f\n", fee);
    printf("---------------------------------------------------------------------------\n");

    saveExitingInfoToFile(newVehicle[i].vehicleNumber, vehicleType[temp], d, fee, newVehicle[i].entryTime, tempTime);
}

// Function to calculate the parking duration in hours
int difference(int entryTime) {
    int diff = time(NULL) - entryTime;
    diff = diff / 3600;
    for (int i = 0; i < 25; i++) {
        if (diff < i) {
            diff = i;
            break;
        }
    }
    return diff;
}

// Function to handle exiting a motorcycle from the parking lot
void exitingMotorcycle() {
    printf("\n\n---------------------------------------------------------------------------\n");
    printf("|                              EXITING                                    |\n");
    printf("|                           - Motorcycle -                                |\n");
    printf("---------------------------------------------------------------------------\n\n");
    char temp3[12];
    printf("Enter vehicle number:  ");
    scanf("%s", temp3);
    convertToUppercase(temp3);

    float fee;
    int d, i, flag;
    for (i = 0; i < index; i++) {
        if (strcmp(temp3, newVehicle[i].vehicleNumber) == 0) {
            d = difference(newVehicle[i].entryTime);
            fee = d * PRICE_MOTO;
            flag = 1;
            exitingDisplay(fee, i, d);
            break;
        }
    }

    if (flag == 0) {
        failedToFind();
    }
    numMoto--;
    memorySave(i);
}

// Function to handle exiting a light vehicle from the parking lot
void exitingLightVehicle() {
    printf("\n\n---------------------------------------------------------------------------\n");
    printf("|                              EXITING                                    |\n");
    printf("|                         - Light Vehicle -                               |\n");
    printf("---------------------------------------------------------------------------\n\n");
    char temp3[12];
    printf("Enter vehicle number:  ");
    scanf("%s", temp3);
    convertToUppercase(temp3);

    float fee;
    int d, i, flag;
    for (i = 0; i < index; i++) {
        if (strcmp(temp3, newVehicle[i].vehicleNumber) == 0) {
            d = difference(newVehicle[i].entryTime);
            fee = d * PRICE_LIGHT;
            flag = 1;
            exitingDisplay(fee, i, d);
            break;
        }
    }

    if (flag == 0) {
        failedToFind();
    }
    numLight--;
    memorySave(i);
}

// Function to handle exiting a heavy vehicle from the parking lot
void exitinggHeavyVehicle() {
    printf("\n\n---------------------------------------------------------------------------\n");
    printf("|                              EXITING                                    |\n");
    printf("|                         - Heavy Vehicle -                               |\n");
    printf("---------------------------------------------------------------------------\n\n");
    char temp3[12];
    printf("Enter vehicle number:  ");
    scanf("%s", temp3);
    convertToUppercase(temp3);

    float fee;
    int d, i, flag;
    for (i = 0; i < index; i++) {
        if (strcmp(temp3, newVehicle[i].vehicleNumber) == 0) {
            d = difference(newVehicle[i].entryTime);
            fee = d * PRICE_HEAVY;
            flag = 1;
            exitingDisplay(fee, i, d);
            break;
        }
    }

    if (flag == 0) {
        failedToFind();
    }
    numHeavy--;
    memorySave(i);
}

// Function to handle exiting a vehicle from the parking lot
void exitingParkingLot() {
    printf("\n\n---------------------------------------------------------------------------\n");
    printf("\n|                              EXITING                                    |\n");
    printf("\n---------------------------------------------------------------------------\n\n");
    printf("\nEnter the vehicle type\n");
    printf("1. Motorcycle\n");
    printf("2. Light Vehicle\n");
    printf("3. Heavy Vehicle\n");
    printf("\nEnter your choice: ");
    int vehicleTNum;
    scanf("%d", &vehicleTNum);

    switch (vehicleTNum) {
        case 1:
            exitingMotorcycle();
            break;
        case 2:
            exitingLightVehicle();
            break;
        case 3:
            exitinggHeavyVehicle();
            break;
        default:
            printf("\nInvalid choice for the Vehicle Type! Please try again\n");
            exitingParkingLot();
    }
}

// Function to display vehicle information
void vehicleInfo() {
    printf("\n\n---------------------------------------------------------------------------\n");
    printf("|                      PARKING LOT INFORMATION                            |\n");
    printf("|                     - Parked Vehicle Details -                          |\n");
    printf("---------------------------------------------------------------------------\n\n\n");
    for (int i = 0; i < index; i++) {
        int temp = newVehicle[i].vehicleType - 1;
        printf("\nVehicle Number : %s\n", newVehicle[i].vehicleNumber);
        printf("Vehicle Type : %s\n", vehicleType[temp]);
        struct tm* localTimeInfo = localtime(&newVehicle[i].entryTime);
        printf("Vehicle Entry Time: %04d-%02d-%02d %02d:%02d:%02d\n",
               localTimeInfo->tm_year + 1900, localTimeInfo->tm_mon + 1, localTimeInfo->tm_mday,
               localTimeInfo->tm_hour, localTimeInfo->tm_min, localTimeInfo->tm_sec);
        printf("\n--------------------------------------------\n");
    }
        printf("\n\n-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n\n\n");

}

// Function to display parking availability
void availability() {
    printf("\n\n---------------------------------------------------------------------------\n");
    printf("|                      PARKING LOT INFORMATION                            |\n");
    printf("|                   - Parking Space Availability -                        |\n");
    printf("---------------------------------------------------------------------------\n\n\n");
    printf("Number of Motorcycle spaces left: %d \n", MAX_MOTORCYCLE - numMoto);
    printf("Number of Light Vehicle spaces left: %d \n", MAX_LIGHT - numLight);
    printf("Number of Heavy Vehicle spaces left: %d \n", MAX_HEAVY - numHeavy);
    printf("\n\n-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n\n\n");
}

// Function to display parking statistics
void statistics() {
    printf("\n\n---------------------------------------------------------------------------\n");
    printf("\n|                      PARKING LOT INFORMATION                            |\n");
    printf("\n---------------------------------------------------------------------------\n\n\n");
    printf("1. Parking Availability\n");
    printf("2. Parked Vehicle Information\n");
    printf("3. Go to main menu\n");
    printf("\nEnter your choice: ");
    int choice;
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            availability();
            break;
        case 2:
            vehicleInfo();
            break;
        case 3:
            main();
            break;
        default:
            printf("\nYour input is invalid! Please try again");
            statistics();
            break;
    }
}

// Function to change the parking fees
void feeChange() {
    int temp, choice;
    srand(time(0));
    int random_number = rand() % 1000000;
    printf("Please enter the following number to confirm changes \n%d\n", random_number);
    scanf("%d", &temp);

    if (temp == random_number) {
        printf("\n\n---------------------------------------------------------------------------\n");
        printf("\n|                              Fee Change Menu                            |\n");
        printf("\n---------------------------------------------------------------------------\n\n\n");
        printf("1. Motorcycle Fee Change\n");
        printf("2. Light Vehicle Fee Change\n");
        printf("3. Heavy Vehicle Fee Change\n ");
        printf("\nEnter Your choice : ");
        scanf("%d", &choice);

        float temp2;
        switch (choice) {
            case 1:
                printf("\nEnter the new fee for Motorcycles\n");
                scanf("%f", &temp2);
                printf("\nFees for motorcycles are changed from %.2f to %.2f\n", PRICE_MOTO, temp2);
                PRICE_MOTO = temp2;
                break;
            case 2:
                printf("\nEnter the new fee for Light Vehicles\n");
                scanf("%f", &temp2);
                printf("\nFees for light vehicles are changed from %.2f to %.2f\n", PRICE_LIGHT, temp2);
                PRICE_LIGHT = temp2;
                break;
            case 3:
                printf("\nEnter the new fee for Heavy Vehicles\n");
                scanf("%f", &temp2);
                printf("\nFees for heavy vehicles are changed from %.2f to %.2f\n", PRICE_HEAVY, temp2);
                PRICE_HEAVY = temp2;
                break;
            default:
                printf("\nInvalid Input! Please try again.\n");
                feeChange();
        }
    } else {
        printf("\nNumber you entered is not correct! Please try again\n");
        feeChange();
    }
}

// Function to display the main menu of the application
void displayMenu() {
    printf("\n\n---------------------------------------------------------------------------\n");
    printf("\n|                      PARKING MANAGEMENT SYSTEM                          |\n");
    printf("\n---------------------------------------------------------------------------\n\n\n");
    printf("1. Enter Parking Lot\n");
    printf("2. Exit Parking Lot\n");
    printf("3. Parking Lot Information\n");
    printf("98. Change Fees\n");
    printf("99. Exit Application\n");
    printf("\nEnter your choice: ");
}

// Main function to run the parking management application
int main() {
    int choice;
    do {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                enterParkingLot();
                break;
            case 2:
                exitingParkingLot();
                break;
            case 3:
                statistics();
                break;
            case 98:
                feeChange();
                break;
            case 99:
                break;
            default:
                printf("\nInvalid Input! Try Again...\n");
                main();
        }
    } while (choice != 99);

    return 0;
}

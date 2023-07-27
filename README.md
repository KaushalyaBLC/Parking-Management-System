# Parking Management System

The Parking Management System is a sophisticated command-line utility implemented in C, designed to efficiently manage a parking lot. This system provides a seamless experience for users to enter and exit vehicles from the parking lot, view parking lot information, and easily change parking fees for various vehicle types.

## Purpose

The purpose of this utility is to streamline the parking management process for small to medium-sized parking facilities. It offers a user-friendly interface and accurate tracking of vehicles entering and exiting the parking lot, ensuring optimal utilization of parking spaces and efficient fee calculation.

## Usage Instructions

1. Clone the repository or download the source code.
2. Compile the C program using a C compiler (e.g., gcc).
3. Run the compiled executable to initiate the Parking Management System.

Upon execution, the program presents a well-organized main menu with several options:

```
---------------------------------------------------------------------------
|                      PARKING MANAGEMENT SYSTEM                          |
---------------------------------------------------------------------------

1. Enter Parking Lot
2. Exit Parking Lot
3. Parking Lot Information
98. Change Fees
99. Exit Application

Enter your choice:
```

To interact with the system, simply follow the intuitive instructions and input the corresponding numbers for the actions you wish to perform.

### Enter Parking Lot
Select option 1 to register a vehicle's entry into the parking lot. You will be prompted to specify the vehicle type (Motorcycle, Light Vehicle, or Heavy Vehicle) and enter the vehicle number. The system seamlessly records the entry, updates parking availability, and provides a successful entry confirmation with the entry timestamp.

### Exit Parking Lot
Choose option 2 to process a vehicle's exit from the parking lot. You will be guided to select the vehicle type and enter the vehicle number. The system intelligently calculates the parking fee based on the duration of the vehicle's stay and displays comprehensive exiting vehicle information, including exit timestamp and fee details.

### Parking Lot Information
Opt for option 3 to access parking lot information. This submenu allows you to obtain real-time parking space availability and view detailed information of the vehicles currently parked in the lot.

### Change Fees
For authorized personnel, select option 98 to modify the parking fees for different vehicle types. This option requires a confirmation number for enhanced security.

### Exit Application
Choose option 99 to gracefully terminate the Parking Management System.

## Dependencies

The Parking Management System is developed using standard C libraries, without any external dependencies. As such, it is highly portable and compatible with a wide range of platforms that support a C compiler.

## Contact

For any inquiries or feedback, please feel free to contact us via email at chamathkaushlyack@gmail.com. We value your thoughts and suggestions and are eager to improve the Parking Management System based on your input.

## Note

This Parking Management System is a professional-grade solution suitable for managing parking facilities efficiently and effectively. While the utility is well-optimized and user-friendly, it is recommended for educational or small-scale applications. For larger parking facilities or production environments, additional features and security measures may be required. We welcome your valuable feedback and contributions to improve this system further. Thank you for using our Parking Management System!

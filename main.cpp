// Kyle Marler
// CIS 1111
// Christmas Shoppe Inventory Manager
/* This program is an inventory manager for a fictitious Christmas store with two locations at The Greene and the Dayton Mall. It allows the user to view inventory, input their own inventory, and obtain the total inventory at both locations. */

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;
using std::ofstream;

// Global constants
// Represents the number of store locations.
const int NUM_STORES = 2;
// Represents the maximum number of allowed items in the array.
const int MAX_ITEMS = 100;


// Beginning of a list of function prototypes.
/* This function named inputInventory accepts both arrays as arguements and allows the user to add elements to both of them. */
void inputInventory(int inventoryArray[MAX_ITEMS][NUM_STORES],string itemArray[MAX_ITEMS]);

/* This function reads the data from a saved file and displays the contents to the console. */
void displaySavedInventory();

/* This function reads the data from a saved file and calls the overloaded function below to calculate the sum. */
void sumOfInventory(int inventoryArray[MAX_ITEMS][NUM_STORES],string itemArray[MAX_ITEMS]);

/* This function sums all the values in inventory and returns the quantity. */
int sumOfInventory(int inventoryArray[MAX_ITEMS][NUM_STORES],int count);




int main()
{
    // Array of ints to store the quantity in inventory at both store locations.
    int inventoryArray[MAX_ITEMS][NUM_STORES];
    
    // Array of strings to store the item names.
    string itemArray[MAX_ITEMS];
    
    int menuSelection;  // Variable to hold the user's menu selection.
    char repeatSelection;   // Variable to hold user's response to repeat program.
    
    cout << "Kyle's Christmas Shoppe\n";
    cout << "Inventory Management System\n\n";
    cout << "##### This program manages the inventory of various items\n";
    cout << "at both our 'The Greene' and Dayon Mall locations. #####\n\n";
    
    do
    {
        cout << "----------------------------\n";
        cout << "1. Add Inventory\n";
        cout << "2. Display Saved Inventory From a File\n";
        cout << "3. Display Sum of Inventory\n";
        cout << "4. Exit Program\n\n";
        
        cout << "Please select from the listed menu options (1-4): ";
        cin >> menuSelection;
        
        // Validate user input.
        while (menuSelection != 1 && menuSelection != 2 && menuSelection != 3 && menuSelection != 4)
        {
            cout << "Please try again and enter a number (1-4): ";
            cin >> menuSelection;
        }
        
        switch(menuSelection)
        {
            case 1: // Input inventory
                inputInventory(inventoryArray,itemArray);
                cout << "\nWould you like to go back to the main menu?\n";
                cout << "Enter Y for yes or N to quit the program: ";
                cin >> repeatSelection;
                break;
            case 2: // Display saved inventory from a file
                displaySavedInventory();
                cout << "\nWould you like to go back to the main menu?\n";
                cout << "Enter Y for yes or N to quit the program: ";
                cin >> repeatSelection;
                break;
            case 3: // Display sum of inventory.
                sumOfInventory(inventoryArray,itemArray);
                cout << "\nWould you like to go back to the main menu?\n";
                cout << "Enter Y for yes or N to quit the program: ";
                cin >> repeatSelection;
                break;
            case 4: // Exit Program.
                cout << "\nThank you. You are now exiting the program.";
                repeatSelection = 'n';
                break;
        }
        cout << endl;
    } while (repeatSelection == 'Y' || repeatSelection == 'y');
    
    cout << endl;
    return 0;
}



// Beginning of a list of function definiitons.
/* This function named inputInventory accepts both arrays as arguements and allows the user to add elements to both of them. */
void inputInventory(int inventoryArray[MAX_ITEMS][NUM_STORES],string itemArray[MAX_ITEMS])
{
    // Variable to store the name of the items.
    string itemNames;
    
    // Variable to store item quantities.
    int itemQuantity;
    
    cout << "\n----------------------------\n";
    
    // Detailed instructions regarding item input criteria.
    cout << "\nThis portion of the program will collect the names of items\n";
    cout << "you wish to keep track of in inventory.\n\n";
    cout << "*IMPORTANT*: Please only use one word with no spaces for the item name.\n";
    cout << "When finished, enter F for finished.\n\n";
    cout << "Item 1: ";
    cin >> itemNames;
    
    // Variable to count how many items have been added to inventory.
    // Also serves as an index in the below if statement.
    int count = 0;
    
    // Detailed instructions regarding quantity input criteria.
    if (itemNames != "F" && itemNames != "f")
    {
        itemArray[count] = itemNames;
        cout << "\nNow, please enter the quantity in inventory\n";
        cout << "for " << itemNames << " at The Greene location.\n";
        cout << "\n*IMPORANT*: This should be a whole number above zero.\n";
        cout << "Quantity for " << itemNames << ": ";
        cin >> itemQuantity;
        inventoryArray[count][0] = itemQuantity;
        cout << "\nPlease enter the quantity\n";
        cout << "in inventory for " << itemNames << " at the Dayton Mall location.\n";
        cout << "Quantity for " << itemNames << ": ";
        cin >> itemQuantity;
        inventoryArray[count][1] = itemQuantity;
        count++;    // Increment the count.
        
        cout << "\nPlease enter another item name to add to inventory, or F to finish: ";
        cin >> itemNames;
    }
    
    // More concise prompts since the user knows the input criteria now.
    while (itemNames != "F" && itemNames != "f" && count < MAX_ITEMS)
    {
        itemArray[count] = itemNames;
        for (int index = 0; index < NUM_STORES; index++)
        {
            cout << "Enter inventory store " << (index + 1) << ": ";
            cin >> itemQuantity;
            inventoryArray[count][index] = itemQuantity;
        }
        count++;    // Increment the count.
        cout << "\nPlease enter another item name to add to inventory, or F to finish: ";
        cin >> itemNames;
    }
    
    /* Saving/writing user input to a file. I had to look online for how to get the read position to the end of the file before writing
     so that it wouldn't keep deleting the contents every time the user added an item to inventory. */
    ofstream fout;
    fout.open("inventory.txt", std::ios_base::app);
    
    for (int items = 0; items < count; items++)
    {
        fout << itemArray[items] << "\t\t";
        
        for (int stores = 0; stores < NUM_STORES; stores++)
        {
            fout << inventoryArray[items][stores] << "\t";
        }
        fout << endl;
    }
    fout.close();
}




/* This function reads the data in a saved file and displays the contents to the console. */
void displaySavedInventory()
{
    // Reading data from a file and displaying to cout.
    ifstream fin;
    fin.open("inventory.txt");
    
    // Variable to store the string contents of the file as it's being read.
    string tempItems;
    // Variable to store the int contents of the file as it's being read.
    int tempInventory;
    
    cout << "\n----------------------------\n";
    cout << "\nThis portion of the program reads the data from a file that was previously saved.\n\n";
    cout << setw(20) << left << "Item" << setw(20) << left
    << "The Greene Qty" << setw(20) << left << "Dayton Mall Qty\n";
    cout << "---------------------------------------\n";
    
    int count = 0;  // Variable to count the number of items.
    
    while (fin >> tempItems)
    {
        cout << setw(20) << left << tempItems;
        fin >> tempInventory;
        cout << setw(20) << left << tempInventory;
        fin >> tempInventory;
        cout << setw(20) << left << tempInventory;
        cout << endl;
        count++;
    }
    
    if (count == 0)
    {
        cout << "There is no inventory to display. The file is empty.\n";
    }
}




/* This function reads the data from a saved file and calls the overloaded function below to calculate the sum. */
void sumOfInventory(int inventoryArray[MAX_ITEMS][NUM_STORES],string itemArray[MAX_ITEMS])
{
    // Reading data from a file and displaying to cout.
    ifstream fin;
    fin.open("inventory.txt");
    
    // Variable to store the string contents of the file as it's being read.
    string tempItems;
    // Variable to store the int contents of the file as it's being read.
    int tempInventory;
    
    // Variable to count how many items have been added to inventory.
    // Also serves as an index in the below while loop.
    int count = 0;
    
    // Reading data from the file into both arrays.
    while (fin >> tempItems)
    {
        itemArray[count] = tempItems;
        fin >> tempInventory;
        inventoryArray[count][0] = tempInventory;
        fin >> tempInventory;
        inventoryArray[count][1] = tempInventory;
        count++;    // Increment the count.
    }
    
    // Display if the file is empty.
    if (count == 0)
    {
        cout << "\nYou have no items in inventory.\n";
    }
    
    if (count > 0)
    {
        int totalInventory = 0;
        
        cout << "\n----------------------------\n";
        cout << "\nThis portion of the program displays your total inventory\n";
        cout << "at both store locations.\n";
        totalInventory = sumOfInventory(inventoryArray, count);
        cout << "\nTotal Inventory: " << totalInventory << endl;
    }
}




/* This function sums all the values in inventory and returns the quantity. */
int sumOfInventory(int inventoryArray[MAX_ITEMS][NUM_STORES], int count)
{
    int total = 0;
    
    for (int items = 0; items < count; items++)
    {
        for (int stores = 0; stores < NUM_STORES; stores++)
        {
            total += inventoryArray[items][stores];
        }
    }
    return total;
}

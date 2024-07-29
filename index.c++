#include<iostream>
#include<fstream>
using namespace std;


int f_length(char str[])
{
	int i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return i;
}


bool is_compare(char str1[], char str2[])
{
	if (f_length(str1) == f_length(str2))
	{
		int i = 0;
		while (str1[i] != '\0')
		{
			if (str1[i] != str2[i])
			{
				return false;
			}
			++i;
		}
		return true;
	}
	return false;
}


bool loginAdmin()
{
	char str[20];
	char password[20] = { 'a','d','m','i','n' };
	cout << "enter password: ";
	cin >> str;
	return is_compare(str, password);
}

const int MAX_PRODUCTS = 100;
const int MAX_NAME_LENGTH = 50;
const int MAX_CUSTOMERS = 100;
const int MAX_USERNAME_LENGTH = 50;
const int MAX_PASSWORD_LENGTH = 50;

//void deleteRecord(int*, char[MAX_PRODUCTS][MAX_NAME_LENGTH], int*, int*);
void view_products(ifstream &fin);

char usernames[MAX_CUSTOMERS][MAX_USERNAME_LENGTH];
char passwords[MAX_CUSTOMERS][MAX_PASSWORD_LENGTH];
int numCustomers = 0;
void registerCustomer() {
	if (numCustomers >= MAX_CUSTOMERS) {
		cout << "Maximum number of customers reached!" << endl;
		return;
	}

	cout << "Enter username: ";
	cin >> usernames[numCustomers];  // Assuming only one user for simplicity

	cout << "Enter password: ";
	cin >> passwords[numCustomers];

	numCustomers++;

	// Open the file in append mode
	ofstream fout;
	fout.open("customer.txt", ios::app);

	// Check if the file is opened successfully
	if (!fout.is_open()) {
		cout << "Error opening file!" << endl;
		return;
	}

	// Write customer information to the file
	fout << usernames[numCustomers - 1] << " " << passwords[numCustomers - 1] << endl;

	// Close the file
	fout.close();

	cout << "Registration successful!" << endl;
}
bool loginCustomer(const char* enteredUsername, const char* enteredPassword) {
	ifstream fin;
	fin.open("customer.txt");

	// Check if the file is opened successfully
	if (!fin.is_open()) {
		cerr << "Error opening file!" << endl;
		return false;
	}

	char storedUsername[MAX_USERNAME_LENGTH];
	char storedPassword[MAX_PASSWORD_LENGTH];

	// Read each line from the file and check the credentials
	while (fin >> storedUsername >> storedPassword) {
		int i = 0;
		while (enteredUsername[i] != '\0' && storedUsername[i] != '\0' && enteredUsername[i] == storedUsername[i]) {
			i++;
		}

		if (enteredUsername[i] == '\0' && storedUsername[i] == '\0') {  // Check if both strings are equal
			i = 0;
			while (enteredPassword[i] != '\0' && storedPassword[i] != '\0' && enteredPassword[i] == storedPassword[i]) {
				i++;
			}

			if (enteredPassword[i] == '\0' && storedPassword[i] == '\0') {  // Check if both strings are equal
				// Credentials match
				fin.close();
				return true;
			}
		}
	}

	// No matching credentials found
	fin.close();
	return false;
}







int main() {
	int proID[100];
	char proName[100][50];
	int proPrice[100];
	int proQuantity[100];
	cout << "\t\t\t\tHowdy! How are you?" << endl;
	cout << "Login as Admin or Costumer? " << endl;
	cout << "1. Admin" << endl;
	cout << "2. Costumer" << endl;
	//For admin login
	int choice;
	cin >> choice;
	if (choice == 1)
	{
		while (!loginAdmin())
		{
			cout << "Sorry can't Connect as Admin coz of Wrong Password :(" << endl;
		}
		cout << "Welcome Admin" << endl;
		cout << "1. Display available products" << endl;
		cout << "2. Insert new product" << endl;
		cout << "3. Delete specific product" << endl;
		cout << "4. Update product information" << endl;
		cout << "5. View orders" << endl;
		cout << "6. Logout" << endl;
		int ad_choice;
		cout << "Enter your choice: ";
		cin >> ad_choice;

		
		ifstream fileInStream;
		fileInStream.open("products.txt");
		//use char array to read from file
		if (ad_choice == 1) {
			char ch;
			while (!fileInStream.eof()) {
				fileInStream.get(ch);
				cout << ch;
			}
			fileInStream.close();
		}
		if (ad_choice == 2)
		{
			int proID[100];
			char proName[100][50];
			int proPrice[100];
			int proQuantity[100];
			ofstream fout;
			fout.open("products.txt", ios::app);
			cout << "How many products you want to add?";
			int n;
			cin >> n;
			for (int i = 0; i < n; i++) {
				cout << "Enter product ID: ";
				cin >> proID[i];
				cout << "Enter product name: ";
				cin.ignore(); //to ignore the enter key
				cin.getline(proName[i], 50);
				cout << "Enter product price: ";
				cin >> proPrice[i];
				cout << "Enter product quantity: ";
				cin >> proQuantity[i];
				cout << "| " << proID[i] << " |" << proName[i] << " |" << proPrice[i] << " |" << proQuantity[i] << "," << endl;
				fout << "| " << proID[i] << " |" << proName[i] << " |" << proPrice[i] << " |" << proQuantity[i] << "," << endl;



			}
			fout.close();

		}
		if (ad_choice == 3) {
			int deleteId;
			cout << "Enter product ID to delete: ";
			cin >> deleteId;

			ifstream fin("products.txt");

			if (!fin.is_open()) {
				cerr << "Error opening file." << endl;
				return 1; // Exit with an error code
			}

			ofstream fout("temp.txt");
			bool deleted = false;

			int proId;
			char proName[50];
			int proPrice;
			int proQuantity;
			char comma;

			while (fin >> proId) {
				fin.get(comma);  // Read the trailing comma
				fin.getline(proName, 50, ',');
				fin >> proPrice >> proQuantity;

				if (proId != deleteId) {
					fout << proId << comma << proName << ',' << proPrice << ',' << proQuantity << endl;
				}
				else {
					deleted = true;
				}
			}

			fin.close();
			fout.close();

			if (deleted) {
				cout << "Product deleted successfully!" << endl;

				// Remove the old file and rename the temporary file
				if (remove("products.txt") != 0) {
					cerr << "Error deleting file!" << endl;
				}

				if (rename("temp.txt", "products.txt") != 0) {
					cerr << "Error renaming file!" << endl;
				}
			}
			else {
				cout << "Product not found." << endl;
				// Delete the temporary file as the product was not found
				remove("temp.txt");
			}
		}

			
		if (ad_choice == 4) {
			int updateId;
			cout << "Enter product ID to update: ";
			cin >> updateId;

			ifstream fin("products.txt");

			if (!fin.is_open()) {
				cout << "Error opening file." << endl;
				
			}

			ofstream fout("temp.txt");
			bool updated = false;

			int proId;
			char proName[50];
			int proPrice;
			int proQuantity;
			char comma;

			while (fin >> proId) {
				fin.get(comma);  // Read the trailing comma
				fin.getline(proName, 50, ',');
				fin >> proPrice >> proQuantity;

				if (proId != updateId) {
					fout << proId << comma << proName << ',' << proPrice << ',' << proQuantity << endl;
				}
				else {
					cout << "Enter new product name: ";
					cin.ignore(); //to ignore the enter key
					cin.getline(proName, 50);
					cout << "Enter new product price: ";
					cin >> proPrice;
					cout << "Enter new product quantity: ";
					cin >> proQuantity;
					fout << proId << comma << proName << ',' << proPrice << ',' << proQuantity << endl;
					updated = true;
				}
			}

			fin.close();
			fout.close();

			if (updated) {
				cout << "Product updated successfully!" << endl;

				// Remove the old file and rename the temporary file
				if (remove("products.txt") != 0) {
					cerr << "Error deleting file!" << endl;
				}

				if (rename("temp.txt", "products.txt") != 0) {
					cerr << "Error renaming file!" << endl;
				}
			}
			else {
				cout << "Product not found." << endl;
				// Delete the temporary file as the product was not found
				remove("temp.txt");
			}
			
			
			
		}
	}
	if (choice == 2)
	{
		cout << "1. Register \n 2. Login \n 3.Log out";
		int costumer_choice;
		cout << "Enter your choice: ";
		cin >> costumer_choice;
		if (costumer_choice == 1)
		{
			registerCustomer();

		}
		if (costumer_choice == 2)
		{
			char enteredUsername[MAX_USERNAME_LENGTH];
			char enteredPassword[MAX_PASSWORD_LENGTH];

			cout << "Enter username: ";
			cin >> enteredUsername;

			cout << "Enter password: ";
			cin >> enteredPassword;

			if (loginCustomer(enteredUsername, enteredPassword)) {
				cout << "Login successful!" << endl;
				cout << "1. View products \n 2. Add to cart \n 3. View cart \n 4. Remove from cart \n 5. Place order \n 6. Logout";
				int costumer_choice;
				cout << "Enter your choice: ";
				cin >> costumer_choice;
				if (costumer_choice == 1)
				{
					ifstream fileInStream;
					fileInStream.open("products.txt");
					//use char array to read from file
					char ch;
					while (!fileInStream.eof()) {
						fileInStream.get(ch);
						cout << ch;
					}
					fileInStream.close();

				}
				if (costumer_choice == 2)
				{
					ifstream fin;
					fin.open("products.txt");
					if (!fin.is_open()) {
						cout << "Error opening file\n";
					
					}
					else {
						ofstream fout;
						fout.open("products.txt");
						int proId[100];
						char proName[100][50];
						int proPrice[100];
						int proQuantity[100];
						char c_choice[50];
						//i want you to check if the product id is present in the file or not if it is present then add it to the cart and decrement the quantity
						//if it is not present then show error message
						char ch;
						while (!fin.eof()) {
							fin >> proId[100] >> proName[100][50] >> proPrice[100] >> proQuantity[100];
							for (int i = 0; c_choice[i] != '\0'; i++)
							{
								cin >> c_choice[i];
								if (c_choice[i] == proId[i])
								{
									fout << proId[i] << endl;
									cout<<proID[i]<<endl;
									fout << proName[i] << endl;
									cout<<proName[i]<<endl;
									fout << proPrice[i] << endl;
									cout<<proPrice[i]<<endl;
									fout << proQuantity[i] << endl;
									cout<<proQuantity[i]<<endl;
								}
								else {
									cout << "Product not found" << endl;
								}
							}

						}



					}
				}
				else {
					cout << "Login failed!" << endl;
				}
				if (costumer_choice == 3) {
					ifstream fin;
					fin.open("products.txt");
					if (!fin.is_open()) {
						cout << "Error opening file\n";
					}
					else {
						ofstream fout;
						fout.open("products.txt");
						int proId[100];
						char proName[100][50];
						int proPrice[100];
						int proQuantity[100];
						char c_choice[50];
						//i want you to check if the product id is present in the file or not if it is present then add it to the cart and decrement the quantity
						//if it is not present then show error message
						//where is decrement?

						char ch;
						while (!fin.eof()) {
							fin >> proId[100] >> proName[100][50] >> proPrice[100] >> proQuantity[100];
							for (int i = 0; c_choice[i] != '\0'; i++)
							{
								cin >> c_choice[i];
								if (c_choice[i] == proId[i])
								{
									fout << proId[i] << endl;
									cout << proID[i] << endl;
									fout << proName[i] << endl;
									cout << proName[i] << endl;
									fout << proPrice[i] << endl;
									cout << proPrice[i] << endl;
									fout << proQuantity[i] << endl;
									cout << proQuantity[i] << endl;
								}
								else {
									cout << "Product not found" << endl;
								}
							}

						}
					}
				}
				if (costumer_choice == 4) {
										ifstream fin;
					fin.open("products.txt");
					if (!fin.is_open()) {
						cout << "Error opening file\n";
					}
					else {
						ofstream fout;
						fout.open("products.txt");
						int proId[100];
						char proName[100][50];
						int proPrice[100];
						int proQuantity[100];
						char c_choice[50];
						//i want you to check if the product id is present in the file or not if it is present then add it to the cart and decrement the quantity
						//if it is not present then show error message
						char ch;
						while (!fin.eof()) {
							fin >> proId[100] >> proName[100][50] >> proPrice[100] >> proQuantity[100];
							for (int i = 0; c_choice[i] != '\0'; i++)
							{
								cin >> c_choice[i];
								if (c_choice[i] == proId[i])
								{
									fout << proId[i] << endl;
									cout << proID[i] << endl;
									fout << proName[i] << endl;
									cout << proName[i] << endl;
									fout << proPrice[i] << endl;
									cout << proPrice[i] << endl;
									fout << proQuantity[i] << endl;
									cout << proQuantity[i] << endl;
								}
								else {
									cout << "Product not found" << endl;
								}
							}

						}
					}
				}
				if (costumer_choice==5)
				{
					ifstream fin;
					fin.open("products.txt");

					if (!fin.is_open()) {
						cout << "Error opening file\n";
					}
					else {
						ifstream fin;
						fin.open("products.txt");

						if (!fin.is_open()) {
							cout << "Error opening file\n";
						}
						else {
							ofstream fout;
							fout.open("cart.txt");  // Use a different name for the output file
							int proId[100];
							char proName[100][50];
							int proPrice[100];
							int proQuantity[100];
							char c_choice[50];

							int i = 0;  // Add this line to define 'i'
							while (fin >> proId[i] >> proName[i] >> proPrice[i] >> proQuantity[i]) {
								cout << "Enter product ID to add to cart: ";
								cin >> c_choice;

								bool found = false;
								for (int j = 0; j < 100; j++) {
									if (proId[j] == atoi(c_choice)) {
										fout << proId[j] << endl;
										cout << proId[j] << endl;
										fout << proName[j] << endl;
										cout << proName[j] << endl;
										fout << proPrice[j] << endl;
										cout << proPrice[j] << endl;
										fout << proQuantity[j] << endl;
										cout << proQuantity[j] << endl;

										// Decrement quantity in the original file (you may want to adjust this based on your requirements)
										proQuantity[j]--;

										found = true;
										break;
									}
								}

								if (!found) {
									cout << "Product not found" << endl;
								}

								i++;  // Increment 'i' for the next iteration
							}
						}

					}

					}
				if(costumer_choice==6){
					cout << "Logout successful!" << endl;
				}
				
			}
		}
	return 0;
}




// Function to delete a record by ID
// Function to delete a record by ID
void deleteRecord(int*& proId, char**& proName, int*& proPrice, int*& proQuantity, int& n) {
	ifstream fin;
	fin.open("products.txt");

	if (!fin.is_open()) {
		cout << "Error opening file\n";
		return;
	}

	ofstream fout;
	fout.open("temp.txt");

	if (!fout.is_open()) {
		cout << "Error creating temporary file\n";
		fin.close();
		return;
	}

	cout << "Enter the ID of the Product you want to delete:";
	int input_ad;
	cin >> input_ad;

	int i = 0;
	while (fin >> proId[i]) {
		fin >> proName[i] >> proPrice[i] >> proQuantity[i];

		if (input_ad == proId[i]) {
			// Skip this record (do not write it to the temporary file)
			cout << "Product with ID " << input_ad << " deleted successfully!" << endl;
		}
		else {
			// Write the record to the temporary file
			fout << proId[i] << ' ' << proName[i] << ' ' << proPrice[i] << ' ' << proQuantity[i] << endl;
		}

		i++;
	}

	fin.close();
	fout.close();

	// Rename the temporary file to the original filename
	if (rename("temp.txt", "products.txt") != 0) {
		cout << "Error renaming file. Products may not have been deleted correctly." << endl;
	}
	else {
		cout << "File renamed successfully." << endl;
	}
}

void view_products(ifstream& fin) {
	char ch;
	while (!fin.eof()) {
		fin.get(ch);
		cout << ch;
	}
	fin.close();
}

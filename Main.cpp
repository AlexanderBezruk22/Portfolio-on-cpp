#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <Lmcons.h>

using namespace std;


bool signIn() 
{
	string username, password, un, pw;

	cout << "Enter username: "; cin >> username;
	cout << "Enter password: "; cin >> password;

	ifstream read("C:/" + username + ".txt");
	getline(read, un);
	getline(read, pw);
	if (username == un && password == pw)
	{
		return true;
	}
	else
		return false;

}



int main() 
{
	int chose; 
	cout << "1: Sign Up\n2: Sign In\nYour choose: "; cin >> chose;
	if (chose == 1)
	{
		string username, password;
		cout << endl << "Enter username: "; cin >> username;
		cout << endl << "Enter password: "; cin >> password;
		ofstream file;
		file.open("C:/" + username + ".txt");
		file << username << endl << password;
		file.close();

		main();
	}
	else if (chose == 2)
	{
		bool result = signIn();

		if (!result) {
			cout << "\nNot found user with username or password" << endl;
			system("PAUSE");
			return 0;
		}
	}
}

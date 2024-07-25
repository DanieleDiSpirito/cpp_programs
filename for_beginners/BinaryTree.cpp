#include <iostream>
#include <fstream>

using namespace std;

int main(){
	
	char SelectedOption;
	int n, i, p, j, k;
	int key[n];
	int dim = 7;
	int a[dim];
	
	cout <<"Benvenuto professor Cardellicchio..." << endl;
	cout << "...scelga una tra le seguenti opzioni:" << endl;
	do{
		cout << "r per utilizzare Command Prompt" << endl;
		cout << "f per leggere file di testo" << endl;
		cin >> SelectedOption;
	} while (SelectedOption != 'r' && SelectedOption != 'f');
			
	switch(SelectedOption)
	{
		case 'r':
			do{
				cout << "Inserisca un valore di n maggiore di zero: ";
				cin >> n;
			} while (n <= 0);
			cout << "Inserisca una chiave per ciascun nodo" << endl;
			for (i = 0; i < n; i++){
				cout << "Chiave: ";
				cin >> key[i];
			}
			cout << "Inserisca un valore per k: ";
			cin >> k;
			cout << "Array Ordinato:" << endl;
			for (i = 0; i < n; i++){
				for (j = i + 1; j <= n - 1; j++){
					if (key[i] > key[j]){
						p = key[j];
						key[j] = key[i];
						key[i] = p;
					}
				}
				cout << "|" << key[i];
			}
			cout << "|\n";
			cout << "Coppie di nodi simili:" << endl;
			for (i = 0; i < n; i++){
				for (j = i + 1; j <= n - 1; j++){
					p = key[j] - key[i];
					if (p < 0){
						p = -p;
					}
					if (p <= k){
						cout << key[i] << "," << key[j] << endl;
					}
				}
			}
			for (i = n - 1; i >= 0; i--){
				for (j = i - 1; j >= 0; j--){
					p = key[i] - key[j];
					if (p < 0){
						p = -p;
					}
					if (p <= k){
						cout << key[i] << "," << key[j] << endl;
					}
				}
			}
			break;			
		case 'f':
			ifstream inputFile;
			inputFile.open ("Array.txt");
			for (i = 0; i < dim; i++){
				inputFile >> a[i];
			}
			cout << "Array letto da file di testo: " << endl;
			for (i = 0; i < dim; i++){
				cout << "|" << a[i];
			}
			cout << "|\n";
			inputFile.close();
			cout << "Inserisca un valore per k: ";
			cin >> k;
			cout << "Array Ordinato:" << endl;
			for (i = 0; i < dim; i++){
				for (j = i + 1; j <= dim - 1; j++){
					if (a[i] > a[j]){
						p = a[j];
						a[j] = a[i];
						a[i] = p;
					}
				}
				cout << "|" << a[i];
			}
			cout << "|\n";
			cout << "Coppie di nodi simili:" << endl;
			for (i = 0; i < dim; i++){
				for (j = i + 1; j <= dim - 1; j++){
					p = a[j] - a[i];
					if (p < 0){
						p = -p;
					}
					if (p <= k){
						cout << a[i] << "," << a[j] << endl;
					}
				}
			}
			for (i = dim - 1; i >= 0; i--){
				for (j = i - 1; j >= 0; j--){
					p = a[i] - a[j];
					if (p < 0){
						p = -p;
					}
					if (p <= k){
						cout << a[i] << "," << a[j] << endl;
					}
				}
			}
			break;
	}
			
	system("pause");
	return 0;
}

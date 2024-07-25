#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    // Inizializzo la classe ofstream
    // Dando come parametro al costruttore
    // Il nome del file da creare
    ofstream file("Balah.txt");
    // Scrivo dentro al file
    file << "Hello world";
    // Chiudo il file
    file.close();
    return 0;
}

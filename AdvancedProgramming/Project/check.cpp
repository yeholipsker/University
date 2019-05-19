#include "Parser.h"
#include "Trip.h"
#include "Cab.h"
#include "TaxiCenter.h"
#include "Map.h"


int main(int argc, char **argv) {
    string s;
    Map* m;
    TaxiCenter t(m);
    Parser p(&t);
    getline(cin,s);
    if(!p.validateMap(s)){
        cout << -1 <<endl;
    }
return 0;
}
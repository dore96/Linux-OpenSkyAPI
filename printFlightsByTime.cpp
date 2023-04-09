#include "utility.cpp"

void printFlightsByTime(DB& DB,char* airport_name);
bool compareArrivals(const flight& a, const flight& b) ;
bool compareDepartures(const flight& a, const flight& b) ;

int main (int argc, char* argv[])
{
    DB DB;
    LoadDB(DB);

    for(int i = 1; i < 2; i++)
    {
        printFlightsByTime(DB,"LLBG");
    }

    return 0;
}

void printFlightsByTime(DB& DB,char* airport_name)
{
    string airportName(airport_name);
    airport* airport = getAirport(DB,airportName);
    int i = 0;

    vector<string> flights;
    int numberOfFlights = airport->arrFlights.size() + airport->depFlights.size();

    flights.reserve(numberOfFlights);

    // Sort the vector using the compare function
    sort(airport->arrFlights.begin(), airport->arrFlights.end(), compareArrivals);
    sort(airport->depFlights.begin(), airport->depFlights.end(), compareDepartures);
    
     // Define iterators for the two vectors
    auto it1 = airport->arrFlights.begin();
    auto it2 = airport->depFlights.begin();

    // Print the two vectors in ascending order
    while (it1 != airport->arrFlights.end() && it2 != airport->depFlights.end()) {
        if (it1->arrivalTime <= it2->depTime) {
            std::cout << it1->arrivalTime << " ";
            ++it1;
        }
        else {
            std::cout << it2->depTime << " ";
            ++it2;
        }
    }
    while (it1 != airport->arrFlights.end()) 
    {
        cout << it1->flightStr;
        ++it1;
    }
    while (it2 != airport->depFlights.end()) 
    {
        cout << it2->flightStr;
        ++it2;
    }

}

bool compareArrivals(const flight& a, const flight& b) 
{
    return a.arrivalTime < b.arrivalTime;
}

bool compareDepartures(const flight& a, const flight& b) 
{
    return a.depTime < b.depTime;
}
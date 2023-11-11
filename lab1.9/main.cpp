#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <queue>

struct Passenger {
    std::string name;
};

struct Flight {
    std::string flightNumber;
    int maxSeats = 0;
    std::vector<Passenger> passengerList;
    std::queue<Passenger> waitingQueue;
};

class ReservationSystem {
private:
    std::vector<Flight> flights;
    std::unordered_map<std::string, std::queue<Passenger>> flightQueues;

public:
    void addFlight(const std::string& flightNumber, size_t maxSeats) {
        Flight flight;
        flight.flightNumber = flightNumber;
        flight.maxSeats = maxSeats;
        flights.push_back(flight);
        flightQueues[flightNumber] = std::queue<Passenger>();
    }

    void bookTicket(const std::string& flightNumber, const std::string& passengerName) {
        auto flight = std::find_if(flights.begin(), flights.end(),
                                   [&flightNumber](const Flight& f) { return f.flightNumber == flightNumber; });

        if (flight != flights.end()) {
            // Check if the passenger is not already in the passenger list
            if (std::find_if(flight->passengerList.begin(), flight->passengerList.end(),
                             [&passengerName](const Passenger& p) { return p.name == passengerName; })
 == flight->passengerList.end()) {
                // Check if there are available seats
                if (flight->passengerList.size() < flight->maxSeats) {
                    flight->passengerList.push_back({passengerName});
                    std::cout << "Ticket booked for " << passengerName << " on flight " << flightNumber
 << std::endl;
                } else {
                    // Add passenger to the waiting queue using hashing
                    flightQueues[flightNumber].push({passengerName});
                    std::cout << "Added " << passengerName << " to the waiting queue for flight " <<
 flightNumber << std::endl;
                }
            } else {
                std::cout << passengerName << " is already booked on flight " << flightNumber << std::
endl;
            }
        } else {
            std::cout << "Flight " << flightNumber << " not found" << std::endl;
        }
    }
};

int main() {
    ReservationSystem reservationSystem;

    // Adding flights
    reservationSystem.addFlight("F001", 2);
    reservationSystem.addFlight("F002", 3);

    // Booking tickets
    reservationSystem.bookTicket("F001", "Passenger1");
    reservationSystem.bookTicket("F001", "Passenger2");
    reservationSystem.bookTicket("F001", "Passenger3");  // This passenger will be added to the waiting queue
    reservationSystem.bookTicket("F002", "Passenger4");
    reservationSystem.bookTicket("F002", "Passenger1");  // This passenger is already booked

    return 0;
}

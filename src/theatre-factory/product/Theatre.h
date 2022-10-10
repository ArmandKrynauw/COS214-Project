#ifndef THEATRE_H
#define THEATRE_H

#include <iostream> //remove later Testing purposes

class Theatre {
    private:
        std::string theatreName;
    public:
        Theatre(std::string theatreName);
        void setTheatreName(std::string);
        std::string getTheatreName();
        ~Theatre();
};

#endif // THEATRE_H
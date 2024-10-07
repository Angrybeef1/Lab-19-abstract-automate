// comsc 210 | Lab 19 abstract & automate | Robert Stonemetz


#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
#include <random>
#include <sstream>


using namespace std;


//structure to represent a single movie review

struct Review {
    double rating;
    string comments;
    Review* next;

    //initialize a review
    Review(double r, string c) : rating(r), comments(c), next(nullptr){}
};

class ReviewList {
    private:
        Review* head; //points to the first review in the list
        int count; //number of reviews in the list

    public:
    //initialize a list
    ReviewList() : head(nullptr), tail(nullptr), count(0) {}

        //add review to the head of the list
        void addToHead (double rating, string comments) {
            Review* newReview = new Review(rating, comments);
            newReview -> next = head;
            head = newReview;
            count++;
        }

        //display reviews
        void displayReviews(){
            Review* current = head;
            int reviewNum = 1;
            double sum = 0;

            cout << "Outputing all reviews:" << endl;
            while (current != nullptr) {
                cout << "    > Reviews #" << reviewNum<< ": " << fixed << setprecision (1) 
                    << current->rating << ": " << current->comments << endl;
                sum += current -> rating;
                current = current -> next;
                reviewNum++;
            }

            if (count > 0) {
                double average = sum / count;
                cout << "    > Average: " << fixed << setprecision(2) << average << endl;
            }
        }

        // Destructor to free allocated memory
        ~ReviewList() {
            while (head != nullptr){
                Review* temp = head;
                head = head -> next;
                delete temp;
            }
        }
    };

    //class to represent movie and reviews
    class Movie {
        private: 
            string title;
            ReviewList reviews;

        public:
            //constructor to init movie with review
            Movie(const string& t) : title(t) {}

            //adds new review to title
            void addReview (double rating, const string& comment) {
                reviews.addToHead(rating, comment);
            }

            //display movie information
            void displayInfo() {
                cout << "Movie: " << title << endl;
                reviews.displayReviews();
                cout << endl;
            }
    };

    


    double getRating() {
        double rating;
        while (true) {
            cout << "Enter review rating 0-5: ";
            if (cin >> rating && rating >= 0 && rating <=5) {
                cin.ignore(10000, '\n');
                return rating;
            } else {
                cout << "Invalid input. Please enter a number between 0 and 5. " << endl;
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }
    }

    string getComments() {
        string comments;
        cout << "Enter review comments: ";
        getline(cin, comments);
        return comments;
    }

    bool continueReviewing() {
        char choice;
        do {
            cout << "Enter another review? Y/N: ";
            cin >> choice;
            cin.ignore(10000, '\n');  // Clear input buffer
            choice = toupper(choice);
        } while (choice != 'Y' && choice != 'N');
        return choice == 'Y';
    }




int main(){
    ReviewList reviews;
    int choice;

    //ask user which insertion to use
    cout << "Which linked list method should we use?" << endl 
         << "    [1] New nodes are added at the head of thelinked list." << endl
         << "    [2] New nodes are added at the tailof the linked list." << endl
         << "    choice: ";
    cin >> choice;

    cin.ignore (10000, '\n'); //clears input.

    bool addToTail = (choice == 2);

    //loop to add reviews
    do {
        double rating = getRating();
        string comments = getComments();

        if (addToTail) {
            reviews.addToTail(rating,comments);
        } else {
            reviews.addToHead(rating, comments);
        }
    } while (continueReviewing());

    reviews.displayReviews();

    return 0;

}
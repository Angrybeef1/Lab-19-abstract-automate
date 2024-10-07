#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
#include <random>
#include <sstream>

using namespace std;

// Structure to represent a single review
struct Review {
    double rating;
    string comments;
    Review* next;

    // Constructor to initialize a review
    Review(double r, string c) : rating(r), comments(c), next(nullptr) {}
};

// Class to manage a linked list of reviews
class ReviewList {
private:
    Review* head;  // Pointer to the first review in the list
    int count;     // Number of reviews in the list

public:
    // Constructor to initialize an empty review list
    ReviewList() : head(nullptr), count(0) {}

    // Method to add a new review to the head of the list
    void addToHead(double rating, string comments)  {
        Review* newReview = new Review(rating, comments);
        newReview->next = head;
        head = newReview;
        count++;
    }

    // Method to display all reviews in the list
    void displayReviews() const {
        Review* current = head;
        int reviewNum = 1;
        double sum = 0;

        cout << "Reviews:" << endl;
        while (current != nullptr) {
            cout << "  > Review #" << reviewNum << ": "
                << fixed << setprecision(1) << current->rating << ": " << current->comments << endl;
            sum += current->rating;
            current = current->next;
            reviewNum++;
        }

        // Calculate and display average rating if there are reviews
        if (count > 0) {
            double average = sum / count;
            cout << "  > Average Rating: " << fixed << setprecision(2) << average << endl;
        }
    }

    // Destructor to free allocated memory
    ~ReviewList() {
        while (head != nullptr) {
            Review* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Class to represent a movie with its reviews
class Movie {
private:
    string title;
    ReviewList reviews;

public:
    // Constructor to initialize a movie with its title
    Movie(const string& t) : title(t) {}

    // Method to add a new review to the movie
    void addReview(double rating, const string& comment)  {
        reviews.addToHead(rating, comment);
    }

    // Method to display movie information and its reviews
    void displayInfo() const {
        cout << "Movie: " << title << endl;
        reviews.displayReviews();
        cout << endl;
    }
};

// Function to generate a random rating between 1.0 and 5.0
double generateRandomRating() {
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_real_distribution<> dis(1.0, 5.0);
    return round(dis(gen) * 10.0) / 10.0;  // Round to one decimal place
}

// Function to read movies and their reviews from a file
vector<Movie> readMoviesFromFile(const string& filename) {
    vector<Movie> movies;
    ifstream file(filename);
    string line;
	

    if (file.is_open()) {
        while (getline(file, line)) {
            if (line[0] == '#') {  // New movie title
                string title = line.substr(1);
                movies.emplace_back(title);
            }
            else if (!movies.empty()) {
                // Add review to the last movie
                movies.back().addReview(generateRandomRating(), line);
            }
        }
    
    file.close();
    } else {
        cout << "Unable to open file: " << filename << endl;
    }

    return movies;
}

int main() {
    // Read movies from file
    vector<Movie> movies = readMoviesFromFile("movies.txt");

    // Check if any movies were loaded
    if (movies.empty()) {
        cout << "No movies were loaded. Please check the content of movies.txt." << endl;
        return 1;
    }

    // Display information for each movie
    for (const auto& movie : movies) {
        movie.displayInfo();
    }

    return 0;
}
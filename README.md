What to submit: the invite/join link to your repl.

Lab 18 currently is structured to store and manipulate movie reviews for a single movie title. 
Abstract this structure by one layer. Automate it such that review comments are read from an external file, and the movie rating is a random double 
(one decimal place) between 1.0 and 5.0.

Create a Movie class with these private member variables: movie title, a linked list for the rating number, and a linked list for review comments.

Your main() function needs to feature a container of Movie objects. It'll be your choice of data structures to use for this container: array, vector, linked list.

Your code doesn't need to ask the user to select adding nodes to the head/tail; you can just add nodes to the head to make it easiest.

Exercise your class by writing a driver/demo program that will have at least two Movie objects, each with at least two reviews.

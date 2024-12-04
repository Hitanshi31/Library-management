#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100
#define MAX_TITLE 50
#define MAX_AUTHOR 50

// Structure to store book information
typedef struct {
    int id;
    char title[MAX_TITLE];
    char author[MAX_AUTHOR];
    int is_available; // 1 for available, 0 for checked out
} Book;

// Array to store books
Book library[MAX_BOOKS];
int book_count = 0;

// Function declarations
void add_book();
void display_books();
void search_book();
void check_out_book();
void return_book();
void menu();

int main() {
    while (1) {
        menu();
    }
    return 0;
}

void menu() {
    int choice;
    printf("\nLibrary Management System\n");
    printf("1. Add Book\n");
    printf("2. Display All Books\n");
    printf("3. Search Book\n");
    printf("4. Check Out Book\n");
    printf("5. Return Book\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            add_book();
            break;
        case 2:
            display_books();
            break;
        case 3:
            search_book();
            break;
        case 4:
            check_out_book();
            break;
        case 5:
            return_book();
            break;
        case 6:
            printf("Exiting the program. Goodbye!\n");
            exit(0);
        default:
            printf("Invalid choice! Please try again.\n");
    }
}

void add_book() {
    if (book_count >= MAX_BOOKS) {
        printf("Library is full! Cannot add more books.\n");
        return;
    }

    Book new_book;
    new_book.id = book_count + 1;
    getchar(); // Clear newline character from input buffer
    printf("Enter book title: ");
    fgets(new_book.title, MAX_TITLE, stdin);
    new_book.title[strcspn(new_book.title, "\n")] = 0; // Remove newline character

    printf("Enter author name: ");
    fgets(new_book.author, MAX_AUTHOR, stdin);
    new_book.author[strcspn(new_book.author, "\n")] = 0; // Remove newline character

    new_book.is_available = 1;
    library[book_count++] = new_book;

    printf("Book added successfully!\n");
}

void display_books() {
    if (book_count == 0) {
        printf("No books available in the library.\n");
        return;
    }

    printf("\nBooks in Library:\n");
    printf("%-5s %-30s %-20s %-10s\n", "ID", "Title", "Author", "Status");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < book_count; i++) {
        printf("%-5d %-30s %-20s %-10s\n", library[i].id, library[i].title, library[i].author, library[i].is_available ? "Available" : "Checked Out");
    }
}

void search_book() {
    char query[MAX_TITLE];
    getchar(); // Clear newline character from input buffer
    printf("Enter book title to search: ");
    fgets(query, MAX_TITLE, stdin);
    query[strcspn(query, "\n")] = 0; // Remove newline character

    printf("\nSearch Results:\n");
    printf("%-5s %-30s %-20s %-10s\n", "ID", "Title", "Author", "Status");
    printf("---------------------------------------------------------------\n");
    int found = 0;
    for (int i = 0; i < book_count; i++) {
        if (strstr(library[i].title, query) != NULL) {
            printf("%-5d %-30s %-20s %-10s\n", library[i].id, library[i].title, library[i].author, library[i].is_available ? "Available" : "Checked Out");
            found = 1;
        }
    }
    if (!found) {
        printf("No books found with the title '%s'.\n", query);
    }
}

void check_out_book() {
    int id;
    printf("Enter book ID to check out: ");
    scanf("%d", &id);

    if (id <= 0 || id > book_count) {
        printf("Invalid book ID!\n");
        return;
    }

    if (!library[id - 1].is_available) {
        printf("Book is already checked out!\n");
        return;
    }

    library[id - 1].is_available = 0;
    printf("Book checked out successfully!\n");
}

void return_book() {
    int id;
    printf("Enter book ID to return: ");
    scanf("%d", &id);

    if (id <= 0 || id > book_count) {
        printf("Invalid book ID!\n");
        return;
    }

    if (library[id - 1].is_available) {
        printf("Book is already available in the library!\n");
        return;
    }

    library[id - 1].is_available = 1;
    printf("Book returned successfully!\n");
}
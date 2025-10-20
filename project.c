#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_BOOKS 1000
#define MAX_MEMBERS 500
#define MAX_TRANSACTIONS 2000
#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "green123"

// Structure definitions
typedef struct {
    int book_id;
    char title[100];
    char author[50];
    char isbn[20];
    char category[30];
    char publisher[50];
    int publication_year;
    float price;
    int total_copies;
    int available_copies;
    char department[30];
    int is_reference;
} Book;

typedef struct {
    int member_id;
    char name[50];
    char type[20]; // Student, Faculty, Staff
    char department[30];
    char email[50];
    char phone[15];
    char join_date[11];
    int max_books;
    int books_issued;
    int is_active;
} Member;

typedef struct {
    int transaction_id;
    int book_id;
    int member_id;
    char issue_date[11];
    char due_date[11];
    char return_date[11];
    float fine_amount;
    char status[20]; // Issued, Returned, Overdue
} Transaction;

typedef struct {
    Book books[MAX_BOOKS];
    Member members[MAX_MEMBERS];
    Transaction transactions[MAX_TRANSACTIONS];
    int book_count;
    int member_count;
    int transaction_count;
} Library;

// Function prototypes
void initializeLibrary(Library *lib);
void displayMainMenu();
void adminLogin();
int authenticateAdmin();
void adminMenu(Library *lib);
void memberMenu(Library *lib);
void addBook(Library *lib);
void searchBooks(Library *lib);
void viewAllBooks(Library *lib);
void updateBook(Library *lib);
void deleteBook(Library *lib);
void addMember(Library *lib);
void searchMembers(Library *lib);
void viewAllMembers(Library *lib);
void updateMember(Library *lib);
void issueBook(Library *lib);
void returnBook(Library *lib);
void viewTransactions(Library *lib);
void calculateFine(Library *lib);
void generateReports(Library *lib);
void saveData(Library *lib);
void loadData(Library *lib);
int validateDate(char *date);
void getCurrentDate(char *date);
void addDaysToDate(char *result, char *start_date, int days);
int dateDifference(char *date1, char *date2);

// Global variables
Library library;

int main() {
    initializeLibrary(&library);
    loadData(&library);
    
    printf("============================================\n");
    printf("  GREEN UNIVERSITY OF BANGLADESH\n");
    printf("    LIBRARY MANAGEMENT SYSTEM\n");
    printf("============================================\n");
    
    int choice;
    do {
        displayMainMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                adminLogin();
                break;
            case 2:
                memberMenu(&library);
                break;
            case 3:
                printf("Thank you for using Library Management System!\n");
                saveData(&library);
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 3);
    
    return 0;
}

void initializeLibrary(Library *lib) {
    lib->book_count = 0;
    lib->member_count = 0;
    lib->transaction_count = 0;
}

void displayMainMenu() {
    printf("\n========== MAIN MENU ==========\n");
    printf("1. Admin Login\n");
    printf("2. Member Access\n");
    printf("3. Exit\n");
    printf("===============================\n");
}

void adminLogin() {
    char username[50], password[50];
    
    printf("\n========== ADMIN LOGIN ==========\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);
    
    if(strcmp(username, ADMIN_USERNAME) == 0 && strcmp(password, ADMIN_PASSWORD) == 0) {
        printf("Login successful!\n");
        adminMenu(&library);
    } else {
        printf("Invalid username or password!\n");
    }
}

void adminMenu(Library *lib) {
    int choice;
    do {
        printf("\n========== ADMIN MENU ==========\n");
        printf("1. Add Book\n");
        printf("2. Search Books\n");
        printf("3. View All Books\n");
        printf("4. Update Book\n");
        printf("5. Delete Book\n");
        printf("6. Add Member\n");
        printf("7. Search Members\n");
        printf("8. View All Members\n");
        printf("9. Update Member\n");
        printf("10. Issue Book\n");
        printf("11. Return Book\n");
        printf("12. View Transactions\n");
        printf("13. Calculate Fine\n");
        printf("14. Generate Reports\n");
        printf("15. Back to Main Menu\n");
        printf("================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: addBook(lib); break;
            case 2: searchBooks(lib); break;
            case 3: viewAllBooks(lib); break;
            case 4: updateBook(lib); break;
            case 5: deleteBook(lib); break;
            case 6: addMember(lib); break;
            case 7: searchMembers(lib); break;
            case 8: viewAllMembers(lib); break;
            case 9: updateMember(lib); break;
            case 10: issueBook(lib); break;
            case 11: returnBook(lib); break;
            case 12: viewTransactions(lib); break;
            case 13: calculateFine(lib); break;
            case 14: generateReports(lib); break;
            case 15: printf("Returning to main menu...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while(choice != 15);
}

void memberMenu(Library *lib) {
    int choice, member_id;
    printf("\nEnter your Member ID: ");
    scanf("%d", &member_id);
    
    // Find member
    int member_index = -1;
    for(int i = 0; i < lib->member_count; i++) {
        if(lib->members[i].member_id == member_id && lib->members[i].is_active) {
            member_index = i;
            break;
        }
    }
    
    if(member_index == -1) {
        printf("Member not found or inactive!\n");
        return;
    }
    
    printf("Welcome, %s!\n", lib->members[member_index].name);
    
    do {
        printf("\n========== MEMBER MENU ==========\n");
        printf("1. Search Books\n");
        printf("2. View All Books\n");
        printf("3. View My Issued Books\n");
        printf("4. Back to Main Menu\n");
        printf("================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: searchBooks(lib); break;
            case 2: viewAllBooks(lib); break;
            case 3: 
                printf("\n=== Books Issued to You ===\n");
                for(int i = 0; i < lib->transaction_count; i++) {
                    if(lib->transactions[i].member_id == member_id && 
                       strcmp(lib->transactions[i].status, "Issued") == 0) {
                        for(int j = 0; j < lib->book_count; j++) {
                            if(lib->books[j].book_id == lib->transactions[i].book_id) {
                                printf("Book: %s (Due: %s)\n", 
                                       lib->books[j].title, 
                                       lib->transactions[i].due_date);
                                break;
                            }
                        }
                    }
                }
                break;
            case 4: printf("Returning to main menu...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while(choice != 4);
}

void addBook(Library *lib) {
    if(lib->book_count >= MAX_BOOKS) {
        printf("Book storage full! Cannot add more books.\n");
        return;
    }
    
    Book new_book;
    printf("\n=== ADD NEW BOOK ===\n");
    
    new_book.book_id = lib->book_count + 1;
    
    printf("Title: ");
    getchar();
    fgets(new_book.title, sizeof(new_book.title), stdin);
    new_book.title[strcspn(new_book.title, "\n")] = 0;
    
    printf("Author: ");
    fgets(new_book.author, sizeof(new_book.author), stdin);
    new_book.author[strcspn(new_book.author, "\n")] = 0;
    
    printf("ISBN: ");
    fgets(new_book.isbn, sizeof(new_book.isbn), stdin);
    new_book.isbn[strcspn(new_book.isbn, "\n")] = 0;
    
    printf("Category: ");
    fgets(new_book.category, sizeof(new_book.category), stdin);
    new_book.category[strcspn(new_book.category, "\n")] = 0;
    
    printf("Publisher: ");
    fgets(new_book.publisher, sizeof(new_book.publisher), stdin);
    new_book.publisher[strcspn(new_book.publisher, "\n")] = 0;
    
    printf("Publication Year: ");
    scanf("%d", &new_book.publication_year);
    
    printf("Price: ");
    scanf("%f", &new_book.price);
    
    printf("Total Copies: ");
    scanf("%d", &new_book.total_copies);
    
    new_book.available_copies = new_book.total_copies;
    
    printf("Department: ");
    getchar();
    fgets(new_book.department, sizeof(new_book.department), stdin);
    new_book.department[strcspn(new_book.department, "\n")] = 0;
    
    printf("Is Reference Book? (1 for Yes, 0 for No): ");
    scanf("%d", &new_book.is_reference);
    
    lib->books[lib->book_count] = new_book;
    lib->book_count++;
    
    printf("Book added successfully! Book ID: %d\n", new_book.book_id);
}

void searchBooks(Library *lib) {
    int choice;
    char search_term[100];
    
    printf("\n=== SEARCH BOOKS ===\n");
    printf("1. Search by Title\n");
    printf("2. Search by Author\n");
    printf("3. Search by Category\n");
    printf("4. Search by ISBN\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    
    getchar();
    printf("Enter search term: ");
    fgets(search_term, sizeof(search_term), stdin);
    search_term[strcspn(search_term, "\n")] = 0;
    
    printf("\n=== SEARCH RESULTS ===\n");
    int found = 0;
    
    for(int i = 0; i < lib->book_count; i++) {
        int match = 0;
        
        switch(choice) {
            case 1:
                if(strstr(lib->books[i].title, search_term) != NULL) match = 1;
                break;
            case 2:
                if(strstr(lib->books[i].author, search_term) != NULL) match = 1;
                break;
            case 3:
                if(strstr(lib->books[i].category, search_term) != NULL) match = 1;
                break;
            case 4:
                if(strstr(lib->books[i].isbn, search_term) != NULL) match = 1;
                break;
        }
        
        if(match) {
            printf("ID: %d | %s | %s | Available: %d/%d\n", 
                   lib->books[i].book_id, 
                   lib->books[i].title, 
                   lib->books[i].author,
                   lib->books[i].available_copies,
                   lib->books[i].total_copies);
            found = 1;
        }
    }
    
    if(!found) {
        printf("No books found!\n");
    }
}

void viewAllBooks(Library *lib) {
    printf("\n=== ALL BOOKS ===\n");
    printf("%-5s %-30s %-20s %-15s %-10s\n", 
           "ID", "Title", "Author", "Category", "Available");
    printf("------------------------------------------------------------------------\n");
    
    for(int i = 0; i < lib->book_count; i++) {
        printf("%-5d %-30s %-20s %-15s %-10d\n", 
               lib->books[i].book_id,
               lib->books[i].title,
               lib->books[i].author,
               lib->books[i].category,
               lib->books[i].available_copies);
    }
}

void addMember(Library *lib) {
    if(lib->member_count >= MAX_MEMBERS) {
        printf("Member storage full! Cannot add more members.\n");
        return;
    }
    
    Member new_member;
    printf("\n=== ADD NEW MEMBER ===\n");
    
    new_member.member_id = lib->member_count + 1;
    
    printf("Name: ");
    getchar();
    fgets(new_member.name, sizeof(new_member.name), stdin);
    new_member.name[strcspn(new_member.name, "\n")] = 0;
    
    printf("Type (Student/Faculty/Staff): ");
    fgets(new_member.type, sizeof(new_member.type), stdin);
    new_member.type[strcspn(new_member.type, "\n")] = 0;
    
    printf("Department: ");
    fgets(new_member.department, sizeof(new_member.department), stdin);
    new_member.department[strcspn(new_member.department, "\n")] = 0;
    
    printf("Email: ");
    fgets(new_member.email, sizeof(new_member.email), stdin);
    new_member.email[strcspn(new_member.email, "\n")] = 0;
    
    printf("Phone: ");
    fgets(new_member.phone, sizeof(new_member.phone), stdin);
    new_member.phone[strcspn(new_member.phone, "\n")] = 0;
    
    // Set default values
    getCurrentDate(new_member.join_date);
    new_member.books_issued = 0;
    new_member.is_active = 1;
    
    // Set max books based on type
    if(strcmp(new_member.type, "Faculty") == 0) {
        new_member.max_books = 10;
    } else if(strcmp(new_member.type, "Staff") == 0) {
        new_member.max_books = 5;
    } else {
        new_member.max_books = 3; // Students
    }
    
    lib->members[lib->member_count] = new_member;
    lib->member_count++;
    
    printf("Member added successfully! Member ID: %d\n", new_member.member_id);
}

void issueBook(Library *lib) {
    int book_id, member_id;
    printf("\n=== ISSUE BOOK ===\n");
    
    printf("Enter Book ID: ");
    scanf("%d", &book_id);
    printf("Enter Member ID: ");
    scanf("%d", &member_id);
    
    // Find book
    int book_index = -1;
    for(int i = 0; i < lib->book_count; i++) {
        if(lib->books[i].book_id == book_id) {
            book_index = i;
            break;
        }
    }
    
    if(book_index == -1) {
        printf("Book not found!\n");
        return;
    }
    
    // Find member
    int member_index = -1;
    for(int i = 0; i < lib->member_count; i++) {
        if(lib->members[i].member_id == member_id && lib->members[i].is_active) {
            member_index = i;
            break;
        }
    }
    
    if(member_index == -1) {
        printf("Member not found or inactive!\n");
        return;
    }
    
    // Check availability
    if(lib->books[book_index].available_copies <= 0) {
        printf("Book not available!\n");
        return;
    }
    
    // Check if member can issue more books
    if(lib->members[member_index].books_issued >= lib->members[member_index].max_books) {
        printf("Member has reached maximum book limit!\n");
        return;
    }
    
    // Check if book is reference
    if(lib->books[book_index].is_reference) {
        printf("Reference books cannot be issued!\n");
        return;
    }
    
    // Create transaction
    Transaction new_trans;
    new_trans.transaction_id = lib->transaction_count + 1;
    new_trans.book_id = book_id;
    new_trans.member_id = member_id;
    
    getCurrentDate(new_trans.issue_date);
    
    // Set due date (15 days from issue)
    addDaysToDate(new_trans.due_date, new_trans.issue_date, 15);
    
    strcpy(new_trans.return_date, "");
    new_trans.fine_amount = 0;
    strcpy(new_trans.status, "Issued");
    
    lib->transactions[lib->transaction_count] = new_trans;
    lib->transaction_count++;
    
    // Update book and member
    lib->books[book_index].available_copies--;
    lib->members[member_index].books_issued++;
    
    printf("Book issued successfully!\n");
    printf("Transaction ID: %d\n", new_trans.transaction_id);
    printf("Due Date: %s\n", new_trans.due_date);
}

void returnBook(Library *lib) {
    int transaction_id;
    printf("\n=== RETURN BOOK ===\n");
    
    printf("Enter Transaction ID: ");
    scanf("%d", &transaction_id);
    
    // Find transaction
    int trans_index = -1;
    for(int i = 0; i < lib->transaction_count; i++) {
        if(lib->transactions[i].transaction_id == transaction_id && 
           strcmp(lib->transactions[i].status, "Issued") == 0) {
            trans_index = i;
            break;
        }
    }
    
    if(trans_index == -1) {
        printf("Transaction not found or book already returned!\n");
        return;
    }
    
    // Update transaction
    getCurrentDate(lib->transactions[trans_index].return_date);
    strcpy(lib->transactions[trans_index].status, "Returned");
    
    // Calculate fine if any
    char current_date[11];
    getCurrentDate(current_date);
    int days_overdue = dateDifference(current_date, lib->transactions[trans_index].due_date);
    
    if(days_overdue > 0) {
        lib->transactions[trans_index].fine_amount = days_overdue * 5.0; // 5 taka per day
        printf("Overdue by %d days. Fine: %.2f Taka\n", days_overdue, lib->transactions[trans_index].fine_amount);
    }
    
    // Update book and member
    for(int i = 0; i < lib->book_count; i++) {
        if(lib->books[i].book_id == lib->transactions[trans_index].book_id) {
            lib->books[i].available_copies++;
            break;
        }
    }
    
    for(int i = 0; i < lib->member_count; i++) {
        if(lib->members[i].member_id == lib->transactions[trans_index].member_id) {
            lib->members[i].books_issued--;
            break;
        }
    }
    
    printf("Book returned successfully!\n");
}

void generateReports(Library *lib) {
    printf("\n=== LIBRARY REPORTS ===\n");
    
    // Books report
    printf("\n1. BOOKS SUMMARY:\n");
    printf("Total Books: %d\n", lib->book_count);
    
    int total_copies = 0, available_copies = 0;
    for(int i = 0; i < lib->book_count; i++) {
        total_copies += lib->books[i].total_copies;
        available_copies += lib->books[i].available_copies;
    }
    printf("Total Copies: %d\n", total_copies);
    printf("Available Copies: %d\n", available_copies);
    printf("Issued Copies: %d\n", total_copies - available_copies);
    
    // Members report
    printf("\n2. MEMBERS SUMMARY:\n");
    printf("Total Members: %d\n", lib->member_count);
    
    int students = 0, faculty = 0, staff = 0;
    for(int i = 0; i < lib->member_count; i++) {
        if(strcmp(lib->members[i].type, "Student") == 0) students++;
        else if(strcmp(lib->members[i].type, "Faculty") == 0) faculty++;
        else if(strcmp(lib->members[i].type, "Staff") == 0) staff++;
    }
    printf("Students: %d\n", students);
    printf("Faculty: %d\n", faculty);
    printf("Staff: %d\n", staff);
    
    // Transactions report
    printf("\n3. TRANSACTIONS SUMMARY:\n");
    printf("Total Transactions: %d\n", lib->transaction_count);
    
    int issued = 0, returned = 0;
    float total_fine = 0;
    for(int i = 0; i < lib->transaction_count; i++) {
        if(strcmp(lib->transactions[i].status, "Issued") == 0) issued++;
        else if(strcmp(lib->transactions[i].status, "Returned") == 0) returned++;
        total_fine += lib->transactions[i].fine_amount;
    }
    printf("Currently Issued: %d\n", issued);
    printf("Returned: %d\n", returned);
    printf("Total Fine Collected: %.2f Taka\n", total_fine);
    
    // Overdue books
    printf("\n4. OVERDUE BOOKS:\n");
    char current_date[11];
    getCurrentDate(current_date);
    int overdue_count = 0;
    
    for(int i = 0; i < lib->transaction_count; i++) {
        if(strcmp(lib->transactions[i].status, "Issued") == 0) {
            if(dateDifference(current_date, lib->transactions[i].due_date) > 0) {
                overdue_count++;
                // Find book and member details
                for(int j = 0; j < lib->book_count; j++) {
                    if(lib->books[j].book_id == lib->transactions[i].book_id) {
                        for(int k = 0; k < lib->member_count; k++) {
                            if(lib->members[k].member_id == lib->transactions[i].member_id) {
                                printf("Book: %s | Member: %s | Due: %s\n", 
                                       lib->books[j].title, 
                                       lib->members[k].name,
                                       lib->transactions[i].due_date);
                                break;
                            }
                        }
                        break;
                    }
                }
            }
        }
    }
    if(overdue_count == 0) {
        printf("No overdue books!\n");
    }
}

// Utility functions
void getCurrentDate(char *date) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(date, "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
}

void addDaysToDate(char *result, char *start_date, int days) {
    struct tm tm = {0};
    sscanf(start_date, "%4d-%2d-%2d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday);
    tm.tm_year -= 1900;
    tm.tm_mon -= 1;
    
    time_t t = mktime(&tm);
    t += days * 24 * 60 * 60;
    
    struct tm *new_tm = localtime(&t);
    sprintf(result, "%04d-%02d-%02d", new_tm->tm_year + 1900, new_tm->tm_mon + 1, new_tm->tm_mday);
}

int dateDifference(char *date1, char *date2) {
    struct tm tm1 = {0}, tm2 = {0};
    sscanf(date1, "%4d-%2d-%2d", &tm1.tm_year, &tm1.tm_mon, &tm1.tm_mday);
    sscanf(date2, "%4d-%2d-%2d", &tm2.tm_year, &tm2.tm_mon, &tm2.tm_mday);
    
    tm1.tm_year -= 1900;
    tm1.tm_mon -= 1;
    tm2.tm_year -= 1900;
    tm2.tm_mon -= 1;
    
    time_t t1 = mktime(&tm1);
    time_t t2 = mktime(&tm2);
    
    return (int)difftime(t1, t2) / (60 * 60 * 24);
}

// Placeholder functions for unimplemented features
void updateBook(Library *lib) { printf("Update Book feature coming soon!\n"); }
void deleteBook(Library *lib) { printf("Delete Book feature coming soon!\n"); }
void searchMembers(Library *lib) { printf("Search Members feature coming soon!\n"); }
void viewAllMembers(Library *lib) { printf("View All Members feature coming soon!\n"); }
void updateMember(Library *lib) { printf("Update Member feature coming soon!\n"); }
void viewTransactions(Library *lib) { printf("View Transactions feature coming soon!\n"); }
void calculateFine(Library *lib) { printf("Calculate Fine feature coming soon!\n"); }

void saveData(Library *lib) {
    FILE *file = fopen("library_data.dat", "wb");
    if(file) {
        fwrite(lib, sizeof(Library), 1, file);
        fclose(file);
        printf("Data saved successfully!\n");
    } else {
        printf("Error saving data!\n");
    }
}

void loadData(Library *lib) {
    FILE *file = fopen("library_data.dat", "rb");
    if(file) {
        fread(lib, sizeof(Library), 1, file);
        fclose(file);
        printf("Data loaded successfully!\n");
    } else {
        printf("No previous data found. Starting fresh.\n");
    }
}
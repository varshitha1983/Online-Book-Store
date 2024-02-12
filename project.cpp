#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>


using namespace std;

struct details{
    std::string name;
    std::string author;
    std::string genre;
    int book_id;
    double price;
    double global_rating;


};

class Book{
    public:
    std::vector<details> books;
  
std::vector<details> readBooks(const std::string& filename)
{
   
    ifstream inFile(filename);
    if (inFile.is_open())
    {
       std::string line; 
        while (std::getline(inFile, line)) {
            details book;  
            std::istringstream iss(line);  
            
            
             if (std::getline(iss, book.name, ',') &&
                std::getline(iss, book.author, ',') &&
                std::getline(iss, book.genre, ',')) {
                
                // Extract book_id, price, and global_rating
                if (iss >> book.book_id >> std::ws &&
                    iss >> book.price >> std::ws &&
                    iss >> book.global_rating) {

                    books.push_back(book);  // Add the Book object to the vector
                } else {
                    // Extraction of book_id, price, or global_rating failed
                    std::cerr << "Error reading line (book_id, price, or global_rating): " << line << "\n";
                }
            } else {
                // Extraction of name, author, or genre failed
                std::cerr << "Error reading line (name, author, or genre): " << line << "\n";
            }
        }

        inFile.close();  // Close the file
    } else {
        std::cerr << "Error opening file: " << filename << "\n";
    }

    return books;  
}

void displayBooks(vector<details> b)
{
    cout<<setw(10)<<"Book ID"<<setw(20)<<"Name"<<setw(20)<<"Author"<<setw(20)<<"Genre"<<setw(10)<<"Price"<<setw(20)<<"Global Rating"<<endl;

    for(int i=0;i<b.size();i++)
    {
        cout<<setw(10)<<b[i].book_id<<setw(20)<<b[i].name<<setw(20)<<b[i].author<<setw(20)<<b[i].genre<<setw(10)<<b[i].price<<setw(20)<<b[i].global_rating<<endl;
    }
    //display(adm);
}


};
class administrator:public Book{
private:

public:
void add_book(string filename)
{
    details d;
    cout<<"Enter the book name:";
    std::getline(std::cin >> std::ws,d.name);
    cout<<"Enter the author of the book:";
    std::getline(std::cin >> std::ws,d.author);
    cout<<"Enter the genre:";
    std::getline(std::cin >> std::ws,d.genre);
    cout<<"Enter the book id:";
    std::cin>>d.book_id;
    cout<<"Enter the price of the book:";
    std::cin>>d.price;
    cout<<"Enter the global rating of the book:";
    std::cin>>d.global_rating;
    //books.push_back(d);


    std::ofstream outFile(filename,std::ios::app);
    outFile<<d.name<<','<<d.author<<','<<d.genre<<','<<d.book_id<<' '<<d.price<<' '<<d.global_rating<<'\n';
    outFile.close();
    

}

void outOfStock(int purchases)
{
    if(purchases == 100)
    {
        cout<<"Item is Out Of Stock"<<endl;
    }
}

void change_price(int id)
{
    if(id<=books.size())
    {
    double p;
    cout<<"Enter the changed price of the book:";
    cin>>p;
    books[id].price=p;
    cout<<"Price changed successfully!"<<endl;
    }
    else{
        cout<<"Invalid id.Please try again!"<<endl;
    }
}

void total_numberOfBooks()
{
    cout<<books.size()<<endl;
}

void clearData(string filename)
{
    std::ofstream outFile(filename,std::ios::trunc);
    outFile.close();
}
};


class user:public Book{
    public:
    void wishlist()
    {

    }
    void myCart()
    {

    }
    void myOrders()
    {

    }
    void myProfile()
    {

    }
    void exploreBooks()
    {

    }
    void myRecoms()
    {
        
    }


};

int main()
{
    Book b;
    administrator a;
    user u;
    int choice,subchoice;
    cout<<"1.User\n2.Administrator"<<endl;
    cout<<"Enter your choice:";
    cin>>choice;
    if(choice == 2){
        cout<<"Enter username and password:";
        string username,password;
        cin>>username;
        cin>>password;
        while((username != "varshitha") && (password !="abc"))
        {
            cout<<"Invalid username or password.Try again!";
        } 
        while(1)
        {
            
            cout<<"1.Add a new book\n2.Change the price of the book\n3.Display the list of the books\n4.Check total number of books\n5.Clear all the data\n6.Exit"<<endl;
            cout<<"Enter your subchoice:";
            cin>>subchoice;
            if(subchoice == 1)
            {
                a.add_book("books.txt");
                //b.readBooks("books.txt");
            }
            else if(subchoice == 2)
            {
                cout<<"Enter the the book id for which you want to change the price:";
                int id;
                cin>>id;
                a.change_price(id);
            }
            else if(subchoice == 3)
            {
                //a.add_book("books.txt");
                vector<details> allBooks=b.readBooks("books.txt");
                a.displayBooks(allBooks);
            }
            else if(subchoice == 4)
            {
                a.total_numberOfBooks();
            }
            else if(subchoice == 5)
            {
                a.clearData("books.txt");
            }
            else if(subchoice == 6)
            {
                exit(1);
            }
        }
    }
    /*a.add_book("books.txt");
    vector<details> allBooks=b.readBooks("books.txt");
    b.displayBooks(allBooks);
    //a.clearData("books.txt");*/


    return 0;
}
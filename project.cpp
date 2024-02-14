#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>


using namespace std;



//Structure for the details of each book
struct details{
    std::string name;
    std::string author;
    std::string genre;
    int book_id;
    double price;
    double global_rating;


};

//Class book which is public accessed by other classes(Public Inheritance)
class Book{
    public:
   
std::vector<details> readBooks(const std::string& filename)
{
   // books.clear();
    std::vector<details> books;
  
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
    cout<<setw(10)<<"Book ID"<<setw(50)<<"Name"<<setw(30)<<"Author"<<setw(30)<<"Genre"<<setw(10)<<"Price"<<setw(20)<<"Global Rating"<<endl;

    for(int i=0;i<b.size();i++)
    {
        cout<<setw(10)<<b[i].book_id<<setw(50)<<b[i].name<<setw(30)<<b[i].author<<setw(30)<<b[i].genre<<setw(10)<<b[i].price<<setw(20)<<b[i].global_rating<<endl;
    }
}

void clearData(string filename)
{
    std::ofstream outFile(filename,std::ios::trunc);
    outFile.close();
}



};


//Class Administrator which is useful for the administrator section

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



void change_price(int id,vector<details> allBooks)
{
    if(id<=allBooks.size())
    {
    double p;
    cout<<"Enter the changed price of the book:";
    cin>>p;
    
    allBooks[id].price=p;
    cout<<"Price changed successfully!"<<endl;
    }
    else{
        cout<<"Invalid id.Please try again!"<<endl;
    }
}

void total_numberOfBooks(vector<details> allBooks)
{
    cout<<allBooks.size()<<endl;
}



};

//Class User which is for the users

class user:public Book{
    public:
    
    void addToWishlist(vector<details> allBooks,int i )
    {
        //vector<details> wishbooks;
        //wishbooks.push_back(allBooks[i]);
        std::ofstream outFile("wishlist.txt",std::ios::app);
        outFile<<allBooks[i].name<<','<<allBooks[i].author<<','<<allBooks[i].genre<<','<<allBooks[i].book_id<<' '<<allBooks[i].price<<' '<<allBooks[i].global_rating<<'\n';
        outFile.close();


    }
    void addToCart(vector<details> allBooks,int i)
    {
        std::ofstream outFile("cart.txt",std::ios::app);
        outFile<<allBooks[i].name<<','<<allBooks[i].author<<','<<allBooks[i].genre<<','<<allBooks[i].book_id<<' '<<allBooks[i].price<<' '<<allBooks[i].global_rating<<'\n';
        outFile.close();
    }
    void myWishlist()
    {
        vector<details> wishBooks=readBooks("wishlist.txt");
        displayBooks(wishBooks);

    }
    void myCart()
    {
        vector<details> cartBooks=readBooks("cart.txt");
        displayBooks(cartBooks);
    }
    
    void exploreBooks(vector<details> allBooks)
    {
        char info;
        cout<<"Press Y if you want to add any book to your cart/wishlist\nPress N to not"<<endl;
        cin>>info;
        while((info != 'n') && (info != 'N') && (info !='Y') && (info !='y'))
        {
            cout<<"Invalid character.Please try again!"<<endl;
            cin>>info;
        }
        if((info == 'N') || (info == 'n'))
        {
            return;
        }
        else if((info == 'Y') || (info == 'y')){
            cout<<"Enter the id of the book:";
            int i;
            cin>>i;
            cout<<"Enter W to add to wishlist & Enter C to add to cart:";
            char temp;
            cin>>temp;
            while((temp!='w') && (temp!='W') && (temp!='c') && (temp!='C'))
            {
                cout<<"Invalid character.Please try again!"<<endl;
                cin>>temp;
            }
            if((temp == 'W') || (temp == 'w'))
            {
                addToWishlist(allBooks,i-1);
            }
            else {
                addToCart(allBooks,i-1);
            }
           
        }
    }
vector<details> myRecoms(vector<details> userWishlist,vector<details> library)
    {
        
        std::vector<details> recommendations;
    for (const auto& wish : userWishlist) {
        for (const auto& book : library) {
            if (book.genre == wish.genre) {
                recommendations.push_back(book);
            }
        }
    }
    return recommendations;
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
            cin>>username;
            cin>>password;
        } 
        vector<details> allBooks;
        allBooks.clear();
        allBooks=b.readBooks("books.txt");
        while(1)
        {
            
            cout<<"\n\n1.Add a new book\n2.Change the price of the book\n3.Display the list of the books\n4.Check total number of books\n5.Clear all the data\n6.Exit"<<endl;
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
                allBooks.clear();
                allBooks=b.readBooks("books.txt");
                a.change_price(id,allBooks);
            }
            else if(subchoice == 3)
            {
                //a.add_book("books.txt");
                allBooks.clear();
                allBooks=b.readBooks("books.txt");
                a.displayBooks(allBooks);
            }
            else if(subchoice == 4)
            {
                allBooks.clear();
                allBooks=b.readBooks("books.txt");
                a.total_numberOfBooks(allBooks);
            }
            else if(subchoice == 5)
            {
                a.clearData("books.txt");
            }
            else if(subchoice == 6)
            {
                exit(1);
            }
            else{
                cout<<"Invalid option.Please try again!"<<endl;
            }
        }
    }

    if(choice == 1){
        cout<<"Enter your good name:";
        string n;
        cin>>n;
        cout<<"\n\nHello "<<n<<"\nWelcome to the Book Store:)\n\n\n";
        int option;
       

        while(1){
            cout<<"1.View My Wishlist\n2.View My Cart\n3.View My Recommentations\n4.Explore books\n5.Clear Data from Wishlist or Cart\n6.Exit\n";
            cout<<"Enter your option:";
            cin>>option;
            if(option == 1){
                u.myWishlist();
            }
            else if(option == 2){
                u.myCart();
            }
            else if(option == 3){
                std::vector<details> userWishlist = u.readBooks("wishlist.txt");
                std::vector<details> library = u.readBooks("books.txt");
                std::vector<details> recommendations = u.myRecoms(userWishlist,library);
                u.displayBooks(recommendations);

            }
            else if(option == 4){
                 vector<details> allBooks=b.readBooks("books.txt");
                u.displayBooks(allBooks);
                u.exploreBooks(allBooks);

            }
            else if(option == 5)
            {
                int suboption;
                cout<<"Enter 1 to clear data from wishlist\nEnter 2 to clear data from Cart:";
                cin>>suboption;
                if(suboption == 1)
                {
                    u.clearData("wishlist.txt");
                }
                if(suboption == 2)
                {
                    u.clearData("cart.txt");
                }

            }
            else if(option == 6){
                exit(1);
            }
            else{
                cout<<"Invalid option.Please try again!"<<endl;
            }

        }

    }



    return 0;
}
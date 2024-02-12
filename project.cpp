#include <iostream>
#include <vector>
#include <string>
#include <algorithm>


using namespace std;

struct details{
    string name_of_the_book;
    string author;
    string genre;
    int book_id;
    double price;
    double global_rating;


};
class administrator{
private:
vector<details> adm;
public:
void add_book()
{
    struct details d;
    cout<<"Enter the book name: ";
    cin>>d.name_of_the_book;
    cout<<"Enter the author of the book:";
    cin>>d.author;
    cout<<"Enter the genre:";
    cin>>d.genre;
    cout<<"Enter the book id:";
    cin>>d.book_id;
    cout<<"Enter the price of the book:";
    cin>>d.price;
    cout<<"Enter the global rating of the book:";
    cin>>d.global_rating;
    adm.push_back(d);

}
void display_books()
{
    for(int i=0;i<adm.size();i++)
    {
        cout<<adm[i].name_of_the_book<<"\t"<<adm[i].author<<"\t"<<adm[i].genre<<"\t"<<adm[i].book_id<<"\t"<<adm[i].price<<"\t"<<adm[i].global_rating<<endl;
    }
    //display(adm);
}
};


int main()
{
    administrator a;
    a.add_book();
    a.display_books();


    return 0;
}
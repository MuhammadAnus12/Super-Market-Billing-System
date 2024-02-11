#include<iostream>
#include<fstream>

using namespace std;

class Node
{
public:
    int pcode;
    float price;
    float dis;
    string pname;
    Node *next;
    Node *prev;

    Node(int code, string name, float cost, float discount)
    {
        pcode = code;
        pname = name;
        price = cost;
        dis = discount;
        next = prev = NULL;
    }
};

class Shopping
{
private:
    Node *head;

public:
    Shopping()
    {
        head = NULL;
    }

    void menu();
    void administrator();
    void buyer();
    void add();
    void edit();
    void rem();
    void list();
    void receipt();
};

void Shopping::menu()
{
    m:
    int choice;
    string email;
    string password;

    cout<<"\t\t\t\t______________________________________\n";
    cout<<"\t\t\t\t                                      \n";
    cout<<"\t\t\t\t          Supermarket Main Menu       \n";
    cout<<"\t\t\t\t                                      \n";
    cout<<"\t\t\t\t______________________________________\n";
    cout<<"\t\t\t\t                                      \n";
    cout<<"\t\t\t\t|  1) Administrator   |\n";
    cout<<"\t\t\t\t|                     |\n";
    cout<<"\t\t\t\t|  2) Buyer           |\n";
    cout<<"\t\t\t\t|                     |\n";
    cout<<"\t\t\t\t|  3) Exit            |\n";
    cout<<"\t\t\t\t|                     |\n";
    cout<<"\n\t\t\t Please select!";
    cin>>choice;

    switch(choice)
    {
        case 1:
            cout<<"\t\t\t Please Login \n";
            cout<<"\t\t\t Enter Email   \n";
            cin>>email;
            cout<<"\t\t\t Password       \n";
            cin>>password;

            if(email=="admin@gmail.com" && password=="admin")
            {
                administrator();
            }
            else
            {
                cout<<"Invalid email/password";
            }
            break;


        case 2:
        {
            buyer();
            break;
        }

        case 3:
        {
            exit(0);
        }

        default :
        {
            cout<< "Please select from the given options";

        }

    }
    goto m;
}

void Shopping::administrator()
{
    m:
    int choice;
    cout<<"\n\n\n\t\t\t Administrator menu";
    cout<<"\n\t\t\t|_____1) Add the product_____|";
    cout<<"\n\t\t\t|                            |";
    cout<<"\n\t\t\t|_____2) Modify the product__|";
    cout<<"\n\t\t\t|                            |";
    cout<<"\n\t\t\t|_____3) Delete the product__|";
    cout<<"\n\t\t\t|                            |";
    cout<<"\n\t\t\t|_____4) Back to main menu___|";

    cout<<"\n\n\t Please enter your choice ";
    cin>>choice;

    switch(choice)
    {
        case 1:
            add();
            break;

        case 2:
            edit();
            break;

        case 3:
            rem();
            break;

        case 4:
            menu();
            break;

        default :
            cout<<"Invalid choice!";

    }
    goto m;
}

void Shopping::buyer()
{
    m:
    int choice;
    cout<<"\t\t\t  Buyer \n";
    cout<<"\t\t\t_____________  \n";
    cout<<"                     \n";
    cout<<"\t\t\t1) Buy product \n";
    cout<<"                     \n";
    cout<<"\t\t\t2) Go back     \n";
    cout<<"\t\t\t Enter your choice : ";

    cin>>choice;

    switch(choice)
    {
        case 1:
            receipt();
            break;

        case 2:
            menu();

        default :

            cout<<"invalid choice";

    }

    goto m;


}

void Shopping::add()
{
    fstream data;
    int token = 0;
    int pcode;
    float p;
    float d;
    string n;

    cout << "\n\n\t\t\t Add new product";
    cout << "\n\n\t Product code of the product ";
    cin >> pcode;

    // Check if the product code already exists
    Node *current = head;
    while (current)
    {
        if (current->pcode == pcode)
        {
            token++;
            break;
        }
        current = current->next;
    }

    if (token > 0)
    {
        cout << "\n Product with the same code already exists. Please choose a different code.\n";
        return;
    }

    cout << "\n\n\t Name of the product ";
    cin >> n;
    cout << "\n\n\t Price of the product";
    cin >> p;
    cout << "\n\n\t Discount on product";
    cin >> d;

    Node *newNode = new Node(pcode, n, p, d);

    if (!head)
    {
        head = newNode;
    }
    else
    {
        current = head;
        while (current->next)
        {
            current = current->next;
        }
        current->next = newNode;
        newNode->prev = current;
    }

    data.open("database.txt", ios::app | ios::out);
    data << " " << pcode << " " << n << " " << p << " " << d << "\n";
    data.close();

    cout << "\n\n\t\t Record inserted !";
}


void Shopping::edit()
{
    fstream data, data1;
    int pkey;
    int token = 0;
    int c;
    float p;
    float d;
    string n;

    cout<<"\n\t\t\t Modify the record";
    cout<<"\n\t\t\t Product code :";
    cin>>pkey;

    data.open("database.txt",ios::in);
    if (!data)
    {
        cout<<"\n\nFile doesn't exist! ";
    }
    else
    {

        data1.open("database1.txt", ios::app|ios::out);

        Node *current = head;

        while (current)
        {
            if (pkey == current->pcode)
            {
                cout<<"\n\t\t Product new code :";
                cin>>c;
                cout<<"\n\t\t Name of the product :";
                cin>>n;
                cout<<"\n\t\t Price :";
                cin>>p;
                cout<<"\n\t\t Discount :";
                cin>>d;

                current->pcode = c;
                current->pname = n;
                current->price = p;
                current->dis = d;

                data1<<" "<<c<<" "<<n<<" "<<p<<" "<<d<<"\n";
                cout<<"\n\n\t\t Record edited ";
                token++;
            }
            else
            {
                data1<<" "<<current->pcode<<" "<<current->pname<<" "<<current->price<<" "<<current->dis<<"\n";
            }
            current = current->next;
        }

        data.close();
        data1.close();

        remove("database.txt");
        rename("database1.txt", "database.txt");

        if (token == 0)
        {
            cout<<"\n\n Record not found sorry!";
        }
    }
}

void Shopping::rem()
{
    fstream data, data1;
    int pkey;
    int token = 0;
    cout<<"\n\n\t Delete product";
    cout<<"\n\n\t Product code :";
    cin>>pkey;
    data.open("database.txt", ios::in);
    if (!data)
    {
        cout<<"File doesnt exist";
    }
    else
    {
        data1.open("database1.txt",ios::app|ios::out);

        Node *current = head;

        while (current)
        {
            if (current->pcode == pkey)
            {
                cout<<"\n\n\t Product deleted successfully";
                token++;
            }
            else
            {
                data1<<" "<<current->pcode<<" "<<current->pname<<" "<<current->price<<" "<<current->dis<<"\n";
            }
            current = current->next;
        }

        data.close();
        data1.close();
        remove("database.txt");
        rename("database1.txt","database.txt");

        if (token == 0)
        {
            cout<<"\n\n Record not found";
        }
    }
}

void Shopping::list()
{
    Node *current = head;

    cout<<"\n\n|___________________________________________________________\n";
    cout<<"ProNo\t\tName\t\tPrice\n";
    cout<<"\n\n|___________________________________________________________\n";

    while (current)
    {
        cout<<current->pcode<<"\t\t"<<current->pname<<"\t\t"<<current->price<<"\n";
        current = current->next;
    }
}

void Shopping::receipt()
{
    system("cls");
    fstream data;

    int arrc[100], arrq[100];
    char choice;
    int c=0;
    float amount=0;
    float discount=0;
    float total=0;

    cout<<"\n\n\t\t\t Receipt ";
    data.open("database.txt",ios::in);
    if (!data)
    {
        cout<<"\n\n Empty database";
    }
    else
    {
        data.close();
        list();
        cout<<"\n____________________________\n";
        cout<<"\n|                            |";
        cout<<"\n|    Please place the order  |";
        cout<<"\n|____________________________|\n";
        do
        {
            m:
            cout<<"\n\n Product Code : ";
            cin>>arrc[c];
            cout<<"\n Product Quantity : ";
            cin>>arrq[c];
            for (int i=0; i<c; i++)
            {
                if (arrc[c] == arrc[i])
                {
                    cout<<"\n\n Duplicate Product Code. Please try again!";
                    goto m;
                }
            }
            c++;
            cout<<"\n\n Want to buy another product? Press y for yes and n for no : ";
            cin>>choice;
        }

        while(choice == 'y');
        system("cls");

        cout<<"\n\n\t\t\t__________RECEIPT______________\n";
        cout<<"\nProduct Num.\tProduct Name\tQuantity \tPrice \tAmount \tAmount with discount\n";

        Node *current = head;

        for(int i=0; i<c; i++)
        {
            while (current)
            {
                if (current->pcode == arrc[i])
                {
                    amount = current->price * arrq[i];
                    discount = amount - (amount * current->dis / 100);
                    total += discount;
                    cout<<"\n"<<current->pcode<<"\t\t"<<current->pname<<"\t\t"<<arrq[i]<<"\t\t"<<current->price
                        <<"\t"<<amount<<"\t\t"<<discount;
                }
                current = current->next;
            }
            current = head;  // Resetting the pointer to the head for the next iteration
        }

        cout<<"\n\n----------------------------------------";
        cout<<"\n Total Amount : "<<total;
    }
}

int main()
{
    Shopping s;
    s.menu();
    return 0;
}

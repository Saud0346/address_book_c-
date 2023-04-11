#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

class B_tree
{
public:
    string data;
    B_tree *left, *right;
};

class contact
{
    string name, address, email, phone_number;

public:
    void set_name(string name)
    {
        this->name = name;
    }
    string get_name()
    {
        return name;
    }

    void set_address(string address)
    {
        this->address = address;
    }
    string get_address()
    {
        return address;
    }

    void set_email(string email)
    {
        this->email = email;
    }
    string get_email()
    {
        return email;
    }

    void set_phone_number(string phone_number)
    {
        this->phone_number = phone_number;
    }
    string get_phone_number()
    {
        return phone_number;
    }

    B_tree *create_B_tree(B_tree *root, string data)
    {
        root = new B_tree;
        root->data = data;
        root->left = root->right = NULL;

        return root;
    }

    // This function inserts data in the tree
    B_tree *insert(B_tree *root, string data)
    {
        if (root == NULL)
            return create_B_tree(root, data);

        else if (root->data >= data)
            root->left = insert(root->left, data);
        else
            root->right = insert(root->right, data);

        return root;
    }

    // This function is called inside delete_element and update_element functions
    void add_updated_data_to_file(B_tree *root, ofstream &file)
    {
        if (root == NULL)
            return;
        add_updated_data_to_file(root->left, file);
        file << root->data << "\n";
        add_updated_data_to_file(root->right, file);
    }

    void show_data(B_tree *root)
    {
        if (root == NULL)
            return;
        show_data(root->left);
        cout << root->data << endl;
        show_data(root->right);
    }

    // Find menimum (This is used in the delete_element function)
    B_tree *find_min(B_tree *root)
    {
        while (root->left != NULL)
        {
            root = root->left;
        }

        return root;
    }

    // update a specific data of file
    B_tree *update_element(B_tree *root, string data)
    {
        if (root->data > data)
            root->left = update_element(root->left, data);
        else if (root->data < data)
            root->right = update_element(root->right, data);
        else if (root->data == data)
        {
            cout << "Enter new data you want to add " << endl;
            getline(cin, data);
            root->data = data;
        }

        // This piece of code delete all the data of file
        ofstream file1("example.txt", ios_base::trunc);
        file1.close();

        // This fun add the updated data to file
        ofstream file2("example.txt", ios_base::app);
        add_updated_data_to_file(root, file2);
        file2.close();

        return root;
    }

    // delete a specific data from file
    B_tree *delete_element(B_tree *root, string data)
    {
        if (root->data > data)
            root->left = delete_element(root->left, data);
        else if (root->data < data)
            root->right = delete_element(root->right, data);
        else if (root->data == data)
        {
            if (root->left == NULL && root->right == NULL)
            {
                B_tree *temp = new B_tree;
                temp = root;
                root = NULL;
                delete temp;
            }

            else if (root->left == NULL)
            {
                B_tree *temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == NULL)
            {
                B_tree *temp = root->left;
                delete root;
                return temp;
            }

            else if (root->left != NULL && root->right != NULL)
            {
                B_tree *temp = find_min(root->right);
                root->data = temp->data;
                root->right = delete_element(root->right, root->data);
            }
        }

        return root;
    }

    // Store data of file in a binary tree
    B_tree *file_to_tree()
    {
        B_tree *root = NULL;

        string data;

        ifstream file("example.txt");
        if (!file.is_open())
        {
            cerr << "Failed to open file." << endl;
            return 0;
        }
        string line;
        while (getline(file, line))
        {
            root = insert(root, line);
        }
        file.close(); // Close the file
        return root;
    }

    // Append / add to file
    void Append()
    {
        contact obj;
        ofstream file;
        string data;

        file.open("example.txt", ios_base::app); // append mode

        cout << "Enter Name: ";
        getline(cin, data);
        obj.set_name(data);

        cout << "Enter Address: ";
        getline(cin, data);
        obj.set_address(data);

        cout << "Enter Phone Number: ";
        getline(cin, data);
        obj.set_phone_number(data);

        cout << "Enter Email: ";
        getline(cin, data);
        obj.set_email(data);

        file << obj.get_name() << "," << obj.get_address() << "," << obj.get_phone_number() << "," << obj.get_email() << "\n";
        file.close();
    }

    

    B_tree *searching(B_tree *root, string data)
    {
        B_tree obj;
        if (root->data > data)
            root->left = searching(root->left, data);
        else if (root->data < data)
            root->right = searching(root->right, data);
        else if (root->data == data)
        {
            
            cout << "Search successful " << endl;
            return 0;
            
        }
        else if(root->left == NULL && root->right == NULL)
        cout << "Not found " << endl;

        
    }
};

int main()
{
    contact obj;
    B_tree *root = NULL;
    string data;
    int choice = 0;
    root = obj.file_to_tree();
    system("CLS");
    while (true)
    {

        cout << "<< 1 for adding data >> " << endl;
        cout << "<< 2 for deleting    >> " << endl;
        cout << "<< 3 for updating    >> " << endl;
        cout << "<< 4 for showing     >> " << endl;
        cout << "<< 5 for searching   >> " << endl;
        cout << "<< 6 to exit         >> " << endl;
        cin >> choice;
        cin.ignore();
        switch (choice)
        {
        case 1:
        {
            obj.Append();
            break;
        }
        case 2:
        {
            cout << "Enter which data you want to delete " << endl;
            getline(cin, data);
            root = obj.delete_element(root, data);

            // This piece of code delete all the data of file
            ofstream file1("example.txt", ios_base::trunc);
            file1.close();

            // This fun add the updated data to file
            ofstream file2("example.txt", ios_base::app);
            obj.add_updated_data_to_file(root, file2);
            file2.close();

            break;
        }
        case 3:
        {
            cout << "Enter which data you want to update " << endl;
            getline(cin, data);
            root = obj.update_element(root, data);
            break;
        }
        case 4:
        {
            obj.show_data(root);
            break;
        }
        case 5:
        {
            cout << "Enter data you want to search " << endl;
            getline(cin, data);
            obj.searching(root, data);
            break;
        }
        case 6:
        {
            exit(0);
            break;
        }
        }
    }

    return 0;
}
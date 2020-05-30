#include <iostream>

using namespace std;
const int sizeofword = 20;

void print_arr(char* arr) 
{
    int index = 0;
    while (index < sizeofword && arr[index] != '\0') 
    {
        cout << arr[index];
        index++;
    }

}

void copy_arr(char* first, char* next) 
{
    for (int i = 0; i < sizeofword; i++)
    {
        first[i] = next[i];
    }
}

struct node 
{
    char eng[sizeofword];
    char ukr[sizeofword];
    int count = 0;

    node(char* en, char* uk)
    {
        copy_arr(en, eng);
        copy_arr(uk, ukr);
    }

    node(char* en, char* uk, int n)
    {
        copy_arr(en, eng);
        copy_arr(uk, ukr);
        count = n;
    }

    node* left = nullptr;
    node* right = nullptr;

    int equals(node* elem) 
    {
        if (elem == nullptr) return 0;

        for (int i = 0; i < sizeofword; i++)
        {
            if (elem->eng[i] == '\0' && eng[i] == '\0') 
                return 0;
            if (eng[i] > elem->eng[i] || elem->eng[i] == '\0') 
                return -1;
            if (eng[i] < elem->eng[i] || eng[i] == '\0') 
                return 1;
        }
        return 0;
    }

    int equals_by_count(node* elem) 
    {
        if (elem == nullptr) 
            return 0;
        if (elem->count < count) 
            return -1;
        else if (elem->count > count) 
            return 1;
        else 
        {
            for (int i = 0; i < sizeofword; i++)
            {
                if (elem->eng[i] == '\0' && eng[i] == '\0') 
                    return 0;
                if (eng[i] > elem->eng[i] || elem->eng[i] == '\0') 
                    return -1;
                if (eng[i] < elem->eng[i] || eng[i] == '\0') 
                    return 1;
            }
            return 0;
        }
    }

    int same(char* unit) 
    {
        for (int i = 0; i < sizeofword; i++) 
        {
            if (unit[i] == '\0' && eng[i] == '\0')
                return 0;
            if (eng[i] > unit[i] || unit[i] == '\0') 
                return -1;
            if (eng[i] < unit[i] || eng[i] == '\0') 
                return 1;
        }
        return 0;
    };
};

static int index = 0;

struct tree {
    node* head = nullptr;
    node* flow_head = nullptr;
    int size = 0;

    void add(node* elem) 
    {
        add(elem, false);
    }

    void get(char* unit) 
    {
        flow_head = head;

        while (true) 
        {
            if (flow_head->equals(unit) == 0) 
            {
                flow_head->count++;
                print_arr(flow_head->ukr);
                cout << endl;
                break;
            }
            else if (flow_head->equals(unit) == -1) 
            {
                if (flow_head->left == nullptr)
                {
                    cout << "not exist" << endl;
                    break;
                }
                else flow_head = flow_head->left;
            }
            else 
            {
                if (flow_head->right == nullptr)
                {
                    cout << "not exist" << endl;
                    break;
                }
                else flow_head = flow_head->right;
            }
        }
    }

    node** get_array()
    {
        index = 0;
        node** arr = new node * [size];
        point_at(head, arr);
        return arr;
    }

    void value()
    {
        node** arr = get_array();
        sort(arr, size);
        head = nullptr;
        int pr_size = size;
        for (int i = 0; i < pr_size; i++) 
            add(arr[i], true);
        size = pr_size;
    }

    void print() 
    {
        if (head != nullptr) print(head, 0);
        else 
            cout << "NULL" << endl;
    }

private:
    void add(node* elem, bool flag) 
    {
        size++;
        elem->left = nullptr;
        elem->right = nullptr;
        if (head == nullptr) 
        {
            head = elem;
        }
        else {
            flow_head = head;

            if (flag) 
            {
                while (true)
                {
                    if (flow_head->equals_by_count(elem) == -1) 
                    {
                        if (flow_head->left == nullptr) 
                        {
                            flow_head->left = elem;
                            break;
                        }
                        else local_head = local_head->left;
                    }
                    else 
                    {
                        if (flow_head->right == nullptr)
                        {
                            flow_head->right = elem;
                            break;
                        }
                        else flow_head = flow_head->right;
                    }
                }
            }
            else 
            {
                while (true)
                {
                    if (flow_head->equals(elem) == -1)
                    {
                        if (flow_head->left == nullptr) 
                        {
                            flow_head->left = elem;
                            break;
                        }
                        else flow_head = flow_head->left;
                    }
                    else 
                    {
                        if (flow_head->right == nullptr)
                        {
                            flow_head->right = elem;
                            break;
                        }
                        else flow_head = flow_head->right;
                    }
                }
            }
        }
    }

    void print(node* elem, int a) 
    {
        cout << '{' << endl;
        for (int i = 0; i <= a; i++) 
            cout << '\t';
        cout << "eng = ";
        print_arr(elem->eng);
        cout << endl;

        for (int i = 0; i <= a; i++)
            cout << '\t';
        cout << "ukr = ";
        print_arr(elem->ukr);
        cout << endl;

        for (int i = 0; i <= a; i++) 
            cout << '\t';
        cout << "count = " << elem->count << endl;

        if (elem->left != nullptr) 
        {
            cout << endl;
            for (int i = 0; i <= a; i++) 
                cout << '\t';
            cout << "left = ";
            print(elem->left, a + 1);
        }
        if (elem->right != nullptr)
        {
            cout << endl;
            for (int i = 0; i <= a; i++) 
                cout << '\t';
            cout << "right = ";
            print(elem->right, a + 1);
        }
        for (int i = 0; i < a; i++) 
            cout << '\t';
        cout << '}' << endl;
    }

    void point_at(node* elem, node** arr) 
    {
        arr[index] = elem;
        index++;
        if (elem->left != nullptr) point_at(elem->left, arr);
        if (elem->right != nullptr) point_at(elem->right, arr);
    }

    void sort(node** arr, int size)
    {
        for (int k = 1; k < size; k++) 
        {
            for (int i = 0; i < size - k; i++) 
            {
                if (arr[i]->count < arr[i + 1]->count) swap(arr[i], arr[i + 1]);
            }
        }
    }
};

void console_window() 
{
    tree tree;
    char eng[sizeofword];
    char ukr[sizeofword];
    int counter;

    const char* message_help = 
        "----------------------------------------\n"

        "n - add new word\n"

        "g - receive translation in English\n"

        "p - print tree\n"

        "s - to simplify a tree\n"

        "x - exit\n"

        "----------------------------------------";

    const char* message_eng = "Enter the word in English: ";

    const char* message_ukr = "Enter the word in Ukrainian: ";

    const char* message_count = "Enter the number of call to word: "
        ;
    const char* message_translate = "Your word in Ukrainian: ";

    const char* message_print = "Your tree: ";

    const char* message_sort = "Íour tree is forgiven";

    char one;

    while (true) 
    {
        cout << message_help << endl;
        cin >> one;

        if (one == 'n')
        {
            cout << message_eng << endl;
            cin.get();
            cin.getline(eng, sizeofword);
            cout << message_ukr << endl;
            cin.getline(ukr, sizeofword);
            cout << message_count << endl;
            cin >> counter;
            tree.add(new node(eng, ukr, counter));
        }
        else if (one == 'g') 
        {
            cout << message_eng << endl;
            cin.get();
            cin.getline(eng, sizeofword);
            cout << message_translate << endl;
            tree.get(eng);
        }
        else if (one == 'p') 
        {
            cout << message_print << endl;
            tree.print();
        }
        else if (one == 's')
        {
            tree.value();
            cout << message_sort << endl;
        }
        else return;
    }
}

int main()
{
    console_window();
    return 0;
}
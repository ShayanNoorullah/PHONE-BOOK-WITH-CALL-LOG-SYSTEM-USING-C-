#include <iostream>
#include <fstream>
#include <string>
#include <queue>
using namespace std;

struct Contact
{
public:
    char key;
    string name;
    long long phone;
    string email;
    string address;
    Contact* next;
public:
    Contact() : phone(0)
    {
        key = '\0';
        name = "";
        email = "";
        address = "";
        next = NULL;
    }
    Contact(long long p, char k, string n, string e, string a) : phone(p)
    {
        key = k;
        name = n;
        email = e;
        address = a;
        next = NULL;
    }
};

class PhoneBook
{
public:
    static const int size = 26;
    Contact* Phonetable[size];

public:
    PhoneBook()
    {
        char c;
        int index;
        for (int i = 0; i < size; i++)
        {
            Phonetable[i] = new Contact();
        }
        for (c = 'A'; c <= 'Z'; c++)
        {
            index = hashfunc(c);
            Phonetable[index]->key = c;
        }
        FILE* fptr = fopen("phonebook.txt", "r");
        if (fptr == NULL)
        {
            printf("file does not exist");
            exit(1);
        }
        char str[100], str2[100], str3[100];
        Contact nn;
        long long vv;
        fseek(fptr, 0, SEEK_SET);
        while (!feof(fptr))
        {
            fscanf(fptr, "%llu %[^\n]s\n", &vv, str);
            nn.phone = vv;
            nn.name = str;
            fscanf(fptr, "%s\n", str2);
            nn.email = str2;
            fscanf(fptr, "%[^\n]s\n", str3);
            nn.address = str3;
            if (numcheck(nn.phone))
            {
                char a = nn.name[0];
                int ind = find(a);
                Contact* newc = new Contact(nn.phone, ind, nn.name, nn.email, nn.address);
                Contact* t = Phonetable[ind]->next;
                Phonetable[ind]->next = newc;
                newc->next = t;
            }
        }
        fclose(fptr);
    }

    int hashfunc(char c)
    {
        c = toupper(c);
        if (c >= 'A' && c <= 'Z')
        {
            return c - 'A';
        }
        else
        {
            return -1;
        }
    }

    bool numcheck(long long p)
    {
        for (int i = 0; i < size; i++)
        {
            Contact* temp = Phonetable[i]->next;
            while (temp != NULL)
            {
                if (temp->phone == p)
                {
                    return false;
                }
                temp = temp->next;
            }
        }
        return true;
    }

    int countDigit(long long n)
    {
        if (n == 0) return 1;
        int count = 1;
        while (n != 0)
        {
            count++;
            n = n / 10;
        }

        return count;
    }

    void ADD_TO_CONTACTS(string n, long long p, string e, string a)
    {
        if (!numcheck(p))
        {
            // cout << "this number already exists" << endl;
            return;
        }
        FILE* fptr = fopen("phonebook.txt", "r");
        FILE* fptr2 = fopen("separate.txt", "w");
        if (fptr == NULL || fptr2 == NULL)
        {
            printf("file does not exist");
            exit(1);
        }

        char x = n[0];
        int index = find(x);
        Contact* newcontact = new Contact(p, index, n, e, a);
        Contact* temp = Phonetable[index]->next;
        Phonetable[index]->next = newcontact;
        newcontact->next = temp;
        checksort(true, index);
        char* s1;
        char* s2;
        char* s3;
        long long gg;
        for (int i = 0; i < size; i++)
        {
            Contact* temp = Phonetable[i]->next;
            while (temp != NULL)
            {
                s1 = &temp->name[0];
                s2 = &temp->email[0];
                s3 = &temp->address[0];
                gg = temp->phone;
                temp = temp->next;
                fprintf(fptr2, "%llu %s\n%s\n%s\n", gg, s1, s2, s3);
            }
        }
        fclose(fptr);
        fclose(fptr2);
        remove("phonebook.txt");
        rename("separate.txt", "phonebook.txt");
    }

    int find(char x)
    {
        x = toupper(x);
        for (int i = 0; i < size; i++)
        {
            if (Phonetable[i]->key == x)
            {
                return i;
            }
        }
        return -1;
    }

    bool Sort(int index)
    {
        Contact* temp = Phonetable[index];
        if (temp->next == NULL || temp->next->next == NULL)
        {
            return false;
        }
        temp = temp->next;
        while (temp->next != NULL)
        {
            if (temp->name > temp->next->name)
            {
                Swap(temp, temp->next);
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    void checksort(bool check, int index)
    {
        if (check == false)
        {
            return;
        }
        check = Sort(index);
        checksort(check, index);
    }

    void Swap(Contact* temp, Contact* temp2)
    {
        Contact* prev = temp;
        Contact* curr = temp2;
        Contact* nextt = curr->next;
        prev->next = nextt;
        curr->next = nextt->next;
        nextt->next = curr;
        return;
    }
void print()
    {
    	cout << endl << "PHONEBOOK RECORDS: " << endl;   
        for (int i = 0; i < size; i++) {
            Contact* temp = Phonetable[i]->next;         
            while (temp != NULL) {
	        	cout << "NAME: " << temp->name << " | PHONENUMBER: " << temp->phone  << " | EMAIL: " <<  temp->email<<" | ADDRESS: " << temp->address << endl;
//              cout << temp->name << ", " << temp->phone << ", " << temp->email << ", " << temp->address << endl;
                temp = temp->next;
            }
            
        }
    }

	void print_at_Alphabet(char c)
	    {
	    	cout << endl;
	    	char x = toupper(c);
	        for (int i = 0; i < size; i++)
	        {
	            if (Phonetable[i]->key == c || Phonetable[i]->key == x)
	            {
	                cout << "PHONEBOOK RECORDS STATING WITH " << Phonetable[i]->key << ": " << endl;
	                Contact* temp = Phonetable[i]->next;
	                while (temp != NULL)
	                {
	                	cout << "NAME: " << temp->name << " | PHONENUMBER: " << temp->phone  << " | EMAIL: " <<  temp->email<<" | ADDRESS: " << temp->address << endl;
//	                    cout << temp->name << ", " << temp->phone << ", " << temp->email << ", " << temp->address << endl;
	                    temp = temp->next;
	                }
	                cout << endl;
	            }
	        }
	    }
	
    bool containletters(string input, string s){
    	bool check;
    	for(int i=0;i<s.length();i++){
    		check=false;
    		for(int j=0;j<input.length();j++){
    			if(s[i]==input[j]){
    				check=true;
				}
			}
			if(check==false){
				return false;
			}
		}
		return true;
	}
	
    void Search(string n){
    	n[0] = toupper(n[0]);
    	char x=n[0];
    	int index=find(x);
    	cout << "CONTACTS SEARCHED FOR: " << endl;
    	Contact* temp = Phonetable[index]->next;
        while (temp != NULL)
        {   
            if(containletters(temp->name,n)){
                cout << temp->name << ", " << temp->phone << ", " << temp->email << ", " << temp->address << endl;
            }
            temp = temp->next;
        }
        cout << endl; 
	}
	
	
    void deletion(string n)
    {
        char x = n[0];
        int index = find(x);
        Contact* temp = Phonetable[index]->next;
        if (temp->name == n)
        {
            Phonetable[index]->next = temp->next;
            goto check;
        }
        while (temp->next->name != n)
        {
            temp = temp->next;
        }
        temp->next = temp->next->next;
    check:
        FILE* fptr = fopen("phonebook.txt", "r");
        FILE* fptr2 = fopen("separate.txt", "w");
        if (fptr == NULL || fptr2 == NULL)
        {
            printf("file does not exist");
            exit(1);
        }
        char* s1;
        char* s2;
        char* s3;
        long long gg;
        for (int i = 0; i < size; i++) {
            Contact* temp = Phonetable[i]->next;
            while (temp != NULL) {
                s1 = &temp->name[0];
                s2 = &temp->email[0];
                s3 = &temp->address[0];
                gg = temp->phone;
                temp = temp->next;
                fprintf(fptr2, "%llu %s\n%s\n%s\n", gg, s1, s2, s3);
            }
        }
        fclose(fptr);
        fclose(fptr2);
        remove("phonebook.txt");
        rename("separate.txt", "phonebook.txt");
        return;
    }

    Contact* editing(string y)
    {
        char x = y[0];
        int option, index = find(x);
        Contact* temp = Phonetable[index]->next;
        while (temp->name != y)
        {
            temp = temp->next;
        }
        string n = temp->name, e = temp->email, a = temp->address;
        long long p = temp->phone;
        cout << "enter what you want to update?" << endl;
        cout << "1 for name,2 for phone number,3 for email and 4 for address" << endl;
        cin >> option;
        switch (option)
        {
        case 1:
            cin.ignore();
            cout << "enter name:" << endl;
            getline(cin, n);
            break;
        case 2:
            cout << "enter phone:" << endl;
            cin >> p;
            if (numcheck(p))
            {
                if (countDigit(p) != 11)
                {
                    cout << "the number should be 11 digits" << endl;
                    cout << "enter phone number:";
                    cin >> p;
                }
            }
            else
            {
                cout << "phone number already exists" << endl;
                return temp;
            }
            break;
        case 3:
            cout << "enter email:" << endl;
            cin.ignore();
            getline(cin, e);
            break;
        case 4:
            cin.ignore();
            cout << "enter address:" << endl;
            getline(cin, a);
            break;
        }
        deletion(y);
        ADD_TO_CONTACTS(n, p, e, a);
        Contact* newc = new Contact(p, find(n[0]), n, e, a);
        return newc;
    }
    Contact* findcontact(string n)
    {
        char x = n[0];
        int index = find(x);
        Contact* temp = Phonetable[index]->next;
        while (temp->name != n)
        {
            temp = temp->next;
        }
        return temp;
    }
};

class Date
{
public:
    int day;
    int month;
    int year;
public:
    Date()
    {
        day = 0;
        month = 0;
        year = 0;
    }
    Date(int d, int m, int y)
    {
        day = d;
        month = m;
        year = y;
    }
    void d_append(int d, int m, int y)
    {
        day = d;
        month = m;
        year = y;
    }
};

class Time
{
public:
    int hour;
    int minute;
    Time()
    {
        hour = 0;
        minute = 0;
    }
    Time(int h, int m)
    {
        hour = h;
        minute = m;
    }
};

class Duration{
	public:
    int ho;
    int min;
    int sec;
    Duration()
    {
        ho = 0;
        min = 0;
        sec = 0;
    }
    Duration(int h, int m, int s)
    {
        ho = h;
        min = m;
        sec = s;
    }
};


class Calllog
{
public:
    Date date;
    Time time;
    Duration duration;
    int checkvalue;
    Contact* contact;
    Calllog* right;
public:
    Calllog()
    {
        right = NULL;
        checkvalue = 0;
    }
    Calllog(int dh, int dm, int ds, int h, int m, int d, int mon, int y, int ch, Contact*& c) :time(h, m), date(d, mon, y), duration(dh, dm, ds)
    {
        contact = c;
        right = NULL;
        checkvalue = ch;
    }
};

class Queue{
	public:
	Calllog *front;
	Calllog *rear;
	Queue(){
		front=NULL;
		rear=NULL;
	}
	
	void enqueue(Calllog *newnode){
		if(front==NULL){
			front=newnode;
			rear=newnode;
		}
		else{
			rear->right=newnode;
			rear=rear->right;
		}
	}
	
	void dequeue(){
		if(front==rear){
			front=NULL;
			rear=NULL;
		}
		else{
		    front=front->right;	
		}
	}
	
	void print(){
		Calllog * temp = front;
		while(temp!=NULL){
		    cout << "NAME: " << temp->contact->name << " | START TIME(HR:MIN): " << temp->time.hour << ":" << temp->time.minute << " | DATE(DD/MM/YYYY):" <<  temp->date.day << "/" 
			<< temp->date.month << "/" << temp->date.year <<  " | DURATION(HR:MIN:SEC) : " << temp->duration.ho << ":" << temp->duration.min << ":" << temp->duration.sec  << " | TYPE: " << (temp->checkvalue == 0? "INCOMING" : "OUTGOING" ) << endl;
			temp = temp->right;
		}
	}
	
};

class User
{
private:
    PhoneBook P;
    Calllog* head;
public:
    User()
    {
        head = NULL;
        FILE* fptr = fopen("call_log.txt", "r");
        if (fptr == NULL)
        {
            printf("file does not exist");
            exit(1);
        }
        int dh, dm, ds, dd, mm, yy, hh, mi, du, chh;
        char s1[100];
        Contact c;
        fseek(fptr, 0, SEEK_SET);
        while (!feof(fptr))
        {
            fscanf(fptr, "%d %d %d %d %d %d %d %d %d %[^\n]s\n", &dd, &mm, &yy, &hh, &mi,&dh, &dm, &ds, &chh, s1);
            c.name = s1;
            Contact* temp = P.findcontact(c.name);
            Calllog* newcalllog = new Calllog(dh, dm, ds, hh, mi, dd, mm, yy, chh, temp);
            if (head == NULL)
            {
                head = newcalllog;
            }
            else
            {
                Calllog* temp = head;
                while (temp->right != NULL) {
                    temp = temp->right;
                }
                temp->right = newcalllog;
            }
        }
        fclose(fptr);
        Calllog* temp = head;
        while (temp->right->right != NULL)
        {
            temp = temp->right;
        }
        temp->right = NULL;
    }
    private:
    int countDigit(long long n)
    {
        if (n == 0)
            return 1;
        int count = 1;
        while (n != 0) {
            n = n / 10;
            count++;
        }
        return count;
    }

    void input(int dh, int dm, int ds, int h, int d, int m, int mon, int y, int ch, Contact* c)
    {
        string n, e, a;
        long long p;
        cout << "Enter Name:";
        getline(cin, n);
        cout << endl;
        cout << "Enter Phone Number:";
        cin >> p;
        if (countDigit(p) != 11)
        {
            cout << "The Number Should BE 11 Digits" << endl;
            cout << "Enter Phone Number:";
            cin >> p;
        }
        cin.ignore();
        cout << "Enter Email:";
        getline(cin, e);
        cout << "Enter Address:";
        cin.ignore();
        getline(cin, a);
        P.ADD_TO_CONTACTS(n, p, e, a);
        char x = n[0];
        int index = P.find(x);
        Contact* newcontact = new Contact(p, index, n, e, a);
        ADD_TO_LOG(dh, dm, ds, h, d, m, mon, y, ch, newcontact);
    }

    void outgoing()
    {
        int dh, dm, ds, d, m, y, h, mon, s;
        string n;
        cout << "Enter Date Information:" ;
        cout << "Enter day:";
        cin >> d;
        cout << endl;
        cout << "Enter Month: ";
        cin >> mon;
        cout << endl;
        cout << "Enter Year: ";
        cin >> y;
        cout << endl;
        cout << "Enter Time Information:";
        cout << "Enter Hour:";
        cin >> h;
        cout << endl;
        cout << "Enter Minute:";
        cin >> m;
        cout << endl;
        cout << "Enter Duration Information:" << endl;
        cout << "Enter Hour:";
        cin >> dh;
        cout << endl;
        cout << "Enter Minute:";
        cin >> dm;
        cout << endl;
        cout << "Enter Seconds:";
        cin >> ds;
        cout << endl;
        cout << "Enter Name:";
        cin.ignore();
        getline(cin, n);
        cout << endl;
        char x = n[0];
        int index = P.find(x);
        Contact* temp = P.Phonetable[index]->next;
        if (temp != NULL)
        {
            while (temp->name != n)
            {
                temp = temp->next;
            }
        }
        if (temp != NULL)
        {
            ADD_TO_LOG(dh, dm, ds, h, d, m, mon, y, 1, temp);
        }
        else
        {
            cout << "The person you are trying to call does not exist in your phonebook" << endl;
            cout << "Enter the record of the person you want to call: " << endl;
            input(dh, dm, ds, h, d, m, mon, y, 1, temp);
        }
    }
    void incoming()
    {
    int dh, dm, ds, d, m, y, h, mon, s;
        string n;
        cout << "Enter Date Information:" ;
        cout << "Enter day:";
        cin >> d;
        cout << endl;
        cout << "Enter Month: ";
        cin >> mon;
        cout << endl;
        cout << "Enter Year: ";
        cin >> y;
        cout << endl;
        cout << "Enter Time Information:";
        cout << "Enter Hour:";
        cin >> h;
        cout << endl;
        cout << "Enter Minute:";
        cin >> m;
        cout << endl;
        cout << "Enter Duration Information:" << endl;
        cout << "Enter Hour:";
        cin >> dh;
        cout << endl;
        cout << "Enter Minute:";
        cin >> dm;
        cout << endl;
        cout << "Enter Seconds:";
        cin >> ds;
        cout << endl;
        cout << "Enter Name:";
        cin.ignore();
        getline(cin, n);
        cout << endl;
        char x = n[0];
        int index = P.find(x);
        Contact* temp = P.Phonetable[index]->next;
        if (temp != NULL)
        {
            while (temp->name != n)
            {
                temp = temp->next;
            }
        }
        if (temp != NULL)
        {
            ADD_TO_LOG(dh, dm, ds, h, d, m, mon, y, 0, temp);
        }
        else
        {
            cout << "the person you are trying to call does not exist in your phonebook" << endl;
            cout << "enter the record of the person you want to call: " << endl;
            input(dh, dm, ds, h, d, m, mon, y, 0, temp);
        }
	}
    void ADD_TO_LOG(int dh, int dm, int ds, int h, int d, int m, int mon, int y, int ch, Contact* c)
    {
        Calllog* newcalllog = new Calllog(dh, dm, ds, h, m, d, mon, y, ch, c);
        if (head == NULL)
        {
            head = newcalllog;
        }
        else
        {
            Calllog* temp = head;
            while (temp->right != NULL) {
                temp = temp->right;
            }
            temp->right = newcalllog;
        }
        sortlog();
        FILE* fptr = fopen("call_log.txt", "a");
        if (fptr == NULL)
        {
            printf("file does not exist");
            exit(1);
        }
        char* s1;
        int ddh, ddm, dds, dd, mm, yy, hh, mi, chh;
        s1 = &newcalllog->contact->name[0];
        ddh = newcalllog->duration.ho;
        ddm = newcalllog->duration.min;
        dds = newcalllog->duration.sec;
        dd = newcalllog->date.day;
        mm = newcalllog->date.month;
        yy = newcalllog->date.year;
        mi = newcalllog->time.minute;
        hh = newcalllog->time.hour;
        chh = newcalllog->checkvalue;
        fprintf(fptr, "%d %d %d %d %d %d %d %d %d %s\n", dd, mm, yy, hh, mi,ddh, ddm, dds, chh, s1);
        fclose(fptr);
    }

    void update_call_log_contact(string y, Contact* v)
    {
        Calllog* temp = head;
        while(temp->right != NULL)
        {
            if (temp->contact->name == y)
            {
                temp->contact->name = v->name;
                temp->contact->phone = v->phone;
                temp->contact->email = v->email;
                temp->contact->address = v->address;
            }
            temp = temp->right;
        }
        FILE* fptr = fopen("call_log.txt", "r");
        FILE* fptr2 = fopen("separate.txt", "w");
        if (fptr == NULL || fptr2 == NULL)
        {
            printf("file does not exist");
            exit(1);
        }
        int dh, dm, ds, dd, mm, yy, hh, mi, chh;
        char s1[100];
        char* s2 = &v->name[0];
        string d;
        fseek(fptr, 0, SEEK_SET);
        while (!feof(fptr))
        {
            fscanf(fptr, "%d %d %d %d %d %d %d %d %d %[^\n]s\n",&dd, &mm, &yy, &hh, &mi, &dh, &dm, &ds, &chh, s1);
            if(s1 == y)
            fprintf(fptr2, "%d %d %d %d %d %d %d %d %d %s\n", dd, mm, yy, hh, mi, dh, dm, ds, chh, s2);
            else
            fprintf(fptr2, "%d %d %d %d %d %d %d %d %d %s\n", dd, mm, yy, hh, mi, dh, dm, ds, chh, s1);
        }
        fclose(fptr);
        fclose(fptr2);
        remove("call_log.txt");
        rename("separate.txt", "call_log.txt");
    }
    
    Calllog* merge(Calllog* left, Calllog* rright)
    {
        Calllog* result = NULL;

        if (left == NULL)
            return rright;
        if (rright == NULL)
            return left;

        if (left->date.year > rright->date.year || (left->date.year == rright->date.year && left->date.month > rright->date.month) ||
            (left->date.year == rright->date.year && left->date.month == rright->date.month && left->date.day > rright->date.day) ||
            (left->date.year == rright->date.year && left->date.month == rright->date.month && left->date.day == rright->date.day && left->time.hour > rright->time.hour) ||
            (left->date.year == rright->date.year && left->date.month == rright->date.month && left->date.day == rright->date.day && left->time.hour == rright->time.hour && left->time.minute > rright->time.minute))
        {
            result = left;
            result->right = merge(left->right, rright);
        }
        else
        {
            result = rright;
            result->right = merge(left, rright->right);
        }

        return result;
    }

    Calllog* mergeSort(Calllog* head)
    {
        if (!head || !head->right)
            return head;

        Calllog* slow = head;
        Calllog* fast = head->right;
        while (fast && fast->right)
        {
            slow = slow->right;
            fast = fast->right->right;
        }

        Calllog* secondHalf = slow->right;
        slow->right = NULL;

        return merge(mergeSort(head), mergeSort(secondHalf));
    }
    
      bool containletters(string input, string s){
    	bool check;
    	for(int i=0;i<s.length();i++){
    		check=false;
    		for(int j=0;j<input.length();j++){
    			if(s[i]==input[j]){
    				check=true;
				}
			}
			if(check==false){
				return false;
			}
		}
		return true;
	}
    void Searchlog(string n)
	{
		sortlog();
    	Calllog* t = head;
    	Queue q;
    	while(t != NULL)
		{
    		if(containletters(t->contact->name,n))
			{
				Calllog* temp = new Calllog(t->duration.ho, t->duration.min, t->duration.sec, t->time.hour, t->time.minute, t->date.day, t->date.month, t->date.year, t->checkvalue, t->contact);
    			q.enqueue(temp);
			}
			t = t->right;
		}
		q.print();
	}
   void printlog()
    {
    	sortlog();
        Calllog* temp = head;
        while (temp != NULL)
        {
        	cout << "NAME: " << temp->contact->name << " | START TIME(HR:MIN): " << temp->time.hour << ":" << temp->time.minute << " | DATE(DD/MM/YYYY):" <<  temp->date.day << "/" 
			<< temp->date.month << "/" << temp->date.year <<  " | DURATION(HR:MIN:SEC) : " << temp->duration.ho << ":" << temp->duration.min << ":" << temp->duration.sec  << " | TYPE: " << (temp->checkvalue == 0? "INCOMING" : "OUTGOING" ) << endl;
//            cout << temp->time.hour << " , " << temp->time.minute << " , " << temp->date.day << " , " << temp->date.month << " , " << temp->date.year << " , "
//                << temp->duration.ho << " , " << temp->duration.min << " , " << temp->duration.sec << " , " << temp->contact->name << endl;
            temp = temp->right;
        }
    }
    
    void sortlog(){
    	head = mergeSort(head);
	}
    public:	
    //functions for printing menu
    void ADD_RECORD_PHONEBOOK(string n, long long p, string e, string a)
    {
        P.ADD_TO_CONTACTS(n, p, e, a);
    }

    void UPDATE_PHONEBOOK(string y)
    {
        Contact* v = P.editing(y);
        update_call_log_contact(y, v);
    }

    void DELETE_PHONEBOOK(string n)
    {
        P.deletion(n);
    }

    void DISPLAY_PHONEBOOK()
    {
        P.print();
    }

    void DISPLAY_BY_ALPHABET_IN_PHONEBOOK(char a)
    {
        P.print_at_Alphabet(a);
    }

    void SEARCH_RECORD(string n)
    {
        P.Search(n);
    }

    void SEARCH_CALL_LOG(string n)
    {
        Searchlog(n);
    }
    void OUTGOING_CALLS()
    {
        outgoing();
    }

    void INCOMING_CALLS()
    {
        incoming();
    }

    void DISPLAY_CALL_LOG()
    {
        printlog();
    }
    void Display_Menu(){
    	cout << "\t\t\tPROJECT TITLE: PHONE BOOK WITH CALL LOG SYSTEM PROJECT" << endl;
    	cout << "\t\t\t\tPROJECT MEMBERS: SHAYAN | RANIA | MARIUM " << endl;
    while(1){
	    	int primary_choice;
	    	int secondary_choice;
	    	int tertiary_choice;
	    	while(1){ //VALIDATES IF ENTERED CHOICE IS CORRECT!
	    		cout << endl;
		    	cout << "HOW CAN WE ASSIST YOU?" << endl;
		    	cout << "1- PERFORM PHONEBOOK OPERATIONS" << endl;
		    	cout << "2- PERFORM CALL LOG OPERATIONS" << endl;
		    	cout << "3- Exit" << endl;
	    		cout << "YOUR CHOICE:  "; cin >> primary_choice;
	    		if(primary_choice >= 1 && primary_choice <= 3){
	    			break;
				}else{
					cout << "INVALID CHOICE! TRY AGAIN" << endl;
				}
			}
			if(primary_choice == 1){ //PHONEBOOK OPERATIONS:
				while(1){ //VALIDATES IF ENTERED CHOICE IS CORRECT!
					cout << endl;
					cout << "PHONEBOOK OPERATIONS:" << endl;
			    	cout << "1- ADD NEW CONTACT RECORD" << endl;
			    	cout << "2- UPDATE EXISTING CONTACT RECORD" << endl;
			    	cout << "3- REMOVE CONTACT FROM PHONEBOOK" << endl;	
			    	cout << "4- SEARCH RECORD IN PHONEBOOK" << endl;
					cout << "5- DISPLAY PHONEBOOK" << endl;
					cout << "YOUR CHOICE:  "; cin >> secondary_choice;
		    		if(secondary_choice >= 1 && secondary_choice <= 5){
		    			break;
					}else{
						cout << "INVALID CHOICE! TRY AGAIN" << endl;
					}				
				}
				if(secondary_choice == 1){
					string name, email, address;
					long long phoneNumber;
					cout << "ENTER YOUR NAME:  ";cin.ignore(); getline(cin, name);
					cout << "ENTER YOUR PHONE NUMBER:  "; cin >> phoneNumber;
					cout << "ENTER YOUR EMAIL ADDRESS:  "; cin.ignore(); cin >> email;
					cout << "ENTER YOUR RESIDENTIAL ADDRESS:  "; cin.ignore(); getline(cin, address);
					ADD_RECORD_PHONEBOOK(name, phoneNumber, email, address);
				}else if(secondary_choice == 2){
					string name;
					cout << "ENTER NAME OF CONTACT PERSON TO UPDATE RECOND: "; cin.ignore(); getline(cin, name);
					UPDATE_PHONEBOOK(name);
				}else if(secondary_choice == 3){
					string name;
					cout << "ENTER NAME OF CONTACT PERSON TO REMOVE RECORD: ";cin.ignore(); getline(cin, name);
					DELETE_PHONEBOOK(name);				
				}else if(secondary_choice == 4){
					string name;
					cout << "ENTER NAME TO SEARCH: ";cin.ignore(); getline(cin, name);
					SEARCH_RECORD(name);
				}else if(secondary_choice == 5){
					while(1){
						cout << endl;
						cout << "ENTER YOUR PREFERENCE:" << endl;
				    	cout << "1- DISPLAY PHONEBOOK CONTACT RECORDS STARTING WITH SPECIFIC ALPHABET" << endl;
				    	cout << "2- DISPLAY ALL PHONEBOOK CONTACT RECORDS" << endl;
						cout << "YOUR PREFERENCE:  "; cin >> tertiary_choice;		
			    		if(tertiary_choice >= 1 && tertiary_choice <= 2){
			    			break;
						}else{
							cout << "INVALID CHOICE! TRY AGAIN" << endl;
						}								
					}
					if(tertiary_choice == 1){
						char character;
						cout << "ENTER CHARACTER:  "; cin >> character;
						DISPLAY_BY_ALPHABET_IN_PHONEBOOK(character);
					}else if( tertiary_choice == 2){
						DISPLAY_PHONEBOOK();
					}
				}
			}else if(primary_choice == 2){ //CALL LOG OPERATIONS
				while(1){ //VALIDATES IF ENTERED CHOICE IS CORRECT!
					cout << endl;
					cout << "CALL LOG OPERATIONS:" << endl;
			    	cout << "1- DISPLAY CALL LOG" << endl;
			    	cout << "2- ADD INCOMING CALLS" << endl;
			    	cout << "3- ADD OUTGOING CALLS" << endl;	
					cout << "4- SEARCH CALL RECORDS" << endl;
					cout << "YOUR CHOICE:  "; cin >> secondary_choice;
		    		if(secondary_choice >= 1 && secondary_choice <= 4){
		    			break;
					}else{
						cout << "INVALID CHOICE! TRY AGAIN" << endl;
					}
				}	
				if(secondary_choice == 1){
					DISPLAY_CALL_LOG();
				}else if(secondary_choice == 2){
					INCOMING_CALLS();
				}else if(secondary_choice == 3){
					OUTGOING_CALLS();
				}else if(secondary_choice == 4){
					string name;
					cout << "ENTER NAME TO SEARCH: ";cin.ignore(); getline(cin, name);
					SEARCH_CALL_LOG(name);			
				}	
			}else if(primary_choice == 3){ //exit program
				exit(1);
			}
		}
	}
};


int main()
{
    User u;
    u.Display_Menu();
}
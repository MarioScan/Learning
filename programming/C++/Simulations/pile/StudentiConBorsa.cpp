#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class Student
{
    private:
        string name;
        string surname;
        float average; 
        int matricola; //unique number assigned to each student.
        int assign_id()
        {
            static int id = 100100;
            return ++id;
        }
    public:
        Student(const string& nome, const string& cognome, float media) 
        : name(nome), surname(cognome), average(media), matricola(assign_id()) {}

        Student() : name(""), surname(""), average(0.0), matricola(assign_id()) {}
        ~Student() {}
        //it is supposed that it might be needed a copy-construct for backup purposes 
        Student(const Student& s) : name(s.name), surname(s.surname), average(s.average), matricola(s.matricola) {}

        const string& get_name() const { return name; }
        const string& get_surname() const { return surname; }
        float get_average() const { return average; }
        int get_matricola() const { return matricola; }

        void set_name(const string& newName) { name = newName; }
        void set_surname(const string& newSurname) { surname = newSurname; }
        void set_average(float newAverage) { average = newAverage; }
        void set_matricola() { matricola = assign_id(); } 

        friend ostream& operator<<(ostream&, const Student&);
        virtual void print() const 
        {
            cout << *this;
        }
        friend istream& operator>>(istream&, Student&);

};
ostream& operator<<(ostream& os, const Student& s)
{
    os << s.matricola << " - " << s.name << " " << s.surname << " - " << s.average;
    return os; 
}
istream& operator>>(istream& is, Student& s)
{
    is >> s.name >> s.surname >> s.average;
    s.set_matricola();
    return is;
}

class Scholarship
{
    private:
        int amount; //euros 
        int duration; //in months
    public:
        Scholarship() : amount(0), duration(0) {}
        Scholarship(int ammontare, int durata) : amount(ammontare), duration(durata) {}
        ~Scholarship() {}

        int get_amount() const { return amount; }
        int get_duration() const { return duration; }

        void set_amount(int newAmount) { amount = newAmount; }
        void set_duration(int newDuration) { duration = newDuration; }
        
        friend ostream& operator<<(ostream&, const Scholarship&);
        void stampa() const
        {
            cout << *this;
        }
};
ostream& operator<<(ostream& os, const Scholarship& s) 
{
    os << "[" << s.amount << " euros - " << s.duration << " months]";
    return os;
}

class StudentWithScholarship : public Student
{
    private:
        Scholarship* bag;
    public:
        StudentWithScholarship(const string& name, const string& surname, float avg, Scholarship* b)
        : Student(name, surname, avg), bag(b) {}
        ~StudentWithScholarship() { if(bag) delete bag; }
        

        int get_bag_amount() const { if(bag) return bag->get_amount(); else 0; }
        int get_bag_duration() const { if(bag) return bag->get_duration(); else 0; }

        void set_bag(Scholarship* newBag) { bag = newBag; }
        void set_bag_amount(int amount) { if(bag) bag->set_amount(amount); else cerr << "Impossible to set new amount for the bag as the bag does not exists.";}
        void set_bag_duration(int duration) { if(bag) bag->set_duration(duration); else cerr << "Impossible to set new duration for the bag as the bag does not exists."; } 

        friend ostream& operator<<(ostream& os, const StudentWithScholarship& s);
        void print() const override
        {
            cout << *this;
        }
        friend istream& operator>>(istream& is, StudentWithScholarship& s);
};
ostream& operator<<(ostream& os, const StudentWithScholarship& s)
{
    os << s.get_matricola() << " - " << s.get_name() << " " << s.get_surname() << " - " << s.get_average();
    os << "[" << s.get_bag_amount() << " euros - " << s.get_bag_duration() << " months]";
    return os;
}
istream& operator>>(istream& is, StudentWithScholarship& s)
{
    string name, surname;
    float average;
    int amount, duration;
    is >> name >> surname >> average >> amount >> duration;
    s.set_name(name); s.set_surname(surname); s.set_average(average);
    s.set_bag_amount(amount); s.set_bag_duration(duration);
    return is;
}

//======================================================================================================

template <class T>
class Node
{
    private:
        T data;
        Node<T>* next;
    public
        Node(const T& dato) : data(dato), next(nullptr) {}
        ~Node() {}

        const T& get_data() const { return data; }
        Node<T>* get_next() const { return next; } 

        void set_next(Node<T>* newNext) { next = newNext; }
};


template <class T>
class Stack
{
    private:
        Node<T>* top;
        int maxElements;
        int count;
    public:
        Stack(int max_elem) : top(nullptr), maxElements(max_elem), count(0) {}
        
        int get_maxElements() const { return maxElements; }
        void set_maxElements(int newMax) { maxElements = newMax; }

        bool isEmpty() const { return top == nullptr; }
        bool isFull() const { return count >= maxElements; }

        Stack<T>* push(const T& newData) //inserting new element on top of the Stack (LIFO)
        {
            if(isFull())
            {
                cout << "Impossible to push any more item: Stack is full. You may want to change the max elements of the stack or delete some.";
                return this;
            }

            Node<T>* newElement = new Node<T>(newData);
            if(!newElement)
            {
                cerr << "Error: couldn't allocate new node. Terminating the program..." << endl;
                exit(1);
            }

            if(isEmpty())
            {
                top = nuovo;
                return this;
            }

            newElement->set_next(top);
            top = newElement;
            return this;
        }

        void peek() const //peek first element of the Stack without removing it.
        {
            if(isEmpty())
            {
                cout << "Impossible to peek the first element of the Stack as there are none." << endl;
                return;
            }

            cout << *(top->get_data());
        }

        T pop() //remove top element and return a copy of the data  
        {
            if(isEmpty())
            {
                cerr << "Impossible to execute Pop function: Stack is empty. Ending process..." << endl;
                exit(1);
            }
            T dataCopy = top->get_data();
            Node<T>* temp = top;
            delete top->get_data(); //we need to deallocate the data inside the Node as we are working with pointers to Student (Student*)            
            top = top->get_next();
            delete temp;
            return dataCopy;
        }

        void clear()
        {
            while(top != nullptr)
            {
                Node<T>* temp = top;
                delete top->get_data();             
                top = top->get_next();
                delete temp;                
            }
        }

        int searchMatricola(int matricola) const //return position in the Stack 
        {
            int k = 0;
            Node<T>* current = top;
            while(current) 
            {
                if(current->get_data()->get_matricola() == matricola)
                    return k;
                current = current->get_next();
                k++;
            }
            return -1; //not found
        }

        void safePrint() const 
        {
            Node<T>* current = top;
            while(current)
            {
                cout << *(current->get_data());
                current = current->get_next();
            }
        }

        void popAndPrintAll() 
        {
            while(top)
            {
                T data = pop();
                data->print();
                top = top->get_next(); 
            }
        }

        ~Stack() { clear(); }
};

int main() 
{
    
    return 0;
}

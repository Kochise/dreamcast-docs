
#include <iostream>
using namespace std;


template <class A, class B>
class Pair
{
private:
	A index;
	B value;
public:
	Pair(A aa, B bb):index(aa),value(bb) {}
	void display()
	{
		cout << index << ' ' << value << endl;
	}
    bool operator>(const Pair<A,B>& p)
    { return index>p.index;}
};

template <class B>
class Pair<char*, B>
{
private:
	char* index;
	B value;
public:
	Pair(char* aa, B bb):value(bb) 
    {index = new char[strlen(aa)]; strcpy(index,aa);}
	void display()
	{
		cout << index << ' ' << value << endl;
	}
    bool operator>(const Pair<char*, B>& p)
    { return ( strcmp(index,p.index) > 0);}
};



int main(int argc, char* argv[])
{
	Pair<double,int> first(2.2,3);
	first.display();
    Pair<double,int> second(2.1,4);
    second.display();
    if (first > second)
        cout << "first is greater" << endl;
    else
        cout << "first is not greater" << endl;
    Pair<char*,int> third("Hello",4);
    third.display();
    Pair<char*,int> fourth("World",5);
    fourth.display();
    if (third > fourth)
        cout << "third is greater" << endl;
    else
        cout << "third is not greater" << endl;

    return 0;
}


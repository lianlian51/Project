#include <iostream>
using namespace std;
class Point
{
	int x1, x2;
public:


	Point(int x = 10, int y = 20){ x1 = x; x2 = y; }
	/*Point operator->(){
	return *this;
	}*/
	int x_cord(){ return x1; }
	int y_cord(){ return x2; }

};

int main()
{
	Point date(3, 4);
	cout << date.x_cord() << endl;
	cout << date.y_cord() << endl;
	//Point more_date[5];
	//cout<<more_date.x_cord<<endl;
	Point* more_date = new Point[5];
	cout << &more_date << endl;
	cout << more_date[0].x_cord() << " " << more_date[0].y_cord() << endl;
	return 0;
}

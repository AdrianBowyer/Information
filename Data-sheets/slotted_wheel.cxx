#include <Magick++.h> 
#include <iostream>
#include <strstream.h>
#include <math.h>

using namespace std; 
using namespace Magick;

inline int iround(double a) 
{
        return( (a > 0.0) ? (int)(a + 0.5) : (int)(a - 0.5) );
}


int main(int argc,char **argv) 
{

  if(argc != 2)
  {
    cerr << "Usage: slotted_wheel output_file\n";
    exit(1);
  }
       try { 


	 int geom;
	 cout << "image size: ";
	 cin >> geom;
         Image image( Geometry(geom,geom), Color("white") );
	 //image.antiAlias(0);

	 //image.strokeAntiAlias(0);

	 image.strokeColor("black");
	 image.fillColor("black");
	 //image.draw(DrawableFillColor("black"));
	 image.strokeWidth(3);

	 int x0 = geom/2;
	 int y0 = geom/2;
	 int x, y;

	 y = geom/16;
	 char slot_t[50];
	 cout << "Number of slots: ";
	 int slots;
	 cin >> slots;
	 ostrstream ost(slot_t, 50);
         ost << slots << '\0';

	 image.draw( DrawableLine(x0, y0 - y, x0, y0 + y));
	 image.draw( DrawableLine(x0 - y, y0, x0 + y, y0));


	list<Drawable> drawList; 
	drawList.push_back(DrawableStrokeColor("black")); // Outline color 
	drawList.push_back(DrawableFont("Courier", AnyStyle, 0, AnyStretch));
	drawList.push_back(DrawablePointSize(50));
	drawList.push_back(DrawableText(x0 - y/2, y0+2*y, slot_t));
	image.draw(drawList);

	 double r0, r1, theta, dtheta;
	 dtheta = 2*M_PI/(double)slots;
	 r0 = y0 - 2*y;
	 r1 = y0 - y;
	 list<Coordinate> clist;
	 image.strokeWidth(1);
	 for(int i = 0; i < slots; i++)
	 {
	   list<Magick::Coordinate> clist;
	   theta = i*dtheta;
	   x = iround(x0 + r0*cos(theta));
	   y = iround(y0 + r0*sin(theta));
	   clist.push_front(Coordinate(x, y));
	   x = iround(x0 + r1*cos(theta));
	   y = iround(y0 + r1*sin(theta));
	   clist.push_front(Coordinate(x, y));
	   theta = theta+0.5*dtheta;
	   x = iround(x0 + r1*cos(theta));
	   y = iround(y0 + r1*sin(theta));
	   clist.push_front(Coordinate(x, y));
	   x = iround(x0 + r0*cos(theta));
	   y = iround(y0 + r0*sin(theta));
	   clist.push_front(Coordinate(x, y));

	   image.draw(DrawablePolyline(clist) );
	 }
 
	 //image.display();
 
	 image.write(argv[1]);
       } 
       catch( Exception &error_ ) 
         { 
           cout << "Caught exception: " << error_.what() << endl; 
           return 1; 
         } 
       return 0; 
}

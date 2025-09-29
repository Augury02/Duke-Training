#include <iostream>
#include <cmath>

enum class PointType // used to specify how the point coordinates should be interpreted
{
  cartesian,
  polar
};

class Point
{
  /*Point(float a, float b, PointType type = PointType::cartesian) //INITIAL COMPLICATED METHOD
  {                                                                //W/O THE USE OF FACTORIES
    if (type == PointType::cartesian)
    {
      x = a; b = y;
    }
    else
    {
      x = a*cos(b);
      y = a*sin(b);
    }
  }*/

  // use a factory method
  Point(float x, float y) : x(x), y(y){} // This is a private constructor; with coordinates x and y for the cartesian plane
                                         // In this method, variables are public but constructors
                                         // are private
public:
  float x, y;

  friend class PointFactory; // The friend command allows the class PointFactory to access the
                             // private constructor Point
};

class PointFactory // This is the class PointFactory which was declared as friend
{
public:
  static Point NewCartesian(float x, float y) // Usage of private constructor Point; creates object named NewCartesian
  {                                           // that has its own return values x and y
    return Point{ x, y };
  }

  static Point NewPolar(float r, float theta)
  {
    return Point{ static_cast<float>(r * cos(theta)), static_cast<float>(r * sin(theta)) }; // creates object named NewPolar that uses return values r*cos(theta)
                                                                                           // and r*sin(theta)
  }

  /* You can observe here that the factory PointFactory created 2 objects with variety (one using cartesian
     and the other, polar coordinates). They both utilized the same private constructor Point; but had
     different arguments and descriptions
  */
};

int main()
{
  Point p1 = PointFactory::NewCartesian(3.0, 4.0);
  Point p2 = PointFactory::NewPolar(5.0, M_PI_4); // M_PI_4 is pi/4, 45 degrees

  std::cout << "Cartesian Point: (" << p1.x << ", " << p1.y << ")\n";
  std::cout << "Polar Point: (" << p2.x << ", " << p2.y << ")\n";
  return 0;
}

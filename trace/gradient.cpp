#define IMAGE_WIDTH 800
#define IMAGE_HEIGHT 400
#define COLORS 255.99

#include "vector.h"
#include "ray.h"

vector<double> color(const ray<double>& r)
{
    vector<double> unitDirection = r.direction().unit();
    double t = 0.5 * (unitDirection[1] + 1.0);  // scale y to [0, 1]

    // linearly interpolate the start color vector (white)
    // and end color vector (green).
    return vector<double>({1.0, 1.0, 1.0}) * t + vector<double>({0.3, 0.97, 0.53}) * (1 - t); // returns our blended value.
}

int main()
{
    // set up file.
    std::cout << "P3" << std::endl << IMAGE_WIDTH << " " << IMAGE_HEIGHT << std::endl << COLORS << std::endl;

    vector<double> lowerLeft({-2.0, -1.0, -2.0});   // dictates the lower left corner of our background.
    vector<double> horizontal({4.0, 0.0, 0.0});
    vector<double> vertical({0.0, 2.0, 0.0});
    vector<double> origin({0.0, 0.0, 0.0});

    for (int y = 0; y < IMAGE_HEIGHT - 1; y++)
    {
        for (int x = 0; x < IMAGE_WIDTH; x++)
        {
            double u = (double) x / (double) IMAGE_WIDTH;
            double v = (double) y / (double) IMAGE_HEIGHT;
            ray<double> lookingAt(origin, lowerLeft + horizontal*u + vertical*v);
            vector<double> col = color(lookingAt);
            
            int r = int(COLORS*col[0]);
            int g = int(COLORS*col[1]);
            int b = int(COLORS*col[2]);

            std::cout << r << ' '<< g << ' ' << b << std::endl;
        }
    }

    return 0;
}
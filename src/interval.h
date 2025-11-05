    #ifndef INTERVAL_H
    #define INTERVAL_H

    #include <limits>

    class interval
    {
    public:
        double min, max;

        interval() : min(+infinity), max(-infinity) {} // Default interval is empty

        interval(double min, double max) : min(min), max(max) {}

        double size() const
        {
            return max - min;
        }

        bool contains(double x) const
        {
            return min <= x && x <= max;
        }

        bool surrounds(double x) const
        {
            return min < x && x < max;
        }

        double clamp(double x) const
        {
            if (x < min)
                return min;
            if (x > max)
                return max;
            return x;
        }

        static const interval empty, universe; // two special interval constants available to all code that uses this class
    };

    const interval interval::empty    = interval(+infinity, -infinity);    // represents no range, since min > max
    const interval interval::universe = interval(-infinity, +infinity);    // represents the entire possible range of numbers(from -∞ to +∞).


    #endif
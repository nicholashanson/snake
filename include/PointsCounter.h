#ifndef POINTSCOUNTER_H
#define POINTSCOUNTER_H

class PointsCounter
{
    public:
        PointsCounter();
        virtual ~PointsCounter();

        auto get_apple_points() const -> int;
        auto get_points_count() const -> int;

        void eat_apple();
        void eat_apples(int);
        void reset_apple_points();
        void increment_points_count();
    protected:
    private:
        int apple_points;
        int bonus_points;
};

#endif // POINTSCOUNTER_H


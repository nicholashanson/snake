#ifndef POINTSCOUNTER_H
#define POINTSCOUNTER_H

class PointsCounter
{
    public:
        PointsCounter();
        virtual ~PointsCounter();

        auto get_apple_points() const -> int;
        auto get_points_count() const -> int;

        auto eat_apple() -> void;
        auto eat_apples(int) -> void;
        auto reset_apple_points() -> void;
        auto increment_points_count() -> void;
    protected:
    private:
        int apple_points;
        int bonus_points;
};

#endif // POINTSCOUNTER_H

#include "PointsCounter.h"
#include "settings.h"

// special members
PointsCounter::PointsCounter() : apple_points( 0 ), bonus_points( 0 ){}
PointsCounter::~PointsCounter(){}

// getters
auto PointsCounter::get_apple_points() const -> int
{return apple_points;}

auto PointsCounter::get_points_count() const -> int
{return apple_points + bonus_points;}

// actions
auto PointsCounter::eat_apple() -> void
{apple_points += settings::points_per_apple;}

auto PointsCounter::eat_apples(int number_of_apples) -> void
{apple_points += number_of_apples * settings::points_per_apple;}

auto PointsCounter::reset_apple_points() -> void
{apple_points = 0;}

auto PointsCounter::increment_points_count() -> void
{apple_points += settings::points_per_apple;}









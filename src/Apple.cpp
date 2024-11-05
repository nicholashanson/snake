#include "Apple.h"

// special members
Apple::Apple(){}
Apple::~Apple(){}

// getters
auto Apple::get_position() const -> square_t
{return position;}

// setters
auto Apple::set_position(const square_t pos) -> void
{position = pos;}

auto Apple::set_position(const int x, const int y) -> void
{set_position( { x, y } );}

// actions
auto Apple::spawn(const int x, const int y) -> void
{position = { x, y };}


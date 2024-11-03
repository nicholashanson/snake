#include "../include/Sim.h"

Sim::Sim()
{
    std::fill(current_state.begin(), current_state.end(), dead);
}

Sim::~Sim()
{
    //dtor
}

// getters

state_t Sim::get_state()
{
    return current_state;
}

cell_pos_t Sim::get_central_cell()
{
    return settings::central_index;
}

cell_pos_t Sim::get_neighbor(cell_pos_t cell, direction_t neigbor)
{
    switch (neigbor)
    {
        case north:
            return cell - settings::board_width;
            break;
        case south:
            return cell + settings::board_height;
            break;
        case east:
            return cell + 1;
            break;
        case west:
            return cell - 1;
            break;
        case northeast:
            return cell - settings::board_width + 1;
            break;
        case northwest:
            return cell - settings::board_width - 1;
            break;
        case southeast:
            return cell + settings::board_width + 1;
            break;
        case southwest:
            return cell + settings::board_width - 1;
            break;
        default: break;
    }
}

cell_pos_vec_t Sim::get_neighbors(cell_pos_t cell, const direction_vec_t& neighbors)
{
    cell_pos_vec_t cells;
    cells.reserve(neighbors.size());
    for (auto it = neighbors.begin(); it != neighbors.end(); ++it)
        cells.push_back(get_neighbor(cell, *it));
    return cells;
}

cell_pos_vec_t Sim::get_cardinal_neighbors(cell_pos_t cell)
{
    direction_vec_t cardinals{north, south, east, west};
    return get_neighbors(cell, cardinals);
}

cell_pos_vec_t Sim::get_intercardinal_neighbors(cell_pos_t cell)
{
    direction_vec_t intercardinals{northeast, northwest, southeast, southwest};
    return get_neighbors(cell, intercardinals);
}

void Sim::get_neighborhood(cell_pos_t i, neighborhood_t &neighbors)
{
    if (i == 0)
        get_top_left_corner_neighborhood(neighbors);
    else if (i == settings::board_width - 1)
        get_top_right_corner_neighborhood(neighbors);
    else if (i == settings::cell_count - settings::board_width)
        get_bottom_left_corner_neighborhood(neighbors);
    else if (i == settings::cell_count - 1)
        get_bottom_right_corner_neighborhood(neighbors);
    else if (i > 0 && i < settings::board_width - 1)
        get_top_edge_neighborhood(i, neighbors);
    else if (i % (settings::board_width) == 0)
        get_left_edge_neighborhood(i, neighbors);
    else if ((i+1) % (settings::board_width) == 0)
        get_right_edge_neighborhood(i, neighbors);
    else if (i > settings::cell_count - settings::board_width)
        get_bottom_edge_neighborhood(i, neighbors);
    else
        __get_neighborhood(i, neighbors);
}

#ifdef MOORE
void Sim::get_top_left_corner_neighborhood(moore_t &neighbors)
{
    std::fill(neighbors.begin(), neighbors.end() - 3, dead);
    neighbors[5] = current_state[1];
    neighbors[6] = current_state[settings::board_width];
    neighbors[7] = current_state[settings::board_width + 1];
}

void Sim::get_top_right_corner_neighborhood(moore_t &neighbors)
{
    cell_pos_t target_cell = settings::board_width - 1;
    std::fill(neighbors.begin(), neighbors.end() - 3, dead);
    neighbors[5] = current_state[target_cell - 1];
    neighbors[6] = current_state[target_cell + settings::board_width - 1];
    neighbors[7] = current_state[target_cell + settings::board_width];
}

void Sim::get_bottom_left_corner_neighborhood(moore_t &neighbors)
{
    cell_pos_t target_cell = settings::cell_count - settings::board_width;
    std::fill(neighbors.begin(), neighbors.end() - 3, dead);
    neighbors[5] = current_state[target_cell - settings::board_width];
    neighbors[6] = current_state[target_cell - settings::board_width + 1];
    neighbors[7] = current_state[target_cell + 1];
}

void Sim::get_bottom_right_corner_neighborhood(moore_t &neighbors)
{
    cell_pos_t target_cell = settings::cell_count - 1;
    std::fill(neighbors.begin(), neighbors.end() - 3, dead);
    neighbors[5] = current_state[target_cell - settings::board_width];
    neighbors[6] = current_state[target_cell - settings::board_width - 1];
    neighbors[7] = current_state[target_cell - 1];
}

void Sim::get_top_edge_neighborhood(cell_pos_t i, moore_t &neighbors)
{
    std::fill(neighbors.begin(), neighbors.end() - 5, dead);
    neighbors[3] = current_state[i - 1];
    neighbors[4] = current_state[i + 1];
    neighbors[5] = current_state[i + settings::board_width - 1];
    neighbors[6] = current_state[i + settings::board_width];
    neighbors[7] = current_state[i + settings::board_width + 1];
}

void Sim::get_right_edge_neighborhood(cell_pos_t i, moore_t &neighbors)
{
    std::fill(neighbors.begin(), neighbors.end() - 5, dead);
    neighbors[3] = current_state[i - settings::board_width - 1];
    neighbors[4] = current_state[i - settings::board_width];
    neighbors[5] = current_state[i - 1];
    neighbors[6] = current_state[i + settings::board_width - 1];
    neighbors[7] = current_state[i + settings::board_width];
}

void Sim::get_bottom_edge_neighborhood(cell_pos_t i, moore_t &neighbors)
{
    std::fill(neighbors.begin(), neighbors.end() - 5, dead);
    neighbors[3] = current_state[i - settings::board_width - 1];
    neighbors[4] = current_state[i - settings::board_width];
    neighbors[5] = current_state[i - settings::board_width + 1];
    neighbors[6] = current_state[i - 1];
    neighbors[7] = current_state[i + 1];
}

void Sim::get_left_edge_neighborhood(cell_pos_t i, moore_t &neighbors)
{
    std::fill(neighbors.begin(), neighbors.end() - 5, dead);
    neighbors[3] = current_state[i - settings::board_width];
    neighbors[4] = current_state[i - settings::board_width + 1];
    neighbors[5] = current_state[i + 1];
    neighbors[6] = current_state[i + settings::board_width];
    neighbors[7] = current_state[i + settings::board_width + 1];
}

void Sim::__get_neighborhood(cell_pos_t i, moore_t &neighbors)
{
    neighbors[0] = current_state[i - settings::board_width - 1];
    neighbors[1] = current_state[i - settings::board_width];
    neighbors[2] = current_state[i - settings::board_width + 1];
    neighbors[3] = current_state[i - 1];
    neighbors[4] = current_state[i + 1];
    neighbors[5] = current_state[i + settings::board_width - 1];
    neighbors[6] = current_state[i + settings::board_width];
    neighbors[7] = current_state[i + settings::board_width + 1];
}
#endif

#ifdef VON_NEUMANN
void Sim::get_top_left_corner_neighborhood(von_neumann_t &neighbors)
{
    neighbors[0] = current_state[1];
    neighbors[1] = current_state[settings::board_width];
    neighbors[2] = dead;
    neighbors[3] = dead;
}

void Sim::get_top_right_corner_neighborhood(von_neumann_t &neighbors)
{
    cell_pos_t target_cell = settings::board_width - 1;
    neighbors[0] = current_state[target_cell - 1];
    neighbors[1] = current_state[target_cell + settings::board_width];
    neighbors[2] = dead;
    neighbors[3] = dead;
}

void Sim::get_bottom_left_corner_neighborhood(von_neumann_t &neighbors)
{
    cell_pos_t target_cell = settings::cell_count - settings::board_width;
    neighbors[0] = current_state[target_cell - settings::board_width];
    neighbors[1] = current_state[target_cell + 1];
    neighbors[2] = dead;
    neighbors[3] = dead;
}

void Sim::get_bottom_right_corner_neighborhood(von_neumann_t &neighbors)
{
    cell_pos_t target_cell = settings::cell_count - 1;
    neighbors[0] = current_state[target_cell - settings::board_width];
    neighbors[1] = current_state[target_cell - 1];
    neighbors[2] = dead;
    neighbors[3] = dead;
}

void Sim::get_top_edge_neighborhood(cell_pos_t i, von_neumann_t &neighbors)
{
    neighbors[0] = current_state[i + settings::board_width];
    neighbors[1] = current_state[i - 1];
    neighbors[2] = current_state[i + 1];
    neighbors[3] = dead;
}

void Sim::get_right_edge_neighborhood(cell_pos_t i, von_neumann_t &neighbors)
{
    neighbors[0] = current_state[i - 1];
    neighbors[1] = current_state[i - settings::board_width];
    neighbors[2] = current_state[i + settings::board_width];
    neighbors[3] = dead;
}

void Sim::get_bottom_edge_neighborhood(cell_pos_t i, von_neumann_t &neighbors)
{
    neighbors[0] = current_state[i - settings::board_width];
    neighbors[1] = current_state[i - 1];
    neighbors[2] = current_state[i + 1];
    neighbors[3] = dead;
}

void Sim::get_left_edge_neighborhood(cell_pos_t i, von_neumann_t &neighbors)
{
    neighbors[0] = current_state[i - settings::board_width];
    neighbors[1] = current_state[i + 1];
    neighbors[2] = current_state[i + settings::board_width];
    neighbors[4] = dead;
}

void Sim::__get_neighborhood(cell_pos_t i, von_neumann_t &neighbors)
{
    neighbors[0] = current_state[i - settings::board_width];
    neighbors[1] = current_state[i - 1];
    neighbors[2] = current_state[i + 1];
    neighbors[3] = current_state[i + settings::board_width];
}
#endif

// setters

// stats

count_t Sim::total_cells()
{
    return current_state.size();
}

count_t Sim::total_live_cells()
{
    return std::count_if(begin(current_state), end(current_state),
        [](const status_t& status){
            return live == status;
    });
}

count_t Sim::live_neighbor_count(const neighborhood_t &neighbors)
{
    return std::count_if(begin(neighbors), end(neighbors),
        [](const status_t& status){
            return live == status;
    });
}

// checkers

bool Sim::board_is_dead()
{
    return std::none_of(begin(current_state), end(current_state),
        [](const status_t& status){
            return live == status;
    });
}

/*
bool Sim::board_is_dead()
{
    bool board_is_dead = true;
    for (auto it = current_state.begin(); it != current_state.end(); ++it)
        if (live == *it)
            board_is_dead = false;
    return board_is_dead;
}
*/

bool Sim::cell_is_live(cell_pos_t cell)
{
    return live == current_state[cell];
}

bool Sim::cell_is_dead(cell_pos_t cell)
{
    return dead == current_state[cell];
}

bool Sim::cells_are_live(const cell_pos_vec_t& cells)
{
    return std::none_of(begin(cells), end(cells),
        [this](const cell_pos_t& index){
            return dead == current_state[index];
    });
}

bool Sim::cells_are_live(count_t cells_to_check, ...)
{
    va_list cells;
    va_start(cells, cells_to_check);
    for (int i = 0; i < cells_to_check; i++)
        if (dead == current_state[va_arg(cells, cell_pos_t)])
            return false;
    return true;
}

bool Sim::cells_are_live(cell_pos_t cell, const cell_pos_vec_t& cells)
{
    if (dead == current_state[cell])
        return false;
    return cells_are_live(cells);
}

bool Sim::cells_are_dead(count_t cells_to_check, ...)
{
    va_list cells;
    va_start(cells, cells_to_check);
    for (int i = 0; i < cells_to_check; i++)
        if (live == current_state[va_arg(cells, cell_pos_t)])
            return false;
    return true;
}

bool Sim::is_edge_cell(cell_pos_t i)
{
    if (i == 0)
        return true;
    else if (i == settings::board_width - 1)
        return true;
    else if (i == settings::cell_count - settings::board_width)
        return true;
    else if (i == settings::cell_count - 1)
        return true;
    else if (i > 0 && i < settings::board_width - 1)
        return true;
    else if (i % (settings::board_width) == 0)
        return true;
    else if ((i+1) % (settings::board_width) == 0)
        return true;
    else if (i > settings::cell_count - settings::board_width)
        return true;
    else
        return false;
}

// actions

void Sim::seed(count_t cells_to_seed, ...)
{
    va_list cells;
    va_start(cells, cells_to_seed);
    for (int i = 0; i < cells_to_seed; i++)
        current_state[va_arg(cells, cell_pos_t)] = live;
    va_end(cells);
}

void Sim::seed(const cell_pos_vec_t& cells)
{
    std::for_each(cells.begin(), cells.end(), [this](const cell_pos_t& i){
        this->current_state[i] = live;
    });
}

void Sim::seed(cell_pos_t cell, const cell_pos_vec_t& cells)
{
    current_state[cell] = live;
    seed(cells);
}

void Sim::generate_seed()
{
    std::random_device rd;
    std::default_random_engine generator( rd() );
    std::uniform_int_distribution<int> distribution( 0, 1 );
    for (int i = 0; i < settings::cell_count; i++)
        if (1 == distribution( generator ))
            current_state[i] = live;
}

void Sim::evolve()
{
    //print_current_state();
    state_t new_state;
    new_state = current_state;
    neighborhood_t neighbors;
    for (cell_pos_t i = 0; i < settings::cell_count; i++){
        get_neighborhood(i, neighbors);
        count_t live_neighbors = live_neighbor_count(neighbors);
        if (live == current_state[i])
            switch (live_neighbors) {
                case 2:
                    break;
                case 3:
                    break;
                default:
                    new_state[i] = dead;
                    break;
            }
        else // this cell is dead
            switch (live_neighbors) {
                case 3:
                    new_state[i] = live;
                    break;
                default: break;
            }
    }
    current_state = new_state;
    //print_current_state();
}

void Sim::print_live_members()
{
    for (int i = 0; i < settings::cell_count; i++)
        if (cell_is_live(i))
            std::cout << i << std::endl;
}

void Sim::print_current_state()
{
    std::cout << "starting" << std::endl;
    for (int i = 0; i < settings::cell_count; i++)
        std::cout << current_state[i] << std::endl;
    std::cout << "ending" << std::endl;
}

void Sim::glider_seed()
{
    current_state[292] = live;
    current_state[231] = live;
    current_state[262] = live;
    current_state[290] = live;
    current_state[291] = live;
}


#ifndef SIM_H
#define SIM_H
#include <cstdarg>
#include <algorithm>
#include "definitions.h"

class Sim
{
    public:
        Sim();
        virtual ~Sim();

        // getters
        state_t get_state();
        cell_pos_t get_central_cell();
        cell_pos_t get_neighbor(cell_pos_t, direction_t);
        cell_pos_vec_t get_cardinal_neighbors(cell_pos_t);
        cell_pos_vec_t get_intercardinal_neighbors(cell_pos_t);
        cell_pos_vec_t get_neighbors(cell_pos_t, const direction_vec_t&);
        cell_pos_vec_t get_neighbors(cell_pos_t, count_t, ...);
        #ifdef MOORE
        void get_neighborhood(cell_pos_t, neighborhood_t&);
        void get_top_left_corner_neighborhood(neighborhood_t&);
        void get_top_right_corner_neighborhood(neighborhood_t&);
        void get_bottom_right_corner_neighborhood(neighborhood_t&);
        void get_bottom_left_corner_neighborhood(neighborhood_t&);
        void get_top_edge_neighborhood(cell_pos_t, neighborhood_t&);
        void get_right_edge_neighborhood(cell_pos_t, neighborhood_t&);
        void get_bottom_edge_neighborhood(cell_pos_t, neighborhood_t&);
        void get_left_edge_neighborhood(cell_pos_t, neighborhood_t&);
        #endif
        #ifdef VON_NEUMANN
        void get_neighborhood(cell_pos_t, neighborhood_t&);
        void get_top_left_corner_neighborhood(von_neumann_t&);
        void get_top_right_corner_neighborhood(von_neumann_t&);
        void get_bottom_right_corner_neighborhood(von_neumann_t&);
        void get_bottom_left_corner_neighborhood(von_neumann_t&);
        void get_top_edge_neighborhood(cell_pos_t, von_neumann_t&);
        void get_right_edge_neighborhood(cell_pos_t, von_neumann_t&);
        void get_bottom_edge_neighborhood(cell_pos_t, von_neumann_t&);
        void get_left_edge_neighborhood(cell_pos_t, neighborhood_t&);
        #endif

        // stats
        count_t total_cells();
        count_t total_live_cells();
        count_t live_neighbor_count(const neighborhood_t&);

        // checkers
        bool board_is_dead();
        bool cell_is_live(cell_pos_t);
        bool cell_is_dead(cell_pos_t);
        bool cells_are_live(const cell_pos_vec_t&);
        bool cells_are_live(count_t, ...);
        bool cells_are_live(cell_pos_t, const cell_pos_vec_t&);
        bool cells_are_dead(count_t, ...);
        bool is_edge_cell(cell_pos_t);

        // actions
        void seed(count_t, ...);
        void seed(cell_pos_t, const cell_pos_vec_t&);
        void seed(const cell_pos_vec_t&);
        void generate_seed();
        void evolve(void);

        void print_live_members();
        void print_current_state();

        void glider_seed();

    protected:

    private:
        void __get_neighborhood(cell_pos_t, neighborhood_t&);

        state_t current_state;
};

#endif // SIM_H

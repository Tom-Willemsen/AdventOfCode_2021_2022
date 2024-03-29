#include "day15_impl.h"

struct sizes {
    uint64_t grid_x;
    uint64_t grid_y;
    uint64_t data_x;
    uint64_t data_y;
};

static inline int64_t id_from_coord(struct sizes* sizes, int64_t x, int64_t y) {
    return sizes->grid_x * y + x;
}

static inline void coord_from_id(int64_t id, struct sizes* sizes, int64_t* x, int64_t* y) {
    *y = id / sizes->grid_x;
    *x = id % sizes->grid_x;
}

static inline uint64_t risk(uint8_t** data, struct sizes* sizes, int64_t x, int64_t y) {
    int64_t v = data[y%sizes->data_y][x%sizes->data_x] + y / sizes->data_y + x / sizes->data_x;
    return ((v-1)%9)+1;
}

static int64_t solve(uint8_t** data, struct sizes* sizes) {
    int64_t current, next, cx, cy, cost, currcost;
    int64_t nx[4], ny[4];
    
    // worst-case optimal path, the grid is full of 9's.
    int64_t worst_cost = 9*(sizes->grid_x + sizes->grid_y);
    
    sized_priorityQ_i64* openset = sized_priorityQ_i64_init(0, worst_cost);
    sized_priorityQ_i64_push(openset, 0, 0);

    map_i64* knowncosts = map_i64_init(sizes->grid_y*sizes->grid_x/2);
    map_i64_set(knowncosts, 0, 0);
    
    while (sized_priorityQ_i64_size(openset) > 0) {
        current = sized_priorityQ_i64_pop(openset);
        coord_from_id(current, sizes, &cx, &cy);
        
        nx[0] = cx+1;  ny[0] = cy;
        nx[1] = cx;    ny[1] = cy+1;
        nx[2] = cx-1;  ny[2] = cy;
        nx[3] = cx;    ny[3] = cy-1;
        
        currcost = map_i64_get(knowncosts, current, worst_cost);
        for (uint64_t i=0; i<4; ++i) {
            if (nx[i] < sizes->grid_x && ny[i] < sizes->grid_y && nx[i] >= 0 && ny[i] >= 0) {
                next = id_from_coord(sizes, nx[i], ny[i]);
                cost = currcost + risk(data, sizes, nx[i], ny[i]);
                
                if (cost < map_i64_get(knowncosts, next, worst_cost)) {
                    map_i64_set(knowncosts, next, cost);
                    sized_priorityQ_i64_push(openset, cost, next);
                }
            }
        }
    }
    
    cost = map_i64_get(knowncosts, id_from_coord(sizes, sizes->grid_x-1, sizes->grid_y-1), worst_cost);

    sized_priorityQ_i64_free(openset);
    map_i64_free(knowncosts);
    
    return cost;
}

void calculate(uint8_t** data, uint64_t ysize, uint64_t xsize, int64_t* part1, int64_t* part2) {
    struct sizes sizes = { .data_x = xsize, .data_y = ysize, .grid_x = xsize, .grid_y = ysize};
    *part1 = solve(data, &sizes);
    sizes.grid_x = xsize*5;
    sizes.grid_y = ysize*5;
    *part2 = solve(data, &sizes);
}

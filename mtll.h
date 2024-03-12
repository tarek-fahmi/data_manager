#ifndef MTLL_H
#define MTLL_H

struct mtll {
    // Define your struct here
};

// A few suggested function prototypes:
// Feel free to change or improve these as you need.

extern struct mtll *mtll_create();

extern void mtll_free(struct mtll *);

extern void mtll_view(struct mtll *);

extern void mtll_view_all(struct mtll **);

extern void mtll_remove(struct mtll **, struct mtll *);

// You will likely need other functions for Parts 2 and 3,
// And for general input / output management

#endif
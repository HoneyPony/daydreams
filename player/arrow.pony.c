#include "my.ponygame.h"

// Automatically copied header lines. May not be useful.

void construct_Arrow(Arrow *self) {
	
}



// void destruct_Arrow(Arrow *self) { }

void tick_Arrow(Arrow *self, ArrowTree *tree) {
	// Super method
	process_Sprite(self, NULL);

	// Physics
	set_lpos(self, add(get_gpos(self), mul(self->velocity, get_dt())));
}


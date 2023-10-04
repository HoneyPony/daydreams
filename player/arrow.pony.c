#include "my.ponygame.h"

// Automatically copied header lines. May not be useful.

void construct_Arrow(Arrow *self) {
	self->lifetime = 0; // Must re-initialize	
}



// void destruct_Arrow(Arrow *self) { }

void tick_Arrow(Arrow *self, ArrowTree *tree) {
	// Super method
	process_Sprite(self, NULL);

	// Physics
	set_lpos(self, add(get_gpos(self), mul(self->velocity, get_dt())));

	self->lifetime += get_dt();
	if(self->lifetime > 1.5) {
		node_destroy(self);
	}

	// End spawning animation
	if(self->current_animation == &res.player.arrow_spawn_tex.loop) {
		if(self->current_frame == 4) {
			sprite_play(self, &res.player.arrow1_tex.loop);
		}
	}
}


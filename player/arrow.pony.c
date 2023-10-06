#include "my.ponygame.h"

// Automatically copied header lines. May not be useful.

void construct_Arrow(Arrow *self) {
	self->lifetime = 0; // Must re-initialize	

	float hsv[] = { 1.0, 0.5, 1.0 };
	float min_hue = 215 / 360.0;
	float max_hue = 290 / 360.0;
	hsv[0] = randf_range(min_hue, max_hue); // random hue
	sprite_set_hsv((Sprite*)self, hsv);

	sh_add(&arrow_hash, self, &self->ref);
}


void
destruct_Arrow(Arrow *self) {
	//logf_info("destructing arrow %p", self);
	sh_remove(&arrow_hash, self, &self->ref);
}

void tick_Arrow(Arrow *self, ArrowTree *tree) {
	// Super method
	process_Sprite(self, NULL);

	// Physics
	set_lpos(self, add(get_gpos(self), mul(self->velocity, get_dt())));

	// Must do this before the node_destroy.
	sh_update(&arrow_hash, self, &self->ref);

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


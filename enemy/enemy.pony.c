#include "my.ponygame.h"

// Automatically copied header lines. May not be useful.

void
construct_Enemy(Enemy *self) {
	self->velocity = vxy(0, 0);
}

// void destruct_Enemy(Enemy *self) { }

static bool
check_collision(Enemy *self, Arrow *arr) {
	float r1 = 128;
	float r2 = 64;

	float dist = length(sub(get_gpos(arr), get_gpos(self)));
	return dist <= r1 + r2;
}

static bool
check_collisions(Enemy *self) {
	// Very slow physics implementation FOR NOW.
	Arrow *ar = node_header(Arrow).list_allocated.next_node;
	while(ar) {
		if(check_collision(self, ar)) {
			return true;
		}

		ar = ar->internal.links.next_node;
	}
	return false;
}

static void
ai(Enemy *self) {
	// Move towards player ...?

	vec2 dir_to_player = sub(get_gpos(player), get_gpos(self));
	vec2 desired_vel = mul(norm(dir_to_player), 500.0);

	vec2 accel = sub(desired_vel, self->velocity);
	float max_accel = length(accel);
	accel = mul(norm(accel), 1600.0 * get_dt());
	if(length(accel) > max_accel) {
		self->velocity = desired_vel;
	}
	else {
		self->velocity = add(self->velocity, accel);
	}

	// Basic physics
	ltranslate(self, mul(self->velocity, get_dt()));
}

void
tick_Enemy(Enemy *self, EnemyTree *tree) {
	// Super method
	process_Sprite(self, NULL);

	bool hit = check_collisions(self);
	if(hit) {
		node_destroy(self);
	}

	
	ai(self);
}


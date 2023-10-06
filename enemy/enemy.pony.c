#include "my.ponygame.h"

// Automatically copied header lines. May not be useful.

void
construct_Enemy(Enemy *self) {
	self->velocity = vxy(0, 0);
	self->health = 1;
}

// void destruct_Enemy(Enemy *self) { }

static bool
check_collision(Enemy *self, Arrow *arr) {
	float r1 = 128;
	float r2 = 64;

	float dist = length(sub(get_gpos(arr), get_gpos(self)));
	return dist <= r1 + r2;
}

static Arrow*
check_collisions(Enemy *self) {
	// Very slow physics implementation FOR NOW.
	/*Arrow *ar = node_header(Arrow).list_allocated.next_node;
	while(ar) {
		if(check_collision(self, ar)) {
			return ar;
		}

		ar = ar->internal.links.next_node;
	}
	return NULL;*/

	return sh_find_closest(&arrow_hash, get_gpos(self), 128 + 64);
}

static void
animate(Enemy *self) {
	float rot = sin(self->walk_anim_t) * 0.15;

	self->walk_anim_t += get_dt() * 8.0;
	self->walk_anim_t = fmod(self->walk_anim_t, PI * 2.0);

	set_lrot(self, rot);
}

static void
ai(Enemy *self) {
	// Move towards player ...?

	vec2 dir_to_player = sub(get_gpos(player), get_gpos(self));
	vec2 desired_vel = mul(norm(dir_to_player), 500.0);

	vec2 accel = sub(desired_vel, self->velocity);
	float max_accel = length(accel);
	accel = mul(norm(accel), 800.0 * get_dt());
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

	Arrow *hit = check_collisions(self);
	if(hit) {
		if(!hit->internal.is_valid) {
			logf_warn("warning! hit destroyed arrow! what!, %p", hit);
		}
		node_destroy(hit); // TODO: Arrow piercing

		self->health -= 1;
		if(self->health <= 0) {
			node_destroy(self);
		}
	}

	
	ai(self);
	animate(self);
}


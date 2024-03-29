#include "my.ponygame.h"

/* Enemy data tables defined by the ENEMY_TYPE index. */

float enemy_knockback[] = {
	1.0 /* ENEMY_PAPER */
};

int enemy_max_health[] = {
	4
};

void
construct_Enemy(Enemy *self) {
	self->velocity = vxy(0, 0);
	self->health = 4;
	self->type = 0;

	for(int i = 0; i < ENEMY_ARROW_TRACK_COUNT; ++i) {
		set_ref(self->arrow_tracker[i], NULL);
	}
	self->arrow_track_next = 0;

	sh_add(&enemy_hash, self, &self->ref);
}

Enemy*
enemy_new_with_type(int type) {
	Enemy *e = new(Enemy);
	e->type = type;

	e->health = enemy_max_health[type];
	return e;
}

void
destruct_Enemy(Enemy *self) {
	sh_remove(&enemy_hash, self, &self->ref);
}

static bool
check_collision(Enemy *self, Arrow *arr) {
	float r1 = 128;
	float r2 = 64;

	float dist = length(sub(get_gpos(arr), get_gpos(self)));
	return dist <= r1 + r2;
}

static int
filter_already_hit_arrows(AnyNode *candidate, void *user_data) {
	Enemy *self = user_data;
	for(int i = 0; i < ENEMY_ARROW_TRACK_COUNT; ++i) {
		if(unbox(self->arrow_tracker[i]) == candidate) return 0;
	}

	return 1;
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



	return sh_find_closest(&arrow_hash, get_gpos(self), 128 + 64,
		(sh_filter){
			.fn = filter_already_hit_arrows,
			.user_data = self
		});
}

static void
animate(Enemy *self) {
	float rot = sin(self->walk_anim_t) * 0.15;

	self->walk_anim_t += get_dt() * 8.0;
	self->walk_anim_t = fmod(self->walk_anim_t, PI * 2.0);

	set_lrot(self, rot);
}

static list_of(AnyNode*) enemy_repel_buffer = NULL;

static void
repel_from_others(Enemy *self) {
	if(!enemy_repel_buffer) {
		ls_init(enemy_repel_buffer);
	}

	vec2 my_pos = get_gpos(self);

	// Find all the nearby enemies
	ls_clear(enemy_repel_buffer);
	sh_find(&enemy_hash, my_pos, 128 * 2, &enemy_repel_buffer);

	vec2 offset = vxy(0, 0);

	foreach(enemy_node, enemy_repel_buffer, {
		vec2 p = get_gpos(enemy_node);
		vec2 dir = sub(p, my_pos);

		// Very strong fall-off using hyperbolic curve, but stretched a bit (0.001)
		float strength = 128.0 / (1.0 + 0.0007 * dot(dir, dir));

		offset = add(offset, mul(norm(dir), -strength));
	})

	ltranslate(self, offset);
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
		arrow_hit(hit);

		set_ref(self->arrow_tracker[self->arrow_track_next], hit);
		self->arrow_track_next = (self->arrow_track_next + 1) % ENEMY_ARROW_TRACK_COUNT;

		self->health -= 1;
		if(self->health <= 0) {
			node_destroy(self);
		}
		else {
			/* Apply knockback */
			self->velocity = add(self->velocity, mul(hit->velocity, enemy_knockback[self->type]));
		}
	}

	
	ai(self);
	repel_from_others(self);
	animate(self);

	if(self->internal.is_valid) {
		sh_update(&enemy_hash, self, &self->ref);
	}
}


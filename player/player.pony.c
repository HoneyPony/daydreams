#include "my.ponygame.h"

// Automatically copied header lines. May not be useful.

void construct_Player(Player *self) {
	self->walk_anim_t = 0;
	self->walk_vel_rot_smoothed = 0;
	self->arrow_timer = 0;
	self->arrows_per_second = 800;

	self->hue = 0;
}

// void destruct_Player(Player *self) { }

static vec2
get_input() {
	vec2 result = vxy(0, 0);
	if(keys.A.pressed) {
		result.x -= 1;
	}
	if(keys.D.pressed) {
		result.x += 1;
	}
	if(keys.W.pressed) {
		result.y += 1;
	}
	if(keys.S.pressed) {
		result.y -= 1;
	}
	return norm(result);
}

float change_angle_for_flip(float rot, float flip) {
	//logf_info("rot = %f\n", rot);
	if(flip < 0) {
		
		rot = -rot;
	}
	return rot;
}

static void
update_hue(Player *self) {
	// Rotate hue over time: 1 minute per cycle
	self->hue = fmod(self->hue + get_dt() * (1.0 / 60.0), 1.0);

	float hsv[] = { 1.0, 1.0, 1.0 };
	hsv[0] = self->hue;
	sprite_set_hsv(self->tree.sprite, hsv);
}

static void
animate(Player *self) {
	if(self->velocity.x > 100) {
		set_lscale(self->tree.sprite, vxy(1, 1));
	}
	if(self->velocity.x < -100) {
		set_lscale(self->tree.sprite, vxy(-1, 1));
	}

	float rot = 0;
	rot += sin(self->walk_anim_t) * 0.15;

	float walk_speed = clamp(length(self->velocity) / 750, 0.0, 1.0);
	self->walk_anim_t += get_dt() * walk_speed * 8.0;
	self->walk_anim_t = fmod(self->walk_anim_t, PI * 2.0);

	float atan_vel = atan2(self->velocity.y, abs(self->velocity.x));
	atan_vel *= 0.25; // Bring closer to 0

	// Smooth out (lpf)
	self->walk_vel_rot_smoothed += (atan_vel - self->walk_vel_rot_smoothed) * 0.2;

	rot += change_angle_for_flip(self->walk_vel_rot_smoothed, get_lscale(self->tree.sprite).x);

	set_lrot(self->tree.sprite, rot);

	update_hue(self);
}

static void
shoot(Player *self) {
	Arrow *ar = new(Arrow);
	reparent(ar, root);

	const float SPAWN_SPREAD = 600;
	const float VEL_SPREAD = 50;


	// Spawn arrows from random locations that all head precisely towards
	// mouse
	//
	// Idea: Player can control arrow locations both by moving the character
	// and by moving the mouse
	vec2 r_spawn_spread = vxy(randf_range(-SPAWN_SPREAD, SPAWN_SPREAD), randf_range(-SPAWN_SPREAD, SPAWN_SPREAD));
	vec2 pos = add(get_lpos(self), r_spawn_spread);
	set_lpos(ar, pos);

	//set_lpos(ar, get_lpos(self));
	
	// Compute velocity, with random spread
	// NOTE: This spread implementation lets you get less spread if you move
	// the mouse farther away -- do we want that?
	vec2 r_vel_spread = vxy(randf_range(-VEL_SPREAD, VEL_SPREAD), randf_range(-VEL_SPREAD, VEL_SPREAD));
	vec2 v = sub(add(mouse_global(), r_vel_spread), pos);
	v = mul(norm(v), 1000);

	ar->velocity = v;

	set_lrot(ar, atan2(v.y, v.x));
}

static void
physics(Player *self) {
	vec2 accel = mul(get_input(), 1600);

	if(length(accel) < 2 && length(self->velocity) > 0) {
		accel = mul(norm(self->velocity), -1600);
		if(length(accel) * get_dt() > length(self->velocity)) {
			self->velocity = vxy(0, 0);
			accel = vxy(0, 0);
		}
	}

	self->velocity = add(self->velocity, mul(accel, get_dt()));

	if(length(self->velocity) > 800) {
		self->velocity = mul(norm(self->velocity), 800);
	}

	set_lpos(self, add(get_lpos(self), mul(self->velocity, get_dt())));
}

void
tick_Player(Player *self, PlayerTree *tree) {
	physics(self);
	animate(self);

	float arrow_time_chunk = 1.0 / self->arrows_per_second;
	self->arrow_timer += get_dt();
	int shots = 0;
	while(self->arrow_timer >= arrow_time_chunk) {
		if(mouse.left.pressed) {
			shoot(self);
		}
		self->arrow_timer -= arrow_time_chunk;
		shots += 1;
	}
	//logf_info("shots = %d", shots);
}


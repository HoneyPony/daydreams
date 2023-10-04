#include "my.ponygame.h"

// Automatically copied header lines. May not be useful.

void construct_Player(Player *self) {
	
}

// void destruct_Player(Player *self) { }

vec2 get_input() {
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

void animate(Player *self) {
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
}

void tick_Player(Player *self, PlayerTree *tree) {
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

	animate(self);
}


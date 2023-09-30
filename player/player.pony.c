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
}


#include "my.ponygame.h"
#include "pony.main.h"

const char *game_title = "Ludum Dare 54";
bool pixel_art_game = false;
bool may_assume_opaque = false;
bool disable_pixel_perfect_framebuffer = true;

// --- Global Variables ---
Player *player;

float enemy_timer = 0.0;
const float enemy_timer_max = 4.0;

impl_begin {
	render_set_target_screen_size(1500 * 2.5, 1000 * 2.5);

	float clear[4] = { 0.8, 0.8, 0.8, 1.0 };
	memcpy(clear_color, clear, sizeof(clear));

	/*Sprite *paper = new(Sprite);
	paper->z_index = -5;
	set_lscale(paper, vxy(0.5, 0.5));
	sprite_play(paper, &res.oga.paper_texture_tex.statc);
	reparent(paper, root);*/

	player = new(Player);
	reparent(player, root);

	//reparent(new(Enemy), root);
}

impl_tick_start {
	
}

void spawn_enemy() {
	Enemy *e = new(Enemy);
	float x = randf_range(-2000, 2000);
	float y = randf_range(0, 1) < 0.5 ? 2000 : -2000;

	if(randf_range(0, 1) < 0.5) {
		// Swap
		float tmp = x;
		x = y;
		y = tmp;
	}

	set_lpos(e, vxy(x, y));
	reparent(e, root);
}

impl_tick_end {
	// Done at end of ticks so as not to affect physics
	enemy_timer += get_dt();
	if(enemy_timer > enemy_timer_max) {
		enemy_timer = 0;
		for(int i = 0; i < 7; ++i) spawn_enemy();
	}
}

#include "my.ponygame.h"
#include "pony.main.h"

const char *game_title = "Ludum Dare 54";
bool pixel_art_game = false;
bool may_assume_opaque = false;
bool disable_pixel_perfect_framebuffer = true;

// --- Global Variables ---
Player *player;

impl_begin {
	render_set_target_screen_size(1500 * 2, 1000 * 2);

	float clear[4] = { 0.6, 0.6, 0.6, 1.0 };
	memcpy(clear_color, clear, sizeof(clear));

	/*Sprite *paper = new(Sprite);
	paper->z_index = -5;
	set_lscale(paper, vxy(0.5, 0.5));
	sprite_play(paper, &res.oga.paper_texture_tex.statc);
	reparent(paper, root);*/

	player = new(Player);
	reparent(player, root);
}

impl_tick_start {
	
}

impl_tick_end {
	
}

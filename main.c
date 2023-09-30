#include "my.ponygame.h"
#include "pony.main.h"

const char *game_title = "Ludum Dare 54";
bool pixel_art_game = false;
bool may_assume_opaque = false;
bool disable_pixel_perfect_framebuffer = true;

// --- Global Variables ---
Player *player;

impl_begin {
	render_set_target_screen_size(1500, 1000);

	float clear[4] = { 0.6, 0.6, 0.6, 1.0 };
	memcpy(clear_color, clear, sizeof(clear));

	player = new(Player);
	reparent(player, root);
}

impl_tick_start {
	
}

impl_tick_end {
	
}

#include "my.ponygame.h"
#include "pony.main.h"

const char *game_title = "Ludum Dare 54";
bool pixel_art_game = false;
bool may_assume_opaque = false;

impl_begin {
	render_set_target_screen_size(1500, 1000);

	Sprite* s = new(Sprite);
	sprite_play(s, &res.player.face_tex.loop);

	reparent(s, root);
}

impl_tick_start {
	
}

impl_tick_end {
	
}
